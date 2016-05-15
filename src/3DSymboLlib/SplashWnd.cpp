// SplashWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "3DSymbolLibNew.h"
#include "SplashWnd.h"


// CSplashWnd

IMPLEMENT_DYNAMIC(CSplashWnd, CWnd)

CSplashWnd::CSplashWnd() {
}

CSplashWnd::~CSplashWnd() {
}


BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
    ON_WM_PAINT()
    ON_WM_TIMER()
END_MESSAGE_MAP()

// CSplashWnd 消息处理程序
void CSplashWnd::Create(UINT nBitmapID) {
    m_bitmap.LoadBitmap(nBitmapID);
    BITMAP bitmap;
    m_bitmap.GetBitmap(&bitmap);
    //CreateEx(0,AfxRegisterWndClass(0),"",WS_POPUP|WS_VISIBLE|WS_BORDER,0,0,bitmap.bmWidth,bitmap.bmHeight,NULL,0);
    CreateEx(0,
             AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
             NULL, WS_POPUP | WS_VISIBLE, 0, 0, bitmap.bmWidth, bitmap.bmHeight, NULL , NULL);
}

void CSplashWnd::OnPaint() {
    // TODO: 在此处添加消息处理程序代码
    // 不为绘图消息调用 CWnd::OnPaint()
    CPaintDC dc(this); // device context forpainting
    BITMAP bitmap;
    m_bitmap.GetBitmap(&bitmap);
    CDC dcComp;
    dcComp.CreateCompatibleDC(&dc);
    dcComp.SelectObject(&m_bitmap);
    // draw bitmap
    dc.BitBlt(0, 0, bitmap.bmWidth, bitmap.bmHeight, &dcComp, 0, 0, SRCCOPY);
}

void CSplashWnd::OnTimer(UINT_PTR nIDEvent) {
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    //CWnd::OnTimer(nIDEvent);
    DestroyWindow(); //销毁初始画面窗口
}