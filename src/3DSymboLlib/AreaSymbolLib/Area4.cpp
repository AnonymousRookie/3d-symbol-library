#include "stdafx.h"
#include "Area4.h"


Area4Symbol::Area4Symbol() : delta_(0.0001f) {}

Area4Symbol::~Area4Symbol() {}

// 找出所有包含在多边形内的三角形(包括完整三角形和经过局部三角化的三角形)
int32 Area4Symbol::FindAllTrianglesInPolygon(Area_4& m_area4, float (*g_terrain)[3]) {  // NOLINT
    FindAllPointsInPolygon(m_area4, g_terrain);
    // 1.多边形内完整的三角形
    m_area4.TrianglesInPolygonVecotr.clear();
    FindTriangles_3_point_inPolygon(m_area4, g_terrain);
    // 2.经过局部三角化的三角形
    m_area4.LocalTrianglesVecotr1.clear();
    FindTriangles_1_point_inPolygon(m_area4, g_terrain);
    m_area4.LocalTrianglesVecotr2.clear();
    FindTriangles_2_point_inPolygon(m_area4, g_terrain);
    // 2.1 多边形顶点处
    m_area4.LocalTrianglesVecotr1_1.clear();
    m_area4.LocalTrianglesVecotr2_1.clear();
    m_area4.LocalTrianglesVecotr_last.clear();
    FindTriangles_polygon_has_vertex_in_triangle(m_area4, g_terrain);
    return 0;
}

// 计算出所有包含在多边形内的点
int32 Area4Symbol::FindAllPointsInPolygon(const Area_4& m_area4, float (*g_terrain)[3]) {
    CPointPolygonRelationship tmp_ppr;
    PPR_Polygon tmp_polygon;
    PPR_Point tmp_point;
    tmp_point.x = m_area4.pt1.x;
    tmp_point.y = m_area4.pt1.z;
    tmp_polygon.push_back(tmp_point);
    tmp_point.x = m_area4.pt2.x;
    tmp_point.y = m_area4.pt2.z;
    tmp_polygon.push_back(tmp_point);
    tmp_point.x = m_area4.pt3.x;
    tmp_point.y = m_area4.pt3.z;
    tmp_polygon.push_back(tmp_point);
    tmp_point.x = m_area4.pt4.x;
    tmp_point.y = m_area4.pt4.z;
    tmp_polygon.push_back(tmp_point);
    PPR_Point tmp_dem_point;
    pointsInPolygonVector.clear();
    int32 Vertex = 0;
    for (int32 z = 0; z < MAP_W; ++z) {
        for (int32 x = 0; x < MAP_W; ++x) {
            Vertex = z * MAP_W + x;
            tmp_dem_point.x = g_terrain [Vertex][0];
            tmp_dem_point.y = g_terrain [Vertex][2];
            int32 inPolygonFlag = tmp_ppr.InPolygon(tmp_polygon, tmp_dem_point);
            if (inPolygonFlag == 0) {  // 点在多边形内
                Point3 tmp_point3 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                pointsInPolygonVector.push_back(tmp_point3);
                inPolygonArrayFlag[x][z] = 1;
            } else {
                inPolygonArrayFlag[x][z] = 0;
            }
        }
    }
    return 0;
}


// 有3个点在多边形形内的三角形
int32 Area4Symbol::FindTriangles_3_point_inPolygon(Area_4& _area4, float (*g_terrain)[3]) {  // NOLINT
    int32 Vertex = 0;
    for (int32 z = 0; z < MAP_W - 1; ++z) {
        for (int32 x = 0; x < MAP_W - 1; ++x) {
            Vertex = z * MAP_W + x;
            Triangle tmp_triangle;
            // 3个点都在多边形内
            if (inPolygonArrayFlag[x][z] == 1 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 1) {
                Vertex = z * MAP_W + x;
                tmp_triangle.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                Vertex = (z + 1) * MAP_W + x;
                tmp_triangle.pt2 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                Vertex = z * MAP_W + (x + 1);
                tmp_triangle.pt3 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                _area4.TrianglesInPolygonVecotr.push_back(tmp_triangle);
            }
            // 3个点都在多边形内
            if (inPolygonArrayFlag[x + 1][z] == 1 && inPolygonArrayFlag[x + 1][z + 1] == 1  && inPolygonArrayFlag[x][z + 1] == 1) {
                Vertex = z * MAP_W + (x + 1);
                tmp_triangle.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_triangle.pt2 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                Vertex = (z + 1) * MAP_W + x;
                tmp_triangle.pt3 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                _area4.TrianglesInPolygonVecotr.push_back(tmp_triangle);
            }
        }
    }
    return 0;
}


// 只有1个点在多边形形内的三角形(需重新三角化)
int32 Area4Symbol::FindTriangles_1_point_inPolygon(Area_4& m_area4, float (*g_terrain)[3]) {  // NOLINT
    {
        int32 Vertex;
        for (int32 z = 0; z < MAP_W - 1; ++z) {
            for (int32 x = 0; x < MAP_W - 1; ++x) {
                Vertex = z * MAP_W + x;
                Triangle tmp_triangle;
                // 三角形只有1个点在多边形内
                if (inPolygonArrayFlag[x][z] == 1 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 0) {
                    Vertex = (z) * MAP_W + (x);
                    tmp_triangle.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    Find_triangles_1_line_2_JD(m_area4, tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22, g_terrain);
                }
                if (inPolygonArrayFlag[x][z] == 0 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 0) {
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_triangle.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    Find_triangles_1_line_2_JD(m_area4, tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22, g_terrain);
                }
                // 三角形只有1个点在多边形内
                if (inPolygonArrayFlag[x][z] == 0 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 1) {
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_triangle.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    Find_triangles_1_line_2_JD(m_area4, tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22, g_terrain);
                }
                // ==========================================================================================
                // 三角形只有1个点在多边形内
                if (inPolygonArrayFlag[x + 1][z + 1] == 1 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 0) {
                    Vertex = (z + 1) * MAP_W + (x + 1);
                    tmp_triangle.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    Find_triangles_1_line_2_JD(m_area4, tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22, g_terrain);
                }
                if (inPolygonArrayFlag[x + 1][z + 1] == 0 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 0) {
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_triangle.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x + 1);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    Find_triangles_1_line_2_JD(m_area4, tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22, g_terrain);
                }
                // 三角形只有1个点在多边形内
                if (inPolygonArrayFlag[x + 1][z + 1] == 0 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 1) {
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_triangle.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    Find_triangles_1_line_2_JD(m_area4, tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22, g_terrain);
                }
            }
        }
    }
    return 0;
}


