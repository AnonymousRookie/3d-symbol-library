
// 3DSymbolLibNewDoc.cpp : CMy3DSymbolLibNewDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "../3DSymbolLibNew.h"
#endif

#include "3DSymbolLibNewDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy3DSymbolLibNewDoc

IMPLEMENT_DYNCREATE(CMy3DSymbolLibNewDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy3DSymbolLibNewDoc, CDocument)
END_MESSAGE_MAP()


// CMy3DSymbolLibNewDoc 构造/析构

CMy3DSymbolLibNewDoc::CMy3DSymbolLibNewDoc() {

}

CMy3DSymbolLibNewDoc::~CMy3DSymbolLibNewDoc() {
}

BOOL CMy3DSymbolLibNewDoc::OnNewDocument() {
    if (!CDocument::OnNewDocument())
        return FALSE;

    return TRUE;
}




// CMy3DSymbolLibNewDoc 序列化

void CMy3DSymbolLibNewDoc::Serialize(CArchive& ar) {  // NOLINT
    if (ar.IsStoring()) {
        // TODO(jason): 在此添加存储代码
    } else {
        // TODO(jason): 在此添加加载代码
    }
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMy3DSymbolLibNewDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds) {  // NOLINT
    // 修改此代码以绘制文档数据
    dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));
    CString strText = _T("TODO(jason): implement thumbnail drawing here");
    LOGFONT lf;
    CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
    pDefaultGUIFont->GetLogFont(&lf);
    lf.lfHeight = 36;
    CFont fontDraw;
    fontDraw.CreateFontIndirect(&lf);
    CFont* pOldFont = dc.SelectObject(&fontDraw);
    dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
    dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMy3DSymbolLibNewDoc::InitializeSearchContent() {
    CString strSearchContent;
    // 从文档数据设置搜索内容。
    // 内容部分应由“;”分隔
    // 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
    SetSearchContent(strSearchContent);
}

void CMy3DSymbolLibNewDoc::SetSearchContent(const CString& value) {
    if (value.IsEmpty()) {
        RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
    } else {
        CMFCFilterChunkValueImpl* pChunk = NULL;
        ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
        if (pChunk != NULL) {
            pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
            SetChunkValue(pChunk);
        }
    }
}

#endif  // SHARED_HANDLERS

// CMy3DSymbolLibNewDoc 诊断

#ifdef _DEBUG
void CMy3DSymbolLibNewDoc::AssertValid() const {
    CDocument::AssertValid();
}

void CMy3DSymbolLibNewDoc::Dump(CDumpContext& dc) const {  // NOLINT
    CDocument::Dump(dc);
}
#endif  // _DEBUG


// CMy3DSymbolLibNewDoc 命令
