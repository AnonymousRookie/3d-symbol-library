// ModelListConfigureDialog.cpp : ʵ���ļ�

#include "stdafx.h"
#include "3DSymbolLibNew.h"
#include "ModelListConfigureDialog.h"
#include "afxdialogex.h"
#include "GlobalVariable.h"

// ModelListConfigureDialog �Ի���

// �º���,���ڱȽ��ַ�����С,��List��������
class MyCompare
{
public:
	bool operator()(const string str1,const string str2)
	{
		return (str1 < str2);
	}
};

IMPLEMENT_DYNAMIC(ModelListConfigureDialog, CDialog)

ModelListConfigureDialog::ModelListConfigureDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ModelListConfigureDialog::IDD, pParent)
{
	// Empty
}

ModelListConfigureDialog::~ModelListConfigureDialog()
{
	// Empty
}

void ModelListConfigureDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_CONGIGURE_MODELLIST, m_configureModeListTree);
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_image);
}


BEGIN_MESSAGE_MAP(ModelListConfigureDialog, CDialog)
	ON_BN_CLICKED(IDOK, &ModelListConfigureDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ModelListConfigureDialog::OnBnClickedCancel)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_DELETE_SYMBOL, &ModelListConfigureDialog::OnEditDeleteSymbol)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_CONGIGURE_MODELLIST, &ModelListConfigureDialog::OnTvnSelchangedTreeCongigureModellist)
	ON_COMMAND(ID_EDIT_ADD_SYMBOL, &ModelListConfigureDialog::OnEditAddSymbol)
END_MESSAGE_MAP()


// ModelListConfigureDialog ��Ϣ�������


void ModelListConfigureDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for(int i=0;i<g_modelKindNumber;++i)
	{
		// Update only changed
		if(g_modelTree[i].isChanged)
		{
			CoInitialize(NULL); // ��ʼ��COM��
			CComPtr<IXMLDOMDocument> spXMLDOM;
			// ����������ʵ����
			HRESULT hr = spXMLDOM.CoCreateInstance (_uuidof(DOMDocument));
			VARIANT_BOOL bSuccess = false;
			// װ��XML�ĵ���
			hr = spXMLDOM->load(CComVariant(g_point_symbolConfigureFile.c_str()),&bSuccess);
		
			int strLen = g_modelTree[i]._noteDirectory.length();
			// "/root/XXX/*" ==> "/root/XXX"
			string subStr = g_modelTree[i]._noteDirectory.substr(0,strLen-2);

			CComBSTR bstrSS(subStr.c_str());
			CComPtr<IXMLDOMNode> spDevice;
			hr = spXMLDOM->selectSingleNode(bstrSS,&spDevice); //����bstrSS��
	
			CComPtr<IXMLDOMElement> spRootEle;
			spXMLDOM->get_documentElement(&spRootEle); //���ڵ�
			CComPtr<IXMLDOMNodeList> spNodeList;
			
			spRootEle->selectNodes(_bstr_t(g_modelTree[i]._noteDirectory.c_str()),&spNodeList);

			long nLen;//�ӽڵ���
			spNodeList->get_length(&nLen); //�ӽڵ���
			for (long j = 0; j != nLen; ++j) //�����ӽڵ�
			{
				CComPtr<IXMLDOMNode> spNode;
				spNodeList->get_item(j, &spNode);
				// ɾ�������ӽڵ�(item)
				spDevice->removeChild(spNode,NULL);
			}
		
			// ��List����ӽ��
			list<string>::iterator iter;
			for(iter=g_modelList[i].begin();iter!=g_modelList[i].end();++iter)
			{
				CComPtr<IXMLDOMNode> spModelNode;
				// ����"Model"�ڵ㡣
				hr = spXMLDOM->createNode(CComVariant(NODE_ELEMENT),CComBSTR("item"),NULL,& spModelNode);
				CComPtr<IXMLDOMNode> spInsertedNode;
				hr = spDevice->appendChild (spModelNode,&spInsertedNode);
				CString strID=(*iter).c_str();
				// ����"Model"���ı���
				spInsertedNode->put_text(strID.AllocSysString());
			}
			
			//�����ĵ���
			spXMLDOM->save(CComVariant(g_point_symbolConfigureFile.c_str()));
			// ������COM��ʹ�á�
			CoUninitialize();
		}
	}
	
	CDialog::OnOK();
}


