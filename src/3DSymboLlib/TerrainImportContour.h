#pragma once


// TerrainImportContour �Ի���

class TerrainImportContour : public CDialog
{
	DECLARE_DYNAMIC(TerrainImportContour)

public:
	TerrainImportContour(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TerrainImportContour();

// �Ի�������
	enum { IDD = IDD_DIALOG_CONTOUR_TERRAIN_IMPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �ر�����ͼƬ
	CString m_TerrainContoureTex;
	// �ȸ���ͼ
	CString m_TerrainContour;
	afx_msg void OnBnClickedButtonTerrainTexBroswer();
	afx_msg void OnBnClickedButtonContoureBroswer();
};
