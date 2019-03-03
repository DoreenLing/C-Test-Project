#include "MultThread_s.h"
#include <iostream> 
using namespace std;
vector<int>a;
//function:���캯������ʼ������
vector <int> clientvector;
char databuf[MAX_NUM_BUF];//������
DWORD WINAPI AcceptThread(Server *param_s);//���տͻ�������
Server::Server()
{
	conning_s = false;        //��ͻ��˵����ӱ�־
	send_s = false;           //���ͱ��
	socket_s = INVALID_SOCKET;       //�������˼���
	acceptthread_s = NULL; //���ݴ����߳̾��
	recvthread_s = NULL;   //���ݽ����߳�
	clientvector.clear();  //�ͻ��˽ӿ�����
	InitializeCriticalSection(&cs);//��ʼ���ٽ�������
}

//function:��ʼ��������
bool Server::InitSever()
{
	if (!InitSocket()) {
		return false;
	}
	return true;
}

//function:��ʼ���׽���
bool Server::InitSocket()
{
	int reval;
	
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2),&wsadata) != 0)
	{
		return false;
	}

	//�������ڼ������׽���
	socket_s = socket(AF_INET,SOCK_STREAM,0);

	//�����׽��ַ�����ģʽ
	//unsigned long u1 = 1;
	//reval = ioctlsocket(socket_s,FIONBIO,(unsigned long*)&u1);
	//if (reval == SOCKET_ERROR) {
	//	return false;
	//}

	//���׽���
	SOCKADDR_IN addr_s;
	addr_s.sin_family = AF_INET;
	addr_s.sin_port = htons(8888);
	addr_s.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	reval = bind(socket_s,(LPSOCKADDR)&addr_s,sizeof(SOCKADDR_IN));
	if (reval == SOCKET_ERROR) {
		return false;
	}

	//����
	reval = listen(socket_s,10);
	if (reval == SOCKET_ERROR) {
		return false;
	}

	//�ȴ��ͻ�������
	cout << "***** server succeeded ! *****" << endl;
	cout << "***** waiting for clients...... *****" << endl;
	return true;
}

//function:����������
bool Server::StarServer()
{
	bool reval = true; //����ֵ
	ShowTipMsg(reval);//��ʾ�û�����
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

//function:�����ͻ��������߳�
bool Server::CreatAcceptThread()
{
	conning_s = true;//���÷�����������״̬
	unsigned long threadid; //�����̵߳�ID��
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
//function:���տͻ�������
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
			//�޷����һ���������Ե��׽���
			if (WSAGetLastError() == WSAEWOULDBLOCK) {
				Sleep(100);
				continue;
			}
			else {
				cout << accept_s << endl;
				return 0;//�߳��˳�
			}
		}
		else {//���տͻ��˵�����
			char* clientip = inet_ntoa(addrclient.sin_addr);
			u_short clientport = ntohs(addrclient.sin_port);
			cout << "***** accept the client *****" << endl;
			cout << "IP: " << clientip << "\tport: " << clientport << endl;
			//��������
			clientvector.push_back(accept_s);
		}
	}
	cout << WSAGetLastError()<< endl;
	cout << accept_s << endl;
	return 0;//�߳��˳�
}

//function:��������
void Server::InAndOut()
{
	while (conning_s) {
		memset(databuf,0,MAX_NUM_BUF);
		cin.getline(databuf, MAX_NUM_BUF);//��������
		//��������
		if (send_s) {
			HandleData(databuf);
		}
	}
}

//function:��һ������
//param: s �˿�
//param: buf ���ݻ���
bool Server::RecvLine(SOCKET s, char* buf)
{
	bool reval = true;    //����ֵ
	bool lineend = false; //�н���
	int readlen = 0; //�����ֽ���
	int datalen = 0;  //���ݳ���
	memset(buf,0,MAX_NUM_BUF); //��ս��ջ�����
	while (!lineend && conning_s) {
		readlen = recv(s,buf + datalen,1,0);//ÿ�ν���һ���ֽ�
		//������
		if (readlen == SOCKET_ERROR) {
			//�������ݻ�����������
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

//function:��ȡ����
//param: s ���߳��׽��ֶ˿�
//param: buf ���ݻ���
bool Server::RecvData(SOCKET s, char* buf)
{
	bool reval = true;    //����ֵ
	bool lineend = false; //�н���
	int readlen = 0; //�����ֽ���
	memset(buf, 0, MAX_NUM_BUF); //��ս��ջ�����
	while (!lineend && conning_s) {
		readlen = recv(s, buf ,MAX_NUM_BUF, 0);
											   //������
		if (readlen == SOCKET_ERROR) {
			//�������ݻ�����������
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

//function:��������
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

//function:ѡ�����ݵĿͻ���
void Server::HandleData(char *buf)
{
	SOCKET client;
	char cnum; //��ʾ�����׽���
	int num; //ָ���ͻ���
	char str1[] = "write";
	char str2[] = "read";
	if (!strncmp(str1,buf,strlen(str1))) {
		buf += strlen(str1);
		//cnum = *buf++;
		num = *buf - '0';
		if(num < clientvector.size())
			client = clientvector.at(num);//��ȡָ���ͻ���
		if (!SendData(client,buf)) {
			ExitServer();
		}
	}
	else if (!strncmp(str2, buf, strlen(str2))) {
		buf += strlen(str2);
		cnum = *buf++;
		num = cnum - '0';
		client = clientvector.at(num);//��ȡָ���ͻ���
		if (!RecvData(client, buf)) {
			ExitServer();
		}
	}
	//�ж��Ƿ��˳�
	else if ((buf[0] == 'e' || buf[0] == 'E') &&(buf[1] == '\n')) {
		conning_s = false;
		ExitServer();
		ShowTipMsg(false);
	}
	else {
		cout << "***** input error !! *****" << endl;
	}
}

//function:�ͷ���Դ
void Server::ExitServer()
{
	closesocket(socket_s);
	WSACleanup();
}

//function:��ʾ��ǩ
void Server::ShowTipMsg(bool firstinput)
{
	if (firstinput)//��һ��
	{
		cout << endl;
		cout << endl;
		cout << "**********************" << endl;
		cout << "* s(S): Start server *" << endl;
		cout << "**********************" << endl;
		cout << "Please input:";

	}
	else {//�˳�������
		cout << endl;
		cout << endl;
		cout << "**********************" << endl;
		cout << "* e(E): Exit  server *" << endl;
		cout << "**********************" << endl;
		cout << " Please input: ";
	}
}

//function:��ʾ������״̬
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