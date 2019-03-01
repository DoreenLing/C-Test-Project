//#include<_dbdao.h>
/*HuffmanTree 也叫最优二叉树 权值最小*/
#include<iostream>
using namespace std;

int Defaultsize = 100;
struct HuffmanNode {
	int data;//权值
	HuffmanNode *left;  // 左孩子
	HuffmanNode *right; // 右孩子
	HuffmanNode *parent;// 父结点
	HuffmanNode() {}
	HuffmanNode(int value, HuffmanNode *l, HuffmanNode *r, HuffmanNode *p) :
		data(value), left(l), right(r), parent(p) {}

};
class HuffmanTree {
public:
	HuffmanTree(){FOUND = new HuffmanNode;flag = 0;};
	~HuffmanTree(){};
	HuffmanNode* CreatTree(int a[],int size);//创建函数
	// 前序遍历"Huffman树"
    void preOrder(HuffmanNode* tree);
    // 中序遍历"Huffman树"
    void inOrder(HuffmanNode* tree);
    // 后序遍历"Huffman树"
    void postOrder(HuffmanNode* tree);
	//寻找权值为Wright的节点
	HuffmanNode *FoundNode(int wright,HuffmanNode *found);
	int flag;
	HuffmanNode *root;
	HuffmanNode *FOUND;
};

//实现哈夫曼的最小堆
class MinHeap {
private:
	HuffmanNode *mHeap;	// 最小堆的数组
	int mCapacity;			// 总的容量
	int mSize;				// 当前有效数据的数量
	int order;             //遍历计数
private:
	// 上调算法
	void filterUp(int start);
	// 下调算法
	void filterDown(int start, int end);
	// 交换两个HuffmanNode节点的全部数据，i和j是节点索引。
	void swapNode(int i, int j);
public:
	MinHeap();
	~MinHeap();

	// 将node的全部数据拷贝给"最小堆的指定节点"
	bool Insert(HuffmanNode *node);
	// 获取最小节点
	HuffmanNode* dumpFromMinimum();

	// 创建最小堆
	HuffmanNode* create(int a[], int size);
	//合并节点
	HuffmanNode* merge(HuffmanNode *NodeL,HuffmanNode *NodeR,HuffmanNode *Par,MinHeap *pHeap);
	// 销毁最小堆
	void destroy();
};
//构造函数

MinHeap::MinHeap()
{
	order = 0;//
}

//折构函数
MinHeap::~MinHeap()
{
	destroy();
}

//自上向下调整
void MinHeap::filterDown(int start, int end)
{
	int i = start;int j = 2*i+1;//j在i的左子女的位置
	HuffmanNode temp = mHeap[i];
	while (j<= end)
	{
		if (j<end&&mHeap[j].data>mHeap[j + 1].data)j++;//指向左右孩子中的最小值
		if (temp.data <= mHeap[j].data)break;
		else {//进行交换
			mHeap[i] = mHeap[j];
			i = j; j = i * 2 + 1;//将i指向现在子女的值，j指向子女的子女
		}
	}
	mHeap[i] = temp;

}

//自下向上调整
//从Start到0 调整
void MinHeap::filterUp(int start)
{
	int j = start;
	int i = (j - 1) / 2;//i指向start的父亲节点
	HuffmanNode temp = mHeap[j];//存储开始节点
	while (j > 0) {
		if (temp.data >= mHeap[i].data)break;
		else {
			mHeap[j] = mHeap[i];
			j = i;
			i = (j - 1) / 2;
		}
	}
	mHeap[j] = temp;
}

//交换两个节点的值,，i和j是节点索引
void MinHeap::swapNode(int i, int j)
{
	HuffmanNode temp;
	temp = mHeap[i];
	mHeap[i] = mHeap[j];
	mHeap[j] = temp;
}

// 插入，插入位置为最后一个节点
bool MinHeap::Insert(HuffmanNode *node)
{
	if (mSize == mCapacity) {
		cout << "Heap have fulled!!!" << endl;
		return false;
	}
	mHeap[mSize] = *node; 
	filterUp(mSize);//向上调整为最小堆
	mSize++;
	return true;

}

