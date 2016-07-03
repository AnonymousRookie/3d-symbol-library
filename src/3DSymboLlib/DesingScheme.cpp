#include "stdafx.h"
#include "DesingScheme.h"

#include "GlobalVariable.h"

#include "LeastSquares.h"


CDesingScheme::CDesingScheme(void) {
    // empty
}


CDesingScheme::~CDesingScheme(void) {
    // empty
}



double CDesingScheme::GetDistenceXY(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}


/************************************************************************/
/* Function: 根据前一个点计算边坡模型                                       */
/************************************************************************/
void CDesingScheme::Get3DLineModel(double x1, double y1, double z1, double x2, double y2, double z2, float fRailwayWidth, float LjWidth, float h_FromGmToLj, float mWidthGuiMianToLujian, float mAngleLujinaToBianPo, CString strJDstyle, CString strJDstyleNext, int64 index, double mLC) {
    float mangle;
    float dx = x2 - x1;
    float dz = z2 - z1;
    double x11, y11, z11, x12, y12, z12;
    double x21, y21, z21, x22, y22, z22;
    // fRailwayWidth：单线地段道床顶面宽度
    float L1 = fRailwayWidth / 2.0;
    // 1.根据线路前后中心线的三维坐标计算 铁轨顶面 左右点的x,y,z坐标
    Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
    PRailway3DCordinate pt;
    pt = new Railway3DCordinate;
    pt->x1 = x11;
    pt->y1 = y11;
    pt->z1 = z11;
    pt->x2 = x12;
    pt->y2 = y12;
    pt->z2 = z12;
    PtS_Railway3D.Add(pt);
    // ２.根据线路前后中心线的三维坐标计算 道床顶面 左右点的x,y,z坐标
    L1 = fRailwayWidth / 2.0 + mWidthGuiMianToLujian;
    Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
    pt = new Railway3DCordinate;
    pt->x1 = x11;
    pt->y1 = y11 - h_FromGmToLj;
    pt->z1 = z11;
    pt->x2 = x12;
    pt->y2 = y12 - h_FromGmToLj;
    pt->z2 = z12;
    PtS_RailwayLj3D.Add(pt);
    // 3.根据线路前后中心线的三维坐标计算碴脚左右点的x,y,z坐标 LjWidth=碴肩至碴脚的水平距离
    L1 = fRailwayWidth / 2.0 + mWidthGuiMianToLujian + LjWidth;
    Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
    pt = new Railway3DCordinate;
    pt->x1 = x11;
    pt->y1 = y11 - h_FromGmToLj;
    pt->z1 = z11;
    pt->x2 = x12;
    pt->y2 = y12 - h_FromGmToLj;
    pt->z2 = z12;
    // 根据线路前后中心线的三维坐标计算计算路基面左右点的x,y,z坐标
    pt->TW_left = GetTW(pt->x1, pt->z1, pt->y1);  // 计算左边坡的填挖类型
    pt->TW_right = GetTW(pt->x2, pt->z2, pt->y2);  // 计算右边坡的填挖类型
    pt->mAngle = mangle;
    PtS_RailwayLjToBP3D.Add(pt);  // 存储边坡左面侧的填挖类型
    // 正常边坡处
    {
        L1 = fRailwayWidth / 2.0 + mWidthGuiMianToLujian + LjWidth;
        // 计算左侧边坡点与地面的交点坐标
        GetDMJD(x1, y1, z1, x2, y2, z2, L1, pt->y1, pt->x1, pt->z1, pt->TW_left, -1, \
                pt->x1, pt->y1, pt->z1, \
                pt->x1, pt->y1, pt->z1, mLC, strJDstyle);
        // 计算右侧边坡点与地面的交点坐标
        GetDMJD(x1, y1, z1, x2, y2, z2, L1, pt->y2, pt->x2, pt->z2, pt->TW_right, 1, \
                pt->x2, pt->y2, pt->z2, \
                pt->x2, pt->y2, pt->z2, mLC, strJDstyle);
    }
}


/************************************************************************/
/* Function: 根据后一个点计算边坡模型                                       */
/************************************************************************/
void CDesingScheme::Get3DLineModelLast(double x1, double y1, double z1, double x2, double y2, double z2, float fRailwayWidth, float LjWidth, float h_FromGmToLj, float mWidthGuiMianToLujian, float mAngleLujinaToBianPo, CString strJDstyle, CString strJDstyleNext, int64 index, double mLC) {
    float mangle;
    float dx = x2 - x1;
    float dz = z2 - z1;
    double x11, y11, z11, x12, y12, z12;
    double x21, y21, z21, x22, y22, z22;
    float L1 = fRailwayWidth / 2.0;
    Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
    PRailway3DCordinate pt;
    pt = new Railway3DCordinate;
    pt->x1 = x21;
    pt->y1 = y21;
    pt->z1 = z21;
    pt->x2 = x22;
    pt->y2 = y22;
    pt->z2 = z22;
    PtS_Railway3D.Add(pt);
    L1 = fRailwayWidth / 2.0 + mWidthGuiMianToLujian;
    Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
    pt = new Railway3DCordinate;
    pt->x1 = x21;
    pt->y1 = y21 - h_FromGmToLj;
    pt->z1 = z21;
    pt->x2 = x22;
    pt->y2 = y22 - h_FromGmToLj;
    pt->z2 = z22;
    PtS_RailwayLj3D.Add(pt);
    L1 = fRailwayWidth / 2.0 + mWidthGuiMianToLujian + LjWidth;
    Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
    pt = new Railway3DCordinate;
    pt->x1 = x21;
    pt->y1 = y21 - h_FromGmToLj;
    pt->z1 = z21;
    pt->x2 = x22;
    pt->y2 = y22 - h_FromGmToLj;
    pt->z2 = z22;
    pt->TW_left = GetTW(pt->x1, pt->z1, pt->y1);
    pt->TW_right = GetTW(pt->x2, pt->z2, pt->y2);
    pt->mAngle = mangle;
    PtS_RailwayLjToBP3D.Add(pt);
    GetDMJDLast(x1, y1, z1, x2, y2, z2, L1, pt->y1, pt->x1, pt->z1, pt->TW_left, -1, \
                pt->x1, pt->y1, pt->z1, \
                pt->x1, pt->y1, pt->z1, mLC, strJDstyle);
    GetDMJDLast(x1, y1, z1, x2, y2, z2, L1, pt->y2, pt->x2, pt->z2, pt->TW_right, 1, \
                pt->x2, pt->y2, pt->z2, \
                pt->x2, pt->y2, pt->z2, mLC, strJDstyle);
}



/************************************************************************/
/* Function: 根据线路前后中心线两点的三维坐标计算对应的路基横断面左右点坐标 */
/************************************************************************/
void CDesingScheme::Get3DCorrdinate(double x1, double y1, double z1, double x2, double y2, double z2, float dx, float dz, float L, double* x11, double* y11, double* z11, double* x12, double* y12, double* z12, double* x21, double* y21, double* z21, double* x22, double* y22, double* z22, float* angle) {
    float mangle;
    if (fabs(dx) <= 0.000001) {  // 如果前后线路中线点的X坐标之差<=0.000001,则认为两点组成的直线平行于Y轴
        if (dz < 0)
            mangle = PAI / 2.0;  // 如果dz<0,直线角度=90
        else
            mangle = 3 / 2.0 * PAI;  // 如果dz<0,直线角度=270
        // 计算线路中线当前点(x1,y1,z1)对应的左侧点三维坐标
        *x11 = x1 - L * sin(mangle);
        *y11 = y1;
        *z11 = z1;
        // 计算线路中线下一点(x2,y2,z2)对应的左侧点三维坐标
        *x21 = x2 - L * sin(mangle);
        *y21 = y2;
        *z21 = z2;
        *angle = mangle;
    } else {  // 根据fabs(dz/dx)值计算前后线路中线点构成的直线角度
        mangle = atan(fabs(dz / dx));
        if (dx >= 0 && dz <= 0) {  // 1 象限
            // 计算线路中线当前点(x1,y1,z1)对应的左侧点三维坐标
            *x11 = x1 - L * sin(mangle);
            *y11 = y1;
            *z11 = z1 - L * cos(mangle);
            // 计算线路中线下一点(x2,y2,z2)对应的左侧点三维坐标
            *x21 = x2 - L * sin(mangle);
            *y21 = y2;
            *z21 = z2 - L * cos(mangle);
            *angle = mangle;
        } else if (dx <= 0 && dz <= 0) {  // 2 象限
            // 计算线路中线当前点(x1,y1,z1)对应的左侧点三维坐标
            *x11 = x1 - L * sin(mangle);
            *y11 = y1;
            *z11 = z1 + L * cos(mangle);
            // 计算线路中线下一点(x2,y2,z2)对应的左侧点三维坐标
            *x21 = x2 - L * sin(mangle);
            *y21 = y2;
            *z21 = z2 + L * cos(mangle);
            *angle = PAI - mangle;
        } else if (dx <= 0 && dz >= 0) {  // 3 象限
            // 计算线路中线当前点(x1,y1,z1)对应的左侧点三维坐标
            *x11 = x1 + L * sin(mangle);
            *y11 = y1;
            *z11 = z1 + L * cos(mangle);
            // 计算线路中线下一点(x2,y2,z2)对应的左侧点三维坐标
            *x21 = x2 + L * sin(mangle);
            *y21 = y2;
            *z21 = z2 + L * cos(mangle);
            *angle = PAI + mangle;
        } else if (dx >= 0 && dz >= 0) {  // 4 象限
            // 计算线路中线当前点(x1,y1,z1)对应的左侧点三维坐标
            *x11 = x1 + L * sin(mangle);
            *y11 = y1;
            *z11 = z1 - L * cos(mangle);
            // 计算线路中线下一点(x2,y2,z2)对应的左侧点三维坐标
            *x21 = x2 + L * sin(mangle);
            *y21 = y2;
            *z21 = z2 - L * cos(mangle);
            *angle = 2 * PAI - mangle;
        }
    }
    // 计算线路中线当前点(x1,y1,z1)对应的右侧点三维坐标
    *x12 = 2 * x1 - *x11;
    *y12 = 2 * y1 - *y11;
    *z12 = 2 * z1 - *z11;
    // 计算线路中线下一点(x2,y2,z2)对应的右侧点三维坐标
    *x22 = 2 * x2 - *x21;
    *y22 = 2 * y2 - *y21;
    *z22 = 2 * z2 - *z21;
}


