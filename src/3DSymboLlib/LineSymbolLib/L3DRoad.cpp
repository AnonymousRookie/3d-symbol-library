#include "stdafx.h"
#include "L3DRoad.h"

L3DRoad::L3DRoad()
    : last_x(0), last_y(0), last_z(0),
      pre_x(0), pre_y(0), pre_z(0),
      p_count(0),
      m_Curve_R(INIT_CURVE_R), m_Curve_L0(INIT_CURVE_L0),
      m_distance_between_2_points(0.0f), m_pre_distance(0.0f),
      b_haveMadeRail3DwayList(FALSE),
      pRailWay_(new Railway) {
    v1_begin.setZero();
    v1_end.setZero();
    v2_begin.setZero();
    v2_end.setZero();
}


L3DRoad::~L3DRoad() {}


void L3DRoad::InitRoad() {
    pRailWay_->Init();
    b_haveMadeRail3DwayList = FALSE;            // 是否已经有三维线路显示列表(透视投影模式下)
    // 选线阈值设定(距离,夹角)
    // 用于计算2点之间线段长度
    last_x = 0, last_y = 0, last_z = 0;
    pre_x  = 0, pre_y  = 0, pre_z = 0;
    // 用于计算2线段间夹角
    v1_begin.setZero();
    v1_end.setZero();
    v2_begin.setZero();
    v2_end.setZero();
    // 记录点的个数
    p_count = 0;
    m_distance_between_2_points = 0.0f;
    m_pre_distance = 0.0f;
}