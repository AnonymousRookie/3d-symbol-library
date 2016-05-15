#include "stdafx.h"
#include "3DSymbolLibNew.h"
#include "ModelParam.h"
#include "afxdialogex.h"

#include "DialogModelList.h"
#include "GlobalVariable.h"

#include "RockClassification.h"

// ModelParam �Ի���

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
	, m_TextureName(_T(""))
{
	modelPath = "";
	modelChanged = false;
	
	CString _3DSFolder = "\\3DModel";
	modelFolder = g_sceneDataPath.c_str() + _3DSFolder;

	isModelTextureUpdated = FALSE;

}

ModelParam::~ModelParam()
{
	// Empty
}

void ModelParam::DoDataExchange(CDataExchange* pDX)
{
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


// ModelParam ��Ϣ�������
BOOL ModelParam::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (!m_strTitle.IsEmpty())
		SetWindowText(m_strTitle);

	return TRUE;
} 


/************************************************************************/
/* Function: �޸�ģ��·��(�����µ�ģ��)									*/
/************************************************************************/
void ModelParam::OnBnClickedButtonChangeModelPath()
{
	CDialogModelList dlg1;
	dlg1.m_Dir = modelFolder;

	
	dlg1.m_format = ".bmp";
	dlg1.m_type = "3DS";

	CString m_3DModelPath;
	if(dlg1.DoModal() == IDOK)
	{
		CString selectItem = dlg1.m_selectItem;
		displayPath = selectItem + ".3DS";
		modelPath = modelFolder + displayPath;

		m_TexturePathAndName = modelFolder + selectItem + ".bmp";

		m_TextureName = selectItem + ".bmp";

		modelChanged = true;
		scale = 1;   // �任���µ�ģ�ͣ�ģ�͵����ű���ҪΪ1
	}

	
	else
		return;	

	this->UpdateData(FALSE);
}


/************************************************************************/
/* Function: ������ʯģ������												*/
/************************************************************************/
void ModelParam::OnBnClickedButtonChangeModelTexture()
{
	CRockClassification dlg;

	// ѡ�е�����	 
	CString selectItem;
	if(dlg.DoModal() == IDOK)
	{ 
		selectItem = dlg.m_selectItem;
		CString m_StoneTexturePath = dlg.m_Dir + "\\" + selectItem;

		isModelTextureUpdated = TRUE;
		m_TexturePathAndName = m_StoneTexturePath;
		
		scale = 1;
	}

	else
		return;	

	// ��Edit�ؼ�����ʾ����ͼƬ��
	m_TextureName = selectItem;
	UpdateData(FALSE);

}
