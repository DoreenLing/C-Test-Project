#pragma once
#include <vector>
#include <list>
#include <WinSock2.h> 

//#include <cstdlib>
//#include <ctime>
#pragma comment(lib,"ws2_32.lib")//引用库文件

#define MAX_NUM_BUF 1024
 //DWORD WINAPI AcceptThread(Server param_s);//接收客户端连接

class Server {
public:
	

	bool conning_s;        //与客户端的链接标志
	bool send_s;           //发送标记
	SOCKET socket_s;       //服务器端监听
	CRITICAL_SECTION cs;   //保护数据的临界区对象
	HANDLE acceptthread_s; //数据处理线程句柄
	HANDLE recvthread_s;   //数据接收线程
	//list<SOCKET> clientvector;
//	vector<int>clientvector;//客户端接口容器
	//vector<int>clientvector;

public:
	Server();             //构造函数
	bool InitSever();     //初始化服务器
	bool InitSocket();    //初始化套接字
	bool StarServer();    //启动服务器
	bool CreatAcceptThread(); //创建客户端需求线程
	int AcceptThreadDo();//接收客户端连接
	void InAndOut();      //处理数据
	bool RecvLine(SOCKET s,char* buf);//读一行数据
	bool RecvData(SOCKET s, char* buf);//读取数据
	bool SendData(SOCKET s, char* buf);    //发送数据
	void HandleData(char *buf);  //选择数据的客户端
	void ExitServer();           //释放资源
	void ShowTipMsg(bool firstinput);//显示标签
	void ShowServerStatue(bool statue);//显示服务器状态
};
