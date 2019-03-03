
#include<vector>
#include"B_Tree.h"
using namespace std;

void main()
{
	//B_Tree<int> a;
	//a.Insert_BTree(1);
	//a.Insert_BTree(2);
	//a.Insert_BTree(3);
	//a.Insert_BTree(4);
	//a.Insert_BTree(5);
	//a.Delete_BTree(1);
	//vector<int> nums(2);
	//vector<int> nums1(2);
	////nums.push_back(1);
	//nums[0] = 2;
	//nums[1] = 2;
	//nums.swap(nums1);

	int i  = 1, *ri = nullptr;
	i = 5; ri = &i;
	int **s = &ri;
	int j, &rj = *ri;
	j = 3.14;
	rj = i;
	cout << i << "    " << *ri << endl;
}