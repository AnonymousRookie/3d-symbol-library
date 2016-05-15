
// 3DSymbolLibNew.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "3DSymbolLibNew.h"
#include "MainFrm.h"

#include "3DSymbolLibNewDoc.h"
#include "3DSymbolLibNewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy3DSymbolLibNewApp

BEGIN_MESSAGE_MAP(CMy3DSymbolLibNewApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMy3DSymbolLibNewApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CMy3DSymbolLibNewApp ����

CMy3DSymbolLibNewApp::CMy3DSymbolLibNewApp()
{
	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("3DSymbolLibNew.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CMy3DSymbolLibNewApp ����

CMy3DSymbolLibNewApp theApp;


// CMy3DSymbolLibNewApp ��ʼ��

BOOL CMy3DSymbolLibNewApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("��ά���ſ�"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)

	

	// ����ļ��б�
	if(m_pRecentFileList != NULL)
	{
		int nMRUSize = m_pRecentFileList->GetSize();
		CString strMRUFile = "";
		
		g_strRecentOpenedFileArray.RemoveAll();
		// ��MRU�б���Ĺ����ļ���ȡ����
		for(int i=0; i<nMRUSize; ++i)
		{
			strMRUFile = m_pRecentFileList->m_arrNames[i];
			 
			if(strMRUFile != "")
			{
				g_strRecentOpenedFileArray.Add(strMRUFile);
			}
		}
	}



	//InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMy3DSymbolLibNewDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CMy3DSymbolLibNewView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	//m_pMainWnd->ShowWindow(SW_SHOW);
	//m_pMainWnd->UpdateWindow();
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����

	//��ʼ��GID+
	GdiplusStartupInput gdiplusStartupInput;   
	GdiplusStartup( &m_gdiplusToken,&gdiplusStartupInput,NULL );



	// [ADD]

	//==============================================================
	// ��ȡϵͳ���������ļ�
	//==============================================================
	char systemConfigureDir[256];
	GetCurrentDirectoryA(256,systemConfigureDir);
	g_systemConfigureFile = strcat(systemConfigureDir,"\\system.ini");
	

	// CString msg;
	// msg.Format("%s",g_systemConfigureFile.c_str());
	// AfxMessageBox(msg);


	CFileFind systemConfigureFinder;
	BOOL isSystemConfigureFind = systemConfigureFinder.FindFile(g_systemConfigureFile.c_str());
	

	if(!isSystemConfigureFind)
	{
		MessageBox(NULL,"Can not find system configure file!","warning",MB_OK);
	}

	CString tmpPath;
	::GetPrivateProfileStringA("SceneDataPath","path","error",tmpPath.GetBuffer(MAX_SIZE),MAX_SIZE,g_systemConfigureFile.c_str());

	g_sceneDataPath = tmpPath.GetBuffer(0);

	tmpPath.ReleaseBuffer();

	//==============================================================
	
	//==============================================================
	// ��ȡ���������ļ�
	//==============================================================
	
	/*char symbolsConfigureDir[256];
	GetCurrentDirectoryA(256,symbolsConfigureDir);
	g_symbolConfigureFile = strcat(symbolsConfigureDir,"\\symbols.xml");

	CFileFind symbolConfigureFinder;
	BOOL isSymbolConfigureFind = symbolConfigureFinder.FindFile(g_symbolConfigureFile.c_str());
	if(!isSymbolConfigureFind)
	{
		MessageBox(NULL,"Can not symbols.xml!","warning",MB_OK);
	}*/


	char symbolsConfigureDir[256];
	//GetCurrentDirectoryA(256,symbolsConfigureDir);

	strcpy(symbolsConfigureDir, g_sceneDataPath.c_str());

	//g_symbolConfigureFile = strcat(symbolsConfigureDir,"\\SymbolLibrary\\symbols.xml");
	
	g_point_symbolConfigureFile = strcat(symbolsConfigureDir,"\\SymbolLibrary\\point.plib");
	g_line_symbolConfigureFile = strcat(symbolsConfigureDir,"\\SymbolLibrary\\line.llib");
	g_area_symbolConfigureFile = strcat(symbolsConfigureDir,"\\SymbolLibrary\\area.alib");

	CFileFind symbolConfigureFinder;
	BOOL isSymbolConfigureFind = symbolConfigureFinder.FindFile(g_point_symbolConfigureFile.c_str());
	if(!isSymbolConfigureFind)
	{
		MessageBox(NULL,"Can not point.plib!","warning",MB_OK);
	}
	//==============================================================
	// ��XML�ļ��е���Ϣ����ȫ��list��
	//==============================================================
	CoInitialize(NULL); // ��ʼ��COM��
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CComPtr<IXMLDOMDocument> spDoc; //DOM
	spDoc.CoCreateInstance(CLSID_DOMDocument);
	VARIANT_BOOL vb;
	
	spDoc->load(CComVariant(g_point_symbolConfigureFile.c_str()), &vb); //����XML�ļ�
	CComPtr<IXMLDOMElement> spRootEle;
	spDoc->get_documentElement(&spRootEle); //���ڵ�

	CComPtr<IXMLDOMNodeList> spNodeList[5];

	string tmp[5];
	for(int i=0;i<g_modelKindNumber;++i)
	{
		tmp[i] = g_modelTree[i]._noteDirectory;
	}

	for(int i=0;i<g_modelKindNumber;++i)
	{
		spRootEle->selectNodes(_bstr_t(tmp[i].c_str()),&spNodeList[i]);

		long nLen;//�ӽڵ���
		spNodeList[i]->get_length(&nLen); //�ӽڵ���
		for (long j = 0; j != nLen; ++j) //�����ӽڵ�
		{
			CComPtr<IXMLDOMNode> spNode;
			spNodeList[i]->get_item(j, &spNode);
			BSTR text;
			spNode->get_text(&text);

			list<string>::iterator iter;

			string tmpStr = (_bstr_t)(text);

			iter = find(g_modelList[i].begin(),g_modelList[i].end(),tmpStr);
			if(iter == g_modelList[i].end())
			{
				g_modelList[i].push_back(tmpStr);
			}
		}
	}
	
	CoUninitialize();

	//==============================================================



	// �½�����  OR  �򿪹���
	CProjectFileSetting prjFileSetDlg;
	prjFileSetDlg.DoModal();

	
	
	return TRUE;
}

int CMy3DSymbolLibNewApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	GdiplusShutdown( m_gdiplusToken ); 

	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CMy3DSymbolLibNewApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CMy3DSymbolLibNewApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMy3DSymbolLibNewApp �Զ������/���淽��

void CMy3DSymbolLibNewApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CMy3DSymbolLibNewApp::LoadCustomState()
{
}

void CMy3DSymbolLibNewApp::SaveCustomState()
{
}

// CMy3DSymbolLibNewApp ��Ϣ�������



