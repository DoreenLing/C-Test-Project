//--------------------------------------------------------------------
// �ļ���:        Window.h
// ��  ��:        ������
// ˵  ��:        ���ǿ���̨��һ���Ӳ���
// ��������:      2018��6��5��
//--------------------------------------------------------------------

#pragma once
#include "console.h"

class Window
{
public:
	/// \brief ��ʼ������
	/// \param console ����̨����
	/// \param rect λ����Ϣ
	void Init(Console& console, SMALL_RECT rect);

	/// \brief �����Ϣ
	/// \param str Ҫ������ַ���
	/// \param coordinate λ����Ϣ x, y
	/// \param color ��ɫ
	/// \param len �ַ�������
	void Output(const char* str, COORD coordinate, WORD color, size_t len = INT_MAX);

private:
	Console* m_pConsole;
	SMALL_RECT m_rect;
};

