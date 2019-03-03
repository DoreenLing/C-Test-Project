#include "MultThread_s.h"
#include <iostream> 
using namespace std;
vector<int>a;
//function:构造函数，初始化变量
vector <int> clientvector;
char databuf[MAX_NUM_BUF];//缓冲区
DWORD WINAPI AcceptThread(Server *param_s);//接收客户端连接
Server::Server()
{
	conning_s = false;        //与客户端的链接标志
	send_s = false;           //发送标记
	socket_s = INVALID_SOCKET;       //服务器端监听
	acceptthread_s = NULL; //数据处理线程句柄
	recvthread_s = NULL;   //数据接收线程
	clientvector.clear();  //客户端接口容器
	InitializeCriticalSection(&cs);//初始化临界区对象
}

//function:初始化服务器
bool Server::InitSever()
{
	if (!InitSocket()) {
		return false;
	}
	return true;
}

//function:初始化套接字
bool Server::InitSocket()
{
	int reval;
	
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2),&wsadata) != 0)
	{
		return false;
	}

	//创建用于监听的套接字
	socket_s = socket(AF_INET,SOCK_STREAM,0);

	//设置套接字非阻塞模式
	//unsigned long u1 = 1;
	//reval = ioctlsocket(socket_s,FIONBIO,(unsigned long*)&u1);
	//if (reval == SOCKET_ERROR) {
	//	return false;
	//}

	//绑定套接字
	SOCKADDR_IN addr_s;
	addr_s.sin_family = AF_INET;
	addr_s.sin_port = htons(8888);
	addr_s.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	reval = bind(socket_s,(LPSOCKADDR)&addr_s,sizeof(SOCKADDR_IN));
	if (reval == SOCKET_ERROR) {
		return false;
	}

	//监听
	reval = listen(socket_s,10);
	if (reval == SOCKET_ERROR) {
		return false;
	}

	//等待客户端连接
	cout << "***** server succeeded ! *****" << endl;
	cout << "***** waiting for clients...... *****" << endl;
	return true;
}

//function:启动服务器
bool Server::StarServer()
{
	bool reval = true; //返回值
	ShowTipMsg(reval);//提示用户输入
	char input;
	cin >> input;
	if (input == 's'||input == 'S') {
		if (CreatAcceptThread()) {
			ShowServerStatue(reval);
		}
		else {
			reval = false;
		}
		send_s = true;
	}
	return reval;
}

//function:创建客户端需求线程
bool Server::CreatAcceptThread()
{
	conning_s = true;//设置服务器的运行状态
	unsigned long threadid; //返回线程的ID号
	//Server *param_s = new Server;
	acceptthread_s = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)AcceptThread,this,0,&threadid);
	
	if (acceptthread_s == NULL) {
		conning_s = false;
		return false;
	}
	else CloseHandle(acceptthread_s);
	return true;
}

DWORD WINAPI AcceptThread(Server *param_s)
{
//	Server server;
	
	return param_s->AcceptThreadDo();
}
//function:接收客户端连接
int Server::AcceptThreadDo()
{
	cout << "read the thread......" << endl;
	SOCKET accept_s;
	sockaddr_in addrclient;
	int len = sizeof(sockaddr_in);
	while (conning_s) {
		//memset(&addrclient,0,len);
		int len = sizeof(SOCKADDR);
		accept_s = accept(socket_s,(SOCKADDR *)&addrclient,&len);
		if (accept_s == INVALID_SOCKET) {
			Sleep(100);
			//无法完成一个非阻塞性的套接字
			if (WSAGetLastError() == WSAEWOULDBLOCK) {
				Sleep(100);
				continue;
			}
			else {
				cout << accept_s << endl;
				return 0;//线程退出
			}
		}
		else {//接收客户端的请求
			char* clientip = inet_ntoa(addrclient.sin_addr);
			u_short clientport = ntohs(addrclient.sin_port);
			cout << "***** accept the client *****" << endl;
			cout << "IP: " << clientip << "\tport: " << clientport << endl;
			//加入容器
			clientvector.push_back(accept_s);
		}
	}
	cout << WSAGetLastError()<< endl;
	cout << accept_s << endl;
	return 0;//线程退出
}

//function:处理数据
void Server::InAndOut()
{
	while (conning_s) {
		memset(databuf,0,MAX_NUM_BUF);
		cin.getline(databuf, MAX_NUM_BUF);//输入数据
		//发送数据
		if (send_s) {
			HandleData(databuf);
		}
	}
}

