//--------------------------------------------------------------------
// 文件名:        Tetris.h
// 内  容:        俄罗斯方块类
// 说  明:        
// 创建日期:        2016年9月6日
//--------------------------------------------------------------------

#pragma once
#include "Console.h"
#include "Window.h"
#include "GameDefine.h"

class Tetris
{
public:

	/// \brief 构造函数
	/// \param console 控制台
	/// \param coordinate 控制台的高和宽
	Tetris(Console& console, COORD coordinate);

	/// \brief 初始化游戏
	/// \param keys 按键
	/// \param keyDesc 按键描述
	/// \param frequency 声效频率
	/// \param duration 延续时间
	void Init(int keys[KeyNum], char keyDesc[KeyNum][5], DWORD frequency, DWORD duration);

	/// \brief 是否正在运行游戏
	bool IsRun();

	/// \brief 获取当前等级
	int GetLevel() const;

	/// \brief 方块下落
	bool Fall();

	/// \brief 消息处理
	/// \param key 按键
	/// \return 游戏结束返回false
	bool MessageProc(const Cmd cmd);

private:
	/// \brief 声效
	void VoiceBeep();

	/// \brief 绘制得分
	void DrawScoreLevel();

	/// \brief 绘制下一个将要出现的图形
	void DrawNext();

	/// \brief 绘制游戏结束界面
	void DrawGameOver();

	/// \brief 绘制颜色
	void Draw(WORD color);

	/// \brief 给定的是否可行
	bool IsFit(int x, int y, int c, int z);

	/// \brief 消除行
	void RemoveRow();

	/// \brief 旋转(逆时针)
	void MoveTrans();

	/// \brief 向左移动
	void MoveLeft();

	/// \brief 向右移动
	void MoveRight();

	/// \brief 向下移动
	/// \return 0: 游戏结束； -1:触底； 1:没有触底
	int MoveDown();

	/// \brief 下落到底
	bool FallToBottom();

private:
	char bg[GAME_HIGHT * GAME_WIDTH + 1];
	char bk[DIAMONDS_TYPES][DIAMONDS_TRANS][DIAMONDS_IFNO_ROW][DIAMONDS_IFNO_COL];

private:
	// 声效频率
	DWORD m_voiceFrequency;

	// 延续时间
	DWORD m_voiceDuration;    

	// 控制按键
	int m_keys[KeyNum];

	// 控制按键的描述
	char m_keyDesc[KeyNum][5];

	// 游戏是否结束
	bool m_gameover;

	// 游戏暂停
	bool m_pause;

	// 游戏声效开关
	bool m_voice;

	// 游戏得分
	int m_score;

	// 游戏速度
	int m_speed;

	// 游戏数据(实际方块的存放数据)
	char m_data[ROWS][COLS];

	// 下一个方块
	int m_next;

	// 位置(x, y)
	int m_x, m_y;

	// 当前方块
	int m_currentDiamonds;

	// 当前方向
	int m_currentDir;

	// 窗口
	Window win;

};

