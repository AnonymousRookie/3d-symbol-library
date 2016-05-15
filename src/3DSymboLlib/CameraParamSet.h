#pragma once


// CCameraParamSet �Ի���

class CCameraParamSet : public CDialog
{
	DECLARE_DYNAMIC(CCameraParamSet)

public:
	CCameraParamSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCameraParamSet();

// �Ի�������
	enum { IDD = IDD_DIALOG_CAMERA_PARAM_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float m_DerAngleY, m_OriginDerAngleY;
	float m_DerAngleZ, m_OriginDerAngleZ;

	afx_msg void OnBnClickedButtonRecoverY();
	afx_msg void OnBnClickedButtonRecoverZ();
};
