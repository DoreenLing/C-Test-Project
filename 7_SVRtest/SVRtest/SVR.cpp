
#include <vector>  
#include <list>  
#include <iostream>  
using namespace std;
#include <Windows.h>  
#include "SVR.h"

#define FEATUREDIM  2//����ά��

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
	param.svm_type = EPSILON_SVR;//SVM���ͣ�
	param.kernel_type = RBF;//�˺�������  
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

//��ȡѵ������
void ClassificationSVM::readTrainData(const string& featureFileName)
{
	FILE *fp = fopen(featureFileName.c_str(), "r");//��ȡ�ļ�
	if (fp == NULL)
	{
		cout << "open feature file error!" << endl;
		return;
	}

	fseek(fp, 0L, SEEK_END);//�����ļ�ָ��fp��λ��.
	long end = ftell(fp);//���ڵõ��ļ�λ��ָ�뵱ǰλ��������ļ��׵�ƫ���ֽ���
	fseek(fp, 0L, SEEK_SET);
	long start = ftell(fp);
	//��ȡ�ļ���ֱ���ļ�ĩβ  
	while (start != end)
	{
		//FEATUREDIM���Զ����������ʾ������ά��  
		svm_node* features = new svm_node[FEATUREDIM + 1];//��Ϊ��Ҫ������ǣ��������ռ�ʱ����ά��+1  
	   //����һ��ѵ��������ÿ��������һ������86�����У��������һ�������Ǹ������Ĺ��ࣩ  
		for (int k = 0; k < FEATUREDIM; k++)
		{
			double value = 0;//Ȩֵ
			fscanf(fp, "%lf", &value);//��ȡ�ļ����ݱ��浽value����
			features[k].index = k + 1;//������ţ���1��ʼ  
			features[k].value = value;//����ֵ 
		}
		features[FEATUREDIM].index = -1;//������� 
		char c;
		fscanf(fp, "\n", &c);//��ȡ���з�
		//negative sample type is 0  
		int type = 0;
		//positive sample type is 1  
		if (featureFileName == "PositiveFeatures.txt")
			type = 1;
		dataList.push_back(features);//ÿ��ȡ����һ�������㽫���������б�
		typeList.push_back(type);//���
		sampleNum++;
		//��ʾѵ������
		cout << sampleNum <<" "<< features<< " " <<type<<endl;
		start = ftell(fp);
	}
	fclose(fp);
}

//ѵ������
void ClassificationSVM::train(const string& modelFileName)
{
	cout << "reading positivie features..." << endl;
	readTrainData("PositiveFeatures.txt");
	cout << "reading negative features..." << endl;
	readTrainData("NegativeFeatures.txt");
	cout << "number of training samples : "<<sampleNum << endl;//ѵ��������(�����ͷ���)
	prob.l = sampleNum;//number of training samples  
	prob.x = new svm_node *[prob.l];//features of all the training samples  
	prob.y = new double[prob.l];//type of all the training samples  
	int index = 0;
	//��ͷ��β���ζ�ȡ
	while (!dataList.empty())
	{
		prob.x[index] = dataList.front();
		prob.y[index] = typeList.front();
		dataList.pop_front();
		typeList.pop_front();
		index++;//��¼��������
		}
	prob.l = index;
	cout << "start training" << endl;
	svm_model *svmModel = svm_train(&prob, &param); //����svm_trainѵ����model  

	cout << "save model" << endl;
	svm_save_model(modelFileName.c_str(), svmModel);//c_str()�����ص�ǰ�ַ��������ַ���ַ
	cout << "done!" << endl;
}

//Ԥ��
void ClassificationSVM::predict(const string& featureFileName, const string& modelFileName)
{
	std::vector<bool> judgeRight;
	svm_model *svmModel = svm_load_model(modelFileName.c_str());//����֮ǰѵ���õ�model  
	FILE *fp;
	if ((fp = fopen(featureFileName.c_str(), "rt")) == NULL)
		return;

	fseek(fp, 0L, SEEK_END);
	long end = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	long start = ftell(fp);
	while (start != end)
	{
		svm_node* input = new svm_node[FEATUREDIM + 1];//����ÿһ��Ԥ�������ֱ�Ԥ������Ҳ���ǵ�FEATUREDIM + 1����ֵ�� 
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
		int predictValue = svm_predict(svmModel, input);//����svm_predict����Ԥ�� 
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