#ifndef SPACE_SEARCH_SET_H
#define SPACE_SEARCH_SET_H


#include "afxwin.h"
#include "afxcolorbutton.h"
#include "SetColorButton.h"
#include "Base/ZTypes.h"

#if !defined(AFX_SPACESEARCHSET_H__EBD6DD48_1D05_44B1_BA52_C02F76596DE1__INCLUDED_)
#define AFX_SPACESEARCHSET_H__EBD6DD48_1D05_44B1_BA52_C02F76596DE1__INCLUDED_
#endif  // !defined(AFX_SPACESEARCHSET_H__EBD6DD48_1D05_44B1_BA52_C02F76596DE1__INCLUDED_)


// CSpaceSearchSet dialog

typedef struct _SpaceSearchInfo {
    // 空间查询标志参数
    int32  m_shizxLength;       // 查询标志的十字线长度
    int32  m_shuzxHeight;       // 查询标志的竖直线长度
    int32  m_QueryLineWidth;    // 查询标志线的宽度
    int32  m_QueryColorR;       // 查询标志线的颜色(红,绿,蓝)
    int32  m_QueryColorG;
    int32  m_QueryColorB;
    BYTE   m_QueryType;        // 标识空间查询类别
    int32  m_bSearchDistencePtNums;  // 查询时点取的空间点数
} SpaceSearchInfo;

class CSpaceSearchSet : public CDialog {
  public:
    explicit CSpaceSearchSet(CWnd* pParent = NULL);


    // Dialog Data
    // {{AFX_DATA(CSpaceSearchSet)
    enum { IDD = IDD_DIALOG_SPACESELECTSET };
    CComboBox   m_combolWidth;

    // }}AFX_DATA


    // Overrides
    // ClassWizard generated virtual function overrides
    // {{AFX_VIRTUAL(CSpaceSearchSet)
  public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);

  protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    // }}AFX_VIRTUAL

    // Implementation
  protected:
    // CBrush pbrush;
    // CMyEdit myedit[2];
    // Generated message map functions
    // {{AFX_MSG(CSpaceSearchSet)
    afx_msg void OnButtonColor();
    // afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    // }}AFX_MSG
    DECLARE_MESSAGE_MAP()

  public:
    CSetColorButton m_ColorPicker;
    SpaceSearchInfo spaceSearchInfo_;
};

// {{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif  // SPACE_SEARCH_SET_H