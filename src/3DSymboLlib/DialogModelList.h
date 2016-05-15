#pragma once
#include "afxcmn.h"

#define  THUMBNAIL_WIDTH 50
#define  THUMBNAIL_HEIGHT 50

// CDialogModelList 对话框

class CDialogModelList : public CDialog
{
	DECLARE_DYNAMIC(CDialogModelList)

public:
	CDialogModelList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogModelList();

// 对话框数据
	enum { IDD = IDD_DIALOG_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listCtlModel;
	CImageList m_imgListModel;
	//vector<CString> m_fileNameList;
	CArray<CString, CString> m_fileNameArray;
	CString m_Dir;
	// [ADD]
	CString m_format;//图片格式
	CString m_type;	// 符号类别
	
	CString m_selectItem;
	
	virtual BOOL OnInitDialog();

	void  DrawThumbnails();
	afx_msg void OnLvnItemchangedListModel(NMHDR *pNMHDR, LRESULT *pResult);
};
