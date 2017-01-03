﻿#include "stdafx.h"
#include "L2DRoad.h"


L2DRoad::L2DRoad() {
}
L2DRoad::~L2DRoad() {
}


// 根据线段的2个端点, 获取增加宽度后的矩形的4个顶点
float L2DRoad::GetArea4FromLine(const Point3& p1, const Point3& p2, const float& line_width, Area_4* pArea4/*output*/, float (*g_terrain)[3]) {
    float k = 0.0f;  //直线p1p2斜率  
    // 线段与x轴垂直
    if (MATH_FLOAT_EQUAL(p1.x, p2.x)) {
        pArea4->pt1.x = p1.x - line_width / 2;
        pArea4->pt1.z = p1.z;
        pArea4->pt1.y = GetHeight(pArea4->pt1.x, pArea4->pt1.z, g_terrain);
        //
        pArea4->pt2.x = p1.x + line_width / 2;
        pArea4->pt2.z = p1.z;
        pArea4->pt2.y = GetHeight(pArea4->pt2.x, pArea4->pt2.z, g_terrain);
        //
        pArea4->pt3.x = p2.x + line_width / 2;
        pArea4->pt3.z = p2.z;
        pArea4->pt3.y = GetHeight(pArea4->pt3.x, pArea4->pt3.z, g_terrain);
        //
        pArea4->pt4.x = p2.x - line_width / 2;
        pArea4->pt4.z = p2.z;
        pArea4->pt4.y = GetHeight(pArea4->pt4.x, pArea4->pt4.z, g_terrain);

        k = 10000.0f;
    } else if (MATH_FLOAT_EQUAL(p1.z, p2.z)) {  // 线段与y轴垂直
        pArea4->pt1.x = p1.x;
        pArea4->pt1.z = p1.z + line_width / 2;
        pArea4->pt1.y = GetHeight(pArea4->pt1.x, pArea4->pt1.z, g_terrain);
        //
        pArea4->pt2.x = p2.x;
        pArea4->pt2.z = p2.z + line_width / 2;
        pArea4->pt2.y = GetHeight(pArea4->pt2.x, pArea4->pt2.z, g_terrain);
        //
        pArea4->pt3.x = p2.x;
        pArea4->pt3.z = p2.z - line_width / 2;
        pArea4->pt3.y = GetHeight(pArea4->pt3.x, pArea4->pt3.z, g_terrain);
        //
        pArea4->pt4.x = p1.x;
        pArea4->pt4.z = p1.z - line_width / 2;
        pArea4->pt4.y = GetHeight(pArea4->pt4.x, pArea4->pt4.z, g_terrain);

        k = 0.0f;
    } else {
        // 求k
        float k = (p1.z - p2.z) / (p1.x - p2.x);
        float deltaX = sin(atan(k)) * line_width / 2;
        float deltaY = cos(atan(k)) * line_width / 2;
        pArea4->pt1.x = p1.x - deltaX;
        pArea4->pt1.z = p1.z + deltaY;
        pArea4->pt1.y = GetHeight(pArea4->pt1.x, pArea4->pt1.z, g_terrain);
        //
        pArea4->pt2.x = p1.x + deltaX;
        pArea4->pt2.z = p1.z - deltaY;
        pArea4->pt2.y = GetHeight(pArea4->pt2.x, pArea4->pt2.z, g_terrain);
        //
        pArea4->pt3.x = p2.x + deltaX;
        pArea4->pt3.z = p2.z - deltaY;
        pArea4->pt3.y = GetHeight(pArea4->pt3.x, pArea4->pt3.z, g_terrain);
        //
        pArea4->pt4.x = p2.x - deltaX;
        pArea4->pt4.z = p2.z + deltaY;
        pArea4->pt4.y = GetHeight(pArea4->pt4.x, pArea4->pt4.z, g_terrain);
    }
    return k;
}



