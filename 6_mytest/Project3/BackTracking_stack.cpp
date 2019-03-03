/*回溯法求迷宫问题,,非递归*/
#include<iostream>
#include<stack>
using namespace std;
struct offset {
	int a, b;
	char *dir;
};

class complax {
public:
	stack<offset> setpath(int x, int y);
	friend ostream& operator<<(ostream &out, offset &temp);
};

ostream& operator<<(ostream&out, offset &temp)
{
		return out << temp.a << "," << temp.b << "," << temp.dir << "--";
}

offset Move2[8] = { { 1,0,"S" },{ 1,1,"SE" },{ 0,1,"E" },{ -1,1,"NE" },
					{ -1,0,"N" },{ -1,-1,"NW" },{ 0,-1,"W" },{ 1,-1,"SW" }				   
 };
const int r = 3, l = 3;//迷宫的行列
int Mark2[r + 2][l + 2];
int Maze2[r + 2][l + 2] = { { 1,1,1,1,1 },
						    { 0,0,1,0,1 },
						    { 1,1,0,0,1 },
						    { 1,0,1,0,0 },
						    { 1,1,1,1,1 }
						};


stack<offset> complax::setpath(int x, int y)
{
	int g, h, i, j, p = 0; char *d;
	Mark2[1][1]=1;
	stack<offset>st; offset temp;
	temp.a = 1; temp.b = 1; temp.dir = "E";
	st.push(temp);
	while (!st.empty()) {
		st.pop();
		i = temp.a; j = temp.b; d = temp.dir;
		while (p < 8) {
			g = temp.a + Move2[p].a;
			h = temp.b + Move2[p].b;	
			if (g == r&&h == l) {  return st; }
			if (Maze2[g][h] == 0 && Mark2[g][h] == 0) {
				Mark2[g][h] = 1;
				temp.a = i; temp.b =j; temp.dir =d;
				st.push(temp);
				i = g; j = h;d = Move2[p].dir;
				p = 0;
			}
			else p++;
		}
	}
	cout << "on path in maze!!!" << endl;
	return st;
}
void mainsx()
{
	complax A; stack<offset>st;
	st=A.setpath(1,1);
	while (!st.empty()) {
		cout << st.top();
		st.pop();
	}
	system("pause");
}