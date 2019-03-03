#pragma once
#include<iostream>

#define DefaultSize 200;
template <class T>
class Binary_Heap {
public :
	Binary_Heap() { ; } //构造函数
	~Binary_Heap() { ; }//折构函数
	void Creat_Min_Heap(T arr[],int size);//创建最小堆
	bool Insert_Min_Heap(T &cur); //插入函数
	void Destory_Min_Heap();//销毁最小堆
	T Get_Top_Min_Heap();//获取堆顶元素
	bool Pop_Top_Min_Heap();//删除堆顶元素
	bool IsEmpty_Min();//判断堆是否为空
	bool IsFull_Min();//判断是否堆满
public:
	void Creat_Max_Heap(T arr[], int size);//创建最大堆
	bool Insert_Max_Heap(T &cur); //插入函数
	void Destory_Max_Heap();//销毁最小堆
	T Get_Top_Max_Heap();//获取堆顶元素
	bool Pop_Top_Max_Heap();//删除堆顶元素
	bool IsEmpty_Max();//判断堆是否为空
	bool IsFull_Max();//判断是否堆满

private:
	T *mHeap_min;//存放堆中元素的数组
	int mCapacity_min;//最小堆的总容量
	int mSize_min;//最小堆的当前有效数据量
private:
	T *mHeap_max;//存放堆中元素的数组
	int mCapacity_max;//最小堆的总容量
	int mSize_max;//最小堆的当前有效数据量
private:
	void FilterUp_Min(int start);//上调算法
	void FilterDown_Min(int start,int end);//下调算法
private:
	void FilterUp_Max(int start);//上调算法
	void FilterDown_Max(int start, int end);//下调算法
};

//function: 最小堆插入新元素
//@para: cur 插入的元素
template<class T>
bool Binary_Heap<T>::Insert_Min_Heap(T &cur)
{
	if (!IsFull_Min()) {//判断堆是否已满
		return false;
	}
	mHeap_min[mSize_min] = cur;
	FilterUp_Min(mSize_min);//向上调整为最小堆
	mSize_min++;
	return true;
}

//function: 创建最小堆
//@para: arr 最小堆数组
//@para: size 最小堆当前大小
template<class T>
void Binary_Heap<T>::Creat_Min_Heap(T arr[], int size)
{
	mCapacity_min = (DefaultSize < size) ? size : DefaultSize;
	mHeap_min = new T[mCapacity_min];
	if (mHeap_min == NULL) {
		exit(1);
	}
	for (int i = 0; i < size; i++) {
		mHeap_min[i] = arr[i];
	}
	mSize_min = size;// 当前的有效数据量
	int cur_pos = (mSize_min - 1)/2;
	while (cur_pos >= 0) {//自上向下调整为最小堆
		FilterDown_Min(cur_pos,mSize_min - 1);
		cur_pos--;
	}
}

//functiuon: 销毁最小堆
template<class T>
void Binary_Heap<T>::Destory_Min_Heap()
{
	mSize_min = 0;
	mCapacity_min = 0;
}

//function：得到堆顶元素
template<class T>
T Binary_Heap<T>::Get_Top_Min_Heap()
{
	if(!IsEmpty_Min()){//如果堆为空，返回
		exit(1);
	}
	return mHeap_min[0];
}

//function:　删除堆顶元素
template<class T>
bool Binary_Heap<T>::Pop_Top_Min_Heap()
{
	if (!IsEmpty_Min()) {//如果堆为空，返回
		exit(1);
	}
	mHeap_min[0] = mHeap_min[mSize_min - 1];//将最后的元素补充到堆顶
	mSize_min--;
	FilterDown_Min(0,mSize_min - 1);//自上向下调整
	return true;
}

//function: 判断堆顶是否为空
template<class T>
bool Binary_Heap<T>::IsEmpty_Min()
{
	if (mSize_min == 0) {
		return true;
	}
	return false;
}

//function: 判断堆是否满
template<class T>
bool Binary_Heap<T>::IsFull_Min()
{
	if (mSize_min == mCapacity_min) {
		return true;
	}
	return false;
}