// 只有2个点在多边形形内的三角形(需重新三角化)
int32 Area4Symbol::FindTriangles_2_point_inPolygon(Area_4& m_area4, float (*g_terrain)[3]) {  // NOLINT
    {
        int32 Vertex;
        for (int32 z = 0; z < MAP_W - 1; ++z) {
            for (int32 x = 0; x < MAP_W - 1; ++x) {
                Vertex = z * MAP_W + x;
                Triangle tmp_triangle1;
                Triangle tmp_triangle2;
                // ok1
                if (inPolygonArrayFlag[x][z] == 1 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 0) {
                    Vertex = (z) * MAP_W + (x);
                    tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                    tmp_triangle2.pt1 = tmp_triangle1.pt1;
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_triangle1.pt2 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    // Find_triangles_1_line_2_JD(tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);
                    PPR_Point tmp_point3, tmp_point4;  // 多边形边的端点
                    PPR_Point JD1, JD2;
                    // CString msg;
                    bool intersectFlag1 = false;
                    bool intersectFlag2 = false;
                    int16 tmp_cout = 4;
                    while (tmp_cout > 0) {
                        if (4 == tmp_cout) {
                            tmp_point3.x = m_area4.pt1.x;
                            tmp_point3.y = m_area4.pt1.z;
                            tmp_point4.x = m_area4.pt2.x;
                            tmp_point4.y = m_area4.pt2.z;
                        } else if (3 == tmp_cout) {
                            tmp_point3.x = m_area4.pt2.x;
                            tmp_point3.y = m_area4.pt2.z;
                            tmp_point4.x = m_area4.pt3.x;
                            tmp_point4.y = m_area4.pt3.z;
                        } else if (2 == tmp_cout) {
                            tmp_point3.x = m_area4.pt3.x;
                            tmp_point3.y = m_area4.pt3.z;
                            tmp_point4.x = m_area4.pt4.x;
                            tmp_point4.y = m_area4.pt4.z;
                        } else if (1 == tmp_cout) {
                            tmp_point3.x = m_area4.pt4.x;
                            tmp_point3.y = m_area4.pt4.z;
                            tmp_point4.x = m_area4.pt1.x;
                            tmp_point4.y = m_area4.pt1.z;
                        }
                        intersectFlag1 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                        intersectFlag2 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                        if (intersectFlag1 && intersectFlag2) {
                            JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                            JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                            float tmp_min_y = MATH_MIN(tmp_triangle1.pt1.z, tmp_triangle1.pt2.z);
                            float tmp_max_y = MATH_MAX(tmp_triangle1.pt1.z, tmp_triangle1.pt2.z);
                            float tmp_min_x = MATH_MIN(tmp_triangle1.pt1.x, tmp_point1.x);
                            float tmp_max_x = MATH_MAX(tmp_triangle1.pt1.x, tmp_point1.x);
                            bool b11 = (JD1.y > (tmp_min_y + delta_)) && (JD1.y < (tmp_max_y - delta_));
                            bool b21 = (JD2.y > (tmp_min_y + delta_)) && (JD2.y < (tmp_max_y - delta_));
                            bool b12 = (JD1.x > (tmp_min_x + delta_)) && (JD1.x < (tmp_max_x - delta_));
                            bool b22 = (JD2.x > (tmp_min_x + delta_)) && (JD2.x < (tmp_max_x - delta_));
                            if (b11 && b12) {
                                tmp_triangle1.pt3 = Point3(JD1.x, GetHeight(JD1.x, JD1.y, g_terrain), JD1.y);
                            } else if (b21 && b22) {
                                tmp_triangle1.pt3 = Point3(JD2.x, GetHeight(JD2.x, JD2.y, g_terrain), JD2.y);
                            } else {
                                AfxMessageBox("warning1: ");
                            }
                            tmp_triangle2.pt2 = Point3(JD1.x, GetHeight(JD1.x, JD1.y, g_terrain), JD1.y);
                            tmp_triangle2.pt3 = Point3(JD2.x, GetHeight(JD2.x, JD2.y, g_terrain), JD2.y);
                            // AfxMessageBox("1");
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle1);
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle2);
                        }
                        tmp_cout--;
                    }
                }
                // ok2
                if (inPolygonArrayFlag[x][z] == 1 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 1) {
                    Vertex = (z) * MAP_W + (x);
                    tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                    tmp_triangle2.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_triangle1.pt2 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    // Find_triangles_1_line_2_JD(tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);
                    PPR_Point tmp_point3, tmp_point4;  // 多边形边的端点
                    PPR_Point JD1, JD2;
                    CString msg;
                    bool intersectFlag1 = false;
                    bool intersectFlag2 = false;
                    int32 tmp_cout = 4;
                    while (tmp_cout > 0) {
                        if (4 == tmp_cout) {
                            tmp_point3.x = m_area4.pt1.x;
                            tmp_point3.y = m_area4.pt1.z;
                            tmp_point4.x = m_area4.pt2.x;
                            tmp_point4.y = m_area4.pt2.z;
                        } else if (3 == tmp_cout) {
                            tmp_point3.x = m_area4.pt2.x;
                            tmp_point3.y = m_area4.pt2.z;
                            tmp_point4.x = m_area4.pt3.x;
                            tmp_point4.y = m_area4.pt3.z;
                        } else if (2 == tmp_cout) {
                            tmp_point3.x = m_area4.pt3.x;
                            tmp_point3.y = m_area4.pt3.z;
                            tmp_point4.x = m_area4.pt4.x;
                            tmp_point4.y = m_area4.pt4.z;
                        } else if (1 == tmp_cout) {
                            tmp_point3.x = m_area4.pt4.x;
                            tmp_point3.y = m_area4.pt4.z;
                            tmp_point4.x = m_area4.pt1.x;
                            tmp_point4.y = m_area4.pt1.z;
                        }
                        intersectFlag1 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                        intersectFlag2 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                        if (intersectFlag1 && intersectFlag2) {
                            JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                            JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                            float tmp_min_y = MATH_MIN(tmp_triangle1.pt1.z, tmp_point1.y);
                            float tmp_max_y = MATH_MAX(tmp_triangle1.pt1.z, tmp_point1.y);
                            float tmp_min_x = MATH_MIN(tmp_triangle1.pt1.x, tmp_triangle1.pt2.x);
                            float tmp_max_x = MATH_MAX(tmp_triangle1.pt1.x, tmp_triangle1.pt2.x);
                            bool b11 = (JD1.y > (tmp_min_y + delta_)) && (JD1.y < (tmp_max_y - delta_));
                            bool b21 = (JD2.y > (tmp_min_y + delta_)) && (JD2.y < (tmp_max_y - delta_));
                            bool b12 = (JD1.x > (tmp_min_x + delta_)) && (JD1.x < (tmp_max_x - delta_));
                            bool b22 = (JD2.x > (tmp_min_x + delta_)) && (JD2.x < (tmp_max_x - delta_));
                            if (b11 && b12) {
                                tmp_triangle1.pt3 = Point3(JD1.x, GetHeight(JD1.x, JD1.y, g_terrain), JD1.y);
                            } else if (b21 && b22) {
                                tmp_triangle1.pt3 = Point3(JD2.x, GetHeight(JD2.x, JD2.y, g_terrain), JD2.y);
                            } else {
                                AfxMessageBox("warning2: ");
                                // AfxMessageBox(__LINE__);
                            }
                            tmp_triangle2.pt2 = Point3(JD1.x, GetHeight(JD1.x, JD1.y, g_terrain), JD1.y);
                            tmp_triangle2.pt3 = Point3(JD2.x, GetHeight(JD2.x, JD2.y, g_terrain), JD2.y);
                            // AfxMessageBox("2");
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle1);
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle2);
                        }
                        tmp_cout--;
                    }
                }
                // ok3
                if (inPolygonArrayFlag[x][z] == 0 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 1) {
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_triangle1.pt1 = Point3(g_terrain [Vertex][0], g_terrain [Vertex][1], g_terrain [Vertex][2]);
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_triangle1.pt2 = Point3(g_terrain [Vertex][0], g_terrain [Vertex][1], g_terrain [Vertex][2]);
                    tmp_triangle2.pt1 = Point3(g_terrain [Vertex][0], g_terrain [Vertex][1], g_terrain [Vertex][2]);
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
                    Vertex = (z) * MAP_W + (x);
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    // Find_triangles_1_line_2_JD(tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);
                    PPR_Point tmp_point3, tmp_point4;  // 多边形边的端点
                    PPR_Point JD1, JD2;
                    CString msg;
                    bool intersectFlag1 = false;
                    bool intersectFlag2 = false;
                    int32 tmp_cout = 4;
                    while (tmp_cout > 0) {
                        if (4 == tmp_cout) {
                            tmp_point3.x = m_area4.pt1.x;
                            tmp_point3.y = m_area4.pt1.z;
                            tmp_point4.x = m_area4.pt2.x;
                            tmp_point4.y = m_area4.pt2.z;
                        } else if (3 == tmp_cout) {
                            tmp_point3.x = m_area4.pt2.x;
                            tmp_point3.y = m_area4.pt2.z;
                            tmp_point4.x = m_area4.pt3.x;
                            tmp_point4.y = m_area4.pt3.z;
                        } else if (2 == tmp_cout) {
                            tmp_point3.x = m_area4.pt3.x;
                            tmp_point3.y = m_area4.pt3.z;
                            tmp_point4.x = m_area4.pt4.x;
                            tmp_point4.y = m_area4.pt4.z;
                        } else if (1 == tmp_cout) {
                            tmp_point3.x = m_area4.pt4.x;
                            tmp_point3.y = m_area4.pt4.z;
                            tmp_point4.x = m_area4.pt1.x;
                            tmp_point4.y = m_area4.pt1.z;
                        }
                        intersectFlag1 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                        intersectFlag2 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                        if (intersectFlag1 && intersectFlag2) {
                            JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                            JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                            double len1 = (tmp_triangle1.pt1.x - JD1.x) * (tmp_triangle1.pt1.x - JD1.x) + (tmp_triangle1.pt1.z - JD1.y) * (tmp_triangle1.pt1.z - JD1.y);
                            double len2 = (tmp_triangle1.pt1.x - JD2.x) * (tmp_triangle1.pt1.x - JD2.x) + (tmp_triangle1.pt1.z - JD2.y) * (tmp_triangle1.pt1.z - JD2.y);
                            if (len1 < len2) {
                                tmp_triangle1.pt3 = Point3(JD1.x, GetHeight(JD1.x, JD1.y, g_terrain), JD1.y);
                            } else if (len1 > len2) {
                                tmp_triangle1.pt3 = Point3(JD2.x, GetHeight(JD2.x, JD2.y, g_terrain), JD2.y);
                            } else {
                                AfxMessageBox("warning3");
                            }
                            tmp_triangle2.pt2 = Point3(JD1.x, GetHeight(JD1.x, JD1.y, g_terrain), JD1.y);
                            tmp_triangle2.pt3 = Point3(JD2.x, GetHeight(JD2.x, JD2.y, g_terrain), JD2.y);
                            // AfxMessageBox("3");
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle1);
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle2);
                        }
                        tmp_cout--;
                    }
                }
                // ========================================================================================
                // ok - 1
                if (inPolygonArrayFlag[x + 1][z + 1] == 1 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 0) {
                    Vertex = (z + 1) * MAP_W + (x + 1);
                    tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                    tmp_triangle2.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_triangle1.pt2 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    // Find_triangles_1_line_2_JD(tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);
                    PPR_Point tmp_point3, tmp_point4;  // 多边形边的端点
                    PPR_Point JD1, JD2;
                    CString msg;
                    bool intersectFlag1 = false;
                    bool intersectFlag2 = false;
                    int32 tmp_cout = 4;
                    while (tmp_cout > 0) {
                        if (4 == tmp_cout) {
                            tmp_point3.x = m_area4.pt1.x;
                            tmp_point3.y = m_area4.pt1.z;
                            tmp_point4.x = m_area4.pt2.x;
                            tmp_point4.y = m_area4.pt2.z;
                        } else if (3 == tmp_cout) {
                            tmp_point3.x = m_area4.pt2.x;
                            tmp_point3.y = m_area4.pt2.z;
                            tmp_point4.x = m_area4.pt3.x;
                            tmp_point4.y = m_area4.pt3.z;
                        } else if (2 == tmp_cout) {
                            tmp_point3.x = m_area4.pt3.x;
                            tmp_point3.y = m_area4.pt3.z;
                            tmp_point4.x = m_area4.pt4.x;
                            tmp_point4.y = m_area4.pt4.z;
                        } else if (1 == tmp_cout) {
                            tmp_point3.x = m_area4.pt4.x;
                            tmp_point3.y = m_area4.pt4.z;
                            tmp_point4.x = m_area4.pt1.x;
                            tmp_point4.y = m_area4.pt1.z;
                        }
                        intersectFlag1 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                        intersectFlag2 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                        if (intersectFlag1 && intersectFlag2) {
                            JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                            JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                            float tmp_min_x = MATH_MIN(tmp_triangle1.pt1.x, tmp_triangle1.pt2.x);
                            float tmp_max_x = MATH_MAX(tmp_triangle1.pt1.x, tmp_triangle1.pt2.x);
                            float tmp_min_y = MATH_MIN(tmp_triangle1.pt1.z, tmp_point1.y);
                            float tmp_max_y = MATH_MAX(tmp_triangle1.pt1.z, tmp_point1.y);
                            bool b11 = (JD1.y > (tmp_min_y + delta_)) && (JD1.y < (tmp_max_y - delta_));
                            bool b21 = (JD2.y > (tmp_min_y + delta_)) && (JD2.y < (tmp_max_y - delta_));
                            bool b12 = (JD1.x > (tmp_min_x + delta_)) && (JD1.x < (tmp_max_x - delta_));
                            bool b22 = (JD2.x > (tmp_min_x + delta_)) && (JD2.x < (tmp_max_x - delta_));
                            if (b11 && b12) {
                                tmp_triangle1.pt3 = Point3(JD1.x, GetHeight(JD1.x, JD1.y, g_terrain), JD1.y);
                            } else if (b21 && b22) {
                                tmp_triangle1.pt3 = Point3(JD2.x, GetHeight(JD2.x, JD2.y, g_terrain), JD2.y);
                            } else {
                                AfxMessageBox("warning4... ");
                                // AfxMessageBox(__LINE__);
                            }
                            tmp_triangle2.pt2 = Point3(JD1.x, GetHeight(JD1.x, JD1.y, g_terrain), JD1.y);
                            tmp_triangle2.pt3 = Point3(JD2.x, GetHeight(JD2.x, JD2.y, g_terrain), JD2.y);
                            // AfxMessageBox(" - 1");
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle1);
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle2);
                        }
                        tmp_cout--;
                    }
                }
                // ok - 2
                if (inPolygonArrayFlag[x + 1][z + 1] == 1 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 1) {
                    Vertex = (z + 1) * MAP_W + (x + 1);
                    tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                    tmp_triangle2.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_triangle1.pt2 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    // Find_triangles_1_line_2_JD(tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);
                    PPR_Point tmp_point3, tmp_point4;  // 多边形边的端点
                    PPR_Point JD1, JD2;
                    CString msg;
                    bool intersectFlag1 = false;
                    bool intersectFlag2 = false;
                    int32 tmp_cout = 4;
                    while (tmp_cout > 0) {
                        if (4 == tmp_cout) {
                            tmp_point3.x = m_area4.pt1.x;
                            tmp_point3.y = m_area4.pt1.z;
                            tmp_point4.x = m_area4.pt2.x;
                            tmp_point4.y = m_area4.pt2.z;
                        } else if (3 == tmp_cout) {
                            tmp_point3.x = m_area4.pt2.x;
                            tmp_point3.y = m_area4.pt2.z;
                            tmp_point4.x = m_area4.pt3.x;
                            tmp_point4.y = m_area4.pt3.z;
                        } else if (2 == tmp_cout) {
                            tmp_point3.x = m_area4.pt3.x;
                            tmp_point3.y = m_area4.pt3.z;
                            tmp_point4.x = m_area4.pt4.x;
                            tmp_point4.y = m_area4.pt4.z;
                        } else if (1 == tmp_cout) {
                            tmp_point3.x = m_area4.pt4.x;
                            tmp_point3.y = m_area4.pt4.z;
                            tmp_point4.x = m_area4.pt1.x;
                            tmp_point4.y = m_area4.pt1.z;
                        }
                        intersectFlag1 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                        intersectFlag2 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                        if (intersectFlag1 && intersectFlag2) {
                            JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                            JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                            float tmp_min_x = MATH_MIN(tmp_triangle1.pt1.x, tmp_point1.x);
                            float tmp_max_x = MATH_MAX(tmp_triangle1.pt1.x, tmp_point1.x);
                            float tmp_min_y = MATH_MIN(tmp_triangle1.pt1.z, tmp_triangle1.pt2.z);
                            float tmp_max_y = MATH_MAX(tmp_triangle1.pt1.z, tmp_triangle1.pt2.z);
                            bool b11 = (JD1.y > (tmp_min_y + delta_)) && (JD1.y < (tmp_max_y - delta_));
                            bool b21 = (JD2.y > (tmp_min_y + delta_)) && (JD2.y < (tmp_max_y - delta_));
                            bool b12 = (JD1.x > (tmp_min_x + delta_)) && (JD1.x < (tmp_max_x - delta_));
                            bool b22 = (JD2.x > (tmp_min_x + delta_)) && (JD2.x < (tmp_max_x - delta_));
                            if (b11 && b12) {
                                tmp_triangle1.pt3 = Point3(JD1.x, GetHeight(JD1.x, JD1.y, g_terrain), JD1.y);
                            } else if (b21 && b22) {
                                tmp_triangle1.pt3 = Point3(JD2.x, GetHeight(JD2.x, JD2.y, g_terrain), JD2.y);
                            } else {
                                AfxMessageBox("warning5... ");
                                // AfxMessageBox(__LINE__);
                            }
                            tmp_triangle2.pt2 = Point3(JD1.x, GetHeight(JD1.x, JD1.y, g_terrain), JD1.y);
                            tmp_triangle2.pt3 = Point3(JD2.x, GetHeight(JD2.x, JD2.y, g_terrain), JD2.y);
                            // AfxMessageBox(" - 2");
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle1);
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle2);
                        }
                        tmp_cout--;
                    }
                }
                // ok - 3
                if (inPolygonArrayFlag[x + 1][z + 1] == 0 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 1) {
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_triangle1.pt2 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                    tmp_triangle2.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
                    Vertex = (z + 1) * MAP_W + (x + 1);
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    // Find_triangles_1_line_2_JD(tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);
                    PPR_Point tmp_point3, tmp_point4;  // 多边形边的端点
                    PPR_Point JD1, JD2;
                    CString msg;
                    bool intersectFlag1 = false;
                    bool intersectFlag2 = false;
                    int32 tmp_cout = 4;
                    while (tmp_cout > 0) {
                        if (4 == tmp_cout) {
                            tmp_point3.x = m_area4.pt1.x;
                            tmp_point3.y = m_area4.pt1.z;
                            tmp_point4.x = m_area4.pt2.x;
                            tmp_point4.y = m_area4.pt2.z;
                        } else if (3 == tmp_cout) {
                            tmp_point3.x = m_area4.pt2.x;
                            tmp_point3.y = m_area4.pt2.z;
                            tmp_point4.x = m_area4.pt3.x;
                            tmp_point4.y = m_area4.pt3.z;
                        } else if (2 == tmp_cout) {
                            tmp_point3.x = m_area4.pt3.x;
                            tmp_point3.y = m_area4.pt3.z;
                            tmp_point4.x = m_area4.pt4.x;
                            tmp_point4.y = m_area4.pt4.z;
                        } else if (1 == tmp_cout) {
                            tmp_point3.x = m_area4.pt4.x;
                            tmp_point3.y = m_area4.pt4.z;
                            tmp_point4.x = m_area4.pt1.x;
                            tmp_point4.y = m_area4.pt1.z;
                        }
                        intersectFlag1 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                        intersectFlag2 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                        if (intersectFlag1 && intersectFlag2) {
                            JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                            JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                            double len1 = (tmp_triangle1.pt1.x - JD1.x) * (tmp_triangle1.pt1.x - JD1.x) + (tmp_triangle1.pt1.z - JD1.y) * (tmp_triangle1.pt1.z - JD1.y);
                            double len2 = (tmp_triangle1.pt1.x - JD2.x) * (tmp_triangle1.pt1.x - JD2.x) + (tmp_triangle1.pt1.z - JD2.y) * (tmp_triangle1.pt1.z - JD2.y);
                            if (len1 < len2) {
                                tmp_triangle1.pt3 = Point3(JD1.x, GetHeight(JD1.x, JD1.y, g_terrain), JD1.y);
                            } else if (len1 > len2) {
                                tmp_triangle1.pt3 = Point3(JD2.x, GetHeight(JD2.x, JD2.y, g_terrain), JD2.y);
                            } else {
                                AfxMessageBox("...warning!");
                            }
                            tmp_triangle2.pt2 = Point3(JD1.x, GetHeight(JD1.x, JD1.y, g_terrain), JD1.y);
                            tmp_triangle2.pt3 = Point3(JD2.x, GetHeight(JD2.x, JD2.y, g_terrain), JD2.y);
                            // AfxMessageBox(" - 3");
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle1);
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle2);
                        }
                        tmp_cout--;
                    }
                }
            }
        }
    }
    return 0;
}  // NOLINT



