#include "stdafx.h"
#include "SimpleLine.h"


SimpleLine::SimpleLine() {
}

SimpleLine::~SimpleLine() {
}


// 空间点求投影到平面的直线方程系数ABC, Ax+By+C=0
void SimpleLine::getLine2ABC(float* A, float* B, float* C, Point3 p1, Point3 p2) {
    // 直线AX+BY+C=0的一般式方程就是：
    //  A = Y2 - Y1
    //  B = X1 - X2
    //  C = X2*Y1 - X1*Y2
    *A = p2.z - p1.z;
    *B = p1.x - p2.x;
    *C = p2.x * p1.z - p1.x * p2.z;
}

// 计算平面交点坐标,并计算出交点出的高程值
void SimpleLine::CalcuateJD(int32 rowNum, int32 row_index_begin, int32 row_index_end,
                            int32 colNum, int32 col_index_begin, int32 col_index_end, Line3 _line, vector<Point3>& _pv,
                            float (*g_terrain)[3]) {  // NOLINT
    // 直线方程系数ABC, Ax+By+C=0
    float A, B, C;
    getLine2ABC(&A, &B, &C, _line.pt1, _line.pt2);
    Point3 tmp_point;
    JD_vector1.clear();
    JD_vector2.clear();
    JD_vector3.clear();
    _pv.clear();
    // 交点1 ---------------------------------------------------------------------
    // 通过格网横坐标 求与线段交点
    if (row_index_begin < row_index_end) {
        for (int32 r = row_index_begin + 1; r < row_index_end; ++r) {
            tmp_point.x = static_cast<float>(r) * MAP_SCALE;  // 平面横坐标
            // 平面纵坐标
            if (MATH_FLOAT_EQUAL_0(B)) {
                break;
            } else {
                tmp_point.z = ((-A) * tmp_point.x - C) / B;
            }
            tmp_point.y = Global::GetHeight(tmp_point.x, tmp_point.z, g_terrain);
            JD_vector1.push_back(tmp_point);
        }
    } else if (row_index_begin > row_index_end) {
        for (int32 r = row_index_begin - 1; r > row_index_end; --r) {
            tmp_point.x = static_cast<float>(r) * MAP_SCALE;  // 平面横坐标
            // 平面纵坐标
            if (MATH_FLOAT_EQUAL_0(B)) {
                break;
            } else {
                tmp_point.z = ((-A) * tmp_point.x - C) / B;
            }
            tmp_point.y = Global::GetHeight(tmp_point.x, tmp_point.z, g_terrain);
            JD_vector1.push_back(tmp_point);
        }
    }
    // 交点2 ---------------------------------------------------------------------
    if (col_index_begin < col_index_end) {
        // 通过格网纵坐标 求与线段交点
        for (int32 c = col_index_begin + 1; c < col_index_end; ++c) {
            tmp_point.z = static_cast<float>(-c) * MAP_SCALE;  // 平面纵坐标
            // 平面横坐标
            if (MATH_FLOAT_EQUAL_0(A)) {
                break;
            } else {
                // Ax+By+C=0
                tmp_point.x = ((-B) * tmp_point.z - C) / A;
            }
            tmp_point.y = Global::GetHeight(tmp_point.x, tmp_point.z, g_terrain);
            JD_vector2.push_back(tmp_point);
        }
    } else if (col_index_begin > col_index_end) {
        // 通过格网纵坐标 求与线段交点
        for (int32 c = col_index_begin - 1; c > col_index_end; --c) {
            tmp_point.z = static_cast<float>(-c) * MAP_SCALE;  // 平面纵坐标
            // 平面横坐标
            if (MATH_FLOAT_EQUAL_0(A)) {
                break;
            } else {
                // Ax+By+C=0
                tmp_point.x = ((-B) * tmp_point.z - C) / A;
            }
            tmp_point.y = Global::GetHeight(tmp_point.x, tmp_point.z, g_terrain);
            JD_vector2.push_back(tmp_point);
        }
    }
    // 交点3 ---------------------------------------------------------------------
    // double line_pos_b = MAP_SCALE * (row_index_begin < row_index_end ? row_index_begin : row_index_end);
    // double line_pos_e = MAP_SCALE * (row_index_begin > row_index_end ? row_index_begin : row_index_end);
    float line_pos_b = MATH_MIN(_line.pt1.x, _line.pt2.x);
    float line_pos_e = MATH_MAX(_line.pt1.x, _line.pt2.x);
    for (int32 r = 0; r < MAP_W; ++r) {
        double b = static_cast<float>(-r) * MAP_SCALE;
        if (GetJDFrom2Line(&tmp_point, b, A, B, C, g_terrain)) {
            if ((line_pos_b < tmp_point.x) && (tmp_point.x < line_pos_e)) {
                JD_vector3.push_back(tmp_point);
            }
        }
    }
    // 2端点
    _pv.push_back(_line.pt1);
    _pv.push_back(_line.pt2);
    //----------------------------------------------
    for (uint32 i = 0; i < JD_vector1.size(); ++i) {
        _pv.push_back(JD_vector1[i]);
    }
    for (uint32 i = 0; i < JD_vector2.size(); ++i) {
        _pv.push_back(JD_vector2[i]);
    }
    // 斜线交点
    for (uint32 i = 0; i < JD_vector3.size(); ++i) {
        _pv.push_back(JD_vector3[i]);
    }
    sort(_pv.begin(), _pv.end(), [](const Point3 & p1, const Point3 & p2)->bool {return p1.x < p2.x;}); // NOLINT
}

