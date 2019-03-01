#include"HuffmanCode.h"

#include<iostream>
using namespace std;


int main(int argc, char const *argv[])
{
	int a[7] = {1,2,3,4,9,6,7};
	MinHeap *heap = new MinHeap();
	HuffmanNode *myHeap = new HuffmanNode;
	HuffmanNode *myHeap1 = new HuffmanNode;
	HuffmanCode my;
	my.OpenFile("myFile.txt");
	//my.CountWord();
	int *b = new int;
	b = my.vectortoArray(my.CountWord());
	myHeap = my.CreatTree(b,my.size);//´´½¨HuffmanTree
	myHeap1 = my.FoundNode(13,myHeap);
	//my.inOrder(myHeap);
	my.GenerateHuffmanCode(myHeap);//huffmancode
	//my.preOrder(myHeap);
	//my.postOrder(myHeap);
	return 0;
}