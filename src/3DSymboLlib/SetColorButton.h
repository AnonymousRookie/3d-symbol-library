#pragma once
#include "Base/ZTypes.h"

// CSetColorButton

class CSetColorButton : public CMFCColorButton {
    DECLARE_DYNAMIC(CSetColorButton)

  public:
    CSetColorButton();
    virtual ~CSetColorButton();

  protected:
    DECLARE_MESSAGE_MAP()
    virtual void OnDraw(CDC* pDC, const CRect& rect, UINT uiState);
};


