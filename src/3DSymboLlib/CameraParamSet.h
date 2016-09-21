#ifndef CAMERA_PARAM_SET_H
#define CAMERA_PARAM_SET_H

#include "define.h"

// CCameraParamSet 对话框

class CCameraParamSet : public CDialog {
    DECLARE_DYNAMIC(CCameraParamSet)

  public:
    explicit CCameraParamSet(CWnd* pParent = NULL);
    virtual ~CCameraParamSet();

    // 对话框数据
    enum { IDD = IDD_DIALOG_CAMERA_PARAM_SET };

  protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()
  public:
    float m_DerAngleY, m_OriginDerAngleY;
    float m_DerAngleZ, m_OriginDerAngleZ;

    afx_msg void OnBnClickedButtonRecoverY();
    afx_msg void OnBnClickedButtonRecoverZ();
};

#endif  // CAMERA_PARAM_SET_H