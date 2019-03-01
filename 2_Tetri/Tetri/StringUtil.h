//--------------------------------------------------------------------
// �ļ���:        StringUtil.h
// ��  ��:        �ַ���������
// ˵  ��:        �ṩ�ַ���������һЩ��ݹ�����
// ��������:        2016��9��6��
// ������:        AceTan
// ��Ȩ����:        AceTan
//--------------------------------------------------------------------

#pragma once

#include <string>
#include <wchar.h>
#include <Windows.h>

// �ַ�������
class StringUtil
{
public:
	// �ַ���ת���ɿ��ַ���
	static const wchar_t* StringToWideStr(const char* info, wchar_t* buf,
		size_t size, long codepage = CP_UTF8);

	// ���ַ���ת�����ַ���
	static const char* WideStrToString(const wchar_t* info, char* buf,
		size_t size, long codepage = CP_UTF8);
};
