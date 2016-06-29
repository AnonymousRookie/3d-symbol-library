
// 判断点与多边形的关系
// 点在多边形内、上、外


/* 射线法判断点q与多边形polygon的位置关系，要求polygon为简单多边形，顶点逆时针排列
 如果点在多边形内：     返回0
 如果点在多边形边上：       返回1
 如果点在多边形外：     返回2
*/






#pragma once



const double INFINITY = 1e10;
const double ESP = 1e-5;
const int MAX_N = 1000;

struct PPR_Point {
    PPR_Point() {}
    PPR_Point(double x, double y): x(x), y(y) {}
    double x, y;
};
struct LineSegment {
    PPR_Point pt1, pt2;
};





typedef vector<PPR_Point> PPR_Polygon;

class CPointPolygonRelationship {
  public:
    CPointPolygonRelationship(void);
    ~CPointPolygonRelationship(void);


    // 判断点与多边形的关系 ========================================================

    // 计算叉乘 |P0P1| × |P0P2|
    double Multiply(PPR_Point p1, PPR_Point p2, PPR_Point p0);
    // 判断线段是否包含点point
    bool IsOnline(PPR_Point point, LineSegment line);
    // 判断线段相交
    bool Intersect(LineSegment L1, LineSegment L2);
    // 判断点在多边形内
    int InPolygon(const PPR_Polygon& polygon, PPR_Point point);







    // 求2线段的交点 ========================================================
    int sgn(double x) {
        return x < -ESP ? -1 : (x > ESP);
    }

    double Cross(const PPR_Point& p1, const PPR_Point& p2, const PPR_Point& p3, const PPR_Point& p4) {
        return (p2.x - p1.x) * (p4.y - p3.y) - (p2.y - p1.y) * (p4.x - p3.x);
    }

    double Area(const PPR_Point& p1, const PPR_Point& p2, const PPR_Point& p3) {
        return Cross(p1, p2, p1, p3);
    }

    double fArea(const PPR_Point& p1, const PPR_Point& p2, const PPR_Point& p3) {
        return fabs(Area(p1, p2, p3));
    }

    bool Meet(const PPR_Point& p1, const PPR_Point& p2, const PPR_Point& p3, const PPR_Point& p4) {
        return max(min(p1.x, p2.x), min(p3.x, p4.x)) <= min(max(p1.x, p2.x), max(p3.x, p4.x))
               && max(min(p1.y, p2.y), min(p3.y, p4.y)) <= min(max(p1.y, p2.y), max(p3.y, p4.y))
               && sgn(Cross(p3, p2, p3, p4) * Cross(p3, p4, p3, p1)) >= 0
               && sgn(Cross(p1, p4, p1, p2) * Cross(p1, p2, p1, p3)) >= 0;
    }
    PPR_Point getJD(const PPR_Point& p1, const PPR_Point& p2, const PPR_Point& p3, const PPR_Point& p4) {
        double s1 = fArea(p1, p2, p3) , s2 = fArea(p1, p2, p4);
        return PPR_Point((p4.x * s1 + p3.x * s2) / (s1 + s2), (p4.y * s1 + p3.y * s2) / (s1 + s2));
    }


};