/************************************************************************/
/* Function: 计算各交点的曲线要素                                           */
/************************************************************************/
void CDesingScheme::CalculateCurveData() {
    CString tt;
    PLineCurve pTempCurveElements;
    double m_startLC = 0;   // 起点里程
    if (PtS_JD.GetSize() > 1) {  // 如果设计交点数大于1
        // 计算第1个交点"JD0"的曲线要素
        pTempCurveElements          = JDCurveElements.GetAt(0);
        pTempCurveElements->ZH      = pTempCurveElements->HZ             = m_startLC;  // 缓直点里程 直缓点里程
        pTempCurveElements->HY      = pTempCurveElements->YH             = m_startLC;
        pTempCurveElements->Alfa        = pTempCurveElements->T          = pTempCurveElements->L      = 0;
        pTempCurveElements->R       = pTempCurveElements->RoateStyle = pTempCurveElements->E      = 0;
        pTempCurveElements->P       = pTempCurveElements->L0             = pTempCurveElements->Ly = pTempCurveElements->Jzxc = 0;
        pTempCurveElements->JDLC        = m_startLC;            // 交点里程
        pTempCurveElements->ID      = "JD0";                // 交点ID号
        pTempCurveElements->x       = PtS_JD.GetAt(0)->x;   // 交点x坐标
        pTempCurveElements->y       = -PtS_JD.GetAt(0)->z;  // 交点y坐标
        pTempCurveElements->z       = PtS_JD.GetAt(0)->y;   // 交点z坐标
        pTempCurveElements->Cneterx = pTempCurveElements->x;  // 曲线圆心x坐标
        pTempCurveElements->Cnetery = pTempCurveElements->y;  // 曲线圆心y坐标
        pTempCurveElements->ZH_xy   = new  Cordinate;        // 直缓点坐标
        pTempCurveElements->ZH_xy->x = pTempCurveElements->x;
        pTempCurveElements->ZH_xy->y = pTempCurveElements->y;
        pTempCurveElements->HY_xy   = new  Cordinate;       // 缓圆点坐标
        pTempCurveElements->HY_xy->x = pTempCurveElements->x;
        pTempCurveElements->HY_xy->y = pTempCurveElements->y;
        pTempCurveElements->YH_xy   = new  Cordinate;       // 圆缓点坐标
        pTempCurveElements->YH_xy->x = pTempCurveElements->x;
        pTempCurveElements->YH_xy->y = pTempCurveElements->y;
        pTempCurveElements->HZ_xy   = new  Cordinate;       // 缓直点坐标
        pTempCurveElements->HZ_xy->x = pTempCurveElements->x;
        pTempCurveElements->HZ_xy->y = pTempCurveElements->y;
        // 计算最后一个交点JDN的曲线要素
        pTempCurveElements       = JDCurveElements.GetAt(PtS_JD.GetSize() - 1);
        pTempCurveElements->Alfa = pTempCurveElements->T = pTempCurveElements->L = 0;  // 交点转角
        pTempCurveElements->RoateStyle = pTempCurveElements->E = 0;             // 外矢距
        pTempCurveElements->Ly   = pTempCurveElements->Jzxc = 0;                    // 夹直线
        pTempCurveElements->Dist = pTempCurveElements->fwj  = 0;                // 交点偏角
        pTempCurveElements->x       = PtS_JD.GetAt(PtS_JD.GetSize() - 1)->x;    // 交点x坐标
        pTempCurveElements->y       = -PtS_JD.GetAt(PtS_JD.GetSize() - 1)->z;   // 交点y坐标
        pTempCurveElements->z       = PtS_JD.GetAt(PtS_JD.GetSize() - 1)->y;    // 交点z坐标
        pTempCurveElements->Cneterx = pTempCurveElements->x;                        // 曲线圆心x坐标
        pTempCurveElements->Cnetery = pTempCurveElements->y;                        // 曲线圆心y坐标
        pTempCurveElements->ZH_xy   = new Cordinate;            // 直缓点坐标
        pTempCurveElements->ZH_xy->x = pTempCurveElements->x;
        pTempCurveElements->ZH_xy->y = pTempCurveElements->y;
        pTempCurveElements->HY_xy   = new Cordinate;            // 缓圆点坐标
        pTempCurveElements->HY_xy->x = pTempCurveElements->x;
        pTempCurveElements->HY_xy->y = pTempCurveElements->y;
        pTempCurveElements->YH_xy   = new Cordinate;            // 圆缓点坐标
        pTempCurveElements->YH_xy->x = pTempCurveElements->x;
        pTempCurveElements->YH_xy->y = pTempCurveElements->y;
        pTempCurveElements->HZ_xy   = new  Cordinate;           // 缓直点坐标
        pTempCurveElements->HZ_xy->x = pTempCurveElements->x;
        pTempCurveElements->HZ_xy->y = pTempCurveElements->y;
        float dertE, dertN;
        float fwj, fwj2;
        int64 i;
        /*
        N
        |
        |
        |
        |
        |____________ E
         */
        // 计算交点JD1与交点JDN之间交点的曲线要素
        for (i = 0; i < PtS_JD.GetSize() - 1; i++) {
            // 求方位角fwj
            dertE   = PtS_JD.GetAt(i + 1)->x      -   PtS_JD.GetAt(i)->x;
            dertN   = (-PtS_JD.GetAt(i + 1)->z)   - (-PtS_JD.GetAt(i)->z);
            if (dertE >= 0 && dertN > 0) {           // 1象限
                fwj = atan(fabs(dertE / dertN));    // 方位角
            } else if (dertE >= 0 && dertN < 0) {   // 2象限
                fwj = PAI - atan(fabs(dertE / dertN));
            } else if (dertE < 0 && dertN < 0) {    // 3象限
                fwj = PAI + atan(fabs(dertE / dertN));
            } else if (dertE < 0 && dertN > 0) {    // 4象限
                fwj = 2 * PAI - atan(fabs(dertE / dertN));
            } else if (dertE > 0 && dertN == 0) {
                fwj = PAI / 2.0;
            } else if (dertE < 0 && dertN == 0) {
                fwj = 3 * PAI / 2.0;
            }
            JDCurveElements.GetAt(i)->fwj   =   fwj;                            // 方位角
            JDCurveElements.GetAt(i)->Dist  =   sqrt(dertE * dertE + dertN * dertN);  // 交点距离
            // 求方位角fwj2
            if (dertN >= 0 && dertE > 0) {          // 1象限
                fwj2 = atan(fabs(dertN / dertE));   // 方位角2
            } else if (dertN >= 0 && dertE < 0) {   // 2象限
                fwj2 = PAI - atan(fabs(dertN / dertE));
            } else if (dertN < 0 && dertE < 0) {    // 3象限
                fwj2 = PAI + atan(fabs(dertN / dertE));
            } else if (dertN < 0 && dertE > 0) {    // 4象限
                fwj2 = 2 * PAI - atan(fabs(dertN / dertE));
            } else if (dertN > 0 && dertE == 0) {
                fwj2 = PAI / 2.0;
            } else if (dertN < 0 && dertE == 0) {
                fwj2 = 3 * PAI / 2.0;
            }
            JDCurveElements.GetAt(i)->fwj2 = fwj2;
        }
        // 最后一个交点的方位角2=0
        JDCurveElements.GetAt(PtS_JD.GetSize() - 1)->fwj2 = 0;
        for (i = 0; i < PtS_JD.GetSize() - 2; i++) {
            // 曲线转角 = fwj[i+1] - fwj[i]
            JDCurveElements.GetAt(i + 1)->Alfa = JDCurveElements.GetAt(i + 1)->fwj - JDCurveElements.GetAt(i)->fwj;
            if (fabs(JDCurveElements.GetAt(i + 1)->Alfa) > PAI) {
                if (JDCurveElements.GetAt(i + 1)->Alfa < 0)
                    JDCurveElements.GetAt(i + 1)->Alfa = fabs(JDCurveElements.GetAt(i + 1)->Alfa) - PAI;
            }
            CString tmpAlfaStr;
            tmpAlfaStr.Format("Alfa = %f 度", (JDCurveElements.GetAt(i + 1)->Alfa) * 180 / PAI);
            if (JDCurveElements.GetAt(i + 1)->Alfa > 0) {
                JDCurveElements.GetAt(i + 1)->RoateStyle = 1;  // 右转
                // AfxMessageBox("右转" + tmpAlfaStr);
            } else if (JDCurveElements.GetAt(i + 1)->Alfa < 0) {
                JDCurveElements.GetAt(i + 1)->RoateStyle = -1;  // 左转
                // AfxMessageBox("左转" + tmpAlfaStr);
            }
            if (PtS_JD.GetAt(i + 1)->x - PtS_JD.GetAt(i)->x > 0) {
                if (JDCurveElements.GetAt(i + 1)->Alfa < 0)
                    JDCurveElements.GetAt(i + 1)->Alfa = -JDCurveElements.GetAt(i + 1)->Alfa;
            }
            float ftan = tan(JDCurveElements.GetAt(i + 1)->Alfa / 2.0);
            // 切线长T[i+1] = (R[i+1] + p[i+1]) * tan(Alfa[i+1]/2) + l0[i+1]/2
            JDCurveElements.GetAt(i + 1)->T = \
                                              (JDCurveElements.GetAt(i + 1)->R + \
                                               JDCurveElements.GetAt(i + 1)->P) * \
                                              tan(JDCurveElements.GetAt(i + 1)->Alfa / 2.0) + \
                                              JDCurveElements.GetAt(i + 1)->L0 / 2.0;
            // 曲线长L[L+1] = Alfa[i+1] * R[i+1] + l0[i+1]
            JDCurveElements.GetAt(i + 1)->L   =   fabs(JDCurveElements.GetAt(i + 1)->Alfa * JDCurveElements.GetAt(i + 1)->R) + JDCurveElements.GetAt(i + 1)->L0;
            // 直缓点里程ZH[i+1] = Dist[i] - T[i] - T[i+1] + HZ[i]
            JDCurveElements.GetAt(i + 1)->ZH  =   JDCurveElements.GetAt(i)->Dist - JDCurveElements.GetAt(i)->T - JDCurveElements.GetAt(i + 1)->T + JDCurveElements.GetAt(i)->HZ;
            // 缓直点里程HZ[i+1] = ZH[i+1] + L[i+1]
            JDCurveElements.GetAt(i + 1)->HZ  =   JDCurveElements.GetAt(i + 1)->ZH + JDCurveElements.GetAt(i + 1)->L;
            JDCurveElements.GetAt(i + 1)->HY  =   JDCurveElements.GetAt(i + 1)->ZH + JDCurveElements.GetAt(i + 1)->L0;
            JDCurveElements.GetAt(i + 1)->YH  =   JDCurveElements.GetAt(i + 1)->HZ - JDCurveElements.GetAt(i + 1)->L0;
            JDCurveElements.GetAt(i + 1)->Ly  =   JDCurveElements.GetAt(i + 1)->YH - JDCurveElements.GetAt(i + 1)->HY;
            JDCurveElements.GetAt(i + 1)->JDLC =   JDCurveElements.GetAt(i + 1)->ZH + JDCurveElements.GetAt(i + 1)->T;
            JDCurveElements.GetAt(i + 1)->E   = (JDCurveElements.GetAt(i + 1)->R + JDCurveElements.GetAt(i + 1)->P) / cos(JDCurveElements.GetAt(i + 1)->Alfa / 2.0) - JDCurveElements.GetAt(i + 1)->R;
            JDCurveElements.GetAt(i + 1)->x   =   PtS_JD.GetAt(i + 1)->x;
            JDCurveElements.GetAt(i + 1)->y   =   -PtS_JD.GetAt(i + 1)->z;
            JDCurveElements.GetAt(i + 1)->z   =   PtS_JD.GetAt(i + 1)->y;
            float distence = JDCurveElements.GetAt(i + 1)->ZH - JDCurveElements.GetAt(i)->JDLC;
            JDCurveElements.GetAt(i + 1)->ZH_xy    = new  Cordinate;
            JDCurveElements.GetAt(i + 1)->ZH_xy->x = JDCurveElements.GetAt(i + 1)->x - JDCurveElements.GetAt(i + 1)->T * cos(JDCurveElements.GetAt(i)->fwj2);
            JDCurveElements.GetAt(i + 1)->ZH_xy->y = JDCurveElements.GetAt(i + 1)->y - JDCurveElements.GetAt(i + 1)->T * sin(JDCurveElements.GetAt(i)->fwj2);
            JDCurveElements.GetAt(i + 1)->HZ_xy    = new  Cordinate;
            JDCurveElements.GetAt(i + 1)->HZ_xy->x = JDCurveElements.GetAt(i + 1)->x + JDCurveElements.GetAt(i + 1)->T * cos(JDCurveElements.GetAt(i + 1)->fwj2);
            JDCurveElements.GetAt(i + 1)->HZ_xy->y = JDCurveElements.GetAt(i + 1)->y + JDCurveElements.GetAt(i + 1)->T * sin(JDCurveElements.GetAt(i + 1)->fwj2);
            double ptx, pty;
            float LL;
            float L0 =  JDCurveElements.GetAt(i + 1)->L0;
            int64 R   =  JDCurveElements.GetAt(i + 1)->R;
            LL       =  JDCurveElements.GetAt(i + 1)->HY - JDCurveElements.GetAt(i + 1)->ZH;
            // (ptx,pty)在缓和曲线上
            ptx = LL - LL * LL * LL * LL * LL / (40.0 * R * R * L0 * L0) + LL * LL * LL * LL * LL * LL * LL * LL * LL / (3456.0 * R * R * R * R * L0 * L0 * L0 * L0);
            pty = LL * LL * LL / (6.0 * R * L0) * (1 - LL * LL * LL * LL / (56.0 * R * R * L0 * L0) + LL * LL * LL * LL * LL * LL * LL * LL / (7040.0 * R * R * R * R * L0 * L0 * L0 * L0));
            float xita = PAI / 2.0 - JDCurveElements.GetAt(i)->fwj;
            double xc, yc;
            if (JDCurveElements.GetAt(i + 1)->RoateStyle == -1) {  // 左转
                xc = cos(xita) * ptx - sin(xita) * pty + JDCurveElements.GetAt(i + 1)->ZH_xy->x;
                yc = sin(xita) * ptx + cos(xita) * pty + JDCurveElements.GetAt(i + 1)->ZH_xy->y;
            } else if (JDCurveElements.GetAt(i + 1)->RoateStyle == 1) {  // 右转
                xc = cos(xita) * ptx + sin(xita) * pty + JDCurveElements.GetAt(i + 1)->ZH_xy->x;
                yc = sin(xita) * ptx - cos(xita) * pty + JDCurveElements.GetAt(i + 1)->ZH_xy->y;
            }
            // 缓圆点坐标(x,y)
            JDCurveElements.GetAt(i + 1)->HY_xy    = new  Cordinate;
            JDCurveElements.GetAt(i + 1)->HY_xy->x = xc;
            JDCurveElements.GetAt(i + 1)->HY_xy->y = yc;
            xita = 3 * PAI / 2.0 - JDCurveElements.GetAt(i + 1)->fwj;
            if (JDCurveElements.GetAt(i + 1)->RoateStyle == -1) {
                xc = cos(xita) * ptx + sin(xita) * pty + JDCurveElements.GetAt(i + 1)->HZ_xy->x;
                yc = sin(xita) * ptx - cos(xita) * pty + JDCurveElements.GetAt(i + 1)->HZ_xy->y;
            } else if (JDCurveElements.GetAt(i + 1)->RoateStyle == 1) {
                xc = cos(xita) * ptx - sin(xita) * pty + JDCurveElements.GetAt(i + 1)->HZ_xy->x;
                yc = sin(xita) * ptx + cos(xita) * pty + JDCurveElements.GetAt(i + 1)->HZ_xy->y;
            }
            // 圆缓点坐标(x,y)
            JDCurveElements.GetAt(i + 1)->YH_xy    = new  Cordinate;
            JDCurveElements.GetAt(i + 1)->YH_xy->x = xc;
            JDCurveElements.GetAt(i + 1)->YH_xy->y = yc;
            double dx, dy;
            dx = JDCurveElements.GetAt(i + 1)->YH_xy->x - JDCurveElements.GetAt(i + 1)->HY_xy->x;
            dy = JDCurveElements.GetAt(i + 1)->YH_xy->y - JDCurveElements.GetAt(i + 1)->HY_xy->y;
            float rAngle = atan(dy / dx);
            float peiAngle = (PAI - fabs(JDCurveElements.GetAt(i + 1)->Alfa) + L0 * 1.0 / JDCurveElements.GetAt(i + 1)->R) / 2.0;
            float thetaAngle;
            double centerx, centery;
            if (JDCurveElements.GetAt(i + 1)->RoateStyle == -1) {
                if (dx > 0) {
                    thetaAngle = peiAngle + rAngle;
                } else if (dx < 0) {
                    thetaAngle = peiAngle + rAngle + PAI;
                }
                centerx = JDCurveElements.GetAt(i + 1)->HY_xy->x + JDCurveElements.GetAt(i + 1)->R * cos(thetaAngle);
                centery = JDCurveElements.GetAt(i + 1)->HY_xy->y + JDCurveElements.GetAt(i + 1)->R * sin(thetaAngle);
            } else if (JDCurveElements.GetAt(i + 1)->RoateStyle == 1) {
                if (dx > 0) {
                    thetaAngle = peiAngle - rAngle;
                } else if (dx < 0) {
                    thetaAngle = peiAngle - rAngle + PAI;
                }
                centerx = JDCurveElements.GetAt(i + 1)->HY_xy->x + JDCurveElements.GetAt(i + 1)->R * cos(thetaAngle);
                centery = JDCurveElements.GetAt(i + 1)->HY_xy->y - JDCurveElements.GetAt(i + 1)->R * sin(thetaAngle);
            }
            // 曲线圆心x,y坐标
            JDCurveElements.GetAt(i + 1)->Cneterx = centerx;
            JDCurveElements.GetAt(i + 1)->Cnetery = centery;
        }
        PLineCurve pPreCurveElements = JDCurveElements.GetAt(PtS_JD.GetSize() - 2);
        pTempCurveElements = JDCurveElements.GetAt(PtS_JD.GetSize() - 1);
        double x1 = pPreCurveElements->HZ_xy->x;
        double y1 = pPreCurveElements->HZ_xy->y;
        double x2 = pTempCurveElements->x;
        double y2 = pTempCurveElements->y;
        double dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
        double mlc  = pPreCurveElements->HZ + dist;
        pTempCurveElements->ZH = pTempCurveElements->HZ = mlc;
        pTempCurveElements->HY = pTempCurveElements->YH = mlc;
        pTempCurveElements->JDLC = mlc;
        pTempCurveElements->L = 0;
        pTempCurveElements->T = 0;
        double m_EndLC = mlc;
        pTempCurveElements->fwj = 0;
        pTempCurveElements->fwj2 = 0;
    }
    Save3DlineZX();  // 在交点间内插点并保存到数组中,供程序调用
}


