﻿
// 3DSymbolLibNewDoc.h : CMy3DSymbolLibNewDoc 类的接口
//


#pragma once
#include "../Base/ZTypes.h"

class CMy3DSymbolLibNewDoc : public CDocument {
  protected:  // 仅从序列化创建
    CMy3DSymbolLibNewDoc();
    DECLARE_DYNCREATE(CMy3DSymbolLibNewDoc)

    // 特性
  public:

    // 操作
  public:

    // 重写
  public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);  // NOLINT
#ifdef SHARED_HANDLERS
    virtual void InitializeSearchContent();
    virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);  // NOLINT
#endif  // SHARED_HANDLERS

    // 实现
  public:
    virtual ~CMy3DSymbolLibNewDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;  // NOLINT
#endif

  protected:

    // 生成的消息映射函数
  protected:
    DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
    // 用于为搜索处理程序设置搜索内容的 Helper 函数
    void SetSearchContent(const CString& value);
#endif  // SHARED_HANDLERS
};
