#include "stdafx.h"
#include "SingleLine.h"


// 空间点求投影到平面的直线方程系数ABC, Ax+By+C=0
void SingleLine::getLine2ABC(float* A, float* B, float* C, Point3 p1, Point3 p2) {
    // 直线AX+BY+C=0的一般式方程就是：
    //  A = Y2 - Y1
    //  B = X1 - X2
    //  C = X2*Y1 - X1*Y2
    *A = p2.z - p1.z;
    *B = p1.x - p2.x;
    *C = p2.x * p1.z - p1.x * p2.z;
}

// 计算平面交点坐标,并计算出交点出的高程值
void SingleLine::CalcuateJD(int32 rowNum, int32 row_index_begin, int32 row_index_end,
                            int32 colNum, int32 col_index_begin, int32 col_index_end, Line3 _line, vector<Point3>& _pv,
                            float (*g_terrain)[3]) {  // NOLINT
    // 直线方程系数ABC, Ax+By+C=0
    float A, B, C;
    getLine2ABC(&A, &B, &C, _line.pt1, _line.pt2);
    Point3 tmp_point;
    JD_vector1.clear();
    JD_vector2.clear();
    JD_vector3.clear();
    _pv.clear();
    // 交点1 ---------------------------------------------------------------------
    // 通过格网横坐标 求与线段交点
    if (row_index_begin < row_index_end) {
        for (int32 r = row_index_begin + 1; r < row_index_end; ++r) {
            tmp_point.x = static_cast<float>(r) * MAP_SCALE;  // 平面横坐标
            // 平面纵坐标
            if (MATH_FLOAT_EQUAL_0(B)) {
                break;
            } else {
                tmp_point.z = ((-A) * tmp_point.x - C) / B;
            }
            tmp_point.y = Global::GetHeight(tmp_point.x, tmp_point.z, g_terrain);
            JD_vector1.push_back(tmp_point);
        }
    } else if (row_index_begin > row_index_end) {
        for (int32 r = row_index_begin - 1; r > row_index_end; --r) {
            tmp_point.x = static_cast<float>(r) * MAP_SCALE;  // 平面横坐标
            // 平面纵坐标
            if (MATH_FLOAT_EQUAL_0(B)) {
                break;
            } else {
                tmp_point.z = ((-A) * tmp_point.x - C) / B;
            }
            tmp_point.y = Global::GetHeight(tmp_point.x, tmp_point.z, g_terrain);
            JD_vector1.push_back(tmp_point);
        }
    }
    // 交点2 ---------------------------------------------------------------------
    if (col_index_begin < col_index_end) {
        // 通过格网纵坐标 求与线段交点
        for (int32 c = col_index_begin + 1; c < col_index_end; ++c) {
            tmp_point.z = static_cast<float>(-c) * MAP_SCALE;  // 平面纵坐标
            // 平面横坐标
            if (MATH_FLOAT_EQUAL_0(A)) {
                break;
            } else {
                // Ax+By+C=0
                tmp_point.x = ((-B) * tmp_point.z - C) / A;
            }
            tmp_point.y = Global::GetHeight(tmp_point.x, tmp_point.z, g_terrain);
            JD_vector2.push_back(tmp_point);
        }
    } else if (col_index_begin > col_index_end) {
        // 通过格网纵坐标 求与线段交点
        for (int32 c = col_index_begin - 1; c > col_index_end; --c) {
            tmp_point.z = static_cast<float>(-c) * MAP_SCALE;  // 平面纵坐标
            // 平面横坐标
            if (MATH_FLOAT_EQUAL_0(A)) {
                break;
            } else {
                // Ax+By+C=0
                tmp_point.x = ((-B) * tmp_point.z - C) / A;
            }
            tmp_point.y = Global::GetHeight(tmp_point.x, tmp_point.z, g_terrain);
            JD_vector2.push_back(tmp_point);
        }
    }
    // 交点3 ---------------------------------------------------------------------
    float line_pos_b = MATH_MIN(_line.pt1.x, _line.pt2.x);
    float line_pos_e = MATH_MAX(_line.pt1.x, _line.pt2.x);
    for (int32 r = 0; r < MAP_W; ++r) {
        double b = static_cast<float>(-r) * MAP_SCALE;
        if (GetJDFrom2Line(&tmp_point, b, A, B, C, g_terrain)) {
            if ((line_pos_b < tmp_point.x) && (tmp_point.x < line_pos_e)) {
                JD_vector3.push_back(tmp_point);
            }
        }
    }
    // 2端点
    _pv.push_back(_line.pt1);
    _pv.push_back(_line.pt2);
    //----------------------------------------------
    for (uint32 i = 0; i < JD_vector1.size(); ++i) {
        _pv.push_back(JD_vector1[i]);
    }
    for (uint32 i = 0; i < JD_vector2.size(); ++i) {
        _pv.push_back(JD_vector2[i]);
    }
    // 斜线交点
    for (uint32 i = 0; i < JD_vector3.size(); ++i) {
        _pv.push_back(JD_vector3[i]);
    }
    sort(_pv.begin(), _pv.end(), [](const Point3 & p1, const Point3 & p2)->bool {return p1.x < p2.x;}); // NOLINT
}