float CDesingScheme::GetDistenceXYZ(double x1, double y1, double z1, double x2, double y2, double z2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1));
}


/************************************************************************/
/* Function: 在交点间内插点并保存到数组中,供程序调用                        */
/************************************************************************/
void CDesingScheme::Save3DlineZX() {
    int32 mNCDistence = 4;
    double x1, y1, z1, x2, y2, z2, x3, y3, z3;
    float ZH_h, HZ_h;
    CString m_strPtStyle;
    PCordinate ppt;
    for (int64 i = 0; i < JDCurveElements.GetSize(); i++) {
        if (i == 0 || i == JDCurveElements.GetSize() - 1) {
            ppt = new Cordinate;
            ppt->x = PtS_JD.GetAt(i)->x;
            ppt->y = PtS_JD.GetAt(i)->y;
            ppt->z = PtS_JD.GetAt(i)->z;
            ppt->dmh = GetHeightValue(ppt->x, -ppt->z);
            ppt->Derh = ppt->y - ppt->dmh;
            ppt->strJDStyle = "交点坐标";
            ppt->Lc = JDCurveElements.GetAt(i)->ZH;
            if (i == 0) {
                PtS_3DLineZX.Add(ppt);
            } else {
                double L1 = GetDistenceXY(PtS_JD.GetAt(i - 1)->x, \
                                          PtS_JD.GetAt(i - 1)->z, PtS_JD.GetAt(i)->x, \
                                          PtS_JD.GetAt(i)->z);
                double L2 = GetDistenceXY(PtS_JD.GetAt(i - 1)->x, \
                                          PtS_JD.GetAt(i - 1)->z, \
                                          JDCurveElements.GetAt(i - 1)->HZ_xy->x, \
                                          -JDCurveElements.GetAt(i - 1)->HZ_xy->y);
                y1 = PtS_JD.GetAt(i - 1)->y;
                y2 = PtS_JD.GetAt(i)->y;
                float  HZ_h = y1 + L2 / L1 * (y2 - y1);
                float  ZH_h = PtS_JD.GetAt(i)->y;
                double LZH2 = JDCurveElements.GetAt(i)->ZH - JDCurveElements.GetAt(i - 1)->HZ;
                // 內插点
                NeiChaDian(LZH2, \
                           JDCurveElements.GetAt(i - 1)->HZ_xy->x, \
                           HZ_h, \
                           -JDCurveElements.GetAt(i - 1)->HZ_xy->y, \
                           JDCurveElements.GetAt(i)->ZH_xy->x, \
                           ZH_h, \
                           -JDCurveElements.GetAt(i)->ZH_xy->y, JDCurveElements.GetAt(i - 1)->HZ\
                          );
                PtS_3DLineZX.RemoveAt(PtS_3DLineZX.GetSize() - 1);
                PtS_3DLineZX.Add(ppt);
            }
        } else if (i > 0 && i < JDCurveElements.GetSize() - 1) {  // 当前交点i不是方案的最后一个交点,有缓和曲线段,曲线段
            x1 = PtS_JD.GetAt(i - 1)->x;
            y1 = PtS_JD.GetAt(i - 1)->y;
            z1 = PtS_JD.GetAt(i - 1)->z;
            x2 = PtS_JD.GetAt(i)->x;
            y2 = PtS_JD.GetAt(i)->y;
            z2 = PtS_JD.GetAt(i)->z;
            x3 = PtS_JD.GetAt(i + 1)->x;
            y3 = PtS_JD.GetAt(i + 1)->y;
            z3 = PtS_JD.GetAt(i + 1)->z;
            double L1 = GetDistenceXY(x1, z1, x2, z2);
            double tx = JDCurveElements.GetAt(i)->ZH_xy->x;
            double tz = -JDCurveElements.GetAt(i)->ZH_xy->y;
            double LZH = GetDistenceXY(x1, z1, tx, tz);
            ZH_h = y1 + LZH / L1 * (y2 - y1);
            double LZH2 = GetDistenceXY(\
                                        JDCurveElements.GetAt(i - 1)->HZ_xy->x, \
                                        -JDCurveElements.GetAt(i - 1)->HZ_xy->y, \
                                        JDCurveElements.GetAt(i)->ZH_xy->x, \
                                        -JDCurveElements.GetAt(i)->ZH_xy->y);
            tx = JDCurveElements.GetAt(i - 1)->HZ_xy->x;
            tz = -JDCurveElements.GetAt(i - 1)->HZ_xy->y;
            double LHZ = GetDistenceXY(x1, z1, tx, tz);
            HZ_h = y1 + LHZ / L1 * (y2 - y1);
            NeiChaDian(LZH2, \
                       JDCurveElements.GetAt(i - 1)->HZ_xy->x, \
                       HZ_h, \
                       -JDCurveElements.GetAt(i - 1)->HZ_xy->y, \
                       JDCurveElements.GetAt(i)->ZH_xy->x, \
                       ZH_h, \
                       -JDCurveElements.GetAt(i)->ZH_xy->y, \
                       JDCurveElements.GetAt(i - 1)->HZ);
            L1 = GetDistenceXY(x2, z2, x3, z3);
            tx = JDCurveElements.GetAt(i)->HZ_xy->x;
            tz = -JDCurveElements.GetAt(i)->HZ_xy->y;
            LHZ = GetDistenceXY(x2, z2, tx, tz);
            HZ_h = y2 + LHZ / L1 * (y3 - y2);
            float Derh = HZ_h - ZH_h;
            float LL = JDCurveElements.GetAt(i)->HZ - JDCurveElements.GetAt(i)->ZH;
            float L0 = JDCurveElements.GetAt(i)->L0;
            BOOL bEnd = FALSE;
            float k = 0;
            while (k < L0 && bEnd == FALSE) {
                float h = ZH_h + k * Derh / LL;
                k += mNCDistence;
                if (k > L0) {
                    k = L0;
                    bEnd = TRUE;
                }
                GetQLXY(L0, JDCurveElements.GetAt(i)->R, \
                        JDCurveElements.GetAt(i)->RoateStyle, \
                        k, JDCurveElements.GetAt(i - 1)->fwj, \
                        JDCurveElements.GetAt(i)->ZH_xy->x, \
                        JDCurveElements.GetAt(i)->ZH_xy->y, 0, 0, &x1, &y1, 1);
                if (k == L0)
                    m_strPtStyle = "缓圆点坐标";
                else
                    m_strPtStyle = "前缓和曲线段点坐标";
                ppt = new Cordinate;
                ppt->x = x1;
                ppt->y = h;
                ppt->z = -y1;
                ppt->dmh = GetHeightValue(ppt->x, -ppt->z);
                ppt->Derh = ppt->y - ppt->dmh;
                ppt->strJDStyle = m_strPtStyle;
                ppt->Lc = k + JDCurveElements.GetAt(i)->ZH;
                PtS_3DLineZX.Add(ppt);
            }
            float Ly = JDCurveElements.GetAt(i)->Ly;
            k = 0;
            bEnd = FALSE;
            while (k < Ly && bEnd == FALSE) {
                k += mNCDistence;
                if (k > Ly) {
                    k = Ly;
                    bEnd = TRUE;
                }
                float h = ZH_h + (k + L0) * Derh / LL;
                GetYQXXY(JDCurveElements.GetAt(i)->Cneterx, JDCurveElements.GetAt(i)->Cnetery, \
                         JDCurveElements.GetAt(i)->R, JDCurveElements.GetAt(i)->RoateStyle, \
                         k, JDCurveElements.GetAt(i)->Alfa, JDCurveElements.GetAt(i)->HY_xy->x, \
                         JDCurveElements.GetAt(i)->HY_xy->y, \
                         JDCurveElements.GetAt(i)->YH_xy->x, JDCurveElements.GetAt(i)->YH_xy->y, \
                         &x1, &y1);
                if (k == Ly)
                    m_strPtStyle = "圆缓点坐标";
                else
                    m_strPtStyle = "圆曲线段点坐标";
                ppt = new Cordinate;
                ppt->x = x1;
                ppt->y = h;
                ppt->z = -y1;
                ppt->dmh = GetHeightValue(ppt->x, -ppt->z);
                ppt->Derh = ppt->y - ppt->dmh;
                ppt->strJDStyle = m_strPtStyle;
                ppt->Lc = k + JDCurveElements.GetAt(i)->HY;
                PtS_3DLineZX.Add(ppt);
            }
            k = L0;
            bEnd = FALSE;
            float L3 = JDCurveElements.GetAt(i)->YH - JDCurveElements.GetAt(i)->ZH;
            while (k > 0 && bEnd == FALSE) {
                k -= mNCDistence;
                float h = ZH_h + ((L0 - k) + L3) * Derh / LL;
                if (k < 0) {
                    k = 0;
                    bEnd = FALSE;
                }
                GetQLXY(L0, JDCurveElements.GetAt(i)->R, JDCurveElements.GetAt(i)->RoateStyle, \
                        k, JDCurveElements.GetAt(i)->fwj, 0, 0, JDCurveElements.GetAt(i)->HZ_xy->x, \
                        JDCurveElements.GetAt(i)->HZ_xy->y, &x1, &y1, 2);
                if (k == 0)
                    m_strPtStyle = "缓直点坐标";
                else
                    m_strPtStyle = "后缓和曲线段点坐标";
                ppt = new Cordinate;
                ppt->x = x1;
                ppt->y = h;
                ppt->z = -y1;
                ppt->dmh = GetHeightValue(ppt->x, -ppt->z);
                ppt->Derh = ppt->y - ppt->dmh;
                ppt->strJDStyle = m_strPtStyle;
                ppt->Lc = (L0 - k) + JDCurveElements.GetAt(i)->YH;
                PtS_3DLineZX.Add(ppt);
            }
        }
    }
}