// 找出符合条件的三角形(三角形只有1个点在多边形内, 且多边形的某条边与三角形有2个交点)
void Area4Symbol::Find_triangles_1_line_2_JD(Area_4& m_area4, Triangle& tmp_triangle, CPointPolygonRelationship& tmp_PPR, PPR_Point& tmp_point1, PPR_Point& tmp_point21, PPR_Point& tmp_point22, float (*g_terrain)[3]) {  // NOLINT
    PPR_Point tmp_point3, tmp_point4;  // 多边形边的端点
    PPR_Point JD1, JD2;
    // CString msg;
    bool intersectFlag1 = false;
    bool intersectFlag2 = false;
    int16 tmp_cout = 4;
    while (tmp_cout > 0) {
        if (4 == tmp_cout) {
            tmp_point3.x = m_area4.pt1.x;
            tmp_point3.y = m_area4.pt1.z;
            tmp_point4.x = m_area4.pt2.x;
            tmp_point4.y = m_area4.pt2.z;
        } else if (3 == tmp_cout) {
            tmp_point3.x = m_area4.pt2.x;
            tmp_point3.y = m_area4.pt2.z;
            tmp_point4.x = m_area4.pt3.x;
            tmp_point4.y = m_area4.pt3.z;
        } else if (2 == tmp_cout) {
            tmp_point3.x = m_area4.pt3.x;
            tmp_point3.y = m_area4.pt3.z;
            tmp_point4.x = m_area4.pt4.x;
            tmp_point4.y = m_area4.pt4.z;
        } else if (1 == tmp_cout) {
            tmp_point3.x = m_area4.pt4.x;
            tmp_point3.y = m_area4.pt4.z;
            tmp_point4.x = m_area4.pt1.x;
            tmp_point4.y = m_area4.pt1.z;
        }
        intersectFlag1 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
        intersectFlag2 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
        if (intersectFlag1 && intersectFlag2) {
            JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
            JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
            tmp_triangle.pt2 = Point3(JD1.x, GetHeight(JD1.x, JD1.y, g_terrain), JD1.y);
            tmp_triangle.pt3 = Point3(JD2.x, GetHeight(JD2.x, JD2.y, g_terrain), JD2.y);
            m_area4.LocalTrianglesVecotr1.push_back(tmp_triangle);
        }
        tmp_cout--;
    }
}



