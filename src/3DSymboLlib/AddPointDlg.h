#ifndef ADD_POINT_DLG_H
#define ADD_POINT_DLG_H

#include "define.h"

// CAddPointDlg 对话框

class CAddPointDlg : public CDialog {
    DECLARE_DYNAMIC(CAddPointDlg)

  public:
    explicit CAddPointDlg(CWnd* pParent = NULL);
    virtual ~CAddPointDlg();

    // 对话框数据
    enum { IDD = IDD_ADDPOINTDLG };

  protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()
};

#endif  // ADD_POINT_DLG_H