/************************************************************************/
/* Function: 內插点                                                     */
/************************************************************************/
void CDesingScheme::NeiChaDian(float ZHLength, double x1, double y1, double z1, double x2, double y2, double z2, double lc) {
    float inputArr[3][2];  // 记录3点
    inputArr[0][0] = x1;
    inputArr[0][1] = y1;
    inputArr[2][0] = x2;
    inputArr[2][1] = y2;
    float outPutArr[3] = {0};  // 系数
    float h;
    int32 m_XX;
    double x, z;
    float dx, dz;
    float mangle;
    PCordinate ppt;
    dx = x2 - x1;
    dz = z2 - z1;
    if (fabs(dx) <= 0.000001) {
        if (z2 < z1)
            mangle = PAI / 2.0;
        else
            mangle = PAI * 3 / 2.0;
    } else {
        mangle = atan(fabs(dz / dx));
        if (dx >= 0 && dz <= 0)
            m_XX = 1;
        else if (dx <= 0 && dz <= 0)
            m_XX = 2;
        else if (dx <= 0 && dz >= 0)
            m_XX = 3;
        else if (dx >= 0 && dz >= 0)
            m_XX = 4;
    }
    bool is_height_enough_flag = false;
    float lt = 0;
    float dh = (y2 - y1) / ZHLength;
    float tmpMaxH = 0;
    while (lt < ZHLength) {
        lt += 10;
        if (lt > ZHLength)
            break;
        h = y1 + lt * dh;
        switch (m_XX) {
            case 1:
                x = lt * cos(mangle) + x1;
                z = -lt * sin(mangle) + z1;
                break;
            case 2:
                x = -lt * cos(mangle) + x1;
                z = -lt * sin(mangle) + z1;
                break;
            case 3:
                x = -lt * cos(mangle) + x1;
                z = lt * sin(mangle) + z1;
                break;
            case 4:
                x = lt * cos(mangle) + x1;
                z = lt * sin(mangle) + z1;
                break;
        }
        if (GetHeightValue(x, z) > g_max_height - 10) {
            if (GetHeightValue(x, z) > tmpMaxH) {
                tmpMaxH = GetHeightValue(x, z);
                inputArr[1][0] = x;
                inputArr[1][1] = tmpMaxH + 5;
            }
            is_height_enough_flag = true;
        }
    }
    if (is_height_enough_flag) {
        CLeastSquares tmpLS;
        tmpLS.process(inputArr, outPutArr);
    }
    if (is_height_enough_flag) {
        lt = 0;
        dh = (y2 - y1) / ZHLength;
        while (lt < ZHLength) {
            lt += 10;
            if (lt > ZHLength)
                break;
            switch (m_XX) {
                case 1:
                    x = lt * cos(mangle) + x1;
                    z = -lt * sin(mangle) + z1;
                    break;
                case 2:
                    x = -lt * cos(mangle) + x1;
                    z = -lt * sin(mangle) + z1;
                    break;
                case 3:
                    x = -lt * cos(mangle) + x1;
                    z = lt * sin(mangle) + z1;
                    break;
                case 4:
                    x = lt * cos(mangle) + x1;
                    z = lt * sin(mangle) + z1;
                    break;
            }
            // h = GetHeightValue(x,z) + 10;
            h = outPutArr[0] + outPutArr[1] * x + outPutArr[2] * x * x;
            ppt = new Cordinate;
            ppt->x = x;
            ppt->y = h;
            ppt->z = z;
            ppt->dmh = GetHeightValue(ppt->x, -ppt->z);
            ppt->Derh = ppt->y - ppt->dmh;
            ppt->strJDStyle = "交点-直缓点坐标";
            ppt->Lc = lc + lt;
            PtS_3DLineZX.Add(ppt);
        }
    } else {
        lt = 0;
        dh = (y2 - y1) / ZHLength;
        while (lt < ZHLength) {
            lt += 10;
            if (lt > ZHLength)
                break;
            h = y1 + lt * dh;
            switch (m_XX) {
                case 1:
                    x = lt * cos(mangle) + x1;
                    z = -lt * sin(mangle) + z1;
                    break;
                case 2:
                    x = -lt * cos(mangle) + x1;
                    z = -lt * sin(mangle) + z1;
                    break;
                case 3:
                    x = -lt * cos(mangle) + x1;
                    z = lt * sin(mangle) + z1;
                    break;
                case 4:
                    x = lt * cos(mangle) + x1;
                    z = lt * sin(mangle) + z1;
                    break;
            }
            ppt = new Cordinate;
            ppt->x = x;
            ppt->y = h;
            ppt->z = z;
            ppt->dmh = GetHeightValue(ppt->x, -ppt->z);
            ppt->Derh = ppt->y - ppt->dmh;
            ppt->strJDStyle = "交点-直缓点坐标";
            ppt->Lc = lc + lt;
            PtS_3DLineZX.Add(ppt);
        }
    }
    ppt = new Cordinate;
    ppt->x = x2;
    ppt->y = y2;
    ppt->z = z2;
    ppt->dmh = GetHeightValue(ppt->x, -ppt->z);
    ppt->Derh = ppt->y - ppt->dmh;
    ppt->strJDStyle = "直缓点坐标";
    ppt->Lc = lc + ZHLength;
    PtS_3DLineZX.Add(ppt);
}


