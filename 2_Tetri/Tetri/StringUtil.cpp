#include "StringUtil.h"
#include <windows.h>

// �ַ���ת�������ַ���
const wchar_t* StringUtil::StringToWideStr(const char* info, wchar_t* buf,
	size_t size, long codepage)
{
	if (NULL == info || NULL == buf || size < sizeof(wchar_t))
	{
		return L"";
	}

	const size_t len = size / sizeof(wchar_t);

	//�ú���ӳ��һ���ַ�����һ�����ַ�(unicode)���ַ���
	int res = MultiByteToWideChar(codepage, 0, info, -1, buf, int(len));

	if (res == 0)
	{
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
		{
			buf[len - 1] = 0;
		}
		else
		{
			buf[0] = 0;
		}
	}

	return buf;
}

// ���ַ���ת�����ַ���
const char* StringUtil::WideStrToString(const wchar_t* info, char* buf,
	size_t size, long codepage)
{
	if (NULL == info || NULL == buf || size < sizeof(char))
	{
		return "";
	}

	int res = WideCharToMultiByte(codepage, 0, info, -1, buf, int(size),
		NULL, NULL);

	if (0 == res)
	{
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
		{
			buf[size - 1] = 0;
		}
		else
		{
			buf[0] = 0;
		}
	}

	return buf;
}
