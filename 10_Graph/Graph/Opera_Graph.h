#pragma once
#include<iostream>
#include<queue>
#define MAX 200 //������󶥵���
#define INF 26656
#define ZERO 0

template<class T>
struct Edge {
	T edge_start; //�ߵĿ�ʼ����
	T edge_end;//�ߵĽ�������
	int edge_weight;//Ȩֵ
	Edge() {}
	Edge(T s, T e, int w) :edge_end(e),edge_start(s),edge_weight(w){}
};

template<class T>
class Graph_Matrix {
public:
	Graph_Matrix() {}
	~Graph_Matrix() {}

	void Get_CurMatrix(int Matrix[][MAX]);//��õ�ǰ�ڽӾ���
	void Get_Matrix(int Matrix[][MAX]);//���ͼ���ڽӾ����൱�ڴ���ͼ��
	void Get_Vex(T vex[]);//��ö�������
	bool IsFull();//ͼ�Ƿ�������
	bool IsEmpty();//ͼ�Ƿ��ǿյ�
	int Get_mVertices();//�õ�ͼ�Ķ�����
	int Get_mEdge();//�õ�ͼ�ı���
	int Set_mVertices(int mvexs);//����ͼ�Ķ�����
	int Set_mEdge(int medges);//����ͼ�ı���
	T Get_Value(int position); //����λ�õõ������ֵ
	int Get_Position(T value);//�õ�����value��λ��
	bool Remove_Vertex(T value);//ɾ���������֮�йصı�
	bool Remove_Edge(T s,T e);//ɾ���ߣ�s��e��
	Edge<T>* Get_AllEdge();//�õ���
	void Sort_Edage(Edge<T> edge[], int elen);//�Ա�����
	int Get_FirstVex(T v);//����v�ĵ�һ���ڽӶ���
	int Get_NextVex(T v, T w);//��ȡ����v����һ�����w����һ���ڽӶ���
	int Get_End(int visit[],int v);//���ص�ǰͼ���յ�
public:
	void DFS(T v);//�����������
	void BFS(T v);//�����������
	void Kruskal();//Kruskal�㷨
	void Prim(T v);//Prim�㷨
public:
	void Dijkstra(T v);//�ؽ�˹�����㷨
	void floyd();//���������㷨
	bool Bellman_Ford(T v);//Bellman-Ford�㷨
	bool SPFA(T v);//SPFA�㷨
private:
	bool Get_Edge();//�õ���
	void DFS(T v, bool visit[]);//�����������
private:
	T mVexs[MAX];  //��������
	int numVexs;//������
	int numEdges;//����
	int mMatrix[MAX][MAX];//�ڽӾ���
	Edge<T> AllEdge[MAX];//���б�
	Edge<T> rets[MAX];//��С�������������
};

//function�� ��õ�ǰ�ڽӾ���
template<class T>
void Graph_Matrix<T>::Get_CurMatrix(int Matrix[][MAX])
{
	for (int i = 0; i < numVexs; i++) {
		for (int j = 0; j < numVexs; j++) {
		     Matrix[i][j] = mMatrix[i][j];
		}
	}
}

//function: ���ͼ���ڽӾ����൱�ڴ���ͼ��
template<class T>
void Graph_Matrix<T>::Get_Matrix(int Matrix[][MAX])
{
	for (int i = 0; i < numVexs; i++) {
		for (int j = 0; j < numVexs; j++) {
			mMatrix[i][j] = Matrix[i][j];
		}
	}
}

//function: ��ö������飨�൱�ڴ���ͼ��
template<class T>
void Graph_Matrix<T>::Get_Vex(T vex[])
{
	for (int i = 0; i < numVexs;i++)
		mVexs[i] = vex[i];
}

//function:�ж�ͼ�Ƿ�Ϊ��
template<class T>
bool Graph_Matrix<T>::IsFull()
{
	if (numVexs == MAX) {
		return true;
	}
	return false;
}

//function: �ж��Ƿ�Ϊ��
template<class T>
bool Graph_Matrix<T>::IsEmpty()
{
	if (numVexs == 0) {
		return true;
	}
	return false;
}

//function: �õ�ͼ�Ķ�����
template<class T>
int Graph_Matrix<T>::Get_mVertices()
{
	return numVexs;
}

//function: �õ�ͼ�ı���
template<class T>
int Graph_Matrix<T>::Get_mEdge()
{
	return numEdges;
}

//function: ����ͼ�Ķ�����
template<class T>
int Graph_Matrix<T>::Set_mVertices(int mvexs)
{
	numVexs = mvexs;
	return numVexs;
}

//function: ����ͼ�ı���
template<class T>
int Graph_Matrix<T>::Set_mEdge(int medges)
{
	numEdges = medges;
	return numEdges;
}

//function: ����λ�õõ������ֵ
template<class T>
T Graph_Matrix<T>::Get_Value(int position)
{
	return mVexs[position];
}

//function: �õ�����value��λ��
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

//function:ɾ���������֮�йصı�
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

//function: ɾ���ߣ�s,e��
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

//function: �õ���
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

//function: �õ���
template<class T>
Edge<T>* Graph_Matrix<T>::Get_AllEdge()
{
	if (Get_Edge() == true) {
		return AllEdge;
	}
	else exit(1);
}

//function�� �Ա����򣬰���Ȩֵ����С����
//para: edge �ߵļ���
//para��elen �ߵö���
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

//function:����v�ĵ�һ���ڽӶ���
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

//function:����v�ĵ�һ���ڽӶ���w����һ������
//para: v ��ǰ����
//para: w ��ǰ����ĵ�һ������
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

//function:�����������
//para��v ��ʼ����
//para��visit ������������
template<class T>
void Graph_Matrix<T>::DFS(T v, bool visit[])
{
	int posv = Get_Position(v);
	if (posv != INF)
		visit[posv] = true; //����Ѿ����ʵĽڵ�
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

//function:�����������
template<class T>
void Graph_Matrix<T>::DFS(T v)
{
	bool visit[MAX];
	for (int i = 0; i < MAX; i++){
		visit[i] = false;
	}
	DFS(v, visit);
}

//function:�����������
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

//function:���ص�ǰͼ���յ�
template<class T>
int Graph_Matrix<T>::Get_End(int visit[], int v)
{
	while (visit[v] != 0)
		v = visit[v];
	return v;
}

//function:Kruskal�㷨
template<class T>
void Graph_Matrix<T>::Kruskal()
{
	bool a = Get_Edge();//�õ����еı�
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
	Sort_Edage(AllEdge, numEdges);//����
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

//function:Prim�㷨
//para: v ��ʼ��
template<class T>
void Graph_Matrix<T>::Prim(T v)
{
	int visited[MAX];//����Ѿ����ʵĽڵ�
	int previous[MAX];//��ǰ�ڵ��ǰ���ڵ�
	int distance[MAX];   //Ȩֵ��Ϣ
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

//function:Dijkstra�㷨
//para: v ��ʼ��
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

//function:���������㷨
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
//para: v ��ʼ��
//�и���·����true�����߷���false
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

//function:SPFA�㷨
//para: v ��ʼ��
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

