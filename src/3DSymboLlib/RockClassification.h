/************************************************************************/
/*      ��ʯ����Ի�����													*/
/************************************************************************/
#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CRockClassification �Ի���

class CRockClassification : public CDialog
{
	DECLARE_DYNAMIC(CRockClassification)

public:
	CRockClassification(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRockClassification();

// �Ի�������
	enum { IDD = IDD_ROCKCLASSIFICATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
 
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnSelchangedTreeRockList(NMHDR *pNMHDR, LRESULT *pResult);

public:
	HTREEITEM hRoot;	//���ڵ���
	HTREEITEM hCataItem;
	HTREEITEM hArtItem;

	CString m_selectItem;
	CString m_Dir;

	// ��ѡ�е�bmp����Ӱ���ڿؼ��ϻ���
	void drawBitmapFromFile(CString bitmapFilePath,CDC*pDC,CRect rect);


	CTreeCtrl m_Rock_Tree_List;
	CStatic m_image;
	virtual BOOL OnInitDialog();
};
