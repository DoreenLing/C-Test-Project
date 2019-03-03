/*循环链表实现约瑟夫环*/
#include<iostream>
using namespace std;
struct CircNode {
	int data;
	CircNode *link;
	CircNode(int m_data) :data(m_data), link(NULL) {}//初始化
};
class CircLink {
public:
	void creatlink();
	void show();
	void outputlink();
private:
	CircNode *first;
	int m;
	int n;
};
void CircLink::creatlink()
{
	CircNode *ptr = NULL;
	CircNode *cur = NULL;
	CircNode *p = new CircNode(1);
	if (p == NULL)
		cout << "Memory allocade false!!!" << endl;
	first = p;
	cur = p;
	cout << "Input the number of node：";
	cin >>n;
	cout << endl;
	for (int i = 2; i <= n; i++) {
		p = new CircNode(i);
		ptr = cur;
		cur = p; 
		ptr->link = cur;
	}
	cur->link = first;
}

void CircLink::show()
{
	CircNode *ptr = first;
	cout << "Show the Node: " << endl;
	while (ptr->link != first)
	{ 
		cout << ptr->data << "->";
		ptr = ptr->link;
	}
	cout << ptr->data << endl;
}
void CircLink::outputlink()
{
	cout << "Input the value of delete:";
	cin >> m;
	cout << endl;
	CircNode *ptr = first,*p=NULL;
	for (int i = 1; i < n-1; i++) {
		for (int j = 1; j < m; j++) {
			p = ptr;
			ptr = ptr->link;
		}
		cout << "The people of out list is: " << ptr->data << endl;
		CircNode *del = ptr;
		ptr = ptr->link;
		p->link = ptr;
		delete del;
		del = NULL;
	}
	cout << "The people be outputed from the list is: " << ptr->data << endl;
}
void mainxx()
{
	CircLink josephous;
	josephous.creatlink();
	josephous.show();
	josephous.outputlink();
	system("pause");
	
}