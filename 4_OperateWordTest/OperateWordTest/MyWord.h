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


//������������
enum Alignment {
	wdAlignParagraphCenter = 1,
	wdAlignParagraphRight,
	wdAlignParagraphJustify
};

//����Word����
/*
wdFormatDocument  ��׼��doc�ĵ�
wdFormatWebArchiv �����ļ���ҳ
wdFormatHTML    ��ҳ
wdFormatFilteredHTML    ȥ��һЩ΢����Ϣ����ҳ
wdFormatTemplate    ģ��
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
	//һЩ��������
public:
	CApplication Application; //����Word
	CDocuments Documents;//word�ĵ�����
	CDocument0 Document;//����word�ĵ�
	CSelection Selection;//ѡ��༭����û�ж����ʱ����ǲ����
	CFont0 Font;//�������   
	CRange Range;//��Χ��

public:
	MyWord();
	~MyWord();
	bool InitMyWordCOM();//��ʼ��COM֧�ֿ�
	bool CreatMyWordApp();//����word����
	bool CreateDocument();//����Document
	bool Create();//����word��document
	void CloseMyWordApp();//�ر�word����

public:
	bool OpenMyWordDoc(CString FileName, BOOL ReadOnly = FALSE, BOOL  AddToRecentFiles = FALSE);//��Word	
	void ShowApp(BOOL flag);//���ӻ�
	bool SaveDoc();//�����ĵ�
	bool SaveAsDoc(CString FileName, int SaveType = FALSE);//��������
	
	/////////д�ļ�����//////////
	void WriteWordDoc(CString Text);//д��Doc�ĵ�
	void NewLine(int nCount = 1);//�س�����
	void WriteTextNewLineText(CString Text,int nCount);//�س���N��д���ļ�

	/////////�������ò���///////////
	void SetFont(int Blod,int Italic,int UnderLine );
	void SetFont(float FontSize /*= 9*/, long FontColor /*= 0*/, long UnderlineColor /*= 0*/);
	void SetTableFont(int Row, int Column, CString FontName, int FontSize = 9, long FontColor = 0, long FontBackColor = 0);

	///////////���ò���/////////////
	//��ȡWord ���ı�����
	void GetWordText(CString &Text);

	bool CloseWordDoc(BOOL SaveChange = FALSE);//�ر�Word
private:

};