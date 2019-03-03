#include<iostream>  
#include<string>  
#include<vector>  
#include<map>  
#include<algorithm>  
#include<cmath>  
#include <Windows.h> 
#include <sstream>    //ʹ��stringstream��Ҫ�������ͷ�ļ� 
using namespace std;

#define MAXLEN 10  //�����ÿ�����ݵĸ���  

vector<vector<string> >state; //ʵ����  
vector<string>item(MAXLEN); //��Ӧһ�е�ʵ��  
vector<string> attribute_row;  //�������е�������  
string yes("��");  //yes  
string no("��");   //  
string blank("");
map<string, vector<string> >map_attribute_values;  //�洢��������Ӧ�����е�ֵ   
int tree_size = 0;  //���Ĵ�С  

struct Node
{//�������Ľڵ�   
	string attribute;  //����ֵ  
	string arrived_value;  //�ﵽ������ֵ  
	vector<Node*>childs;  //���еĺ���  
	Node()
	{
		attribute = blank;  //��ʼ�����Ժ͵����ֵΪ��   
		arrived_value = blank;  //�����ֵΪΪ��   
	}
};

Node *root;

void read(const string& featureFileName)
{
	//��ȡѵ������
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
		
			for (int k = 0; k < MAXLEN; k++)
			{
				char value[15] = "";//Ȩֵ
				fscanf(fp, "%s",value);//��ȡ�ļ����ݱ��浽value����
				//fgets(value,100,fp);
				item[k] = value ; //�������   
			}
			state.push_back(item);  //�����õ���Ŀ����state���а������

			char c;
			fscanf(fp, "\n", &c);//��ȡ���з�
							
			for (int j = 0; j<MAXLEN; j++)  //�����6   
			{
				attribute_row.push_back(state[0][j]);  //�����������
			}
			start = ftell(fp);
		}
		fclose(fp);
	}

//��������ʵ���������Ժ�ֵ��ɵ�map  
//�õ�����ÿһ������Ϊ�����������ɲ��ظ�ֵΪֵ��map��   
void ComputeMapFrom2DVector()
{
	unsigned int i, j, k;
	bool exited = false;  //�����ж��Ƿ����  
	vector<string>values;
	for (i = 1; i<MAXLEN - 1; i++)  //�����м������   
	{
		for (j = 1; j<state.size(); j++)   //�����ȱ���ÿһ��   
		{
			for (k = 0; k<values.size(); k++)  //������ǰ��values����鿴��ǰ����ֵ�Ƿ����   
				if (!values[k].compare(state[j][i]))  //�����ǰ����ֵ����   
					exited = true;  //��ע���������Ѿ�������   
			if (!exited)   //���Ҫ�ǲ�����   
			{
				values.push_back(state[j][i]);  //��������Դ���������ȥ   
			}
			exited = false;
		}

		map_attribute_values[state[0][i]] = values;  //�������Ժ�����ֵ��ӳ���  
		values.erase(values.begin(), values.end());  //�������   

	}
}

//��ʣ��������������ж��ǲ��Ƕ�����ͬ�ı�ǩ   
bool AllTheSameLabel(vector<vector<string> >remain_state, string label)
{
	int count = 0;  //  
	for (unsigned int i = 0; i<remain_state.size(); i++)
	{ //�������е���Ŀ   
		if (!remain_state[i][MAXLEN - 1].compare(label))  //ͳ�ƺ�label��ǩ��ͬ������  
			count++;
	}
	if (count == remain_state.size() - 1)  //������е����ݶ�����ͬ�ı�ǩ   
		return true;  //����true   
	else
		return false;
}

