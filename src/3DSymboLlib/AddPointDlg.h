#pragma once


// CAddPointDlg �Ի���

class CAddPointDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddPointDlg)

public:
	CAddPointDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddPointDlg();

// �Ի�������
	enum { IDD = IDD_ADDPOINTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
