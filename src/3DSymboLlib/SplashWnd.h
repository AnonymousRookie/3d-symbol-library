#pragma once
#include "Base/ZTypes.h"

// CSplashWnd

class CSplashWnd : public CWnd {
    DECLARE_DYNAMIC(CSplashWnd)

  public:
    CSplashWnd();
    virtual ~CSplashWnd();

  protected:
    DECLARE_MESSAGE_MAP()

  public:
    CBitmap m_bitmap;
    //  void Create(void);
    void Create(UINT nBitmapID);
    afx_msg void OnPaint();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
};


