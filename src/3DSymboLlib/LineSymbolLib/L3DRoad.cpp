#include "stdafx.h"
#include "L3DRoad.h"

L3DRoad::L3DRoad()
    : last_x(0), last_y(0), last_z(0),
      pre_x(0), pre_y(0), pre_z(0),
      p_count(0),
      m_Curve_R(INIT_CURVE_R), m_Curve_L0(INIT_CURVE_L0),
      m_distance_between_2_points(0.0f), m_pre_distance(0.0f),
      b_haveMadeRail3DwayList(FALSE),
      pRailWay_(new Railway) {
    v1_begin.setZero();
    v1_end.setZero();
    v2_begin.setZero();
    v2_end.setZero();
}


L3DRoad::~L3DRoad() {}


void L3DRoad::InitRoad() {
    pRailWay_->Init();
    b_haveMadeRail3DwayList = FALSE;            // 是否已经有三维线路显示列表(透视投影模式下)
    // 选线阈值设定(距离,夹角)
    // 用于计算2点之间线段长度
    last_x = 0, last_y = 0, last_z = 0;
    pre_x  = 0, pre_y  = 0, pre_z = 0;
    // 用于计算2线段间夹角
    v1_begin.setZero();
    v1_end.setZero();
    v2_begin.setZero();
    v2_end.setZero();
    // 记录点的个数
    p_count = 0;
    m_distance_between_2_points = 0.0f;
    m_pre_distance = 0.0f;
}


void L3DRoad::DrawFillFace(const vector<Railway3DCordinate>& fillFacePoints, CTexture* texture) const {
    int32 f_size = fillFacePoints.size();
    glBindTexture(GL_TEXTURE_2D, texture->GetTxtID());
    glColor3f(0.5, 0.6, 0.3);
    // 以四边形为单位从上到下依次填充
    for (int32 i = 0; i < 7; i += 2) {
        glBegin(GL_QUADS);
        {
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(fillFacePoints[i].x1, fillFacePoints[i].y1, fillFacePoints[i].z1);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(fillFacePoints[i + 1].x1, fillFacePoints[i + 1].y1, fillFacePoints[i + 1].z1);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(fillFacePoints[i + 1].x2, fillFacePoints[i + 1].y2, fillFacePoints[i + 1].z2);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(fillFacePoints[i].x2, fillFacePoints[i].y2, fillFacePoints[i].z2);
        }
        glEnd();
    }
}


