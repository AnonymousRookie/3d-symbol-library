#ifndef SYSTEM_SETTING_H
#define SYSTEM_SETTING_H

#include "define.h"
/************************************************************************/
/* 系统设置对话框                                                         */
/************************************************************************/

class CSystemSetting : public CDialog {
    DECLARE_DYNAMIC(CSystemSetting)

  public:
    explicit CSystemSetting(CWnd* pParent = NULL);
    virtual ~CSystemSetting();

    // 对话框数据
    enum { IDD = IDD_SYSTEMSETTING };

  protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()
  public:
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnBnClickedButtonChangePath();
    CString m_SceneDataPATH;
    virtual BOOL OnInitDialog();
};

#endif  // SYSTEM_SETTING_H