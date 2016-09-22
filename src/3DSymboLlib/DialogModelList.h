#ifndef DIALOG_MODEL_LIST_H
#define DIALOG_MODEL_LIST_H

#include "afxcmn.h"
#include "Base/ZTypes.h"

#define  THUMBNAIL_WIDTH 50
#define  THUMBNAIL_HEIGHT 50

// CDialogModelList 对话框

class CDialogModelList : public CDialog {
    DECLARE_DYNAMIC(CDialogModelList)

  public:
    explicit CDialogModelList(CWnd* pParent = NULL);
    virtual ~CDialogModelList();

    // 对话框数据
    enum { IDD = IDD_DIALOG_LIST };

  protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()
  public:
    CListCtrl m_listCtlModel;
    CImageList m_imgListModel;
    CArray<CString, CString> m_fileNameArray;
    CString m_Dir;

    CString m_format;  // 图片格式
    CString m_type;    // 符号类别

    CString m_selectItem;

    virtual BOOL OnInitDialog();

    void  DrawThumbnails();
    afx_msg void OnLvnItemchangedListModel(NMHDR* pNMHDR, LRESULT* pResult);
};

#endif  // DIALOG_MODEL_LIST_H