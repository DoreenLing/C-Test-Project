#include <Windows.h>
#include "Window.h"
#include "StringUtil.h"

#ifndef INVALID_RETURN_VOID
#define INVALID_RETURN_VOID(condition) if((condition)) {return;}
#endif

// һЩ�����Ķ���
const DWORD CURSOR_SIZE = 25;
const SHORT SMALL_RECT_TOP = 0;
const SHORT SMALL_RECT_LEFT = 0;

/// \brief ��ʼ������
/// \param console ����̨����
/// \param rect λ����Ϣ
void Window::Init(Console& console, SMALL_RECT rect)
{
	// ���λ����Ϣ�Ƿ�Ϸ�
	INVALID_RETURN_VOID(rect.Left >= rect.Right
		&& rect.Top >= rect.Bottom
		&& rect.Left < 0
		&& rect.Right > console.m_coord.X
		&& rect.Top > console.m_coord.Y);

	m_pConsole = &console;
	m_rect = rect;
}

/// \brief �����Ϣ
/// \param str Ҫ������ַ���
/// \param coordinate λ����Ϣ x, y
/// \param color ��ɫ
/// \param len �ַ�������
void Window::Output(const char* str, COORD coordinate, WORD color, size_t len)
{
	// �ȼ��λ����Ϣ�Ƿ�Ϸ�
	INVALID_RETURN_VOID(coordinate.X < 0
		|| coordinate.Y < 0
		|| coordinate.X >(m_rect.Right - m_rect.Left)
		|| coordinate.Y >(m_rect.Bottom - m_rect.Top));

	COORD coord = { m_rect.Left + coordinate.X, m_rect.Top + coordinate.Y };
	DWORD num = 0;
	WORD colorArray[2] = { color, color };

	// �ַ���ת��
	for (const char* p = str; len != 0 && *p != 0; --len, ++p, ++coord.X)
	{
		// ��Ҫ����
		if (coord.X >= m_rect.Right)
		{
			coord.X = m_rect.Left + coordinate.X;
			++coord.Y;
			INVALID_RETURN_VOID(coord.Y >= m_rect.Bottom);
		}

		// ���ֽ��ַ�
		if (*p > 0)
		{
			WriteConsoleOutputCharacterA(m_pConsole->m_hStdOutput, p, 1, coord, &num);
			INVALID_RETURN_VOID(num != 1);
			WriteConsoleOutputAttribute(m_pConsole->m_hStdOutput, colorArray, 1, coord, &num);
			INVALID_RETURN_VOID(num != 1);
		}
		// ˫�ֽ��ַ�
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
