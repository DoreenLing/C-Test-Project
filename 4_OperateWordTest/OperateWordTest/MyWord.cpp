#include"stdafx.h"
#include"MyWord.h"

MyWord::MyWord()
{

}

MyWord::~MyWord()
{
	Application.ReleaseDispatch();
	Documents.ReleaseDispatch();
	Document.ReleaseDispatch();
	Selection.ReleaseDispatch();
	Font.ReleaseDispatch();
	Range.ReleaseDispatch();
}
//function：初始化com端口
bool MyWord::InitMyWordCOM()
{
	if (CoInitialize(NULL) != S_OK) {
		AfxMessageBox(_T("fail to initCOM"));
		return FALSE;
	}
	else {
		return TRUE;
	}
}

//function：创建word程序
bool MyWord::CreatMyWordApp()
{
	if (!Application.CreateDispatch(_T("word.Application"), NULL)) {
		AfxMessageBox(_T("plesse install the office"));
		return FALSE;
	}
	return TRUE;
}
//function：创建Document
bool MyWord::CreateDocument()
{
	if (!Application.m_lpDispatch) {
		AfxMessageBox(_T("Application is NULL,Documents created fail!"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	else {
		Documents = Application.get_Documents();
		if (Documents.m_lpDispatch == NULL) {
			AfxMessageBox(_T("It fail to creat documents"));
			return FALSE;
		}
		else {
			CComVariant Template(_T(""));//创建一个空的模版
			CComVariant NewTemplate(false);
			CComVariant DocumentType(0);
			CComVariant Visible;//不处理 用默认值
			Document = Documents.Add(&Template, &NewTemplate, &DocumentType, &Visible);
			if (!Document.m_lpDispatch) {
				AfxMessageBox(_T("It fail to creat word"));
				return FALSE;
			}
			else {
				Selection = Application.get_Selection();//获得当前Word操作。开始认为是在doc获得selection。仔细想一下确实应该是Word的接口点
				if (!Selection.m_lpDispatch) {
					AfxMessageBox(_T("It fail to get selection"));
					return FALSE;
				}
				else {
					return TRUE;
				}
			}
		}
	}
}

//function:创建word 和 document
bool MyWord::Create()
{
	if (CreatMyWordApp()) {
		if (CreateDocument()) {
			return TRUE;
		}
		else
			return FALSE;
	}
	else
		return FALSE;
}

//function：关闭word对象
void MyWord::CloseMyWordApp()
{
	COleVariant vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!Application.m_lpDispatch) {
		AfxMessageBox(_T("It fail to get the Word "));
		return;
	}
	else {
		Application.Quit(vOpt, vOpt, vOpt);
		//这里释放资源好像不是很好，所以我就在析构函数去处理了。
	}
}

//function：打开文件
//@prama：FileName: 文件名
//@prama:ReadOnly： 
//@prama:AddToRecentFiles：
bool MyWord::OpenMyWordDoc(CString FileName, BOOL ReadOnly, BOOL  AddToRecentFiles)
{
	CComVariant Read(ReadOnly);
	CComVariant AddToR(AddToRecentFiles);
	CComVariant Name(FileName);

	COleVariant vTrue((short)TRUE), vFalse((short)FALSE);
	COleVariant varstrNull(_T(""));
	COleVariant varZero((short)0);
	COleVariant varTrue(short(1), VT_BOOL);
	COleVariant varFalse(short(0), VT_BOOL);
	COleVariant vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	if (!Application.m_lpDispatch) {
		//创建word程序
		if (Create() == FALSE) {
			return FALSE;
		}
	}
	//if (!Documents.m_lpDispatch) {
	//	Documents = Application.get_Documents();
	//	if (!Documents.m_lpDispatch) {
	//		AfxMessageBox(_T("It fail to create document"));
	//		return FALSE;
	//	}
	//}
	CComVariant format(0);//打开方式 0 为doc的打开方式
	Document = Documents.Open(&Name, varFalse, &Read, &AddToR, vOpt, vOpt,
		vFalse, vOpt, vOpt, &format, vOpt, vTrue, vOpt, vOpt, vOpt, vOpt);
	if (!Document.m_lpDispatch) {
		AfxMessageBox(_T("It fail to open the file"));
		return FALSE;
	}
	else {
		Selection = Application.get_Selection();
		if (!Selection.m_lpDispatch) {
			AfxMessageBox(_T("It fail to get selection"));
			return FALSE;
		}
		return TRUE;
	}
}

//function:写入文件
//@prama:Text 写入内容
void MyWord::WriteWordDoc(CString Text)
{
	Selection.TypeText(Text);
}

//function:保存文件
bool MyWord::SaveDoc()
{
	if (!Document.m_lpDispatch) {
		AfxMessageBox(_T("It fail to create Documents and fail to save the doc"));
		return FALSE;
	}
	else {
		Document.Save();
		return TRUE;
	}
}

//function:文件另存为
//@prama:FileName 文件名
//@prama:SaveType 存储类型
bool MyWord::SaveAsDoc(CString FileName, int SaveType)
{
	CComVariant vTrue(TRUE);
	CComVariant vFalse(FALSE);
	CComVariant vOpt;
	CComVariant cFileName(FileName);
	CComVariant FileFormat(SaveType);
	Document = Application.get_ActiveDocument();
	if (!Document.m_lpDispatch) {
		AfxMessageBox(_T("It fail to create Documents and fail to save the doc"));
		return FALSE;
	}
	else {
		//最好按照宏来写 不然可能出现问题、 毕竟这个是微软写的
		/*ActiveDocument.SaveAs FileName:="xiaoyuer.doc", FileFormat:= _
		wdFormatDocument, LockComments:=False, Password:="", AddToRecentFiles:= _
		True, WritePassword:="", ReadOnlyRecommended:=False, EmbedTrueTypeFonts:= _
		False, SaveNativePictureFormat:=False, SaveFormsData:=False, _
		SaveAsAOCELetter:=False*/

		Document.SaveAs(&cFileName, &FileFormat, &vFalse, COleVariant(_T("")), &vTrue,
			COleVariant(_T("")), &vFalse, &vFalse, &vFalse, &vFalse, &vFalse, &vOpt, &vOpt, &vOpt, &vOpt, &vOpt);

	}
	return TRUE;
}

//function:关闭Word
//@prama: SaveChange 是否另存为
bool MyWord::CloseWordDoc(BOOL SaveChange/* =FALSE */)
{
	CComVariant vTrue(TRUE);
	CComVariant vFalse(FALSE);
	CComVariant vOpt;
	CComVariant cSavechage(SaveChange);
	if (!Document.m_lpDispatch) {
		AfxMessageBox(_T("It fail to create Documents and fail to close the doc"));
		return FALSE;
	}
	else {
		if (TRUE == SaveChange) {
			SaveDoc();
		}
		//下面第一个参数填vTrue 会出现错误，可能是后面的参数也要对应的变化
		//但vba 没有给对应参数 我就用这种方法来保存
		Document.Close(&vFalse, &vOpt, &vOpt);
	}
	return TRUE;
}

//function:回车换行
//@prama:nCount 换行数量
void MyWord::NewLine(int  nCount)
{
	if (nCount <= 0) {
		nCount = 0;
	}
	else {
		for (int i = 0; i < nCount; i++) {
			Selection.TypeParagraph();//新建一段
		}
	}
}

//function:回车换n行
//@prama:nCount 换行数量
//@prama:Text 写入内容
void  MyWord::WriteTextNewLineText(CString Text, int nCount)
{
	NewLine(nCount);
	WriteWordDoc(Text);
}

//function:设置字体形式       
//@prama:Italic 斜体(0.1)
//@prama:UnderLine 下划线(0.1)
//@prama:Blod 粗体权值(几百)
void  MyWord::SetFont(int  Blodsize, int Italicsize /*= FALSE*/, int UnderLinesize /*= FALSE*/)
{
	if (!Selection.m_lpDispatch) {
		AfxMessageBox(_T("It fail to create Documents and fail to save the doc"));
		return;
	}
	else {
		Selection.get_Text();
		Font = Selection.get_Font();//获得当前字体
		Font.put_Bold(Blodsize);
		Font.put_Italic(Italicsize);
		Font.put_Underline(UnderLinesize);
		Selection.put_Font(Font);
	}
}

//function:设置字体颜色以及大小      
//@prama:FontSize 字体大小
//@prama:FontColor 字体颜色
//@prama:UnderlineColor 下划线颜色
void  MyWord::SetFont(float FontSize /*= 9*/, long FontColor /*= 0*/, long UnderlineColor /*= 0*/)
{
	if (!Selection.m_lpDispatch) {
		AfxMessageBox(_T("It fail to create Documents and fail to save the doc"));
		return;
	}
	else {
		Selection.get_Text();
		Font = Selection.get_Font();//获得当前字体
		Font.put_Size(FontSize);
		Font.put_Color(FontColor);
		Font.put_UnderlineColor(UnderlineColor);
		Selection.put_Font(Font);
	}
}

//function:设置表格字体      
//@prama:Row 字体大小
//@prama:Column 字体颜色
//@prama:UnderlineColor 下划线颜色
void  MyWord::SetTableFont(int Row, int Column, CString FontName, int FontSize /*= 9*/, long FontColor /*= 0*/, long FontBackColor /*= 0*/)
{
	;
}

//function:获取文档中的文本      
//@prama:Text 获取内容
void MyWord::GetWordText(CString &Text)
{
	//CComVariant vOpt;
	COleVariant vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	Document = Application.get_ActiveDocument();//获得当前激活文档 就是当前正在编辑文档
	if (!Document.m_lpDispatch)
	{
		AfxMessageBox(_T("It fail to get active Document"));
		return;
	}
	else
	{
		Range = Document.Range(vOpt, vOpt);
		Text = Range.get_Text();
		AfxMessageBox(Text);
	}
}