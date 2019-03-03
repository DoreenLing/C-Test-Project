#pragma once
#include<iostream>
#include<queue>
#define MAX 200 //定义最大顶点数
#define INF 26656
#define ZERO 0

template<class T>
struct Edge {
	T edge_start; //边的开始顶点
	T edge_end;//边的结束顶点
	int edge_weight;//权值
	Edge() {}
	Edge(T s, T e, int w) :edge_end(e),edge_start(s),edge_weight(w){}
};

template<class T>
class Graph_Matrix {
public:
	Graph_Matrix() {}
	~Graph_Matrix() {}

	void Get_CurMatrix(int Matrix[][MAX]);//获得当前邻接矩阵
	void Get_Matrix(int Matrix[][MAX]);//获得图的邻接矩阵（相当于创建图）
	void Get_Vex(T vex[]);//获得顶点数组
	bool IsFull();//图是否是满的
	bool IsEmpty();//图是否是空的
	int Get_mVertices();//得到图的顶点数
	int Get_mEdge();//得到图的边数
	int Set_mVertices(int mvexs);//设置图的顶点数
	int Set_mEdge(int medges);//设置图的边数
	T Get_Value(int position); //根据位置得到顶点的值
	int Get_Position(T value);//得到顶点value的位置
	bool Remove_Vertex(T value);//删除顶点和与之有关的边
	bool Remove_Edge(T s,T e);//删除边（s，e）
	Edge<T>* Get_AllEdge();//得到边
	void Sort_Edage(Edge<T> edge[], int elen);//对边排序
	int Get_FirstVex(T v);//顶点v的第一个邻接顶点
	int Get_NextVex(T v, T w);//获取顶点v的下一个点点w的下一个邻接顶点
	int Get_End(int visit[],int v);//返回当前图的终点
public:
	void DFS(T v);//深度优先搜索
	void BFS(T v);//广度优先搜索
	void Kruskal();//Kruskal算法
	void Prim(T v);//Prim算法
public:
	void Dijkstra(T v);//地杰斯特拉算法
	void floyd();//费罗伊德算法
	bool Bellman_Ford(T v);//Bellman-Ford算法
	bool SPFA(T v);//SPFA算法
private:
	bool Get_Edge();//得到边
	void DFS(T v, bool visit[]);//深度优先搜索
private:
	T mVexs[MAX];  //顶点数组
	int numVexs;//顶点数
	int numEdges;//边数
	int mMatrix[MAX][MAX];//邻接矩阵
	Edge<T> AllEdge[MAX];//所有边
	Edge<T> rets[MAX];//最小生成树结果矩阵
};

//function： 获得当前邻接矩阵
template<class T>
void Graph_Matrix<T>::Get_CurMatrix(int Matrix[][MAX])
{
	for (int i = 0; i < numVexs; i++) {
		for (int j = 0; j < numVexs; j++) {
		     Matrix[i][j] = mMatrix[i][j];
		}
	}
}

//function: 获得图的邻接矩阵（相当于创建图）
template<class T>
void Graph_Matrix<T>::Get_Matrix(int Matrix[][MAX])
{
	for (int i = 0; i < numVexs; i++) {
		for (int j = 0; j < numVexs; j++) {
			mMatrix[i][j] = Matrix[i][j];
		}
	}
}

//function: 获得顶点数组（相当于创建图）
template<class T>
void Graph_Matrix<T>::Get_Vex(T vex[])
{
	for (int i = 0; i < numVexs;i++)
		mVexs[i] = vex[i];
}

//function:判断图是否为满
template<class T>
bool Graph_Matrix<T>::IsFull()
{
	if (numVexs == MAX) {
		return true;
	}
	return false;
}

//function: 判断是否为空
template<class T>
bool Graph_Matrix<T>::IsEmpty()
{
	if (numVexs == 0) {
		return true;
	}
	return false;
}

//function: 得到图的顶点数
template<class T>
int Graph_Matrix<T>::Get_mVertices()
{
	return numVexs;
}

//function: 得到图的边数
template<class T>
int Graph_Matrix<T>::Get_mEdge()
{
	return numEdges;
}

//function: 设置图的顶点数
template<class T>
int Graph_Matrix<T>::Set_mVertices(int mvexs)
{
	numVexs = mvexs;
	return numVexs;
}

