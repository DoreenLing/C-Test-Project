/*���ݷ����Թ�����,,�ݹ�*/
#include<iostream>
using namespace std;


struct offset {
	int a, b; //ƫ����
	char *dir;//����
};
offset Move[8] = { {-1,0,"N"},{-1,1,"NE"},{ 0,1,"E" },{ 1,1,"SE" },
					{1,0,"S" },{ 1,-1,"SW" },{ 0,-1,"W" },{ -1,-1,"NW" } };
const int r = 3, l = 3;//�Թ�������
int Mark[r+2][l+2];
int Maze[r + 2][l + 2] = { { 1,1,1,1,1 },
						   { 0,0,1,0,1 },
						   { 1,1,0,0,1 },
						   { 1,0,1,0,0 },
						   { 1,1,1,1,1 } 
						};

int Setpath(int x, int y)
{
	int g, h; char *d;
	if (x == r&&y == l) return 1;
	for (int i = 0; i < 8; i++) {
		g = x + Move[i].a;
		h = y + Move[i].b;
		d = Move[i].dir;

		if (Maze[g][h] == 0 && Mark[g][h] == 0) {
			Mark[g][h] = 1;          //���߹���·���Ϊ1
			if (Setpath(g, h)) {      //�ݹ���̽
				cout << "(" << g << "," << h << ")," << "direction:" << d << "--";//�������
				return 1;
			}
		}
	}
	if (x == 1 && y == 1)cout << "No path in Maze!!!" << endl;
	return 0;
}
void maindg()
{
	for (int i = 0; i < r + 2; i++)
		for (int j = 0; j < l + 2; j++) Mark[i][j]=0;
	Mark[1][1] = 1;
	if (Setpath(1, 1))
		cout << "E" << endl;
	system("pause");
}