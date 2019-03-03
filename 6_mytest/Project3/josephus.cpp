/*
**********************循环链表解决约瑟夫环问题***********************
* 问题：约瑟夫环
* 有编号从1到N的N个人坐成一圈报数，从第K个人开始报数，报到M的人出局，
* 下一位再从1开始报数，如此持续，直止剩下一位为止，报告此人的编号X。
* 输入N,K,M，求出X。
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
	MyNode *m_pHead;//循环链表的头节点  
	int    m_N;     //链表节点个数  
	int    m_K;     //第一个报数人的序号  
	int    m_M;     //报数出局的数  
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
	while (m_K--)            //寻找第K个人（开始报数的人）  
	{
		pre = cur;
		cur = cur->m_pNext;
	}
	while (m_N--)            //输出链表中所有的节点值  
	{
		int s = m_M - 1;
		while (s--)            //寻找间隔M的人  
		{
			pre = cur;
			cur = cur->m_pNext;
		}
		MyNode *p = cur;
		cout << p->m_data << ",";
		cur = cur->m_pNext;    //删除节点的过程  
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