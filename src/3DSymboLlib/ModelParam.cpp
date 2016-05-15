#include "stdafx.h"
#include "3DSymbolLibNew.h"
#include "ModelParam.h"
#include "afxdialogex.h"

#include "DialogModelList.h"
#include "GlobalVariable.h"

#include "RockClassification.h"

// ModelParam 对话框

IMPLEMENT_DYNAMIC(ModelParam, CDialog)

ModelParam::ModelParam(CWnd* pParent /*=NULL*/)
    : CDialog(ModelParam::IDD, pParent)
    , posX(0)
    , posY(0)
    , posZ(0)
    , rotX(0)
    , rotY(0)
    , rotZ(0)
    , scale(1)
    , displayPath(_T(""))
    , m_TextureName(_T("")) {
    modelPath = "";
    modelChanged = false;
    CString _3DSFolder = "\\3DModel";
    modelFolder = g_sceneDataPath.c_str() + _3DSFolder;
    isModelTextureUpdated = FALSE;
}

ModelParam::~ModelParam() {
    // Empty
}

void ModelParam::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, posX);
    DDX_Text(pDX, IDC_EDIT3, posY);
    DDX_Text(pDX, IDC_EDIT4, posZ);
    DDX_Text(pDX, IDC_EDIT5, rotX);
    DDV_MinMaxInt(pDX, rotX, -360, 360);
    DDX_Text(pDX, IDC_EDIT6, rotY);
    DDV_MinMaxInt(pDX, rotY, -360, 360);
    DDX_Text(pDX, IDC_EDIT7, rotZ);
    DDV_MinMaxInt(pDX, rotZ, -360, 360);
    DDX_Text(pDX, IDC_EDIT8, scale);
    DDV_MinMaxInt(pDX, scale, 0.0, INT_MAX);
    DDX_Text(pDX, IDC_EDIT9, displayPath);
    DDX_Text(pDX, IDC_EDIT_MODEL_TEXTURE, m_TextureName);
}


BEGIN_MESSAGE_MAP(ModelParam, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_CHANGE_MODEL_PATH, &ModelParam::OnBnClickedButtonChangeModelPath)
    ON_BN_CLICKED(IDC_BUTTON_CHANGE_MODEL_TEXTURE, &ModelParam::OnBnClickedButtonChangeModelTexture)
END_MESSAGE_MAP()


// ModelParam 消息处理程序
BOOL ModelParam::OnInitDialog() {
    CDialog::OnInitDialog();
    if (!m_strTitle.IsEmpty())
        SetWindowText(m_strTitle);
    return TRUE;
}


/************************************************************************/
/* Function: 修改模型路径(更换新的模型)                                 */
/************************************************************************/
void ModelParam::OnBnClickedButtonChangeModelPath() {
    CDialogModelList dlg1;
    dlg1.m_Dir = modelFolder;
    dlg1.m_format = ".bmp";
    dlg1.m_type = "3DS";
    CString m_3DModelPath;
    if (dlg1.DoModal() == IDOK) {
        CString selectItem = dlg1.m_selectItem;
        displayPath = selectItem + ".3DS";
        modelPath = modelFolder + displayPath;
        m_TexturePathAndName = modelFolder + selectItem + ".bmp";
        m_TextureName = selectItem + ".bmp";
        modelChanged = true;
        scale = 1;   // 变换成新的模型，模型的缩放比例要为1
    } else
        return;
    this->UpdateData(FALSE);
}


/************************************************************************/
/* Function: 更换岩石模型纹理                                               */
/************************************************************************/
void ModelParam::OnBnClickedButtonChangeModelTexture() {
    CRockClassification dlg;
    // 选中的纹理
    CString selectItem;
    if (dlg.DoModal() == IDOK) {
        selectItem = dlg.m_selectItem;
        CString m_StoneTexturePath = dlg.m_Dir + "\\" + selectItem;
        isModelTextureUpdated = TRUE;
        m_TexturePathAndName = m_StoneTexturePath;
        scale = 1;
    } else
        return;
    // 在Edit控件中显示纹理图片名
    m_TextureName = selectItem;
    UpdateData(FALSE);
}