/************************************************************************/
/* Function: 计算[缓和曲线段]上点的坐标                                 */
/************************************************************************/
void CDesingScheme::GetQLXY(float L0, int64 R, int32 RoateStyle, float LL, float fwj, double ZH_xy_x, double ZH_xy_y, double HZ_xy_x, double HZ_xy_y, double* xc, double* yc, int32 Q_H_L) {
    double ptx, pty;
    ptx = LL - LL * LL * LL * LL * LL / (40.0 * R * R * L0 * L0) + LL * LL * LL * LL * LL * LL * LL * LL * LL / (3456.0 * R * R * R * R * L0 * L0 * L0 * L0);
    pty = LL * LL * LL / (6.0 * R * L0) * (1 - LL * LL * LL * LL / (56.0 * R * R * L0 * L0) + LL * LL * LL * LL * LL * LL * LL * LL / (7040.0 * R * R * R * R * L0 * L0 * L0 * L0));
    float xita;
    if (Q_H_L == 1) {
        xita = PAI / 2.0 - fwj;
        if (RoateStyle == -1) {
            *xc = cos(xita) * ptx - sin(xita) * pty + ZH_xy_x;
            *yc = sin(xita) * ptx + cos(xita) * pty + ZH_xy_y;
        } else if (RoateStyle == 1) {
            *xc = cos(xita) * ptx + sin(xita) * pty + ZH_xy_x;
            *yc = sin(xita) * ptx - cos(xita) * pty + ZH_xy_y;
        }
    } else {
        xita = 3 * PAI / 2.0 - fwj;
        if (RoateStyle == -1) {
            *xc = cos(xita) * ptx + sin(xita) * pty + HZ_xy_x;
            *yc = sin(xita) * ptx - cos(xita) * pty + HZ_xy_y;
        } else if (RoateStyle == 1) {
            *xc = cos(xita) * ptx - sin(xita) * pty + HZ_xy_x;
            *yc = sin(xita) * ptx + cos(xita) * pty + HZ_xy_y;
        }
    }
}


/************************************************************************/
/* Function: 计算[圆曲线]上点的坐标                                     */
/************************************************************************/
void CDesingScheme::GetYQXXY(double centerx, double centery, int64 R, int32 RoateStyle, float LL, float alfa, double HY_xy_x, double HY_xy_y, double YH_xy_x, double YH_xy_y, double* xc, double* yc) {
    double dx, dy;
    dx = HY_xy_x - centerx;
    dy = HY_xy_y - centery;
    float peiAngle = atan(dy / dx);
    float thetaAngle = LL * 1.0 / R;
    float rAngle;
    if (RoateStyle == -1) {
        if (dx > 0) {
            rAngle = peiAngle + thetaAngle;
        } else if (dx < 0) {
            rAngle = peiAngle + thetaAngle - PAI;
        }
    } else if (RoateStyle == 1) {
        if (dx > 0) {
            rAngle = peiAngle - thetaAngle;
        } else if (dx < 0) {
            rAngle = peiAngle - thetaAngle + PAI;
        }
    }
    *xc = centerx + R * cos(rAngle);
    *yc = centery + R * sin(rAngle);
}


