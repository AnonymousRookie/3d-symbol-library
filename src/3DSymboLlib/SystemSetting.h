#pragma once

/************************************************************************/
/* 系统设置对话框	类														*/
/************************************************************************/

class CSystemSetting : public CDialog
{
	DECLARE_DYNAMIC(CSystemSetting)

public:
	CSystemSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSystemSetting();

// 对话框数据
	enum { IDD = IDD_SYSTEMSETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonChangePath();
	CString m_SceneDataPATH;
	virtual BOOL OnInitDialog();
};
