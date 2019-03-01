//#include<_dbdao.h>
/*HuffmanTree Ҳ�����Ŷ����� Ȩֵ��С*/
#include<iostream>
using namespace std;

int Defaultsize = 100;
struct HuffmanNode {
	int data;//Ȩֵ
	HuffmanNode *left;  // ����
	HuffmanNode *right; // �Һ���
	HuffmanNode *parent;// �����
	HuffmanNode() {}
	HuffmanNode(int value, HuffmanNode *l, HuffmanNode *r, HuffmanNode *p) :
		data(value), left(l), right(r), parent(p) {}

};
class HuffmanTree {
public:
	HuffmanTree(){FOUND = new HuffmanNode;flag = 0;};
	~HuffmanTree(){};
	HuffmanNode* CreatTree(int a[],int size);//��������
	// ǰ�����"Huffman��"
    void preOrder(HuffmanNode* tree);
    // �������"Huffman��"
    void inOrder(HuffmanNode* tree);
    // �������"Huffman��"
    void postOrder(HuffmanNode* tree);
	//Ѱ��ȨֵΪWright�Ľڵ�
	HuffmanNode *FoundNode(int wright,HuffmanNode *found);
	int flag;
	HuffmanNode *root;
	HuffmanNode *FOUND;
};

//ʵ�ֹ���������С��
class MinHeap {
private:
	HuffmanNode *mHeap;	// ��С�ѵ�����
	int mCapacity;			// �ܵ�����
	int mSize;				// ��ǰ��Ч���ݵ�����
	int order;             //��������
private:
	// �ϵ��㷨
	void filterUp(int start);
	// �µ��㷨
	void filterDown(int start, int end);
	// ��������HuffmanNode�ڵ��ȫ�����ݣ�i��j�ǽڵ�������
	void swapNode(int i, int j);
public:
	MinHeap();
	~MinHeap();

	// ��node��ȫ�����ݿ�����"��С�ѵ�ָ���ڵ�"
	bool Insert(HuffmanNode *node);
	// ��ȡ��С�ڵ�
	HuffmanNode* dumpFromMinimum();

	// ������С��
	HuffmanNode* create(int a[], int size);
	//�ϲ��ڵ�
	HuffmanNode* merge(HuffmanNode *NodeL,HuffmanNode *NodeR,HuffmanNode *Par,MinHeap *pHeap);
	// ������С��
	void destroy();
};
//���캯��

MinHeap::MinHeap()
{
	order = 0;//
}

//�۹�����
MinHeap::~MinHeap()
{
	destroy();
}

//�������µ���
void MinHeap::filterDown(int start, int end)
{
	int i = start;int j = 2*i+1;//j��i������Ů��λ��
	HuffmanNode temp = mHeap[i];
	while (j<= end)
	{
		if (j<end&&mHeap[j].data>mHeap[j + 1].data)j++;//ָ�����Һ����е���Сֵ
		if (temp.data <= mHeap[j].data)break;
		else {//���н���
			mHeap[i] = mHeap[j];
			i = j; j = i * 2 + 1;//��iָ��������Ů��ֵ��jָ����Ů����Ů
		}
	}
	mHeap[i] = temp;

}

