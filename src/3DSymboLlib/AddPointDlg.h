#pragma once
#include "define.h"

// CAddPointDlg 对话框

class CAddPointDlg : public CDialog {
    DECLARE_DYNAMIC(CAddPointDlg)

  public:
    CAddPointDlg(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CAddPointDlg();

    // 对话框数据
    enum { IDD = IDD_ADDPOINTDLG };

  protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
};
