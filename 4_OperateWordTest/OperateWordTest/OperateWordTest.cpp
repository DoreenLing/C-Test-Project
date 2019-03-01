// OperateWordTest.cpp : 定义控制台应用程序的入口点。
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


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;
int main()
{
    int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(nullptr);
	if (hModule != nullptr)
	{
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
		{
			// TODO: 更改错误代码以符合您的需要
			wprintf(L"错误: MFC 初始化失败\n");
			nRetCode = 1;
		}
		else
		{
			//打开word文档
			MyWord myword;
			CString FileName = _T("H:\\VS2015PROJECT\\TCP\\OperateWordTest\\test1.docx");
			BOOL ReadOnly = FALSE;
			BOOL  AddToRecentFiles = FALSE;
			myword.InitMyWordCOM();
			myword.OpenMyWordDoc(FileName, ReadOnly,AddToRecentFiles);//打开文档
			CString Text = _T("Hi i'm new word,can we make a friend");
			myword.WriteWordDoc(Text);//加入新的内容
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
		////	MY_WORD.OpenMyWordDoc(FileName, ReadOnly, AddToRecentFiles);//打开文档
		//	CString Text = _T("Hi i'm new word,can we make a friend");
		//	MY_WORD.WriteWordDoc(Text);//加入新的内容
		//	CString My;
		//	MY_WORD.GetWordText(My);
		//	MY_WORD.CloseWordDoc(FALSE);
		}
  	}
    else
    {
        // TODO: 更改错误代码以符合您的需要
        wprintf(L"错误: GetModuleHandle 失败\n");
        nRetCode = 1;
    }


    return nRetCode;
}