//������ֵ------����ʵ�������ԣ��Ƿ�Ϊ���ڵ�   
double ComputeEntropy(vector<vector<string> >remain_state, string attribute, string value, bool ifparent)
{
	vector<int>count(2, 0);
	unsigned int i, j;
	bool done_flag = false;  //�ڱ�ֵ  
	for (j = 1; j<MAXLEN; j++)  //   
	{
		if (done_flag)break;
		if (!attribute_row[j].compare(attribute))
		{//�ҵ��������   
			for (i = 1; i<remain_state.size(); i++)
			{//����ÿһ��ʵ��   
				if ((!ifparent && !remain_state[i][j].compare(value)) || ifparent)
				{
					if (!remain_state[i][MAXLEN - 1].compare(yes))
					{//ͳ��yes��no������   
						count[0]++;   //yes������   
					}
					else
						count[1]++;
				}
			}
			done_flag = true;   //������ÿһ������ֵ֮���˳�   
		}
	}

	if (count[0] == 0 || count[1] == 0) return 0;//ȫ��������ʵ������ȫ�����Ǹ�ʵ��  
												 //��ʼ������  
	double sum = count[0] + count[1];  //���ȼ���ʵ��������  
	double entropy = -count[0] / sum*log(count[0] / sum) / log(2.0) - count[1] / sum*log(count[1] / sum) / log(2.0);
	return entropy;  //������ֵ   

}
int FindAttributeByName(string attri)
{
	for (int i = 0; i<MAXLEN; i++)
	{//����ÿһ������   
		if (!state[0][i].compare(attri))
			return i;
	}
	cerr << "�����ҵ�������Եı��" << endl;
	return 0;
}

//����
vector<double>  bubbleSort(vector<double> a, int size)
{
	double temp;
	for (int pass = 1; pass<size; pass++)
	{
		for (int k = 0; k<size - pass; k++)
			if (a[k]>a[k + 1])
			{
				temp = a[k];
				a[k] = a[k + 1];
				a[k + 1] = temp;
			}
	}
	return a;
}