/************************************************************************/
/* Function:  计算边坡与在面的交点坐标                                      */
/************************************************************************/
void CDesingScheme::GetDMJD(double x1, double y1, double z1, double x2, double y2, double z2, \
                            float L, float h0, double x0, double z0, int32 TW, int32 LeftRight, \
                            double tx0, double ty0, double tz0, double tx1, double ty1, double tz1, double mLC, CString strJDstyle) {
    double x11, y11, z11, x12, y12, z12;
    double x21, y21, z21, x22, y22, z22;
    float L1, mangle;
    float dx = x2 - x1;
    float dz = z2 - z1;
    PLuQianHuPo ptt;
    ptt = new LuQianHuPo;
    float m_Lj_Dh = 0.6;  // 碴肩至碴脚的高度
    // 根据规范设置的 路堤 护坡数值
    float Lt_h1 = 6;        // 1级边坡坡高
    float Lt_h2 = 12;       // 2级边坡坡高
    float Lt_m1 = 1.5;      // 1级边坡坡率
    float Lt_m2 = 1.75;     // 2级边坡坡率
    float Lt_b = 2.0;       // 边坡平台宽度
    float Lt_h3 = ty0 - Lt_h1 - Lt_h2;      // 2级边坡坡高
    float Lt_m3 = 0.45;                     // 1级边坡坡率
    // ----------------------------------------------------------
    if (LeftRight == -1) {  // 左侧边坡
        ptt->Huponums_L = 3;
        /************************************************************************/
        /*                              一级边坡                                 */
        /************************************************************************/
        // 点1
        ptt->HuPo_L[0].Hp[0].x = tx0;
        ptt->HuPo_L[0].Hp[0].y = ty0;
        ptt->HuPo_L[0].Hp[0].z = tz0;
        // 点2
        ptt->HuPo_L[0].Hp[1].x = tx1;
        ptt->HuPo_L[0].Hp[1].y = ty1;
        ptt->HuPo_L[0].Hp[1].z = tz1;
        // 点3
        L1 = L + Lt_h1 * Lt_m1;
        Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
        ptt->HuPo_L[0].Hp[2].x = x11;
        ptt->HuPo_L[0].Hp[2].y = y11 - m_Lj_Dh - Lt_h1;
        ptt->HuPo_L[0].Hp[2].z = z11;
        // 一级护坡的高度、边坡坡率、边坡类型
        ptt->HuPo_L[0].h = Lt_h1; /**/ ptt->HuPo_L[0].m = Lt_m1; /**/ ptt->HuPo_L[0].style = 0;
        /************************************************************************/
        /*                              二级边坡                                 */
        /************************************************************************/
        // 点1
        // 一级护坡的最后1个点 与 二级护坡的第1个点重合
        ptt->HuPo_L[1].Hp[0].x = ptt->HuPo_L[0].Hp[2].x;
        ptt->HuPo_L[1].Hp[0].y = ptt->HuPo_L[0].Hp[2].y;
        ptt->HuPo_L[1].Hp[0].z = ptt->HuPo_L[0].Hp[2].z;
        // 点2
        L1 = L + Lt_h1 * Lt_m1 + Lt_b;
        Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
        ptt->HuPo_L[1].Hp[1].x = x11;
        ptt->HuPo_L[1].Hp[1].y = ptt->HuPo_L[1].Hp[0].y;
        ptt->HuPo_L[1].Hp[1].z = z11;
        // 点3
        L1 = L + Lt_h1 * Lt_m1 + Lt_b + Lt_h2 * Lt_m2;
        Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
        ptt->HuPo_L[1].Hp[2].x = x11;
        ptt->HuPo_L[1].Hp[2].y = y11 - m_Lj_Dh - Lt_h1 - Lt_h2;
        ptt->HuPo_L[1].Hp[2].z = z11;
        // 二级护坡的高度、边坡坡率、边坡平台宽度、边坡类型
        ptt->HuPo_L[1].h = Lt_h2;
        ptt->HuPo_L[1].m = Lt_m2;
        ptt->HuPo_L[1].b = Lt_b;
        ptt->HuPo_L[1].style = 1;
        /************************************************************************/
        /*                              三级边坡                                 */
        /************************************************************************/
        // 点1
        ptt->HuPo_L[2].Hp[0].x = ptt->HuPo_L[1].Hp[2].x;
        ptt->HuPo_L[2].Hp[0].y = ptt->HuPo_L[1].Hp[2].y;
        ptt->HuPo_L[2].Hp[0].z = ptt->HuPo_L[1].Hp[2].z;
        // 点2
        L1 = L + Lt_h1 * Lt_m1 + Lt_b + Lt_h2 * Lt_m2 + Lt_b;
        Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
        ptt->HuPo_L[2].Hp[1].x = x11;
        ptt->HuPo_L[2].Hp[1].y = ptt->HuPo_L[2].Hp[0].y;
        ptt->HuPo_L[2].Hp[1].z = z11;
        // 点3
        L1 = L + Lt_h1 * Lt_m1 + Lt_b + Lt_h2 * Lt_m2 + Lt_b + Lt_h3 * Lt_m3;
        Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
        ptt->HuPo_L[2].Hp[2].x = x11;
        ptt->HuPo_L[2].Hp[2].y = y11 - m_Lj_Dh - Lt_h1 - Lt_h2 - Lt_h3;
        ptt->HuPo_L[2].Hp[2].z = z11;
        ptt->HuPo_L[2].m     = Lt_m3;
        ptt->HuPo_L[2].b = Lt_b;
        ptt->HuPo_L[2].style = 2;
        PtS_HuPo.Add(ptt);
        int64 MN = PtS_HuPo.GetSize() - 1;
        PtS_HuPo.GetAt(MN)->TW_left = TW;
        PtS_HuPo.GetAt(MN)->Lc = mLC;
        PtS_HuPo.GetAt(MN)->strJDStyle = strJDstyle;
    }  // End 左侧边坡
    else if (LeftRight == 1) {  // 右侧边坡
        ptt = PtS_HuPo.GetAt(PtS_HuPo.GetSize() - 1);
        ptt->Huponums_R = 3;
        /************************************************************************/
        /*                              一级边坡                                 */
        /************************************************************************/
        // 点1
        ptt->HuPo_R[0].Hp[0].x = tx0;
        ptt->HuPo_R[0].Hp[0].y = ty0;
        ptt->HuPo_R[0].Hp[0].z = tz0;
        // 点2
        ptt->HuPo_R[0].Hp[1].x = tx1;
        ptt->HuPo_R[0].Hp[1].y = ty1;
        ptt->HuPo_R[0].Hp[1].z = tz1;
        // 点3
        L1 = L + Lt_h1 * Lt_m1;
        Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
        ptt->HuPo_R[0].Hp[2].x = x12;
        ptt->HuPo_R[0].Hp[2].y = y12 - m_Lj_Dh - Lt_h1;
        ptt->HuPo_R[0].Hp[2].z = z12;
        // 一级护坡的高度、边坡坡率、边坡类型
        ptt->HuPo_R[0].h = Lt_h1; /**/ ptt->HuPo_R[0].m = Lt_m1; /**/ ptt->HuPo_R[0].style = 0;
        /************************************************************************/
        /*                              二级边坡                                 */
        /************************************************************************/
        // 点1
        // 一级护坡的最后1个点 与 二级护坡的第1个点重合
        ptt->HuPo_R[1].Hp[0].x = ptt->HuPo_R[0].Hp[2].x;
        ptt->HuPo_R[1].Hp[0].y = ptt->HuPo_R[0].Hp[2].y;
        ptt->HuPo_R[1].Hp[0].z = ptt->HuPo_R[0].Hp[2].z;
        // 点2
        L1 = L + Lt_h1 * Lt_m1 + Lt_b;
        Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
        ptt->HuPo_R[1].Hp[1].x = x12;
        ptt->HuPo_R[1].Hp[1].y = ptt->HuPo_R[1].Hp[0].y;
        ptt->HuPo_R[1].Hp[1].z = z12;
        // 点3
        L1 = L + Lt_h1 * Lt_m1 + Lt_b + Lt_h2 * Lt_m2;
        Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
        ptt->HuPo_R[1].Hp[2].x = x12;
        ptt->HuPo_R[1].Hp[2].y = y12 - m_Lj_Dh - Lt_h1 - Lt_h2;
        ptt->HuPo_R[1].Hp[2].z = z12;
        // 二级护坡的高度、边坡坡率、边坡平台宽度、边坡类型
        ptt->HuPo_R[1].h = Lt_h2;
        ptt->HuPo_R[1].m = Lt_m2;
        ptt->HuPo_R[1].b = Lt_b;
        ptt->HuPo_R[1].style = 1;
        /************************************************************************/
        /*                              三级边坡                                 */
        /************************************************************************/
        // 点1
        ptt->HuPo_R[2].Hp[0].x = ptt->HuPo_R[1].Hp[2].x;
        ptt->HuPo_R[2].Hp[0].y = ptt->HuPo_R[1].Hp[2].y;
        ptt->HuPo_R[2].Hp[0].z = ptt->HuPo_R[1].Hp[2].z;
        // 点2
        L1 = L + Lt_h1 * Lt_m1 + Lt_b + Lt_h2 * Lt_m2 + Lt_b;
        Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
        ptt->HuPo_R[2].Hp[1].x = x12;
        ptt->HuPo_R[2].Hp[1].y = ptt->HuPo_R[2].Hp[0].y;
        ptt->HuPo_R[2].Hp[1].z = z12;
        // 点3
        L1 = L + Lt_h1 * Lt_m1 + Lt_b + Lt_h2 * Lt_m2 + Lt_b + Lt_h3 * Lt_m3;
        Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
        ptt->HuPo_R[2].Hp[2].x = x12;
        ptt->HuPo_R[2].Hp[2].y = y12 - m_Lj_Dh - Lt_h1 - Lt_h2 - Lt_h3;
        ptt->HuPo_R[2].Hp[2].z = z12;
        ptt->HuPo_R[2].m     = Lt_m3;
        ptt->HuPo_R[2].b = Lt_b;
        ptt->HuPo_R[2].style = 2;
        int64 MN = PtS_HuPo.GetSize() - 1;
        PtS_HuPo.GetAt(MN)->TW_right = TW;
    }  // End 右侧边坡
    // ----------------------------------------------------------
}



