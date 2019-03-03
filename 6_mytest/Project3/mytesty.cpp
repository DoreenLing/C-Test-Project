/*单链表实现多项式的加法*/
#include<iostream>
using namespace std;

struct PolyNode {
	int cofe;
	int exp;
	PolyNode *link;
	PolyNode(int m_data,int m_exp,PolyNode *next = NULL):cofe(m_data),exp(m_exp),link(next) {}//初始化
	PolyNode *InsertAfter(int c,int e);
};
class PolyLink {
public:
	PolyNode* creatPoly();
	void showPoly();
	PolyLink addPoly(PolyLink &A, PolyLink &B);
private:
	PolyNode *first;
	int m;
	int n;
};
PolyNode* PolyNode::InsertAfter(int c, int e)
{
	link = new PolyNode(c, e, link);
	return link;
}
PolyNode* PolyLink::creatPoly()
{
	int c, e; char N,Y; PolyNode*creat;
	cout << "Input cofe and exp (min)" << endl;
	cin >> c; cin >> e;
	first =new	PolyNode(c,e);
	creat = first;
	cout << "Are you want to create Ploy? 'Y' or 'N'" << endl;
	cin >> N;
	while (N != 'N') {
		cout << "Input cofe and exp,from small to big(the type is int)" << endl;
		cin >> c; cin >> e;
		creat = creat->InsertAfter( c, e);
		cout << "Are you want to stop it? 'Y' or 'N'" << endl;
		cin >> Y;
		if (Y == 'Y')
			return creat;
	}
	return creat;
}
void PolyLink::showPoly()
{
	PolyNode*current;
	current = first;
	cout << "Show the Ploy: " << endl;
	while (current != NULL&&current->link!=NULL) {
		cout << current->cofe<<"x" << "exp("<<current->exp<<")";
		cout << "+";
		current = current->link;
	}
	cout << current->cofe << "x" << "exp(" << current->exp << ")";
	cout << endl;
}
PolyLink  PolyLink::addPoly(PolyLink &A, PolyLink &B)
{
	PolyLink C;
	PolyNode *PA, *PB, *PC, *P;
	C.first = new PolyNode(0, 0);
	PC = C.first;
	A.creatPoly();
	B.creatPoly();
	PA = A.first;
	PB = B.first;
	int allcofe;
	while (PA != NULL&&PB != NULL) {
		if (PA->exp == PB->exp) {
			allcofe = PA->cofe + PA->cofe;
			PC = PC->InsertAfter(allcofe, PA->exp);
			PA = PA->link; PB = PB->link;
		}
		else if(PA->exp < PB->exp)
		{
			allcofe = PA->cofe;
			PC = PC->InsertAfter(allcofe,PA->exp);
			PA = PA->link;
		}
		else if (PA->exp >PB->exp)
		{
			allcofe = PB->cofe;
			PC = PC->InsertAfter(allcofe, PB->exp);
			PB = PB->link;
		}
	}
	if (PB != NULL) {
		PC = PC->InsertAfter(PB->cofe, PB->exp);
		PB = PB->link;
	}
	if (PA != NULL) {
		PC = PC->InsertAfter(PA->cofe, PA->exp);
		PA = PA->link;
	}
	return C;
}
void mainBB()
{
	PolyLink A,B,C;
	PolyNode *PC;
	C.addPoly(A, B).showPoly();
	A.showPoly();
	B.showPoly();
	system("pause");
}