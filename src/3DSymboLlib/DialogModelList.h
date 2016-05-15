#pragma once
#include "afxcmn.h"

#define  THUMBNAIL_WIDTH 50
#define  THUMBNAIL_HEIGHT 50

// CDialogModelList �Ի���

class CDialogModelList : public CDialog
{
	DECLARE_DYNAMIC(CDialogModelList)

public:
	CDialogModelList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogModelList();

// �Ի�������
	enum { IDD = IDD_DIALOG_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listCtlModel;
	CImageList m_imgListModel;
	//vector<CString> m_fileNameList;
	CArray<CString, CString> m_fileNameArray;
	CString m_Dir;
	// [ADD]
	CString m_format;//ͼƬ��ʽ
	CString m_type;	// �������
	
	CString m_selectItem;
	
	virtual BOOL OnInitDialog();

	void  DrawThumbnails();
	afx_msg void OnLvnItemchangedListModel(NMHDR *pNMHDR, LRESULT *pResult);
};
