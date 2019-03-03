#include<iostream>  
#include<string>  
#include<vector>  
#include<map>  
#include<algorithm>  
#include<cmath>  
#include <Windows.h> 
#include <sstream>    //使用stringstream需要引入这个头文件 
using namespace std;

#define MAXLEN 10  //输入的每行数据的个数  

vector<vector<string> >state; //实例集  
vector<string>item(MAXLEN); //对应一行的实例  
vector<string> attribute_row;  //保存首行的属性名  
string yes("是");  //yes  
string no("否");   //  
string blank("");
map<string, vector<string> >map_attribute_values;  //存储属性所对应的所有的值   
int tree_size = 0;  //树的大小  

struct Node
{//决策树的节点   
	string attribute;  //属性值  
	string arrived_value;  //达到的属性值  
	vector<Node*>childs;  //所有的孩子  
	Node()
	{
		attribute = blank;  //初始化属性和到达的值为空   
		arrived_value = blank;  //到达的值为为空   
	}
};

Node *root;

void read(const string& featureFileName)
{
	//读取训练数据
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
		
			for (int k = 0; k < MAXLEN; k++)
			{
				char value[15] = "";//权值
				fscanf(fp, "%s",value);//读取文件数据保存到value里面
				//fgets(value,100,fp);
				item[k] = value ; //填充属性   
			}
			state.push_back(item);  //将填充好的条目放入state表中按行填充

			char c;
			fscanf(fp, "\n", &c);//读取换行符
							
			for (int j = 0; j<MAXLEN; j++)  //最大是6   
			{
				attribute_row.push_back(state[0][j]);  //填充属性数组
			}
			start = ftell(fp);
		}
		fclose(fp);
	}

//根据数据实例计算属性和值组成的map  
//得到：以每一个属性为键，它的若干不重复值为值的map表   
void ComputeMapFrom2DVector()
{
	unsigned int i, j, k;
	bool exited = false;  //用于判断是否存在  
	vector<string>values;
	for (i = 1; i<MAXLEN - 1; i++)  //对用中间的属性   
	{
		for (j = 1; j<state.size(); j++)   //列优先遍历每一列   
		{
			for (k = 0; k<values.size(); k++)  //遍历当前的values数组查看当前属性值是否存在   
				if (!values[k].compare(state[j][i]))  //如果当前属性值存在   
					exited = true;  //标注在数组中已经存在了   
			if (!exited)   //如果要是不存在   
			{
				values.push_back(state[j][i]);  //将这个属性存入数组中去   
			}
			exited = false;
		}

		map_attribute_values[state[0][i]] = values;  //建立属性和属性值的映射表  
		values.erase(values.begin(), values.end());  //清空数据   

	}
}

//在剩余的所有数据中判断是不是都是相同的标签   
bool AllTheSameLabel(vector<vector<string> >remain_state, string label)
{
	int count = 0;  //  
	for (unsigned int i = 0; i<remain_state.size(); i++)
	{ //遍历所有的条目   
		if (!remain_state[i][MAXLEN - 1].compare(label))  //统计和label标签相同的数量  
			count++;
	}
	if (count == remain_state.size() - 1)  //如果所有的数据都是相同的标签   
		return true;  //返回true   
	else
		return false;
}

//计算熵值------数据实例，属性，是否为父节点   
double ComputeEntropy(vector<vector<string> >remain_state, string attribute, string value, bool ifparent)
{
	vector<int>count(2, 0);
	unsigned int i, j;
	bool done_flag = false;  //哨兵值  
	for (j = 1; j<MAXLEN; j++)  //   
	{
		if (done_flag)break;
		if (!attribute_row[j].compare(attribute))
		{//找到这个属性   
			for (i = 1; i<remain_state.size(); i++)
			{//对于每一个实例   
				if ((!ifparent && !remain_state[i][j].compare(value)) || ifparent)
				{
					if (!remain_state[i][MAXLEN - 1].compare(yes))
					{//统计yes和no的数量   
						count[0]++;   //yes的数量   
					}
					else
						count[1]++;
				}
			}
			done_flag = true;   //处理完每一个属性值之后退出   
		}
	}

	if (count[0] == 0 || count[1] == 0) return 0;//全部都是正实例或者全部都是负实例  
												 //开始计算熵  
	double sum = count[0] + count[1];  //首先计算实例的数量  
	double entropy = -count[0] / sum*log(count[0] / sum) / log(2.0) - count[1] / sum*log(count[1] / sum) / log(2.0);
	return entropy;  //返回熵值   

}
int FindAttributeByName(string attri)
{
	for (int i = 0; i<MAXLEN; i++)
	{//遍历每一个属性   
		if (!state[0][i].compare(attri))
			return i;
	}
	cerr << "不能找到这个属性的编号" << endl;
	return 0;
}

