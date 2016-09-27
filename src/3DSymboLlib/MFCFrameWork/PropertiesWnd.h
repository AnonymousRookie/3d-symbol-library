#ifndef PROPERTIES_WND_H
#define PROPERTIES_WND_H

#include "../Base/ZTypes.h"

class CPropertiesToolBar : public CMFCToolBar {
  public:
    virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler) {
        CMFCToolBar::OnUpdateCmdUI(reinterpret_cast<CFrameWnd*>(GetOwner()), bDisableIfNoHndler);
    }

    virtual BOOL AllowShowOnList() const {
        return FALSE;
    }
};

class CPropertiesWnd : public CDockablePane {
  public:
    CPropertiesWnd();

    void AdjustLayout();

  public:
    void SetVSDotNetLook(BOOL bSet) {
        m_wndPropList.SetVSDotNetLook(bSet);
        m_wndPropList.SetGroupNameFullWidth(bSet);
    }

  protected:
    CFont m_fntPropList;
    CComboBox m_wndObjectCombo;
    CPropertiesToolBar m_wndToolBar;
    CMFCPropertyGridCtrl m_wndPropList;

  public:
    virtual ~CPropertiesWnd();

  protected:
    afx_msg int32 OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int32 cx, int32 cy);
    afx_msg void OnExpandAllProperties();
    afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
    afx_msg void OnSortProperties();
    afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
    afx_msg void OnProperties1();
    afx_msg void OnUpdateProperties1(CCmdUI* pCmdUI);
    afx_msg void OnProperties2();
    afx_msg void OnUpdateProperties2(CCmdUI* pCmdUI);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

    DECLARE_MESSAGE_MAP()

    void InitPropList();
    void SetPropListFont();
};

#endif  // PROPERTIES_WND_H