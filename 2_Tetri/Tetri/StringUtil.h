//--------------------------------------------------------------------
// 文件名:        StringUtil.h
// 内  容:        字符串工具类
// 说  明:        提供字符串操作的一些便捷工具类
// 创建日期:        2016年9月6日
// 创建人:        AceTan
// 版权所有:        AceTan
//--------------------------------------------------------------------

#pragma once

#include <string>
#include <wchar.h>
#include <Windows.h>

// 字符串处理
class StringUtil
{
public:
	// 字符串转换成宽字符串
	static const wchar_t* StringToWideStr(const char* info, wchar_t* buf,
		size_t size, long codepage = CP_UTF8);

	// 宽字符串转换成字符串
	static const char* WideStrToString(const wchar_t* info, char* buf,
		size_t size, long codepage = CP_UTF8);
};