//����������ɢ������ȡ�������ݵ���Ϣ����
double Computecon_data(vector<vector<string> >remain_state, string attribute)
{

	int attribute_num = FindAttributeByName(attribute);//�ҵ���Ӧ���Եı��
	vector<double> attribute_type;//��Ӧ������
	vector<double> attribute_list;
	int j;
	//������ø����Ե���ֵ
	for (j = 0; j < remain_state.size(); j++)
	{
		attribute_type.push_back(atof(remain_state[j][attribute_num].c_str()));
	}
	attribute_list = bubbleSort(attribute_type, attribute_type.size());//����������

	vector<double>attribute_Ta;
	for (j = 0; j < remain_state.size() - 1; j++)
	{
		double er = (attribute_list[j] + attribute_list[j + 1]) / 2;
		attribute_Ta.push_back(er);//��ȡ�м�ֵ�б�
	}

	//������ȡ����ֵ����
	vector< vector<int> >count_point(attribute_Ta.size()), count_count0(attribute_Ta.size()), count_count1(attribute_Ta.size());
	for (int i = 0; i <attribute_Ta.size(); i++)
	{
		count_point[i].resize(2);//��������Ĵ�С2Xattribute_Ta.size()
		count_count0[i].resize(2);
		count_count1[i].resize(2);
	}
	cout << count_count1.size() << endl;

	for (int m = 0; m <attribute_Ta.size(); m++)
	{
		vector<int>count0(2, 0), tempoint(2, 0), count1(2, 0);
		for (int n = 0; n < attribute_type.size(); n++)
		{
			if (attribute_Ta[m] < attribute_type[n])
			{
				tempoint[0]++;//ͳ�ƴ��ڶ��ֵ�ĸ���
				if (!remain_state[n][MAXLEN - 1].compare(yes))
				{//ͳ��yes��no������   
					count0[0]++;   //yes������
				}
				else
					count0[1]++;
			}
			else {
				tempoint[1]++;//ͳ��С�ڶ��ֵ�ĸ���
				if (!remain_state[n][MAXLEN - 1].compare(yes))
				{//ͳ��yes��no������   
					count1[0]++;   //yes������   
				}
				else
					count1[1]++;
			}
		}

		count_point[m][0] = tempoint[0];//��¼���ڶ��ֵ�ĸ���
		count_point[m][1] = tempoint[1];//��¼С�ڶ��ֵ�ĸ���
		count_count0[m][0] = count0[0];//��¼���ڶ��ֵ�ʱΪyes�ĸ���
		count_count0[m][1] = count0[1];//��¼���ڶ��ֵ�ʱΪno�ĸ���
		count_count1[m][0] = count1[0];//��¼С�ڶ��ֵ�ʱΪyes�ĸ���
		count_count1[m][1] = count1[1];//��¼С�ڶ��ֵ�ʱΪno�ĸ���

	}

	double parent_entropy = ComputeEntropy(remain_state, attribute, blank, true);//���׵���

	//����ÿһ������,����ÿһ������ռ��ʵ���ı��� 
	vector<double> ratio;
	for (j = 0; j<attribute_Ta.size(); j++)
	{  //���������Ǵ��ڶ��ֵ�ı���
		ratio.push_back((double)count_point[j][0] / (double)(remain_state.size()));
	}
	//������Ϣ��
	double temp_entropy, children_entropy = 0;
	vector<double> entropy_0, entropy_1;
	for (j = 0; j < attribute_Ta.size(); j++)
	{
		double entropy0;
		if (count_count0[j][0] == 0 || count_count0[j][1] == 0)//ȫ��������ʵ������ȫ�����Ǹ�ʵ��
		{
			entropy0 = 0;
			entropy_0.push_back(entropy0);  //��¼���ڶ��ֵ�ĸ�����ֵ   
		}
		else
		{
			double sum0 = count_count0[j][0] + count_count0[j][1];  //���ȼ���ʵ��������  
			entropy0 = -count_count0[j][0] / sum0*log(count_count0[j][0] / sum0) / log(2.0) - count_count0[j][1] / sum0*log(count_count0[j][1] / sum0) / log(2.0);
			entropy_0.push_back(entropy0);  //��¼���ڶ��ֵ�ĸ�����ֵ   
		}
		double entropy1;
		if (count_count1[j][0] == 0 || count_count1[j][1] == 0)//ȫ��������ʵ������ȫ�����Ǹ�ʵ��
		{
			entropy1 = 0;
			entropy_1.push_back(entropy1);  //��¼С�ڶ��ֵ�ĸ�����ֵ   
		}
		else
		{
			double sum1 = count_count1[j][0] + count_count1[j][1];  //���ȼ���ʵ��������  
			entropy1 = -count_count1[j][0] / sum1*log(count_count1[j][0] / sum1) / log(2.0) - count_count1[j][1] / sum1*log(count_count1[j][1] / sum1) / log(2.0);
			entropy_1.push_back(entropy1);  //��¼С�ڶ��ֵ�ĸ�����ֵ 
		}
	}
	//������Ϣ����
	vector<double>Gain;
	for (j = 0; j < attribute_Ta.size(); j++)
	{
		children_entropy = ratio[j] * entropy_0[j] + (1 - ratio[j])* entropy_1[j];
		double gain;
		gain = parent_entropy - children_entropy;
		Gain.push_back(gain);//��¼ÿ�����ֵ����Ϣ����
	}

	vector<double>Gain_list = bubbleSort(Gain, Gain.size());//����������

	cout << endl;
	double Gain_max = Gain_list[Gain.size() - 1];//��ȡ�����Ϣ����
	cout << Gain_max;
	return Gain_max;
}

