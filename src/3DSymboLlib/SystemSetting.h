#pragma once

/************************************************************************/
/* ϵͳ���öԻ���	��														*/
/************************************************************************/

class CSystemSetting : public CDialog
{
	DECLARE_DYNAMIC(CSystemSetting)

public:
	CSystemSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSystemSetting();

// �Ի�������
	enum { IDD = IDD_SYSTEMSETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonChangePath();
	CString m_SceneDataPATH;
	virtual BOOL OnInitDialog();
};
