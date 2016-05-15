#pragma once


// CCameraParamSet 对话框

class CCameraParamSet : public CDialog
{
	DECLARE_DYNAMIC(CCameraParamSet)

public:
	CCameraParamSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCameraParamSet();

// 对话框数据
	enum { IDD = IDD_DIALOG_CAMERA_PARAM_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_DerAngleY, m_OriginDerAngleY;
	float m_DerAngleZ, m_OriginDerAngleZ;

	afx_msg void OnBnClickedButtonRecoverY();
	afx_msg void OnBnClickedButtonRecoverZ();
};