/************************************************************************/
/* Function: ȡ����ʱ��List�б�ɾ����Ԫ�����²���							*/
/************************************************************************/
void ModelListConfigureDialog::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	for(int i=0;i<g_modelKindNumber;++i)
	{
		//add
		list<string>::iterator iter_del;
		for(iter_del=g_delList[i].begin();iter_del!=g_delList[i].end();++iter_del)
		{
			g_modelList[i].push_back(*iter_del);
		}
		g_delList[i].clear();

		//delete
		list<string>::iterator iter_add = g_delList[i].begin();
		while(iter_add != g_delList[i].end())
		{
			iter_add = g_delList[i].erase(iter_add);
		}
		g_addList[i].clear();

	}
	

	CDialog::OnCancel();
}


BOOL ModelListConfigureDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	//============================================
	// ��list�ж�ȡ��Ϣ��ʾ��tree��
	//============================================
	for(int i=0;i<g_modelKindNumber;++i)
	{
		g_modelTree[i].isChanged = 0;
		// ����
		g_modelList[i].sort(MyCompare());
	}


	hRoot = m_configureModeListTree.InsertItem("�����б�����",0,0);
 
	
	LPCTSTR item[5];	// {"3DS Model","City Symbol","Tree Model","3D Tree Model","Weather Symbol"};
	
	for(int i=0;i<g_modelKindNumber;++i)
	{
		item[i] = g_modelTree[i]._item.c_str();
	}

	for(int i=0;i<g_modelKindNumber;++i)
	{
		hCataItem = m_configureModeListTree.InsertItem(item[i],1,1,hRoot,TVI_LAST);
		list<string>::iterator iter;
		for(iter=g_modelList[i].begin();iter!=g_modelList[i].end();++iter)
		{
			hArtItem = m_configureModeListTree.InsertItem((*iter).c_str(),2,2,hCataItem,TVI_LAST);
		}
	}
	return TRUE;
}


/************************************************************************/
/* Function: �����˵�													*/
/************************************************************************/
void ModelListConfigureDialog::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: �ڴ˴������Ϣ����������
	if (point != CPoint(-1, -1))
	{
		CPoint ptTree = point;
		m_configureModeListTree.ScreenToClient(&ptTree);
		UINT flags = 0;
		HTREEITEM hTreeItem = m_configureModeListTree.HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			m_configureModeListTree.SelectItem(hTreeItem);
			CMenu menu;
			menu.LoadMenu(IDR_MENU_POPUP_CONFIGURE_EDIT);
			CMenu * pMenu = menu.GetSubMenu(0);
			m_configureModeListTree.SetFocus();	

			//========================================================
			HTREEITEM selectedItem = m_configureModeListTree.GetSelectedItem();
			HTREEITEM selectedParentItem = m_configureModeListTree.GetParentItem(selectedItem);
			HTREEITEM rootItem = m_configureModeListTree.GetRootItem();
			if(rootItem == selectedParentItem)
			{
				//MessageBox("�����ڵ�","",MB_OK);
				pMenu->EnableMenuItem(ID_EDIT_DELETE_SYMBOL, MF_DISABLED|MF_GRAYED);
			}
			if(rootItem == m_configureModeListTree.GetParentItem(selectedParentItem))
			{
				pMenu->EnableMenuItem(ID_EDIT_ADD_SYMBOL, MF_DISABLED|MF_GRAYED);
				//MessageBox("3���ڵ�","",MB_OK);
			}
			if(rootItem == selectedItem)
			{
				//MessageBox("���ڵ�","",MB_OK);
				pMenu->EnableMenuItem(ID_EDIT_ADD_SYMBOL, MF_DISABLED|MF_GRAYED);
				pMenu->EnableMenuItem(ID_EDIT_DELETE_SYMBOL, MF_DISABLED|MF_GRAYED);
			}
			//========================================================

			pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	
		}
	}
}


