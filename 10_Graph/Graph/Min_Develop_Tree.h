#pragma once
#include"Opera_Graph.h"

template<class T>
class Min_Develop_Tree:public Graph_Matrix<T> {
public:
	Min_Develop_Tree() {}
	~Min_Develop_Tree() {}
	void Get_MyMatrix(); //��ȡ��ǰ�ڽӾ���
	T Get_FirstVex(T v);//����v�ĵ�һ���ڽӶ���
	T Get_NextVex(T v,T w);//��ȡ����v����һ�����w����һ���ڽӶ���
	void DFS(T v, bool visit[]);//�����������
	void BFS(T v);//�����������
private:
	int mMatrix[MAX][MAX];//�ڽӾ���
	EData rets[MAX];//��С�������������
};

//function����ȡ��ǰ�ڽӾ���
template<class T>
void Min_Develop_Tree<T>::Get_MyMatrix()
{
	Get_CurMatrix(mMatrix);
}
//function : ��ȡ����v�ĵ�һ���ڽӶ���
//para��v ��ǰ�����Ķ���
template<class T>
T Min_Develop_Tree<T>::Get_FirstVex(T v)
{

}