// 计算2条直线的交点y=x+b, Ax+By+C=0, 返回0表示无交点
BOOL SingleLine::GetJDFrom2Line(Point3* p/*out*/, double b, double A, double B, double C, float (*g_terrain)[3]) {
    if (MATH_FLOAT_EQUAL_0(A)) {  // A == 0
        p->z = -C / B;
        p->x = p->z - b;
        p->y = Global::GetHeight(p->x, p->z, g_terrain);
    } else {
        if (!(MATH_FLOAT_EQUAL_0(B))) {
            if (MATH_FLOAT_EQUAL_0(-A / B - 1)) {
                return 0;  // 2直线平行无交点
            } else {
                p->x = (-1) * (B * b + C) / (A + B);
                p->z = p->x + b;
                p->y = Global::GetHeight(p->x, p->z, g_terrain);
            }
        } else {  // B == 0
            p->x = -C / A;
            p->z = p->x + b;
            p->y = Global::GetHeight(p->x, p->z, g_terrain);
        }
    }
    return 1;
}



// 计算线段_line所经过的横向和纵向格网数, 及索引范围
void SingleLine::CalcuateGridNum(int32* rowNum, int32* row_index_begin, int32* row_index_end,
                                 int32* colNum, int32* col_index_begin, int32* col_index_end, Line3 _line) {
    int32 tmp_rowNum = 0;
    int32 tmp_row_index_begin = 0;
    int32 tmp_row_index_end = 0;
    int32 tmp_colNum = 0;
    int32 tmp_col_index_begin = 0;
    int32 tmp_col_index_end = 0;
    double r1 = abs(_line.pt1.x);
    double c1 = abs(_line.pt1.z);
    double r2 = abs(_line.pt2.x);
    double c2 = abs(_line.pt2.z);
    tmp_row_index_begin = static_cast<int32>(r1) / static_cast<int32>(MAP_SCALE);
    tmp_row_index_end = static_cast<int32>(r2) / static_cast<int32>(MAP_SCALE);
    tmp_col_index_begin = static_cast<int32>(c1) / static_cast<int32>(MAP_SCALE);
    tmp_col_index_end = static_cast<int32>(c2) / static_cast<int32>(MAP_SCALE);
    *rowNum = abs(tmp_row_index_end - tmp_row_index_begin);
    *row_index_begin = tmp_row_index_begin;
    *row_index_end = tmp_row_index_end;
    *colNum = abs(tmp_col_index_end - tmp_col_index_begin);
    *col_index_begin = tmp_col_index_begin;
    *col_index_end = tmp_col_index_end;
}



 void SingleLine::GetEveryJDInLines(const Point3& p1, const Point3& p2) 
 {
    Line_a_JD_vector.clear();

    int32 tmp_rowNum = 0;
    int32 tmp_row_index_begin = 0;
    int32 tmp_row_index_end = 0;
    int32 tmp_colNum = 0;
    int32 tmp_col_index_begin = 0;
    int32 tmp_col_index_end = 0;
    Line3 tmp_line;
    tmp_line.pt1 = p1;
    tmp_line.pt2 = p2;

    CalcuateGridNum(&tmp_rowNum, &tmp_row_index_begin, &tmp_row_index_end,
                    &tmp_colNum, &tmp_col_index_begin, &tmp_col_index_end, tmp_line);
    CalcuateJD(tmp_rowNum, tmp_row_index_begin, tmp_row_index_end,
               tmp_colNum, tmp_col_index_begin, tmp_col_index_end, tmp_line, Line_a_JD_vector, g_terrain);

    all_line_JD_vector_.push_back(Line_a_JD_vector);
    Line_a_JD_vector.clear();

    LOGGER_INFO << " all_line_JD_vector_[0].size() = " << all_line_JD_vector_[0].size();
}

 
 