//排序法
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

//连续数据离散化，求取连续数据的信息增益
double Computecon_data(vector<vector<string> >remain_state, string attribute)
{

	int attribute_num = FindAttributeByName(attribute);//找到对应属性的编号
	vector<double> attribute_type;//对应属性列
	vector<double> attribute_list;
	int j;
	//遍历获得该属性的列值
	for (j = 0; j < remain_state.size(); j++)
	{
		attribute_type.push_back(atof(remain_state[j][attribute_num].c_str()));
	}
	attribute_list = bubbleSort(attribute_type, attribute_type.size());//排序后的数据

	vector<double>attribute_Ta;
	for (j = 0; j < remain_state.size() - 1; j++)
	{
		double er = (attribute_list[j] + attribute_list[j + 1]) / 2;
		attribute_Ta.push_back(er);//求取中间值列表
	}

	//遍历获取属性值个数
	vector< vector<int> >count_point(attribute_Ta.size()), count_count0(attribute_Ta.size()), count_count1(attribute_Ta.size());
	for (int i = 0; i <attribute_Ta.size(); i++)
	{
		count_point[i].resize(2);//设置数组的大小2Xattribute_Ta.size()
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
				tempoint[0]++;//统计大于二分点的个数
				if (!remain_state[n][MAXLEN - 1].compare(yes))
				{//统计yes和no的数量   
					count0[0]++;   //yes的数量
				}
				else
					count0[1]++;
			}
			else {
				tempoint[1]++;//统计小于二分点的个数
				if (!remain_state[n][MAXLEN - 1].compare(yes))
				{//统计yes和no的数量   
					count1[0]++;   //yes的数量   
				}
				else
					count1[1]++;
			}
		}

		count_point[m][0] = tempoint[0];//记录大于二分点的个数
		count_point[m][1] = tempoint[1];//记录小于二分点的个数
		count_count0[m][0] = count0[0];//记录大于二分点时为yes的个数
		count_count0[m][1] = count0[1];//记录大于二分点时为no的个数
		count_count1[m][0] = count1[0];//记录小于二分点时为yes的个数
		count_count1[m][1] = count1[1];//记录小于二分点时为no的个数

	}

	double parent_entropy = ComputeEntropy(remain_state, attribute, blank, true);//父亲的熵

	//对于每一个属性,计算每一个属性占总实例的比例 
	vector<double> ratio;
	for (j = 0; j<attribute_Ta.size(); j++)
	{  //这里计算的是大于二分点的比例
		ratio.push_back((double)count_point[j][0] / (double)(remain_state.size()));
	}
	//计算信息熵
	double temp_entropy, children_entropy = 0;
	vector<double> entropy_0, entropy_1;
	for (j = 0; j < attribute_Ta.size(); j++)
	{
		double entropy0;
		if (count_count0[j][0] == 0 || count_count0[j][1] == 0)//全部都是正实例或者全部都是负实例
		{
			entropy0 = 0;
			entropy_0.push_back(entropy0);  //记录大于二分点的各个熵值   
		}
		else
		{
			double sum0 = count_count0[j][0] + count_count0[j][1];  //首先计算实例的数量  
			entropy0 = -count_count0[j][0] / sum0*log(count_count0[j][0] / sum0) / log(2.0) - count_count0[j][1] / sum0*log(count_count0[j][1] / sum0) / log(2.0);
			entropy_0.push_back(entropy0);  //记录大于二分点的各个熵值   
		}
		double entropy1;
		if (count_count1[j][0] == 0 || count_count1[j][1] == 0)//全部都是正实例或者全部都是负实例
		{
			entropy1 = 0;
			entropy_1.push_back(entropy1);  //记录小于二分点的各个熵值   
		}
		else
		{
			double sum1 = count_count1[j][0] + count_count1[j][1];  //首先计算实例的数量  
			entropy1 = -count_count1[j][0] / sum1*log(count_count1[j][0] / sum1) / log(2.0) - count_count1[j][1] / sum1*log(count_count1[j][1] / sum1) / log(2.0);
			entropy_1.push_back(entropy1);  //记录小于二分点的各个熵值 
		}
	}
	//计算信息增益
	vector<double>Gain;
	for (j = 0; j < attribute_Ta.size(); j++)
	{
		children_entropy = ratio[j] * entropy_0[j] + (1 - ratio[j])* entropy_1[j];
		double gain;
		gain = parent_entropy - children_entropy;
		Gain.push_back(gain);//记录每个二分点的信息增益
	}

	vector<double>Gain_list = bubbleSort(Gain, Gain.size());//排序后的数据

	cout << endl;
	double Gain_max = Gain_list[Gain.size() - 1];//获取最大信息增益
	cout << Gain_max;
	return Gain_max;
}

