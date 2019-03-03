#include <iostream>  
#include <opencv.hpp>  
#include <cxcore.hpp> 
#include "sampledatas.h"
using namespace cv;
using namespace std;

int main(void)
{
	cout << '\n' << "/********************************************/" << '\n';
	cout << "/****************LDA*******************/" << '\n';
	cout << "/********************************************/" << '\n';
	//�������ݼ�����
	Mat mat_0 = Mat(9, 2, CV_64FC1,ldadata.data30a0);//��һ������
	Mat mat_1 = Mat(8, 2, CV_64FC1, ldadata.data30a1);//�ڶ�������
	//Sw,Sb
	Mat colsMean(Mat mat);
	Mat SbMat(Mat mean_0, Mat mean_1);
	Mat SwMat(Mat mat, Mat mean);
	Mat Matw(Mat MatSb, Mat MatSw);
	Mat Sw,Maxw;
	Sw = SwMat(mat_0, colsMean(mat_0))+ SwMat(mat_1, colsMean(mat_1));
	Maxw = Matw(SbMat(colsMean(mat_0), colsMean(mat_1)), Sw);
	cout << "�������������" << Maxw << endl;
	//��ֵͶӰ
	Mat y_0,y_1;
	y_0 = Maxw*colsMean(mat_0);
	y_1 = Maxw*colsMean(mat_1);
	cout << "��һ���ֵͶӰ��" << y_0 << endl;
	cout << "�ڶ����ֵͶӰ��" << y_1 << endl;

	system("pause");
	return 0;

}
//���о�ֵ
Mat colsMean(Mat mat)
{
	Mat temp_col;
	Mat means;// = Mat(1, mat.cols, CV_64FC1);
	Scalar meana; 
	//����
	for (int i = 0; i < mat.cols; i++) {
		temp_col = mat.colRange(i, i + 1);
		meana = mean(temp_col);
		means.push_back(meana.val[0]);
	}
	return means;
}

//������ɢ�Ⱦ���(����ƽ��ֵ���� ���ݼ�����)
Mat SwMat(Mat mat, Mat mean)
{
	int i;
	Mat MatSw;//= Mat(mat.cols,mat.cols, CV_64FC1);
	Mat x_row;
	//�ڱ���ȡ��
	for (i = 0; i < mat.rows ; i++)
	{
		x_row = mat.rowRange(i, i + 1);
		MatSw = MatSw + (x_row - mean.t()).t()*(x_row - mean.t());
	}
	return MatSw;
}
//�����ɢ�Ⱦ���(����ƽ��ֵ���� ���ݼ�����)
Mat SbMat(Mat mean_0, Mat mean_1)
{
	Mat MatSb;
	MatSb = (mean_0 - mean_1)*(mean_0 - mean_1).t();
	return MatSb;
}
//���������ֵ��������()����ֵ����Ĭ��Ϊ�о���
Mat Matw(Mat MatSb,Mat MatSw)
{
	Mat  MyMat,eValuesMat, eVectorsMat,nMatSw;
	invert(MatSw,nMatSw);
	MyMat = nMatSw*MatSb;
	eigen(MyMat, eValuesMat, eVectorsMat);
	cout << "����ֵ�� " << eValuesMat << endl;
	cout << "���������� " << eVectorsMat << endl;
	//��ȡ�������ֵ(����ǰ����ɴ�С���е�)
	//eVectorsMat.rowRange(0,1);
	return eVectorsMat.rowRange(0, 1);
}