/**************************************/
/* Function: 绘制边坡                 */
/**************************************/
void L3DRoad::DrawBP(int64 index, int32 BPside, std::shared_ptr<CDesingScheme> pDesingScheme_, CTexture* m_cTxtureBP, CTexture* m_cTxturePT) {
    float mNCDistence = 4.0;
    int64 i = index;
    int32 j;
    if (1 == BPside) {  // 左边坡
        int32 N1 = pDesingScheme_->PtS_HuPo.GetAt(i)->Huponums_L;
        int32 N2 = pDesingScheme_->PtS_HuPo.GetAt(i + 1)->Huponums_L;
        if (pDesingScheme_->PtS_HuPo.GetAt(i)->TW_left == 0 || pDesingScheme_->PtS_HuPo.GetAt(i)->TW_right == 0) {
            glColor3f(0, 1, 1);
        } else {
            glColor3f(1, 0, 0);
        }
        if (N1 <= N2 && N1 > 0 && N2 > 0) {
            for (j = 0; j < N1; ++j) {
                glBindTexture(GL_TEXTURE_2D, m_cTxtureBP->GetTxtID());
                // 如果路基类型相同(同为路堑或路堤)
                if (pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].style == pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].style) {
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].z);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].z);
                    glEnd();
                } else {  // 如果路基类型相同(路堑,路堤相连)
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].z);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j + 1].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j + 1].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j + 1].Hp[2].z);
                    glEnd();
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j + 1].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j + 1].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j + 1].Hp[2].z);
                    glTexCoord2f(0.5f, 0.5f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j + 1].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j + 1].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j + 1].Hp[1].z);
                    glTexCoord2f(0.5f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].z);
                    glEnd();
                }
                if (j > 0) {
                    glBindTexture(GL_TEXTURE_2D, m_cTxturePT->GetTxtID());
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[0].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[0].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[0].z);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[0].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[0].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[0].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].z);
                    glEnd();
                }
            }
        } else {
            for (j = 0; j < N2; ++j) {
                glBindTexture(GL_TEXTURE_2D, m_cTxtureBP->GetTxtID());
                if (pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].style == \
                        pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].style) {
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].z);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].z);
                    glEnd();
                } else {
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j + 1].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j + 1].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j + 1].Hp[2].z);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].z);
                    glEnd();
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j + 1].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j + 1].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j + 1].Hp[2].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j + 1].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j + 1].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j + 1].Hp[1].z);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].z);
                    glEnd();
                }
                if (j > 0) {
                    glBindTexture(GL_TEXTURE_2D, m_cTxturePT->GetTxtID());
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[0].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[0].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[0].z);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[0].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[0].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[0].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].z);
                    glEnd();
                }
            }
        }
    } else if (BPside == 2) {
        int32 N1 = pDesingScheme_->PtS_HuPo.GetAt(i)->Huponums_R;
        int32 N2 = pDesingScheme_->PtS_HuPo.GetAt(i + 1)->Huponums_R;
        if (N1 <= N2 && N1 > 0 && N2 > 0) {
            for (j = 0; j < N1; ++j) {
                glBindTexture(GL_TEXTURE_2D, m_cTxtureBP->GetTxtID());
                if (pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].style == \
                        pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].style) {
                    glBegin(GL_POLYGON);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].z);
                    glEnd();
                } else {
                    glBegin(GL_POLYGON);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j + 1].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j + 1].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j + 1].Hp[2].z);
                    glEnd();
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j + 1].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j + 1].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j + 1].Hp[2].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j + 1].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j + 1].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j + 1].Hp[1].z);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].z);
                    glEnd();
                }
                if (j > 0) {
                    glBindTexture(GL_TEXTURE_2D, m_cTxturePT->GetTxtID());
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[0].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[0].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[0].z);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[0].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[0].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[0].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].z);
                    glEnd();
                }
            }
        } else {
            for (j = 0; j < N2; ++j) {
                glBindTexture(GL_TEXTURE_2D, m_cTxtureBP->GetTxtID());
                if (pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].style == \
                        pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].style) {
                    glBegin(GL_POLYGON);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].z);
                    glEnd();
                } else {
                    glBegin(GL_POLYGON);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j + 1].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j + 1].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j + 1].Hp[2].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].z);
                    glEnd();
                    glBegin(GL_POLYGON);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j + 1].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j + 1].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j + 1].Hp[2].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j + 1].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j + 1].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j + 1].Hp[1].z);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].z);
                    glEnd();
                }
                if (j > 0) {
                    glBindTexture(GL_TEXTURE_2D, m_cTxturePT->GetTxtID());
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[0].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[0].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[0].z);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[0].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[0].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[0].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].x,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].y,
                               pDesingScheme_->PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].z);
                    glEnd();
                }
            }
        }
    }
    glLineWidth(1.0);
    glColor3f(1, 1, 1);
}



