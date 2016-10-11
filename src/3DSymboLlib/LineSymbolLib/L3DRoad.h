#ifndef L3D_ROAD_H
#define L3D_ROAD_H


#include "../MathUtils/Vec3.h"


class L3DRoad {
  public:
    L3DRoad();
    ~L3DRoad();

    /************************************************************************/
    /* Variables: 选线阈值设定(距离,夹角)                                       */
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
};


#endif  // L3D_ROAD_H