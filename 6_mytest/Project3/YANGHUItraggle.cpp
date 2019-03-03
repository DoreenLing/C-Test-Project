/*Ñî»ÔÈý½Ç*/
#include<iostream>
#include<queue>
using namespace std;
void mainyh()
{
	queue<int>q;
	int i = 1, s =0, t = 0, j, u;
	q.push(i); q.push(i);
	for (i = 1; i < 6; i++) {
		cout << endl;
		q.push(0);
		for (j = 1; j <= i + 2; j++) {
			s = q.front();
			u = s + t;
			t = s;
			q.push(u);
			q.pop();
			if (j != i + 2)cout << s <<" " ;
		}
	}
	system("pause");
}