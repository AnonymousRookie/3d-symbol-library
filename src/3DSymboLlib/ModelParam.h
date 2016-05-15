#pragma once

#include "afxcmn.h"
// ModelParam �Ի���

class ModelParam : public CDialog
{
	DECLARE_DYNAMIC(ModelParam)

public:
	ModelParam(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModelParam();

// �Ի�������
	enum { IDD = IDD_DIALOG_MODEL_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int posX;
	int posY;
	int posZ;
	int rotX;
	int rotY;
	int rotZ;
	float scale;
	CString displayPath;
	bool modelChanged;// ģ���Ƿ��Ѹ���

	bool isModelTextureUpdated;// ģ�������Ƿ����ı�

	// �����·�����ļ���
	CString m_TexturePathAndName;


	virtual BOOL OnInitDialog(); 
	CString m_strTitle; //���öԻ������
	CString modelPath;
	CString modelFolder;
	afx_msg void OnBnClickedButtonChangeModelPath();
	afx_msg void OnBnClickedButtonChangeModelTexture();
	CString m_TextureName;
};
