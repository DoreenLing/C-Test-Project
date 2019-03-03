#include"Binary_Heap.h"
#include"Opera_Graph.h"
//#include"Min_Develop_Tree.h"
#include<iostream>
#include<math.h>
#include<string>
#include< stdlib.h > 
#include<stack>
#include<map>

using namespace std;

int Max[MAX][MAX] = { {0,1,2,INF},
				  {1,0,INF,3},
				  {2,INF,0,INF},
				  {INF,3,INF,0} 
};
char VEX[4] = {'A','B','C','D'};
//int main()
//{
//	int a = 2; 
//	int b = 3;
//	Binary_Heap<int> c;
//	cout << c.IsEmpty_Max()<< endl;
//
//	Graph_Matrix<char> m;
//
//	int vex = 4;
//	m.Set_mVertices(vex);//设置图的顶点数
//	int edge = 3;
//	m.Set_mEdge(edge);//设置图的边数
//	m.Get_Matrix(Max);
//	m.Get_Vex(VEX);
//	m.BFS('A');
//	m.Kruskal();
//	m.Prim('A');
//	m.Dijkstra('A');
//
//	system("pause");
//}

//int B(int num) 
//{
//	string num_string =to_string(num);
//	int size = num_string.size();
//	int sum = 0;
//	if (size <= 1) {
//		return num;
//	}
//	else {
//		
//		for (int i = size - 1; i > 0; i--) {
//			int a = pow(10,i);
//			int num1 = num - num%a;	
//			sum = sum + num1/a;
//			num = num - num1;
//		}
//		sum += num;
//		if (sum < 10) {
//			return sum;
//		}
//		B(sum);
//	}
//	return sum;
//}
//
//string addStrings(string num1, string num2) {
//	int num1_size = num1.size() - 1;
	//int num2_size = num2.size() - 1;
