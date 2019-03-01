#include <Windows.h>
#include "Window.h"
#include "StringUtil.h"

#ifndef INVALID_RETURN_VOID
#define INVALID_RETURN_VOID(condition) if((condition)) {return;}
#endif

// 一些常量的定义
const DWORD CURSOR_SIZE = 25;
const SHORT SMALL_RECT_TOP = 0;
const SHORT SMALL_RECT_LEFT = 0;

/// \brief 初始化窗口
/// \param console 控制台引用
/// \param rect 位置信息
void Window::Init(Console& console, SMALL_RECT rect)
{
	// 检测位置信息是否合法
	INVALID_RETURN_VOID(rect.Left >= rect.Right
		&& rect.Top >= rect.Bottom
		&& rect.Left < 0
		&& rect.Right > console.m_coord.X
		&& rect.Top > console.m_coord.Y);

	m_pConsole = &console;
	m_rect = rect;
}

/// \brief 输出信息
/// \param str 要输出的字符串
/// \param coordinate 位置信息 x, y
/// \param color 颜色
/// \param len 字符串长度
void Window::Output(const char* str, COORD coordinate, WORD color, size_t len)
{
	// 先检测位置信息是否合法
	INVALID_RETURN_VOID(coordinate.X < 0
		|| coordinate.Y < 0
		|| coordinate.X >(m_rect.Right - m_rect.Left)
		|| coordinate.Y >(m_rect.Bottom - m_rect.Top));

	COORD coord = { m_rect.Left + coordinate.X, m_rect.Top + coordinate.Y };
	DWORD num = 0;
	WORD colorArray[2] = { color, color };

	// 字符串转换
	for (const char* p = str; len != 0 && *p != 0; --len, ++p, ++coord.X)
	{
		// 需要换行
		if (coord.X >= m_rect.Right)
		{
			coord.X = m_rect.Left + coordinate.X;
			++coord.Y;
			INVALID_RETURN_VOID(coord.Y >= m_rect.Bottom);
		}

		// 单字节字符
		if (*p > 0)
		{
			WriteConsoleOutputCharacterA(m_pConsole->m_hStdOutput, p, 1, coord, &num);
			INVALID_RETURN_VOID(num != 1);
			WriteConsoleOutputAttribute(m_pConsole->m_hStdOutput, colorArray, 1, coord, &num);
			INVALID_RETURN_VOID(num != 1);
		}
		// 双字节字符
		else
		{
			INVALID_RETURN_VOID(len < 2 || *(p + 1) == 0 || (coord.X + 1) >= m_rect.Right);
			WriteConsoleOutputCharacterA(m_pConsole->m_hStdOutput, p, 2, coord, &num);
			INVALID_RETURN_VOID(num != 2);
			WriteConsoleOutputAttribute(m_pConsole->m_hStdOutput, colorArray, 2, coord, &num);
			INVALID_RETURN_VOID(num != 2);

			--len;
			++p;
			++coord.X;
		}
	}
}