// 多边形顶点处的三角形
void Area4Symbol::FindTriangles_polygon_has_vertex_in_triangle(Area_4& m_area4, float (*g_terrain)[3]) {  // NOLINT
    int32 Vertex;
    for (int32 z = 0; z < MAP_W - 1; ++z) {
        for (int32 x = 0; x < MAP_W - 1; ++x) {
            Vertex = z * MAP_W + x;
            Triangle tmp_triangle1;
            Triangle tmp_triangle2;
            PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
            /************************************************************************/
            /*       三角形只有1个点在多边形内                                          */
            /************************************************************************/
            // ------------------------------------
            if (inPolygonArrayFlag[x][z] == 0 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 1) {
                Vertex = (z) * MAP_W + (x + 1);
                tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle2.pt1 = tmp_triangle1.pt1;
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_1_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_point1, tmp_point21, tmp_point22, g_terrain);
            }
            // 三角形只有1个点在多边形内
            if (inPolygonArrayFlag[x][z] == 0 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 0) {
                Vertex = (z + 1) * MAP_W + (x);
                tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle2.pt1 = tmp_triangle1.pt1;
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_1_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_point1, tmp_point21, tmp_point22, g_terrain);
            }
            // 三角形只有1个点在多边形内
            if (inPolygonArrayFlag[x][z] == 1 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 0) {
                Vertex = (z) * MAP_W + (x);
                tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle2.pt1 = tmp_triangle1.pt1;
                // 求多边形边界与三角形边的交点
                Vertex = (z) * MAP_W + (x);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_1_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_point1, tmp_point21, tmp_point22, g_terrain);
            }
            // ------------------------------------
            // 三角形只有1个点在多边形内
            if (inPolygonArrayFlag[x + 1][z + 1] == 0 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 1) {
                Vertex = (z) * MAP_W + (x + 1);
                tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle2.pt1 = tmp_triangle1.pt1;
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_1_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_point1, tmp_point21, tmp_point22, g_terrain);
            }
            // 三角形只有1个点在多边形内
            if (inPolygonArrayFlag[x + 1][z + 1] == 0 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 0) {
                Vertex = (z + 1) * MAP_W + (x);
                tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle2.pt1 = tmp_triangle1.pt1;
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_1_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_point1, tmp_point21, tmp_point22, g_terrain);
            }
            // 三角形只有1个点在多边形内
            if (inPolygonArrayFlag[x + 1][z + 1] == 1 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 0) {
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle2.pt1 = tmp_triangle1.pt1;
                // 求多边形边界与三角形边的交点
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_1_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_point1, tmp_point21, tmp_point22, g_terrain);
            }
            /************************************************************************/
            /*       三角形只有2个点在多边形内                                          */
            /************************************************************************/
            // 三角化将后产生3个小三角形
            Triangle tmp_triangle3;
            // ------------------------------------
            // 1-1
            if (inPolygonArrayFlag[x][z] == 1 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 0) {
                Vertex = (z + 1) * MAP_W + (x);
                tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle3.pt1 = tmp_triangle1.pt1;
                Vertex = (z) * MAP_W + (x);
                tmp_triangle2.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle3.pt2 = tmp_triangle2.pt1;
                // 此时 tmp_point1应为在多边形外的一点
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_2_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_point1, tmp_point21, tmp_point22, g_terrain);
            }
            // 1-2
            if (inPolygonArrayFlag[x][z] == 1 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 1) {
                Vertex = (z) * MAP_W + (x + 1);
                tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle3.pt1 = tmp_triangle1.pt1;
                Vertex = (z) * MAP_W + (x);
                tmp_triangle2.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle3.pt2 = tmp_triangle2.pt1;
                // 此时 tmp_point1应为在多边形外的一点
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_2_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_point1, tmp_point21, tmp_point22, g_terrain);
            }
            // 1-3
            if (inPolygonArrayFlag[x][z] == 0 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 1) {
                Vertex = (z) * MAP_W + (x + 1);
                tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle3.pt1 = tmp_triangle1.pt1;
                Vertex = (z + 1) * MAP_W + (x);
                tmp_triangle2.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle3.pt2 = tmp_triangle2.pt1;
                // 此时 tmp_point1应为在多边形外的一点
                Vertex = (z) * MAP_W + (x);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_2_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_point1, tmp_point21, tmp_point22, g_terrain);
            }
            // 2-1
            if (inPolygonArrayFlag[x + 1][z + 1] == 1 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 0) {
                Vertex = (z + 1) * MAP_W + (x);
                tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle3.pt1 = tmp_triangle1.pt1;
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_triangle2.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle3.pt2 = tmp_triangle2.pt1;
                // 此时 tmp_point1应为在多边形外的一点
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_2_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_point1, tmp_point21, tmp_point22, g_terrain);
            }
            // 2-2
            if (inPolygonArrayFlag[x + 1][z + 1] == 1 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 1) {
                Vertex = (z) * MAP_W + (x + 1);
                tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle3.pt1 = tmp_triangle1.pt1;
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_triangle2.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle3.pt2 = tmp_triangle2.pt1;
                // 此时 tmp_point1应为在多边形外的一点
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_2_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_point1, tmp_point21, tmp_point22, g_terrain);
            }
            // 2-3
            if (inPolygonArrayFlag[x + 1][z + 1] == 0 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 1) {
                Vertex = (z) * MAP_W + (x + 1);
                tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle3.pt1 = tmp_triangle1.pt1;
                Vertex = (z + 1) * MAP_W + (x);
                tmp_triangle2.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle3.pt2 = tmp_triangle2.pt1;
                // 此时 tmp_point1应为在多边形外的一点
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_2_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_point1, tmp_point21, tmp_point22, g_terrain);
            }
            /************************************************************************/
            /* 多边形的1个顶点在某个三角形中，但该三角形的3个顶点都在多边形外               */
            /************************************************************************/
            // 此时三角化后将产生4个三角形
            Triangle tmp_triangle4;
            // 1- 1
            if (inPolygonArrayFlag[x][z] == 1 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 0) {
                Vertex = (z) * MAP_W + (x);
                tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle2.pt1 = tmp_triangle1.pt1;
                tmp_triangle3.pt1 = tmp_triangle1.pt1;
                // 三角形共斜边的对角三角形
                PPR_Point tmp_point0;
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_point0.x = g_terrain [Vertex][0];
                tmp_point0.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_last(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_triangle4, tmp_point0, tmp_point1, tmp_point21, tmp_point22, g_terrain);
            }
            // 1-2
            if (inPolygonArrayFlag[x][z] == 0 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 0) {
                Vertex = (z + 1) * MAP_W + (x);
                tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle2.pt1 = tmp_triangle1.pt1;
                tmp_triangle3.pt1 = tmp_triangle1.pt1;
                // 对角三角形
                if (z >= 1) {
                    PPR_Point tmp_point0;
                    Vertex = (z - 1) * MAP_W + (x + 1);
                    tmp_point0.x = g_terrain [Vertex][0];
                    tmp_point0.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    FindTriangles_polygon_has_vertex_in_triangle_last(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_triangle4, tmp_point0, tmp_point1, tmp_point21, tmp_point22, g_terrain);
                }
            }
            // 1-3
            if (inPolygonArrayFlag[x][z] == 0 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 1) {
                Vertex = (z) * MAP_W + (x + 1);
                tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle2.pt1 = tmp_triangle1.pt1;
                tmp_triangle3.pt1 = tmp_triangle1.pt1;
                // 对角三角形
                if (x >= 1) {
                    PPR_Point tmp_point0;
                    Vertex = (z + 1) * MAP_W + (x - 1);
                    tmp_point0.x = g_terrain [Vertex][0];
                    tmp_point0.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    FindTriangles_polygon_has_vertex_in_triangle_last(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_triangle4, tmp_point0, tmp_point1, tmp_point21, tmp_point22, g_terrain);
                }
            }
            // 2-1
            if (inPolygonArrayFlag[x + 1][z + 1] == 1 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 0) {
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle2.pt1 = tmp_triangle1.pt1;
                tmp_triangle3.pt1 = tmp_triangle1.pt1;
                // 三角形共斜边的对角三角形
                PPR_Point tmp_point0;
                Vertex = (z) * MAP_W + (x);
                tmp_point0.x = g_terrain [Vertex][0];
                tmp_point0.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_last(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_triangle4, tmp_point0, tmp_point1, tmp_point21, tmp_point22, g_terrain);
            }
            // 2-2
            if (inPolygonArrayFlag[x + 1][z + 1] == 0 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 0) {
                Vertex = (z + 1) * MAP_W + (x);
                tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle2.pt1 = tmp_triangle1.pt1;
                tmp_triangle3.pt1 = tmp_triangle1.pt1;
                // 对角三角形
                if (x < MAP_W - 2) {
                    PPR_Point tmp_point0;
                    Vertex = (z) * MAP_W + (x + 2);
                    tmp_point0.x = g_terrain [Vertex][0];
                    tmp_point0.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x + 1);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    FindTriangles_polygon_has_vertex_in_triangle_last(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_triangle4, tmp_point0, tmp_point1, tmp_point21, tmp_point22, g_terrain);
                }
            }
            // 2-3
            if (inPolygonArrayFlag[x + 1][z + 1] == 0 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 1) {
                Vertex = (z) * MAP_W + (x + 1);
                tmp_triangle1.pt1 = Point3(g_terrain[Vertex][0], g_terrain[Vertex][1], g_terrain[Vertex][2]);
                tmp_triangle2.pt1 = tmp_triangle1.pt1;
                tmp_triangle3.pt1 = tmp_triangle1.pt1;
                // 对角三角形
                if (z < MAP_W - 2) {
                    PPR_Point tmp_point0;
                    Vertex = (z + 2) * MAP_W + (x);
                    tmp_point0.x = g_terrain [Vertex][0];
                    tmp_point0.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    FindTriangles_polygon_has_vertex_in_triangle_last(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_triangle4, tmp_point0, tmp_point1, tmp_point21, tmp_point22, g_terrain);
                }
            }
        }
    }
}


