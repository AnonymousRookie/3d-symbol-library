#include "stdafx.h"
#include "FiveStar.h"
#include "..\MathUtils\MathUtil.h"


void FiveStarTools::CalculateFiveStarInfo(const float d, const Point3& pO, FiveStar* pFiveStarInfo) {
    pFiveStarInfo->d_ = d;
    pFiveStarInfo->pO_ = pO;
    //
    float theta = MATH_DEG_TO_RAD(30);
    //
    float a = d * sin(theta);
    float b = d * cos(theta);
    float c = a / tan(2 * theta);
    float e = a / sin(2 * theta);
    //
    float m = pO.x;
    float n = pO.z;
    float h = pO.y;
    pFiveStarInfo->pA_ = Point3(m, h, n + b + c);
    pFiveStarInfo->pR_ = Point3(m, h, n - e);
    pFiveStarInfo->pB_ = Point3(m - d - a, h, n + c);
    pFiveStarInfo->pE_ = Point3(m + d + a, h, n + c);
    pFiveStarInfo->pP_ = Point3(m - a, h, n + c);
    pFiveStarInfo->pT_ = Point3(m + a, h, n + c);
    pFiveStarInfo->pQ_ = Point3(m - e * cos(theta), h, n - e * sin(theta));
    pFiveStarInfo->pS_ = Point3(m + e * cos(theta), h, n - e * sin(theta));
    pFiveStarInfo->pC_ = Point3(m - d * cos(2 * theta), h, n - e - d * sin(2 * theta));
    pFiveStarInfo->pD_ = Point3(m + d * cos(2 * theta), h, n - e - d * sin(2 * theta));
}