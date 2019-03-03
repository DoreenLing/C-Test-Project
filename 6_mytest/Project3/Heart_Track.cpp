#include<iostream>
#include <cstdio> 
#include<math.h>
#include <time.h> 
#include<stack>
#include<windows.h>
#include"Heart_Track.h"
using namespace std;

/*初始化父节点*/
void Disjoin_set::initSet()
{
	memset(Rank, 0, sizeof(Rank));
	for (int i = 0; i < MAXSIZE; ++i)
		Parent[i] = i;
}

int Disjoin_set::FindSet(int x)
{
	if (x != Parent[x])
		Parent[x] = FindSet(Parent[x]);
	return Parent[x];
}

void Disjoin_set::UnionSet(int root1, int root2)
{
	int x = FindSet(root1);
	int y = FindSet(root2);
	if (x == y)return;
	if (Rank[x] > Rank[y])
		Parent[y] = x;//x设为y的父节点
	else {  
		Parent[x] = y;
		if (Rank[x] == Rank[y])
			++Rank[y];
	}
}

int Disjoin_set::Postolist(int x, int y)
{
	return x*M + y;
}

void Heart_Track::best_Simple()
{
	/*for (float y = 1.5; y > -1.5; y -= 0.11) {
		for (float x = -1.2; x < 1.1; x += 0.07) {
			float a = x*x + y*y - 1;
			float b = a*a*a - x*x*y*y*y;
			if (b <= 0.0)
				cout << "█";
			else cout << " ";
		}
		cout << endl;
	}*/
	int i = 0, j = 0; int m=0, n=0;
	for (float y = 1.2f; y > -1.0f; y -= 0.09f)
	{
		for (float x = -1.1f; x < 1.2f; x += 0.09f)
		{
			float a = x * x + y * y - 1;
			if (a * a * a - x * x * y * y * y <= 0.0f)
			{
				cout << "█"; m++;
			}
			else
				cout<<"  ";
			j++;
		}
		i++; n++; cout << m; m = 0;
		j = 0; cout << endl;
	}cout << n;
}

void Heart_Track::Simple()
{
	for (float y = 1.5; y > -1.5; y -= 0.1) {
		for (float x = -1.5; x < 1.5; x += 0.05) {
			float a = x*x + y*y - 1;
			float b = a*a*a - x*x*y*y*y;
			if (b <= 0.0)
				cout << "--*``^.^"[(int)(b*-6.0)];
			else cout << " ";
		}
		cout << endl;
	}
}

bool Heart_Track::inMaze(int x, int y)
{
	return (x >= 0 && x < M&&y >= 0 && y < N);
		
}

void Heart_Track::ClearMask(int x, int y)
{
	for (int i = x - 1; i <= x + 1; i++)
		for (int j = y - 1; j <= y + 1; j++)
			if (inMaze(i, j))
				Mask[i][j] = false;
}

/*初始化心型*/
void Heart_Track::initHeart()
{
	int i = 0, j = 0; int m = 0, n = 0;
	for (float y = 1.2f; y > -1.0f; y -= 0.09f) {
		for (float x = -1.1f; x < 1.2f; x += 0.09f) {
			float a = x*x + y*y - 1;
			float b = a*a*a - x*x*y*y*y;
			if (b <= 0.0f) {
				Area[i][j] = true;
				//cout << "█";//m++;
			}
			else {
				Area[i][j] = false;
			//	cout << "  ";
			}
			j++;	
		}	
		//cout << m; //m = 0;
		//cout << endl;
		i++; j = 0;// n++;
	}
	//cout << n;
}