// Function: 获取地面高度
float L2DRoad::GetHeight(float x, float z, float (*g_terrain)[3]) {
    float CameraX = x / MAP_SCALE;                  // 计算在哪一列
    float CameraZ = -z / MAP_SCALE;                 // 计算在哪一行
    int32 Col0 = static_cast<int32>(CameraX);       // 块的列号
    int32 Row0 = static_cast<int32>(CameraZ);       // 块的行号
    int32 Col1 = Col0 + 1;                          // 相邻列
    int32 Row1 = Row0 + 1;                          // 相邻块
    if (Col1 > MAP_W)   Col1 = 0;                   // 相邻列大于地块数，取首列
    if (Row1 > MAP_W)   Row1 = 0;                   // 相邻行大于地块数，取首行
    float h00 = g_terrain[Col0 + Row0 * MAP_W][1];  // 获取块四角的高度
    float h01 = g_terrain[Col1 + Row0 * MAP_W][1];
    float h11 = g_terrain[Col1 + Row1 * MAP_W][1];
    float h10 = g_terrain[Col0 + Row1 * MAP_W][1];
    float tx = CameraX - static_cast<int32>(CameraX);              // 求块内X偏移位置
    float ty = CameraZ - static_cast<int32>(CameraZ);              // 求块内Z偏移位置
    float txty = tx * ty;                           // 以下为双线性插值（内插）计算
    // 返回插值计算值，为所求点的高度
    return h00 * (1.0f - ty - tx + txty) + h01 * (tx - txty) + h11 * txty + h10 * (ty - txty);
}