//����һ�����Ե���Ϣ����ֵ   
double ComputeGain(vector<vector<string> >remain_state, string attribute)
{
	unsigned int j, k, m;
	double Gain;
	//������ֵ   
	double children_entropy = 0;  //���ӵ���  
	vector<string> values = map_attribute_values[attribute];  //��ȡ������Ե�����ֵ�� 

	vector<double> ratio;//
	vector<int> count_values;
	int tempint;  //  
	if (attribute.compare("�ܶ�") && attribute.compare("������")) {
		double parent_entropy = ComputeEntropy(remain_state, attribute, blank, true);//���׵���

		for (m = 0; m < values.size(); m++)
		{//���������е�ÿһ��ֵ   
			tempint = 0;
			for (k = 1; k < MAXLEN - 1; k++)
			{//�����Ա������������   
				if (!attribute_row[k].compare(attribute))
				{//����ҵ��������   
					for (j = 1; j < remain_state.size(); j++)
					{
						if (!remain_state[j][k].compare(values[m]))
							tempint++;  //ͳ�����������ÿһ������ֵ�ĸ���   
					}
				}
			}
			count_values.push_back(tempint);  //��¼ÿһ������ֵ�ĸ���   
		}
		for (j = 0; j < values.size(); j++)
		{//����ÿһ������,����ÿһ������ռ��ʵ���ı���   
			ratio.push_back((double)count_values[j] / (double)(remain_state.size() - 1));
		}

		double temp_entropy;  //  
		for (j = 0; j < values.size(); j++)
		{//����ÿһ������ֵ   
			temp_entropy = ComputeEntropy(remain_state, attribute, values[j], false); //����ÿһ������ֵ����  
			children_entropy += ratio[j] * temp_entropy;
		}
	Gain = parent_entropy - children_entropy;
	}
	if (!attribute.compare("�ܶ�") || !attribute.compare("������"))
		Gain = Computecon_data(remain_state, attribute);
	return Gain;  //������Ϣ����ֵ   

}

//ͨ���������ܱ����ҵ�������Եı��   


string MostCommonLabel(vector<vector<string> >remain_state)
{
	int p = 0, n = 0;
	for (unsigned i = 0; i<remain_state.size(); i++)
	{//���ڸ�ʵ����   
		if (!remain_state[i][MAXLEN - 1].compare(yes))
			p++;   //�ҳ�����yes��ǩ��  
		else
			n++;
	}
	if (p >= n)  //�������ǩ��������   
		return yes;
	else
		return no;
}


//���ڵ㣬ԭʼ���ݣ������б� ���õݹ��˼�������й��� 
//remain_stateΪʣ������������  
//remian_attributeΪʣ�໹û�п��ǵ�����  
//���ظ����ָ��
Node* BuildDecisionTreeDFS(Node *p, vector<vector<string> >remain_state, vector<string>remain_attribute)
{
	if (p == NULL)
		p = new Node();  //���Pָ��Ҫ��Ϊ�յĻ����½�һ���ڵ�  
	if (AllTheSameLabel(remain_state, yes))  //������е���Ŀ����yes��ǩ   
	{
		p->attribute = yes;  //��ô��������Ϊyes   
		return p;  //��������ڵ�   
	}

	if (AllTheSameLabel(remain_state, no))  //������е����ǩ����no   
	{
		p->attribute = no;  //�����е����ǩ��Ϊno   
		return p;
	}

	if (remain_attribute.size() == 0)  //���ʣ������Դ�СΪ0   
	{
		string label = MostCommonLabel(remain_state);  //ͳ�Ƴ���������һ��   
		p->attribute = label;   //����������ǩ��Ϊ����ı�ǩ   
		return p;  //����p   
	}

	double max_gain = 0, temp_gain;  //������Ϣ���棬����ʱ��Ϣ�������  
	vector<string>::iterator max_it = remain_attribute.begin(); //���ݵ���ʼ������   
	vector<string>::iterator it1;

	for (it1 = remain_attribute.begin()+1; it1<remain_attribute.end()-1; it1++)
	{//�������е�����  
		temp_gain = ComputeGain(remain_state, (*it1));  //����ÿ�����Ե���Ϣ���� 
		cout << *it1 << endl;
		if (temp_gain>max_gain)  //��ȡ������Ϣ����   
		{
			max_gain = temp_gain;  //��ȡ������Ϣ����ֵ   
			max_it = it1;  //��ȡӵ�������Ϣ����ֵ������   
		}
	}

	//������Ϣ����ֵ�������������������Ļ���  
	//���Ҹ��������������Լ�  
	vector<string>new_attribute;  //�µ����Լ�   
	vector<vector<string> >new_state;  //�µ�������

	for (vector<string>::iterator it2 = remain_attribute.begin(); it2<remain_attribute.end(); it2++)
	{//����ԭʼ���Լ�   
		if ((*it2).compare(*max_it))  //������ӵ�������Ϣ��������Լ����µ����Ա���   
			new_attribute.push_back(*it2);
	}
	
	//ȷ������ѻ�������  
	p->attribute = *max_it;  //��ǰ�ڵ������ֵ��Ϊ�ղŻ�ȡ�ġ��������  
	vector<string>values = map_attribute_values[*max_it];  //��ȡ������Ե�����ֵ  
	int attribute_num = FindAttributeByName(*max_it);  //�ҵ�������Եı��  
	new_state.push_back(attribute_row);  //�����µ����ݱ� ???

	for (vector<string>::iterator it3 = values.begin(); it3<values.end(); it3++)
	{//����������Ա��е�ÿһ��ֵ   
		for (unsigned int i = 1; i<remain_state.size(); i++)
		{//����ʵ�����е�ÿһ��ʵ��   
			if (!remain_state[i][attribute_num].compare(*it3))
			{//����ʵ�����зָ�����ÿһ��ֵ��ÿһ��ʵ��   
				new_state.push_back(remain_state[i]);
			}
		}

		//���ڷָ����Ե�ÿһ��ֵ  
		Node *new_node = new Node();  //�½�һ���ڵ�  
		new_node->arrived_value = *it3;  //���ǽ�Ҫͨ��������ֵ   
		if (new_state.size() == 0)
		{//�����ǰ����ֵ��ʵ����Ϊ��   
			new_node->attribute = MostCommonLabel(remain_state);
			//�����ǩ���ĸ��������Ϊ���ǩ   
		}
		else
			BuildDecisionTreeDFS(new_node, new_state, new_attribute);
		//��� ������һ����ǩ�����Ҵ�С��������0��ô���ٴλ���  
		p->childs.push_back(new_node);
		//������֮������ڵ���Ϊp�ĺ��ӽڵ�   
		new_state.erase(new_state.begin() + 1, new_state.end());
		//������������֮����������   

	}
	return p;
}

