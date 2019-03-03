/*
**********************ѭ��������Լɪ������***********************
* ���⣺Լɪ��
* �б�Ŵ�1��N��N��������һȦ�������ӵ�K���˿�ʼ����������M���˳��֣�
* ��һλ�ٴ�1��ʼ��������˳�����ֱֹʣ��һλΪֹ��������˵ı��X��
* ����N,K,M�����X��
[cpp] view plain copy
*********************************************************************
*/

#include <iostream>  
using namespace std;

struct MyNode
{
	MyNode(int a_data) :m_data(a_data), m_pNext(NULL) {}
	int    m_data;
	MyNode *m_pNext;
};

class Josephus
{
public:
	Josephus(int a_N, int a_K, int a_M) :m_N(a_N), m_K(a_K), m_M(a_M)
	{
		createList();
		outputList();
	}
protected:
	void createList();
	void outputList();
private:
	MyNode *m_pHead;//ѭ�������ͷ�ڵ�  
	int    m_N;     //����ڵ����  
	int    m_K;     //��һ�������˵����  
	int    m_M;     //�������ֵ���  
};
void Josephus::createList()
{
	MyNode *pre = NULL;
	MyNode *cur = NULL;
	MyNode *p = new MyNode(1);
	m_pHead = p;
	cur = p;
	for (int i = 2; i <= m_N; i++)
	{
		p = new MyNode(i);
		pre = cur;
		cur = p;
		pre->m_pNext = cur;
	}
	cur->m_pNext = m_pHead;
	int n = m_N;
	p = m_pHead;
	while (n--)
	{
		cout << p->m_data << ",";
		p = p->m_pNext;
	}
	cout << endl;
}

void Josephus::outputList()
{
	MyNode *pre = NULL;
	MyNode *cur = m_pHead;
	m_K;
	while (m_K--)            //Ѱ�ҵ�K���ˣ���ʼ�������ˣ�  
	{
		pre = cur;
		cur = cur->m_pNext;
	}
	while (m_N--)            //������������еĽڵ�ֵ  
	{
		int s = m_M - 1;
		while (s--)            //Ѱ�Ҽ��M����  
		{
			pre = cur;
			cur = cur->m_pNext;
		}
		MyNode *p = cur;
		cout << p->m_data << ",";
		cur = cur->m_pNext;    //ɾ���ڵ�Ĺ���  
		pre->m_pNext = cur;
		delete p;
		p = NULL;
	}
}

int mainqq()
{
	Josephus josephus(100, 5, 5);
	return 0;
}