//function: 设置图的边数
template<class T>
int Graph_Matrix<T>::Set_mEdge(int medges)
{
	numEdges = medges;
	return numEdges;
}

//function: 根据位置得到顶点的值
template<class T>
T Graph_Matrix<T>::Get_Value(int position)
{
	return mVexs[position];
}

//function: 得到顶点value的位置
template<class T>
int Graph_Matrix<T>::Get_Position(T value)
{
	for (int i = 0; i < numVexs; i++) {
		if (mVexs[i] == value) {
			return i;
		}
	}
	return INF;
}

//function:删除顶点和与之有关的边
template<class T>
bool Graph_Matrix<T>::Remove_Vertex(T value)
{
	int pos = Get_Position(value);
	if (numVexs == 0 || pos == INF) {
		return false;
	}
	int k = 0;
	for (int i = 0; i < numVexs; i++) {
		if (mMatrix[pos][i] != ZERO&&mMatrix[pos][i] != INF)
			k++;
		if (mMatrix[i][pos] != ZERO&&mMatrix[i][pos] != INF)
			k++;
	}
	for (int j = 0; j < numVexs - pos; j++) {
		for (int i = 0; i < numVexs; i++) {
			mMatrix[pos + j][i] = mMatrix[pos + j+1][i];
			mMatrix[i][pos + j] = mMatrix[i][pos + j + 1];
		}
	}
	numVexs--;
	numEdges = numEdges - k;
	return true;
}

//function: 删除边（s,e）
template<class T>
bool Graph_Matrix<T>::Remove_Edge(T s, T e)
{
	int pos_s = Get_Position(s);
	int pos_e = Get_Position(e);
	if (pos_s == INF || pos_e == INF) {
		return false;
	}
	mMatrix[pos_s][pos_e] = INF;
	return true;
}

//function: 得到边
template<class T>
bool Graph_Matrix<T>::Get_Edge()
{
//	Edge<T> *edge = new Edge<T>[MAX];
	//AllEdge = new Edge<T>[MAX];
	int k = 0;
	if (numEdges == 0 || numVexs == 0) {
		return false;
	}
	for (int i = 0; i < numVexs; i++) {
		for (int j = 0; j < numVexs; j++){
			if (mMatrix[i][j] != ZERO&&mMatrix[i][j] != INF) {
				AllEdge[k].edge_start = Get_Value(i);
				AllEdge[k].edge_end = Get_Value(j);
				AllEdge[k].edge_weight = mMatrix[i][j];
				k++;
			}
		}
	}
	numEdges = k;
	return true;
}

//function: 得到边
template<class T>
Edge<T>* Graph_Matrix<T>::Get_AllEdge()
{
	if (Get_Edge() == true) {
		return AllEdge;
	}
	else exit(1);
}

//function： 对边排序，按照权值，从小到大
//para: edge 边的集合
//para：elen 边得多少
template<class T>
void Graph_Matrix<T>::Sort_Edage(Edge<T> edge[], int elen)
{
	for (int i = 0; i < elen - 1; i++) {
		for ( int j = 0; j < elen - i -1; j++){
			if (edge[j].edge_weight>edge[j+1].edge_weight) {
				int temp = edge[j+1].edge_weight;
				T temps = edge[j + 1].edge_start;
				T tempe = edge[j + 1].edge_end;

				edge[j+1].edge_weight = edge[j].edge_weight;
				edge[j + 1].edge_start = edge[j].edge_start;
				edge[j + 1].edge_end = edge[j].edge_end;

				edge[j].edge_weight = temp;
				edge[j].edge_start = temps;
				edge[j].edge_end = tempe;
			}
		}
	}
}

//function:顶点v的第一个邻接顶点
template<class T>
int Graph_Matrix<T>::Get_FirstVex(T v)
{
	int pos = Get_Position(v);
//	T firstvex;
	if (pos == INF) {
		exit(1);
	}
	for (int i = 0; i < numVexs; i++) {
		if (mMatrix[pos][i] != 0 && mMatrix[pos][i] != INF) {
			//firstvex = Get_Value(i);
			return i;
		}
	}
	return INF;
}

