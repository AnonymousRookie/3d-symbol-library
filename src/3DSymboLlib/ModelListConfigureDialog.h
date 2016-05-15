#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// ModelListConfigureDialog �Ի���

class ModelListConfigureDialog : public CDialog
{
	DECLARE_DYNAMIC(ModelListConfigureDialog)

public:
	ModelListConfigureDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModelListConfigureDialog();

// �Ի�������
	enum { IDD = IDD_MODELLISTCONFIGUREDIALOG };

public:
	HTREEITEM hRoot;	//���ڵ���
	HTREEITEM hCataItem;
	HTREEITEM hArtItem;

	// ��ѡ�е�����Ӱ���ڿؼ��ϻ���
	void drawBitmapFromFile(CString bitmapFilePath,CDC*pDC,CRect rect);
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CTreeCtrl m_configureModeListTree;
	virtual BOOL OnInitDialog();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnEditDeleteSymbol();
	afx_msg void OnTvnSelchangedTreeCongigureModellist(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic m_image;
	afx_msg void OnEditAddSymbol();
};