//	int size_max = max(num1.size(), num2.size());
//	int size_result = size_max;
//	int value1 = 0;
//	int value2 = 0;
//	int sum = 0;
//	int ret = 0;
//	string num3(size_max+1,'0');
//	while (num1_size >= 0||num2_size >= 0) {
//		num1_size < 0 ? value1 = 0 : value1 = num1[num1_size] - 48;
//		num2_size < 0 ? value2 = 0 : value2 = num2[num2_size] - 48;
//		sum = value1 + value2 + ret;
//		ret = sum / 10;
//		num3[size_result] = sum%10 + 48;
//		if (num1_size >= 0) --num1_size;
//		if (num2_size >= 0) --num2_size;
//		size_result--;
//	}
//	if (ret != 0) {
//		num3[size_result] = ret + 48;
//		return num3;
//	}
//	else {
//		return num3.substr(1, size_result-1);
//	}
//	
//}
//
//
//int cmp(const  void  *a, const  void *b)
//{
//	return *(int *)a - *(int *)b;
//}
//int arrayPairSum(vector<int>& nums) {
//	sort(nums.begin(), nums.end());
//	//首先从小到大排序
//	int size = nums.size();
//	int sum = 0;
//	/*for (int i = 0; i < size; i++) {
//		for (int j = i + 1; j < size; j++) {
//			if (nums[j] < nums[i]) {
//				swap(nums[i], nums[j]);
//			}
//		}
//	}
//	int sum = 0;
//	if (nums.size() <= 2) {
//		return nums[0];
//	}*/
//	for (int i = size - 2; i >= 0; i = i - 2) {
//		sum = sum + nums[i];
//	}
//	return sum;
//}
//bool backspaceCompare(string S, string T) {
//	for (int i = 1; i < S.size(); i++) {
//		if (S[i] == '#') {
//			S[i] = '*';
//			S[i - 1] = '*';
//			int j = i;
//			while (j - 2 >= 0) {
//				S[j] = S[j - 2];
//				S[j - 2] = '*';
//				j--;
//			}
//		}
//	}
//
//
//	for (int i = 1; i <T.size(); i++) {
//		if (T[i] == '#') {
//			T[i] = '*';
//			T[i - 1] = '*';
//			int j = i;
//			while (j - 2 >= 0) {
//				T[j] = T[j - 2];
//				T[j - 2] = '*';
//				j--;
//			}
//		}
//	}
//	string ret_s;
//	for (int i = 0; i < S.size(); i++) {
//		if (S[i] != '*'&&S[i] != '#') {
//			ret_s.push_back(S[i]);
//		}
//	}
//	string ret_t;
//	for (int i = 0; i < T.size(); i++) {
//		if (T[i] != '*'&&T[i] != '#') {
//			ret_t.push_back(T[i]);
//		}
//	}
//	if (ret_t == ret_s)return true;
//	else return false;
//}
//bool backspaceCompare(string S, string T) {
//
//	string a = "", b = "";
//
//	for (auto c : S)
//	{
//		if (c == '#') a.size()>0 ? a.pop_back() : void();
//		else a.push_back(c);
//	}
//
//
//	for (auto t : T)
//	{
//		if (t == '#') b.size()>0 ? b.pop_back() : void();
//		else b.push_back(t);
//	}
//
//	return a.compare(b) == 0;
//
//
//}
/*nt main() {
	string num1, num2;
	vector<int> nums ;
	string T;
	string S ;
	T.push_back('c');
	T.push_back('b');
	T.push_back('#');
	T.push_back('c');
	S.push_back('c');
	S.push_back('d');
	S.push_back('#');
	S.push_back('c');
	backspaceCompare(S, T);
	nums.push_back(7);
	nums.push_back(6);
	nums.push_back(0);
	nums.push_back(3);
	nums.push_back(0);
	nums.push_back(2);
	arrayPairSum(nums);
	num1.push_back('1');
	num2.push_back('9');
	addStrings(num1, num2);
	int num = 38;
	B(num);
	queue<int>s;

}*/
string convertToBase7(int num)
{
	string result;
	int i = 0;
	while (num > 0) {
		int ref = num % 7;
		if (ref == 0) {
			num = num / 7;
			i++;
		}
		else {
			num = num - ref;
			int j = result.size();
			while (j < i) {
				result.push_back((char)(0 + 48));
				j++;
			}
			result.push_back((char)(ref + 48));
		}
	}
	string myresult;
	for (int k = result.size() - 1; k >= 0;k--) {
		myresult.push_back(result[k]);
	}
	return myresult;
}
int calPoints(vector<string>& ops) {
	stack<int> score;
	for (int i = 0; i < ops.size(); i++) {
		if (ops[i] == "C") {
			if (!score.empty()) {
				score.pop();
			}
		}
		else if (ops[i] == "D") {
			if (!score.empty()) {
				int record = score.top();
				score.push(record * 2);
			}
		}
		else if (ops[i] == "+") {
			if (!score.empty()) {
				int size = score.size();
				if (size > 1) {
					int rd1 = score.top();
					score.pop();
					int rd2 = score.top();
					score.pop();
					score.push(rd2);
					score.push(rd1);
					score.push(rd1 + rd2);
				}
				else {
					score.push(score.top());
				}
			}
		}
		else {
			score.push(stoi(ops[i].c_str()));
		}
	}
	int sum = 0;
	while (score.size() > 0) {
		sum = sum + score.top();
		score.pop();
	}
	return sum;
}
//int maxProfit(vector<int>& prices) {
//	map<int, int> record;
//	vector<int> money;
//	bool flag = false;
//	for (int i = 0; i < prices.size(); i++) {
//		record[prices[i]] = i;
//	}
//	for (auto rd = record.begin(); rd != record.end();rd++) {
//		for (auto iter = record.rbegin(); iter != record.rend(); iter++) {
//			if ((*rd).second < (*iter).second) {
//				money.push_back(iter->first - rd->first);
//				break;
//			}
//		}
//	}
//	int temp = 0;
//	for (int i = 0; i < money.size(); i++) {
//		if (money[i]>temp) {
//			temp = money[i];
//		}
//	}
//	return temp;
//}
int maxProfit(vector<int>& prices) {
	int temp1 = 0;
	int temp2 = 0;
	int j = 0;
	int sum = 0;
	for (int i = j; i < prices.size(); i++) {
		temp1 = prices[i];
		temp2 = temp1;
		for (j = i + 1; j < prices.size(); j++) {
			if ((prices[j] <= temp2 && temp2 > temp1)) {
				sum = sum + temp2 - temp1;
				i = j - 1;
				break;
			}
			if (j == (prices.size() - 1) && prices[j] >= temp2&&prices[j] > temp1) {
				sum = sum + prices[j] - temp1;
				i = j;
				break;
			}
			temp2 = prices[j];
		}
	}
	return sum;
}
int binaryGap(int N) {
	vector<int> num;
	while (N > 0) {
		int x = N % 2;
		if (x == 0) {
			N = N / 2;
			num.push_back(x);
		}
		else {
			num.push_back(x);
			N = N - x;
			N = N / 2;
		}
	}
	int temp = 0;
	int sub = 0;
	int flag = 0;
	for (int i = 0; i < num.size(); i++) {
		if (num[i] == 1) {
			flag++;
			if (sub < i - temp&&flag > 1) {
				sub = i - temp;
			}
			temp = i;
		}
	}
	if (flag == 1) {
		sub = 0;
	}
	return sub;
}
bool hasGroupsSizeX(vector<int>& deck) {
	vector<int> record;
	int flag = 0;
	int num = 0;
	bool result = false;
	while (deck.size() > 0) {
		num = 0;
		int temp = deck[0];
		for (int i = 0; i < deck.size(); i++) {
			if (temp == deck[i]) {
				num++;
				if (i <= flag) {
					flag = i;
				}
			}
			else {
				deck[flag] = deck[i];
				flag++;
			}
		}
		if (num < 2) {
			return false;
		}
		else {
			record.push_back(num);
			deck.resize(deck.size() - num);
		}
	}
	for (int i = 0; i < record.size(); i++) {
		int temp1 = record[0];
		int temp2 = record[i];
		int temp3 = 0;
		while (temp2 > 0) {
			temp3 = temp1 %temp2;
			temp1 = temp2;
			temp2 = temp3;
			if (temp2 == 1) {
				return false;
			}
			if (temp2 == 0) {
				result = true;
			}
		}
	}
	return result;
}
int search(vector<int>& nums, int target) {
	int start = 0;
	int end = nums.size();
	int temp = end / 2;
	int cd = start + temp;
	if (nums.size() < 2) {
		if (nums.size() > 0 && nums[0] == target)
			return 0;
		else return -1;
	}
	while (start != end) {
		while (nums[cd] < target) {
			start = start + temp;
			temp = (end - start) / 2;
			cd = start + temp;
		}
		while (nums[cd] > target) {
			end = temp;
			temp = (end - start) / 2;
			cd = temp + start;
		}
		if (nums[cd] == target) {
			return cd;
		}
		if (end - start == 0 && nums[cd] != target) {
			return -1;
		}
	}
	return -1;
}
struct direct {
	int a, b;
};