void Area4Symbol::FindTriangles_polygon_has_vertex_in_triangle_1_1(Area_4& m_area4, Triangle& tmp_triangle1, Triangle& tmp_triangle2, PPR_Point& tmp_point1, PPR_Point& tmp_point21, PPR_Point& tmp_point22, float (*g_terrain)[3]) {  // NOLINT
    CPointPolygonRelationship tmp_PPR;
    // 有1个顶点在多边形内的三角形
    PPR_Polygon tmp_polygon_tri;
    tmp_polygon_tri.push_back(tmp_point1);
    tmp_polygon_tri.push_back(tmp_point21);
    tmp_polygon_tri.push_back(tmp_point22);
    PPR_Point tmp_polygon_point;    // 多边形顶点
    PPR_Point tmp_polygon_point_ra;  // 多边形顶点 相邻的 一个顶点
    PPR_Point tmp_polygon_point_rb;  // 多边形顶点 相邻的 另一个顶点
    PPR_Point JD1, JD2;
    // CString msg;
    bool intersectFlag11 = false;
    bool intersectFlag12 = false;
    bool intersectFlag21 = false;
    bool intersectFlag22 = false;
    int16 tmp_cout = 4;
    while (tmp_cout > 0) {
        if (4 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt1.x;
            tmp_polygon_point.y = m_area4.pt1.z;
            tmp_polygon_point_ra.x = m_area4.pt2.x;
            tmp_polygon_point_ra.y = m_area4.pt2.z;
            tmp_polygon_point_rb.x = m_area4.pt4.x;
            tmp_polygon_point_rb.y = m_area4.pt4.z;
        } else if (3 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt2.x;
            tmp_polygon_point.y = m_area4.pt2.z;
            tmp_polygon_point_ra.x = m_area4.pt1.x;
            tmp_polygon_point_ra.y = m_area4.pt1.z;
            tmp_polygon_point_rb.x = m_area4.pt3.x;
            tmp_polygon_point_rb.y = m_area4.pt3.z;
        } else if (2 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt3.x;
            tmp_polygon_point.y = m_area4.pt3.z;
            tmp_polygon_point_ra.x = m_area4.pt2.x;
            tmp_polygon_point_ra.y = m_area4.pt2.z;
            tmp_polygon_point_rb.x = m_area4.pt4.x;
            tmp_polygon_point_rb.y = m_area4.pt4.z;
        } else if (1 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt4.x;
            tmp_polygon_point.y = m_area4.pt4.z;
            tmp_polygon_point_ra.x = m_area4.pt1.x;
            tmp_polygon_point_ra.y = m_area4.pt1.z;
            tmp_polygon_point_rb.x = m_area4.pt3.x;
            tmp_polygon_point_rb.y = m_area4.pt3.z;
        }
        int32 inTriangleFlag = -1;
        inTriangleFlag = tmp_PPR.InPolygon(tmp_polygon_tri, tmp_polygon_point);
        // 如果多边形的顶点也在三角形中
        if (inTriangleFlag == 0) {
            intersectFlag11 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_ra);
            intersectFlag12 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_rb);
            intersectFlag21 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
            intersectFlag22 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);
            if ((intersectFlag11 || intersectFlag12) && (intersectFlag21 || intersectFlag22)) {
                if (intersectFlag11)
                    JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_ra);
                if (intersectFlag12)
                    JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_rb);
                if (intersectFlag21)
                    JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
                if (intersectFlag22)
                    JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);
                tmp_triangle1.pt2 = Point3(JD1.x, GetHeight(JD1.x, JD1.y, g_terrain), JD1.y);
                tmp_triangle1.pt3 = Point3(tmp_polygon_point.x, GetHeight(tmp_polygon_point.x, tmp_polygon_point.y, g_terrain), tmp_polygon_point.y);
                tmp_triangle2.pt2 = tmp_triangle1.pt3;
                tmp_triangle2.pt3 = Point3(JD2.x, GetHeight(JD2.x, JD2.y, g_terrain), JD2.y);
                m_area4.LocalTrianglesVecotr1_1.push_back(tmp_triangle1);
                m_area4.LocalTrianglesVecotr1_1.push_back(tmp_triangle2);
            }
        }
        tmp_cout--;
    }
}



