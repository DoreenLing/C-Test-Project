#pragma once
/*******************88888888888*/
// B-树 多用于文件查找系统
/*********************************/
#include<iostream>

#define m  3 //定义树的阶数
 
template<class T>
struct Node {
	int keynum; //关键字的数量
	T key[m + 1];//关键字，这里统一从一开始计数
	Node<T> *parent;//父亲节点
	Node<T> *child[m + 1];//记录孩子节点
	Node() :keynum(0), parent(NULL) {
		for (int i = 0; i <= m; i++) {
			key[i] = 0;
			child[i] = NULL;
		}
	}
};

//搜索结果三元组定义
template<class T>
struct Triple {
	Node<T> *r;//节点地址
	int k, tag; //k节点中关键码序号
	            //tag 搜索成功标志，1 成功，0 失败
};
template<class T>
class B_Tree {
public:
	B_Tree() { root = new Node<T>; }
	~B_Tree() {}

	Triple<T> SearchKey_BTree(T key);//查找函数
	bool Insert_BTree(T key);//插入
	bool Delete_BTree(T key);
private:
	Node<T> * Gethead();
	int Search(T K, Node<T>* & ptr);
	void Insert(T k,int p,Node<T>*&ptr,Node<T> *cl);
	bool Split(Node<T> *& tree, Node<T> * & ap); //结点分裂
	bool Newroot(Node<T> * &ptr, Node<T> * &lchild, Node<T> * &rchild, T key);
	void RotateLeft(Node<T> * ptr, Node<T> * par, int m_c, int pos_p);//左旋
	void RotateRight(Node<T> * ptr, Node<T> * par, int m_c, int pos_p);//右旋
	void Merge(Node<T> * ptr, Node<T> * par, Node<T> * pl, int pos_p);//节点合并
	//void WalkThrough(Node<T> * & tree);
private:
	Node<T> *root;//根节点
};

//function:得到根节点
template<class T>
Node<T> * B_Tree<T>::Gethead()
{
	root->parent = NULL;
//	root->parent->keynum = 0;
	 return root;
}
//function:建立新节点
//para:prt; 待建立的节点
//para:lchild:左孩子
//para: rchild :右孩子
template<class T>
bool B_Tree<T>::Newroot(Node<T> * &ptr, Node<T> * &lchild, Node<T> * &rchild,T key)
{
	ptr->keynum = 1;
	ptr->key[1] = key;
	ptr->child[0] = lchild;
	if (lchild) {
		ptr->child[0]->parent = ptr;
	}
	ptr->child[1] = rchild;
	if (rchild) {
		ptr->child[1]->parent = ptr;
	}
	return true;
}

//function:查找关键字
//para:K; 待查找的关键字
//para: ptr:当前带查找的节点
template<class T>
int B_Tree<T>::Search(T K, Node<T>* & ptr)
{
	int j = 0;
	for (int i = 1; i < ptr->keynum + 1;i++) {
		if (K >= ptr->key[i]) {
			j = i;
		}
	}
	return j;
}

//function:查找关键字
//para:K; 待查找的关键字
//para: tree: 树
template<class T>
Triple<T> B_Tree<T>::SearchKey_BTree(T key)
{
	Node<T>* p = Gethead();//获取根节点
	Node<T>* q = NULL;
	Triple<T> result;
	int i = 0;
	while (p){
		i = this->Search(key,p);
		//记住I返回的两种情况：第一种是找到对应的关键字
		//第二种是找到最后一个小于k的关键字下标
		if (i > 0 && p->key[i] == key) {
			//找到了记录节点的关键字
			result.r = p;
			result.tag = 1;
			result.k = i;
			return result;
		}
		else {
			q = p;//记录p的值，方便返回
			p = p->child[i];
		}
	}
	//返回插入点
	result.r = q; result.k = i; result.tag = 0;
	return result;
}

//function:在某一个节点插入关键字
//para: K; 待插入的关键字
//para: p; 插入关键字的位置
//para: ptr:当前需要插入的节点
//para: cl,插入关键码的孩子
template<class T>
void B_Tree<T>::Insert(T k, int p, Node<T>*&ptr, Node<T> *cl)
{
	//将节点插入到key[p]中
	for (int i = ptr->keynum; i > p;i--) {
		//这里需要将节点后移
		ptr->key[i + 1] = ptr->key[i];
		ptr->child[i + 1] = ptr->child[i];
	}
	//插入新的关键字
	ptr->key[p + 1] = k;
	ptr->child[p+1] = cl;//新插入的关键字，孩子节点空
	ptr->keynum++;
}

