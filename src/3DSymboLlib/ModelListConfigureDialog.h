#ifndef MODEL_LIST_CONFIGURE_DLG_H
#define MODEL_LIST_CONFIGURE_DLG_H

#include "afxcmn.h"
#include "afxwin.h"
#include "define.h"

//  ModelListConfigureDialog 对话框

class ModelListConfigureDialog : public CDialog {
    DECLARE_DYNAMIC(ModelListConfigureDialog)

  public:
    explicit ModelListConfigureDialog(CWnd* pParent = NULL);
    virtual ~ModelListConfigureDialog();

    // 对话框数据
    enum { IDD = IDD_MODELLISTCONFIGUREDIALOG };

  public:
    HTREEITEM hRoot;    // 根节点句柄
    HTREEITEM hCataItem;
    HTREEITEM hArtItem;

    // 将选中的纹理影像在控件上绘制
    void drawBitmapFromFile(CString bitmapFilePath, CDC* pDC, CRect rect);


  protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()

  public:
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
    CTreeCtrl m_configureModeListTree;
    virtual BOOL OnInitDialog();
    afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);  // NOLINT
    afx_msg void OnEditDeleteSymbol();
    afx_msg void OnTvnSelchangedTreeCongigureModellist(NMHDR* pNMHDR, LRESULT* pResult);
    CStatic m_image;
    afx_msg void OnEditAddSymbol();
};

#endif  // MODEL_LIST_CONFIGURE_DLG_H