#pragma once
/*******************88888888888*/
// B-�� �������ļ�����ϵͳ
/*********************************/
#include<iostream>

#define m  3 //�������Ľ���
 
template<class T>
struct Node {
	int keynum; //�ؼ��ֵ�����
	T key[m + 1];//�ؼ��֣�����ͳһ��һ��ʼ����
	Node<T> *parent;//���׽ڵ�
	Node<T> *child[m + 1];//��¼���ӽڵ�
	Node() :keynum(0), parent(NULL) {
		for (int i = 0; i <= m; i++) {
			key[i] = 0;
			child[i] = NULL;
		}
	}
};

//���������Ԫ�鶨��
template<class T>
struct Triple {
	Node<T> *r;//�ڵ��ַ
	int k, tag; //k�ڵ��йؼ������
	            //tag �����ɹ���־��1 �ɹ���0 ʧ��
};
template<class T>
class B_Tree {
public:
	B_Tree() { root = new Node<T>; }
	~B_Tree() {}

	Triple<T> SearchKey_BTree(T key);//���Һ���
	bool Insert_BTree(T key);//����
	bool Delete_BTree(T key);
private:
	Node<T> * Gethead();
	int Search(T K, Node<T>* & ptr);
	void Insert(T k,int p,Node<T>*&ptr,Node<T> *cl);
	bool Split(Node<T> *& tree, Node<T> * & ap); //������
	bool Newroot(Node<T> * &ptr, Node<T> * &lchild, Node<T> * &rchild, T key);
	void RotateLeft(Node<T> * ptr, Node<T> * par, int m_c, int pos_p);//����
	void RotateRight(Node<T> * ptr, Node<T> * par, int m_c, int pos_p);//����
	void Merge(Node<T> * ptr, Node<T> * par, Node<T> * pl, int pos_p);//�ڵ�ϲ�
	//void WalkThrough(Node<T> * & tree);
private:
	Node<T> *root;//���ڵ�
};

//function:�õ����ڵ�
template<class T>
Node<T> * B_Tree<T>::Gethead()
{
	root->parent = NULL;
//	root->parent->keynum = 0;
	 return root;
}
//function:�����½ڵ�
//para:prt; �������Ľڵ�
//para:lchild:����
//para: rchild :�Һ���
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

//function:���ҹؼ���
//para:K; �����ҵĹؼ���
//para: ptr:��ǰ�����ҵĽڵ�
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

//function:���ҹؼ���
//para:K; �����ҵĹؼ���
//para: tree: ��
template<class T>
Triple<T> B_Tree<T>::SearchKey_BTree(T key)
{
	Node<T>* p = Gethead();//��ȡ���ڵ�
	Node<T>* q = NULL;
	Triple<T> result;
	int i = 0;
	while (p){
		i = this->Search(key,p);
		//��סI���ص������������һ�����ҵ���Ӧ�Ĺؼ���
		//�ڶ������ҵ����һ��С��k�Ĺؼ����±�
		if (i > 0 && p->key[i] == key) {
			//�ҵ��˼�¼�ڵ�Ĺؼ���
			result.r = p;
			result.tag = 1;
			result.k = i;
			return result;
		}
		else {
			q = p;//��¼p��ֵ�����㷵��
			p = p->child[i];
		}
	}
	//���ز����
	result.r = q; result.k = i; result.tag = 0;
	return result;
}

//function:��ĳһ���ڵ����ؼ���
//para: K; ������Ĺؼ���
//para: p; ����ؼ��ֵ�λ��
//para: ptr:��ǰ��Ҫ����Ľڵ�
//para: cl,����ؼ���ĺ���
template<class T>
void B_Tree<T>::Insert(T k, int p, Node<T>*&ptr, Node<T> *cl)
{
	//���ڵ���뵽key[p]��
	for (int i = ptr->keynum; i > p;i--) {
		//������Ҫ���ڵ����
		ptr->key[i + 1] = ptr->key[i];
		ptr->child[i + 1] = ptr->child[i];
	}
	//�����µĹؼ���
	ptr->key[p + 1] = k;
	ptr->child[p+1] = cl;//�²���Ĺؼ��֣����ӽڵ��
	ptr->keynum++;
}

