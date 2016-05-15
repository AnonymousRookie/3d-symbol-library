#pragma once


// CSkyBoxTexLoad 对话框

class CSkyBoxTexLoad : public CDialog {
    DECLARE_DYNAMIC(CSkyBoxTexLoad)

  public:
    CSkyBoxTexLoad(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CSkyBoxTexLoad();

    // 对话框数据
    enum { IDD = IDD_DIALOG_SKYBOX };

  protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
