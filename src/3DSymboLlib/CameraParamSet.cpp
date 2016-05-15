// CameraParamSet.cpp : 实现文件
//

#include "stdafx.h"
#include "3DSymbolLibNew.h"
#include "CameraParamSet.h"
#include "afxdialogex.h"


// CCameraParamSet 对话框

IMPLEMENT_DYNAMIC(CCameraParamSet, CDialog)

CCameraParamSet::CCameraParamSet(CWnd* pParent /*=NULL*/)
    : CDialog(CCameraParamSet::IDD, pParent)
    , m_DerAngleY(0)
    , m_DerAngleZ(0) {
}

CCameraParamSet::~CCameraParamSet() {
}

void CCameraParamSet::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_MOUSE_Y_SENSI, m_DerAngleY);
    DDX_Text(pDX, IDC_EDIT_MOUSE_Z_SENSI, m_DerAngleZ);
}


BEGIN_MESSAGE_MAP(CCameraParamSet, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_RECOVER_Y, &CCameraParamSet::OnBnClickedButtonRecoverY)
    ON_BN_CLICKED(IDC_BUTTON_RECOVER_Z, &CCameraParamSet::OnBnClickedButtonRecoverZ)
END_MESSAGE_MAP()


// CCameraParamSet 消息处理程序


void CCameraParamSet::OnBnClickedButtonRecoverY() {
    // TODO: 在此添加控件通知处理程序代码
    SetDlgItemInt(IDC_EDIT_MOUSE_Y_SENSI, m_OriginDerAngleY);
}


void CCameraParamSet::OnBnClickedButtonRecoverZ() {
    // TODO: 在此添加控件通知处理程序代码
    SetDlgItemInt(IDC_EDIT_MOUSE_Z_SENSI, m_OriginDerAngleZ);
}
