/************************************************************************/
/*      岩石分类对话框类                                                    */
/************************************************************************/
#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CRockClassification 对话框

class CRockClassification : public CDialog {
    DECLARE_DYNAMIC(CRockClassification)

  public:
    CRockClassification(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CRockClassification();

    // 对话框数据
    enum { IDD = IDD_ROCKCLASSIFICATION };

  protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()

  public:
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnSelchangedTreeRockList(NMHDR* pNMHDR, LRESULT* pResult);

  public:
    HTREEITEM hRoot;    // 根节点句柄
    HTREEITEM hCataItem;
    HTREEITEM hArtItem;

    CString m_selectItem;
    CString m_Dir;

    // 将选中的bmp纹理影像在控件上绘制
    void drawBitmapFromFile(CString bitmapFilePath, CDC* pDC, CRect rect);


    CTreeCtrl m_Rock_Tree_List;
    CStatic m_image;
    virtual BOOL OnInitDialog();
};
