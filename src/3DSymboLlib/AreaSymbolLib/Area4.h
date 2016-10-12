#ifndef AREA_4_H
#define AREA_4_H

#include "../MathUtils/Vec3.h"
#include "../MathUtils/PointPolygonRelationship.h"

/************************************************************************/
/* 面符号三角化                                                         */
/************************************************************************/



typedef struct _Triangle {
    Point3 pt1;
    Point3 pt2;
    Point3 pt3;
} Triangle, *PTriangle;


// 四边形
typedef struct _Area_4 {
    Point3 pt1;
    Point3 pt2;
    Point3 pt3;
    Point3 pt4;

    // 保存所有多边形内部完整的三角形
    vector<Triangle> TrianglesInPolygonVecotr;
    // 保存所有局部三角化了的三角形(三角形只有1个点在多边形内, 且多边形的某条边与三角形有2个交点)
    vector<Triangle> LocalTrianglesVecotr1;
    // 保存所有局部三角化了的三角形(三角形只有2个点在多边形内, 且多边形的某条边与三角形有2个交点)
    vector<Triangle> LocalTrianglesVecotr2;
    // 保存所有局部三角化了的三角形(三角形只有1个点在多边形内, 且多边形的1个端点在三角形中)
    vector<Triangle> LocalTrianglesVecotr1_1;
    // 保存所有局部三角化了的三角形(三角形只有2个点在多边形内, 且多边形的1个端点在三角形中)
    vector<Triangle> LocalTrianglesVecotr2_1;
    // 保存所有局部三角化了的三角形(某三角形没有点在多边形内, 但多边形的1个端点在三角形中)
    vector<Triangle> LocalTrianglesVecotr_last;

    CString area_texture;
    UINT area_texture_rd;

    uint16 deleted;
} Area_4, *PArea_4;


class Area4Symbol {
  public:
    Area4Symbol();
    ~Area4Symbol();

    // 找出所有包含在多边形内的三角形(包括完整三角形和经过局部三角化的三角形)
    int32 FindAllTrianglesInPolygon(Area_4& m_area4, float (*g_terrain)[3]);  // NOLINT

    // 计算出所有包含在多边形内的点
    int32 FindAllPointsInPolygon(const Area_4& m_area4, float (*g_terrain)[3]);

    // 只有1个点在多边形形内的三角形(需重新三角化)
    int32 FindTriangles_1_point_inPolygon(Area_4& m_area4, float (*g_terrain)[3]);  // NOLINT

    // 只有2个点在多边形形内的三角形(需重新三角化)
    int32 FindTriangles_2_point_inPolygon(Area_4& m_area4, float (*g_terrain)[3]);  // NOLINT

    // 有3个点在多边形形内的三角形
    int32 FindTriangles_3_point_inPolygon(Area_4& _area4, float (*g_terrain)[3]);  // NOLINT

    // 多边形的一条边  与  三角形  有2个交点, 找出符合条件的三角形
    void Find_triangles_1_line_2_JD(Area_4& m_area4, Triangle& tmp_triangle, CPointPolygonRelationship& tmp_PPR, PPR_Point& tmp_point1, PPR_Point& tmp_point21, PPR_Point& tmp_point22, float (*g_terrain)[3]);  // NOLINT


    // 多边形顶点处的三角形
    void FindTriangles_polygon_has_vertex_in_triangle(Area_4& m_area4, float (*g_terrain)[3]);  // NOLINT
    void FindTriangles_polygon_has_vertex_in_triangle_1_1(Area_4& m_area4, Triangle& tmp_triangle1, Triangle& tmp_triangle2, PPR_Point& tmp_point1, PPR_Point& tmp_point21, PPR_Point& tmp_point22, float (*g_terrain)[3]);  // NOLINT
    void FindTriangles_polygon_has_vertex_in_triangle_2_1(Area_4& m_area4, Triangle& tmp_triangle1, Triangle& tmp_triangle2, Triangle& tmp_triangle3, PPR_Point& tmp_point1, PPR_Point& tmp_point21, PPR_Point& tmp_point22, float (*g_terrain)[3]);  // NOLINT
    void FindTriangles_polygon_has_vertex_in_triangle_last(Area_4& m_area4, Triangle& tmp_triangle1, Triangle& tmp_triangle2, Triangle& tmp_triangle3, Triangle& tmp_triangle4, PPR_Point& tmp_point0, PPR_Point& tmp_point1, PPR_Point& tmp_point21, PPR_Point& tmp_point22, float (*g_terrain)[3]);  // NOLINT


    float GetHeight(float x, float z, float (*g_terrain)[3]);
  public:
    // 存放多边形内的点
    vector<Point3> pointsInPolygonVector;
    vector<Point3> index_pointsInPolygonVector;
    // (MAP_W * MAP_W)方阵 1:在多边形内, 0:不在
    int32 inPolygonArrayFlag[MAP_W][MAP_W];
};


#endif  // AREA_4_H