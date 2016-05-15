#include "stdafx.h"
#include "3DSymbolLibNew.h"
#include "TerrainImportContour.h"
#include "afxdialogex.h"


// TerrainImportContour 对话框

IMPLEMENT_DYNAMIC(TerrainImportContour, CDialog)

TerrainImportContour::TerrainImportContour(CWnd* pParent /*=NULL*/)
	: CDialog(TerrainImportContour::IDD, pParent)
	, m_TerrainContoureTex(_T(""))
	, m_TerrainContour(_T(""))
{
	// Empty
}

TerrainImportContour::~TerrainImportContour()
{
	// Empty
}

void TerrainImportContour::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TERRAIN_TEXTURE, m_TerrainContoureTex);
	DDX_Text(pDX, IDC_EDIT_TERRAIN_CONTOUR, m_TerrainContour);
}


BEGIN_MESSAGE_MAP(TerrainImportContour, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_TERRAIN_TEX_BROSWER, &TerrainImportContour::OnBnClickedButtonTerrainTexBroswer)
	ON_BN_CLICKED(IDC_BUTTON_CONTOURE_BROSWER, &TerrainImportContour::OnBnClickedButtonContoureBroswer)
END_MESSAGE_MAP()


// TerrainImportContour 消息处理程序

// 浏览地形纹理图片
void TerrainImportContour::OnBnClickedButtonTerrainTexBroswer()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tt,stt;
	FILE *fp;

	CFileDialog FileDialog(TRUE,"地表纹理",NULL,OFN_HIDEREADONLY \
		| OFN_OVERWRITEPROMPT,\
		"地表纹理sand(*.bmp)|*.bmp|\
		文本格式(*.txt)|*.txt||",NULL);

	FileDialog.m_ofn.lpstrTitle="选择地表纹理文件";	


	if(FileDialog.DoModal() == IDOK)
		m_TerrainContoureTex = FileDialog.GetPathName();
	else
		return;	
	this->UpdateData(FALSE);

	if((fp=fopen(m_TerrainContoureTex,"r"))==NULL)
	{
		MessageBox("地面纹理文件不存在!","初始化地面模型",MB_ICONINFORMATION+MB_OK);
		exit(-1);
	}
}

void TerrainImportContour::OnBnClickedButtonContoureBroswer()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tt,stt;
	FILE *fp;

	CFileDialog FileDialog(TRUE,"等高势图",NULL,OFN_HIDEREADONLY \
		| OFN_OVERWRITEPROMPT,\
		"等高势图terrain(*.bmp)|*.bmp|\
		文本格式(*.txt)|*.txt||",NULL);

	FileDialog.m_ofn.lpstrTitle="选择等高势图文件";	


	if(FileDialog.DoModal() == IDOK)
		m_TerrainContour = FileDialog.GetPathName();
	else
		return;	
	this->UpdateData(FALSE);

	if((fp=fopen(m_TerrainContour,"r"))==NULL)
	{
		MessageBox("等高势图文件不存在!","初始化地面模型",MB_ICONINFORMATION+MB_OK);
		exit(-1);
	}
}
