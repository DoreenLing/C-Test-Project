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
	//构造数据集矩阵
	Mat mat_0 = Mat(9, 2, CV_64FC1,ldadata.data30a0);//第一类样本
	Mat mat_1 = Mat(8, 2, CV_64FC1, ldadata.data30a1);//第二类样本
	//Sw,Sb
	Mat colsMean(Mat mat);
	Mat SbMat(Mat mean_0, Mat mean_1);
	Mat SwMat(Mat mat, Mat mean);
	Mat Matw(Mat MatSb, Mat MatSw);
	Mat Sw,Maxw;
	Sw = SwMat(mat_0, colsMean(mat_0))+ SwMat(mat_1, colsMean(mat_1));
	Maxw = Matw(SbMat(colsMean(mat_0), colsMean(mat_1)), Sw);
	cout << "最大特征向量：" << Maxw << endl;
	//均值投影
	Mat y_0,y_1;
	y_0 = Maxw*colsMean(mat_0);
	y_1 = Maxw*colsMean(mat_1);
	cout << "第一类均值投影：" << y_0 << endl;
	cout << "第二类均值投影：" << y_1 << endl;

	system("pause");
	return 0;

}
//求列均值
Mat colsMean(Mat mat)
{
	Mat temp_col;
	Mat means;// = Mat(1, mat.cols, CV_64FC1);
	Scalar meana; 
	//遍历
	for (int i = 0; i < mat.cols; i++) {
		temp_col = mat.colRange(i, i + 1);
		meana = mean(temp_col);
		means.push_back(meana.val[0]);
	}
	return means;
}

//求类内散度矩阵(输入平均值矩阵 数据集矩阵)
Mat SwMat(Mat mat, Mat mean)
{
	int i;
	Mat MatSw;//= Mat(mat.cols,mat.cols, CV_64FC1);
	Mat x_row;
	//第遍历取行
	for (i = 0; i < mat.rows ; i++)
	{
		x_row = mat.rowRange(i, i + 1);
		MatSw = MatSw + (x_row - mean.t()).t()*(x_row - mean.t());
	}
	return MatSw;
}
//求类间散度矩阵(输入平均值矩阵 数据集矩阵)
Mat SbMat(Mat mean_0, Mat mean_1)
{
	Mat MatSb;
	MatSb = (mean_0 - mean_1)*(mean_0 - mean_1).t();
	return MatSb;
}
//求最大特征值特征向量()特征值矩阵默认为列矩阵
Mat Matw(Mat MatSb,Mat MatSw)
{
	Mat  MyMat,eValuesMat, eVectorsMat,nMatSw;
	invert(MatSw,nMatSw);
	MyMat = nMatSw*MatSb;
	eigen(MyMat, eValuesMat, eVectorsMat);
	cout << "特征值： " << eValuesMat << endl;
	cout << "特征向量： " << eVectorsMat << endl;
	//求取最大特征值(输出是按照由大到小排列的)
	//eVectorsMat.rowRange(0,1);
	return eVectorsMat.rowRange(0, 1);
}
