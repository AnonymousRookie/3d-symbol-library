// AreaClassification.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DSymbolLibNew.h"
#include "AreaClassification.h"
#include "afxdialogex.h"


 

#include <io.h>


// CAreaClassification �Ի���

IMPLEMENT_DYNAMIC(CAreaClassification, CDialog)

CAreaClassification::CAreaClassification(CWnd* pParent /*=NULL*/)
	: CDialog(CAreaClassification::IDD, pParent)
{

}

CAreaClassification::~CAreaClassification()
{
}

void CAreaClassification::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_Image);
	DDX_Control(pDX, IDC_TREE_AREA_LIST, m_Area_Texture_List);
}


BEGIN_MESSAGE_MAP(CAreaClassification, CDialog)
	ON_BN_CLICKED(IDOK, &CAreaClassification::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAreaClassification::OnBnClickedCancel)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_AREA_LIST, &CAreaClassification::OnSelchangedTreeAreaList)
//	ON_COMMAND(ID_MENU_UPDATE_AREA_TEXTURE, &CAreaClassification::OnMenuUpdateAreaTexture)
//ON_COMMAND(ID_MENU_AREA_DELETE, &CAreaClassification::OnMenuAreaDelete)
END_MESSAGE_MAP()


// CAreaClassification ��Ϣ�������


void CAreaClassification::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();

	CString tmp = "\\";
	CString topItem = "AreaTexture";
	HTREEITEM selectItem = m_Area_Texture_List.GetSelectedItem();
	CString selectItemText = m_Area_Texture_List.GetItemText(selectItem);
	HTREEITEM parentItem = m_Area_Texture_List.GetParentItem(selectItem);
	CString parentItemText = m_Area_Texture_List.GetItemText(parentItem);

	m_selectItem = selectItemText;
	m_Dir = g_sceneDataPath.c_str() + tmp + topItem + tmp + parentItemText;
}


void CAreaClassification::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}


 

void CAreaClassification::OnSelchangedTreeAreaList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	HTREEITEM selectItem = m_Area_Texture_List.GetSelectedItem();
	CString selectItemText = m_Area_Texture_List.GetItemText(selectItem);

	HTREEITEM parentItem = m_Area_Texture_List.GetParentItem(selectItem);
	CString parentItemText = m_Area_Texture_List.GetItemText(parentItem);


	CString topItem = "AreaTexture";
	CString RockType[1] = {"grassland"};
	CString imgPathAndName;
	CString tmp = "\\";
	for(int i=0;i<1;++i)
	{
		if(parentItemText == RockType[i])
		{
			imgPathAndName = g_sceneDataPath.c_str() + tmp + topItem+ tmp + RockType[i] + tmp + selectItemText;
			//MessageBox(imgPathAndName,"");
			// BMP
			if(1)
			{
				CRect rect;
				CDC *pdc = GetDC();
				GetDlgItem(IDC_STATIC_IMAGE)->GetWindowRect(rect);
				this->ScreenToClient(rect);
				drawBitmapFromFile(imgPathAndName,pdc,rect);
			}	
		}
	}
}


// ��ѡ�е�bmp����Ӱ���ڿؼ��ϻ���
void CAreaClassification::drawBitmapFromFile(CString bitmapFilePath,CDC*pDC,CRect rect)
{
	HANDLE   filehandle=::LoadImage(NULL,bitmapFilePath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);  //����Ӱ���ļ� 
	if(filehandle!=NULL)   //������سɹ�
	{   
		CBitmap   bmp;   
		if(bmp.Attach(filehandle))   
		{   
			BITMAP   bmpInfo;   
			bmp.GetBitmap(&bmpInfo);   //��ȡ��Դλͼ��Ϣ
			CDC   dcMemory;   
			dcMemory.CreateCompatibleDC(pDC);   //����һ�����ض��豸����һ�µ��ڴ��豸����
			dcMemory.SelectObject(&bmp);   //ѡ��bmp����ָ�����豸�����Ļ�����,���¶����滻��ǰ����ͬ���͵Ķ���
			//����ָ���豸�����е�λͼ����ģʽ. HALFTONE����Դ�������е�����ӳ�䵽Ŀ������������ؿ��У�
			//����Ŀ�����ؿ��һ����ɫ��Դ���ص���ɫ�ӽ���

			//StretchBlt():Դ�����и���һ��λͼ��Ŀ�����,��Ҫʱ��ĿǰĿ���豸���õ�ģʽ����ͼ��������ѹ����
			pDC->StretchBlt(rect.left,rect.top,rect.Width(),rect.Height(),&dcMemory,0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,SRCCOPY);   
			bmp.Detach();   //����bmp����
		}   
	}   
}

BOOL CAreaClassification::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString tmp = "\\";
	CString topItem = "AreaTexture";
	CString RockType[1] = {"grassland"};

	hRoot = m_Area_Texture_List.InsertItem(topItem,0,0);

	for(int i=0;i<1;++i)
	{
		hCataItem = m_Area_Texture_List.InsertItem(RockType[i],1,1,hRoot,TVI_LAST);
		m_Dir = g_sceneDataPath.c_str() + tmp + topItem + tmp + RockType[i];
		if(1)
		{
			// ��ȡ�ļ���������ָ�������ļ�
			_finddata_t fileDir;
			char* dir= new char[m_Dir.GetLength()+ strlen("\\*.BMP")];
			sprintf(dir, m_Dir+"\\*.BMP"); 
			long lfDir;
			int fileNum = 0;
			//������ָ�����ļ�����ƥ��ĵ�һ��ʵ�������ɹ��򷵻ص�һ��ʵ���ľ�������򷵻�-1L
			if((lfDir = _findfirst(dir,&fileDir))==-1l)
				printf("No file is found\n");
			else{
				printf("file list:\n");
				do{
					printf("%s\n",fileDir.name);// XXX.format
					hArtItem = m_Area_Texture_List.InsertItem(fileDir.name,2,2,hCataItem,TVI_LAST);
					++fileNum;
				}while( _findnext( lfDir, &fileDir ) == 0 );
			}
			_findclose(lfDir);
		}

	}

	return TRUE;

 
}


//void CAreaClassification::OnMenuUpdateAreaTexture()
//{
//	// TODO: �ڴ���������������
//
//}


//void CAreaClassification::OnMenuAreaDelete()
//{
//	// TODO: �ڴ���������������
//}
