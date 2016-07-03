﻿#pragma once
#include "define.h"

/////////////////////////////////////////////////////////////////////////////
// CViewTree 窗口

class CViewTree : public CTreeCtrl {
    // 构造
  public:
    CViewTree();

    // 重写
  protected:
    virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

    // 实现
  public:
    virtual ~CViewTree();

  protected:
    DECLARE_MESSAGE_MAP()
};
