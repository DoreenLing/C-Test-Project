#include"HuffmanTree.h"
#include<fstream>
#include<string>
#include <cassert>
#include<map>
#include<vector>
#include"stack"
class HuffmanCode:public HuffmanTree//继承Huffman树的类
{
public:
	HuffmanCode() { }//构造函数
	~HuffmanCode(){}//折构函数
	//生成哈夫曼编码
	void GenerateHuffmanCode(HuffmanNode *Tree);
	//打开需要统计的文件
	void OpenFile(string file);
	//记录文件中的对应字数
	int CountWord(char word);
	//统计字符出现的次数并放入数组中
	vector<int> CountWord();
	//将vector转化成数组
	int *vectortoArray(vector<int>word);
	int size;//数组的大小
private:
	stack<int> CurCode;//用于存储当前编码
	map<char, int> mapWord;//用于统计字符
	vector<int>word;//用于存储字符出现次数
};

//生成哈夫曼编码
/*由叶子节点向上遍历*/
void HuffmanCode::GenerateHuffmanCode(HuffmanNode *Tree)
{
	if (Tree == NULL)
		return;
	//如果当前节点的左右孩子都为空，那么当前节点为叶子节点
	if (Tree->left == NULL&&Tree->right == NULL) {
		HuffmanNode *Cur = new HuffmanNode;//当前节点
		Cur = Tree;
		HuffmanNode *CurParent = new HuffmanNode;//当前节点的父节点	
		HuffmanNode *CurF = new HuffmanNode;
		while (Cur->parent != NULL) {//从叶子节点到根遍历
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
			Cur = CurParent;//将父节点赋给当前节点
		}
		//输出，根据队列的先入先出特性
		cout << Tree->data << ": ";
		while (!CurCode.empty()) {
			cout << CurCode.top();
			CurCode.pop();//弹出第一个元素
		}
		cout << endl;
	}
	GenerateHuffmanCode(Tree->left);//递归调用
	GenerateHuffmanCode(Tree->right);
}
//读取文件内容
void HuffmanCode::OpenFile(string file)
{
	fstream Ofile;
	Ofile.open(file.data());//打开文件
	assert(Ofile.is_open());   //若失败,则输出错误消息,并终止程序运行 
	char c;	
	while (!Ofile.eof()) {
		Ofile >> c;
		CountWord(c);
	}

}
//记录字符出现次数
int HuffmanCode::CountWord(char word)
{
	map<char,int>::iterator myfind;
	myfind = mapWord.find(word);//查找键值为word的值
	if (myfind == mapWord.end()) {//如果没有找到就返回map的尾部迭代器
		mapWord[word] = 1;//如果没有找到就新建
	}
	else {
		int count = myfind->second;
		count++;//字符出现的次数增加1
		mapWord[word] = count;//插入
	}
	return 0;
}
//统计字符出现次数
vector<int> HuffmanCode::CountWord()
{
	map<char, int>::iterator iter;
	iter = mapWord.begin();
	while (iter != mapWord.end()) {
		cout << iter->first << " : " << iter->second << endl;
		word.push_back(iter->second);//存入字符到容器
		iter++;
	}
	return word;
}
//将vector转化成数组
int *HuffmanCode::vectortoArray(vector<int>word)
{
	size = word.size();
	int *Array = new int[size];
	for (int i = 0; i < size; i++)
		Array[i] = word[i];
	return Array;
}