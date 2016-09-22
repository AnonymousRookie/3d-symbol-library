#ifndef SKY_BOX_TEX_LOAD_H
#define SKY_BOX_TEX_LOAD_H

#include "Base/ZTypes.h"

// CSkyBoxTexLoad 对话框

class CSkyBoxTexLoad : public CDialog {
    DECLARE_DYNAMIC(CSkyBoxTexLoad)

  public:
    explicit CSkyBoxTexLoad(CWnd* pParent = NULL);
    virtual ~CSkyBoxTexLoad();

    // 对话框数据
    enum { IDD = IDD_DIALOG_SKYBOX };

  protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()
  public:
    CString m_SkyBoxTexTP;
    CString m_SkyBoxTexLF;
    CString m_SkyBoxTexBK;
    CString m_SkyBoxTexRT;
    CString m_SkyBoxTexFR;
    afx_msg void OnBnClickedButtonSkyTp();
    afx_msg void OnBnClickedButtonSkyLf();
    afx_msg void OnBnClickedButtonSkyBk();
    afx_msg void OnBnClickedButtonSkyRt();
    afx_msg void OnBnClickedButtonSkyFr();
};

#endif  // SKY_BOX_TEX_LOAD_H