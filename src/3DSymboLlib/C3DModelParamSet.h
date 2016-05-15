#pragma once
#include "afxwin.h"


// C3DModelParamSet 对话框

#define WM_GOODBYE				WM_USER+100		//对话框消息响应
#define WM_UPDATE_EDIT_XY		WM_USER+101		//更新对话框

#define SET_XY_BY_MOUSE_FALSE	WM_USER+102		//checkbox 状态 ==> 选中
#define SET_XY_BY_MOUSE_TRUE	WM_USER+103		//checkbox 状态 ==> 未选中

struct ModeParam
{
	//景观树,3d景观树,城市符号
	//tree,3dtree,CitySymbol
	CString type;
};


class C3DModelParamSet : public CDialog
{
	DECLARE_DYNAMIC(C3DModelParamSet)

public:
	C3DModelParamSet(CWnd* pParent = NULL);   // 标准构造函数(模态对话框)
	C3DModelParamSet(CView *pView);			  // 非模态对话框构造函数

	virtual ~C3DModelParamSet();

	BOOL C3DModelParamSet::Create();

	// 对话框数据
	enum { IDD = IDD_DIALOG_3DMODEL_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()



public:
	CView *m_pView; //指向调用此对话框的视类对象的指针
	ModeParam m_modeParam;
public:
	// xPos 位置 // hPos 高度 // zPos 位置
	// radiu 旋转半径
	// angle 角度
	// scale 大小
	int		xPos;
	int		zPos;
	float	hPos;	
	float	radiu;
	int		angle;
	float	scale; 
	virtual BOOL OnInitDialog(); 

	CString m_strTitle; //对话框标题

	// 模型绕 X 轴旋转角度
	int iRotateX;
	// 模型绕Y轴旋转角度
	int iRotateY;
	// 模型绕Z轴旋转角度
	int iRotateZ;
	// 纹理映射方式
	int iDisplayType;
	afx_msg void OnBnClickedRadioRepeat();
	afx_msg void OnBnClickedRadioStretch();


	virtual void OnOK();
	virtual void OnCancel();


public:
	int isSetXYByMouse;

	afx_msg void OnClickedCheckSetXyByMouse();
	CButton m_SetPosCheckBox;

	// 自定义响应消息,响应模型设置,非模式对话框
	afx_msg LRESULT OnUpdateEditXY(WPARAM wParam, LPARAM lParam);
};