direct dir[4]{
	{ 1,0 },{ 0,1 },{ -1,0 },{ 0,-1 }
};

int maxAreaOfIsland(vector<vector<int>>& grid) {
	//使用队列存储待访问的点
	int size1 = grid.size();
	if (size1 == 0) {
		return 0;
	}
	int size2 = grid[0].size();
	queue<direct>st; direct dire;
	int d = 0, x, y, m, n, flag = 0; vector<int>cd;

	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size2; j++) {
			flag = 0;
			if (grid[i][j] == 1) {
				dire.a = i; dire.b = j;
				st.push(dire);
				flag++;//计数
				grid[i][j] = 2;//访问过的元素标记为2

				while (!st.empty()) {
					dire = st.front();
					st.pop();
					m = dire.a;
					n = dire.b;
					d = 0;
					//遍历四个方向的值
					while (d < 4) {
						x = m + dir[d].a;
						y = n + dir[d].b;
						if(x >= 0&&y>=0&&x<size1&&y<size2)
						if (grid[x][y] == 1) {
							dire.a = x; dire.b = y;
							st.push(dire);
							flag++;
							grid[x][y] = 2;
						}
						d++;
					}
				}
				cd.push_back(flag);
			}
		}
	}
	int size3 = cd.size();
	if (size3 == 0) {
		return 0;
	}
	int temp = 0;
	for (int i = 0; i < size3; i++) {
		if (cd[i] > temp) {
			temp = cd[i];
		}
	}
	return temp;
}
bool canPlaceFlowers(vector<int>& flowerbed, int n) {
	int count = 0;
	for (int i = 0; i < flowerbed.size(); i++) {
		if (flowerbed[i] == 0) {
			count++;
		}
		if (flowerbed[i] ==1 || i == flowerbed.size() - 1) {
			int m = ((count - 1) / 2.0);
			n = n - m;
			count = 0;
		}
		if (n <= 0)return true;
	}
	if (n <= 0)return true;
	else return false;
}
string countAndSay(int n) {
	if (n <= 1) {
		return "1";
	}

}
int findShortestSubArray(vector<int>& nums) {
	map< int, pair< int, int > >re;
	int j = 0,te = 1;
	for (int i = 0; i < nums.size() - 1; i++) {
		int count = 1;
		te = 1;
		if (re.find(nums[i]) != re.end()) {
			continue;
		}
		for (j = i + 1; j < nums.size(); j++) {
			if (nums[i] == nums[j]) {
				count++;
				te = j;
			}
		}
		if (count == 1) {
			re[nums[i]] = pair<int, int>(count, te);
		}
		else
		{
			re[nums[i]] = pair<int, int>(count, te - i + 1);
		}		
	}
	pair<int, int>temp(0, 50000);
	for (auto iter = re.begin(); iter != re.end(); iter++) {
		if (((*iter).second.first > temp.first)||((*iter).second.first == temp.first&& (*iter).second.second <= temp.second) ) {
			temp = (*iter).second;
		}
	}
	return temp.second;
}
void main()
{
	for (int i = 10; i >= 0;i--) {
		cout << i;

	}
//	vector<vector<int>>grid(6);
//	for (int i = 0; i <6; i++)
//		grid[i].resize(6);
//	for (int i = 0; i < 6; i++)
//		for (int j = 0; j < 6; j =j+2){
//			grid[i][j] = 1;
//	}
////	maxAreaOfIsland(grid);
//	string a; a.erase();
//	string v1 = "uuu";
//	a = v1;
//	v1.erase();
//	queue<int>v;
//	
//	int count = 4;
//	countAndSay(count);
	//int m = (count - 1) / 2.0;

	//int num = 100;
	//cout << 'A' + 32 << endl;
	//int a = 'A' + 32;
	//char c = 'A' + 32;
	vector<string> ops;
	vector <int> prices;
	prices.push_back(1);
	prices.push_back(2);
	prices.push_back(2);
	prices.push_back(3);
	prices.push_back(1);
	prices.push_back(4);
	prices.push_back(2);
	//prices.resize(14,4);
	//hasGroupsSizeX(prices);
	//search(prices, 3);
	ops.push_back("5");
	ops.push_back("-2");
	ops.push_back("4");
	ops.push_back("C");
	ops.push_back("D");
	ops.push_back("9");
	ops.push_back("+");
	ops.push_back("+");
	//calPoints(ops);
	map<pair<int,int>,int>l;
	findShortestSubArray(prices);
	

}