/**************************************/
/* Function: 绘制中心线               */
/**************************************/
void L3DRoad::DrawCenterLine(int64 index,
                             BOOL ifSelectLine,
                             std::shared_ptr<CDesingScheme> pDesingScheme_,
                             CArray<PCordinate,
                             PCordinate>& m_TempPts,
                             const GetHeightCallBack& getHeightCallBack,
                             float getHeightCallBack_arg_x,
                             float getHeightCallBack_arg_z) {
    CString tt;
    double x1 = 0.0, y1 = 0.0, z1 = 0.0;
    double x2 = 0.0, y2 = 0.0, z2 = 0.0;
    double x0, y0, z0;
    float DerDistence = 2.0f;
    float Dh;
    m_TempPts.RemoveAll();
    if (ifSelectLine) {  // 在选线设计
        Dh = 5;
        x1 = pDesingScheme_->PtS_JD.GetAt(index)->x;
        // y1=pDesingScheme_->PtS_JD.GetAt(index)->y;
        z1 = pDesingScheme_->PtS_JD.GetAt(index)->z;
        y1 = getHeightCallBack(x1, z1);
        x2 = pDesingScheme_->PtS_JD.GetAt(index + 1)->x;
        // y2=pDesingScheme_->PtS_JD.GetAt(index+1)->y;
        z2 = pDesingScheme_->PtS_JD.GetAt(index + 1)->z;
        y2 = getHeightCallBack(x2, z2);
    }
    glColor3f(0, 0, 1);
    PCordinate pt;
    double L = pDesingScheme_->GetDistenceXYZ(x1, y1, z1, x2, y2, z2);
    double L0 = 0;
    while (L0 <= L) {
        x0 = x1 + L0 / L * (x2 - x1);
        y0 = y1 + L0 / L * (y2 - y1);
        z0 = z1 + L0 / L * (z2 - z1);
        // 地面高程
        float dmh = getHeightCallBack(x0, -z0);
        if (y0 >= dmh - Dh) {  // 设计线点高程大于地面高程
            pt = new Cordinate;
            pt->x = x0;
            pt->y = y0;
            pt->z = z0;
            m_TempPts.Add(pt);
        } else {
            if (m_TempPts.GetSize() > 1) {
                glBegin(GL_LINE_STRIP);
                for (int32 k = 0; k < m_TempPts.GetSize(); k++) {
                    glVertex3f(m_TempPts.GetAt(k)->x, m_TempPts.GetAt(k)->y, m_TempPts.GetAt(k)->z);
                }
                glEnd();
                m_TempPts.RemoveAll();
                L0 -= DerDistence;
            }
        }
        L0 += DerDistence;
        if (L0 >= L) {
            x0 = x2;
            y0 = y2;
            z0 = z2;
            dmh = getHeightCallBack(x0, -z0);
            if (y0 >= dmh - Dh) {  // 设计线点高程大于地面高程
                pt = new Cordinate;
                pt->x = x0;
                pt->y = y0;
                pt->z = z0;
                m_TempPts.Add(pt);
                if (m_TempPts.GetSize() > 1) {
                    glBegin(GL_LINE_STRIP);
                    for (int32 k = 0; k < m_TempPts.GetSize(); k++) {
                        glVertex3f(m_TempPts.GetAt(k)->x, m_TempPts.GetAt(k)->y, m_TempPts.GetAt(k)->z);
                    }
                    glEnd();
                    m_TempPts.RemoveAll();
                }
            }
            break;
        }
    }
    if (m_TempPts.GetSize() > 1) {
        glBegin(GL_LINE_STRIP);
        for (int32 k = 0; k < m_TempPts.GetSize(); k++) {
            glVertex3f(m_TempPts.GetAt(k)->x, m_TempPts.GetAt(k)->y, m_TempPts.GetAt(k)->z);
        }
        glEnd();
        m_TempPts.RemoveAll();
    }
}