// 保存线符号，并且增加宽度变成多边形(等分每个线段外接矩形)
void L2DRoad::SaveLineSymbol(LineSymbol* pLineSymbol_, float (*g_terrain)[3]) {
    // 将刚才创建的线符号保存
    int32 line_count = allLineSymbols_.size();
    if (nullptr != pLineSymbol_ && pLineSymbol_->line_type_ != 0) {
        allLineSymbols_.insert(std::unordered_map<int32, LineSymbol>::value_type(line_count++, *pLineSymbol_));
    } else {
        return;
    }
    // LOGGER_INFO << "==============> allLineSymbols_.size() = " << allLineSymbols_.size();
    for (auto iter = allLineSymbols_.begin(); iter != allLineSymbols_.end(); ++iter) {
        LineSymbol pLs = iter->second;
        vector<Vec3> lp = pLs.line_points_;
        // LOGGER_INFO << "lp.size() = " << lp.size();
        if (!lp.empty()) {
            int32 key_line_index = iter->first;
            std::shared_ptr<CArray<PArea_4, PArea_4>> m_Line_Area4_Array_ = std::make_shared<CArray<PArea_4, PArea_4>>();  // 存放一条线中所有的面符号(线符号增加宽度后形成的面)
            

            // 存放一条线中所有的面符号(等分之后的)
            std::shared_ptr<CArray<PArea_4, PArea_4>> m_Line_XiFen_Area4_Array = std::make_shared<CArray<PArea_4, PArea_4>>();
            vector<vector<Area_4>> allBigAreaContainsSmallAreaVector;
            // 等分每个矩形块
            vector<Area_4> BigArea4Vector;

            // 对线符号按矩形分块
            int32 point_count = lp.size();
            if (point_count >= 2) {
                for (int32 i = 0; i < point_count - 1; ++i) {
                    Area_4* pArea4 = new Area_4;
                    Point3 p1 = Point3(lp.at(i).x, lp.at(i).y, lp.at(i).z);
                    Point3 p2 = Point3(lp.at(i + 1).x, lp.at(i + 1).y, lp.at(i + 1).z);
                    float k = GetArea4FromLine(p1, p2, pLs.line_width_, pArea4, g_terrain);
                    CString tmpTextureStr;
                    tmpTextureStr.Format("%s", pLs.line_texture_.c_str());
                    pArea4->area_texture = tmpTextureStr;
                    pArea4->deleted = 0;
                    m_Line_Area4_Array_->Add(pArea4);

                    
                    float distance_p1p2 = distance_xz(p1, p2);
                    int32 n = static_cast<int32>(distance_p1p2 / pLs.line_width_);

                    for (auto i=0; i<=n-1; ++i) {
                        Point3 tmpPoint_begin;
                        tmpPoint_begin.x = p1.x + i * (p2.x-p1.x) / n;
                        tmpPoint_begin.z = p1.z + i * (p2.z-p1.z) / n;
                        tmpPoint_begin.y = GetHeight(tmpPoint_begin.x, tmpPoint_begin.z, g_terrain);
                        //
                        Point3 tmpPoint_end;
                        tmpPoint_end.x = p1.x + (i+1) * (p2.x-p1.x) / n;
                        tmpPoint_end.z = p1.z + (i+1) * (p2.z-p1.z) / n;
                        tmpPoint_end.y = GetHeight(tmpPoint_end.x, tmpPoint_end.z, g_terrain);
                        // 
                        Area_4 smallArea4;
                        GetArea4FromLine(tmpPoint_begin, tmpPoint_end, pLs.line_width_, &smallArea4, g_terrain);
                        CString tmpTextureStr;
                        tmpTextureStr.Format("%s", pLs.line_texture_.c_str());
                        smallArea4.area_texture = tmpTextureStr;
                        smallArea4.deleted = 0;
                        BigArea4Vector.push_back(smallArea4);
                    }
                    
                    allBigAreaContainsSmallAreaVector.push_back(BigArea4Vector);
                    BigArea4Vector.clear();
                }
            }
            // 线路拐点，矩形相交 ==> 梯形

            std::shared_ptr<CArray<PArea_4, PArea_4>> pLine_Area4_Array_After_XiangJiao = std::make_shared<CArray<PArea_4, PArea_4>>();  // 存放一条线中所有的面符号(线符号增加宽度后形成的面)
            if (m_Line_Area4_Array_->GetSize() >= 2) {  // 至少2个矩形，相交
                CPointPolygonRelationship tmpCPR;
                LineSegment tmpLineSegment_A1;
                LineSegment tmpLineSegment_A2;
                LineSegment tmpLineSegment_B1;
                LineSegment tmpLineSegment_B2;
                for (int32 i = 0; i < m_Line_Area4_Array_->GetSize() - 1; ++i) {
                    // -----------------
                    auto size_a = allBigAreaContainsSmallAreaVector.at(i).size();
                    Area_4& pTmpArea4_A = allBigAreaContainsSmallAreaVector.at(i).at(size_a-1);

                    // -----------------
                    tmpLineSegment_A1.pt1 = PPR_Point(pTmpArea4_A.pt1.x, pTmpArea4_A.pt1.z);
                    tmpLineSegment_A1.pt2 = PPR_Point(pTmpArea4_A.pt4.x, pTmpArea4_A.pt4.z);
                    tmpLineSegment_A2.pt1 = PPR_Point(pTmpArea4_A.pt2.x, pTmpArea4_A.pt2.z);
                    tmpLineSegment_A2.pt2 = PPR_Point(pTmpArea4_A.pt3.x, pTmpArea4_A.pt3.z);
                    // ----------------------------------------------------------
                    Area_4& pTmpArea4_B = allBigAreaContainsSmallAreaVector.at(i+1).at(0);

                    tmpLineSegment_B1.pt1 = PPR_Point(pTmpArea4_B.pt1.x, pTmpArea4_B.pt1.z);
                    tmpLineSegment_B1.pt2 = PPR_Point(pTmpArea4_B.pt4.x, pTmpArea4_B.pt4.z);
                    tmpLineSegment_B2.pt1 = PPR_Point(pTmpArea4_B.pt2.x, pTmpArea4_B.pt2.z);
                    tmpLineSegment_B2.pt2 = PPR_Point(pTmpArea4_B.pt3.x, pTmpArea4_B.pt3.z);
                    //
                    bool xj_1 = tmpCPR.Intersect(tmpLineSegment_A1, tmpLineSegment_B1);
                    bool xj_2 = tmpCPR.Intersect(tmpLineSegment_A2, tmpLineSegment_B2);
                    LOGGER_INFO << "xiangjiao 1? = " << tmpCPR.Intersect(tmpLineSegment_A1, tmpLineSegment_B1);
                    LOGGER_INFO << "xiangjiao 2? = " << tmpCPR.Intersect(tmpLineSegment_A2, tmpLineSegment_B2);
                    if (xj_1 || xj_2) {
                        if (xj_1) {
                            PPR_Point JD1 = tmpCPR.getJD(tmpLineSegment_A1.pt1, tmpLineSegment_A1.pt2, tmpLineSegment_B1.pt1, tmpLineSegment_B1.pt2);
                            LOGGER_INFO << "JD1 = " << JD1.x << ", " << JD1.y;
                            float a1 = 0.0f, b1 = 0.0f, c1 = 0.0f;
                            a1 = tmpLineSegment_A2.pt2.y - tmpLineSegment_A2.pt1.y;
                            b1 = tmpLineSegment_A2.pt1.x - tmpLineSegment_A2.pt2.x;
                            c1 = tmpLineSegment_A2.pt2.x * tmpLineSegment_A2.pt1.y - tmpLineSegment_A2.pt1.x * tmpLineSegment_A2.pt2.y;
                            float a2 = 0.0f, b2 = 0.0f, c2 = 0.0f;
                            a2 = tmpLineSegment_B2.pt2.y - tmpLineSegment_B2.pt1.y;
                            b2 = tmpLineSegment_B2.pt1.x - tmpLineSegment_B2.pt2.x;
                            c2 = tmpLineSegment_B2.pt2.x * tmpLineSegment_B2.pt1.y - tmpLineSegment_B2.pt1.x * tmpLineSegment_B2.pt2.y;
                            PPR_Point JD2;
                            if (MATH_FLOAT_EQUAL_0(a1 * b2 - a2 * b1)) {
                                AfxMessageBox("MATH_FLOAT_EQUAL_0(a1*b2 - a2*b1)...");
                            } else {
                                JD2.x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
                                JD2.y = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1);
                            }
                            LOGGER_INFO << ".....JD2 = " << JD2.x << ", " << JD2.y;
                            // 矩形 ==> 梯形, 修改原来四边形的坐标
                            pTmpArea4_A.pt4.x = JD1.x;
                            pTmpArea4_A.pt4.z = JD1.y;
                            pTmpArea4_A.pt4.y = GetHeight(pTmpArea4_A.pt4.x, pTmpArea4_A.pt4.z, g_terrain);
                            pTmpArea4_A.pt3.x = JD2.x;
                            pTmpArea4_A.pt3.z = JD2.y;
                            pTmpArea4_A.pt3.y = GetHeight(pTmpArea4_A.pt4.x, pTmpArea4_A.pt4.z, g_terrain);
                            pTmpArea4_B.pt1.x = JD1.x;
                            pTmpArea4_B.pt1.z = JD1.y;
                            pTmpArea4_B.pt1.y = GetHeight(pTmpArea4_B.pt1.x, pTmpArea4_B.pt1.z, g_terrain);
                            pTmpArea4_B.pt2.x = JD2.x;
                            pTmpArea4_B.pt2.z = JD2.y;
                            pTmpArea4_B.pt2.y = GetHeight(pTmpArea4_B.pt2.x, pTmpArea4_B.pt2.z, g_terrain);
                        } else {
                            PPR_Point JD2 = tmpCPR.getJD(tmpLineSegment_A2.pt1, tmpLineSegment_A2.pt2, tmpLineSegment_B2.pt1, tmpLineSegment_B2.pt2);
                            LOGGER_INFO << "JD2 = " << JD2.x << ", " << JD2.y;
                            float a1 = 0.0f, b1 = 0.0f, c1 = 0.0f;
                            a1 = tmpLineSegment_A1.pt2.y - tmpLineSegment_A1.pt1.y;
                            b1 = tmpLineSegment_A1.pt1.x - tmpLineSegment_A1.pt2.x;
                            c1 = tmpLineSegment_A1.pt2.x * tmpLineSegment_A1.pt1.y - tmpLineSegment_A1.pt1.x * tmpLineSegment_A1.pt2.y;
                            float a2 = 0.0f, b2 = 0.0f, c2 = 0.0f;
                            a2 = tmpLineSegment_B1.pt2.y - tmpLineSegment_B1.pt1.y;
                            b2 = tmpLineSegment_B1.pt1.x - tmpLineSegment_B1.pt2.x;
                            c2 = tmpLineSegment_B1.pt2.x * tmpLineSegment_B1.pt1.y - tmpLineSegment_B1.pt1.x * tmpLineSegment_B1.pt2.y;
                            PPR_Point JD1;
                            if (MATH_FLOAT_EQUAL_0(a1 * b2 - a2 * b1)) {
                                AfxMessageBox("MATH_FLOAT_EQUAL_0(a1*b2 - a2*b1)...");
                            } else {
                                JD1.x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
                                JD1.y = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1);
                            }
                            LOGGER_INFO << "...JD1 = " << JD1.x << ", " << JD1.y;
                            pTmpArea4_A.pt4.x = JD1.x;
                            pTmpArea4_A.pt4.z = JD1.y;
                            pTmpArea4_A.pt4.y = GetHeight(pTmpArea4_A.pt4.x, pTmpArea4_A.pt4.z, g_terrain);
                            pTmpArea4_A.pt3.x = JD2.x;
                            pTmpArea4_A.pt3.z = JD2.y;
                            pTmpArea4_A.pt3.y = GetHeight(pTmpArea4_A.pt4.x, pTmpArea4_A.pt4.z, g_terrain);
                            pTmpArea4_B.pt1.x = JD1.x;
                            pTmpArea4_B.pt1.z = JD1.y;
                            pTmpArea4_B.pt1.y = GetHeight(pTmpArea4_B.pt1.x, pTmpArea4_B.pt1.z, g_terrain);
                            pTmpArea4_B.pt2.x = JD2.x;
                            pTmpArea4_B.pt2.z = JD2.y;
                            pTmpArea4_B.pt2.y = GetHeight(pTmpArea4_B.pt2.x, pTmpArea4_B.pt2.z, g_terrain);
                        }
                    }
                }
            }


            for (auto i=0; i< m_Line_Area4_Array_->GetSize(); ++i) {
                auto tmpSize = allBigAreaContainsSmallAreaVector.at(i).size();
                for (decltype(tmpSize) j=0; j < tmpSize; ++j) {
                    Area_4* pArea4 = new Area_4;
                    CString tmpTextureStr;
                    tmpTextureStr.Format("%s", pLs.line_texture_.c_str());
                    pArea4->area_texture = tmpTextureStr;
                    pArea4->deleted = 0;

                    auto tmpVector = allBigAreaContainsSmallAreaVector.at(i);
                    pArea4->pt1 = tmpVector.at(j).pt1;
                    pArea4->pt2 = tmpVector.at(j).pt2;
                    pArea4->pt3 = tmpVector.at(j).pt3;
                    pArea4->pt4 = tmpVector.at(j).pt4;

                    m_Line_XiFen_Area4_Array->Add(pArea4);
                }
            }

            LOGGER_INFO << "----------------------------------";

            auto size1 = m_Line_Area4_Array_->GetSize();

            //if (size1 >= 2) {

            //    {
            //        Area_4* pArea4 = new Area_4;
            //        CString tmpTextureStr;
            //        tmpTextureStr.Format("%s", pLs.line_texture_.c_str());
            //        pArea4->area_texture = tmpTextureStr;
            //        pArea4->deleted = 0;

            //        auto size2 = allBigAreaContainsSmallAreaVector.at(0).size();
            //        auto tmpVector = allBigAreaContainsSmallAreaVector.at(0).at(size2-1);
            //        pArea4->pt1 = tmpVector.pt1;
            //        pArea4->pt2 = tmpVector.pt2;
            //        pArea4->pt3 = tmpVector.pt3;
            //        pArea4->pt4 = tmpVector.pt4;


            //        m_Line_XiFen_Area4_Array->Add(pArea4);
            //    }
            //    
            //    {
            //        Area_4* pArea4 = new Area_4;
            //        CString tmpTextureStr;
            //        tmpTextureStr.Format("%s", pLs.line_texture_.c_str());
            //        pArea4->area_texture = tmpTextureStr;
            //        pArea4->deleted = 0;
            //        auto tmpVector2 = allBigAreaContainsSmallAreaVector.at(1).at(0);
            //        pArea4->pt1 = tmpVector2.pt1;
            //        pArea4->pt2 = tmpVector2.pt2;
            //        pArea4->pt3 = tmpVector2.pt3;
            //        pArea4->pt4 = tmpVector2.pt4;

            //        m_Line_XiFen_Area4_Array->Add(pArea4);

            //    }

                
            //}



            allLineArea4Array_.insert(std::unordered_map<int32, std::shared_ptr<CArray<PArea_4, PArea_4>>>::value_type(key_line_index, m_Line_XiFen_Area4_Array));

            
           // allLineArea4Array_.insert(std::unordered_map<int32, std::shared_ptr<CArray<PArea_4, PArea_4>>>::value_type(key_line_index, m_Line_Area4_Array_));

        }
    }
}




