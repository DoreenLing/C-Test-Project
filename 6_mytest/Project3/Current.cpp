/*队列的应用，电路布线 */
/*问题描述：把布线的区域换成一个网络，该网络用一个二维数组来存储，其中*/
/*通路用0表示，墙壁用1表示，从该区域内的某一个点向另一个点布线，求布线的最短路径与路径长度*/
/*解决办法：把起点值设置为2，然后把它四周走的通电设置为3，以此类推，直到走布线去或者到达赋值*/
/*终点，然后从终点按照数值依次减小路线往回走即可找到最短路径。*/
/*实现此操作使用队列，先入先出*/
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct MySnake {
	int col,row;//坐标的行列值
};
MySnake Move[4] = {{ 0,-1 },{ 1,0 },{0,1},{-1,0} };//建立方向数组
	
/*grid表示电路网格，m,n分别表示行列长度,start,stop分别表示开始点和结束点*/
vector<MySnake> FindPath(int grid[10][10],MySnake &start,MySnake &stop)
{
	vector<MySnake>Path;
	//标定路线
	MySnake here, nbr; queue<MySnake>Q;
	here.row = start.row; here.col = start.col;
	grid[here.row][here.col] = 2;//标定开始的值为2，与0,1区分开来
	
	do {
		for (int i = 0; i< 4; i++) {
			nbr.row = here.row + Move[i].row;
			nbr.col = here.col + Move[i].col;
			if (grid[nbr.row][nbr.col] == 0) {
				grid[nbr.row][nbr.col] = grid[here.row][here.col] + 1;
				if (nbr.row == stop.row&&nbr.col == stop.col)//退出内循环
					break;
				Q.push(nbr);//相邻位置进队
			}
		}
		if (nbr.row == stop.row&&nbr.col == stop.col)//退出外循环
				break;
		if (Q.empty()) {
				cout << "It's false to find path!!!" << endl;
				return Path;
			}

		here = Q.front();//出队，将其赋给当前位置
		Q.pop();

	} while (1);

	//从终点回溯，寻找最短路径
	here.row = stop.row;//终点的坐标赋值给当前坐标
	here.col = stop.col;
	cout << "从终点回溯，寻找最短路径" << endl;
	while (here.row != start.row&&here.col != start.col) {
		Path.push_back(here);//将当前坐标存入路线
		for (int i = 0; i < 4; i++) {
			nbr.row = here.row + Move[i].row;
			nbr.col = here.col + Move[i].col;
			if (grid[nbr.row][nbr.col] == grid[here.row][here.col] - 1)
				break;
		}
		here.row = nbr.row;
		here.col = nbr.col;
	}
	for (int x = 0; x < 10; x++) {
		for (int j = 0; j < 10; j++)
			cout << grid[x][j];
		cout << endl;
	}
	return Path;
}
void mainhj()
{
	//创建空白电路板
	int grid[10][10] = {
					   {1,1,1,1,1,1,1,1,1,1},
					   {1,0,0,0,0,0,0,0,0,1}, 
			   		   {1,0,0,0,0,0,0,0,0,1},
					   {1,0,0,0,0,0,1,1,0,1},
					   {1,0,1,0,0,0,0,0,1,1},
					   {1,0,0,0,1,1,1,1,0,1},
					   {1,0,1,0,0,0,1,1,0,1},
					   {1,1,0,0,1,0,0,0,0,1},
					   {1,0,0,0,1,0,0,0,0,1},
					   {1,1,1,1,1,1,1,1,1,1}
	};
	vector<MySnake> Path; MySnake display_path;//声明路线
	MySnake start = { 2,2 }, stop = {7,7};
	Path = FindPath(grid,start,stop);
	cout << Path.size() << endl;
	//输出路径
	cout << "Display the path:" << endl;
	while(!Path.empty()) {
		display_path = Path.back();
		cout << "(" << display_path.row << "," << display_path.col << ")" << "-->";
		Path.pop_back();
	}
	system("pause");
}