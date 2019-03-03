
#include <vector>  
#include <list>  
#include <iostream>  
#include <Windows.h>  
#include "svm.h"

class ClassificationSVM
{
public:
	ClassificationSVM();
	~ClassificationSVM();
	void train(const std::string& modelFileName);
	void predict(const std::string& featureaFileName, const std::string& modelFileName);
	friend ostream& operator<<(ostream &out, svm_node* &temp);
	void setParam();
	void readTrainData(const std::string& featureFileName);
private:
	svm_parameter param;
	svm_problem prob;//all the data for train  
	std::list<svm_node*> dataList;//list of features of all the samples   
	std::list<double>  typeList;//list of type of all the samples   
	int sampleNum;
	//bool* judgeRight;  
};
ostream& operator<<(ostream &out, svm_node* &temp)
{
	return out << temp[0].index<<":"<<temp[0].value << " " << temp[1].index << ":" << temp[1].value;
}