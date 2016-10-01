#ifndef Z_CAMERA_H
#define Z_CAMERA_H

#include "MathUtils/vec3.h"

class Camera {
  public:
    Camera(): m_vEyePosition(),
        m_vLook(),
        m_vUp(),
        m_viewHeight(0.0f),
        m_oldviewHeight(0.0f),
        m_originLook(),
        m_viewdegree(0.0f),
        rad_xz(0.0f),
        g_Angle(0.0f),
        g_elev(0.0f),
        gao(0.0f),
        m_Step_X(0.0f),
        m_Step_Z(0.0f),
        m_xTrans(0.0f),
        m_zTrans(0.0f) {}

    ~Camera() {}

  public:
    void InitCamera();
  public:
    // 相机参数变量
    CVector3    m_vEyePosition;     // 相机视点坐标
    CVector3    m_vLook;            // 相机观察点坐标
    CVector3    m_vUp;              // 相机向中三维矢量

    float       m_viewHeight;       // 视点高度
    float       m_oldviewHeight;    // 前一视点高度

    CVector3    m_originLook;       // 相机初始视点坐标
    float       m_viewdegree;       // 观察点与视点之间的俯视角

    // 漫游
    float       rad_xz;             // 角度
    float       g_Angle;            // 方位角
    float       g_elev;             // 仰俯角
    float       gao;

    // 摄像机  键盘控制
    // 相机旋转参数
    float   m_Step_X;   // 相机在X方向移动的步长(鼠标控制)
    float   m_Step_Z;   // 相机在Z方向移动的步长(鼠标控制)

    float   m_xTrans;   // 在X方向上移动的距离(键盘控制)
    float   m_zTrans;   // 在Z方向上移动的距离(键盘控制)
};


#endif  // Z_CAMERA_H