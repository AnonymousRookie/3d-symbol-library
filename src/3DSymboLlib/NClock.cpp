#include "stdafx.h"
#include "NClock.h"


NClcok::NClcok()
    : m_NorthPtangle(90) {}

NClcok::~NClcok() {}


/****************************************************************/
/* Function: 创建时钟指北针显示列表                               */
/****************************************************************/
void NClcok::MakeClockList() {
    glNewList(m_ClockList, GL_COMPILE);             // 创建显示列表
    float R = 0.5, x, y;                            // 时钟圆盘半径
    int32 i;
    glColor3f(0.0, 1.0, 1.0);                       // 设置文字颜色
    x = R * cos((0) * PAI_D180) + 0.37;             // 加上偏移量，准备写入字母"E"，表示刻度3
    y = R * sin((0) * PAI_D180) + 0.48;
    PrintText(x, y, (LPTSTR)(LPCTSTR)"E");          // 在设置坐标位置写入E，表示方向“东”
    x = R * cos((90) * PAI_D180) + 0.47;            // 加上偏移量，准备写入字母"N"，表示刻度12
    y = R * sin((90) * PAI_D180) + 0.36;
    PrintText(x, y, (LPTSTR)(LPCTSTR)"N");          // 在设置坐标位置写入N，表示方向“北”
    x = R * cos((180) * PAI_D180) + 0.59;           // 加上偏移量，准备写入字母"W" ，表示刻度9
    y = R * sin((180) * PAI_D180) + 0.48;
    PrintText(x, y, (LPTSTR)(LPCTSTR)"W");          // 在设置坐标位置写入W，表示方向“西”
    x = R * cos((270) * PAI_D180) + 0.48;           // 加上偏移量，准备写入字母"S" ，表示刻度6
    y = R * sin((270) * PAI_D180) + 0.58;
    PrintText(x, y, (LPTSTR)(LPCTSTR)"S");          // 在设置坐标位置写入S，表示方向“南”
    glColor3f(1.0, 1.0, 1.0);                       // 设置时钟刻度数字颜色
    x = R * cos((30) * PAI_D180) + 0.39;            // 设置坐标
    y = R * sin((30) * PAI_D180) + 0.43;
    PrintText(x, y, (LPTSTR)(LPCTSTR)"2");          // 写入数字刻度
    x = R * cos((60) * PAI_D180) + 0.42;
    y = R * sin((60) * PAI_D180) + 0.40;
    PrintText(x, y, (LPTSTR)(LPCTSTR)"1");          // 写入数字刻度1
    x = R * cos((120) * PAI_D180) + 0.49;
    y = R * sin((120) * PAI_D180) + 0.38;
    PrintText(x, y, (LPTSTR)(LPCTSTR)"11");         // 写入数字刻度11
    x = R * cos((150) * PAI_D180) + 0.55;
    y = R * sin((150) * PAI_D180) + 0.42;
    PrintText(x, y, (LPTSTR)(LPCTSTR)"10");         // 写入数字刻度10
    x = R * cos((210) * PAI_D180) + 0.58;
    y = R * sin((210) * PAI_D180) + 0.53;
    PrintText(x, y, (LPTSTR)(LPCTSTR)"8");          // 写入数字刻度8
    x = R * cos((240) * PAI_D180) + 0.54;
    y = R * sin((240) * PAI_D180) + 0.58;
    PrintText(x, y, (LPTSTR)(LPCTSTR)"7");          // 写入数字刻度7
    x = R * cos((300) * PAI_D180) + 0.43;
    y = R * sin((300) * PAI_D180) + 0.58;
    PrintText(x, y, (LPTSTR)(LPCTSTR)"5");          // 写入数字刻度5
    x = R * cos((330) * PAI_D180) + 0.40;
    y = R * sin((330) * PAI_D180) + 0.52;
    PrintText(x, y, (LPTSTR)(LPCTSTR)"4");          // 写入数字刻度4
    // 设置时钟圆内圆盘的颜色
    glColor3f(0.0, 1.0, 0.0);
    glLineWidth(2.0);                               // 设置线宽
    // 绘制时钟圆外圆盘
    glBegin(GL_LINE_STRIP);
    for (i = 0; i <= 360; i++) {
        x = R * cos(i * PAI_D180) + 0.5;
        y = R * sin(i * PAI_D180) + 0.5;
        glVertex2f(x, y);
    }
    glEnd();
    // 绘制时钟内表示小时之间的刻度,用圆点表示
    float d;
    for (i = 0; i <= 360; i += 6) {
        switch (i) {
            case 0:                                     // 在N(12点)处
                glColor3f(0.0, 1.0, 1.0);               // 设置颜色
                glPointSize(4.0);                       // 设置点的大小
                break;
            case 90:                                    // 在W(9点)处
                glColor3f(0.0, 1.0, 1.0);               // 设置颜色
                glPointSize(4.0);                       // 设置点的大小
                break;
            case 180:                                   // 在S(6点)处
                glColor3f(0.0, 1.0, 1.0);               // 设置颜色
                glPointSize(4.0);                       // 设置点的大小
                break;
            case 270:                                   // 在E(3点)处
                glColor3f(0.0, 1.0, 1.0);               // 设置颜色
                glPointSize(4.0);                       // 设置点的大小
                break;
            default:
                glColor3f(0.77, 0.67, 0.95);            // 设置颜色
                glPointSize(2.0);                       // 设置点的大小
                break;
        }
        if (i % 30 == 0 && i % 90 != 0) {           // 在整时刻处(如7点,8点等)
            glColor3f(1.0, 0.0, 1.0);               // 设置颜色
            glPointSize(3.0);                       // 设置点的大小
        }
        d = 0.04;                                   // 偏移量
        x = R * cos(i * PAI_D180) + 0.5;            // 计算x坐标
        y = R * sin(i * PAI_D180) + 0.5;            // 计算y坐标
        // 绘制点标志
        glBegin(GL_POINTS);
        x = x - d * cos(i * PAI_D180);
        y = y - d * sin(i * PAI_D180);
        glVertex2f(x, y);
        glEnd();
    }
    glLineWidth(1.0);                               // 设置线宽
    glEndList();                                    // 结束显示列表
}


