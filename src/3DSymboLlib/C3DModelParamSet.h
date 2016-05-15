#pragma once
#include "afxwin.h"


// C3DModelParamSet �Ի���

#define WM_GOODBYE				WM_USER+100		//�Ի�����Ϣ��Ӧ
#define WM_UPDATE_EDIT_XY		WM_USER+101		//���¶Ի���

#define SET_XY_BY_MOUSE_FALSE	WM_USER+102		//checkbox ״̬ ==> ѡ��
#define SET_XY_BY_MOUSE_TRUE	WM_USER+103		//checkbox ״̬ ==> δѡ��

struct ModeParam
{
	//������,3d������,���з���
	//tree,3dtree,CitySymbol
	CString type;
};


class C3DModelParamSet : public CDialog
{
	DECLARE_DYNAMIC(C3DModelParamSet)

public:
	C3DModelParamSet(CWnd* pParent = NULL);   // ��׼���캯��(ģ̬�Ի���)
	C3DModelParamSet(CView *pView);			  // ��ģ̬�Ի����캯��

	virtual ~C3DModelParamSet();

	BOOL C3DModelParamSet::Create();

	// �Ի�������
	enum { IDD = IDD_DIALOG_3DMODEL_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()



public:
	CView *m_pView; //ָ����ô˶Ի������������ָ��
	ModeParam m_modeParam;
public:
	// xPos λ�� // hPos �߶� // zPos λ��
	// radiu ��ת�뾶
	// angle �Ƕ�
	// scale ��С
	int		xPos;
	int		zPos;
	float	hPos;	
	float	radiu;
	int		angle;
	float	scale; 
	virtual BOOL OnInitDialog(); 

	CString m_strTitle; //�Ի������

	// ģ���� X ����ת�Ƕ�
	int iRotateX;
	// ģ����Y����ת�Ƕ�
	int iRotateY;
	// ģ����Z����ת�Ƕ�
	int iRotateZ;
	// ����ӳ�䷽ʽ
	int iDisplayType;
	afx_msg void OnBnClickedRadioRepeat();
	afx_msg void OnBnClickedRadioStretch();


	virtual void OnOK();
	virtual void OnCancel();


public:
	int isSetXYByMouse;

	afx_msg void OnClickedCheckSetXyByMouse();
	CButton m_SetPosCheckBox;

	// �Զ�����Ӧ��Ϣ,��Ӧģ������,��ģʽ�Ի���
	afx_msg LRESULT OnUpdateEditXY(WPARAM wParam, LPARAM lParam);
};
