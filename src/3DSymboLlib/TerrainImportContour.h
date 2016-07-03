#pragma once
#include "define.h"

// TerrainImportContour 对话框

class TerrainImportContour : public CDialog {
    DECLARE_DYNAMIC(TerrainImportContour)

  public:
    TerrainImportContour(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~TerrainImportContour();

    // 对话框数据
    enum { IDD = IDD_DIALOG_CONTOUR_TERRAIN_IMPORT };

  protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
  public:
    // 地表纹理图片
    CString m_TerrainContoureTex;
    // 等高势图
    CString m_TerrainContour;
    afx_msg void OnBnClickedButtonTerrainTexBroswer();
    afx_msg void OnBnClickedButtonContoureBroswer();
};
