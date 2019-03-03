#pragma once
/*�����Թ�*/
//�궨��
#define M 25
#define N 25
#define DELAY 1
#define MAXSIZE 1638400  

int Rank[MAXSIZE];
int Parent[MAXSIZE];

enum {MASK=0,ROAD=1,BACK=2,INWALL=3,OUTWALL=4,EMPTYWALL=5}BlockType;
enum {EAST=7,SOUTH=8,WEST=9,NORTH=10,ROLL=6}direction;

//����ṹ��
struct offsettings {
	int col;
	int row;
	int dir;
};
//��������
int Move[4][2] = { { 0,1},{ 1,0 },{ 0,-1 },{ -1,0 } };

class Heart_Track {
public:
	Heart_Track() { 
	in.col =4; in.row = 2;
	start.col = 3; start.row =3;
	end.col = 15; end.row = 21; 
	}
	~Heart_Track() {;}
	void best_Simple();//�򵥵���ʾ��
	void Simple();//�м仨���б仯
	void initHeart();//��ʼ������
	void initMaze(int maze[M][N]);//�����Թ�
	void showBack(int maze[M][N]);
	void findPath(int maze[M][N]);//Ѱ��·��
	void ClearMask(int x,int y);
	bool inMaze(int x,int y);//�ж��Ƿ���������
	void gotoxy(int x ,int y);
	void hideCursor();
	void updateMaze(int maze[M][N]);
private:
		bool Area[M][N];//�洢������ֵ����
		bool Mask[M][N];//������ʾЧ��
		bool Visit[M][N];//�洢���ʵ�
		offsettings in;//��ʼ��
		offsettings end;//������
		offsettings start;//��ʼ��
};

//���鼯�� ���������Թ�
class Disjoin_set {
public:
	void initSet();//��ʼ�����ڵ�
	int FindSet(int x);//Ѱ�Ҹ��ڵ�
	void UnionSet(int root1, int root2);//�ϲ����ཻ����
	int Postolist(int x,int y);//��ÿ������
};
