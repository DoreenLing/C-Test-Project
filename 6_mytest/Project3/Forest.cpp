/*森林的建立以及应用*/
#include<iostream>
using namespace std;

struct	ForestNode {
	char data;
	ForestNode *firestchild, *nextsibling;
	ForestNode(char value, ForestNode *fc = NULL, ForestNode *ns = NULL) :data(value), firestchild(fc), nextsibling(ns) {}
};

class ForestLink {
public:
	ForestLink() { root = current = NULL; }
	ForestNode* creatForest(istream &in, ForestNode* &p);
	void Preorder(ForestNode* &p);
	void Postorder(ForestNode* &p);
	void Whithorder(ForestNode* &p);
	ForestNode* Firstchild(ForestNode* &p, char &ch);
	bool parent();
	void show();
private:
	ForestNode *root, *current;
};

/*先根次序遍历法建立树*/
ForestNode*ForestLink::creatForest(istream &in, ForestNode* &p)
{
	char ch;
	cout << "Input the element. If you want to stop it,please 'N': ";
	in >> ch;
	if (ch == 'N') p = NULL;
	else {
		p = new ForestNode(ch);
		if (p == NULL)
			cout << "false!!!"<<endl;
		cout << "Creat the first child" << endl;
		creatForest(in, p->firestchild);
		cout << "Creat the next sibling" << endl;
		creatForest(in, p->nextsibling);
	}
	return  p;
}
void ForestLink::Preorder(ForestNode* &p)
{
	if (p) {
		cout << p->data << "-->";
		Preorder(p->firestchild);
		Preorder(p->nextsibling);
	}
}

void ForestLink::Postorder(ForestNode* &p)
{
	if (p) {
		Preorder(p->firestchild);
		cout << p->data << "-->";
		Preorder(p->nextsibling);
	}
}
void ForestLink::Whithorder(ForestNode* &p)
{
	if (p) {
		cout << p->data << "-->";
		Whithorder(p->nextsibling);		
		Whithorder(p->firestchild);		
	}
}
ForestNode* ForestLink::Firstchild( ForestNode* &p,char &ch)
{
	int i = 0;
	if (p != NULL&&i==0) {
		if (p->data == ch) i=1;
		else for (p->firestchild; p != NULL; p = p->nextsibling) {
			if (p->data == ch) break;
		}
	}
	if (p != NULL&&p->firestchild != NULL) {
		p = p->firestchild; return p;
	}
	p = NULL; return p;
}
void mainxxb()
{
	ForestLink A;
	ForestNode *p;
	A.creatForest(cin, p);
	A.Preorder(p);
	cout << endl;
	A.Postorder(p);
	cout << endl;
	A.Whithorder(p);
	system("pause");
}