#pragma once
#include "afxwin.h"





// CProjectFileSetting 对话框

class CProjectFileSetting : public CDialog {
    DECLARE_DYNAMIC(CProjectFileSetting)

  public:
    CProjectFileSetting(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CProjectFileSetting();

    // 对话框数据
    enum { IDD = IDD_PROJECTFILESETTING };

  protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()

  public:
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnBnClickedRadioNewProject();

    afx_msg void OnBnClickedRadioOpenProject();
    CListBox m_recentlyOpenedProjectList;

    unsigned int new_project_flag;


    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangeListRecentlyOpenedProject();
};