/************************************************************************/
/* Function: tree control ���һ��˵���delete								*/
/************************************************************************/
void ModelListConfigureDialog::OnEditDeleteSymbol()
{
	// TODO: �ڴ���������������
	HTREEITEM selectItem = m_configureModeListTree.GetSelectedItem();
	
	CString selectItemText = m_configureModeListTree.GetItemText(selectItem);

	HTREEITEM parentItem = m_configureModeListTree.GetParentItem(selectItem);

	CString parentItemText = m_configureModeListTree.GetItemText(parentItem);

	// delete from tree control
	m_configureModeListTree.DeleteItem(selectItem);

	for(int i=0;i<g_modelKindNumber;++i)
	{
		if(parentItemText == g_modelTree[i]._item.c_str())
		{
			list<string>::iterator iter = g_modelList[i].begin();
			while(iter != g_modelList[i].end())
			{
				if((*iter).c_str() == selectItemText)
				{
					// delete from model list
					iter = g_modelList[i].erase(iter);

					list<string>::iterator tmpIter;
					for(tmpIter=g_addList[i].begin();tmpIter!=g_addList[i].end();)
					{
						if((*tmpIter).c_str() == selectItemText)
						{
							tmpIter = g_addList[i].erase(tmpIter);
						}
						else
							++tmpIter;
					}
					if(tmpIter==g_addList[i].end())
					{
						g_delList[i].push_back(LPCSTR(selectItemText));
					}

					
					g_modelTree[i].isChanged = 1;
				}
				else
				{
					++iter;
				}
			}
			
		}
	}
}


/************************************************************************/
/* Function: tree control ���һ��˵���add									*/
/************************************************************************/
void ModelListConfigureDialog::OnEditAddSymbol()
{
	// TODO: �ڴ���������������

	HTREEITEM selectItem = m_configureModeListTree.GetSelectedItem();
	
	CString selectItemText = m_configureModeListTree.GetItemText(selectItem);

	// �ļ��Ի������,��ʽ������,Ĭ��·��
	CString l_title,l_filter,l_initialDir;
	CString l_tmp = "\\";
	int l_symbolType = -1;
	if(selectItemText == g_modelTree[0]._item.c_str())
	{
		l_symbolType = 0;
		l_title = "���3DSģ��";
		l_filter = "3DSģ��(*.BMP)|*.BMP|";
		l_initialDir = g_sceneDataPath.c_str() + l_tmp + g_symbolFolder._3DSFolder.c_str();
	}
	if(selectItemText == g_modelTree[1]._item.c_str())
	{
		l_symbolType = 1;
		l_title = "��ӳ��з���";
		l_filter = "���з���(*.png)|*.png|";
		l_initialDir = g_sceneDataPath.c_str() + l_tmp + g_symbolFolder._CityFolder.c_str();
	}
	if(selectItemText == g_modelTree[2]._item.c_str())
	{
		l_symbolType = 2;
		l_title = "��Ӿ�����";
		l_filter = "������(*.BMP)|*.BMP|";
		l_initialDir = g_sceneDataPath.c_str() + l_tmp + g_symbolFolder._TreeFolder.c_str();
	}
	if(selectItemText == g_modelTree[3]._item.c_str())
	{
		l_symbolType = 3;
		l_title = "���3D������";
		l_filter = "3D������(*.BMP)|*.BMP|";
		l_initialDir = g_sceneDataPath.c_str() + l_tmp + g_symbolFolder._3DTreeFolder.c_str();
	}
	if(selectItemText == g_modelTree[4]._item.c_str())
	{
		l_symbolType = 4;
		l_title = "�����������";
		l_filter = "��������(*.BMP)|*.BMP|";
		l_initialDir = g_sceneDataPath.c_str() + l_tmp + g_symbolFolder._WeatherFolder.c_str();
	}
	
	CString file;
	CFileDialog FileDialog(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,l_filter,NULL);
	
	// Ĭ�ϴ������е��ļ�·��
	FileDialog.m_ofn.lpstrInitialDir = l_initialDir;

	FileDialog.m_ofn.lpstrTitle = l_title;	

	if((FileDialog.DoModal()==IDOK) && (l_symbolType!=-1))
	{
		file = FileDialog.GetFileName();
		
		int index = file.Find('.');
		
		CString ret = file.Left(index);

		list<string>::iterator iter = g_modelList[l_symbolType].begin();
		while(iter != g_modelList[l_symbolType].end())
		{
			if((*iter).c_str() == ret)
			{
				MessageBox("�벻Ҫ�ظ������ͬ�ķ���!","Warning",MB_OK);
				return;
			}
			else
			{
				++iter;
			}
		}
		if(iter == g_modelList[l_symbolType].end())
		{
			g_modelList[l_symbolType].push_back(LPCSTR(ret));

			list<string>::iterator tmpIter;
			for(tmpIter=g_delList[l_symbolType].begin();tmpIter!=g_delList[l_symbolType].end();)
			{
				if((*tmpIter).c_str() == ret)
				{
					tmpIter = g_delList[l_symbolType].erase(tmpIter);
				}
				else
					++tmpIter;
			}
			if(tmpIter==g_delList[l_symbolType].end())
			{
				g_addList[l_symbolType].push_back(LPCSTR(ret));
			}
			
			m_configureModeListTree.InsertItem(ret,2,2,selectItem,TVI_LAST);
			g_modelTree[l_symbolType].isChanged = 1;
		}
	}
}