// 计算2条直线的交点y=x+b, Ax+By+C=0, 返回0表示无交点
BOOL SimpleLine::GetJDFrom2Line(Point3* p/*out*/, double b, double A, double B, double C, float (*g_terrain)[3]) {
    if (MATH_FLOAT_EQUAL_0(A)) {  // A == 0
        p->z = -C / B;
        p->x = p->z - b;
        p->y = Global::GetHeight(p->x, p->z, g_terrain);
    } else {
        if (!(MATH_FLOAT_EQUAL_0(B))) {
            if (MATH_FLOAT_EQUAL_0(-A / B - 1)) {
                return 0;  // 2直线平行无交点
            } else {
                p->x = (-1) * (B * b + C) / (A + B);
                p->z = p->x + b;
                p->y = Global::GetHeight(p->x, p->z, g_terrain);
            }
        } else {  // B == 0
            p->x = -C / A;
            p->z = p->x + b;
            p->y = Global::GetHeight(p->x, p->z, g_terrain);
        }
    }
    return 1;
}



// 计算线段_line所经过的横向和纵向格网数, 及索引范围
void SimpleLine::CalcuateGridNum(int32* rowNum, int32* row_index_begin, int32* row_index_end,
                                 int32* colNum, int32* col_index_begin, int32* col_index_end, Line3 _line) {
    int32 tmp_rowNum = 0;
    int32 tmp_row_index_begin = 0;
    int32 tmp_row_index_end = 0;
    int32 tmp_colNum = 0;
    int32 tmp_col_index_begin = 0;
    int32 tmp_col_index_end = 0;
    double r1 = abs(_line.pt1.x);
    double c1 = abs(_line.pt1.z);
    double r2 = abs(_line.pt2.x);
    double c2 = abs(_line.pt2.z);
    tmp_row_index_begin = static_cast<int32>(r1) / static_cast<int32>(MAP_SCALE);
    tmp_row_index_end = static_cast<int32>(r2) / static_cast<int32>(MAP_SCALE);
    tmp_col_index_begin = static_cast<int32>(c1) / static_cast<int32>(MAP_SCALE);
    tmp_col_index_end = static_cast<int32>(c2) / static_cast<int32>(MAP_SCALE);
    *rowNum = abs(tmp_row_index_end - tmp_row_index_begin);
    *row_index_begin = tmp_row_index_begin;
    *row_index_end = tmp_row_index_end;
    *colNum = abs(tmp_col_index_end - tmp_col_index_begin);
    *col_index_begin = tmp_col_index_begin;
    *col_index_end = tmp_col_index_end;
}



// 线编辑 ==》融合   线矢量与地表三角网融合
void SimpleLine::OnLineFuse(const CArray<PLine3, PLine3>& m_LinesArray, float (*g_terrain)[3]) {
    // TODO(jason): 在此添加命令处理程序代码
    int32 tmp_rowNum = 0;
    int32 tmp_row_index_begin = 0;
    int32 tmp_row_index_end = 0;
    int32 tmp_colNum = 0;
    int32 tmp_col_index_begin = 0;
    int32 tmp_col_index_end = 0;
    Line3 tmp_line;
    tmp_line.pt1 = m_LinesArray[0]->pt1;
    tmp_line.pt2 = m_LinesArray[0]->pt2;
    // 1
    tmp_line.pt1 = m_LinesArray[0]->pt1;
    tmp_line.pt2 = m_LinesArray[0]->pt2;
    // if(abs(tmp_line.pt1._x - tmp_line.pt2._x) < MAP_SCALE)
    {
        tmp_line.pt1.x -= 1;
        tmp_line.pt2.x -= 1;
    }
    // else
    // {
    //   tmp_line.pt1._z += 5;
    //   tmp_line.pt2._z += 5;
    // }
    CalcuateGridNum(&tmp_rowNum, &tmp_row_index_begin, &tmp_row_index_end,
                    &tmp_colNum, &tmp_col_index_begin, &tmp_col_index_end, tmp_line);
    CalcuateJD(tmp_rowNum, tmp_row_index_begin, tmp_row_index_end,
               tmp_colNum, tmp_col_index_begin, tmp_col_index_end, tmp_line, Line_a_JD_vector, g_terrain);
    tmp_line.pt1 = m_LinesArray[0]->pt1;
    tmp_line.pt2 = m_LinesArray[0]->pt2;
    // if(abs(tmp_line.pt1._x - tmp_line.pt2._x) < MAP_SCALE)
    {
        tmp_line.pt1.x += 1;
        tmp_line.pt2.x += 1;
    }
    /*else
    {
        tmp_line.pt1._z -= 5;
        tmp_line.pt2._z -= 5;
    }*/
    CalcuateGridNum(&tmp_rowNum, &tmp_row_index_begin, &tmp_row_index_end,
                    &tmp_colNum, &tmp_col_index_begin, &tmp_col_index_end, tmp_line);
    CalcuateJD(tmp_rowNum, tmp_row_index_begin, tmp_row_index_end,
               tmp_colNum, tmp_col_index_begin, tmp_col_index_end, tmp_line, Line_b_JD_vector, g_terrain);
    fuse_Flag = TRUE;
}


