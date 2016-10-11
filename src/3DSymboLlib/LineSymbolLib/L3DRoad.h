#ifndef L3D_ROAD_H
#define L3D_ROAD_H


#include "../MathUtils/Vec3.h"


enum {INIT_CURVE_R = 15, INIT_CURVE_L0 = 1};

class L3DRoad {
  public:
    L3DRoad();
    ~L3DRoad();

    /************************************************************************/
    /* Variables: 选线阈值设定(距离,夹角)                                     */
    /************************************************************************/
  public:
    // 用于计算2点之间线段长度
    float last_x, last_y, last_z;
    float pre_x,  pre_y,  pre_z;
    // 用于计算2线段间夹角
    CVector3 v1_begin, v1_end;
    CVector3 v2_begin, v2_end;
    // 记录点的个数
    int32 p_count;

    /************************************************************************/
    /* Variables: 曲线要素设定                                               */
    /************************************************************************/
  public:
    int64  m_Curve_R;    // 曲线半径
    int32  m_Curve_L0;   // 缓和曲线长

    float m_distance_between_2_points;  // 当前2点线段间的距离
    float m_pre_distance;               // 前一线段间的距离
};


#endif  // L3D_ROAD_H