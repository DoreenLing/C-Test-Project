/*二叉树的建立以及应用*/
#include<iostream>

using namespace std;

struct BinTreeNode {
	char data;
	BinTreeNode *LeftChild, *RightChild;
	BinTreeNode() :LeftChild(NULL), RightChild(NULL){}
	BinTreeNode(char x,BinTreeNode* L=NULL,BinTreeNode* R=NULL) :data(x), LeftChild(L), RightChild(R) {}
};

class BinTree
{
public:
	BinTree() :Root(NULL) {}
	~BinTree() { Destory(Root); }
	void Destory(BinTreeNode *SubTree);
	void CreatBinTree(istream &in,BinTreeNode* &SubTree);
	void PreBinTree(ostream &out, BinTreeNode* &SubTree);
	void inBinTree(ostream &out, BinTreeNode* &SubTree);
	void PostBinTree(ostream &out, BinTreeNode* &SubTree);
	BinTreeNode *CreatTreeP_I(char *VLR,char *LVR,int n);
private:
	BinTreeNode *Root;
};

void BinTree::Destory(BinTreeNode *SubTree)
{
	if (SubTree != NULL) {
		Destory(SubTree->LeftChild);
		Destory(SubTree->RightChild);
		delete SubTree;
	}
}
void BinTree::CreatBinTree(istream &in, BinTreeNode* &SubTree)
{
	char ch;
	cout << "Input the element. If you want to stop it,please 'N': ";
	in >> ch;
	if (ch=='N') SubTree = NULL;
	else{
		SubTree = new BinTreeNode(ch);
		if (SubTree == NULL)
			cout << "Memory allocade false!!!" << endl;
		CreatBinTree(in,SubTree->LeftChild);//输入当然时候需要调两次才能跳出当前循环
		CreatBinTree(in,SubTree->RightChild);
	}
}

BinTreeNode* BinTree::CreatTreeP_I(char *VLR, char *LVR, int n)
{
	if (n == 0)return NULL;
	int k = 0;
	while (VLR[0] != LVR[k])k++;
	BinTreeNode *p = new BinTreeNode(VLR[0]);
	p->LeftChild = CreatTreeP_I(VLR+1,LVR,k);
	p->RightChild = CreatTreeP_I(VLR+k+1,LVR+k+1,n-k-1);
	return p;
}

void BinTree::PreBinTree(ostream &out, BinTreeNode* &SubTree)
{
	if (SubTree){
		cout << SubTree->data << "--";
		PreBinTree(out, SubTree->LeftChild);
		PreBinTree(out, SubTree->RightChild);
	}
}
void BinTree::inBinTree(ostream &out, BinTreeNode* &SubTree)
{
	if (SubTree) {
		inBinTree(out, SubTree->LeftChild);
		cout << SubTree->data << "--";
		inBinTree(out, SubTree->RightChild);
	}
}

void BinTree::PostBinTree(ostream &out, BinTreeNode* &SubTree)
{
	if (SubTree) {
		PostBinTree(out, SubTree->LeftChild);
		PostBinTree(out, SubTree->RightChild);
		cout << SubTree->data << "--";
	}
}

void mainDF()
{
	BinTree A,C;
	BinTreeNode* B,*D;
	A.CreatBinTree(cin,B );
	A.PreBinTree(cout,B);
	cout << endl;
	A.inBinTree(cout, B);
	cout << endl;
	A.PostBinTree(cout,B);
	cout << endl;
	char *X, *Y;
	char M[9] = {'a','q','h','f','d','e','c','k','g'};
	char N[9] = {'h','q','d','f','a','e','k','c','g'};
	X = M; Y = N;
	D = C.CreatTreeP_I(X,Y,9);
	C.PreBinTree(cout, D);
	system("pause");
}