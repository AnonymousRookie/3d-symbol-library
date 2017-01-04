#pragma once
#include "../MathUtils/Vec3.h"
#include "../Base/Uncopyable.h"
#include <vector>
#include <string>
#include "../AreaSymbolLib/Area4.h"
#include <unordered_map>
#include <memory>

struct AreaFiveStarSymbol {
    AreaFiveStarSymbol() : area_texture_("NONE"),
        d_(10.0f),
        theta_(36.0f),
        area_type_(""),
        deleted_(false) {
    }

    float d_;           // 五角星边长
    float theta_;       // 五角星锐角度数(36度)
    Point3 pO_;         // 五角星中心坐标
    string area_texture_;       // 纹理
    string area_type_;          // 面符号类型
    bool deleted_;      // 标记是否已经删除

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
    // 外接矩形
    Point3 pI_;
    Point3 pJ_;
    Point3 pH_;

};



class FiveStar : Base::Uncopyable {
public:
    FiveStar() {}
    ~FiveStar() {}
  public:
    void SaveFiveStarInfo(const float d, const Point3& pO, AreaFiveStarSymbol* pFiveStarSymbol);

public:
    std::unordered_map<int32, AreaFiveStarSymbol> allFiveStarSymbols_;  // 存放所有的五角星面符号
    std::unordered_map<int32, std::shared_ptr<CArray<PArea_4, PArea_4>>> allFiveStarArea4Array_;  // 存放所有五角星的小四边形
    BOOL fiveStar_fuse_Flag_;  // 是否已经对五角星符号进行融合
};