//function:顶点v的第一个邻接顶点w的下一个顶点
//para: v 当前顶点
//para: w 当前顶点的第一个顶点
template<class T>
int Graph_Matrix<T>::Get_NextVex(T v, T w)
{
	int posv = Get_Position(v);
	int posw = Get_Position(w);
	//T nextvex;
	if (posv == INF||posw == INF) {
		exit(1);
	}
	for (int i = posw +1; i < numVexs; i++) {
		if (mMatrix[posv][i] != 0 && mMatrix[posv][i] != INF) {
			//nexttvex = Get_Value(i);
			return i;
		}
	}
	return INF;
}

//function:深度优先搜索
//para：v 开始顶点
//para：visit 辅助遍历数组
template<class T>
void Graph_Matrix<T>::DFS(T v, bool visit[])
{
	int posv = Get_Position(v);
	if (posv != INF)
		visit[posv] = true; //标记已经访问的节点
	else
		return;
	int w = Get_FirstVex(v);
	while(w != INF) {
		if (visit[w] == false) {
			T tw = Get_Value(w);
			DFS(tw,visit);
		}
		T tw = Get_Value(w);
		w = Get_NextVex(v,tw);
	}
}

//function:深度优先搜索
template<class T>
void Graph_Matrix<T>::DFS(T v)
{
	bool visit[MAX];
	for (int i = 0; i < MAX; i++){
		visit[i] = false;
	}
	DFS(v, visit);
}

//function:广度优先搜索
template<class T>
void Graph_Matrix<T>::BFS(T v)
{
	bool visit[MAX];
	queue<int> a;
	for (int i = 0; i < MAX; i++) {
		visit[i] = false;
	}
	int posv = Get_Position(v);
	if (posv != INF){
		visit[posv] = true;
		a.push(posv);
		while (!a.empty()) {
			int cur = a.front();
			a.pop();
			T vexcur = Get_Value(cur);
			int w = Get_FirstVex(vexcur);
			while (w != INF) {
				if (visit[w] == false) {
					visit[w] = true;
					a.push(w);
				}
				T vexw = Get_Value(w);
				w = Get_NextVex(vexcur,vexw);
			}
		}
	}
}

//function:返回当前图的终点
template<class T>
int Graph_Matrix<T>::Get_End(int visit[], int v)
{
	while (visit[v] != 0)
		v = visit[v];
	return v;
}

//function:Kruskal算法
template<class T>
void Graph_Matrix<T>::Kruskal()
{
	bool a = Get_Edge();//得到所有的边
	Edge<T> temp[MAX];
	int j = 0;
	int visit[MAX] = { 0 };
	if (a == false)
		return;
	for (int i = 0; i < numEdges; i++) {
		temp[i].edge_start = AllEdge[i].edge_start;
		temp[i].edge_end = AllEdge[i].edge_end;
		temp[i].edge_weight = AllEdge[i].edge_weight;
	}
	Sort_Edage(AllEdge, numEdges);//排序
	for (int i = 0; i < numEdges; i++) {
		int s = Get_Position(AllEdge[i].edge_start);
		int e = Get_Position(AllEdge[i].edge_end);
		
		int u = Get_End(visit, s);
		int w = Get_End(visit, e);
		if (u != w) {
			visit[u] = w;
			rets[j].edge_start = AllEdge[i].edge_start;
			rets[j].edge_end = AllEdge[i].edge_end;
			rets[j].edge_weight = AllEdge[i].edge_weight;
			j++;
		}

	}
}

//function:Prim算法
//para: v 开始点
template<class T>
void Graph_Matrix<T>::Prim(T v)
{
	int visited[MAX];//标记已经访问的节点
	int previous[MAX];//当前节点的前驱节点
	int distance[MAX];   //权值信息
	int x = Get_Position(v);
	for (int i = 0; i < numVexs; i ++) {
		visited[i] = 0;
		previous[i] = x;
		distance[i] = mMatrix[x][i];
	}
	visited[x] = 1;
	for (int j = 0; j < numVexs - 1; j++) {
		int temp = INF;
		int tempvex;
		for (int i= 0; i < numVexs; i ++) {
			if (visited[i] == 0) {
				if (distance[i] < temp) {
					temp = distance[i];
					tempvex = i;
				}
			}
		}
		visited[tempvex] = 1;
		for (int i = 0; i < numVexs; i++) {
			if (visited[i] == 0) {
				if (distance[i] > mMatrix[tempvex][i]) {
					distance[i] = mMatrix[tempvex][i];
					previous[i] = tempvex;
				}
			}
		}
	}
}

