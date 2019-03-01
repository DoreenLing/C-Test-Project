//--------------------------------------------------------------------
// 文件名:        Window.h
// 内  容:        窗体类
// 说  明:        它是控制台的一个子部分
// 创建日期:      2018年6月5日
//--------------------------------------------------------------------

#pragma once
#include "console.h"

class Window
{
public:
	/// \brief 初始化窗口
	/// \param console 控制台引用
	/// \param rect 位置信息
	void Init(Console& console, SMALL_RECT rect);

	/// \brief 输出信息
	/// \param str 要输出的字符串
	/// \param coordinate 位置信息 x, y
	/// \param color 颜色
	/// \param len 字符串长度
	void Output(const char* str, COORD coordinate, WORD color, size_t len = INT_MAX);

private:
	Console* m_pConsole;
	SMALL_RECT m_rect;
};

