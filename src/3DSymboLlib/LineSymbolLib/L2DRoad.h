#ifndef L2D_ROAD_H
#define L2D_ROAD_H

#include "../MathUtils/Vec3.h"
#include "../Base/Uncopyable.h"
#include <vector>
#include <string>
#include "../AreaSymbolLib/Area4.h"
#include <unordered_map>
#include "../MathUtils/PointPolygonRelationship.h"
#include <memory>

struct LineSymbol {
    LineSymbol() : line_texture_("NONE"),
        line_type_(0),
        line_width_(18.5),
        deleted_(false),
        inserted_(false) {
        line_points_.clear();
    }

    vector<Vec3> line_points_;  // 线上各点
    string line_texture_;       // 纹理
    int32 line_type_;             // 线符号类型
    float line_width_;          // 线宽
    bool deleted_;  // 标记是否已经删除
    bool inserted_;  // 标记是否已插入
};




class L2DRoad : Base::Uncopyable {
  public:
    L2DRoad();
    ~L2DRoad();

    // 根据线段的2个端点, 获取增加宽度后的矩形的4个顶点
    float GetArea4FromLine(const Point3& p1, const Point3& p2, const float& line_width, Area_4* pArea4/*output*/, float (*g_terrain)[3]);

    float GetHeight(float x, float z, float (*g_terrain)[3]);

    // 保存线符号，并且增加宽度变成多边形
    void SaveLineSymbol(LineSymbol* pLineSymbol_, float (*g_terrain)[3]);


    float distance_xz(const Vec3& v1, const Vec3& v2) {
        float dx = v1.x - v2.x;
        float dz = v1.z - v2.z;
        return std::sqrt(dx * dx + dz * dz);
    }

    std::unordered_map<int32, LineSymbol> allLineSymbols_;  // 存放所有的线符号
    std::unordered_map<int32, std::shared_ptr<CArray<PArea_4, PArea_4>>> allLineArea4Array_;  // 存放所有的线的面
    BOOL Line_fuse_Flag_;  // 是否已经对线符号进行融合

  protected:
  private:
};


#endif  // L2D_ROAD_H