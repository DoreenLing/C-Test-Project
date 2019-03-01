
//--------------------------------------------------------------------
// 文件名:        Console.h
// 内  容:        控制台类
// 说  明:        控制台类的一些声明
// 创建日期:      2018年6月5日
//--------------------------------------------------------------------

#pragma once            // 保证该文件只被包含一次

#include <wchar.h>     //宽字符处理及输入/输出
#include <windows.h>    // 使用windows系统下的东西需要引入的头文件

class Console
{
	//友元类的所有成员函数都是另一个类的友元函数(包括私有成员和保护成员)。
	friend class Window; //声明window为console的友元类

public:

	/// \brief 初始化控制台
	/// \param caption 控制台标题
	/// \param coordinate 控制台的高和宽
	void Init(const char caption[25], COORD coordinate);

public:
	HANDLE m_hStdInput;            // 标准输入句柄

private:
	HANDLE m_hStdOutput;        // 标准输出句柄
	COORD  m_coord;                // 位置信息(x,y)

};

