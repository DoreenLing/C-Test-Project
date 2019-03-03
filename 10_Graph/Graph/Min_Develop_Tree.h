#pragma once
#include"Opera_Graph.h"

template<class T>
class Min_Develop_Tree:public Graph_Matrix<T> {
public:
	Min_Develop_Tree() {}
	~Min_Develop_Tree() {}
	void Get_MyMatrix(); //获取当前邻接矩阵
	T Get_FirstVex(T v);//顶点v的第一个邻接顶点
	T Get_NextVex(T v,T w);//获取顶点v的下一个点点w的下一个邻接顶点
	void DFS(T v, bool visit[]);//深度优先搜索
	void BFS(T v);//广度优先搜索
private:
	int mMatrix[MAX][MAX];//邻接矩阵
	EData rets[MAX];//最小生成树结果矩阵
};

//function：获取当前邻接矩阵
template<class T>
void Min_Develop_Tree<T>::Get_MyMatrix()
{
	Get_CurMatrix(mMatrix);
}
//function : 获取顶点v的第一个邻接顶点
//para：v 当前操作的顶点
template<class T>
T Min_Develop_Tree<T>::Get_FirstVex(T v)
{

}
