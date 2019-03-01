#include "Tetris.h"
#include <time.h>
#include <stdio.h>

/// \brief 构造函数
/// \param console 控制台
/// \param coordinate 控制台的高和宽
Tetris::Tetris(Console & console, COORD coordinate)
{
	// 创建一个矩形
	SMALL_RECT rect = { coordinate.X, coordinate.Y, coordinate.X + GAME_WIDTH, coordinate.Y + GAME_HIGHT };

	// 初始化这个窗口
	win.Init(console, rect);

}

/// \brief 初始化游戏
/// \param keys 按键
/// \param keyDesc 按键描述
/// \param frequency 声效频率
/// \param duration 延续时间
void Tetris::Init(int keys[KeyNum], char keyDesc[KeyNum][5], DWORD frequency, DWORD duration)
{
	// 初始化游戏的数据
	memcpy(m_keys, keys, sizeof(m_keys));
	memcpy(m_keyDesc, keyDesc, sizeof(m_keyDesc));
	memcpy(bk, Diamonds, sizeof(bk));
	memcpy(bg, Background, sizeof(bg));

	m_voiceFrequency = frequency;
	m_voiceDuration = duration;
	m_gameover = false;
	m_pause = true;
	m_score = 0;
	m_speed = 0;

	// 方块数据部分置0
	memset(m_data, 0, sizeof(m_data));

	// 设置随机种子
	srand((unsigned)time(NULL));

	// 下一个方块
	m_next = rand() % DIAMONDS_TYPES;

	m_x = 4;
	m_y = 2;
	m_currentDiamonds = -1;
	m_currentDir = 0;

	COORD coord = { 0, 0 };

	win.Output(bg + 0, coord, COLOR_STILL, GAME_WIDTH);

	for (int i = 1; i < ROWS - 1; ++i)
	{
		coord = { 0, (SHORT)i };
		win.Output(bg + GAME_WIDTH * i + 0, coord, COLOR_STILL, 2);
		coord = { 2, (SHORT)i };
		win.Output(bg + GAME_WIDTH * i + 2, coord, COLOR_BLANK, 22);
		coord = { 24, (SHORT)i };
		win.Output(bg + GAME_WIDTH * i + 24, coord, COLOR_STILL, 14);
	}

	coord = { 0, 20 }; 
	win.Output(bg + GAME_WIDTH * 20, coord, COLOR_STILL, GAME_WIDTH);

	for (int j = 0; j < KeyNum; ++j)
	{
		coord = { 33, (SHORT)j + 7 };
		win.Output(m_keyDesc[j], coord, COLOR_STILL, 4);
	}

	// 绘制下一个将要出现的方块
	DrawNext();
}

/// \brief 是否正在运行游戏
bool Tetris::IsRun()
{
	return !m_gameover && !m_pause;
}

/// \brief 获取当前等级
int Tetris::GetLevel() const
{
	return m_speed;
}

/// \brief 方块下落
bool Tetris::Fall()
{
	return MessageProc(CMD_DOWN);
}

/// \brief 消息处理
/// \param key 按键
/// \return 游戏结束返回false
bool Tetris::MessageProc(const Cmd cmd)
{
	int const key = m_keys[cmd];
	// 游戏结束
	if (m_gameover)
	{
		// 游戏重新开始
		if (m_keys[GameBegin] == key)
		{
			Init(m_keys, m_keyDesc, m_voiceFrequency, m_voiceDuration);
			return true;
		}

		return false;
	}

	// 游戏暂停
	if (m_pause)
	{
		// 游戏重新开始
		if (m_keys[GameBegin] == key)
		{
			m_pause = false;
			if (m_currentDiamonds == -1)
			{
				m_currentDiamonds = m_next;
				m_next = rand() % DIAMONDS_TYPES;
				DrawNext();
			}
		}
		else if (m_keys[GameVoice] == key)
		{
			m_voice = !m_voice;
		}
		else
		{
			return true;
		}

		VoiceBeep();

		return true;
	}

	if (m_keys[GamePause] == key)        // 按下暂停键
	{
		m_pause = true;
	}
	else if (m_keys[GameVoice] == key)    // 按下声效键
	{
		m_voice = !m_voice;
	}
	else if (m_keys[Up] == key)            // 按下变形键
	{
		MoveTrans();
	}
	else if (m_keys[Left] == key)        // 按下方向左键
	{
		MoveLeft();
	}
	else if (m_keys[Right] == key)        // 按下方向右键
	{
		MoveRight();
	}
	else if (m_keys[Down] == key)        // 按下方向下键
	{
		if (0 == MoveDown())
		{
			return false;
		}
	}
	else if (m_keys[FallDown] == key)        // 按下方块直接落地键
	{
		if (!FallToBottom())
		{
			return false;
		}
	}

	return true;
}

/// \brief 声效
void Tetris::VoiceBeep()
{
	if (m_voice)
	{
		Beep(m_voiceFrequency, m_voiceDuration);
	}
}

/// \brief 绘制得分
void Tetris::DrawScoreLevel()
{
	char tmp[6];
	COORD coord = { 0, 0 };
	sprintf_s(tmp, "%05d", m_score);
	coord = { 31, 19 };
	win.Output(tmp, coord, COLOR_STILL, 5);
	sprintf_s(tmp, "%1d", m_speed);
	coord = { 28, 19 };
	win.Output(tmp, coord, COLOR_STILL, 1);
}

