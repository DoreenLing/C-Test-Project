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
//function����ʼ��com�˿�
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

//function������word����
bool MyWord::CreatMyWordApp()
{
	if (!Application.CreateDispatch(_T("word.Application"), NULL)) {
		AfxMessageBox(_T("plesse install the office"));
		return FALSE;
	}
	return TRUE;
}
//function������Document
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
			CComVariant Template(_T(""));//����һ���յ�ģ��
			CComVariant NewTemplate(false);
			CComVariant DocumentType(0);
			CComVariant Visible;//������ ��Ĭ��ֵ
			Document = Documents.Add(&Template, &NewTemplate, &DocumentType, &Visible);
			if (!Document.m_lpDispatch) {
				AfxMessageBox(_T("It fail to creat word"));
				return FALSE;
			}
			else {
				Selection = Application.get_Selection();//��õ�ǰWord��������ʼ��Ϊ����doc���selection����ϸ��һ��ȷʵӦ����Word�Ľӿڵ�
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

//function:����word �� document
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

//function���ر�word����
void MyWord::CloseMyWordApp()
{
	COleVariant vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!Application.m_lpDispatch) {
		AfxMessageBox(_T("It fail to get the Word "));
		return;
	}
	else {
		Application.Quit(vOpt, vOpt, vOpt);
		//�����ͷ���Դ�����Ǻܺã������Ҿ�����������ȥ�����ˡ�
	}
}

//function�����ļ�
//@prama��FileName: �ļ���
//@prama:ReadOnly�� 
//@prama:AddToRecentFiles��
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
		//����word����
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
	CComVariant format(0);//�򿪷�ʽ 0 Ϊdoc�Ĵ򿪷�ʽ
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

//function:д���ļ�
//@prama:Text д������
void MyWord::WriteWordDoc(CString Text)
{
	Selection.TypeText(Text);
}

//function:�����ļ�
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

//function:�ļ����Ϊ
//@prama:FileName �ļ���
//@prama:SaveType �洢����
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
		//��ð��պ���д ��Ȼ���ܳ������⡢ �Ͼ������΢��д��
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

//function:�ر�Word
//@prama: SaveChange �Ƿ����Ϊ
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
		//�����һ��������vTrue ����ִ��󣬿����Ǻ���Ĳ���ҲҪ��Ӧ�ı仯
		//��vba û�и���Ӧ���� �Ҿ������ַ���������
		Document.Close(&vFalse, &vOpt, &vOpt);
	}
	return TRUE;
}

//function:�س�����
//@prama:nCount ��������
void MyWord::NewLine(int  nCount)
{
	if (nCount <= 0) {
		nCount = 0;
	}
	else {
		for (int i = 0; i < nCount; i++) {
			Selection.TypeParagraph();//�½�һ��
		}
	}
}

//function:�س���n��
//@prama:nCount ��������
//@prama:Text д������
void  MyWord::WriteTextNewLineText(CString Text, int nCount)
{
	NewLine(nCount);
	WriteWordDoc(Text);
}

//function:����������ʽ       
//@prama:Italic б��(0.1)
//@prama:UnderLine �»���(0.1)
//@prama:Blod ����Ȩֵ(����)
void  MyWord::SetFont(int  Blodsize, int Italicsize /*= FALSE*/, int UnderLinesize /*= FALSE*/)
{
	if (!Selection.m_lpDispatch) {
		AfxMessageBox(_T("It fail to create Documents and fail to save the doc"));
		return;
	}
	else {
		Selection.get_Text();
		Font = Selection.get_Font();//��õ�ǰ����
		Font.put_Bold(Blodsize);
		Font.put_Italic(Italicsize);
		Font.put_Underline(UnderLinesize);
		Selection.put_Font(Font);
	}
}

//function:����������ɫ�Լ���С      
//@prama:FontSize �����С
//@prama:FontColor ������ɫ
//@prama:UnderlineColor �»�����ɫ
void  MyWord::SetFont(float FontSize /*= 9*/, long FontColor /*= 0*/, long UnderlineColor /*= 0*/)
{
	if (!Selection.m_lpDispatch) {
		AfxMessageBox(_T("It fail to create Documents and fail to save the doc"));
		return;
	}
	else {
		Selection.get_Text();
		Font = Selection.get_Font();//��õ�ǰ����
		Font.put_Size(FontSize);
		Font.put_Color(FontColor);
		Font.put_UnderlineColor(UnderlineColor);
		Selection.put_Font(Font);
	}
}

//function:���ñ������      
//@prama:Row �����С
//@prama:Column ������ɫ
//@prama:UnderlineColor �»�����ɫ
void  MyWord::SetTableFont(int Row, int Column, CString FontName, int FontSize /*= 9*/, long FontColor /*= 0*/, long FontBackColor /*= 0*/)
{
	;
}

//function:��ȡ�ĵ��е��ı�      
//@prama:Text ��ȡ����
void MyWord::GetWordText(CString &Text)
{
	//CComVariant vOpt;
	COleVariant vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	Document = Application.get_ActiveDocument();//��õ�ǰ�����ĵ� ���ǵ�ǰ���ڱ༭�ĵ�
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