/************************************************************************/
/* Function: ��Ӧѡ�иı��¼�,��ʾ��Ӧ��ͼƬ								*/
/************************************************************************/
void ModelListConfigureDialog::OnTvnSelchangedTreeCongigureModellist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	*pResult = 0;
 

	HTREEITEM selectItem = m_configureModeListTree.GetSelectedItem();
	CString selectItemText = m_configureModeListTree.GetItemText(selectItem);

	HTREEITEM parentItem = m_configureModeListTree.GetParentItem(selectItem);
	CString parentItemText = m_configureModeListTree.GetItemText(parentItem);

	CString imgPathAndName;
	CString tmp = "\\";
	for(int i=0;i<g_modelKindNumber;++i)
	{
		if(parentItemText == g_modelTree[i]._item.c_str())
		{
			if(0 == i)
			{
				imgPathAndName = g_sceneDataPath.c_str() + tmp + g_symbolFolder._3DSFolder.c_str() + tmp + selectItemText + ".bmp";
				//MessageBox(imgPathAndName,"");
			}
			// PNG
			else if(1 == i)
			{
				imgPathAndName = g_sceneDataPath.c_str() + tmp + g_symbolFolder._CityFolder.c_str() + tmp + selectItemText + ".png";
				//MessageBox(imgPathAndName,"");

				GetDlgItem(IDC_STATIC_IMAGE)->GetParent()->RedrawWindow();

				CWnd* pWnd;
				pWnd=GetDlgItem(IDC_STATIC_IMAGE);//�����ǻ�ÿؼ����
				CDC* pDC=pWnd->GetDC();
				HDC hDC = pDC->m_hDC;
 
				CRect rect_frame;
				pWnd->GetClientRect(&rect_frame);

				CImage image;
				image.Load(imgPathAndName);
 
				::SetStretchBltMode(hDC,HALFTONE);
				::SetBrushOrgEx(hDC,0,0,NULL);
 
				image.Draw(hDC,rect_frame);
				ReleaseDC(pDC);//�ͷ�picture�ؼ���DC
			}
			else if(2 == i)
			{
				imgPathAndName = g_sceneDataPath.c_str() + tmp + g_symbolFolder._TreeFolder.c_str() + tmp + selectItemText + ".bmp";
				//MessageBox(imgPathAndName,"");
			}
			else if(3 == i)
			{
				imgPathAndName = g_sceneDataPath.c_str() + tmp + g_symbolFolder._3DTreeFolder.c_str() + tmp + selectItemText + ".bmp";
				//MessageBox(imgPathAndName,"");
			}
			else if(4 == i)
			{
				imgPathAndName = g_sceneDataPath.c_str() + tmp + g_symbolFolder._WeatherFolder.c_str() + tmp + selectItemText + ".bmp";
				//MessageBox(imgPathAndName,"");
			}
			// BMP
			if(i != 1)
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


/************************************************************************/
/* Function: ��ѡ�е�bmp����Ӱ���ڿؼ��ϻ���								*/
/************************************************************************/
void ModelListConfigureDialog::drawBitmapFromFile(CString bitmapFilePath,CDC*pDC,CRect rect)
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