void PrintTree(Node *p, int depth) {
	for (int i = 0; i < depth; i++) cout << '\t';//����������������tab  
	if (!p->arrived_value.empty()) {
		cout << p->arrived_value << endl;
		for (int i = 0; i < depth + 1; i++) cout << '\t';//����������������tab  
	}
	cout << p->attribute << endl;
	for (vector<Node*>::iterator it = p->childs.begin(); it != p->childs.end(); it++) {
		PrintTree(*it, depth + 1);
	}
}

void FreeTree(Node *p) {
	if (p == NULL)
		return;
	for (vector<Node*>::iterator it = p->childs.begin(); it != p->childs.end(); it++) {
		FreeTree(*it);
	}
	delete p;
	tree_size++;
}

void Tdisplay(vector<vector<string> >data)
{
	cout << endl << "��������" << endl;
	for (int i = 0; i<data.size(); i++)
	{
		for (int j = 0; j<data[i].size(); j++)
			cout << data[i][j] << " ";
		cout << endl;
	}
	cout << endl << "��������" << endl;
}
int main()
{
	cout << "���ļ��ж�ȡ���ݼ�" << endl;
	//read("ID3_test.txt");  //���ļ���ȡ����
	read("ID30_test.txt");
	vector<string>remain_attribute;  //��Ҫ����������  
	for(int j=0;j<MAXLEN;j++)
		remain_attribute.push_back(state[0][j]);  //����һ����������

	vector<vector<string> >remain_state;  //ʣ�������   
	
	for (unsigned int i = 1; i < state.size(); i++)  //�������ݱ�Ĵ�С   
	{
		remain_state.push_back(state[i]);  //����һ��ԭʼ����
	}
	cout << "��ʾԭʼ���ݼ�" << endl;
	Tdisplay(state);
	cout <<  endl;

	ComputeMapFrom2DVector();  //�������Ժ�ֵ��ӳ���   
	root = BuildDecisionTreeDFS(root, remain_state, remain_attribute);  //���������� 

	cout << "the decision tree is :" << endl;
	PrintTree(root,0);
	FreeTree(root);
	cout << endl;
	cout << "tree_size:" << tree_size << endl;

	system("pause");					

	return 0;
}
