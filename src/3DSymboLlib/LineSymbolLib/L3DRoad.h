#ifndef L3D_ROAD_H
#define L3D_ROAD_H

#include <memory>
#include "../MathUtils/Vec3.h"


enum {INIT_CURVE_R = 15, INIT_CURVE_L0 = 1};

// 路基断面结构
struct Railway {
    Railway()
        : m_Railway_width(5.0f),
          m_Lj_width(0.8f),
          m_GuiMianToLujianWidth(0.6f),
          m_Lj_Dh(m_GuiMianToLujianWidth * (1 / 1.75)),
          m_TieGui_width(1.435f) {}

    void Init() {
        m_Railway_width = 5.0;            // 路基断面总宽度
        m_Lj_width = 0.8;                 // 路肩宽度
        m_GuiMianToLujianWidth = 0.6;     // 碴肩至碴脚的高度
        m_Lj_Dh = m_GuiMianToLujianWidth * (1 / 1.75);  // 铁轨到碴肩的距离
        m_TieGui_width = 1.435;           // 铁轨间距
    }

    float   m_Railway_width;        // 路基断面总宽度
    float   m_Lj_width;             // 路肩宽度
    float   m_GuiMianToLujianWidth;  // 铁轨到碴肩的距离
    float   m_Lj_Dh;                // 碴肩至碴脚的高度
    float   m_TieGui_width;         // 铁轨间距
};



class L3DRoad {
  public:
    L3DRoad();
    ~L3DRoad();

public:
    void InitRoad();

  public:
    BOOL b_haveMadeRail3DwayList;   // 是否已经有三维线路显示列表(透视投影模式下)
    std::shared_ptr<Railway> pRailWay_;  // 线路路基结构

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