/************************************************************************/
/* Function: 计算终点处边坡与面的交点坐标                                   */
/************************************************************************/
void CDesingScheme::GetDMJDLast(double x1, double y1, double z1, double x2, double y2, double z2, \
                                float L, float h0, double x0, double z0, int32 TW, int32 LeftRight, \
                                double tx0, double ty0, double tz0, double tx1, double ty1, double tz1, double mLC, CString strJDstyle) {
    double x11, y11, z11, x12, y12, z12;
    double x21, y21, z21, x22, y22, z22;
    float L1, mangle;
    float dx = x2 - x1;
    float dz = z2 - z1;
    PLuQianHuPo ptt;
    ptt = new LuQianHuPo;
    float m_Lj_Dh = 0.6;  // 碴肩至碴脚的高度
    // 根据规范设置的 路堤 护坡数值
    float Lt_h1 = 6;        // 1级边坡坡高
    float Lt_h2 = 12;       // 2级边坡坡高
    float Lt_m1 = 1.5;      // 1级边坡坡率
    float Lt_m2 = 1.75;     // 2级边坡坡率
    float Lt_b = 2.0;       // 边坡平台宽度
    float Lt_h3 = ty0 - Lt_h1 - Lt_h2;      // 2级边坡坡高
    float Lt_m3 = 0.45;                     // 1级边坡坡率
    // ----------------------------------------------------------
    if (LeftRight == -1) {  // 左侧边坡
        ptt->Huponums_L = 3;
        /************************************************************************/
        /*                              一级边坡                                 */
        /************************************************************************/
        // 点1
        ptt->HuPo_L[0].Hp[0].x = tx0; /**/ ptt->HuPo_L[0].Hp[0].y = ty0;  /**/ ptt->HuPo_L[0].Hp[0].z = tz0;
        // 点2
        ptt->HuPo_L[0].Hp[1].x = tx1; /**/ ptt->HuPo_L[0].Hp[1].y = ty1;  /**/ ptt->HuPo_L[0].Hp[1].z = tz1;
        // 点3
        L1 = L + Lt_h1 * Lt_m1;
        Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
        ptt->HuPo_L[0].Hp[2].x = x21;
        ptt->HuPo_L[0].Hp[2].y = y21 - m_Lj_Dh - Lt_h1;
        ptt->HuPo_L[0].Hp[2].z = z21;
        // 一级护坡的高度、边坡坡率、边坡类型
        ptt->HuPo_L[0].h = Lt_h1;
        ptt->HuPo_L[0].m = Lt_m1;
        ptt->HuPo_L[0].style = 0;
        /************************************************************************/
        /*                              二级边坡                                 */
        /************************************************************************/
        // 点1
        // 一级护坡的最后1个点 与 二级护坡的第1个点重合
        ptt->HuPo_L[1].Hp[0].x = ptt->HuPo_L[0].Hp[2].x;
        ptt->HuPo_L[1].Hp[0].y = ptt->HuPo_L[0].Hp[2].y;
        ptt->HuPo_L[1].Hp[0].z = ptt->HuPo_L[0].Hp[2].z;
        // 点2
        L1 = L + Lt_h1 * Lt_m1 + Lt_b;
        Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
        ptt->HuPo_L[1].Hp[1].x = x21;
        ptt->HuPo_L[1].Hp[1].y = ptt->HuPo_L[1].Hp[0].y;
        ptt->HuPo_L[1].Hp[1].z = z21;
        // 点3
        L1 = L + Lt_h1 * Lt_m1 + Lt_b + Lt_h2 * Lt_m2;
        Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
        ptt->HuPo_L[1].Hp[2].x = x21;
        ptt->HuPo_L[1].Hp[2].y = y21 - m_Lj_Dh - Lt_h1 - Lt_h2;
        ptt->HuPo_L[1].Hp[2].z = z21;
        // 二级护坡的高度、边坡坡率、边坡平台宽度、边坡类型
        ptt->HuPo_L[1].h = Lt_h2;
        ptt->HuPo_L[1].m = Lt_m2;
        ptt->HuPo_L[1].b = Lt_b;
        ptt->HuPo_L[1].style = 1;
        /************************************************************************/
        /*                              三级边坡                                 */
        /************************************************************************/
        // 点1
        ptt->HuPo_L[2].Hp[0].x = ptt->HuPo_L[1].Hp[2].x;
        ptt->HuPo_L[2].Hp[0].y = ptt->HuPo_L[1].Hp[2].y;
        ptt->HuPo_L[2].Hp[0].z = ptt->HuPo_L[1].Hp[2].z;
        // 点2
        L1 = L + Lt_h1 * Lt_m1 + Lt_b + Lt_h2 * Lt_m2 + Lt_b;
        Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
        ptt->HuPo_L[2].Hp[1].x = x21;
        ptt->HuPo_L[2].Hp[1].y = ptt->HuPo_L[2].Hp[0].y;
        ptt->HuPo_L[2].Hp[1].z = z21;
        // 点3
        L1 = L + Lt_h1 * Lt_m1 + Lt_b + Lt_h2 * Lt_m2 + Lt_b + Lt_h3 * Lt_m3;
        Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
        ptt->HuPo_L[2].Hp[2].x = x21;
        ptt->HuPo_L[2].Hp[2].y = y21 - m_Lj_Dh - Lt_h1 - Lt_h2 - Lt_h3;
        ptt->HuPo_L[2].Hp[2].z = z21;
        ptt->HuPo_L[2].m     = Lt_m3;
        ptt->HuPo_L[2].b = Lt_b;
        ptt->HuPo_L[2].style = 2;
        PtS_HuPo.Add(ptt);
        int64 MN = PtS_HuPo.GetSize() - 1;
        PtS_HuPo.GetAt(MN)->TW_left = TW;
        PtS_HuPo.GetAt(MN)->Lc = mLC;
        PtS_HuPo.GetAt(MN)->strJDStyle = strJDstyle;
    }  // End 左侧边坡
    else if (LeftRight == 1) {  // 右侧边坡
        ptt = PtS_HuPo.GetAt(PtS_HuPo.GetSize() - 1);
        ptt->Huponums_R = 3;
        /************************************************************************/
        /*                              一级边坡                                 */
        /************************************************************************/
        // 点1
        ptt->HuPo_R[0].Hp[0].x = tx0;
        ptt->HuPo_R[0].Hp[0].y = ty0;
        ptt->HuPo_R[0].Hp[0].z = tz0;
        // 点2
        ptt->HuPo_R[0].Hp[1].x = tx1;
        ptt->HuPo_R[0].Hp[1].y = ty1;
        ptt->HuPo_R[0].Hp[1].z = tz1;
        // 点3
        L1 = L + Lt_h1 * Lt_m1;
        Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
        ptt->HuPo_R[0].Hp[2].x = x22;
        ptt->HuPo_R[0].Hp[2].y = y22 - m_Lj_Dh - Lt_h1;
        ptt->HuPo_R[0].Hp[2].z = z22;
        // 一级护坡的高度、边坡坡率、边坡类型
        ptt->HuPo_R[0].h = Lt_h1; /**/ ptt->HuPo_R[0].m = Lt_m1; /**/ ptt->HuPo_R[0].style = 0;
        /************************************************************************/
        /*                              二级边坡                                 */
        /************************************************************************/
        // 点1
        // 一级护坡的最后1个点 与 二级护坡的第1个点重合
        ptt->HuPo_R[1].Hp[0].x = ptt->HuPo_R[0].Hp[2].x;
        ptt->HuPo_R[1].Hp[0].y = ptt->HuPo_R[0].Hp[2].y;
        ptt->HuPo_R[1].Hp[0].z = ptt->HuPo_R[0].Hp[2].z;
        // 点2
        L1 = L + Lt_h1 * Lt_m1 + Lt_b;
        Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
        ptt->HuPo_R[1].Hp[1].x = x22;
        ptt->HuPo_R[1].Hp[1].y = ptt->HuPo_R[1].Hp[0].y;
        ptt->HuPo_R[1].Hp[1].z = z22;
        // 点3
        L1 = L + Lt_h1 * Lt_m1 + Lt_b + Lt_h2 * Lt_m2;
        Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
        ptt->HuPo_R[1].Hp[2].x = x22;
        ptt->HuPo_R[1].Hp[2].y = y22 - m_Lj_Dh - Lt_h1 - Lt_h2;
        ptt->HuPo_R[1].Hp[2].z = z22;
        // 二级护坡的高度、边坡坡率、边坡平台宽度、边坡类型
        ptt->HuPo_R[1].h = Lt_h2;
        ptt->HuPo_R[1].m = Lt_m2;
        ptt->HuPo_R[1].b = Lt_b;
        ptt->HuPo_R[1].style = 1;
        /************************************************************************/
        /*                              三级边坡                                 */
        /************************************************************************/
        // 点1
        ptt->HuPo_R[2].Hp[0].x = ptt->HuPo_R[1].Hp[2].x;
        ptt->HuPo_R[2].Hp[0].y = ptt->HuPo_R[1].Hp[2].y;
        ptt->HuPo_R[2].Hp[0].z = ptt->HuPo_R[1].Hp[2].z;
        // 点2
        L1 = L + Lt_h1 * Lt_m1 + Lt_b + Lt_h2 * Lt_m2 + Lt_b;
        Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
        ptt->HuPo_R[2].Hp[1].x = x22;
        ptt->HuPo_R[2].Hp[1].y = ptt->HuPo_R[2].Hp[0].y;
        ptt->HuPo_R[2].Hp[1].z = z22;
        // 点3
        L1 = L + Lt_h1 * Lt_m1 + Lt_b + Lt_h2 * Lt_m2 + Lt_b + Lt_h3 * Lt_m3;
        Get3DCorrdinate(x1, y1, z1, x2, y2, z2, dx, dz, L1, &x11, &y11, &z11, &x12, &y12, &z12, &x21, &y21, &z21, &x22, &y22, &z22, &mangle);
        ptt->HuPo_R[2].Hp[2].x = x22;
        ptt->HuPo_R[2].Hp[2].y = y22 - m_Lj_Dh - Lt_h1 - Lt_h2 - Lt_h3;
        ptt->HuPo_R[2].Hp[2].z = z22;
        ptt->HuPo_R[2].m     = Lt_m3;
        ptt->HuPo_R[2].b = Lt_b;
        ptt->HuPo_R[2].style = 2;
        int64 MN = PtS_HuPo.GetSize() - 1;
        PtS_HuPo.GetAt(MN)->TW_right = TW;
    }  // End 右侧边坡
    // ----------------------------------------------------------
}




/************************************************************************/
/* Function:  计算边坡点与地面线的交点坐标                                  */
/************************************************************************/
void CDesingScheme::GetBpJD(float H0, float Afla, float mangle, double x0, double z0, int32 bsignTW, int32 mLeftRight, double* tx, double* ty, double* tz) {
    double xx, zz;
    float L = 0.1;
    float h1 = -999;
    float hNew = -9999;
    float m_bc = 0.2;
    float DerC = 0.05;
    while (fabs(h1 - hNew) > DerC) {
        h1 = H0 - bsignTW * L * sin(Afla);
        hNew = GetH(L, Afla, mangle, x0, z0, mLeftRight, &xx, &zz);  // 对应的地面高程
        if (bsignTW == -1) {
            if (h1 - hNew > 0) {  // 如果超出了地面
                hNew = h1;
            } else {  // 还是低于地面线
                L = L * 1.1;
            }
        } else  if (bsignTW == 1) {
            if (h1 - hNew < 0) {
                hNew = h1;
            } else {
                L = L * 1.1;
            }
        }
    }
    if (fabs(h1 - hNew) < DerC) {
        if (mLeftRight == -1) {
            *tx = xx;
            *ty = hNew;
            *tz = zz;
        } else {
            *tx = xx;
            *ty = hNew;
            *tz = zz;
        }
    }
}

float CDesingScheme::GetH(float L, float Afla, float mAngle, double x0, double z0, int32 mLeftRight, double* xx, double* zz) {
    double x, z;
    float peita;
    if (mAngle >= 0 && mAngle <= PAI / 2.0) {
        peita = PAI / 2 - mAngle;
        x = mLeftRight * L * cos(Afla) * cos(peita) + x0;
        z = mLeftRight * L * cos(Afla) * sin(peita) + z0;
    } else if (mAngle > PAI / 2.0 && mAngle <= PAI) {
        peita = mAngle - PAI / 2;
        x = mLeftRight * L * cos(Afla) * cos(peita) + x0;
        z = -mLeftRight * L * cos(Afla) * sin(peita) + z0;
    } else if (mAngle > PAI && mAngle <= PAI * 3 / 2.0) {
        peita = PAI * 3.0 / 2 - mAngle;
        x = -mLeftRight * L * cos(Afla) * cos(peita) + x0;
        z = -mLeftRight * L * cos(Afla) * sin(peita) + z0;
    } else if (mAngle > PAI * 3 / 2.0 && mAngle <= PAI * 2.0) {
        peita = mAngle - PAI * 3.0 / 2;
        x = -mLeftRight * L * cos(Afla) * cos(peita) + x0;
        z = mLeftRight * L * cos(Afla) * sin(peita) + z0;
    }
    float mh = GetHeightValue(x, -z);
    *xx = x;
    *zz = z;
    return mh;
}

