#include"HuffmanTree.h"
#include<fstream>
#include<string>
#include <cassert>
#include<map>
#include<vector>
#include"stack"
class HuffmanCode:public HuffmanTree//�̳�Huffman������
{
public:
	HuffmanCode() { }//���캯��
	~HuffmanCode(){}//�۹�����
	//���ɹ���������
	void GenerateHuffmanCode(HuffmanNode *Tree);
	//����Ҫͳ�Ƶ��ļ�
	void OpenFile(string file);
	//��¼�ļ��еĶ�Ӧ����
	int CountWord(char word);
	//ͳ���ַ����ֵĴ���������������
	vector<int> CountWord();
	//��vectorת��������
	int *vectortoArray(vector<int>word);
	int size;//����Ĵ�С
private:
	stack<int> CurCode;//���ڴ洢��ǰ����
	map<char, int> mapWord;//����ͳ���ַ�
	vector<int>word;//���ڴ洢�ַ����ִ���
};

//���ɹ���������
/*��Ҷ�ӽڵ����ϱ���*/
void HuffmanCode::GenerateHuffmanCode(HuffmanNode *Tree)
{
	if (Tree == NULL)
		return;
	//�����ǰ�ڵ�����Һ��Ӷ�Ϊ�գ���ô��ǰ�ڵ�ΪҶ�ӽڵ�
	if (Tree->left == NULL&&Tree->right == NULL) {
		HuffmanNode *Cur = new HuffmanNode;//��ǰ�ڵ�
		Cur = Tree;
		HuffmanNode *CurParent = new HuffmanNode;//��ǰ�ڵ�ĸ��ڵ�	
		HuffmanNode *CurF = new HuffmanNode;
		while (Cur->parent != NULL) {//��Ҷ�ӽڵ㵽������
			CurParent = Cur->parent;
			if (CurParent->left == Cur) {
				CurCode.push(0);
				CurF = CurParent->right;
			}
			else {
				CurCode.push(1);
				CurF = CurParent->left;
			}
			flag = 0;
			CurParent = FoundNode(CurF->data + Cur->data, root);
			Cur = CurParent;//�����ڵ㸳����ǰ�ڵ�
		}
		//��������ݶ��е������ȳ�����
		cout << Tree->data << ": ";
		while (!CurCode.empty()) {
			cout << CurCode.top();
			CurCode.pop();//������һ��Ԫ��
		}
		cout << endl;
	}
	GenerateHuffmanCode(Tree->left);//�ݹ����
	GenerateHuffmanCode(Tree->right);
}
//��ȡ�ļ�����
void HuffmanCode::OpenFile(string file)
{
	fstream Ofile;
	Ofile.open(file.data());//���ļ�
	assert(Ofile.is_open());   //��ʧ��,�����������Ϣ,����ֹ�������� 
	char c;	
	while (!Ofile.eof()) {
		Ofile >> c;
		CountWord(c);
	}

}
//��¼�ַ����ִ���
int HuffmanCode::CountWord(char word)
{
	map<char,int>::iterator myfind;
	myfind = mapWord.find(word);//���Ҽ�ֵΪword��ֵ
	if (myfind == mapWord.end()) {//���û���ҵ��ͷ���map��β��������
		mapWord[word] = 1;//���û���ҵ����½�
	}
	else {
		int count = myfind->second;
		count++;//�ַ����ֵĴ�������1
		mapWord[word] = count;//����
	}
	return 0;
}
//ͳ���ַ����ִ���
vector<int> HuffmanCode::CountWord()
{
	map<char, int>::iterator iter;
	iter = mapWord.begin();
	while (iter != mapWord.end()) {
		cout << iter->first << " : " << iter->second << endl;
		word.push_back(iter->second);//�����ַ�������
		iter++;
	}
	return word;
}
//��vectorת��������
int *HuffmanCode::vectortoArray(vector<int>word)
{
	size = word.size();
	int *Array = new int[size];
	for (int i = 0; i < size; i++)
		Array[i] = word[i];
	return Array;
}