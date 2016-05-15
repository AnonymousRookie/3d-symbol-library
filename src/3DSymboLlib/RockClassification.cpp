/************************************************************************/
/*      ��ʯ����Ի�����													*/
/************************************************************************/
#include "stdafx.h"
#include "3DSymbolLibNew.h"
#include "RockClassification.h"
#include "afxdialogex.h"

#include <io.h>
// CRockClassification �Ի���

IMPLEMENT_DYNAMIC(CRockClassification, CDialog)

CRockClassification::CRockClassification(CWnd* pParent /*=NULL*/)
	: CDialog(CRockClassification::IDD, pParent)
{

}

CRockClassification::~CRockClassification()
{
}

void CRockClassification::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_ROCK_LIST, m_Rock_Tree_List);
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_image);
}


BEGIN_MESSAGE_MAP(CRockClassification, CDialog)
	 
	ON_BN_CLICKED(IDOK, &CRockClassification::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CRockClassification::OnBnClickedCancel)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_ROCK_LIST, &CRockClassification::OnSelchangedTreeRockList)
END_MESSAGE_MAP()


// CRockClassification ��Ϣ�������


BOOL CRockClassification::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString tmp = "\\";
	CString topItem = "��ʯ����";
	CString RockType[3] = {"�ҽ���","������","������"};

	hRoot = m_Rock_Tree_List.InsertItem(topItem,0,0);

	for(int i=0;i<3;++i)
	{
		hCataItem = m_Rock_Tree_List.InsertItem(RockType[i],1,1,hRoot,TVI_LAST);
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
					hArtItem = m_Rock_Tree_List.InsertItem(fileDir.name,2,2,hCataItem,TVI_LAST);
					++fileNum;
				}while( _findnext( lfDir, &fileDir ) == 0 );
			}
			_findclose(lfDir);
		}

	}
	
	return TRUE;
}
 


void CRockClassification::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();

	CString tmp = "\\";
	CString topItem = "��ʯ����";
	HTREEITEM selectItem = m_Rock_Tree_List.GetSelectedItem();
	CString selectItemText = m_Rock_Tree_List.GetItemText(selectItem);
	HTREEITEM parentItem = m_Rock_Tree_List.GetParentItem(selectItem);
	CString parentItemText = m_Rock_Tree_List.GetItemText(parentItem);

	m_selectItem = selectItemText;
	m_Dir = g_sceneDataPath.c_str() + tmp + topItem + tmp + parentItemText;
}


void CRockClassification::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}


void CRockClassification::OnSelchangedTreeRockList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	HTREEITEM selectItem = m_Rock_Tree_List.GetSelectedItem();
	CString selectItemText = m_Rock_Tree_List.GetItemText(selectItem);

	HTREEITEM parentItem = m_Rock_Tree_List.GetParentItem(selectItem);
	CString parentItemText = m_Rock_Tree_List.GetItemText(parentItem);


	CString topItem = "��ʯ����";
	CString RockType[3] = {"�ҽ���","������","������"};
	CString imgPathAndName;
	CString tmp = "\\";
	for(int i=0;i<3;++i)
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
void CRockClassification::drawBitmapFromFile(CString bitmapFilePath,CDC*pDC,CRect rect)
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


