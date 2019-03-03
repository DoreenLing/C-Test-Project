#pragma once
#include <vector>
#include <list>
#include <WinSock2.h> 

//#include <cstdlib>
//#include <ctime>
#pragma comment(lib,"ws2_32.lib")//���ÿ��ļ�

#define MAX_NUM_BUF 1024
 //DWORD WINAPI AcceptThread(Server param_s);//���տͻ�������

class Server {
public:
	

	bool conning_s;        //��ͻ��˵����ӱ�־
	bool send_s;           //���ͱ��
	SOCKET socket_s;       //�������˼���
	CRITICAL_SECTION cs;   //�������ݵ��ٽ�������
	HANDLE acceptthread_s; //���ݴ����߳̾��
	HANDLE recvthread_s;   //���ݽ����߳�
	//list<SOCKET> clientvector;
//	vector<int>clientvector;//�ͻ��˽ӿ�����
	//vector<int>clientvector;

public:
	Server();             //���캯��
	bool InitSever();     //��ʼ��������
	bool InitSocket();    //��ʼ���׽���
	bool StarServer();    //����������
	bool CreatAcceptThread(); //�����ͻ��������߳�
	int AcceptThreadDo();//���տͻ�������
	void InAndOut();      //��������
	bool RecvLine(SOCKET s,char* buf);//��һ������
	bool RecvData(SOCKET s, char* buf);//��ȡ����
	bool SendData(SOCKET s, char* buf);    //��������
	void HandleData(char *buf);  //ѡ�����ݵĿͻ���
	void ExitServer();           //�ͷ���Դ
	void ShowTipMsg(bool firstinput);//��ʾ��ǩ
	void ShowServerStatue(bool statue);//��ʾ������״̬
};
