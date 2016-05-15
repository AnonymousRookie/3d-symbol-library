// SkyBoxTexLoad.cpp : 实现文件
//

#include "stdafx.h"
#include "3DSymbolLibNew.h"
#include "SkyBoxTexLoad.h"
#include "afxdialogex.h"


// CSkyBoxTexLoad 对话框

IMPLEMENT_DYNAMIC(CSkyBoxTexLoad, CDialog)

CSkyBoxTexLoad::CSkyBoxTexLoad(CWnd* pParent /*=NULL*/)
	: CDialog(CSkyBoxTexLoad::IDD, pParent)
	, m_SkyBoxTexTP(_T(""))
	, m_SkyBoxTexLF(_T(""))
	, m_SkyBoxTexBK(_T(""))
	, m_SkyBoxTexRT(_T(""))
	, m_SkyBoxTexFR(_T(""))
{

}

CSkyBoxTexLoad::~CSkyBoxTexLoad()
{
}

void CSkyBoxTexLoad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SKY_TP, m_SkyBoxTexTP);
	DDX_Text(pDX, IDC_EDIT_SKY_LF, m_SkyBoxTexLF);
	DDX_Text(pDX, IDC_EDIT_SKY_BK, m_SkyBoxTexBK);
	DDX_Text(pDX, IDC_EDIT_SKY_RT, m_SkyBoxTexRT);
	DDX_Text(pDX, IDC_EDIT_SKY_FR, m_SkyBoxTexFR);
}


BEGIN_MESSAGE_MAP(CSkyBoxTexLoad, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SKY_TP, &CSkyBoxTexLoad::OnBnClickedButtonSkyTp)
	ON_BN_CLICKED(IDC_BUTTON_SKY_LF, &CSkyBoxTexLoad::OnBnClickedButtonSkyLf)
	ON_BN_CLICKED(IDC_BUTTON_SKY_BK, &CSkyBoxTexLoad::OnBnClickedButtonSkyBk)
	ON_BN_CLICKED(IDC_BUTTON_SKY_RT, &CSkyBoxTexLoad::OnBnClickedButtonSkyRt)
	ON_BN_CLICKED(IDC_BUTTON_SKY_FR, &CSkyBoxTexLoad::OnBnClickedButtonSkyFr)
END_MESSAGE_MAP()


// CSkyBoxTexLoad 消息处理程序


void CSkyBoxTexLoad::OnBnClickedButtonSkyTp()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tt,stt;
	FILE *fp;

	CFileDialog FileDialog(TRUE,"天空盒",NULL,OFN_HIDEREADONLY \
		| OFN_OVERWRITEPROMPT,\
		"天空盒(*.bmp)|*.bmp|",NULL);

	FileDialog.m_ofn.lpstrTitle="选择天空盒[顶部]文件";	


	if(FileDialog.DoModal() == IDOK)
		m_SkyBoxTexTP = FileDialog.GetPathName();
	else
		return;	
	this->UpdateData(FALSE);

	if((fp=fopen(m_SkyBoxTexTP,"r"))==NULL)
	{
		MessageBox("天空盒文件不存在!","初始化天空盒模型",MB_ICONINFORMATION+MB_OK);
		exit(-1);
	}
}


void CSkyBoxTexLoad::OnBnClickedButtonSkyLf()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	CString tt,stt;
	FILE *fp;

	CFileDialog FileDialog(TRUE,"天空盒",NULL,OFN_HIDEREADONLY \
		| OFN_OVERWRITEPROMPT,\
		"天空盒(*.bmp)|*.bmp|",NULL);

	FileDialog.m_ofn.lpstrTitle="选择天空盒[左面]文件";	


	if(FileDialog.DoModal() == IDOK)
		m_SkyBoxTexLF = FileDialog.GetPathName();
	else
		return;	
	this->UpdateData(FALSE);

	if((fp=fopen(m_SkyBoxTexLF,"r"))==NULL)
	{
		MessageBox("天空盒文件不存在!","初始化天空盒模型",MB_ICONINFORMATION+MB_OK);
		exit(-1);
	}
}


void CSkyBoxTexLoad::OnBnClickedButtonSkyBk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tt,stt;
	FILE *fp;

	CFileDialog FileDialog(TRUE,"天空盒",NULL,OFN_HIDEREADONLY \
		| OFN_OVERWRITEPROMPT,\
		"天空盒(*.bmp)|*.bmp|",NULL);

	FileDialog.m_ofn.lpstrTitle="选择天空盒[后面]文件";	


	if(FileDialog.DoModal() == IDOK)
		m_SkyBoxTexBK = FileDialog.GetPathName();
	else
		return;	
	this->UpdateData(FALSE);

	if((fp=fopen(m_SkyBoxTexBK,"r"))==NULL)
	{
		MessageBox("天空盒文件不存在!","初始化天空盒模型",MB_ICONINFORMATION+MB_OK);
		exit(-1);
	}
}


void CSkyBoxTexLoad::OnBnClickedButtonSkyRt()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tt,stt;
	FILE *fp;

	CFileDialog FileDialog(TRUE,"天空盒",NULL,OFN_HIDEREADONLY \
		| OFN_OVERWRITEPROMPT,\
		"天空盒(*.bmp)|*.bmp|",NULL);

	FileDialog.m_ofn.lpstrTitle="选择天空盒[右边]文件";	


	if(FileDialog.DoModal() == IDOK)
		m_SkyBoxTexRT = FileDialog.GetPathName();
	else
		return;	
	this->UpdateData(FALSE);

	if((fp=fopen(m_SkyBoxTexRT,"r"))==NULL)
	{
		MessageBox("天空盒文件不存在!","初始化天空盒模型",MB_ICONINFORMATION+MB_OK);
		exit(-1);
	}
}


void CSkyBoxTexLoad::OnBnClickedButtonSkyFr()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tt,stt;
	FILE *fp;

	CFileDialog FileDialog(TRUE,"天空盒",NULL,OFN_HIDEREADONLY \
		| OFN_OVERWRITEPROMPT,\
		"天空盒(*.bmp)|*.bmp|",NULL);

	FileDialog.m_ofn.lpstrTitle="选择天空盒[前面]文件";	


	if(FileDialog.DoModal() == IDOK)
		m_SkyBoxTexFR = FileDialog.GetPathName();
	else
		return;	
	this->UpdateData(FALSE);

	if((fp=fopen(m_SkyBoxTexFR,"r"))==NULL)
	{
		MessageBox("天空盒文件不存在!","初始化天空盒模型",MB_ICONINFORMATION+MB_OK);
		exit(-1);
	}
}
