#include "console.h"

#ifndef INVALID_RETURN_VOID
#define INVALID_RETURN_VOID(condition) if((condition)) {return;}
#endif

// 一些常量的定义
const DWORD CURSOR_SIZE = 25;
const SHORT SMALL_RECT_TOP = 0;
const SHORT SMALL_RECT_LEFT = 0;


/// \brief 打开控制台
/// \param caption 控制台标题
/// \param coordinate 控制台的高和宽
void Console::Init(const char caption[25], COORD coordinate)
{
	// 如果所给坐标不合法，则直接退出
	INVALID_RETURN_VOID(coordinate.X <= 0 || coordinate.Y <= 0);

	// 获得输出句柄
	m_hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	m_hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	// 判断得到的句柄是否合法
	INVALID_RETURN_VOID(INVALID_HANDLE_VALUE == m_hStdOutput);
	INVALID_RETURN_VOID(INVALID_HANDLE_VALUE == m_hStdInput);

	// 去除光标
	CONSOLE_CURSOR_INFO cci = { CURSOR_SIZE, false };
	SetConsoleCursorInfo(m_hStdOutput, &cci);

	// 设置窗体大小
	SMALL_RECT sr = { SMALL_RECT_TOP, SMALL_RECT_LEFT, coordinate.X - 1, coordinate.Y - 1 };
	SetConsoleWindowInfo(m_hStdOutput, true, &sr);

	// 设置缓冲区大小
	m_coord = coordinate;
	SetConsoleScreenBufferSize(m_hStdOutput, m_coord);

	// 设置窗口标题
	SetConsoleTitle(caption);
}
