#pragma once
#include<iostream>

#define DefaultSize 200;
template <class T>
class Binary_Heap {
public :
	Binary_Heap() { ; } //���캯��
	~Binary_Heap() { ; }//�۹�����
	void Creat_Min_Heap(T arr[],int size);//������С��
	bool Insert_Min_Heap(T &cur); //���뺯��
	void Destory_Min_Heap();//������С��
	T Get_Top_Min_Heap();//��ȡ�Ѷ�Ԫ��
	bool Pop_Top_Min_Heap();//ɾ���Ѷ�Ԫ��
	bool IsEmpty_Min();//�ж϶��Ƿ�Ϊ��
	bool IsFull_Min();//�ж��Ƿ����
public:
	void Creat_Max_Heap(T arr[], int size);//��������
	bool Insert_Max_Heap(T &cur); //���뺯��
	void Destory_Max_Heap();//������С��
	T Get_Top_Max_Heap();//��ȡ�Ѷ�Ԫ��
	bool Pop_Top_Max_Heap();//ɾ���Ѷ�Ԫ��
	bool IsEmpty_Max();//�ж϶��Ƿ�Ϊ��
	bool IsFull_Max();//�ж��Ƿ����

private:
	T *mHeap_min;//��Ŷ���Ԫ�ص�����
	int mCapacity_min;//��С�ѵ�������
	int mSize_min;//��С�ѵĵ�ǰ��Ч������
private:
	T *mHeap_max;//��Ŷ���Ԫ�ص�����
	int mCapacity_max;//��С�ѵ�������
	int mSize_max;//��С�ѵĵ�ǰ��Ч������
private:
	void FilterUp_Min(int start);//�ϵ��㷨
	void FilterDown_Min(int start,int end);//�µ��㷨
private:
	void FilterUp_Max(int start);//�ϵ��㷨
	void FilterDown_Max(int start, int end);//�µ��㷨
};

//function: ��С�Ѳ�����Ԫ��
//@para: cur �����Ԫ��
template<class T>
bool Binary_Heap<T>::Insert_Min_Heap(T &cur)
{
	if (!IsFull_Min()) {//�ж϶��Ƿ�����
		return false;
	}
	mHeap_min[mSize_min] = cur;
	FilterUp_Min(mSize_min);//���ϵ���Ϊ��С��
	mSize_min++;
	return true;
}

//function: ������С��
//@para: arr ��С������
//@para: size ��С�ѵ�ǰ��С
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
	mSize_min = size;// ��ǰ����Ч������
	int cur_pos = (mSize_min - 1)/2;
	while (cur_pos >= 0) {//�������µ���Ϊ��С��
		FilterDown_Min(cur_pos,mSize_min - 1);
		cur_pos--;
	}
}

//functiuon: ������С��
template<class T>
void Binary_Heap<T>::Destory_Min_Heap()
{
	mSize_min = 0;
	mCapacity_min = 0;
}

//function���õ��Ѷ�Ԫ��
template<class T>
T Binary_Heap<T>::Get_Top_Min_Heap()
{
	if(!IsEmpty_Min()){//�����Ϊ�գ�����
		exit(1);
	}
	return mHeap_min[0];
}

//function:��ɾ���Ѷ�Ԫ��
template<class T>
bool Binary_Heap<T>::Pop_Top_Min_Heap()
{
	if (!IsEmpty_Min()) {//�����Ϊ�գ�����
		exit(1);
	}
	mHeap_min[0] = mHeap_min[mSize_min - 1];//������Ԫ�ز��䵽�Ѷ�
	mSize_min--;
	FilterDown_Min(0,mSize_min - 1);//�������µ���
	return true;
}

//function: �ж϶Ѷ��Ƿ�Ϊ��
template<class T>
bool Binary_Heap<T>::IsEmpty_Min()
{
	if (mSize_min == 0) {
		return true;
	}
	return false;
}

//function: �ж϶��Ƿ���
template<class T>
bool Binary_Heap<T>::IsFull_Min()
{
	if (mSize_min == mCapacity_min) {
		return true;
	}
	return false;
}

//function: ���ϵ���Ϊ��С��
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

//function: ���µ���Ϊ��С��
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

//function: ���Ѳ�����Ԫ��
//@para: cur �����Ԫ��
template<class T>
bool Binary_Heap<T>::Insert_Max_Heap(T &cur)
{
	if (!IsFull_Max()) {//�ж϶��Ƿ�����
		return false;
	}
	mHeap_max[mSize_max] = cur;
	FilterUp_Max(mSize_max);//���ϵ���Ϊ����
	mSize_max++;
	return true;
}

//function: ��������
//@para: arr ��������
//@para: size ���ѵ�ǰ��С
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
	mSize_max = size;// ��ǰ����Ч������
	int cur_pos = (mSize_max - 1) / 2;
	while (cur_pos >= 0) {//�������µ���Ϊ����
		FilterDown_Max(cur_pos, mSize_max - 1);
		cur_pos--;
	}
}

//functiuon: ��������
template<class T>
void Binary_Heap<T>::Destory_Max_Heap()
{
	mSize_max = 0;
	mCapacity_max = 0;
}

//function���õ��Ѷ�Ԫ��
template<class T>
T Binary_Heap<T>::Get_Top_Max_Heap()
{
	if (!IsEmpty_Max()) {//�����Ϊ�գ�����
		exit(1);
	}
	return mHeap_max[0];
}

//function:��ɾ���Ѷ�Ԫ��
template<class T>
bool Binary_Heap<T>::Pop_Top_Max_Heap()
{
	if (!IsEmpty_Max()) {//�����Ϊ�գ�����
		exit(1);
	}
	mHeap_max[0] = mHeap_max[mSize_max - 1];//������Ԫ�ز��䵽�Ѷ�
	mSize_max--;
	FilterDown_Max(0, mSize_max - 1);//�������µ���
	return true;
}

//function: �ж϶Ѷ��Ƿ�Ϊ��
template<class T>
bool Binary_Heap<T>::IsEmpty_Max()
{
	if (mSize_max == 0) {
		return true;
	}
	return false;
}

//function: �ж϶��Ƿ���
template<class T>
bool Binary_Heap<T>::IsFull_Max()
{
	if (mSize_max == mCapacity_max) {
		return true;
	}
	return false;
}

//function: ���ϵ���Ϊ����
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

//function: ���µ���Ϊ����
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