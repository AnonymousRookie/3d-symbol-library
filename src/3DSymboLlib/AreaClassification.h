#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CAreaClassification �Ի���

class CAreaClassification : public CDialog
{
	DECLARE_DYNAMIC(CAreaClassification)

public:
	CAreaClassification(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAreaClassification();

// �Ի�������
	enum { IDD = IDD_AREACLASSIFICATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


public:
	HTREEITEM hRoot;	//���ڵ���
	HTREEITEM hCataItem;
	HTREEITEM hArtItem;

	CString m_selectItem;
	CString m_Dir;
	// ��ѡ�е�bmp����Ӱ���ڿؼ��ϻ���
	void drawBitmapFromFile(CString bitmapFilePath,CDC*pDC,CRect rect);


public:
	CStatic m_Image;
	CTreeCtrl m_Area_Texture_List;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnSelchangedTreeAreaList(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
//	afx_msg void OnMenuUpdateAreaTexture();
//	afx_msg void OnMenuAreaDelete();
};
