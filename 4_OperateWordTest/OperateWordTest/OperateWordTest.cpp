// OperateWordTest.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
//HINSTANCE?hinstLib;
//#include<iostream>
#include"MyWord.h"
//#include "My_Word_DLL.h"
//#pragma comment(lib,"H:\\VS2015PROJECT\\TCP\\OperateWordTest\\My_Word_DLL.lib");

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;
int main()
{
    int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(nullptr);
	if (hModule != nullptr)
	{
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
		{
			// TODO: ���Ĵ�������Է���������Ҫ
			wprintf(L"����: MFC ��ʼ��ʧ��\n");
			nRetCode = 1;
		}
		else
		{
			//��word�ĵ�
			MyWord myword;
			CString FileName = _T("H:\\VS2015PROJECT\\TCP\\OperateWordTest\\test1.docx");
			BOOL ReadOnly = FALSE;
			BOOL  AddToRecentFiles = FALSE;
			myword.InitMyWordCOM();
			myword.OpenMyWordDoc(FileName, ReadOnly,AddToRecentFiles);//���ĵ�
			CString Text = _T("Hi i'm new word,can we make a friend");
			myword.WriteWordDoc(Text);//�����µ�����
			CString My;
			myword.GetWordText(My);
			cout << My.GetLength();
			myword.WriteWordDoc(My);
			CString My1;
			myword.GetWordText(My);
			myword.CloseWordDoc(FALSE);


		//	CMy_Word_DLL MY_WORD;
		//	MY_WORD.InitMyWordCOM();
		//	
		////	MY_WORD.OpenMyWordDoc(FileName, ReadOnly, AddToRecentFiles);//���ĵ�
		//	CString Text = _T("Hi i'm new word,can we make a friend");
		//	MY_WORD.WriteWordDoc(Text);//�����µ�����
		//	CString My;
		//	MY_WORD.GetWordText(My);
		//	MY_WORD.CloseWordDoc(FALSE);
		}
  	}
    else
    {
        // TODO: ���Ĵ�������Է���������Ҫ
        wprintf(L"����: GetModuleHandle ʧ��\n");
        nRetCode = 1;
    }


    return nRetCode;
}