void Area4Symbol::FindTriangles_polygon_has_vertex_in_triangle_2_1(Area_4& m_area4, Triangle& tmp_triangle1, Triangle& tmp_triangle2, Triangle& tmp_triangle3, PPR_Point& tmp_point1, PPR_Point& tmp_point21, PPR_Point& tmp_point22, float (*g_terrain)[3]) {  // NOLINT
    CPointPolygonRelationship tmp_PPR;
    // 有2个顶点在多边形内的三角形
    PPR_Polygon tmp_polygon_tri;
    tmp_polygon_tri.push_back(tmp_point1);
    tmp_polygon_tri.push_back(tmp_point21);
    tmp_polygon_tri.push_back(tmp_point22);
    PPR_Point tmp_polygon_point;    // 多边形顶点
    PPR_Point tmp_polygon_point_ra;  // 多边形顶点 相邻的 一个顶点
    PPR_Point tmp_polygon_point_rb;  // 多边形顶点 相邻的 另一个顶点
    PPR_Point JD1, JD2;
    // CString msg;
    bool intersectFlag11 = false;
    bool intersectFlag12 = false;
    bool intersectFlag21 = false;
    bool intersectFlag22 = false;
    int16 tmp_cout = 4;
    while (tmp_cout > 0) {
        if (4 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt1.x;
            tmp_polygon_point.y = m_area4.pt1.z;
            tmp_polygon_point_ra.x = m_area4.pt2.x;
            tmp_polygon_point_ra.y = m_area4.pt2.z;
            tmp_polygon_point_rb.x = m_area4.pt4.x;
            tmp_polygon_point_rb.y = m_area4.pt4.z;
        } else if (3 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt2.x;
            tmp_polygon_point.y = m_area4.pt2.z;
            tmp_polygon_point_ra.x = m_area4.pt1.x;
            tmp_polygon_point_ra.y = m_area4.pt1.z;
            tmp_polygon_point_rb.x = m_area4.pt3.x;
            tmp_polygon_point_rb.y = m_area4.pt3.z;
        } else if (2 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt3.x;
            tmp_polygon_point.y = m_area4.pt3.z;
            tmp_polygon_point_ra.x = m_area4.pt2.x;
            tmp_polygon_point_ra.y = m_area4.pt2.z;
            tmp_polygon_point_rb.x = m_area4.pt4.x;
            tmp_polygon_point_rb.y = m_area4.pt4.z;
        } else if (1 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt4.x;
            tmp_polygon_point.y = m_area4.pt4.z;
            tmp_polygon_point_ra.x = m_area4.pt1.x;
            tmp_polygon_point_ra.y = m_area4.pt1.z;
            tmp_polygon_point_rb.x = m_area4.pt3.x;
            tmp_polygon_point_rb.y = m_area4.pt3.z;
        }
        int32 inTriangleFlag = -1;
        inTriangleFlag = tmp_PPR.InPolygon(tmp_polygon_tri, tmp_polygon_point);
        // 如果多边形的顶点也在三角形中
        if (inTriangleFlag == 0) {
            intersectFlag11 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_ra);
            intersectFlag12 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_rb);
            intersectFlag21 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
            intersectFlag22 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);
            if ((intersectFlag11 || intersectFlag12) && (intersectFlag21 || intersectFlag22)) {
                if (intersectFlag11)
                    JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_ra);
                if (intersectFlag12)
                    JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_rb);
                if (intersectFlag21)
                    JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
                if (intersectFlag22)
                    JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);
                tmp_triangle1.pt2 = Point3(JD1.x, GetHeight(JD1.x, JD1.y, g_terrain), JD1.y);
                tmp_triangle1.pt3 = Point3(tmp_polygon_point.x, GetHeight(tmp_polygon_point.x, tmp_polygon_point.y, g_terrain), tmp_polygon_point.y);
                tmp_triangle2.pt2 = tmp_triangle1.pt3;
                tmp_triangle2.pt3 = Point3(JD2.x, GetHeight(JD2.x, JD2.y, g_terrain), JD2.y);
                tmp_triangle3.pt3 = tmp_triangle1.pt3;
                // AfxMessageBox("21");
                m_area4.LocalTrianglesVecotr2_1.push_back(tmp_triangle1);
                m_area4.LocalTrianglesVecotr2_1.push_back(tmp_triangle2);
                m_area4.LocalTrianglesVecotr2_1.push_back(tmp_triangle3);
            }
        }
        tmp_cout--;
    }
}



