﻿#include "stdafx.h"

#include "GLFont.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// uint32 Base;
//////////////////////////////////////////////////////////////////////

CGLFont::CGLFont() {
}

CGLFont::~CGLFont() {
}

void CGLFont::Entext(float x, float y, LPCTSTR str, HFONT hFont,
                     float r, float g, float b) {                  // 平面字符显示，不支持汉字
    HDC hdc = wglGetCurrentDC();                                    // 获取设置场景
    SelectObject(hdc, hFont);                                       // 设置字体
    uint32 Base = glGenLists(96);                             // 创建大小为96显示列表，存放字符位图
    wglUseFontBitmaps(hdc, 32, 96, Base);                           // 创建位图字体
    glDisable(GL_TEXTURE_2D);                                       // 不使用贴图
    glDisable(GL_LIGHTING);                                         // 不使用光照
    glPushAttrib(GL_LIST_BIT);                                      // 保存显示列表位属性
    glColor3f(r, g, b);                                             // 颜色
    glRasterPos2f(x / 100, y / 100);                                // 平面定位
    glListBase(Base - 32);                                      // 从显示列表开始
    glCallLists(strlen(str), GL_UNSIGNED_BYTE, str);            // 绘制显示列表
    glPopAttrib();                                                  // 恢复显示列表属性
    glEnable(GL_LIGHTING);                                          // 使用光照
    glEnable(GL_TEXTURE_2D);                                        // 使用纹理
    glDeleteLists(Base, 96);                                        // 删除显示列表
}

//////////////////////////////////////////////////////////////////
void CGLFont::C3dtext(LPCTSTR str, HFONT hFont, float z) {          // 3D文字显示。 支持汉字
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    Printfc3d("立体汉字", hFont, z);                                // 调用3D文字显示
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
}

void CGLFont::Printfc3d(CString strText, HFONT hFont, float z) {    // 主要原理是获取文字的轮廓线，用线和弧线将文字转化成3D对象
    HDC hdc = wglGetCurrentDC();                                    // 设备场景
    HFONT hOldFont = (HFONT)::SelectObject(hdc, hFont);             // 将字体选入场景，返回之前的字体
    UCHAR* pChar = (UCHAR*)strText.GetBuffer(strText.GetLength());  // 设置字符串长度
    int32   nListNum;                                                 // 定义列表变量
    DWORD dwChar;                                                   // 定义字符指针
    GLYPHMETRICSFLOAT pgmf[1];                                      // 轮廓字体字符集的信息
    glPushMatrix();                                                 // 压入堆栈
    for (int32 i = 0; i < strText.GetLength(); i++) {
        if (IsDBCSLeadByte((BYTE)pChar[i])) {                       // 是否双字节（汉字）
            dwChar = (DWORD)((pChar[i] << 8) | pChar[i + 1]);       // 取当前字符，双字节转换
            i++;
        } else {
            dwChar = pChar[i];                                      // 取当前字符
        }
        nListNum = glGenLists(1);                                   // 创建列表
        wglUseFontOutlines(hdc,                                  // 拥有字体的HDC
                           dwChar,                                   // 转化为显示列表的第一个字符
                           1,                                        // 转化为显示列表的字符数
                           nListNum,                                 // 显示列表的开始
                           0.0f,
                           z,                                        // Z轴负方向的厚度
                           WGL_FONT_POLYGONS,                        // 绘制字体的方式
                           pgmf                                      // 指向存放信息的数组，为count个
                          );
        glCallList(nListNum);                                       // 绘制显示列表
        glDeleteLists(nListNum, 1);                                 // 删除列表
    }
    glPopMatrix();                                                  // 弹出堆栈
    strText.ReleaseBuffer();                                        // 清除字符串
    ::SelectObject(hdc, hOldFont);                                  // 恢复字体
}

////////////////////////////////////////////////////////////////////////
void CGLFont:: Settext(float x, float y, CString str, HFONT Font, float r, float g, float b) {  // 平面汉字
    glLoadIdentity();
    glPushAttrib(GL_CURRENT_BIT);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glColor3f(r, g, b);
    glTranslatef(-(420 - x) / 800, (260 - y) / 600, -1.0f);       // 定位
    Printftext(0, 0, str, Font);                                  // OpenGL平面汉字
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glPopAttrib();
}

// 基本原理是在系统内部建立一个确定字体的设备场景（MDC），用GDI方式将文字在设备场景中形成单色位图
// 再用OpenGL的平面位图显示函数glBitmap将文字显示出来
void CGLFont:: Printftext(int32 x, int32 y, LPCTSTR lpszText, HFONT hFont) {
    CBitmap bitmap;                                                 // 设备相关位图变量
    BITMAP bm;                                                      // 位图结构变量
    SIZE size;                                                      // 位图尺寸
    HDC MDC = ::CreateCompatibleDC(0);                              // 暂存设备场景
    SelectObject(MDC, hFont);                                       // 选择新字体
    ::GetTextExtentPoint32(MDC, lpszText, strlen(lpszText), &size);  // 获取字符位图大小
    bitmap.CreateBitmap(size.cx, size.cy, 1, 1, NULL);              // 创建与MDC相关单色位图
    HBITMAP oldBmp = (HBITMAP)SelectObject(MDC, bitmap);            // 字符位图与MDC关连
    SetBkColor(MDC, RGB(0,     0,   0));                            // 底色 黑色
    SetTextColor(MDC, RGB(255, 255, 255));                          // 字色 白色
    TextOut(MDC, 0, 0, lpszText, strlen(lpszText));                 // 输出文字到暂存MDC
    bitmap.GetBitmap(&bm);                                          // 获得相关位图数据结构
    size.cx = (bm.bmWidth + 31) & (~31);                            // 边缘对齐
    int32 bufsize = size.cy * size.cx;                                // 图形数据长度
    struct {
        BITMAPINFOHEADER bih;
        RGBQUAD col[2];
    } bic;                                                          // 定义单色位图结构
    BITMAPINFO* binf = (BITMAPINFO*)&bic;                           // 获取位图结构信息
    binf->bmiHeader.biSize     = sizeof(binf->bmiHeader);           // 获取结构信息长度
    binf->bmiHeader.biWidth    = bm.bmWidth;
    binf->bmiHeader.biHeight   = bm.bmHeight;
    binf->bmiHeader.biPlanes   = 1;
    binf->bmiHeader.biBitCount = 1;                                 // 单色
    binf->bmiHeader.biCompression = BI_RGB;                         // 颜色方式
    binf->bmiHeader.biSizeImage   = bufsize;                        // 图形数据长度
    UCHAR* Bits = new UCHAR[bufsize];                               // 定义图形数据块变量
    ::GetDIBits(MDC, bitmap, 0, bm.bmHeight, Bits, binf, DIB_RGB_COLORS);  // 取设备无关数据到Bits
    glPixelStorei(GL_UNPACK_ALIGNMENT , 1);                         // 控制像素存储
    glRasterPos2i(x, y);                                            // 平面定位
    glBitmap(size.cx, size.cy, 0, 0, 0, 0, Bits);                   // 平面位图显示
    delete Bits;                                                    // 删除Bits
    SelectObject(MDC, oldBmp);                                      // 恢复位图特性
    ::DeleteDC(MDC);                                                // 删除设备场景
}