//function:Dijkstra算法
//para: v 开始点
template<class T>
void Graph_Matrix<T>::Dijkstra(T v)
{
	int w = Get_Position(v);
	int *visited = new int[numVexs];
	int *path = new int[numVexs];
	int *distance = new int[numEdges];
	for (int i = 0; i < numVexs; i++) {
		visited[i] = 0;
		path[i] = w;
		distance[i] = mMatrix[w][i];
	}
	visited[w] = 1;
	for (int j = 0; j < numVexs -1; j++ ) {
		int temp = INF;
		int tempvex;
		for (int i = 0; i < numVexs; i++){
			if (visited[i] == 0 && distance[i] < temp) {
				temp = distance[i];
				tempvex = i;
			}
		}
		visited[tempvex] = 1;
		for (int i = 0; i < numVexs; i ++) {
			if (visited[i] == 0&&distance[i]>temp+mMatrix[tempvex][i]) {
				distance[i] = temp + mMatrix[tempvex][i];
				path[i] = tempvex;
			}
		}
	}
	delete []visited;
	visited = nullptr;
	delete []path;
	path = nullptr;
	delete[]distance;
	distance = nullptr;
}

//function:费罗伊德算法
template<class T>
void Graph_Matrix<T>::floyd()
{
	int temp[numVexs][numVexs];
	int path[numVexs][numVexs];
	for (int i = 0; i < numVexs; i++) {
		for (int j = 0; j < numVexs; j ++) {
			temp[i][j] = mMatrix[i][j];
			path[i][j] = i;
		}
	}
	for (int k = 0; k < numVexs; v++) {
		for (int i = 0; i < numVexs; i ++) {
			for (int j = 0; j < numVexs; j++) {
				if (temp[i][j] > temp[i][k]+temp[k][j]) {
					temp[i][j] = temp[i][k] + temp[k][j];
					path[i][j] = path[k][j];
				}
			}
		}
	}
}

//function:Bellman_Ford
//para: v 开始点
//有负回路返回true，否者返回false
template<class T>
bool Graph_Matrix<T>::Bellman_Ford(T v)
{
	int *distance = int[numEdges];
	int tempvex = Get_Position(v);
	for (int i = 0; i < numVexs; i++) {
		distance[i] = mMatrix[tempvex][i];
	}
	for (int i = 0; i < numVexs - 1; i++) {
		for (int j = 0; j < numVexs; j++) {
			for (int k = 0; k < numVexs; k++) {
				if (mMatrix[j][k] != 0 && mMatrix[j][k] != IFN) {
					if (distance[k] > distance[j] + mMatrix[j][k]) {
						distance[k] = distance[j] + mMatrix[j][k];
					}
				}
			}
		}
	}
	for (int j = 0; j < numVexs; j++) {
		for (int k = 0; k < numVexs; k++) {
			if (mMatrix[j][k] != 0 && mMatrix[j][k] != IFN) {
				if (distance[k] > distance[j] + mMatrix[j][k]) {
					return true;
				}
			}
		}	
	}
	delete[]distance;
	distance = nullptr;
	return false;
}

//function:SPFA算法
//para: v 开始点
template<class T>
bool Graph_Matrix<T>::SPFA(T v)
{
	int *distance = new int[numEdges];
	int *visited = new int[numVexs];
	queue<int> q;
	int *cnt = new int[numVexs];
	int tempvex = Get_Position(v);
	if (tempvex == INF){
		return;
	}
	for (int i = 0; i < numVexs; i ++) {
		visited[i] = 0;
		cnt[i] = 0;
		if (i < numEdges) {
			distance[i] = INF;
		}
	}
	q.push(tempvex);
	distance[tempvex] = 0;
	while (!q.empty()) {
		tempvex = q.front();
		q.pop();
		visited[tempvex] = 0;
		for (int i = 0; i < numVexs; i++) {
			if (distance[tempvex] + mMatrix[tempvex][i] < distance[i]) {
				distance[i] = distance[tempvex] + mMatrix[tempvex][i];
				if (visited[i] == 0) {
					visited[i] = 1;
					q.push(i);
					cnt[i]++;
					if (cnt[i] > numVexs) {
						return false;
					}
				}
			}
		}
	}
	delete[]visited;
	visited = nullptr;
	delete[]distance;
	distance = nullptr;
	return true;
}