/*初始化迷宫*/
void Heart_Track::initMaze(int maze[M][N])
{
	//initHeart();
	srand((unsigned)time(NULL));//产生随机数种子

	//随机打通迷宫的某些墙
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++) {
			if (Area[i][j] && !(Area[i][j - 1] && Area[i - 1][j] && Area[i][j + 1] && Area[i + 1][j]))
				maze[i][j] = OUTWALL;
			else if (Area[i][j] && i % 2 == 0 && j % 2 == 0)
				maze[i][j] = ROAD;
			else if (Area[i][j])
				maze[i][j] = INWALL;
			else
				maze[i][j] = EMPTYWALL; 
			if (Area[i][j])
			{
				maze[0][j] = OUTWALL; maze[i][0] = OUTWALL; maze[i][24] = OUTWALL;
			}
			Visit[i][j] = false;//还未访问
			Mask[i][j]= true;//
		}
	//将迷宫的入口和出口设为通路
	maze[start.row][start.col] = maze[end.row][end.col] = ROLL;
	updateMaze(maze);//更新窗口
	Disjoin_set p;
	p.initSet();
	Visit[start.row][start.col] = true;
	int x, y, d, xt1, xt2, yt1, yt2; 
	while (p.FindSet(p.Postolist(start.row, start.col)) != p.FindSet(p.Postolist(end.row, end.col))) {
		do {
			x = rand() % (M - 1) + 1;
			y = rand() % (N - 1) + 1;
			
		} while (maze[x][y]==OUTWALL);
		d = x % 2;
		
		if (d == 0)
		{
			xt1 = x + 1;
			yt1 = y;
			xt2 = x - 1;
			yt2 = y;
			//随机生成的点在xin型区域内且两个子集不相交
			if (p.FindSet(p.Postolist(xt1, yt1)) != p.FindSet(p.Postolist(xt2, yt2)))
			{
				maze[x][y] = ROAD; 
				p.UnionSet(p.Postolist(xt1, yt1), p.Postolist(xt2, yt2));
			}
			
		}
		else if (d == 1)
		{
			xt1 = x;
			yt1 = y + 1;
			xt2 = x;
			yt2 = y - 1;
			if ( p.FindSet(p.Postolist(xt1, yt1)) != p.FindSet(p.Postolist(xt2, yt2)))
			{
				maze[x][y] = ROAD;
				p.UnionSet(p.Postolist(xt1, yt1), p.Postolist(xt2, yt2));
			}
			
		}
	
	}

//	showBack(maze);
}

/*寻找路径*/
void Heart_Track::findPath(int maze[M][N])
{
	stack<offsettings>st; offsettings temp;

	//开始点入栈
	temp.row = start.row; temp.col = start.col; temp.dir = EAST;
	maze[temp.row][temp.col] = ROLL;
	maze[end.row][end.col] = ROLL;
	updateMaze(maze);//更新窗口
	st.push(temp);
	//寻路
	int x, y, g, h, dir, p = 0, flag = 0;
	while (!st.empty()) {
		p = 0;
		temp = st.top();st.pop();//出栈	
		x = temp.row; y = temp.col; dir= temp.dir;

		//showBack(maze);
	//	system("pause");
		while (p < 4) {
			g = x + Move[p][0];
			h = y + Move[p][1];

			if (g == end.row&&h == end.col) { 
				cout << end.row<<"," << end.col<<endl;
				cout << "Show the path in maze!!!" << endl;
				return;
			}

			//合法的移动且此位置并未被访问过 
			if ( maze[g][h] == ROAD && Visit[g][h]==false&& maze[g][h] != OUTWALL) {
				Visit[g][h] = true;//标记为已访问
				maze[g][h] = dir;

				temp.row = x; temp.col = y; temp.dir = dir;
				st.push(temp);
				x = g; y = h; 
				p = 0; dir = 7;
				updateMaze(maze);//更新窗口

			}
			else {p++; dir++;}
			if (p >= 4) { flag = 1;
			maze[x][y] = BACK;
			updateMaze(maze);//更新窗口
			}
		}
		if (flag == 1 && maze[x][y] != ROLL) {
			maze[x][y] = BACK;
		//	updateMaze( maze);//更新窗口
		}
	}

	cout<< "on path in maze!!!" << endl;
	//showBack(maze);
	return ;
}

/*显示函数*/
void Heart_Track::showBack(int maze[M][N])
{
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (Area[i][j] == false)
				cout << "  ";
			else if (maze[i][j] == INWALL)
				cout << "█";
			else if (maze[i][j] == OUTWALL)
				cout << "●";
			else if (maze[i][j] == EMPTYWALL)
				cout << "  ";
			else if (maze[i][j] == ROAD)
				cout << "  ";
			else if (maze[i][j] == BACK)
				cout << "○";
			else if (maze[i][j] == WEST)
				cout << "←";
			else if (maze[i][j] == NORTH)
				cout << "↑";
			else if (maze[i][j] == EAST)
				cout << "→";
			else if (maze[i][j] == SOUTH)
				cout << "↓";
			else if(maze[i][j] == ROLL)
				cout << "★";
			else cout << "  ";
			if (j != 0 && j % (N - 1) == 0)
				cout << "\n";
		} 
		//cout << "\n";
	}
	cout << "测试" << endl;
}

void Heart_Track::gotoxy(int x,int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void Heart_Track::hideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void Heart_Track::updateMaze(int maze[M][N])
{
	hideCursor();
	gotoxy(0, 0);
	showBack(maze);
	Sleep(1);
}

void maincv()
{
	Heart_Track p;
	int maze[M][N];
//	p.best_Simple();
//	p.Simple();
	p.initHeart();
	p.initMaze(maze);
	p.findPath(maze); 
	p.showBack(maze);
	system("pause");
}