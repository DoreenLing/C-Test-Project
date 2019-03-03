/*���е�Ӧ�ã���·���� */
/*�����������Ѳ��ߵ����򻻳�һ�����磬��������һ����ά�������洢������*/
/*ͨ·��0��ʾ��ǽ����1��ʾ���Ӹ������ڵ�ĳһ��������һ���㲼�ߣ����ߵ����·����·������*/
/*����취�������ֵ����Ϊ2��Ȼ����������ߵ�ͨ������Ϊ3���Դ����ƣ�ֱ���߲���ȥ���ߵ��︳ֵ*/
/*�յ㣬Ȼ����յ㰴����ֵ���μ�С·�������߼����ҵ����·����*/
/*ʵ�ִ˲���ʹ�ö��У������ȳ�*/
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct MySnake {
	int col,row;//���������ֵ
};
MySnake Move[4] = {{ 0,-1 },{ 1,0 },{0,1},{-1,0} };//������������
	
/*grid��ʾ��·����m,n�ֱ��ʾ���г���,start,stop�ֱ��ʾ��ʼ��ͽ�����*/
vector<MySnake> FindPath(int grid[10][10],MySnake &start,MySnake &stop)
{
	vector<MySnake>Path;
	//�궨·��
	MySnake here, nbr; queue<MySnake>Q;
	here.row = start.row; here.col = start.col;
	grid[here.row][here.col] = 2;//�궨��ʼ��ֵΪ2����0,1���ֿ���
	
	do {
		for (int i = 0; i< 4; i++) {
			nbr.row = here.row + Move[i].row;
			nbr.col = here.col + Move[i].col;
			if (grid[nbr.row][nbr.col] == 0) {
				grid[nbr.row][nbr.col] = grid[here.row][here.col] + 1;
				if (nbr.row == stop.row&&nbr.col == stop.col)//�˳���ѭ��
					break;
				Q.push(nbr);//����λ�ý���
			}
		}
		if (nbr.row == stop.row&&nbr.col == stop.col)//�˳���ѭ��
				break;
		if (Q.empty()) {
				cout << "It's false to find path!!!" << endl;
				return Path;
			}

		here = Q.front();//���ӣ����丳����ǰλ��
		Q.pop();

	} while (1);

	//���յ���ݣ�Ѱ�����·��
	here.row = stop.row;//�յ�����긳ֵ����ǰ����
	here.col = stop.col;
	cout << "���յ���ݣ�Ѱ�����·��" << endl;
	while (here.row != start.row&&here.col != start.col) {
		Path.push_back(here);//����ǰ�������·��
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
	//�����հ׵�·��
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
	vector<MySnake> Path; MySnake display_path;//����·��
	MySnake start = { 2,2 }, stop = {7,7};
	Path = FindPath(grid,start,stop);
	cout << Path.size() << endl;
	//���·��
	cout << "Display the path:" << endl;
	while(!Path.empty()) {
		display_path = Path.back();
		cout << "(" << display_path.row << "," << display_path.col << ")" << "-->";
		Path.pop_back();
	}
	system("pause");
}