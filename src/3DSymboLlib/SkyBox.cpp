#include "stdafx.h"
#include "SkyBox.h"

SkyBox::SkyBox()
    : iSkyBoxLoaded_(false) {}

SkyBox::~SkyBox() {}

/********************************************************/
/* Function:生成天空                                     */
/********************************************************/
void SkyBox::CreateSkyBox() {
    glPushMatrix();
    int32 a = 3, wi = 3, he = 1, le = 3;
    float width = MAP * wi;
    float height = MAP * he;
    float length = MAP * le;
    int32 x0 = MAP - width / 2;
    int32 x1 = MAP + width / 2;
    int32 y0 = MAP / a - height / 3;
    int32 y1 = MAP / a + height / 3;
    int32 z0 = -MAP - length / 2;
    int32 z1 = -MAP + length / 2;
    // 设置BACK纹理参数
    glBindTexture(GL_TEXTURE_2D, g_texSkyBox[BK]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // 开始绘制
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x1, y0, z0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x1, y1, z0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x0, y1, z0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x0, y0, z0);
    glEnd();
    // 设置FRONT部分的纹理参数
    glBindTexture(GL_TEXTURE_2D, g_texSkyBox[FR]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // 开始绘制
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x0, y0, z1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x0, y1, z1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x1, y1, z1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x1, y0, z1);
    glEnd();
    // 设置TOP部分的纹理参数
    glBindTexture(GL_TEXTURE_2D, g_texSkyBox[TP]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // 开始绘制
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x0, y1, z1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x0, y1, z0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x1, y1, z0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x1, y1, z1);
    glEnd();
    // 设置LEFT部分的纹理参数
    glBindTexture(GL_TEXTURE_2D, g_texSkyBox[LF]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // 开始绘制
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x0, y1, z0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x0, y1, z1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x0, y0, z1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x0, y0, z0);
    glEnd();
    // 设置RIGHT部分的纹理参数
    glBindTexture(GL_TEXTURE_2D, g_texSkyBox[RT]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // 开始绘制
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x1, y0, z0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x1, y0, z1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x1, y1, z1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x1, y1, z0);
    glEnd();
    glPopMatrix();
}