bool LoadT8(char* filename, GLuint& texture) {  // NOLINT
    AUX_RGBImageRec* pImage = NULL;
    pImage = auxDIBImageLoad(filename);         // 装入位图
    if (pImage == NULL)  return false;          // 位图没装入，返回错误
    glGenTextures(1, &texture);                 // 生成贴图（纹理）
    glBindTexture(GL_TEXTURE_2D, texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4,
                      pImage->sizeX,
                      pImage->sizeY,
                      GL_RGB, GL_UNSIGNED_BYTE,
                      pImage->data
                     );
    free(pImage->data);                         // 释放位图数据占据的内存资源
    free(pImage);
    return true;
}

// 绘制交点连线
void SimpleLine::DrawJDLine(const vector<Point3>& _pv1, const vector<Point3>& _pv2) {
    double DD = 1.0f;
    double tmpMinX = 0.0, tmpMinY = 0.0, tmpMaxX = 0.0, tmpMaxY = 0.0, tmpU = 0.0, tmpV = 0.0;
    GetMinXY(_pv1, _pv2, &tmpMinX, &tmpMinY, &tmpMaxX, &tmpMaxY);
    // 配置地形
    // double tmpX = 0.0, tmpY = 0.0, tmpZ = 0.0;
    Point3 tmpPoint;
    // 三角网
    glEnable(GL_TEXTURE_2D);    // 开启纹理
    // glBindTexture(GL_TEXTURE_2D, m_cTxtureRailway.GetTxtID());
    GLuint rd;
    char cc[256] = "E:/VS2012_Project/CGBak/LatestVersion/DataFormated/RoadTexture/铁路/way5.bmp";
    LoadT8(cc,  rd);
    glBindTexture(GL_TEXTURE_2D, rd);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    if (fuse_Flag == TRUE) {
        glPushAttrib(GL_CURRENT_BIT);  // 保存现有颜色属性
        glPushMatrix();             // 压入矩阵堆栈
        glLineWidth(2.0);           // 设置线宽
        glColor3f(0, 0.5, 1);       // 设置颜色
        glBegin(GL_TRIANGLE_STRIP);
        for (uint32 i = 0, j = 0, k = 0; i < _pv1.size(), j < _pv2.size(); ++i, ++j, ++k) {
            if (k % 2 == 0) {
                tmpPoint = Point3(_pv1[i].x, _pv1[i].y + DD, _pv1[i].z);
            } else {
                tmpPoint = Point3(_pv2[j].x, _pv2[j].y + DD, _pv2[j].z);
            }
            tmpMinX = 0.0, tmpMinY = 0.0, tmpMaxX = 10.0, tmpMaxY = 10.0;
            GetUV(tmpPoint.x, tmpPoint.z, tmpMinX, tmpMinY, tmpMaxX, tmpMaxY, &tmpU, &tmpV);
            glTexCoord2f(tmpU, tmpV);
            glVertex3f(tmpPoint.x, tmpPoint.y, tmpPoint.z);
        }
        glEnd();
        glLineWidth(1.0);           // 恢复线宽
        glPopAttrib();
        glPopMatrix();              // 弹出矩阵堆栈
    }
}


// 所有三角形顶点坐标最小最大值
void SimpleLine::GetMinXY(const vector<Point3>& _pv1,  const vector<Point3>& _pv2, double* _minX, double* _minY, double* _maxX, double* _maxY) {
    vector<Point3> tmpPV;
    uint32 i = 0;
    for (i = 0; i < _pv1.size(); ++i) {
        tmpPV.push_back(_pv1[i]);
    }
    for (i = 0; i < _pv2.size(); ++i) {
        tmpPV.push_back(_pv2[i]);
    }
    sort(tmpPV.begin(), tmpPV.end(), [](const Point3 & p1, const Point3 & p2)->bool {return p1.x < p2.x;}); // NOLINT
    *_minX = abs(tmpPV[0].x);
    *_maxX = abs(tmpPV[tmpPV.size() - 1].x);
    sort(tmpPV.begin(), tmpPV.end(), [](const Point3 & p1, const Point3 & p2)->bool {return p1.z < p2.z;}); // NOLINT
    *_maxY = abs(tmpPV[0].z);
    *_minY = abs(tmpPV[tmpPV.size() - 1].z);
}

// 线符号纹理坐标
void SimpleLine::GetUV(double _x, double _y, double _minX, double _minY, double _maxX, double _maxY, double* _u, double* _v) {
    *_u = (abs(_x) - _minX) / (_maxX - _minX);
    *_v = (abs(_y) - _minY) / (_maxY - _minY);
}



