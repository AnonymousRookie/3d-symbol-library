#pragma once
#include "../MathUtils/Vec3.h"

struct FiveStar {
    // 五角星边长
    float d_;
    Point3 pO_;
    // 待求
    Point3 pA_;
    Point3 pB_;
    Point3 pC_;
    Point3 pD_;
    Point3 pE_;
    Point3 pP_;
    Point3 pQ_;
    Point3 pR_;
    Point3 pS_;
    Point3 pT_;
};

class FiveStarTools {
  public:
    static void CalculateFiveStarInfo(const float d, const Point3& pO, FiveStar* pFiveStarInfo);
};