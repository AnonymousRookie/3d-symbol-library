#include "stdafx.h"
#include "3DSymbolLibNew.h"
#include "SpaceSearchSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CSpaceSearchSet::CSpaceSearchSet(CWnd* pParent /*=NULL*/)
    : CDialog(CSpaceSearchSet::IDD, pParent) {
    // {{AFX_DATA_INIT(CSpaceSearchSet)
    spaceSearchInfo_.m_shizxLength = 5;
    spaceSearchInfo_.m_shuzxHeight = 20;
    // }}AFX_DATA_INIT
}


void CSpaceSearchSet::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
    // {{AFX_DATA_MAP(CSpaceSearchSet)
    DDX_Control(pDX, IDC_COMBOL_WIDTH, m_combolWidth);
    DDX_Text(pDX, IDC_EDIT_SHIZXLENGTH, spaceSearchInfo_.m_shizxLength);
    DDX_Text(pDX, IDC_EDIT_SHUZXHEIGHT, spaceSearchInfo_.m_shuzxHeight);
    // }}AFX_DATA_MAP
    // DDX_Control(pDX, IDC_BUTTON_COLOR, button);
    DDX_Control(pDX, IDC_BUTTON_COLOR, m_ColorPicker);
}


BEGIN_MESSAGE_MAP(CSpaceSearchSet, CDialog)
    // {{AFX_MSG_MAP(CSpaceSearchSet)
    ON_BN_CLICKED(IDC_BUTTON_COLOR, OnButtonColor)
    ON_WM_CTLCOLOR()
    // }}AFX_MSG_MAP
END_MESSAGE_MAP()


// CSpaceSearchSet message handlers

// 颜色按钮响应函数
void CSpaceSearchSet::OnButtonColor() {
    COLORREF color = m_ColorPicker.GetColor();
    if (color == -1) {
        color = m_ColorPicker.GetAutomaticColor();
    }
    spaceSearchInfo_.m_QueryColorR = GetRValue(color);  // 得到所选择的颜色的红色
    spaceSearchInfo_.m_QueryColorG = GetGValue(color);  // 绿
    spaceSearchInfo_.m_QueryColorB = GetBValue(color);  // 蓝
}


// 信息初始化
BOOL CSpaceSearchSet::OnInitDialog() {
    CDialog::OnInitDialog();
    m_combolWidth.ResetContent();       // 存储标志线宽度的下拉框清空
    for (int32 i = 1; i <= 20; i++) {   // 线宽最大宽度为20
        CString tt;
        tt.Format("%d", i);
        m_combolWidth.AddString(tt);
    }
    // 设置下拉框的当前选择项
    if (spaceSearchInfo_.m_QueryLineWidth > 0)
        m_combolWidth.SetCurSel(spaceSearchInfo_.m_QueryLineWidth - 1);
    else
        m_combolWidth.SetCurSel(0);
    m_ColorPicker.EnableAutomaticButton(_T("默认值"), RGB(spaceSearchInfo_.m_QueryColorR, spaceSearchInfo_.m_QueryColorG, spaceSearchInfo_.m_QueryColorB));
    m_ColorPicker.EnableOtherButton(_T("其余颜色"));
    m_ColorPicker.SetColor((COLORREF) - 1);
    // m_ColorPicker.SetColumnsNumber(10);
    this->UpdateData(FALSE);  //  数据变量更新
    // 根据标志线颜色创建画刷
    // pbrush.CreateSolidBrush(RGB(spaceSearchInfo_.m_QueryColorR,spaceSearchInfo_.m_QueryColorG,spaceSearchInfo_.m_QueryColorB));
    return TRUE;
}

BOOL CSpaceSearchSet::PreTranslateMessage(MSG* pMsg) {
    if (pMsg->wParam == VK_RETURN) {  // 如果按钮是回车键
        CDialog* pWnd = reinterpret_cast<CDialog*>(GetParent());
        pWnd->NextDlgCtrl();
        return FALSE;
    } else {
        return CDialog::PreTranslateMessage(pMsg);
    }
}


// 确定扫钮响应函数
void CSpaceSearchSet::OnOK() {
    this->UpdateData();  // 更新数据
    CString tt;
    m_combolWidth.GetLBText(m_combolWidth.GetCurSel(), tt);  // 得到
    spaceSearchInfo_.m_QueryLineWidth = m_combolWidth.GetCurSel();  // 得到标志线宽度
    CDialog::OnOK();  // 以IDOK模式关闭退出对话框
}
