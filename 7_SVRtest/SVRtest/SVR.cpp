
#include <vector>  
#include <list>  
#include <iostream>  
using namespace std;
#include <Windows.h>  
#include "SVR.h"

#define FEATUREDIM  2//特征维度

ClassificationSVM::ClassificationSVM()
{
	;
}

ClassificationSVM::~ClassificationSVM()
{
	;
}
void ClassificationSVM::setParam()
{
	param.svm_type = EPSILON_SVR;//SVM类型，
	param.kernel_type = RBF;//核函数类型  
	param.degree = 3;/* for poly */
	param.gamma =0.01;
	param.coef0 = 0;
	param.nu =1;
	param.cache_size = 40;
	param.C = 600;
	param.eps = 1e-5;
	param.p = 0.1;
	param.shrinking = 1;
	param.nr_weight = 1;
	param.weight = NULL;
	param.weight_label = NULL;
}

//读取训练数据
void ClassificationSVM::readTrainData(const string& featureFileName)
{
	FILE *fp = fopen(featureFileName.c_str(), "r");//读取文件
	if (fp == NULL)
	{
		cout << "open feature file error!" << endl;
		return;
	}

	fseek(fp, 0L, SEEK_END);//设置文件指针fp的位置.
	long end = ftell(fp);//用于得到文件位置指针当前位置相对于文件首的偏移字节数
	fseek(fp, 0L, SEEK_SET);
	long start = ftell(fp);
	//读取文件，直到文件末尾  
	while (start != end)
	{
		//FEATUREDIM是自定义变量，表示特征的维度  
		svm_node* features = new svm_node[FEATUREDIM + 1];//因为需要结束标记，因此申请空间时特征维度+1  
	   //读入一个训练样本（每个样本是一个长度86的序列，其中最后一个变量是该样本的归类）  
		for (int k = 0; k < FEATUREDIM; k++)
		{
			double value = 0;//权值
			fscanf(fp, "%lf", &value);//读取文件数据保存到value里面
			features[k].index = k + 1;//特征标号，从1开始  
			features[k].value = value;//特征值 
		}
		features[FEATUREDIM].index = -1;//结束标记 
		char c;
		fscanf(fp, "\n", &c);//读取换行符
		//negative sample type is 0  
		int type = 0;
		//positive sample type is 1  
		if (featureFileName == "PositiveFeatures.txt")
			type = 1;
		dataList.push_back(features);//每读取数据一个特征便将特征存入列表
		typeList.push_back(type);//标记
		sampleNum++;
		//显示训练数据
		cout << sampleNum <<" "<< features<< " " <<type<<endl;
		start = ftell(fp);
	}
	fclose(fp);
}

//训练数据
void ClassificationSVM::train(const string& modelFileName)
{
	cout << "reading positivie features..." << endl;
	readTrainData("PositiveFeatures.txt");
	cout << "reading negative features..." << endl;
	readTrainData("NegativeFeatures.txt");
	cout << "number of training samples : "<<sampleNum << endl;//训练数据量(正例和反例)
	prob.l = sampleNum;//number of training samples  
	prob.x = new svm_node *[prob.l];//features of all the training samples  
	prob.y = new double[prob.l];//type of all the training samples  
	int index = 0;
	//从头到尾依次读取
	while (!dataList.empty())
	{
		prob.x[index] = dataList.front();
		prob.y[index] = typeList.front();
		dataList.pop_front();
		typeList.pop_front();
		index++;//记录特征个数
		}
	prob.l = index;
	cout << "start training" << endl;
	svm_model *svmModel = svm_train(&prob, &param); //调用svm_train训练出model  

	cout << "save model" << endl;
	svm_save_model(modelFileName.c_str(), svmModel);//c_str()它返回当前字符串的首字符地址
	cout << "done!" << endl;
}

//预测
void ClassificationSVM::predict(const string& featureFileName, const string& modelFileName)
{
	std::vector<bool> judgeRight;
	svm_model *svmModel = svm_load_model(modelFileName.c_str());//载入之前训练好的model  
	FILE *fp;
	if ((fp = fopen(featureFileName.c_str(), "rt")) == NULL)
		return;

	fseek(fp, 0L, SEEK_END);
	long end = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	long start = ftell(fp);
	while (start != end)
	{
		svm_node* input = new svm_node[FEATUREDIM + 1];//读入每一个预测样本分别预测结果（也就是第FEATUREDIM + 1个数值） 
		for (int k = 0; k<FEATUREDIM; k++)
		{
			double value = 0;
			fscanf(fp, "%lf", &value);
			input[k].index = k + 1;
			input[k].value = value;
		}
		char c;
		fscanf(fp, "\n", &c);
		input[FEATUREDIM].index = -1;
		int predictValue = svm_predict(svmModel, input);//调用svm_predict进行预测 
		if (featureFileName == "positive_test.txt")
		{   
			if (predictValue == 1)
				judgeRight.push_back(false);
			else
				judgeRight.push_back(true);
		}
		else if (featureFileName == "negative_test.txt")
		{
			if (predictValue == 1)
				judgeRight.push_back(false);
			else
				judgeRight.push_back(true);
		}
		start = ftell(fp);
	}
	fclose(fp);

	int correctNum = 0;
	int totalNum = judgeRight.size();
	for (int i = 0; i < totalNum; i++)
	{
		if (judgeRight[i] == true)
			correctNum++;
	}
	double precent = 1.0 * correctNum / totalNum;
	cout <<" The current precent of test data : ";
	cout << precent*100<<"%"<< endl;
}

void main()
{
	ClassificationSVM p;
	p.setParam();
	p.train("modelFileName.txt");
	p.predict("positive_test.txt","modelFileName.txt");
	system("pause");
}