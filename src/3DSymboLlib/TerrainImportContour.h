#ifndef TERRAIN_IMPORT_CONTOUR_H
#define TERRAIN_IMPORT_CONTOUR_H

#include "define.h"

// TerrainImportContour 对话框

class TerrainImportContour : public CDialog {
    DECLARE_DYNAMIC(TerrainImportContour)

  public:
    explicit TerrainImportContour(CWnd* pParent = NULL);
    virtual ~TerrainImportContour();

    // 对话框数据
    enum { IDD = IDD_DIALOG_CONTOUR_TERRAIN_IMPORT };

  protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()
  public:
    // 地表纹理图片
    CString m_TerrainContoureTex;
    // 等高势图
    CString m_TerrainContour;
    afx_msg void OnBnClickedButtonTerrainTexBroswer();
    afx_msg void OnBnClickedButtonContoureBroswer();
};

#endif  // TERRAIN_IMPORT_CONTOUR_H