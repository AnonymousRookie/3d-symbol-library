#include "stdafx.h"
#include "FiveStar.h"
#include "..\MathUtils\MathUtil.h"




void FiveStar::SaveFiveStarInfo(const float d, const Point3& pO, AreaFiveStarSymbol* pFiveStarSymbol) {

    if (pFiveStarSymbol == nullptr || pFiveStarSymbol->area_type_ == "") {
        LOGGER_WARNING << "pFiveStarSymbol == nullptr || pFiveStarSymbol->area_type_ == """;
        return;
    }



    // CalculateFiveStarInfo 
    pFiveStarSymbol->d_ = d;
    pFiveStarSymbol->pO_ = pO;
    //
    float theta = MATH_DEG_TO_RAD(pFiveStarSymbol->theta_ / 2);
    //
    float a = d * sin(theta);
    float b = d * cos(theta);
    float c = a / tan(2 * theta);
    float e = a / sin(2 * theta);
    //
    float m = pO.x;
    float n = pO.z;
    float h = pO.y;
    pFiveStarSymbol->pA_ = Point3(m, h, n + b + c);
    pFiveStarSymbol->pR_ = Point3(m, h, n - e);
    pFiveStarSymbol->pB_ = Point3(m - d - a, h, n + c);
    pFiveStarSymbol->pE_ = Point3(m + d + a, h, n + c);
    pFiveStarSymbol->pP_ = Point3(m - a, h, n + c);
    pFiveStarSymbol->pT_ = Point3(m + a, h, n + c);
    pFiveStarSymbol->pQ_ = Point3(m - e * cos(theta), h, n - e * sin(theta));
    pFiveStarSymbol->pS_ = Point3(m + e * cos(theta), h, n - e * sin(theta));
    pFiveStarSymbol->pC_ = Point3(m - d * cos(2 * theta), h, n - e - d * sin(2 * theta));
    pFiveStarSymbol->pD_ = Point3(m + d * cos(2 * theta), h, n - e - d * sin(2 * theta));
    // 外接矩形
    pFiveStarSymbol->pI_ = Point3(m - d - a, h, n - e - d * sin(2 * theta));
    pFiveStarSymbol->pJ_ = Point3(m + d + a, h, n - e - d * sin(2 * theta));
    pFiveStarSymbol->pH_ = Point3(m - d - a, h, n + b + c);
    
    // save

    int32 fiveStarcount = allFiveStarSymbols_.size();
    allFiveStarSymbols_.insert(std::unordered_map<int32, AreaFiveStarSymbol>::value_type(fiveStarcount, *pFiveStarSymbol));
 

    // 存放一个五角星中所有的面
    std::shared_ptr<CArray<PArea_4, PArea_4>> l_fiveStar_Area4_Array = std::make_shared<CArray<PArea_4, PArea_4>>();

    PArea_4 area = new Area_4;
    // APOT
    area->pt1 = pFiveStarSymbol->pA_;
    area->pt2 = pFiveStarSymbol->pP_;
    area->pt3 = pFiveStarSymbol->pO_;
    area->pt4 = pFiveStarSymbol->pT_;
    l_fiveStar_Area4_Array->Add(area);

    area = new Area_4;
    // BQOP
    area->pt1 = pFiveStarSymbol->pB_;
    area->pt2 = pFiveStarSymbol->pQ_;
    area->pt3 = pFiveStarSymbol->pO_;
    area->pt4 = pFiveStarSymbol->pP_;
    l_fiveStar_Area4_Array->Add(area);

    area = new Area_4;
    // CROQ
    area->pt1 = pFiveStarSymbol->pC_;
    area->pt2 = pFiveStarSymbol->pR_;
    area->pt3 = pFiveStarSymbol->pO_;
    area->pt4 = pFiveStarSymbol->pQ_;
    l_fiveStar_Area4_Array->Add(area);

    area = new Area_4;
    // DSOR
    area->pt1 = pFiveStarSymbol->pD_;
    area->pt2 = pFiveStarSymbol->pS_;
    area->pt3 = pFiveStarSymbol->pO_;
    area->pt4 = pFiveStarSymbol->pR_;
    l_fiveStar_Area4_Array->Add(area);

    area = new Area_4;
    // ETOS
    area->pt1 = pFiveStarSymbol->pE_;
    area->pt2 = pFiveStarSymbol->pT_;
    area->pt3 = pFiveStarSymbol->pO_;
    area->pt4 = pFiveStarSymbol->pS_;
    l_fiveStar_Area4_Array->Add(area);
    
    allFiveStarArea4Array_.insert(std::unordered_map<int32, std::shared_ptr<CArray<PArea_4, PArea_4>>>::value_type(fiveStarcount, l_fiveStar_Area4_Array));
}