//function:���ѽڵ�
//para: ptr; �����ѵĽڵ�
//para: ap:�·��ѳ����Ľڵ�
template<class T>
bool B_Tree<T>::Split(Node<T> *& ptr, Node<T> * & ap)
{
	//���ڵ�Q���ѳ������ڵ㣬ǰһ�뱣����һ�����������ڵ�ap
	int s = (m + 1) / 2;
	//ap = new Node<T>;
	if (!ap) {
		return false;
	}
	if (ptr->child[s]) {
		ap->child[0] = ptr->child[s];//��ԭ���ڵ��м�λ�ùؼ���
					//��Ӧָ��ָ��������ŵ������ڵ��0λ��
	}
	for (int i = s + 1; i <= m; i++ ) {
		//��һ������ap
		ap->child[i - s] = ptr->child[i];  ptr->child[i] = NULL;
		ap->key[i - s] = ptr->key[i]; ptr->key[i] = 0;
		//�ı亢��ָ��
		if (ap->child[i - s]) {
			ap->child[i - s]->parent = ap;
		}
	}
	ap->keynum = m - s;
	ap->parent = ptr->parent;
	ptr->keynum = s - 1; 
	return true;
}

//function:��ĳһ���ڵ����ؼ���
//para: key; ������Ĺؼ���
template<class T>
bool B_Tree<T>::Insert_BTree(T key)
{
	Triple<T> loc = SearchKey_BTree(key);//����������key�����λ��
	if (loc.tag == 1) {
		return false;
	}
	Node<T>* ptr = loc.r;//��ȡ����Ľڵ�
	Node<T>* ap,*temp;
	Node<T>* cl = NULL;
	int pos = loc.k;
	while (1) {
		//�Ƚ�ǰ�ڵ����ֱ�Ӳ���
		Insert(key, pos, ptr, cl);
		if (ptr->keynum < m) {
			return true;
		}
		//�����ǰ�ڵ㲻��ֱ�Ӳ���
		//׼�����ѽڵ�
		int s = (m + 1) / 2;//s��[m/2]���±�
		ap = new Node<T>;//�·��ѳ����Ľڵ�
		if (!Split(ptr,ap)) {//����
			return false;
		}
		key = ptr->key[s];
		T temps = key;
		
		//�������Ͻ��е�����ptr��Ϊ��
		if (ptr->parent != NULL) {
			ptr = ptr->parent;
			pos = Search(temps, ptr);//�ڸ��׽ڵ�����������temps��λ��
			cl = ap;
		}
		else {//���ptr�Ѿ��Ǹ��׽ڵ���
			//�����µĸ�
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

//function:���ֵܺ͸��׽ڵ��滻
//para: ptr; ��ǰ�ڵ�
//para: par:���׽ڵ�
//para: m_c:�ڵ�Ӧ�ñ��ֵ����ٽ���
//para: pos_p:���׽ڵ������λ��
template<class T>
void B_Tree<T>::RotateRight(Node<T> * ptr, Node<T> * par, int m_c, int pos_p)
{
	Node<T> * pl = par->child[pos_p +1];//��ǰ�ڵ���ҽڵ�
	int d = m_c;
	if (pl->keynum > d - 1) {
		ptr->key[ptr->keynum + 1] = par->key[pos_p + 1];//���׽ڵ�����Ӧ�ڵ�����
		par->key[pos_p + 1] = pl->key[1];//���ֵ���С�ؼ������Ƹ��ڵ�
		ptr->child[ptr->keynum + 1] = pl->child[0];//���ֵ�����ָ������
		if (ptr->child[ptr->keynum + 1]) {
			ptr->child[ptr->keynum + 1]->parent = ptr;
		}
		ptr->keynum++;
		//���ֵ�ʣ��ڵ�����
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

//function:���ֵܺ͸��׽ڵ��滻
//para: ptr; ��ǰ�ڵ�
//para: par:���׽ڵ�
//para: m_c:�ڵ�Ӧ�ñ��ֵ����ٽ���
//para: pos_p:���׽ڵ������λ��
template<class T>
void B_Tree<T>::RotateLeft(Node<T> * ptr, Node<T> * par, int m_c, int pos_p)
{
	Node<T>* pl = par->child[pos_p];//��ǰ�ڵ����ڵ�
	int d = m_c;
	if (pl->keynum > d-1) {
		ptr->key[0] = par->key[pos_p];//���׽ڵ�����Ӧ�ڵ�����
		par->key[pos_p] = pl->key[ptr->keynum];//���ֵ����ұ߽ڵ�����
		for (int i = ptr->keynum; i >= 0; --i) {//��ǰ�ڵ�����
			ptr->key[i + 1] = ptr->key[i];
			ptr->child[i + 1] = ptr->child[i];
		}
		ptr->keynum++;
		ptr->child[0] = pl->child[pl->keynum];//���ֵ�����ָ������
		if (ptr->child[0]) {
			ptr->child[0]->parent = ptr;
		}
		pl->key[pl->keynum] = 0;
		pl->child[pl->keynum] = NULL;
		pl->keynum--;
	}
	else Merge(ptr, par, pl, pos_p);
}

//function:�ϲ��ڵ�
//para: ptr; ��ǰ�ڵ�
//para: par:���׽ڵ�
//para: pl:���ֵ�
//para: pos_p:���׽ڵ�ϲ���λ��
template<class T>
void B_Tree<T>::Merge(Node<T> * ptr, Node<T> * par, Node<T> * pl, int pos_p)
{
	//����ǰ���ڵ����Ǹ��ָ���ߵĹؼ������Ƶ���ǰ�ڵ�
	ptr->key[ptr->keynum + 1] = par->key[pos_p];
	ptr->keynum++;
	//�����ֵ�����һ��ָ��
	//ptr->child[ptr->keynum + 1] = pl->child[0];
	//Ϊ�˷��㣬�Ƚ��ҽڵ�ȫ���ϲ�����ǰ�ڵ�
	for (int i = 1; i<=pl->keynum;i++) {
		ptr->key[ptr->keynum + i] = pl->key[i];
		ptr->child[ptr->keynum + i] = pl->child[i];
		ptr->keynum++;
	}
	//����ǰ�ڵ�ȫ���ϲ����ұ߽ڵ�
	for(int i = ptr->keynum; i > 0; i--){
		pl->key[i] = ptr->key[i];
		pl->child[i] = ptr->child[i];
	}
	pl->keynum = ptr->keynum;
	ptr->keynum = 0;
	//�����׽ڵ��ֵ��ָ������
	par->child[pos_p-1] = par->child[pos_p];
	for (int i = pos_p; i < par->keynum;i++) {
		par->key[i] = par->key[i+1];
		par->child[i] = par->child[i+1];
	}
	par->keynum--;
}

//function:�ϲ��ڵ�
//para: tree; ��ǰ��
//para: key: ��ɾ���Ĺؼ���
template<class T>
bool B_Tree<T>::Delete_BTree( T key)
{
	Triple<T> loc = SearchKey_BTree(key);//����key
	if (loc.tag == 0) {
		return false;
	}
	Node<T> *ptr = loc.r, *temp,*mychild;//�ҵ���ɾ��
	int pos = loc.k;//ɾ���Ĺؼ��ֵ�λ��
	//��һ��������ýڵ��Ҷ�ӽڵ�
	if (ptr->child[pos]!= NULL) {
		//��child[pos]�����ҳ���С�ؼ��֣�
		//���key[pos]
		mychild = ptr->child[pos];
		temp = ptr;
		while (mychild != NULL) {
			temp = mychild;
			mychild = mychild->child[0];
		}
		ptr->key[pos] = temp->key[1];
		//��Ҷ�ڵ��йؼ��ֺ�ָ����ǰ�ƶ���ɾ��key[1]
		for (int i = 1; i <temp->keynum; i++) {
			temp->key[i] = temp->key[i + 1];
		}
		temp->keynum--;
		ptr = temp;//ת��ΪҶ�ӽڵ�ɾ��
	}
	else{
		for (int i = 1; i < ptr->keynum; i++) {
			ptr->key[i] = ptr->key[i + 1];
		}
		ptr->keynum--;
	}
	//ɾ��Ҷ�ڵ�
	
	int d = (m + 1) / 2;
	while (1) {
		//���2��n = [m/2] - 1,��Ҫ���е���
		if (ptr->keynum < d - 1) {
			temp = ptr->parent;//�ҵ����׽ڵ�
			int j = 0;
			while (j <= temp->keynum&&temp->child[j]!=ptr) {//�ڸ��� �ڵ����ҵ�����λ��
				j++;
			}
			if (j == 0) {//�����ֵ����ϵ���
				RotateRight(ptr, temp, d, j);
			}
			else {//�����ֵ����ϵ���
				RotateLeft(ptr, temp, d, j);
			}
			ptr = temp;
			if(ptr ->parent == NULL) break;
		}
		else break;//���õ���
	}
	if (ptr->parent == NULL) {
		//ptr = ptr->parent->child[0];
		ptr->parent = NULL;
		root = ptr;
	}
	return true;
}