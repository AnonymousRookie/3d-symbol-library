#include "stdafx.h"
#include "3DSymbolLibNew.h"
#include "ProjectFileSetting.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "GlobalVariable.h"
// CProjectFileSetting 对话框

IMPLEMENT_DYNAMIC(CProjectFileSetting, CDialog)

CProjectFileSetting::CProjectFileSetting(CWnd* pParent /*=NULL*/)
    : CDialog(CProjectFileSetting::IDD, pParent) {
    new_project_flag = 1;
}

CProjectFileSetting::~CProjectFileSetting() {
}

void CProjectFileSetting::DoDataExchange(CDataExchange* pDX) {
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


// CProjectFileSetting 消息处理程序





void CProjectFileSetting::OnBnClickedOk() {
    // TODO(jason): 在此添加控件通知处理程序代码
    CDialog::OnOK();
    CMainFrame* pMF = (CMainFrame*)AfxGetApp()->m_pMainWnd;  // 先通过获取当前框架指针
    CView* active = pMF->GetActiveView();  // 才能获取当前视类指针
    if (active != NULL)  // 获取了当前视类指针才能发送消息
        active->PostMessage(WM_PROJECT_SET_OK, new_project_flag, 0);  // 使用PostMessage发送消息
}


void CProjectFileSetting::OnBnClickedCancel() {
    // TODO(jason): 在此添加控件通知处理程序代码
    CDialog::OnCancel();
}


// 单选按钮 新建工程 点击消息的消息处理函数
void CProjectFileSetting::OnBnClickedRadioNewProject() {
    // TODO(jason): 在此添加控件通知处理程序代码
    m_recentlyOpenedProjectList.EnableWindow(FALSE);
    new_project_flag = 1;
}

// 单选按钮 打开工程 点击消息的消息处理函数
void CProjectFileSetting::OnBnClickedRadioOpenProject() {
    // TODO(jason): 在此添加控件通知处理程序代码
    m_recentlyOpenedProjectList.EnableWindow(TRUE);
    new_project_flag = 0;
}




BOOL CProjectFileSetting::OnInitDialog() {
    CDialog::OnInitDialog();
    // 默认新建工程
    CheckDlgButton(IDC_RADIO_NEW_PROJECT, 1);
    CheckDlgButton(IDC_RADIO_OPEN_PROJECT, 0);
    m_recentlyOpenedProjectList.EnableWindow(FALSE);
    // list box
    for (int32 i = 0; i < g_strRecentOpenedFileArray.GetSize(); ++i) {
        int32 pos_begin = 0;
        int32 pos_end = 0;
        int32 tmp_len = g_strRecentOpenedFileArray.GetAt(i).GetLength();
        int32 pos = 0;
        int32 count = 0;
        while (pos != -1) {
            pos = g_strRecentOpenedFileArray.GetAt(i).Find('\\', pos + 1);
            if (pos != -1) {
                count++;
                if (count == 2) {
                    pos_begin = pos;
                }
                pos_end = pos;
            }
        }
        // 路径目录超过3层，中间以"..."连接
        if (count > 2) {
            CString str_left = g_strRecentOpenedFileArray.GetAt(i).Left(pos_begin + 1);
            CString str_right = g_strRecentOpenedFileArray.GetAt(i).Right(tmp_len - pos_end);
            CString tmpStr = str_left + "..." + str_right;
            if (tmpStr.Right(4) == _T(".prj"))
                m_recentlyOpenedProjectList.AddString(tmpStr);
        } else {
            if (g_strRecentOpenedFileArray.GetAt(i).Right(4) == _T(".prj"))
                m_recentlyOpenedProjectList.AddString(g_strRecentOpenedFileArray.GetAt(i));
        }
    }
    g_recentlyOpenedProjectName = _T("更多工程...");
    m_recentlyOpenedProjectList.AddString(_T("更多工程..."));
    // 默认选中最后一项 "更多工程..."
    int32 listCount = m_recentlyOpenedProjectList.GetCount();
    m_recentlyOpenedProjectList.SetCurSel(listCount - 1);
    return TRUE;  // return TRUE unless you set the focus to a control
}


// 选中项改变时, 响应消息
void CProjectFileSetting::OnSelchangeListRecentlyOpenedProject() {
    // TODO(jason): 在此添加控件通知处理程序代码
    CString strText = "";
    int32 nCurSel = -1;
    nCurSel = m_recentlyOpenedProjectList.GetCurSel();      // 获取当前选中列表项
    int32 listCount = m_recentlyOpenedProjectList.GetCount();
    if (nCurSel != listCount - 1) {
        g_recentlyOpenedProjectName = g_strRecentOpenedFileArray.GetAt(nCurSel);
    } else {
        nCurSel = m_recentlyOpenedProjectList.GetCurSel();      // 获取当前选中列表项
        m_recentlyOpenedProjectList.GetText(nCurSel, strText);  // 获取选中列表项的字符串
        g_recentlyOpenedProjectName = strText;  // 选中的最近打开的工程文件名
    }
}