//计算一个属性的信息增益值   
double ComputeGain(vector<vector<string> >remain_state, string attribute)
{
	unsigned int j, k, m;
	double Gain;
	//计算熵值   
	double children_entropy = 0;  //孩子的熵  
	vector<string> values = map_attribute_values[attribute];  //获取这个属性的属性值列 

	vector<double> ratio;//
	vector<int> count_values;
	int tempint;  //  
	if (attribute.compare("密度") && attribute.compare("含糖率")) {
		double parent_entropy = ComputeEntropy(remain_state, attribute, blank, true);//父亲的熵

		for (m = 0; m < values.size(); m++)
		{//对于属性中的每一个值   
			tempint = 0;
			for (k = 1; k < MAXLEN - 1; k++)
			{//在属性表中找这个属性   
				if (!attribute_row[k].compare(attribute))
				{//如果找到这个属性   
					for (j = 1; j < remain_state.size(); j++)
					{
						if (!remain_state[j][k].compare(values[m]))
							tempint++;  //统计这个属性中每一个属性值的个数   
					}
				}
			}
			count_values.push_back(tempint);  //记录每一个属性值的个数   
		}
		for (j = 0; j < values.size(); j++)
		{//对于每一个属性,计算每一个属性占总实例的比例   
			ratio.push_back((double)count_values[j] / (double)(remain_state.size() - 1));
		}

		double temp_entropy;  //  
		for (j = 0; j < values.size(); j++)
		{//对于每一个属性值   
			temp_entropy = ComputeEntropy(remain_state, attribute, values[j], false); //计算每一个属性值的熵  
			children_entropy += ratio[j] * temp_entropy;
		}
	Gain = parent_entropy - children_entropy;
	}
	if (!attribute.compare("密度") || !attribute.compare("含糖率"))
		Gain = Computecon_data(remain_state, attribute);
	return Gain;  //返回信息增益值   

}

//通过属性在总表中找到这个属性的编号   


string MostCommonLabel(vector<vector<string> >remain_state)
{
	int p = 0, n = 0;
	for (unsigned i = 0; i<remain_state.size(); i++)
	{//对于该实例表   
		if (!remain_state[i][MAXLEN - 1].compare(yes))
			p++;   //找出输入yes标签的  
		else
			n++;
	}
	if (p >= n)  //返回类标签数量最多的   
		return yes;
	else
		return no;
}