void Area4Symbol::FindTriangles_polygon_has_vertex_in_triangle_last(Area_4& m_area4, Triangle& tmp_triangle1, Triangle& tmp_triangle2, Triangle& tmp_triangle3, Triangle& tmp_triangle4, PPR_Point& tmp_point0, PPR_Point& tmp_point1, PPR_Point& tmp_point21, PPR_Point& tmp_point22, float (*g_terrain)[3]) {  // NOLINT
    CPointPolygonRelationship tmp_PPR;
    PPR_Polygon tmp_polygon_tri;
    tmp_polygon_tri.push_back(tmp_point0);
    tmp_polygon_tri.push_back(tmp_point21);
    tmp_polygon_tri.push_back(tmp_point22);
    PPR_Point tmp_polygon_point;    // 多边形顶点
    PPR_Point tmp_polygon_point_ra;  // 多边形顶点 相邻的 一个顶点
    PPR_Point tmp_polygon_point_rb;  // 多边形顶点 相邻的 另一个顶点
    PPR_Point JD1, JD2 , JD3, JD4;
    // CString msg;
    int16 tmp_cout = 4;
    while (tmp_cout > 0) {
        if (4 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt1.x;
            tmp_polygon_point.y = m_area4.pt1.z;
            tmp_polygon_point_ra.x = m_area4.pt2.x;
            tmp_polygon_point_ra.y = m_area4.pt2.z;
            tmp_polygon_point_rb.x = m_area4.pt4.x;
            tmp_polygon_point_rb.y = m_area4.pt4.z;
        } else if (3 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt2.x;
            tmp_polygon_point.y = m_area4.pt2.z;
            tmp_polygon_point_ra.x = m_area4.pt1.x;
            tmp_polygon_point_ra.y = m_area4.pt1.z;
            tmp_polygon_point_rb.x = m_area4.pt3.x;
            tmp_polygon_point_rb.y = m_area4.pt3.z;
        } else if (2 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt3.x;
            tmp_polygon_point.y = m_area4.pt3.z;
            tmp_polygon_point_ra.x = m_area4.pt2.x;
            tmp_polygon_point_ra.y = m_area4.pt2.z;
            tmp_polygon_point_rb.x = m_area4.pt4.x;
            tmp_polygon_point_rb.y = m_area4.pt4.z;
        } else if (1 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt4.x;
            tmp_polygon_point.y = m_area4.pt4.z;
            tmp_polygon_point_ra.x = m_area4.pt1.x;
            tmp_polygon_point_ra.y = m_area4.pt1.z;
            tmp_polygon_point_rb.x = m_area4.pt3.x;
            tmp_polygon_point_rb.y = m_area4.pt3.z;
        }
        int32 inTriangleFlag = -1;
        inTriangleFlag = tmp_PPR.InPolygon(tmp_polygon_tri, tmp_polygon_point);
        bool intersectFlag11 = false;
        bool intersectFlag12 = false;
        bool intersectFlag21 = false;
        bool intersectFlag22 = false;
        bool intersectFlag31 = false;
        bool intersectFlag32 = false;
        // 如果多边形的顶点也在对角三角形中
        if (inTriangleFlag == 0) {
            // 与三角形斜边有交点
            intersectFlag31 = tmp_PPR.Meet(tmp_point21, tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
            intersectFlag32 = tmp_PPR.Meet(tmp_point21, tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);
            intersectFlag11 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_ra);
            intersectFlag12 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_rb);
            intersectFlag21 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
            intersectFlag22 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);
            if ((intersectFlag31 && intersectFlag32) && (intersectFlag11 || intersectFlag12) && (intersectFlag21 || intersectFlag22)) {
                if (intersectFlag11)
                    JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_ra);
                if (intersectFlag12)
                    JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_rb);
                if (intersectFlag21)
                    JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
                if (intersectFlag22)
                    JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);
                JD3 = tmp_PPR.getJD(tmp_point21, tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
                JD4 = tmp_PPR.getJD(tmp_point21, tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);
                PPR_Point tmp;
                float len1 = (JD3.x - tmp_point21.x) * (JD3.x - tmp_point21.x) + (JD3.y - tmp_point21.y);
                float len2 = (JD4.x - tmp_point21.x) * (JD4.x - tmp_point21.x) + (JD4.y - tmp_point21.y);
                if (len1 > len2) {
                    tmp = PPR_Point(JD3.x, JD3.y);
                    JD3 = PPR_Point(JD4.x, JD4.y);
                    JD4 = PPR_Point(tmp.x, tmp.y);
                }
                tmp_triangle4.pt1 = Point3(tmp_polygon_point.x, GetHeight(tmp_polygon_point.x, tmp_polygon_point.y, g_terrain), tmp_polygon_point.y);
                tmp_triangle4.pt2 = Point3(JD3.x, GetHeight(JD3.x, JD3.y, g_terrain), JD3.y);
                tmp_triangle4.pt3 = Point3(JD4.x, GetHeight(JD4.x, JD4.y, g_terrain), JD4.y);
                tmp_triangle1.pt2 = Point3(JD1.x, GetHeight(JD1.x, JD1.y, g_terrain), JD1.y);
                tmp_triangle1.pt3 = tmp_triangle4.pt2;
                tmp_triangle2.pt2 = Point3(JD2.x, GetHeight(JD2.x, JD2.y, g_terrain), JD2.y);
                tmp_triangle2.pt3 = tmp_triangle4.pt3;
                tmp_triangle3.pt2 = tmp_triangle4.pt2;
                tmp_triangle3.pt3 = tmp_triangle4.pt3;
                // AfxMessageBox("last2");
                m_area4.LocalTrianglesVecotr_last.push_back(tmp_triangle1);
                m_area4.LocalTrianglesVecotr_last.push_back(tmp_triangle2);
                m_area4.LocalTrianglesVecotr_last.push_back(tmp_triangle3);
                m_area4.LocalTrianglesVecotr_last.push_back(tmp_triangle4);
            }
        }
        tmp_cout--;
    }
}



/************************************************************************/
/* Function: 获取地面高度                                                */
/************************************************************************/
float Area4Symbol::GetHeight(float x, float z, float (*g_terrain)[3]) {
    float CameraX = x / MAP_SCALE;                  // 计算在哪一列
    float CameraZ = -z / MAP_SCALE;                 // 计算在哪一行
    int32 Col0 = static_cast<int32>(CameraX);       // 块的列号
    int32 Row0 = static_cast<int32>(CameraZ);       // 块的行号
    int32 Col1 = Col0 + 1;                          // 相邻列
    int32 Row1 = Row0 + 1;                          // 相邻块
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