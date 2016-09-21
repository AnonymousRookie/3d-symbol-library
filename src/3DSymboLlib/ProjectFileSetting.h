#ifndef PROJECT_FILE_SETTING_H
#define PROJECT_FILE_SETTING_H

#include "afxwin.h"
#include "define.h"

// CProjectFileSetting 对话框

class CProjectFileSetting : public CDialog {
    DECLARE_DYNAMIC(CProjectFileSetting)

  public:
    explicit CProjectFileSetting(CWnd* pParent = NULL);
    virtual ~CProjectFileSetting();

    // 对话框数据
    enum { IDD = IDD_PROJECTFILESETTING };

  protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()

  public:
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnBnClickedRadioNewProject();

    afx_msg void OnBnClickedRadioOpenProject();
    CListBox m_recentlyOpenedProjectList;

    uint32 new_project_flag;


    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangeListRecentlyOpenedProject();
};

#endif  // PROJECT_FILE_SETTING_H