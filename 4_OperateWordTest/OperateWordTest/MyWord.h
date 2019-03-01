#pragma once
#include"CApplication.h"
#include"CDocument0.h"
#include"CDocuments.h"
#include"CRange.h"
#include"CFont0.h"
#include"CSelection.h"
#include"CTable0.h"
#include"CTables0.h"
#include"CRange0.h"
#include"stdafx.h"


//段落对齐的属性
enum Alignment {
	wdAlignParagraphCenter = 1,
	wdAlignParagraphRight,
	wdAlignParagraphJustify
};

//保存Word类型
/*
wdFormatDocument  标准的doc文档
wdFormatWebArchiv 单个文件网页
wdFormatHTML    网页
wdFormatFilteredHTML    去掉一些微软信息的网页
wdFormatTemplate    模版
*/

enum SaveType {
	wdFormatDocument = 0,
	wdFormatWebArchive = 9,
	wdFormatHTML = 8,
	wdFormatFilteredHTML = 10,
	wdFormatTemplate = 1
};


class MyWord
{
	//一些对象申明
public:
	CApplication Application; //创建Word
	CDocuments Documents;//word文档集合
	CDocument0 Document;//单个word文档
	CSelection Selection;//选择编辑对象，没有对象的时候就是插入点
	CFont0 Font;//字体对象   
	CRange Range;//范围？

public:
	MyWord();
	~MyWord();
	bool InitMyWordCOM();//初始化COM支持库
	bool CreatMyWordApp();//创建word程序
	bool CreateDocument();//创建Document
	bool Create();//创建word和document
	void CloseMyWordApp();//关闭word程序

public:
	bool OpenMyWordDoc(CString FileName, BOOL ReadOnly = FALSE, BOOL  AddToRecentFiles = FALSE);//打开Word	
	void ShowApp(BOOL flag);//可视化
	bool SaveDoc();//保存文档
	bool SaveAsDoc(CString FileName, int SaveType = FALSE);//保存类型
	
	/////////写文件操作//////////
	void WriteWordDoc(CString Text);//写入Doc文档
	void NewLine(int nCount = 1);//回车换行
	void WriteTextNewLineText(CString Text,int nCount);//回车换N行写入文件

	/////////字体设置操作///////////
	void SetFont(int Blod,int Italic,int UnderLine );
	void SetFont(float FontSize /*= 9*/, long FontColor /*= 0*/, long UnderlineColor /*= 0*/);
	void SetTableFont(int Row, int Column, CString FontName, int FontSize = 9, long FontColor = 0, long FontBackColor = 0);

	///////////常用操作/////////////
	//获取Word 纯文本内容
	void GetWordText(CString &Text);

	bool CloseWordDoc(BOOL SaveChange = FALSE);//关闭Word
private:

};