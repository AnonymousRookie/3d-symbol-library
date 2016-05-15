#include "stdafx.h"
#include "3DSymbolLibNew.h"
#include "TerrainImportContour.h"
#include "afxdialogex.h"


// TerrainImportContour �Ի���

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


// TerrainImportContour ��Ϣ�������

// �����������ͼƬ
void TerrainImportContour::OnBnClickedButtonTerrainTexBroswer()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString tt,stt;
	FILE *fp;

	CFileDialog FileDialog(TRUE,"�ر�����",NULL,OFN_HIDEREADONLY \
		| OFN_OVERWRITEPROMPT,\
		"�ر�����sand(*.bmp)|*.bmp|\
		�ı���ʽ(*.txt)|*.txt||",NULL);

	FileDialog.m_ofn.lpstrTitle="ѡ��ر������ļ�";	


	if(FileDialog.DoModal() == IDOK)
		m_TerrainContoureTex = FileDialog.GetPathName();
	else
		return;	
	this->UpdateData(FALSE);

	if((fp=fopen(m_TerrainContoureTex,"r"))==NULL)
	{
		MessageBox("���������ļ�������!","��ʼ������ģ��",MB_ICONINFORMATION+MB_OK);
		exit(-1);
	}
}

void TerrainImportContour::OnBnClickedButtonContoureBroswer()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString tt,stt;
	FILE *fp;

	CFileDialog FileDialog(TRUE,"�ȸ���ͼ",NULL,OFN_HIDEREADONLY \
		| OFN_OVERWRITEPROMPT,\
		"�ȸ���ͼterrain(*.bmp)|*.bmp|\
		�ı���ʽ(*.txt)|*.txt||",NULL);

	FileDialog.m_ofn.lpstrTitle="ѡ��ȸ���ͼ�ļ�";	


	if(FileDialog.DoModal() == IDOK)
		m_TerrainContour = FileDialog.GetPathName();
	else
		return;	
	this->UpdateData(FALSE);

	if((fp=fopen(m_TerrainContour,"r"))==NULL)
	{
		MessageBox("�ȸ���ͼ�ļ�������!","��ʼ������ģ��",MB_ICONINFORMATION+MB_OK);
		exit(-1);
	}
}
