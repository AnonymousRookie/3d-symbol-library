/************************************************************************/
/* 系统设置对话框   类                                                      */
/************************************************************************/

#include "stdafx.h"
#include "3DSymbolLibNew.h"
#include "SystemSetting.h"
#include "afxdialogex.h"


// CSystemSetting 对话框

IMPLEMENT_DYNAMIC(CSystemSetting, CDialog)

CSystemSetting::CSystemSetting(CWnd* pParent /*=NULL*/)
    : CDialog(CSystemSetting::IDD, pParent)
    , m_SceneDataPATH(_T("")) {
    // Empty
}

CSystemSetting::~CSystemSetting() {
    // Empty
}

void CSystemSetting::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_SCENE_DATA_PATH, m_SceneDataPATH);
}


BEGIN_MESSAGE_MAP(CSystemSetting, CDialog)
    ON_BN_CLICKED(IDOK, &CSystemSetting::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &CSystemSetting::OnBnClickedCancel)
    ON_BN_CLICKED(IDC_BUTTON_CHANGE_PATH, &CSystemSetting::OnBnClickedButtonChangePath)
END_MESSAGE_MAP()


// CSystemSetting 消息处理程序


void CSystemSetting::OnBnClickedOk() {
    // TODO: 在此添加控件通知处理程序代码
    g_sceneDataPath = m_SceneDataPATH;
    char sceneDir[256];
    GetCurrentDirectoryA(256, sceneDir);
    g_systemConfigureFile = strcat(sceneDir, "\\system.ini");
    CFileFind finder;
    BOOL isFind = finder.FindFile(g_systemConfigureFile.c_str());
    if (!isFind) {
        MessageBox("Can not find configure file!", "warning", MB_OK);
    } else {
        ::WritePrivateProfileStringA("SceneDataPath", "path", m_SceneDataPATH, g_systemConfigureFile.c_str());
    }
    CDialog::OnOK();
}


void CSystemSetting::OnBnClickedCancel() {
    // TODO: 在此添加控件通知处理程序代码
    CDialog::OnCancel();
}


void CSystemSetting::OnBnClickedButtonChangePath() {
    // TODO: 在此添加控件通知处理程序代码
    char szPath[MAX_PATH];     //存放选择的目录路径
    CString str;
    ZeroMemory(szPath, sizeof(szPath));
    BROWSEINFO bi;
    bi.hwndOwner = m_hWnd;
    bi.pidlRoot = NULL;
    bi.pszDisplayName = szPath;
    bi.lpszTitle = "请选择场景数据文件所在的目录";
    bi.ulFlags = 0;
    bi.lpfn = NULL;
    bi.lParam = 0;
    bi.iImage = 0;
    //弹出选择目录对话框
    LPITEMIDLIST lp = SHBrowseForFolder(&bi);
    if (lp && SHGetPathFromIDList(lp, szPath)) {
        str.Format("选择的目录为 %s",  szPath);
        //AfxMessageBox(str);
        m_SceneDataPATH = szPath;
        UpdateData(FALSE);
    }
}

BOOL CSystemSetting::OnInitDialog() {
    CDialog::OnInitDialog();
    m_SceneDataPATH = CString(g_sceneDataPath.c_str());
    UpdateData(FALSE);
    return TRUE;
}
