#pragma once

#include "afxcmn.h"
// ModelParam 对话框

class ModelParam : public CDialog {
    DECLARE_DYNAMIC(ModelParam)

  public:
    ModelParam(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~ModelParam();

    // 对话框数据
    enum { IDD = IDD_DIALOG_MODEL_PARAM };

  protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
    bool modelChanged;// 模型是否已更换

    bool isModelTextureUpdated;// 模型纹理是否发生改变

    // 纹理的路径及文件名
    CString m_TexturePathAndName;


    virtual BOOL OnInitDialog();
    CString m_strTitle; //设置对话框标题
    CString modelPath;
    CString modelFolder;
    afx_msg void OnBnClickedButtonChangeModelPath();
    afx_msg void OnBnClickedButtonChangeModelTexture();
    CString m_TextureName;
};
