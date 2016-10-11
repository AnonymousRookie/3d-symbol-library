#ifndef N_CLOCK_H
#define N_CLOCK_H

#include "Base/Uncopyable.h"

class NClcok : Base::Uncopyable {
  public:
    NClcok();
    ~NClcok();

    void MakeClockList() const;
    void PrintText(float x, float y, char* str) const;
    void DrawNorthPt() const;

  public:
    // 显示列表参数
    GLuint m_ClockList;     // 时钟指北针显示列表
    float m_NorthPtangle;   // 指北针初始指向角度
};

#endif  // N_CLOCK_H