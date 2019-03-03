/*二叉搜索树的建立*/
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;
struct BSTNode{
	int value;
	BSTNode *left, *right;
	//构造函数，初始化
	BSTNode(int data, BSTNode* r = NULL, BSTNode* l = NULL):value(data),right(r),left(l) {}
};
class BSTline {
public:
	BSTline() :Root(NULL){}//构造函数
	~BSTline() { ; }//折构函数
	BSTNode* Creat_BST(string path, BSTNode* &root);//创建树
	bool Insert(int &x,BSTNode* &ptr);//插入节点
	BSTNode* Search(int x,BSTNode* &ptr);//搜索
	bool Remove(int &x,BSTNode* &ptr);//删除节点
	void inBST(BSTNode* ptr);//二叉树的中序遍历
	void writefile(BSTNode* &ptr);//写入文件
private:
	BSTNode *Root;//根节点
	int Refvalue;//输入停止标志
};

//插入节点
//在以ptr为根节点的二叉搜索树中插入节点x
bool BSTline::Insert(int &x, BSTNode* &ptr)
{
	if (ptr == NULL) {//如果为空树，那么将此节点作为根节点
		ptr = new BSTNode(x);//创建新节点
		if (ptr == NULL)exit(1);
		return true;
	}
	else if (x < ptr->value) {
		Insert(x, ptr->left);//在左子树中插入
	}
	else if (x > ptr->value)
		Insert(x,ptr->right);//在有子树中插入
	else return false;
}

//创建二叉搜索树
BSTNode* BSTline::Creat_BST(string path,BSTNode* &root)
{
	//从文件中读取要创建树的数据
	int x; string line;
	ifstream file(path, ifstream::in);
	while (getline(file, line)){//按行读取数据
		stringstream lines(line);
		while (!lines.eof())//判读是否输出完全
		{
			lines >> x;
			Insert(x, root);
		}
	}
	Root = root;
	return root;
}

//二叉搜索树的搜索
BSTNode* BSTline::Search(int x, BSTNode* &ptr)
{
	//以ptr为根节点在二叉搜索树中搜索
	if (ptr == NULL)return NULL;
	else if (x < ptr->value)
		return Search(x, ptr->left);
	else if (x > ptr->value)
		return Search(x,ptr->right);
	else return ptr;//返回搜索到的节点
}

//二叉树的删除
bool BSTline::Remove(int &x, BSTNode* &ptr)
{
	BSTNode* temp;//用于存储搜索节点
	if (ptr != NULL)
		if (x < ptr->value) Remove(x,ptr->left);
		else if (x > ptr->value) Remove(x,ptr->right);
		else if (ptr->left != NULL&&ptr->right != NULL) {//左右子树均不为空在有子
			//树终须遍历的第一个数字填补
			temp = ptr->right;
			while (temp->left != NULL)temp = temp->left;
			ptr->value = temp->value;//数字替换
			Remove(ptr->value, ptr->right);//遍历右子树
		}
		else {
			temp = ptr;//将寻找到的节点赋值给temp
			if (ptr->left == NULL)ptr = ptr->right;//当左右子树有一个不为空时，用另一个填补
			else ptr = ptr->left;
			delete temp;
			}
	return false;
}

//二叉树的中序遍历
void BSTline::inBST(BSTNode* ptr)
{
	if (ptr) {
		inBST(ptr->left);
		ofstream file("indata.txt", ios::app);
		file << ptr->value << " ";
		file.close();
		cout << ptr->value << "--";
		inBST(ptr->right);
	}
}

//将搜索儿茶树按照终须遍历的顺序存入文件
void BSTline::writefile(BSTNode* &ptr)
{
	//将遍历后的数目存入文件
	ofstream file("indata.txt",ios::app);//打开文件，若文件不存在就创建它
	if (!file) return;//打开文件失败则结束运行
	//file << " it my data "<<endl;//写入标题
	//ofstream of("temp.txt", ios::app);
	file.close();
}

void main()
{
	string path = "data.txt";//读取文件路径
	BSTline bst; BSTNode *root=NULL;
	bst.Creat_BST(path,root);//创建
	bst.inBST(root);//中序遍历
	int x = 77;
	cout<<bst.Search(x, root)->value<<endl;
	int i = 11;
	bst.Remove(i,root);//删除
	bst.inBST(root);//中序遍历
	cout << endl;
	int j = 100;
	bst.Insert(j, root);
	bst.inBST(root);//中序遍历
	system("pause");
}
