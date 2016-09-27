/************************************************************************/
/*      岩石分类对话框类                                                  */
/************************************************************************/
#ifndef ROCK_CLASSIFICATION_H
#define ROCK_CLASSIFICATION_H

#include "afxcmn.h"
#include "afxwin.h"
#include "../Base/ZTypes.h"

class CRockClassification : public CDialog {
    DECLARE_DYNAMIC(CRockClassification)

  public:
    explicit CRockClassification(CWnd* pParent = NULL);
    virtual ~CRockClassification();

    // 对话框数据
    enum { IDD = IDD_ROCKCLASSIFICATION };

  protected:
    virtual void DoDataExchange(CDataExchange* pDX);

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

#endif  // ROCK_CLASSIFICATION_H