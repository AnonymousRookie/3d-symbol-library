#include "stdafx.h"
#include "SetColorButton.h"


IMPLEMENT_DYNAMIC(CSetColorButton, CMFCColorButton)

CSetColorButton::CSetColorButton() {
}

CSetColorButton::~CSetColorButton() {
}


BEGIN_MESSAGE_MAP(CSetColorButton, CMFCColorButton)
END_MESSAGE_MAP()



// CSetColorButton 消息处理程序
void CSetColorButton::OnDraw(CDC* pDC, const CRect& rect, UINT uiState) {
    ASSERT_VALID(pDC);
    CRect rcClient = rect;
    rcClient.DeflateRect(-1, -1);
    CRect rcArrow;
    rcArrow.right = rcClient.right - 7;
    rcArrow.left = rcArrow.right - 6;
    rcArrow.top = rcClient.Height() / 2 - 2;
    rcArrow.bottom = rcArrow.top + 3;
    CPoint point[3];
    point[0] = CPoint(rcArrow.left, rcArrow.top);
    point[1] = CPoint(rcArrow.right, rcArrow.top);
    point[2] = CPoint(rcArrow.Width() / 2 + rcArrow.left, rcArrow.bottom);
    CBrush br;
    br.CreateSolidBrush(RGB(0, 0, 0));
    CBrush* obr = reinterpret_cast<CBrush*>(pDC->SelectObject(br));
    pDC->Polygon(point, 3);
    pDC->SelectObject(&obr);
    // ----------------
    // Draw color box:
    // ----------------
    CRect rectColor = rect;
    rectColor.right -= 13;
    rectColor.DeflateRect(4, 4);
    pDC->Draw3dRect(rectColor, afxGlobalData.clrBtnHilite, afxGlobalData.clrBtnHilite);
    rectColor.DeflateRect(1, 1);
    if (m_pPalette == NULL) {
        RebuildPalette(NULL);
    }
    CPalette* pCurPalette = pDC->SelectPalette(m_pPalette, FALSE);
    pDC->RealizePalette();
    COLORREF color = m_Color;
    if (color == (COLORREF) - 1)  // Automatic
        color = m_ColorAutomatic;
    if (color != (COLORREF) - 1 && (uiState & ODS_DISABLED) == 0) {
        if (afxGlobalData.m_nBitsPerPixel == 8) {  // 256 colors
            ASSERT_VALID(m_pPalette);
            color =  PALETTEINDEX(m_pPalette->GetNearestPaletteIndex(color));
        }
        CBrush br(color);
        pDC->FillRect(rectColor, &br);
    }
    if (pCurPalette != NULL) {
        pDC->SelectPalette(pCurPalette, FALSE);
    }
}