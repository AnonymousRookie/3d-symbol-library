#include "stdafx.h"
#include "L3DRoad.h"

L3DRoad::L3DRoad()
    : last_x(0), last_y(0), last_z(0),
      pre_x(0), pre_y(0), pre_z(0),
      p_count(0),
      m_Curve_R(INIT_CURVE_R), m_Curve_L0(INIT_CURVE_L0),
      m_distance_between_2_points(0.0f), m_pre_distance(0.0f) {
    v1_begin.setZero();
    v1_end.setZero();
    v2_begin.setZero();
    v2_end.setZero();
}


L3DRoad::~L3DRoad() {}