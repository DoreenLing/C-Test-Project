#pragma once
/*心型迷宫*/
//宏定义
#define M 25
#define N 25
#define DELAY 1
#define MAXSIZE 1638400  

int Rank[MAXSIZE];
int Parent[MAXSIZE];

enum {MASK=0,ROAD=1,BACK=2,INWALL=3,OUTWALL=4,EMPTYWALL=5}BlockType;
enum {EAST=7,SOUTH=8,WEST=9,NORTH=10,ROLL=6}direction;

//坐标结构体
struct offsettings {
	int col;
	int row;
	int dir;
};
//方向数组
int Move[4][2] = { { 0,1},{ 1,0 },{ 0,-1 },{ -1,0 } };

class Heart_Track {
public:
	Heart_Track() { 
	in.col =4; in.row = 2;
	start.col = 3; start.row =3;
	end.col = 15; end.row = 21; 
	}
	~Heart_Track() {;}
	void best_Simple();//简单的显示心
	void Simple();//中间花纹有变化
	void initHeart();//初始化心型
	void initMaze(int maze[M][N]);//生成迷宫
	void showBack(int maze[M][N]);
	void findPath(int maze[M][N]);//寻找路径
	void ClearMask(int x,int y);
	bool inMaze(int x,int y);//判断是否在区域中
	void gotoxy(int x ,int y);
	void hideCursor();
	void updateMaze(int maze[M][N]);
private:
		bool Area[M][N];//存储心型有值区域
		bool Mask[M][N];//用于显示效果
		bool Visit[M][N];//存储访问点
		offsettings in;//开始点
		offsettings end;//结束点
		offsettings start;//开始点
};

//并查集类 用于生成迷宫
class Disjoin_set {
public:
	void initSet();//初始化父节点
	int FindSet(int x);//寻找根节点
	void UnionSet(int root1, int root2);//合并不相交子树
	int Postolist(int x,int y);//将每个点标号
};
