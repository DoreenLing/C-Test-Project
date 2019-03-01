
//--------------------------------------------------------------------
// �ļ���:        Console.h
// ��  ��:        ����̨��
// ˵  ��:        ����̨���һЩ����
// ��������:      2018��6��5��
//--------------------------------------------------------------------

#pragma once            // ��֤���ļ�ֻ������һ��

#include <wchar.h>     //���ַ���������/���
#include <windows.h>    // ʹ��windowsϵͳ�µĶ�����Ҫ�����ͷ�ļ�

class Console
{
	//��Ԫ������г�Ա����������һ�������Ԫ����(����˽�г�Ա�ͱ�����Ա)��
	friend class Window; //����windowΪconsole����Ԫ��

public:

	/// \brief ��ʼ������̨
	/// \param caption ����̨����
	/// \param coordinate ����̨�ĸߺͿ�
	void Init(const char caption[25], COORD coordinate);

public:
	HANDLE m_hStdInput;            // ��׼������

private:
	HANDLE m_hStdOutput;        // ��׼������
	COORD  m_coord;                // λ����Ϣ(x,y)

};

