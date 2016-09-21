#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "define.h"

// CAreaClassification 对话框

class CAreaClassification : public CDialog {
    DECLARE_DYNAMIC(CAreaClassification)

  public:
    explicit CAreaClassification(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CAreaClassification();

    // 对话框数据
    enum { IDD = IDD_AREACLASSIFICATION };

  protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()


  public:
    HTREEITEM hRoot;    // 根节点句柄
    HTREEITEM hCataItem;
    HTREEITEM hArtItem;

    CString m_selectItem;
    CString m_Dir;
    // 将选中的bmp纹理影像在控件上绘制
    void drawBitmapFromFile(const CString& bitmapFilePath, CDC* pDC, CRect rect);


  public:
    CStatic m_Image;
    CTreeCtrl m_Area_Texture_List;
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnSelchangedTreeAreaList(NMHDR* pNMHDR, LRESULT* pResult);
    virtual BOOL OnInitDialog();
};