/****************************************************/
/* Function: 实现透视投影模式下的线路三维模型绘制       */
/****************************************************/
void L3DRoad::DrawRailwaythesme(std::shared_ptr<CDesingScheme> pDesingScheme_,
                                CTexture* FillFace,
                                GLuint m_Rail3DwayList,
                                CTexture* m_cTxtureBP,
                                CTexture* m_cTxturePT,
                                CTexture* m_cTxtureRailway,
                                CTexture* m_cTxtureGdToLJ,
                                CTexture* m_cTxtureLJ) {
    CString m_style, m_stylePre, m_styleNext;
    // 如果还没有构建线路三维模型的显示列表
    if (b_haveMadeRail3DwayList == FALSE) {
        glNewList(m_Rail3DwayList, GL_COMPILE_AND_EXECUTE);  // 创建显示列表
        glColor3f(0.75, 0.75, 0.75);        // 设置颜色
        glLineWidth(2.0);                   // 设置线宽
        // 1.绘制左侧路基边坡
        glColor3f(1, 0, 0);
        glBindTexture(GL_TEXTURE_2D, m_cTxtureBP->GetTxtID());           // 绑定路基边坡纹理
        for (int32 i = 0; i < pDesingScheme_->PtS_HuPo.GetSize() - 1; i++) {
            m_style = pDesingScheme_->PtS_3DLineZX.GetAt(i)->strJDStyle;  // 交点类型
            m_styleNext = pDesingScheme_->PtS_3DLineZX.GetAt(i + 1)->strJDStyle;
            // 如果交点类型是非其他的点，则绘制路基边坡
            if (m_style != "...") {
                DrawBP(i, 1, pDesingScheme_, m_cTxtureBP, m_cTxturePT);  // 绘制左侧路基边坡
            }
        }
        // 2.绘制右侧路基边坡
        glBindTexture(GL_TEXTURE_2D, m_cTxtureBP->GetTxtID());               // 绑定路基边坡纹理
        for (int32 i = 0; i < pDesingScheme_->PtS_HuPo.GetSize() - 1; i++) {
            m_style = pDesingScheme_->PtS_3DLineZX.GetAt(i)->strJDStyle;     // 交点类型
            m_styleNext = pDesingScheme_->PtS_3DLineZX.GetAt(i + 1)->strJDStyle;  // 下一点的交点类型
            if (m_style != "...") {
                glBindTexture(GL_TEXTURE_2D, m_cTxtureBP->GetTxtID());
                DrawBP(i, 2, pDesingScheme_, m_cTxtureBP, m_cTxturePT);  // 绘制右侧路基边坡
            }
        }
        // 3.绘制轨道
        glBindTexture(GL_TEXTURE_2D, m_cTxtureRailway->GetTxtID());          // 绑定轨道纹理
        glLineWidth(2.0);                                                   // 设置线宽
        for (int32 i = 0; i < pDesingScheme_->PtS_Railway3D.GetSize() - 1; i++) {
            if (pDesingScheme_->PtS_3DLineZX.GetAt(i)->Derh == 0)            // 如果挖为0
                glColor3f(0, 1, 1);                                         // 设置颜色
            else
                glColor3f(1, 0, 1);
            float L = pDesingScheme_->GetDistenceXY(pDesingScheme_->PtS_Railway3D.GetAt(i)->x1, \
                                                    pDesingScheme_->PtS_Railway3D.GetAt(i)->z1, \
                                                    pDesingScheme_->PtS_Railway3D.GetAt(i + 1)->x2, \
                                                    pDesingScheme_->PtS_Railway3D.GetAt(i + 1)->z2);
            // 以矩形方式连接前后相临轨道断面
            glBegin(GL_POLYGON);
            glTexCoord2f(0.0f, 0.0f);  // 设置纹理坐标(当前轨道断面左侧点)
            glVertex3f(pDesingScheme_->PtS_Railway3D.GetAt(i)->x1, \
                       pDesingScheme_->PtS_Railway3D.GetAt(i)->y1,
                       pDesingScheme_->PtS_Railway3D.GetAt(i)->z1);
            glTexCoord2f(1.0f, 0.0f);  // 设置纹理坐标(当前轨道断面右侧点)
            glVertex3f(pDesingScheme_->PtS_Railway3D.GetAt(i)->x2, \
                       pDesingScheme_->PtS_Railway3D.GetAt(i)->y2,
                       pDesingScheme_->PtS_Railway3D.GetAt(i)->z2);
            glTexCoord2f(1.0f, L / 10);  // 设置纹理坐标(下一前轨道断面右侧点)
            glVertex3f(pDesingScheme_->PtS_Railway3D.GetAt(i + 1)->x2, \
                       pDesingScheme_->PtS_Railway3D.GetAt(i + 1)->y2,
                       pDesingScheme_->PtS_Railway3D.GetAt(i + 1)->z2);
            glTexCoord2f(0.0f, L / 10);  // 设置纹理坐标(下一前轨道断面左侧点)
            glVertex3f(pDesingScheme_->PtS_Railway3D.GetAt(i + 1)->x1, \
                       pDesingScheme_->PtS_Railway3D.GetAt(i + 1)->y1,
                       pDesingScheme_->PtS_Railway3D.GetAt(i + 1)->z1);
            glEnd();
        }
        // 4.绘制道床边坡
        glBindTexture(GL_TEXTURE_2D, m_cTxtureGdToLJ->GetTxtID());  // 绑定道床边坡纹理
        glColor3f(1, 1, 0);  // 设置颜色
        for (int32 i = 0; i < pDesingScheme_->PtS_Railway3D.GetSize() - 1; i++) {
            // 以矩形方式连接方式绘制左侧道床边坡
            glBegin(GL_POLYGON);
            glTexCoord2f(1.0f, 0.0f);  // 设置纹理坐标(当前左侧道床边坡左侧点)
            glVertex3f(pDesingScheme_->PtS_Railway3D.GetAt(i)->x1, \
                       pDesingScheme_->PtS_Railway3D.GetAt(i)->y1,
                       pDesingScheme_->PtS_Railway3D.GetAt(i)->z1);
            glTexCoord2f(1.0f, 1.0f);  // 设置纹理坐标(当前左侧道床边坡右侧点)
            glVertex3f(pDesingScheme_->PtS_Railway3D.GetAt(i + 1)->x1, \
                       pDesingScheme_->PtS_Railway3D.GetAt(i + 1)->y1,
                       pDesingScheme_->PtS_Railway3D.GetAt(i + 1)->z1);
            glTexCoord2f(0.0f, 1.0f);  // 设置纹理坐标(下一左侧道床边坡右侧点)
            glVertex3f(pDesingScheme_->PtS_RailwayLj3D.GetAt(i + 1)->x1, \
                       pDesingScheme_->PtS_RailwayLj3D.GetAt(i + 1)->y1,
                       pDesingScheme_->PtS_RailwayLj3D.GetAt(i + 1)->z1);
            glTexCoord2f(0.0f, 0.0f);  // 设置纹理坐标(下一左侧道床边坡左侧点)
            glVertex3f(pDesingScheme_->PtS_RailwayLj3D.GetAt(i)->x1, \
                       pDesingScheme_->PtS_RailwayLj3D.GetAt(i)->y1,
                       pDesingScheme_->PtS_RailwayLj3D.GetAt(i)->z1);
            glEnd();
            // 以矩形方式连接方式绘制右侧道床边坡
            glBegin(GL_POLYGON);
            glTexCoord2f(0.0f, 0.0f);  // 设置纹理坐标(当前右侧道床边坡左侧点)
            glVertex3f(pDesingScheme_->PtS_Railway3D.GetAt(i)->x2, \
                       pDesingScheme_->PtS_Railway3D.GetAt(i)->y2,
                       pDesingScheme_->PtS_Railway3D.GetAt(i)->z2);
            glTexCoord2f(0.0f, 1.0f);  // 设置纹理坐标(当前右侧道床边坡右侧点)
            glVertex3f(pDesingScheme_->PtS_Railway3D.GetAt(i + 1)->x2, \
                       pDesingScheme_->PtS_Railway3D.GetAt(i + 1)->y2,
                       pDesingScheme_->PtS_Railway3D.GetAt(i + 1)->z2);
            glTexCoord2f(1.0f, 1.0f);  // 设置纹理坐标(下一右侧道床边坡右侧点)
            glVertex3f(pDesingScheme_->PtS_RailwayLj3D.GetAt(i + 1)->x2, \
                       pDesingScheme_->PtS_RailwayLj3D.GetAt(i + 1)->y2,
                       pDesingScheme_->PtS_RailwayLj3D.GetAt(i + 1)->z2);
            glTexCoord2f(1.0f, 0.0f);  // 设置纹理坐标(下一右侧道床边坡左侧点)
            glVertex3f(pDesingScheme_->PtS_RailwayLj3D.GetAt(i)->x2, \
                       pDesingScheme_->PtS_RailwayLj3D.GetAt(i)->y2,
                       pDesingScheme_->PtS_RailwayLj3D.GetAt(i)->z2);
            glEnd();
        }
        // 5.绘制路肩
        glBindTexture(GL_TEXTURE_2D, m_cTxtureLJ->GetTxtID());  // 绑定路肩纹理
        glColor3f(1, 0.5, 0.25);
        for (int32 i = 0; i < pDesingScheme_->PtS_RailwayLj3D.GetSize() - 1; i++) {
            // 以矩形方式连接方式绘制左侧路肩
            glBegin(GL_POLYGON);
            glTexCoord2f(0.0f, 0.0f);  // 设置纹理坐标(当前左侧路肩断面左侧点)
            glVertex3f(pDesingScheme_->PtS_RailwayLjToBP3D.GetAt(i)->x1, \
                       pDesingScheme_->PtS_RailwayLjToBP3D.GetAt(i)->y1,
                       pDesingScheme_->PtS_RailwayLjToBP3D.GetAt(i)->z1);
            glTexCoord2f(0.0f, 1.0f);  // 设置纹理坐标(当前左侧路肩断面右侧点)
            glVertex3f(pDesingScheme_->PtS_RailwayLjToBP3D.GetAt(i + 1)->x1, \
                       pDesingScheme_->PtS_RailwayLjToBP3D.GetAt(i + 1)->y1,
                       pDesingScheme_->PtS_RailwayLjToBP3D.GetAt(i + 1)->z1);
            glTexCoord2f(1.0f, 1.0f);  // 设置纹理坐标(下一左侧路肩断面右侧点)
            glVertex3f(pDesingScheme_->PtS_RailwayLj3D.GetAt(i + 1)->x1, \
                       pDesingScheme_->PtS_RailwayLj3D.GetAt(i + 1)->y1,
                       pDesingScheme_->PtS_RailwayLj3D.GetAt(i + 1)->z1);
            glTexCoord2f(1.0f, 0.0f);  // 设置纹理坐标(下一左侧路肩断面左侧点)
            glVertex3f(pDesingScheme_->PtS_RailwayLj3D.GetAt(i)->x1, \
                       pDesingScheme_->PtS_RailwayLj3D.GetAt(i)->y1,
                       pDesingScheme_->PtS_RailwayLj3D.GetAt(i)->z1);
            glEnd();
            // 以矩形方式连接方式绘制右侧路肩
            glBegin(GL_POLYGON);
            glTexCoord2f(0.0f, 0.0f);  // 设置纹理坐标(当前右侧路肩断面左侧点)
            glVertex3f(pDesingScheme_->PtS_RailwayLj3D.GetAt(i)->x2, \
                       pDesingScheme_->PtS_RailwayLj3D.GetAt(i)->y2,
                       pDesingScheme_->PtS_RailwayLj3D.GetAt(i)->z2);
            glTexCoord2f(1.0f, 0.0f);  // 设置纹理坐标(当前右侧路肩断面右侧点)
            glVertex3f(pDesingScheme_->PtS_RailwayLjToBP3D.GetAt(i)->x2, \
                       pDesingScheme_->PtS_RailwayLjToBP3D.GetAt(i)->y2,
                       pDesingScheme_->PtS_RailwayLjToBP3D.GetAt(i)->z2);
            glTexCoord2f(1.0f, 1.0f);  // 设置纹理坐标(下一右侧路肩断面右侧点)
            glVertex3f(pDesingScheme_->PtS_RailwayLjToBP3D.GetAt(i + 1)->x2, \
                       pDesingScheme_->PtS_RailwayLjToBP3D.GetAt(i + 1)->y2,
                       pDesingScheme_->PtS_RailwayLjToBP3D.GetAt(i + 1)->z2);
            glTexCoord2f(0.0f, 1.0f);  // 设置纹理坐标(下一右侧路肩断面左侧点)
            glVertex3f(pDesingScheme_->PtS_RailwayLj3D.GetAt(i + 1)->x2, \
                       pDesingScheme_->PtS_RailwayLj3D.GetAt(i + 1)->y2,
                       pDesingScheme_->PtS_RailwayLj3D.GetAt(i + 1)->z2);
            glEnd();
        }
        // 6.填补断面
        int32 JD_Count = pDesingScheme_->PtS_JD.GetSize();
        int32 b_pIndex = 0;
        int32 e_pIndex = JD_Count - 1;
        if (JD_Count > 0) {
            // 保存2个面上的点的坐标信息
            vector<Railway3DCordinate> rc2;
            vector<Railway3DCordinate> rc1;
            // 计算前后断面各点
            pDesingScheme_->CalculateFillFacePoints(rc2, rc1);
            // 根据点绘制面
            DrawFillFace(rc2, FillFace);
            DrawFillFace(rc1, FillFace);
        }
        glLineWidth(1.0);               // 恢复线宽
        glEndList();                    // 结束显示列表
        b_haveMadeRail3DwayList = TRUE;  // 标识已经创建显示列表
    } else {                            // 如果已经构建线路三维模型的显示列表,则直接调用显示列表
        glCallList(m_Rail3DwayList);    // 调用线路三维模型显示列表
    }
    glPopAttrib();                      // 弹出属性堆栈
}