//销毁最小堆
void  MinHeap::destroy()
{
	mCapacity = 0;
	mSize = 0;
	delete []mHeap;
	mHeap = NULL;
}

//创建最小堆
HuffmanNode* MinHeap::create(int a[], int size)
{
	mCapacity = (Defaultsize < size)?size : Defaultsize;//最大容量
	mHeap = new  HuffmanNode[mCapacity];
	if (mHeap == NULL) {
		cout << "It's false to acllocate the storage" << endl;
		exit(1);
	}
	//初始化堆
	for (int i= 0; i < size; i++) {
		mHeap[i].data = a[i];
		int k = mHeap[i].data;
		mHeap[i].left = mHeap[i].right = mHeap[i].parent = NULL;
	}
	mSize = size;//当前有效数据量
	int CurrentPos = (mSize - 1) / 2;//当前位置
	while (CurrentPos >= 0) {
		//局部自上向下调整为最小堆
		filterDown(CurrentPos, mSize-1);
		CurrentPos--;
	}
	return mHeap;
}

/* 
 * 新建一个节点，并将最小堆中最小节点的数据复制给该节点。
 * 然后除最小节点之外的数据重新构造成最小堆。
 *
 * 返回值：
 *     失败返回NULL。
 */
HuffmanNode *MinHeap::dumpFromMinimum()
{
	HuffmanNode *myMiniNode = new HuffmanNode;
	if(myMiniNode == NULL)
		return NULL;
	int i = mSize;
	if(i >= 0){
		*myMiniNode = mHeap[0];//将最小节点赋给新节点
		mHeap[0] = mHeap[mSize-1];//将最后一个元素补到根节点
		mSize--;
		filterDown(0,mSize-1);//向下调整算法
		return myMiniNode;
	}
	else return NULL;	
}
//合并节点
HuffmanNode* MinHeap::merge(HuffmanNode *NodeL,HuffmanNode *NodeR,HuffmanNode *Par,MinHeap *pHeap)
{
	NodeL = pHeap->dumpFromMinimum();//先是左节点再是右节点
	NodeR = pHeap->dumpFromMinimum();//再是右节点
	Par->data = NodeL->data+NodeR->data;
	Par->left = NodeL;
	Par->right = NodeR;
	NodeL->parent = Par;
	NodeR->parent = Par;
	Insert(Par);
	return Par;
}
//创建哈夫曼树
HuffmanNode* HuffmanTree::CreatTree(int a[],int size)
{
	HuffmanNode *NodeL = new HuffmanNode;
	HuffmanNode *NodeR = new HuffmanNode;
	HuffmanNode *Par = new HuffmanNode;;
	MinHeap *heap = new MinHeap();
	heap->create(a,size);//创建关于a的最小堆
	for(int i = 0;i<size-1;i++){
		Par = new HuffmanNode;
		Par = heap->merge(NodeL,NodeR,Par,heap);
	}
	 root = Par;
    // 销毁最小堆
    heap->destroy();
    delete heap;
	root->parent = NULL;
	return root;
}
//前序遍历
void HuffmanTree::preOrder(HuffmanNode *Tree)
{	
	if(Tree){
		cout<<Tree->data<<endl;
		postOrder(Tree->left);
		postOrder(Tree->right);
	}
}
//中序遍历
void HuffmanTree::inOrder(HuffmanNode *Tree)
{	
	if(Tree){
		postOrder(Tree->left);
		cout<<Tree->data<<endl;
		postOrder(Tree->right);
	}
}
//后序遍历
void HuffmanTree::postOrder(HuffmanNode *Tree)
{
	if(Tree){
		postOrder(Tree->left);
		postOrder(Tree->right);	
		cout<<Tree->data<<endl;
	}
}
//寻找权值为Wright的节点，并返回该节点
HuffmanNode *HuffmanTree::FoundNode(int wright,HuffmanNode *found)
{
	//利用中序遍历的思想
	if (flag == 1)
		return FOUND;
	if(found){
		FoundNode(wright,found->left);
		int a = found->data;
		if(wright == found->data&&found->left!=NULL&&found->right!=NULL){
			FOUND = found;
			//return found;
			flag = 1;
		}
		FoundNode(wright,found->right);
	}
}