#ifndef N_CLOCK_H
#define N_CLOCK_H

class NClcok {
  public:
    NClcok();
    ~NClcok();

    void MakeClockList();
    void PrintText(float x, float y, char* str);
    void DrawNorthPt();

  public:
    // 显示列表参数
    GLuint m_ClockList;     // 时钟指北针显示列表
    float m_NorthPtangle;   // 指北针初始指向角度
};

#endif  // N_CLOCK_H