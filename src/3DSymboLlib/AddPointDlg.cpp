#include "stdafx.h"
#include "3DSymbolLibNew.h"
#include "AddPointDlg.h"
#include "afxdialogex.h"


// CAddPointDlg 对话框

IMPLEMENT_DYNAMIC(CAddPointDlg, CDialog)

CAddPointDlg::CAddPointDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CAddPointDlg::IDD, pParent) {
}

CAddPointDlg::~CAddPointDlg() {
}

void CAddPointDlg::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddPointDlg, CDialog)
END_MESSAGE_MAP()


// CAddPointDlg 消息处理程序
