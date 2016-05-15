// ProjectFileSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DSymbolLibNew.h"
#include "ProjectFileSetting.h"
#include "afxdialogex.h"
 
#include "MainFrm.h"
#include "GlobalVariable.h"
// CProjectFileSetting �Ի���

IMPLEMENT_DYNAMIC(CProjectFileSetting, CDialog)

CProjectFileSetting::CProjectFileSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectFileSetting::IDD, pParent)
{
	new_project_flag = 1;
}

CProjectFileSetting::~CProjectFileSetting()
{
}

void CProjectFileSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RECENTLY_OPENED_PROJECT, m_recentlyOpenedProjectList);
}


BEGIN_MESSAGE_MAP(CProjectFileSetting, CDialog)
	ON_BN_CLICKED(IDOK, &CProjectFileSetting::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CProjectFileSetting::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RADIO_NEW_PROJECT, &CProjectFileSetting::OnBnClickedRadioNewProject)
	ON_BN_CLICKED(IDC_RADIO_OPEN_PROJECT, &CProjectFileSetting::OnBnClickedRadioOpenProject)


	ON_LBN_SELCHANGE(IDC_LIST_RECENTLY_OPENED_PROJECT, &CProjectFileSetting::OnSelchangeListRecentlyOpenedProject)
END_MESSAGE_MAP()


// CProjectFileSetting ��Ϣ�������





void CProjectFileSetting::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();

	CMainFrame* pMF=(CMainFrame*)AfxGetApp()->m_pMainWnd;  //��ͨ����ȡ��ǰ���ָ��
	CView * active = pMF->GetActiveView();//���ܻ�ȡ��ǰ����ָ��
	if(active != NULL)  //��ȡ�˵�ǰ����ָ����ܷ�����Ϣ
	active->PostMessage(WM_PROJECT_SET_OK,new_project_flag,0);   //ʹ��PostMessage������Ϣ
}


void CProjectFileSetting::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}


// ��ѡ��ť �½����� �����Ϣ����Ϣ������
void CProjectFileSetting::OnBnClickedRadioNewProject()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_recentlyOpenedProjectList.EnableWindow(FALSE);
	new_project_flag = 1;
}

// ��ѡ��ť �򿪹��� �����Ϣ����Ϣ������
void CProjectFileSetting::OnBnClickedRadioOpenProject()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_recentlyOpenedProjectList.EnableWindow(TRUE);
	new_project_flag = 0;
}




BOOL CProjectFileSetting::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Ĭ���½�����
	CheckDlgButton(IDC_RADIO_NEW_PROJECT, 1);
	CheckDlgButton(IDC_RADIO_OPEN_PROJECT, 0);

	m_recentlyOpenedProjectList.EnableWindow(FALSE);
	
	//list box

	for(int i=0;i<g_strRecentOpenedFileArray.GetSize();++i)
	{
		int pos_begin = 0;
		int pos_end = 0;

		int tmp_len = g_strRecentOpenedFileArray.GetAt(i).GetLength();
		int pos = 0;
		int count = 0;
		while(pos != -1)
		{
			pos = g_strRecentOpenedFileArray.GetAt(i).Find('\\',pos+1);
			if(pos != -1)
			{
				count++;
				if(count == 2)
				{
					pos_begin = pos;
				}
				pos_end = pos;
			}
		}
		// ·��Ŀ¼����3�㣬�м���"..."����
		if(count > 2)
		{
			CString str_left = g_strRecentOpenedFileArray.GetAt(i).Left(pos_begin+1);
			CString str_right = g_strRecentOpenedFileArray.GetAt(i).Right(tmp_len-pos_end);

			CString tmpStr = str_left + "..." + str_right;

			if(tmpStr.Right(4) == _T(".prj"))
				m_recentlyOpenedProjectList.AddString(tmpStr);
		}
		else
		{
			if(g_strRecentOpenedFileArray.GetAt(i).Right(4) == _T(".prj"))
				m_recentlyOpenedProjectList.AddString(g_strRecentOpenedFileArray.GetAt(i));
		}
	}
	
	
	g_recentlyOpenedProjectName = _T("���๤��...");
	m_recentlyOpenedProjectList.AddString(_T("���๤��..."));
	
	

	// Ĭ��ѡ�����һ�� "���๤��..."
	int listCount = m_recentlyOpenedProjectList.GetCount();
	m_recentlyOpenedProjectList.SetCurSel(listCount-1);

	return TRUE;  // return TRUE unless you set the focus to a control

}


// ѡ����ı�ʱ, ��Ӧ��Ϣ
void CProjectFileSetting::OnSelchangeListRecentlyOpenedProject()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strText = "";
	int nCurSel = -1;
	nCurSel = m_recentlyOpenedProjectList.GetCurSel();		//��ȡ��ǰѡ���б���


	int listCount = m_recentlyOpenedProjectList.GetCount();
	if(nCurSel != listCount-1)
	{
		g_recentlyOpenedProjectName = g_strRecentOpenedFileArray.GetAt(nCurSel);
	}
	else
	{
		nCurSel = m_recentlyOpenedProjectList.GetCurSel();		//��ȡ��ǰѡ���б���
		m_recentlyOpenedProjectList.GetText(nCurSel, strText);	//��ȡѡ���б�����ַ���
		g_recentlyOpenedProjectName = strText;	// ѡ�е�����򿪵Ĺ����ļ���
	}
}