//根节点，原始数据，属性列表 采用递归的思想来进行构建 
//remain_state为剩余待分类的样例  
//remian_attribute为剩余还没有考虑的属性  
//返回根结点指针
Node* BuildDecisionTreeDFS(Node *p, vector<vector<string> >remain_state, vector<string>remain_attribute)
{
	if (p == NULL)
		p = new Node();  //如果P指针要是为空的话就新建一个节点  
	if (AllTheSameLabel(remain_state, yes))  //如果所有的条目都是yes标签   
	{
		p->attribute = yes;  //那么属性设置为yes   
		return p;  //返回这个节点   
	}

	if (AllTheSameLabel(remain_state, no))  //如果所有的类标签都是no   
	{
		p->attribute = no;  //将所有的类标签置为no   
		return p;
	}

	if (remain_attribute.size() == 0)  //如果剩余的属性大小为0   
	{
		string label = MostCommonLabel(remain_state);  //统计出属性最多的一组   
		p->attribute = label;   //将这组的类标签作为该类的标签   
		return p;  //返回p   
	}

	double max_gain = 0, temp_gain;  //最大的信息增益，和临时信息增益变量  
	vector<string>::iterator max_it = remain_attribute.begin(); //数据的起始迭代器   
	vector<string>::iterator it1;

	for (it1 = remain_attribute.begin()+1; it1<remain_attribute.end()-1; it1++)
	{//遍历所有的属性  
		temp_gain = ComputeGain(remain_state, (*it1));  //计算每个属性的信息增益 
		cout << *it1 << endl;
		if (temp_gain>max_gain)  //获取最大的信息增益   
		{
			max_gain = temp_gain;  //获取最大的信息增益值   
			max_it = it1;  //获取拥有最大信息增益值的属性   
		}
	}

	//根据信息增益值最大的属性来进行样例的划分  
	//并且跟新样例集和属性集  
	vector<string>new_attribute;  //新的属性集   
	vector<vector<string> >new_state;  //新的样例集

	for (vector<string>::iterator it2 = remain_attribute.begin(); it2<remain_attribute.end(); it2++)
	{//对于原始属性集   
		if ((*it2).compare(*max_it))  //将除了拥有最大信息增益的属性加入新的属性表中   
			new_attribute.push_back(*it2);
	}
	
	//确定了最佳划分属性  
	p->attribute = *max_it;  //当前节点的属性值置为刚才获取的”最大“属性  
	vector<string>values = map_attribute_values[*max_it];  //获取这个属性的属性值  
	int attribute_num = FindAttributeByName(*max_it);  //找到这个属性的编号  
	new_state.push_back(attribute_row);  //构建新的数据表 ???

	for (vector<string>::iterator it3 = values.begin(); it3<values.end(); it3++)
	{//遍历最大属性表中的每一个值   
		for (unsigned int i = 1; i<remain_state.size(); i++)
		{//对于实例表中的每一个实例   
			if (!remain_state[i][attribute_num].compare(*it3))
			{//对于实例表中分割属性每一个值的每一个实例   
				new_state.push_back(remain_state[i]);
			}
		}

		//对于分割属性的每一个值  
		Node *new_node = new Node();  //新建一个节点  
		new_node->arrived_value = *it3;  //这是将要通往的属性值   
		if (new_state.size() == 0)
		{//如果当前属性值的实例表为空   
			new_node->attribute = MostCommonLabel(remain_state);
			//将类标签最多的给这个类最为类标签   
		}
		else
			BuildDecisionTreeDFS(new_node, new_state, new_attribute);
		//如果 都不是一个标签，并且大小还都不是0那么就再次划分  
		p->childs.push_back(new_node);
		//构建好之后将这个节点作为p的孩子节点   
		new_state.erase(new_state.begin() + 1, new_state.end());
		//将除了属性名之外的数据清空   

	}
	return p;
}

void PrintTree(Node *p, int depth) {
	for (int i = 0; i < depth; i++) cout << '\t';//按照树的深度先输出tab  
	if (!p->arrived_value.empty()) {
		cout << p->arrived_value << endl;
		for (int i = 0; i < depth + 1; i++) cout << '\t';//按照树的深度先输出tab  
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
	cout << endl << "测试数据" << endl;
	for (int i = 0; i<data.size(); i++)
	{
		for (int j = 0; j<data[i].size(); j++)
			cout << data[i][j] << " ";
		cout << endl;
	}
	cout << endl << "测试数据" << endl;
}
int main()
{
	cout << "从文件中读取数据集" << endl;
	//read("ID3_test.txt");  //从文件读取数据
	read("ID30_test.txt");
	vector<string>remain_attribute;  //主要的属性数组  
	for(int j=0;j<MAXLEN;j++)
		remain_attribute.push_back(state[0][j]);  //复制一份属性数组

	vector<vector<string> >remain_state;  //剩余的数据   
	
	for (unsigned int i = 1; i < state.size(); i++)  //遍历数据表的大小   
	{
		remain_state.push_back(state[i]);  //复制一份原始数据
	}
	cout << "显示原始数据集" << endl;
	Tdisplay(state);
	cout <<  endl;

	ComputeMapFrom2DVector();  //构建属性和值的映射表   
	root = BuildDecisionTreeDFS(root, remain_state, remain_attribute);  //构建决策树 

	cout << "the decision tree is :" << endl;
	PrintTree(root,0);
	FreeTree(root);
	cout << endl;
	cout << "tree_size:" << tree_size << endl;

	system("pause");					

	return 0;
}