//function:分裂节点
//para: ptr; 待分裂的节点
//para: ap:新分裂出来的节点
template<class T>
bool B_Tree<T>::Split(Node<T> *& ptr, Node<T> * & ap)
{
	//将节点Q分裂成两个节点，前一半保留后一半移入新生节点ap
	int s = (m + 1) / 2;
	//ap = new Node<T>;
	if (!ap) {
		return false;
	}
	if (ptr->child[s]) {
		ap->child[0] = ptr->child[s];//将原来节点中间位置关键字
					//相应指针指向的子树放到新生节点的0位置
	}
	for (int i = s + 1; i <= m; i++ ) {
		//后一半移入ap
		ap->child[i - s] = ptr->child[i];  ptr->child[i] = NULL;
		ap->key[i - s] = ptr->key[i]; ptr->key[i] = 0;
		//改变孩子指针
		if (ap->child[i - s]) {
			ap->child[i - s]->parent = ap;
		}
	}
	ap->keynum = m - s;
	ap->parent = ptr->parent;
	ptr->keynum = s - 1; 
	return true;
}

//function:在某一个节点插入关键字
//para: key; 待插入的关键字
template<class T>
bool B_Tree<T>::Insert_BTree(T key)
{
	Triple<T> loc = SearchKey_BTree(key);//在树种搜索key插入的位置
	if (loc.tag == 1) {
		return false;
	}
	Node<T>* ptr = loc.r;//获取插入的节点
	Node<T>* ap,*temp;
	Node<T>* cl = NULL;
	int pos = loc.k;
	while (1) {
		//先将前节点可以直接插入
		Insert(key, pos, ptr, cl);
		if (ptr->keynum < m) {
			return true;
		}
		//如果当前节点不能直接插入
		//准备分裂节点
		int s = (m + 1) / 2;//s是[m/2]的下标
		ap = new Node<T>;//新分裂出来的节点
		if (!Split(ptr,ap)) {//分裂
			return false;
		}
		key = ptr->key[s];
		T temps = key;
		
		//从下向上进行调整，ptr不为根
		if (ptr->parent != NULL) {
			ptr = ptr->parent;
			pos = Search(temps, ptr);//在父亲节点中搜索插入temps的位置
			cl = ap;
		}
		else {//如果ptr已经是父亲节点了
			//产生新的根
			Node<T>* myroot = new Node<T>;
			myroot->key[1] = temps;
			myroot->keynum = 1;
			myroot->child[0] = ptr;
			myroot->child[1] = ap;
			ptr->parent = ap->parent = myroot;
			root = myroot;
			return true;
		}
	}
	return true;
}

//function:右兄弟和父亲节点替换
//para: ptr; 当前节点
//para: par:父亲节点
//para: m_c:节点应该保持的最少阶数
//para: pos_p:父亲节点调整的位置
template<class T>
void B_Tree<T>::RotateRight(Node<T> * ptr, Node<T> * par, int m_c, int pos_p)
{
	Node<T> * pl = par->child[pos_p +1];//当前节点的右节点
	int d = m_c;
	if (pl->keynum > d - 1) {
		ptr->key[ptr->keynum + 1] = par->key[pos_p + 1];//父亲节点中相应节点下移
		par->key[pos_p + 1] = pl->key[1];//右兄弟最小关键码上移父节点
		ptr->child[ptr->keynum + 1] = pl->child[0];//有兄弟最左指针左移
		if (ptr->child[ptr->keynum + 1]) {
			ptr->child[ptr->keynum + 1]->parent = ptr;
		}
		ptr->keynum++;
		//右兄弟剩余节点左移
		for (int i = 1; i < pl->keynum; i++) {
			pl->key[i] = pl->key[i + 1];
			pl->child[i - 1] = pl->child[i];
		}
		pl->child[pl->keynum] = NULL;
		pl->key[pl->keynum] = 0;
		pl->keynum--;
	}
	else Merge(ptr,par, pl,1);
}

