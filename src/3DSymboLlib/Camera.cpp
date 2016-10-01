#include "stdafx.h"
#include "Camera.h"
#include "MathUtils/MathUtil.h"


void Camera::InitCamera() {
    // 相机参数向上矢量
    m_vUp = CVector3(0.0f, 1.0f, 0.0f);
    m_viewdegree = 0;  // 初始视角增量
    m_viewHeight = m_oldviewHeight = 88;  // 相机初始高度
    m_vEyePosition = CVector3(334.0f, 88.0f, -384.0f);
    g_Angle = 6;                        // 视点方位角初值
    g_elev = 0;                         // 俯仰角初始值
    gao = 1.8;
    rad_xz = MATH_DEG_TO_RAD(g_Angle);  // 计算左右旋转角度
    m_vLook = CVector3(m_vEyePosition.x + 100 * cos(rad_xz),
                       m_vEyePosition.y + g_elev,
                       m_vEyePosition.z + 100 * sin(rad_xz));
}