/// \brief 绘制下一个将要出现的图形
void Tetris::DrawNext()
{
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			COORD coord = { 28 + (SHORT)j * 2, 1 + (SHORT)i };
			char* tmp = bk[m_next][0][i][j] == 0 ? "　" : "■";
			win.Output(tmp, coord, COLOR_STILL, 2);
		}
	}
}

/// \brief 绘制游戏结束界面
void Tetris::DrawGameOver()
{
	COORD coord = { 28, 1 };
	win.Output("游戏结束", coord, COLOR_STILL);
	coord = { 28, 2 };
	win.Output(" ", coord, COLOR_STILL);
}

/// \brief 绘制颜色
void Tetris::Draw(WORD color)
{
	COORD coord = { 0, 0 };

	for (int i = 0; i < 4; ++i)
	{
		if (m_y + i < 0 || m_y + i >= ROWS - 2)
		{
			continue;
		}

		for (int j = 0; j < 4; ++j)
		{
			if (bk[m_currentDiamonds][m_currentDir][i][j] == 1)
			{
				coord = { SHORT(2 + m_x * 2 + j * 2), SHORT(1 + m_y + i) };
				win.Output("■", coord, color, 2);
			}
		}
	}
}

/// \brief 给定的是否可行
bool Tetris::IsFit(int x, int y, int c, int z)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (bk[c][z][i][j] == 1)
			{
				if (y + i < 0)
				{
					continue;
				}
				if (y + i >= (ROWS - 2) || x + j < 0 || x + j >= (COLS - 2) || m_data[y + i][x + j] == 1)
				{
					return false;
				}
			}
		}
	}

	return true;
}

/// \brief 消除行
void Tetris::RemoveRow()
{
	int lineCount = 0;
	COORD coord = { 0, 0 };
	for (int i = 0; i < (ROWS - 2); ++i)
	{
		if (0 == memcmp(m_data[i], FULL_LINE , (COLS - 2)))
		{
			++lineCount;
			for (int m = 0; m < (COLS - 2); ++m)
			{
				for (int n = i; n > 1; --n)
				{
					m_data[n][m] = m_data[n - 1][m];
					coord = { SHORT(2 + m * 2), SHORT(1 + n) };
					WORD color = m_data[n][m] == 1 ? COLOR_STILL : COLOR_BLANK;
					win.Output("■", coord, color, 2);
				}

				m_data[0][m] = 0;
				coord = { SHORT(2 + m * 2) , 1 };
				win.Output("■", coord, COLOR_BLANK, 2);
			}
		}
	}

	char data[ROWS - 2][COLS - 2] = { 0 };
	if (lineCount == 0)
	{
		return;
	}

	int score = 0;
	switch (lineCount)
	{
	case 1:
		score = ONE_ROW_SCORE;
		break;
	case 2:
		score = TWO_ROWS_SCORE;
		break;
	case 3:
		score = THREE_ROWS_SCORE;
		break;
	case 4:
		score = FOUR_ROWS_SCORE;
		break;
	}

	m_score += score;

	if (score > MAX_SCORE)
	{
		score = MAX_SCORE;
	}

	m_speed = score / SPEED_ADD_SCORE;

	DrawScoreLevel();
}

/// \brief 旋转(逆时针)
void Tetris::MoveTrans()
{
	if (IsFit(m_x, m_y, m_currentDiamonds, (m_currentDir + 1) % 4))
	{
		VoiceBeep();
		Draw(COLOR_BLANK);

		m_currentDir = (m_currentDir + 1) % 4;
		Draw(COLOR_MOVE);
	}
}

/// \brief 向左移动
void Tetris::MoveLeft()
{
	if (IsFit(m_x - 1, m_y, m_currentDiamonds, m_currentDir))
	{
		VoiceBeep();
		Draw(COLOR_BLANK);

		--m_x;
		Draw(COLOR_MOVE);
	}
}

/// \brief 向右移动
void Tetris::MoveRight()
{
	if (IsFit(m_x + 1, m_y, m_currentDiamonds, m_currentDir))
	{
		VoiceBeep();
		Draw(COLOR_BLANK);

		++m_x;
		Draw(COLOR_MOVE);
	}
}

/// \brief 向下移动
/// \return 0: 游戏结束； -1:触底； 1:没有触底
int Tetris::MoveDown()
{
	
	if (IsFit(m_x, m_y + 1, m_currentDiamonds, m_currentDir))
	{
		VoiceBeep();
		Draw(COLOR_BLANK);

		++m_y;
		Draw(COLOR_MOVE);

		return 1;
	}

	// 触底了
	if (m_y != -2)
	{
		Draw(COLOR_STILL);
		for (int i = 0; i < 4; ++i)
		{
			if (m_y + i < 0)
			{
				continue;
			}

			for (int j = 0; j < 4; ++j)
			{
				if (bk[m_currentDiamonds][m_currentDir][i][j] == 1)
				{
					m_data[m_y + i][m_x + j] = 1;
				}
			}

		}
		RemoveRow();

		m_x = 4;
		m_y = -2;
		m_currentDir = 0;
		m_currentDiamonds = m_next;

		m_next = rand() % DIAMONDS_TYPES;
		DrawNext();

		return -1;
	}

	// 游戏结束

	m_gameover = true;
	DrawGameOver();

	return 0;
}

/// \brief 下落到底
bool Tetris::FallToBottom()
{
	int r = MoveDown();
	while (r == 1)
	{
		r = MoveDown();
	}

	return r == -1;
}

