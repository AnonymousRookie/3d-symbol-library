// C3DModelParamSet.cpp : 实现文件


#include "stdafx.h"
#include "3DSymbolLibNew.h"
#include "C3DModelParamSet.h"
#include "afxdialogex.h"


// C3DModelParamSet 对话框

IMPLEMENT_DYNAMIC(C3DModelParamSet, CDialog)

C3DModelParamSet::C3DModelParamSet(CWnd* pParent /*=NULL*/)
    : CDialog(C3DModelParamSet::IDD, pParent)
    , xPos(389)
    , zPos(-389)
    , hPos(0)
    , radiu(0)
    , angle(0)
    , scale(1)
    , iRotateX(0)
    , iRotateY(0)
    , iRotateZ(0)
    , iDisplayType(0) {
    //模态对话框的构造函数，m_pView为空
    m_pView = NULL;
}

C3DModelParamSet::C3DModelParamSet(CView* pView)// 非模态对话框构造函数
    : xPos(389)
    , zPos(-389)
    , hPos(0)
    , radiu(0)
    , angle(0)
    , scale(1)
    , iRotateX(0)
    , iRotateY(0)
    , iRotateZ(0)
    , iDisplayType(0) {
    //非模态对话框的构造函数，m_pView不为空
    m_pView = pView;
    isSetXYByMouse = 0;
}

C3DModelParamSet::~C3DModelParamSet() {
    // Empty
}

BOOL C3DModelParamSet::Create() {
    return CDialog::Create(C3DModelParamSet::IDD);
}

void C3DModelParamSet::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_MODEL_X, xPos);
    DDX_Text(pDX, IDC_EDIT_MODEL_Z, zPos);
    DDX_Text(pDX, IDC_EDIT_MODEL_H, hPos);
    DDX_Text(pDX, IDC_EDIT_MODEL_RADIU, radiu);
    DDX_Text(pDX, IDC_EDIT_MODEL_ANGLE, angle);
    DDX_Text(pDX, IDC_EDIT_SCASLE, scale);
    DDX_Text(pDX, IDC_EDIT_MODEL_ROTATE_X, iRotateX);
    DDV_MinMaxInt(pDX, iRotateX, 0, 360);
    DDX_Text(pDX, IDC_EDIT_MODEL_ROTATE_Y, iRotateY);
    DDV_MinMaxInt(pDX, iRotateY, 0, 360);
    DDX_Text(pDX, IDC_EDIT_MODEL_ROTATE_Z, iRotateZ);
    DDV_MinMaxInt(pDX, iRotateZ, 0, 360);
    DDX_Radio(pDX, IDC_RADIO_REPEAT, iDisplayType);
    DDX_Control(pDX, IDC_CHECK_SET_XY_BY_MOUSE, m_SetPosCheckBox);
}


BEGIN_MESSAGE_MAP(C3DModelParamSet, CDialog)
    ON_BN_CLICKED(IDC_RADIO_REPEAT, &C3DModelParamSet::OnBnClickedRadioRepeat)
    ON_BN_CLICKED(IDC_RADIO_STRETCH, &C3DModelParamSet::OnBnClickedRadioStretch)
    ON_BN_CLICKED(IDC_CHECK_SET_XY_BY_MOUSE, &C3DModelParamSet::OnClickedCheckSetXyByMouse)
    ON_MESSAGE(WM_UPDATE_EDIT_XY, &C3DModelParamSet::OnUpdateEditXY)
END_MESSAGE_MAP()


// C3DModelParamSet 消息处理程序


BOOL C3DModelParamSet::OnInitDialog() {
    CDialog::OnInitDialog();
    if (!m_strTitle.IsEmpty())
        SetWindowText(m_strTitle);
    m_SetPosCheckBox.SetCheck(0);
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}


void C3DModelParamSet::OnBnClickedRadioRepeat() {
    // TODO: 在此添加控件通知处理程序代码
    iDisplayType = 0; // 纹理重复映射 repeat
}


void C3DModelParamSet::OnBnClickedRadioStretch() {
    // TODO: 在此添加控件通知处理程序代码
    iDisplayType = 1; // 纹理拉伸映射
}


void C3DModelParamSet::OnOK() {
    // TODO: 在此添加专用代码和/或调用基类
    if (m_pView != NULL) {
        //非模式对话框不调用基类CDialog的OnOK函数
        UpdateData(TRUE);
        m_pView->PostMessage(WM_GOODBYE, IDOK);
    } else {
        //AfxMessageBox("模式o   ...  k");
        //模态对话框直接调用基类的OnOK函数
        CDialog::OnOK();
    }
}


void C3DModelParamSet::OnCancel() {
    // TODO: 在此添加专用代码和/或调用基类
    if (m_pView != NULL) {
        //非模式对话框不调用基类CDialog的OnCancel函数
        //发送用户定义的消息WM_GOODBYE
        m_pView->PostMessage(WM_GOODBYE, IDCANCEL);
    } else {
        //模态对话框直接调用基类的OnCancel函数
        CDialog::OnCancel();
    }
}


/************************************************************************/
/* Function: 通过鼠标点击屏幕获取坐标来设置模型摆放位置                     */
/************************************************************************/
void C3DModelParamSet::OnClickedCheckSetXyByMouse() {
    // TODO: 在此添加控件通知处理程序代码
    if (m_SetPosCheckBox.GetCheck() == 0) {
        isSetXYByMouse = 0;
        //AfxMessageBox("n");
        m_pView->PostMessage(WM_GOODBYE, SET_XY_BY_MOUSE_FALSE);
    } else if (m_SetPosCheckBox.GetCheck() == 1) {
        isSetXYByMouse = true;
        //AfxMessageBox("y");
        m_pView->PostMessage(WM_GOODBYE, SET_XY_BY_MOUSE_TRUE);
    }
}


/************************************************************************/
/* Function: 自定义消息响应, 非模式对话框, 根据鼠标选取的坐标更新对话框     */
/************************************************************************/
LRESULT C3DModelParamSet::OnUpdateEditXY(WPARAM wParam, LPARAM lParam) {
    UpdateData(FALSE); // 更新对话框
    return 0;
}