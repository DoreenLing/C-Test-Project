/*�����������Ľ���*/
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;
struct BSTNode{
	int value;
	BSTNode *left, *right;
	//���캯������ʼ��
	BSTNode(int data, BSTNode* r = NULL, BSTNode* l = NULL):value(data),right(r),left(l) {}
};
class BSTline {
public:
	BSTline() :Root(NULL){}//���캯��
	~BSTline() { ; }//�۹�����
	BSTNode* Creat_BST(string path, BSTNode* &root);//������
	bool Insert(int &x,BSTNode* &ptr);//����ڵ�
	BSTNode* Search(int x,BSTNode* &ptr);//����
	bool Remove(int &x,BSTNode* &ptr);//ɾ���ڵ�
	void inBST(BSTNode* ptr);//���������������
	void writefile(BSTNode* &ptr);//д���ļ�
private:
	BSTNode *Root;//���ڵ�
	int Refvalue;//����ֹͣ��־
};

//����ڵ�
//����ptrΪ���ڵ�Ķ����������в���ڵ�x
bool BSTline::Insert(int &x, BSTNode* &ptr)
{
	if (ptr == NULL) {//���Ϊ��������ô���˽ڵ���Ϊ���ڵ�
		ptr = new BSTNode(x);//�����½ڵ�
		if (ptr == NULL)exit(1);
		return true;
	}
	else if (x < ptr->value) {
		Insert(x, ptr->left);//���������в���
	}
	else if (x > ptr->value)
		Insert(x,ptr->right);//���������в���
	else return false;
}

//��������������
BSTNode* BSTline::Creat_BST(string path,BSTNode* &root)
{
	//���ļ��ж�ȡҪ������������
	int x; string line;
	ifstream file(path, ifstream::in);
	while (getline(file, line)){//���ж�ȡ����
		stringstream lines(line);
		while (!lines.eof())//�ж��Ƿ������ȫ
		{
			lines >> x;
			Insert(x, root);
		}
	}
	Root = root;
	return root;
}

//����������������
BSTNode* BSTline::Search(int x, BSTNode* &ptr)
{
	//��ptrΪ���ڵ��ڶ���������������
	if (ptr == NULL)return NULL;
	else if (x < ptr->value)
		return Search(x, ptr->left);
	else if (x > ptr->value)
		return Search(x,ptr->right);
	else return ptr;//�����������Ľڵ�
}

//��������ɾ��
bool BSTline::Remove(int &x, BSTNode* &ptr)
{
	BSTNode* temp;//���ڴ洢�����ڵ�
	if (ptr != NULL)
		if (x < ptr->value) Remove(x,ptr->left);
		else if (x > ptr->value) Remove(x,ptr->right);
		else if (ptr->left != NULL&&ptr->right != NULL) {//������������Ϊ��������
			//����������ĵ�һ�������
			temp = ptr->right;
			while (temp->left != NULL)temp = temp->left;
			ptr->value = temp->value;//�����滻
			Remove(ptr->value, ptr->right);//����������
		}
		else {
			temp = ptr;//��Ѱ�ҵ��Ľڵ㸳ֵ��temp
			if (ptr->left == NULL)ptr = ptr->right;//������������һ����Ϊ��ʱ������һ���
			else ptr = ptr->left;
			delete temp;
			}
	return false;
}

//���������������
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

//�������������������������˳������ļ�
void BSTline::writefile(BSTNode* &ptr)
{
	//�����������Ŀ�����ļ�
	ofstream file("indata.txt",ios::app);//���ļ������ļ������ھʹ�����
	if (!file) return;//���ļ�ʧ�����������
	//file << " it my data "<<endl;//д�����
	//ofstream of("temp.txt", ios::app);
	file.close();
}

void main()
{
	string path = "data.txt";//��ȡ�ļ�·��
	BSTline bst; BSTNode *root=NULL;
	bst.Creat_BST(path,root);//����
	bst.inBST(root);//�������
	int x = 77;
	cout<<bst.Search(x, root)->value<<endl;
	int i = 11;
	bst.Remove(i,root);//ɾ��
	bst.inBST(root);//�������
	cout << endl;
	int j = 100;
	bst.Insert(j, root);
	bst.inBST(root);//�������
	system("pause");
}
