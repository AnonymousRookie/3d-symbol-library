// C3DModelParamSet.cpp : ʵ���ļ�


#include "stdafx.h"
#include "3DSymbolLibNew.h"
#include "C3DModelParamSet.h"
#include "afxdialogex.h"


// C3DModelParamSet �Ի���

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
	, iDisplayType(0)
{
	//ģ̬�Ի���Ĺ��캯����m_pViewΪ��
	m_pView = NULL;
	
}

C3DModelParamSet::C3DModelParamSet(CView *pView)// ��ģ̬�Ի����캯��
	: xPos(389)
	, zPos(-389)
	, hPos(0)
	, radiu(0)
	, angle(0)
	, scale(1)
	, iRotateX(0)
	, iRotateY(0)
	, iRotateZ(0)
	, iDisplayType(0)
{
	//��ģ̬�Ի���Ĺ��캯����m_pView��Ϊ��
	m_pView = pView;
	isSetXYByMouse = 0;
}

C3DModelParamSet::~C3DModelParamSet()
{
	// Empty
}

BOOL C3DModelParamSet::Create()
{
	return CDialog::Create(C3DModelParamSet::IDD);
}

void C3DModelParamSet::DoDataExchange(CDataExchange* pDX)
{
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
	ON_MESSAGE(WM_UPDATE_EDIT_XY,&C3DModelParamSet::OnUpdateEditXY)
END_MESSAGE_MAP()


// C3DModelParamSet ��Ϣ�������


BOOL C3DModelParamSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (!m_strTitle.IsEmpty())
		SetWindowText(m_strTitle);

	m_SetPosCheckBox.SetCheck(0);


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
} 


void C3DModelParamSet::OnBnClickedRadioRepeat()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	iDisplayType = 0; // �����ظ�ӳ�� repeat
	
}


void C3DModelParamSet::OnBnClickedRadioStretch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	iDisplayType = 1; // ��������ӳ��
}


void C3DModelParamSet::OnOK()
{
	
	// TODO: �ڴ����ר�ô����/����û���
	if(m_pView != NULL)
	{
		//��ģʽ�Ի��򲻵��û���CDialog��OnOK����
		UpdateData(TRUE);
		m_pView->PostMessage(WM_GOODBYE, IDOK);
	}
	else
	{
		//AfxMessageBox("ģʽo   ...  k");
		//ģ̬�Ի���ֱ�ӵ��û����OnOK����
		CDialog::OnOK();
	}
}


void C3DModelParamSet::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	if(m_pView != NULL)
	{
		//��ģʽ�Ի��򲻵��û���CDialog��OnCancel����
		//�����û��������ϢWM_GOODBYE
		m_pView->PostMessage(WM_GOODBYE, IDCANCEL);
	}
	else
	{
		//ģ̬�Ի���ֱ�ӵ��û����OnCancel����
		CDialog::OnCancel();
	}
}


/************************************************************************/
/* Function: ͨ���������Ļ��ȡ����������ģ�Ͱڷ�λ��						*/
/************************************************************************/
void C3DModelParamSet::OnClickedCheckSetXyByMouse()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_SetPosCheckBox.GetCheck() == 0)
	{
		isSetXYByMouse = 0;
		//AfxMessageBox("n");
		m_pView->PostMessage(WM_GOODBYE, SET_XY_BY_MOUSE_FALSE);
	}
	else if(m_SetPosCheckBox.GetCheck() == 1)
	{
		isSetXYByMouse = true;
		//AfxMessageBox("y");
		m_pView->PostMessage(WM_GOODBYE, SET_XY_BY_MOUSE_TRUE);
	}
	
}


/************************************************************************/
/* Function: �Զ�����Ϣ��Ӧ, ��ģʽ�Ի���, �������ѡȡ��������¶Ի���		*/
/************************************************************************/
LRESULT C3DModelParamSet::OnUpdateEditXY(WPARAM wParam, LPARAM lParam)
{
	UpdateData(FALSE); // ���¶Ի���
	return 0;
}