float CDesingScheme::GetHeightValue(float x, float z) {
    float CameraX = x / MAP_SCALE;                  // 计算在哪一列
    float CameraZ = -z / MAP_SCALE;                     // 计算在哪一行
    int32 Col0 = static_cast<int32>(CameraX);                        // 块的列号
    int32 Row0 = static_cast<int32>(CameraZ);                        // 块的行号
    int32 Col1 = Col0 + 1;                            // 相邻列
    int32 Row1 = Row0 + 1;                            // 相邻块
    if (Col1 > MAP_W)   Col1 = 0;                   // 相邻列大于地块数，取首列
    if (Row1 > MAP_W)   Row1 = 0;                   // 相邻行大于地块数，取首行
    float h00 = g_terrain[Col0 + Row0 * MAP_W][1];  // 获取块四角的高度
    float h01 = g_terrain[Col1 + Row0 * MAP_W][1];
    float h11 = g_terrain[Col1 + Row1 * MAP_W][1];
    float h10 = g_terrain[Col0 + Row1 * MAP_W][1];
    float tx = CameraX - static_cast<int32>(CameraX);              // 求块内X偏移位置
    float ty = CameraZ - static_cast<int32>(CameraZ);              // 求块内Z偏移位置
    float txty = tx * ty;                           // 以下为双线性插值（内插）计算
    // 返回插值计算值，为所求点的高度
    return h00 * (1.0f - ty - tx + txty) + h01 * (tx - txty) + h11 * txty + h10 * (ty - txty);
}


/************************************************************************/
/* Function: 计算边坡的填挖类型                                         */
/************************************************************************/
int32 CDesingScheme::GetTW(double x, double z, float H) {
    int32 mTW;
    double tx1 = x;
    double ty1 = -z;
    float mh = GetHeightValue(tx1, ty1);
    if (fabs(H - mh) <= 0.001)  // 如果路基面点的高程与垂直正下方的地面点高程之差<=0.001
        mTW = 0;  // 认为是填挖平衡点(即填挖0点)
    else if (H < mh)
        mTW = -1;  // <垂直正下方的地面点高程,为路堑
    else
        mTW = 1;  // >垂直正下方的地面点高程,为路堤
    return mTW;  // 返回计算的边坡填挖类型
}


/************************************************************************/
/* Function: 计算2端横断面上的点坐标                                        */
/************************************************************************/
void CDesingScheme::CalculateFillFacePoints(vector<Railway3DCordinate>& rcVector2, vector<Railway3DCordinate>& rcVector1) {  // NOLINT
    Railway3DCordinate rc2;  // 面2
    Railway3DCordinate rc1;  // 面1
    //1------------------------------------------------------------
    int32 a = PtS_Railway3D.GetSize();
    int32 railway3D_bIndex = 0;
    int32 railway3D_eIndex = a - 1;
    rc1.x1 = PtS_Railway3D[railway3D_bIndex]->x1;
    rc1.y1 = PtS_Railway3D[railway3D_bIndex]->y1;
    rc1.z1 = PtS_Railway3D[railway3D_bIndex]->z1;
    rc1.x2 = PtS_Railway3D[railway3D_bIndex]->x2;
    rc1.y2 = PtS_Railway3D[railway3D_bIndex]->y2;
    rc1.z2 = PtS_Railway3D[railway3D_bIndex]->z2;
    rcVector1.push_back(rc1);
    rc2.x1 = PtS_Railway3D[railway3D_eIndex]->x1;
    rc2.y1 = PtS_Railway3D[railway3D_eIndex]->y1;
    rc2.z1 = PtS_Railway3D[railway3D_eIndex]->z1;
    rc2.x2 = PtS_Railway3D[railway3D_eIndex]->x2;
    rc2.y2 = PtS_Railway3D[railway3D_eIndex]->y2;
    rc2.z2 = PtS_Railway3D[railway3D_eIndex]->z2;
    rcVector2.push_back(rc2);
    //2------------------------------------------------------------
    int32 b = PtS_RailwayLj3D.GetSize();
    int32 railwayLj3D_bIndex = 0;
    int32 railwayLj3D_eIndex = b - 1;
    rc1.x1 = PtS_RailwayLj3D[railwayLj3D_bIndex]->x1;
    rc1.y1 = PtS_RailwayLj3D[railwayLj3D_bIndex]->y1;
    rc1.z1 = PtS_RailwayLj3D[railwayLj3D_bIndex]->z1;
    rc1.x2 = PtS_RailwayLj3D[railwayLj3D_bIndex]->x2;
    rc1.y2 = PtS_RailwayLj3D[railwayLj3D_bIndex]->y2;
    rc1.z2 = PtS_RailwayLj3D[railwayLj3D_bIndex]->z2;
    rcVector1.push_back(rc1);
    rc2.x1 = PtS_RailwayLj3D[railwayLj3D_eIndex]->x1;
    rc2.y1 = PtS_RailwayLj3D[railwayLj3D_eIndex]->y1;
    rc2.z1 = PtS_RailwayLj3D[railwayLj3D_eIndex]->z1;
    rc2.x2 = PtS_RailwayLj3D[railwayLj3D_eIndex]->x2;
    rc2.y2 = PtS_RailwayLj3D[railwayLj3D_eIndex]->y2;
    rc2.z2 = PtS_RailwayLj3D[railwayLj3D_eIndex]->z2;
    rcVector2.push_back(rc2);
    //3------------------------------------------------------------
    int32 c = PtS_RailwayLjToBP3D.GetSize();
    int32 railwayLjToBP3D_bIndex = 0;
    int32 railwayLjToBP3D_eIndex = b - 1;
    rc1.x1 = PtS_RailwayLjToBP3D[railwayLjToBP3D_bIndex]->x1;
    rc1.y1 = PtS_RailwayLjToBP3D[railwayLjToBP3D_bIndex]->y1;
    rc1.z1 = PtS_RailwayLjToBP3D[railwayLjToBP3D_bIndex]->z1;
    rc1.x2 = PtS_RailwayLjToBP3D[railwayLjToBP3D_bIndex]->x2;
    rc1.y2 = PtS_RailwayLjToBP3D[railwayLjToBP3D_bIndex]->y2;
    rc1.z2 = PtS_RailwayLjToBP3D[railwayLjToBP3D_bIndex]->z2;
    rcVector1.push_back(rc1);
    rc2.x1 = PtS_RailwayLjToBP3D[railwayLjToBP3D_eIndex]->x1;
    rc2.y1 = PtS_RailwayLjToBP3D[railwayLjToBP3D_eIndex]->y1;
    rc2.z1 = PtS_RailwayLjToBP3D[railwayLjToBP3D_eIndex]->z1;
    rc2.x2 = PtS_RailwayLjToBP3D[railwayLjToBP3D_eIndex]->x2;
    rc2.y2 = PtS_RailwayLjToBP3D[railwayLjToBP3D_eIndex]->y2;
    rc2.z2 = PtS_RailwayLjToBP3D[railwayLjToBP3D_eIndex]->z2;
    rcVector2.push_back(rc2);
    //------------------------------------------------------------
    // 护坡计算断面各点
    int32 d = PtS_HuPo.GetSize();
    int32 hp_bIndex = 0;
    int32 hp_eInde = d - 1;
    int32 i, j;
    // 面1-------------------------------------------------------
    for (i = 1; i < 3; ++i) {
        if (i < 2) {
            for (j = 0; j < 2; ++j) {
                rc1.x1 = PtS_HuPo[hp_bIndex]->HuPo_L[i].Hp[j].x;
                rc1.y1 = PtS_HuPo[hp_bIndex]->HuPo_L[i].Hp[j].y;
                rc1.z1 = PtS_HuPo[hp_bIndex]->HuPo_L[i].Hp[j].z;
                rc1.x2 = PtS_HuPo[hp_bIndex]->HuPo_R[i].Hp[j].x;
                rc1.y2 = PtS_HuPo[hp_bIndex]->HuPo_R[i].Hp[j].y;
                rc1.z2 = PtS_HuPo[hp_bIndex]->HuPo_R[i].Hp[j].z;
                rcVector1.push_back(rc1);
            }
        } else if (i == 2) {
            for (j = 0; j < 3; ++j) {
                rc1.x1 = PtS_HuPo[hp_bIndex]->HuPo_L[i].Hp[j].x;
                rc1.y1 = PtS_HuPo[hp_bIndex]->HuPo_L[i].Hp[j].y;
                rc1.z1 = PtS_HuPo[hp_bIndex]->HuPo_L[i].Hp[j].z;
                rc1.x2 = PtS_HuPo[hp_bIndex]->HuPo_R[i].Hp[j].x;
                rc1.y2 = PtS_HuPo[hp_bIndex]->HuPo_R[i].Hp[j].y;
                rc1.z2 = PtS_HuPo[hp_bIndex]->HuPo_R[i].Hp[j].z;
                rcVector1.push_back(rc1);
            }
        }
    }
    // 面2--------------------------------------------------
    for (i = 1; i < 3; ++i) {
        if (i < 2) {
            for (j = 0; j < 2; ++j) {
                rc2.x1 = PtS_HuPo[hp_eInde]->HuPo_L[i].Hp[j].x;
                rc2.y1 = PtS_HuPo[hp_eInde]->HuPo_L[i].Hp[j].y;
                rc2.z1 = PtS_HuPo[hp_eInde]->HuPo_L[i].Hp[j].z;
                rc2.x2 = PtS_HuPo[hp_eInde]->HuPo_R[i].Hp[j].x;
                rc2.y2 = PtS_HuPo[hp_eInde]->HuPo_R[i].Hp[j].y;
                rc2.z2 = PtS_HuPo[hp_eInde]->HuPo_R[i].Hp[j].z;
                rcVector2.push_back(rc2);
            }
        } else if (i == 2) {
            for (j = 0; j < 3; ++j) {
                rc2.x1 = PtS_HuPo[hp_eInde]->HuPo_L[i].Hp[j].x;
                rc2.y1 = PtS_HuPo[hp_eInde]->HuPo_L[i].Hp[j].y;
                rc2.z1 = PtS_HuPo[hp_eInde]->HuPo_L[i].Hp[j].z;
                rc2.x2 = PtS_HuPo[hp_eInde]->HuPo_R[i].Hp[j].x;
                rc2.y2 = PtS_HuPo[hp_eInde]->HuPo_R[i].Hp[j].y;
                rc2.z2 = PtS_HuPo[hp_eInde]->HuPo_R[i].Hp[j].z;
                rcVector2.push_back(rc2);
            }
        }
    }
}