/****************************************************************/
/* Function: 在指定位置输出文本                                   */
/****************************************************************/
void NClcok::PrintText(float x, float y, char* str) {
    int32 length = static_cast<int32>(strlen(str));              // 字符串长度
    glRasterPos2f(x, y);                                         // 定位当前光标
    for (int32 m = 0; m < length; ++m) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[m]);   // 用位图方式按指定的字体绘制一个字符串
    }
}


/****************************************************************/
/* Function: 绘制指北针                                          */
/****************************************************************/
void NClcok::DrawNorthPt() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);      // 以填充方式绘制
    glDisable(GL_TEXTURE_2D);                       // 关闭纹理
    float x1, y1, x2, y2, x3, y3;
    float mPtangle = 25;
    float tempangle;
    float L1, L2;
    L1 = 0.3;
    L2 = 0.2;
    x1 = 0.5;
    y1 = 0.5;                                // 时钟圆心点坐标，指北针围绕该点进行指向旋转
    x3 = x1 + L1 * cos((m_NorthPtangle) * PAI_D180);
    y3 = y1 + L1 * sin((m_NorthPtangle) * PAI_D180);
    // 如果指北针指向角位于第1象限
    if (m_NorthPtangle >= 0 && m_NorthPtangle <= 90) {
        tempangle = m_NorthPtangle - mPtangle;
        x2 = x1 - L2 * cos(tempangle * PAI_D180);
        y2 = y1 - L2 * sin(tempangle * PAI_D180);
        glColor3f(1.0, 1.0, 0.0);                       // 设置颜色
        glBegin(GL_TRIANGLES);                          // 绘制左侧三角形
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glEnd();
        glColor3f(1.0, 0.0, 0.0);                       // 设置颜色
        tempangle = m_NorthPtangle + mPtangle;
        x2 = x1 - L2 * cos(tempangle * PAI_D180);
        y2 = y1 - L2 * sin(tempangle * PAI_D180);
        glBegin(GL_TRIANGLES);                          // 绘制右侧三角形
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glEnd();
    }
    // 如果指北针指向角位于第2象限
    if (m_NorthPtangle > 90 && m_NorthPtangle <= 180) {
        tempangle = 180 - m_NorthPtangle - mPtangle;
        x2 = x1 + L2 * cos(tempangle * PAI_D180);
        y2 = y1 - L2 * sin(tempangle * PAI_D180);
        glColor3f(1.0, 1.0, 0.0);                   // 设置颜色
        glBegin(GL_TRIANGLES);                      // 绘制左侧三角形
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glEnd();
        glColor3f(1.0, 0.0, 0.0);                   // 设置颜色
        tempangle = 180 - m_NorthPtangle + mPtangle;
        x2 = x1 + L2 * cos(tempangle * PAI_D180);
        y2 = y1 - L2 * sin(tempangle * PAI_D180);
        glBegin(GL_TRIANGLES);                      // 绘制右侧三角形
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glEnd();
    }
    // 如果指北针指向角位于第3象限
    if (m_NorthPtangle > 180 && m_NorthPtangle <= 270) {
        tempangle = m_NorthPtangle - 180 - mPtangle;
        x2 = x1 + L2 * cos(tempangle * PAI_D180);
        y2 = y1 + L2 * sin(tempangle * PAI_D180);
        glColor3f(1.0, 1.0, 0.0);                   // 设置颜色
        glBegin(GL_TRIANGLES);                      // 绘制左侧三角形
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glEnd();
        glColor3f(1.0, 0.0, 0.0);                   // 设置颜色
        tempangle = m_NorthPtangle - 180 + mPtangle;
        x2 = x1 + L2 * cos(tempangle * PAI_D180);
        y2 = y1 + L2 * sin(tempangle * PAI_D180);
        glBegin(GL_TRIANGLES);                      // 绘制右侧三角形
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glEnd();
    }
    // 如果指北针指向角位于第4象限
    if (m_NorthPtangle > 270 && m_NorthPtangle <= 360) {
        tempangle = 360 - m_NorthPtangle - mPtangle;
        x2 = x1 - L2 * cos(tempangle * PAI_D180);
        y2 = y1 + L2 * sin(tempangle * PAI_D180);
        glColor3f(1.0, 1.0, 0.0);                   // 设置颜色
        glBegin(GL_TRIANGLES);                      // 绘制左侧三角形
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glEnd();
        glColor3f(1.0, 0.0, 0.0);                   // 设置颜色
        tempangle = 360 - m_NorthPtangle + mPtangle;
        x2 = x1 - L2 * cos(tempangle * PAI_D180);
        y2 = y1 + L2 * sin(tempangle * PAI_D180);
        glBegin(GL_TRIANGLES);                      // 绘制右侧三角形
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glEnd();
    }
    glColor3f(0.4, 0.47, 0.72);                     // 设置颜色
    glLineWidth(2.0);                               // 设置线宽
    glBegin(GL_LINES);                              // 指北针下短直线
    glVertex2f(x1, y1);
    x2 = x1 - 0.1 * cos((m_NorthPtangle) * PAI_D180);
    y2 = y1 - 0.1 * sin((m_NorthPtangle) * PAI_D180);
    glVertex2f(x2, y2);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_TEXTURE_2D);                        // 开启纹理
    glLineWidth(1.0);                               // 设置线宽
}