// 保存线符号，并且增加宽度变成多边形

//void L2DRoad::SaveLineSymbol(LineSymbol* pLineSymbol_, float (*g_terrain)[3]) {
//    // 将刚才创建的线符号保存
//    int32 line_count = allLineSymbols_.size();
//    if (nullptr != pLineSymbol_ && pLineSymbol_->line_type_ != 0) {
//        allLineSymbols_.insert(std::unordered_map<int32, LineSymbol>::value_type(line_count++, *pLineSymbol_));
//    } else {
//        return;
//    }
//    // LOGGER_INFO << "==============> allLineSymbols_.size() = " << allLineSymbols_.size();
//    for (auto iter = allLineSymbols_.begin(); iter != allLineSymbols_.end(); ++iter) {
//        LineSymbol pLs = iter->second;
//        vector<Vec3> lp = pLs.line_points_;
//        // LOGGER_INFO << "lp.size() = " << lp.size();
//        if (!lp.empty()) {
//            int32 key_line_index = iter->first;
//            std::shared_ptr<CArray<PArea_4, PArea_4>> m_Line_Area4_Array_ = std::make_shared<CArray<PArea_4, PArea_4>>();  // 存放一条线中所有的面符号(线符号增加宽度后形成的面)
//            for (auto it = lp.begin(); it != lp.end(); ++it) {
//                // LOGGER_INFO << (*it).x << ", " << (*it).y << ", " << (*it).z;
//            }
//            // 对线符号按矩形分块
//            int32 point_count = lp.size();
//            if (point_count >= 2) {
//                for (int32 i = 0; i < point_count - 1; ++i) {
//                    Area_4* pArea4 = new Area_4;
//                    Point3 p1 = Point3(lp.at(i).x, lp.at(i).y, lp.at(i).z);
//                    Point3 p2 = Point3(lp.at(i + 1).x, lp.at(i + 1).y, lp.at(i + 1).z);
//                    GetArea4FromLine(p1, p2, pLs.line_width_, pArea4, g_terrain);
//                    CString tmpTextureStr;
//                    tmpTextureStr.Format("%s", pLs.line_texture_.c_str());
//                    pArea4->area_texture = tmpTextureStr;
//                    pArea4->deleted = 0;
//                    m_Line_Area4_Array_->Add(pArea4);
//                }
//            }
//            // 线路拐点，矩形相交 ==> 梯形
//            std::shared_ptr<CArray<PArea_4, PArea_4>> pLine_Area4_Array_After_XiangJiao = std::make_shared<CArray<PArea_4, PArea_4>>();  // 存放一条线中所有的面符号(线符号增加宽度后形成的面)
//            if (m_Line_Area4_Array_->GetSize() >= 2) {  // 至少2个矩形，相交
//                CPointPolygonRelationship tmpCPR;
//                LineSegment tmpLineSegment_A1;
//                LineSegment tmpLineSegment_A2;
//                LineSegment tmpLineSegment_B1;
//                LineSegment tmpLineSegment_B2;
//                for (int32 i = 0; i < m_Line_Area4_Array_->GetSize() - 1; ++i) {
//                    Area_4* pTmpArea4_A = m_Line_Area4_Array_->GetAt(i);
//                    tmpLineSegment_A1.pt1 = PPR_Point(pTmpArea4_A->pt1.x, pTmpArea4_A->pt1.z);
//                    tmpLineSegment_A1.pt2 = PPR_Point(pTmpArea4_A->pt4.x, pTmpArea4_A->pt4.z);
//                    tmpLineSegment_A2.pt1 = PPR_Point(pTmpArea4_A->pt2.x, pTmpArea4_A->pt2.z);
//                    tmpLineSegment_A2.pt2 = PPR_Point(pTmpArea4_A->pt3.x, pTmpArea4_A->pt3.z);
//                    // ----------------------------------------------------------
//                    Area_4* pTmpArea4_B = m_Line_Area4_Array_->GetAt(i + 1);
//                    tmpLineSegment_B1.pt1 = PPR_Point(pTmpArea4_B->pt1.x, pTmpArea4_B->pt1.z);
//                    tmpLineSegment_B1.pt2 = PPR_Point(pTmpArea4_B->pt4.x, pTmpArea4_B->pt4.z);
//                    tmpLineSegment_B2.pt1 = PPR_Point(pTmpArea4_B->pt2.x, pTmpArea4_B->pt2.z);
//                    tmpLineSegment_B2.pt2 = PPR_Point(pTmpArea4_B->pt3.x, pTmpArea4_B->pt3.z);
//                    //
//                    bool xj_1 = tmpCPR.Intersect(tmpLineSegment_A1, tmpLineSegment_B1);
//                    bool xj_2 = tmpCPR.Intersect(tmpLineSegment_A2, tmpLineSegment_B2);
//                    LOGGER_INFO << "xiangjiao 1? = " << tmpCPR.Intersect(tmpLineSegment_A1, tmpLineSegment_B1);
//                    LOGGER_INFO << "xiangjiao 2? = " << tmpCPR.Intersect(tmpLineSegment_A2, tmpLineSegment_B2);
//                    if (xj_1 || xj_2) {
//                        if (xj_1) {
//                            PPR_Point JD1 = tmpCPR.getJD(tmpLineSegment_A1.pt1, tmpLineSegment_A1.pt2, tmpLineSegment_B1.pt1, tmpLineSegment_B1.pt2);
//                            LOGGER_INFO << "JD1 = " << JD1.x << ", " << JD1.y;
//                            float a1 = 0.0f, b1 = 0.0f, c1 = 0.0f;
//                            a1 = tmpLineSegment_A2.pt2.y - tmpLineSegment_A2.pt1.y;
//                            b1 = tmpLineSegment_A2.pt1.x - tmpLineSegment_A2.pt2.x;
//                            c1 = tmpLineSegment_A2.pt2.x * tmpLineSegment_A2.pt1.y - tmpLineSegment_A2.pt1.x * tmpLineSegment_A2.pt2.y;
//                            float a2 = 0.0f, b2 = 0.0f, c2 = 0.0f;
//                            a2 = tmpLineSegment_B2.pt2.y - tmpLineSegment_B2.pt1.y;
//                            b2 = tmpLineSegment_B2.pt1.x - tmpLineSegment_B2.pt2.x;
//                            c2 = tmpLineSegment_B2.pt2.x * tmpLineSegment_B2.pt1.y - tmpLineSegment_B2.pt1.x * tmpLineSegment_B2.pt2.y;
//                            PPR_Point JD2;
//                            if (MATH_FLOAT_EQUAL_0(a1 * b2 - a2 * b1)) {
//                                AfxMessageBox("MATH_FLOAT_EQUAL_0(a1*b2 - a2*b1)...");
//                            } else {
//                                JD2.x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
//                                JD2.y = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1);
//                            }
//                            LOGGER_INFO << ".....JD2 = " << JD2.x << ", " << JD2.y;
//                            // 矩形 ==> 梯形, 修改原来四边形的坐标
//                            pTmpArea4_A->pt4.x = JD1.x;
//                            pTmpArea4_A->pt4.z = JD1.y;
//                            pTmpArea4_A->pt4.y = GetHeight(pTmpArea4_A->pt4.x, pTmpArea4_A->pt4.z, g_terrain);
//                            pTmpArea4_A->pt3.x = JD2.x;
//                            pTmpArea4_A->pt3.z = JD2.y;
//                            pTmpArea4_A->pt3.y = GetHeight(pTmpArea4_A->pt4.x, pTmpArea4_A->pt4.z, g_terrain);
//                            pTmpArea4_B->pt1.x = JD1.x;
//                            pTmpArea4_B->pt1.z = JD1.y;
//                            pTmpArea4_B->pt1.y = GetHeight(pTmpArea4_B->pt1.x, pTmpArea4_B->pt1.z, g_terrain);
//                            pTmpArea4_B->pt2.x = JD2.x;
//                            pTmpArea4_B->pt2.z = JD2.y;
//                            pTmpArea4_B->pt2.y = GetHeight(pTmpArea4_B->pt2.x, pTmpArea4_B->pt2.z, g_terrain);
//                        } else {
//                            PPR_Point JD2 = tmpCPR.getJD(tmpLineSegment_A2.pt1, tmpLineSegment_A2.pt2, tmpLineSegment_B2.pt1, tmpLineSegment_B2.pt2);
//                            LOGGER_INFO << "JD2 = " << JD2.x << ", " << JD2.y;
//                            float a1 = 0.0f, b1 = 0.0f, c1 = 0.0f;
//                            a1 = tmpLineSegment_A1.pt2.y - tmpLineSegment_A1.pt1.y;
//                            b1 = tmpLineSegment_A1.pt1.x - tmpLineSegment_A1.pt2.x;
//                            c1 = tmpLineSegment_A1.pt2.x * tmpLineSegment_A1.pt1.y - tmpLineSegment_A1.pt1.x * tmpLineSegment_A1.pt2.y;
//                            float a2 = 0.0f, b2 = 0.0f, c2 = 0.0f;
//                            a2 = tmpLineSegment_B1.pt2.y - tmpLineSegment_B1.pt1.y;
//                            b2 = tmpLineSegment_B1.pt1.x - tmpLineSegment_B1.pt2.x;
//                            c2 = tmpLineSegment_B1.pt2.x * tmpLineSegment_B1.pt1.y - tmpLineSegment_B1.pt1.x * tmpLineSegment_B1.pt2.y;
//                            PPR_Point JD1;
//                            if (MATH_FLOAT_EQUAL_0(a1 * b2 - a2 * b1)) {
//                                AfxMessageBox("MATH_FLOAT_EQUAL_0(a1*b2 - a2*b1)...");
//                            } else {
//                                JD1.x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
//                                JD1.y = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1);
//                            }
//                            LOGGER_INFO << "...JD1 = " << JD1.x << ", " << JD1.y;
//                            pTmpArea4_A->pt4.x = JD1.x;
//                            pTmpArea4_A->pt4.z = JD1.y;
//                            pTmpArea4_A->pt4.y = GetHeight(pTmpArea4_A->pt4.x, pTmpArea4_A->pt4.z, g_terrain);
//                            pTmpArea4_A->pt3.x = JD2.x;
//                            pTmpArea4_A->pt3.z = JD2.y;
//                            pTmpArea4_A->pt3.y = GetHeight(pTmpArea4_A->pt4.x, pTmpArea4_A->pt4.z, g_terrain);
//                            pTmpArea4_B->pt1.x = JD1.x;
//                            pTmpArea4_B->pt1.z = JD1.y;
//                            pTmpArea4_B->pt1.y = GetHeight(pTmpArea4_B->pt1.x, pTmpArea4_B->pt1.z, g_terrain);
//                            pTmpArea4_B->pt2.x = JD2.x;
//                            pTmpArea4_B->pt2.z = JD2.y;
//                            pTmpArea4_B->pt2.y = GetHeight(pTmpArea4_B->pt2.x, pTmpArea4_B->pt2.z, g_terrain);
//                        }
//                    }
//                }
//            }
//            allLineArea4Array_.insert(std::unordered_map<int32, std::shared_ptr<CArray<PArea_4, PArea_4>>>::value_type(key_line_index, m_Line_Area4_Array_));
//
//        }
//    }
//}