//function: 向上调整为最小堆
template<class T>
void Binary_Heap<T>::FilterUp_Min(int start)
{
	int j = start, i = (j - 1) / 2;
	T temp = mHeap_min[j];
	while (i > 0) {
		if (temp < mHeap_min[i]) {
			mHeap_min[j] = mHeap_min[i];
			j = i;
			i = (j-1)/2
		}
		else break;
	}
	mHeap_min[j] = temp;

}

//function: 向下调整为最小堆
template<class T>
void Binary_Heap<T>::FilterDown_Min(int start, int end)
{
	int j = start, i = 2 * j + 1;
	T temp = mHeap_min[j];
	while (i <= end)
	{
		if (i < end&&temp > mHeap_min[i + 1]) {
			i++;
		}
		if (temp > mHeap_min[i]) {
			mHeap_min[j] = mHeap_min[i];
			j = i;
			i = 2 * j + 1;
		}
		else break;
	}
	mHeap_min[j] = temp;
}

//function: 最大堆插入新元素
//@para: cur 插入的元素
template<class T>
bool Binary_Heap<T>::Insert_Max_Heap(T &cur)
{
	if (!IsFull_Max()) {//判断堆是否已满
		return false;
	}
	mHeap_max[mSize_max] = cur;
	FilterUp_Max(mSize_max);//向上调整为最大堆
	mSize_max++;
	return true;
}

//function: 创建最大堆
//@para: arr 最大堆数组
//@para: size 最大堆当前大小
template<class T>
void Binary_Heap<T>::Creat_Max_Heap(T arr[], int size)
{
	mCapacity_max = (DefaultSize < size) ? size : DefaultSize;
	mHeap_max = new T[mCapacity_max];
	if (mHeap_max == NULL) {
		exit(1);
	}
	for (int i = 0; i < size; i++) {
		mHeap_max[i] = arr[i];
	}
	mSize_max = size;// 当前的有效数据量
	int cur_pos = (mSize_max - 1) / 2;
	while (cur_pos >= 0) {//自上向下调整为最大堆
		FilterDown_Max(cur_pos, mSize_max - 1);
		cur_pos--;
	}
}

//functiuon: 销毁最大堆
template<class T>
void Binary_Heap<T>::Destory_Max_Heap()
{
	mSize_max = 0;
	mCapacity_max = 0;
}

//function：得到堆顶元素
template<class T>
T Binary_Heap<T>::Get_Top_Max_Heap()
{
	if (!IsEmpty_Max()) {//如果堆为空，返回
		exit(1);
	}
	return mHeap_max[0];
}

//function:　删除堆顶元素
template<class T>
bool Binary_Heap<T>::Pop_Top_Max_Heap()
{
	if (!IsEmpty_Max()) {//如果堆为空，返回
		exit(1);
	}
	mHeap_max[0] = mHeap_max[mSize_max - 1];//将最后的元素补充到堆顶
	mSize_max--;
	FilterDown_Max(0, mSize_max - 1);//自上向下调整
	return true;
}

//function: 判断堆顶是否为空
template<class T>
bool Binary_Heap<T>::IsEmpty_Max()
{
	if (mSize_max == 0) {
		return true;
	}
	return false;
}

//function: 判断堆是否满
template<class T>
bool Binary_Heap<T>::IsFull_Max()
{
	if (mSize_max == mCapacity_max) {
		return true;
	}
	return false;
}

//function: 向上调整为最大堆
template<class T>
void Binary_Heap<T>::FilterUp_Max(int start)
{
	int j = start, i = (j - 1) / 2;
	T temp = mHeap_max[j];
	while (i > 0) {
		if (temp > mHeap_max[i]) {
			mHeap_max[j] = mHeap_max[i];
			j = i;
			i = (j - 1) / 2
		}
		else break;
	}
	mHeap_max[j] = temp;

}

//function: 向下调整为最大堆
template<class T>
void Binary_Heap<T>::FilterDown_Max(int start, int end)
{
	int j = start, i = 2 * j + 1;
	T temp = mHeap_max[j];
	while (i <= end)
	{
		if (i < end&&temp < mHeap_max[i + 1]) {
			i++;
		}
		if (temp < mHeap_max[i]) {
			mHeap_max[j] = mHeap_max[i];
			j = i;
			i = 2 * j + 1;
		}
		else break;
	}
	mHeap_max[j] = temp;
}