//function:读一行数据
//param: s 端口
//param: buf 数据缓存
bool Server::RecvLine(SOCKET s, char* buf)
{
	bool reval = true;    //返回值
	bool lineend = false; //行结束
	int readlen = 0; //读入字节数
	int datalen = 0;  //数据长度
	memset(buf,0,MAX_NUM_BUF); //清空接收缓存区
	while (!lineend && conning_s) {
		readlen = recv(s,buf + datalen,1,0);//每次接收一个字节
		//错误处理
		if (readlen == SOCKET_ERROR) {
			//接收数据缓冲区不可用
			int errcode = WSAGetLastError();
			if (errcode == WSAEWOULDBLOCK) {
				continue;
			}
			else if (WSAENETDOWN == errcode || WSAETIMEDOUT == errcode || WSAECONNRESET == errcode) {
				reval = false;
				break;
			}
		}
		if (readlen == 0) {
			reval = false;
			break;
		}
		if (*(buf + datalen) == '\n') {
			lineend = true;
			send_s = true;
		}
		else {
			datalen += readlen;
		}
	}
	return reval;
}

//function:读取数据
//param: s 子线程套接字端口
//param: buf 数据缓存
bool Server::RecvData(SOCKET s, char* buf)
{
	bool reval = true;    //返回值
	bool lineend = false; //行结束
	int readlen = 0; //读入字节数
	memset(buf, 0, MAX_NUM_BUF); //清空接收缓存区
	while (!lineend && conning_s) {
		readlen = recv(s, buf ,MAX_NUM_BUF, 0);
											   //错误处理
		if (readlen == SOCKET_ERROR) {
			//接收数据缓冲区不可用
			int errcode = WSAGetLastError();
			if (errcode == WSAEWOULDBLOCK) {
				continue;
			}
			else if (WSAENETDOWN == errcode || WSAETIMEDOUT == errcode || WSAECONNRESET == errcode) {
				reval = false;
				break;
			}
		}
		if (readlen == 0) {
			reval = false;
			break;
		}
		lineend = true;
	}
	return reval;
}

//function:发送数据
bool Server::SendData(SOCKET s, char* buf)
{
	bool lineend = false;
	int sendlen = 0;
	bool reval = true;
	while (!lineend && conning_s) {
		sendlen = send(s, buf,strlen(buf),0);
		if (sendlen == SOCKET_ERROR){
			int errcode = WSAGetLastError();
			if (errcode == WSAEWOULDBLOCK) {
				continue;
			}
			else if (WSAENETDOWN == errcode || WSAETIMEDOUT == errcode || WSAECONNRESET == errcode) {
				reval = false;
				break;
			}
		}
		lineend = true;
	}
	return reval;
}

//function:选择数据的客户端
void Server::HandleData(char *buf)
{
	SOCKET client;
	char cnum; //显示几号套接字
	int num; //指定客户端
	char str1[] = "write";
	char str2[] = "read";
	if (!strncmp(str1,buf,strlen(str1))) {
		buf += strlen(str1);
		//cnum = *buf++;
		num = *buf - '0';
		if(num < clientvector.size())
			client = clientvector.at(num);//提取指定客户端
		if (!SendData(client,buf)) {
			ExitServer();
		}
	}
	else if (!strncmp(str2, buf, strlen(str2))) {
		buf += strlen(str2);
		cnum = *buf++;
		num = cnum - '0';
		client = clientvector.at(num);//提取指定客户端
		if (!RecvData(client, buf)) {
			ExitServer();
		}
	}
	//判断是否退出
	else if ((buf[0] == 'e' || buf[0] == 'E') &&(buf[1] == '\n')) {
		conning_s = false;
		ExitServer();
		ShowTipMsg(false);
	}
	else {
		cout << "***** input error !! *****" << endl;
	}
}

//function:释放资源
void Server::ExitServer()
{
	closesocket(socket_s);
	WSACleanup();
}

//function:显示标签
void Server::ShowTipMsg(bool firstinput)
{
	if (firstinput)//第一次
	{
		cout << endl;
		cout << endl;
		cout << "**********************" << endl;
		cout << "* s(S): Start server *" << endl;
		cout << "**********************" << endl;
		cout << "Please input:";

	}
	else {//退出服务器
		cout << endl;
		cout << endl;
		cout << "**********************" << endl;
		cout << "* e(E): Exit  server *" << endl;
		cout << "**********************" << endl;
		cout << " Please input: ";
	}
}

//function:显示服务器状态
void Server::ShowServerStatue(bool statue)
{
	if (statue)
	{
		cout << "**********************" << endl;
		cout << "* Server succeeded!  *" << endl;
		cout << "**********************" << endl;
	}
	else {
		cout << "**********************" << endl;
		cout << "* Server failed   !  *" << endl;
		cout << "**********************" << endl;
	}
}

void main()
{
	a.push_back(1);
	Server server;
	server.InitSever();
	server.StarServer();
	server.InAndOut();
	system("pause");
}