//�������ϵ���
//��Start��0 ����
void MinHeap::filterUp(int start)
{
	int j = start;
	int i = (j - 1) / 2;//iָ��start�ĸ��׽ڵ�
	HuffmanNode temp = mHeap[j];//�洢��ʼ�ڵ�
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

//���������ڵ��ֵ,��i��j�ǽڵ�����
void MinHeap::swapNode(int i, int j)
{
	HuffmanNode temp;
	temp = mHeap[i];
	mHeap[i] = mHeap[j];
	mHeap[j] = temp;
}

// ���룬����λ��Ϊ���һ���ڵ�
bool MinHeap::Insert(HuffmanNode *node)
{
	if (mSize == mCapacity) {
		cout << "Heap have fulled!!!" << endl;
		return false;
	}
	mHeap[mSize] = *node; 
	filterUp(mSize);//���ϵ���Ϊ��С��
	mSize++;
	return true;

}

//������С��
void  MinHeap::destroy()
{
	mCapacity = 0;
	mSize = 0;
	delete []mHeap;
	mHeap = NULL;
}

//������С��
HuffmanNode* MinHeap::create(int a[], int size)
{
	mCapacity = (Defaultsize < size)?size : Defaultsize;//�������
	mHeap = new  HuffmanNode[mCapacity];
	if (mHeap == NULL) {
		cout << "It's false to acllocate the storage" << endl;
		exit(1);
	}
	//��ʼ����
	for (int i= 0; i < size; i++) {
		mHeap[i].data = a[i];
		int k = mHeap[i].data;
		mHeap[i].left = mHeap[i].right = mHeap[i].parent = NULL;
	}
	mSize = size;//��ǰ��Ч������
	int CurrentPos = (mSize - 1) / 2;//��ǰλ��
	while (CurrentPos >= 0) {
		//�ֲ��������µ���Ϊ��С��
		filterDown(CurrentPos, mSize-1);
		CurrentPos--;
	}
	return mHeap;
}

/* 
 * �½�һ���ڵ㣬������С������С�ڵ�����ݸ��Ƹ��ýڵ㡣
 * Ȼ�����С�ڵ�֮����������¹������С�ѡ�
 *
 * ����ֵ��
 *     ʧ�ܷ���NULL��
 */
HuffmanNode *MinHeap::dumpFromMinimum()
{
	HuffmanNode *myMiniNode = new HuffmanNode;
	if(myMiniNode == NULL)
		return NULL;
	int i = mSize;
	if(i >= 0){
		*myMiniNode = mHeap[0];//����С�ڵ㸳���½ڵ�
		mHeap[0] = mHeap[mSize-1];//�����һ��Ԫ�ز������ڵ�
		mSize--;
		filterDown(0,mSize-1);//���µ����㷨
		return myMiniNode;
	}
	else return NULL;	
}
//�ϲ��ڵ�
HuffmanNode* MinHeap::merge(HuffmanNode *NodeL,HuffmanNode *NodeR,HuffmanNode *Par,MinHeap *pHeap)
{
	NodeL = pHeap->dumpFromMinimum();//������ڵ������ҽڵ�
	NodeR = pHeap->dumpFromMinimum();//�����ҽڵ�
	Par->data = NodeL->data+NodeR->data;
	Par->left = NodeL;
	Par->right = NodeR;
	NodeL->parent = Par;
	NodeR->parent = Par;
	Insert(Par);
	return Par;
}
//������������
HuffmanNode* HuffmanTree::CreatTree(int a[],int size)
{
	HuffmanNode *NodeL = new HuffmanNode;
	HuffmanNode *NodeR = new HuffmanNode;
	HuffmanNode *Par = new HuffmanNode;;
	MinHeap *heap = new MinHeap();
	heap->create(a,size);//��������a����С��
	for(int i = 0;i<size-1;i++){
		Par = new HuffmanNode;
		Par = heap->merge(NodeL,NodeR,Par,heap);
	}
	 root = Par;
    // ������С��
    heap->destroy();
    delete heap;
	root->parent = NULL;
	return root;
}
//ǰ�����
void HuffmanTree::preOrder(HuffmanNode *Tree)
{	
	if(Tree){
		cout<<Tree->data<<endl;
		postOrder(Tree->left);
		postOrder(Tree->right);
	}
}
//�������
void HuffmanTree::inOrder(HuffmanNode *Tree)
{	
	if(Tree){
		postOrder(Tree->left);
		cout<<Tree->data<<endl;
		postOrder(Tree->right);
	}
}
//�������
void HuffmanTree::postOrder(HuffmanNode *Tree)
{
	if(Tree){
		postOrder(Tree->left);
		postOrder(Tree->right);	
		cout<<Tree->data<<endl;
	}
}
//Ѱ��ȨֵΪWright�Ľڵ㣬�����ظýڵ�
HuffmanNode *HuffmanTree::FoundNode(int wright,HuffmanNode *found)
{
	//�������������˼��
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