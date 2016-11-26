#ifndef L2D_ROAD_H
#define L2D_ROAD_H

#include "../MathUtils/Vec3.h"
#include "../Base/Uncopyable.h"
#include <vector>
#include <string>



struct LineSymbol {
    LineSymbol() : line_texture_(""),
        line_type_(0),
        line_width_(8) {
        line_points_.clear();
    }

    vector<Vec3*> line_points_;  // 线上各点
    string line_texture_;       // 纹理
    int line_type_;             // 线符号类型
    float line_width_;          // 线宽
};




class L2DRoad : Base::Uncopyable {
  public:
    L2DRoad();
    ~L2DRoad();
  protected:
  private:
};


#endif  // L2D_ROAD_H