//function:左兄弟和父亲节点替换
//para: ptr; 当前节点
//para: par:父亲节点
//para: m_c:节点应该保持的最少阶数
//para: pos_p:父亲节点调整的位置
template<class T>
void B_Tree<T>::RotateLeft(Node<T> * ptr, Node<T> * par, int m_c, int pos_p)
{
	Node<T>* pl = par->child[pos_p];//当前节点的左节点
	int d = m_c;
	if (pl->keynum > d-1) {
		ptr->key[0] = par->key[pos_p];//父亲节点中相应节点下移
		par->key[pos_p] = pl->key[ptr->keynum];//左兄弟最右边节点上移
		for (int i = ptr->keynum; i >= 0; --i) {//当前节点右移
			ptr->key[i + 1] = ptr->key[i];
			ptr->child[i + 1] = ptr->child[i];
		}
		ptr->keynum++;
		ptr->child[0] = pl->child[pl->keynum];//左兄弟最右指针右移
		if (ptr->child[0]) {
			ptr->child[0]->parent = ptr;
		}
		pl->key[pl->keynum] = 0;
		pl->child[pl->keynum] = NULL;
		pl->keynum--;
	}
	else Merge(ptr, par, pl, pos_p);
}

//function:合并节点
//para: ptr; 当前节点
//para: par:父亲节点
//para: pl:右兄弟
//para: pos_p:父亲节点合并的位置
template<class T>
void B_Tree<T>::Merge(Node<T> * ptr, Node<T> * par, Node<T> * pl, int pos_p)
{
	//将当前父节点找那个分割二者的关键字下移到当前节点
	ptr->key[ptr->keynum + 1] = par->key[pos_p];
	ptr->keynum++;
	//从右兄弟左移一个指针
	//ptr->child[ptr->keynum + 1] = pl->child[0];
	//为了方便，先将右节点全部合并到当前节点
	for (int i = 1; i<=pl->keynum;i++) {
		ptr->key[ptr->keynum + i] = pl->key[i];
		ptr->child[ptr->keynum + i] = pl->child[i];
		ptr->keynum++;
	}
	//将当前节点全部合并到右边节点
	for(int i = ptr->keynum; i > 0; i--){
		pl->key[i] = ptr->key[i];
		pl->child[i] = ptr->child[i];
	}
	pl->keynum = ptr->keynum;
	ptr->keynum = 0;
	//将父亲节点的值和指针左移
	par->child[pos_p-1] = par->child[pos_p];
	for (int i = pos_p; i < par->keynum;i++) {
		par->key[i] = par->key[i+1];
		par->child[i] = par->child[i+1];
	}
	par->keynum--;
}

//function:合并节点
//para: tree; 当前树
//para: key: 待删除的关键字
template<class T>
bool B_Tree<T>::Delete_BTree( T key)
{
	Triple<T> loc = SearchKey_BTree(key);//搜索key
	if (loc.tag == 0) {
		return false;
	}
	Node<T> *ptr = loc.r, *temp,*mychild;//找到，删除
	int pos = loc.k;//删除的关键字的位置
	//第一种情况，该节点非叶子节点
	if (ptr->child[pos]!= NULL) {
		//从child[pos]里面找出最小关键字，
		//替代key[pos]
		mychild = ptr->child[pos];
		temp = ptr;
		while (mychild != NULL) {
			temp = mychild;
			mychild = mychild->child[0];
		}
		ptr->key[pos] = temp->key[1];
		//在叶节点中关键字和指针向前移动，删除key[1]
		for (int i = 1; i <temp->keynum; i++) {
			temp->key[i] = temp->key[i + 1];
		}
		temp->keynum--;
		ptr = temp;//转化为叶子节点删除
	}
	else{
		for (int i = 1; i < ptr->keynum; i++) {
			ptr->key[i] = ptr->key[i + 1];
		}
		ptr->keynum--;
	}
	//删除叶节点
	
	int d = (m + 1) / 2;
	while (1) {
		//情况2，n = [m/2] - 1,需要进行调整
		if (ptr->keynum < d - 1) {
			temp = ptr->parent;//找到父亲节点
			int j = 0;
			while (j <= temp->keynum&&temp->child[j]!=ptr) {//在父亲 节点中找到调整位置
				j++;
			}
			if (j == 0) {//与右兄弟联合调整
				RotateRight(ptr, temp, d, j);
			}
			else {//与左兄弟联合调整
				RotateLeft(ptr, temp, d, j);
			}
			ptr = temp;
			if(ptr ->parent == NULL) break;
		}
		else break;//不用调整
	}
	if (ptr->parent == NULL) {
		//ptr = ptr->parent->child[0];
		ptr->parent = NULL;
		root = ptr;
	}
	return true;
}