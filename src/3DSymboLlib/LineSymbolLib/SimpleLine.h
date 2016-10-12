#ifndef SIMPLE_LINE_H
#define SIMPLE_LINE_H

#include "../MathUtils/Vec3.h"
#include "../SymbolDefines.h"
#include "../GlobalVariable.h"
#include "../Base/Uncopyable.h"

class SimpleLine : Base::Uncopyable {
  public:
    SimpleLine();
    ~SimpleLine();

  public:
    // 空间点求投影到平面的直线方程系数ABC, Ax+By+C=0
    void getLine2ABC(float* A, float* B, float* C, Point3 p1, Point3 p2);
    // 计算平面交点坐标,并计算出交点出的高程值
    void CalcuateJD(int32 rowNum, int32 row_index_begin, int32 row_index_end,
                    int32 colNum, int32 col_index_begin, int32 col_index_end, Line3 _line, vector<Point3>& _pv, float (*g_terrain)[3]);  // NOLINT

    // 计算2条直线的交点y=x+b, Ax+By+C=0, 返回-1表示无交点
    BOOL GetJDFrom2Line(Point3* p/*out*/, double b, double A, double B, double C, float (*g_terrain)[3]);

    // 计算线段_line所经过的横向和纵向格网数, 及索引范围
    void CalcuateGridNum(int32* rowNum, int32* row_index_begin, int32* row_index_end,
                         int32* colNum, int32* col_index_begin, int32* col_index_end, Line3 _line);

    // 线矢量与地表三角网融合
    void OnLineFuse(const CArray<PLine3, PLine3>& m_LinesArray /* 存放所有的线符号*/ , float (*g_terrain)[3]);

    void DrawJDLine(const vector<Point3>& _pv1,  const vector<Point3>& _pv2);

    // 所有三角形顶点坐标最小最大值
    void GetMinXY(const vector<Point3>& _pv1,  const vector<Point3>& _pv2, double* _minX, double* _minY, double* _maxX, double* _maxY);

    // 线符号纹理坐标
    void GetUV(double _x, double _y, double _minX, double _minY, double _maxX, double _maxY, double* _u, double* _v);



  public:
    vector<Point3> JD_vector1;
    vector<Point3> JD_vector2;
    vector<Point3> JD_vector3;  // 斜线交点


    vector<Point3> Line_a_JD_vector;
    vector<Point3> Line_b_JD_vector;

    BOOL fuse_Flag;
};

#endif  // SIMPLE_LINE_H