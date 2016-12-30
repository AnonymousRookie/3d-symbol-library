#ifndef SYMBOL_LIB_NEW_VIEW_H
#define SYMBOL_LIB_NEW_VIEW_H

#include <memory>
#include <MMSystem.h>
#include <cmath>
#include <algorithm>
#include <functional>
#include <atlimage.h>
#include "MFCFrameWork/MainFrm.h"
#include "SpaceSearchSet.h"
#include "CameraParamSet.h"
#include "TerrainImportContour.h"
#include "SkyBoxTexLoad.h"
#include "Texture.h"
#include "PointSymbolLib/Load3DS.H"
#include "PointSymbolLib/C3DModelParamSet.h"
#include "PointSymbolLib/ModelParam.h"
#include "GLFont.h"
#include "stdafx.h"
#include "Base/ZTypes.h"
#include "MathUtils/PointPolygonRelationship.h"
#include "MathUtils/Vec3.h"
#include "Camera.h"
#include "SymbolDefines.h"
#include "NClock.h"
#include "AreaSymbolLib/Area4.h"
#include "SkyBox.h"
#include "LineSymbolLib/SimpleLine.h"
#include "LineSymbolLib/L3DRoad.h"
#include "LineSymbolLib/DesingScheme.h"
#include "LineSymbolLib/L2DRoad.h"
#include <unordered_map>

#include "AreaSymbolLib/FiveStar.h"


class CMy3DSymbolLibNewView : public CView {
  protected:  // 仅从序列化创建
    CMy3DSymbolLibNewView();
    DECLARE_DYNCREATE(CMy3DSymbolLibNewView)

  public:
    CMy3DSymbolLibNewDoc* GetDocument() const;

  public:
    virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);  // NOLINT

  protected:
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  public:
    virtual ~CMy3DSymbolLibNewView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;  // NOLINT
#endif

    // 生成的消息映射函数
  protected:
    afx_msg void OnFilePrintPreview();
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    DECLARE_MESSAGE_MAP()
  public:
    PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
    PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;

    HWND        hwnd;
    CDC*        m_pDC;
    HGLRC       m_hRC;

    int32 m_SCREEN_WIDTH;       // 屏幕宽度
    int32 m_SCREEN_HEIGHT;      // 屏幕高度

    int32 WinViewX, WinViewY;   // 存储所定义视口的宽度和高度
    BOOL bStereoAvailable_;     // 显卡是否支持立体显示

    GLfloat m_ViewWideNarrow;   // 用来调整gluPerspective()函数定义平截头体的视野的角度(增大或减小)
    double m_near, m_far;       // gluPerspective()函数定义平截头体的近剪裁平面和远剪裁平面的距离

    float m_FrustumAngle;

    BOOL SetupPixelFormat();
    BOOL InitializeOpenGL(CDC* pDC);
    void InitList();  // 初始化显示列表

    void InitData();
    afx_msg int32 OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnSize(UINT nType, int32 cx, int32 cy);
    afx_msg LRESULT OnGoodBye(WPARAM wParam, LPARAM lParam);  // 自定义响应消息,响应模型设置,非模式对话框



    /*********************************************************************************************/
    // 地形Terrain
    /*********************************************************************************************/
  public:
    // 导入等高线地势图纹理及数据
    int32               iTerrainType;                       // 1-等高, 2-随机, 0-没有导入地形
    CString             terrainTexFileName;
    CString             terrainContourFileName;
    BITMAPINFOHEADER    g_bit;                              // 定义位图结构，在ModelObj中使用灰度等高线图生成地形
    uint8*              g_imageData;                        // 定义图形缓存区，在ModelObj中使用灰度等高线图生成地形
    UINT                texTerrain;                         // 贴图
    bool                LoadT8(char* filename, GLuint& texture);  // NOLINT
    uint8*              LoadBit(char* filename, BITMAPINFOHEADER* bitmap);

    bool        g_isTerrainInit;
    void        InitTerrain();
    void        DrawTerrain();
    float       GetHeight(float x, float z);        // 获取地面高度

    // 地形数据
    std::unique_ptr<TerrainData> pTerrainData_;
    // 地形纹理
    void LoadTerrainTex(CString terrainTex, CString terrainContour);
    afx_msg void OnContourTerrainImport();

    // 地形等高线数据
    std::vector<float> terrainContourData_;
    /*********************************************************************************************/
    // 相机Camera
    /*********************************************************************************************/
  public:
    std::unique_ptr<Camera> pCamera_;
    // 用于计算相机事参数的CVector3类型变量
    Vec3    m_vStrafe;
    CVector3    View;
    void CamraUpdate();
    void MoveCameraZ(float speed);
    void CheckForMovement();
    void MoveCameraX(float speed);
    void SetCamra();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    void SetViewByMouse();
    void RotateView(float angle, float x, float y, float z);
    float  derAngleY;       //  鼠标控制时Y方向的敏感系数
    float  derAngleZ;       //  鼠标控制时Z方向的敏感系数
    float  derDisScale;     //  鼠标移动模型时敏感系数
    afx_msg void OnCameraParamSet();
    bool    m_bmouseView;       // 是否起用鼠标控制相机
    POINT   m_oldMousePos;      // 前一鼠标位置

    /*********************************************************************************************/
    // 天空盒SkyBox
    /*********************************************************************************************/
  public:
    // 天空盒
    std::unique_ptr<SkyBox> pSkyBox_;
    afx_msg void OnSkyboxTex();
    // 天气数据
    CString m_WeatherFolder, m_WeatherTex;
    // 天空盒纹理
    void LoadSkyBoxTex(CString skyTP, CString skyLF, CString skyBK, CString skyRT, CString skyFR);
    CString g_texSkyBoxFlieNameTP, g_texSkyBoxFlieNameLF, g_texSkyBoxFlieNameBK, g_texSkyBoxFlieNameRT, g_texSkyBoxFlieNameFR;

    // 导入天气纹理 只有一个纹理
    afx_msg void OnWeatherLoad();

    UINT g_weatherTex;          // 贴图,纹理
    void ShowWeather();
    bool bIsWeatherLoad_;

    GLuint m_SkyList;       // 时钟指北针显示列表
    bool m_bShowbreviary;   // 是否显示缩略视图
    void MakeSkykList();
    void DrawSky();
    void SetSkyProjection();
    void SetSkyProjectionNavigate();

    /*********************************************************************************************/
    // 绘图模式
    /*********************************************************************************************/
  public:
    // 设置绘图模式
    int32 m_Drawmode;
    void SetDrawMode();
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnUpdateDrawmodeLine(CCmdUI* pCmdUI);
    afx_msg void OnDrawmodeRender();
    afx_msg void OnUpdateDrawmodeRender(CCmdUI* pCmdUI);
    afx_msg void OnUpdateDrawmodeTexture(CCmdUI* pCmdUI);
    afx_msg void OnDrawmodeLine();
    afx_msg void OnDrawmodeTexture();


    /*********************************************************************************************/
    // 空间查询 SpaceSearch
    /*********************************************************************************************/
  public:
    // 空间查询标志参数
    SpaceSearchInfo spaceSearchInfo_;
    double pt1[3], pt2[3];     // 存储查询的坐标
    BYTE    m_OperateType;      // 模型操作类型
    afx_msg void OnQueryCoordinate();
    afx_msg void OnUpdateQueryCoordinate(CCmdUI* pCmdUI);
    afx_msg void OnQueryDistence();
    afx_msg void OnUpdateQueryDistence(CCmdUI* pCmdUI);
    void DrawSearchPoint();
    afx_msg void OnSpacequerySet();

    void ScreenToGL(CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

    int32     m_keynumber;  // 标识键盘按键值
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);





    /*********************************************************************************************/
    // 三维漫游
    /*********************************************************************************************/
  public:
    BOOL m_ShowFlyPath;                                 // 标识是否显示飞行路径
    CArray<PCordinate, PCordinate> m_FlayPath;          // 存储进行飞行路径选择时所选择的一系列点坐标
    CArray<PCordinate, PCordinate> m_FlayPathTempPts;   // 存储临时进行飞行路径选择时所选择的一系列点坐标
    afx_msg void OnPathManuinput();
    void DrawFlyPath();
    afx_msg void OnFlppathInterpolation();
    afx_msg void OnFlypathSave();
    int32 FlyPathSave(char* pathfile);
    BOOL m_PathFlag;  // 是否输入飞行路径
    afx_msg void OnFlyOpenpath();
    int32 FlyPathRead(char* pathfile);
    afx_msg void OnFlyOnoffpath();
    afx_msg void OnUpdateFlyOnoffpath(CCmdUI* pCmdUI);

    BYTE m_FlyHeightType;               // 三维漫游类型(固定高度漫游,固定高差漫游)
    int32 m_flypathPtIndex;             // 飞行路径坐标索引号
    int32 m_flyPathCurrentPtIndex;      // 在飞行过程中记录当前路径点的索引号,用于暂停飞行器
    int32 m_flyspeed;                   // 飞行时的计时器时间间隔

    BOOL m_fly_start_pause_Enable;      // 暂停/开始是否生效

    afx_msg void OnFlyStaticheight();
    afx_msg void OnUpdateFlyStaticheight(CCmdUI* pCmdUI);
    void SetFLyTimer();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    void GetCameraCorrdinate(double x1, double y1, double z1, double x2, double y2, double z2);
    float m_maxHeight, m_minHeight, m_StaticHeight;
    afx_msg void OnFlyRoutineheight();

    GLfloat m_ViewUpDown;           // 视角上,下倾
    afx_msg void OnUpdateFlyRoutineheight(CCmdUI* pCmdUI);

    BOOL m_FlyPause;                // 是否暂停飞行
    afx_msg void OnFlyPlaypause();
    afx_msg void OnUpdateFlyPlaypause(CCmdUI* pCmdUI);
    afx_msg void OnFlyStop();
    afx_msg void OnFlyOnestep();
    afx_msg void OnFlyViewEnlarge();
    afx_msg void OnFlyViewSmall();
    afx_msg void OnFlyHeightUp();
    afx_msg void OnFlyHeightDown();
    afx_msg void OnFlyViewUp();
    afx_msg void OnFlyViewDown();
    afx_msg void OnFlySpeedUp();
    afx_msg void OnFlySpeedDown();
    void DisplayHelp();
    CGLFont* Font;              // 显示飞行时快捷键文字提示
    int32 m_Time,               // 开始时间
          m_Fram,               // 显示次数
          tim;                  // 刷新速度
    HFONT   hFont, hFont0;
    void    TextFlyHelp();      // 显示文字




    /*********************************************************************************************/
    // 指北针 NClcok
    /*********************************************************************************************/
  public:
    std::unique_ptr<NClcok> pNClock_;  // 指北针
    void DrawClock();
    void SetClockProjectionNavigate();
    void GetNorthPtangle();


    /*********************************************************************************************/
    // 非3DS模型参数设置的非模式对话框   函数与变量
    /*********************************************************************************************/
  public:
    C3DModelParamSet* paramSet_modeless_dlg;
    void C3DModelParamSetTOPModelStruct(C3DModelParamSet* model, PModelStruct& pStruct);  // NOLINT
    PModelStruct p3dtree;           // 3dtree
    PModelStruct ptree;             // tree
    PModelStruct pCitySymbol;       // CitySymbol
    BOOL m_isSetXYByMouse;


    /*********************************************************************************************/
    // 场景 工程文件管理
    /*********************************************************************************************/
  public:
    // 场景配置文件导入
    bool m_bSecneConfig;
    afx_msg void OnSceneLoad();
    CString m_AllDataPath;  // 所有数据文件路径
    CString m_SceneConfig;  // 场景文件夹
    void loadSceneFile(CString filename);   // 加载场景工程文件
    // 加载点文件
    void LoadPointSymbolFile(CString filename);
    // 加载线文件
    void LoadLineSymbolFile(CString filename);
    // 加载区文件
    void LoadAreaSymbolFile(CString filename);
    // 当前工程文件名
    CString m_CurrentProjectName;
    // 当前符号种类个数
    CString m_CurrentSymbolTypeNum;
    // 点、线、区文件
    CString m_PointSymbolFile, m_LineSymbolFile, m_AreaSymbolFile;
    // 判断当前工程中是否存在已经打开的点、线、面文件
    BOOL exist_point_file();
    BOOL exist_line_file();
    BOOL exist_area_file();
    BOOL exist_point_flag;
    BOOL exist_line_flag;
    BOOL exist_area_flag;
    // 新建符号文件
    int32 new_symbol_file(uint32 type, char* fileName);  // 0,1,2 点线面
    int32 new_point_file();
    int32 new_line_file();
    int32 new_area_file();
    // 保存点文件
    int32 savePointSymbolFile(CString filename);
    // 保存线文件
    int32 saveLineSymbolFile(CString filename);
    // 保存区文件
    int32 saveAreaSymbolFile(CString filename);
    bool ScenSave(CString scenePth);
    void DrawScene();

    afx_msg void OnConfigureSymbolList();
    afx_msg void OnSystemSetting();
    afx_msg void OnCloseCurrentScene();
    afx_msg void OnSceneNew();
    afx_msg void OnSceneSaveAs();
    afx_msg void OnSceneSave();

    /*********************************************************************************************/
    // 点符号
    /*********************************************************************************************/
  public:
    /* 3DS 模型 */
    std::unique_ptr<T3DModelData> pT3DModelData_;
    // 控制选中模型,单个模型选择可以控制所有模型参数设置，组模型选择的话只能移动组合模型
    // 右键按下 弹起 标识
    int32 m_selectedModelID;  // 当前鼠标选中模型ID，当前默认只有3DS模型
    afx_msg void OnModelMove();
    afx_msg void OnModelParam();
    afx_msg void OnModelScale();
    afx_msg void OnModelDelete();
    // 射线拾取物体
    void JudgeRayIntersect(
        CVector3& rayStart,      // 射线起点
        CVector3& rayDir,        // 射线长度和方向
        CVector3& returnNormal   // 可选的，相交点处法向量
    );
    // 判断射线是否与AABB包围盒，并返回交点
    float RayIntersect(
        CVector3& rayStart,      // 射线起点
        CVector3& rayDir,        // 射线长度和方向
        CVector3& returnNormal,  // 可选的，相交点处法向量
        CVector3& min,           // 包围盒左下角顶点
        CVector3& max            // 包围盒右上角顶点
    );

    // 拾取模型集合
    vector<PSelectedModel> m_pSelectedModelSet;
    // 选中物体线框颜色
    float wireR, wireG, wireB;
    // 闪烁定时器启动标识
    bool m_bFlash;

    bool m_bMouseMoveSelect;  // 选择模式下的鼠标移动拾取模型
    int32 m_mouseShape;        // 鼠标形态

    // 3DS模型
    afx_msg void On3dsModelLoad();

    int32 m_i3DModelNum;
    CArray<PModelParamStruct, PModelParamStruct> m_3DModel;
    // 3DS模型
    std::unique_ptr<CLoad3DS> p3ds_;  // 定义3DS模型

    void Draw3DModel(PModelParamStruct model);

    afx_msg void On3dsModelSelectSet();
    afx_msg void OnUpdate3dsModelSelectSet(CCmdUI* pCmdUI);
    bool bIsSelect3DModel_;

    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

    bool bIsMouseMove3DModel_;
    afx_msg void On3dsModelMouseMove();
    afx_msg void OnUpdate3dsModelMouseMove(CCmdUI* pCmdUI);
    void JudgeModelSelected(PCordinate ppt);        // 判断模型组中哪些模型被选中,进行状态修改
    int32 m_bMouseMove3DModelPtNums;                // 左键按下数量加一,左键弹起再加一,到2时就可移动模型位置,移动向量为鼠标变动向量
    // 3D模型设置
    void Load3DModel(PModelParamStruct p3d, int32 iLoadModelType);

    // ----------------------------------------------------------------------------

    /* 景观树数据 */
    std::unique_ptr<TreeModelData> pTreeModelData_;
    // 景观树控制
    afx_msg void OnTreeLoad();
    CArray<PModelStruct, PModelStruct> m_TreeModel;     // 存储所有景观树信息
    void LoadT16(char* filename, GLuint& texture);      // NOLINT
    int32 m_iTreeModelNum;
    UINT g_cactus[50];                                  // 贴图,纹理

    // 显示特殊平面树，场景旋转时树也跟着旋转，始终是正面对着用户，这样就看不出是平面了
    void ShowTree(int32 i);

    // 导入3D立体景观树模型
    afx_msg void On3dTreeLoad();
    CArray<PModelStruct, PModelStruct> m_3DTreeModel;   // 存储所有景观树信息
    int32 m_i3DTreeModelNum;
    UINT g_cactus3DTree[50];                            // 贴图,纹理
    // 显示特殊平面树，场景旋转时树也跟着旋转，始终是正面对着用户，这样就看不出是平面了
    void Show3DTree(int32 i);

    // ----------------------------------------------------------------------------

    /* 城市标识数据 */
    std::unique_ptr<CitySymbolData> pCitySymbolData_;
    // 城市符号
    afx_msg void OnCitySymbolLoad();
    int32 m_iCitySymbolModelNum;
    CArray<PModelStruct, PModelStruct> m_CitySymbolModel;   // 存储所有城市符号信息
    UINT g_citySymbolTex[50];                               // 贴图,纹理
    void ShowCitySymbol(int32 i);
    void LoadPNG(const char* fileName, GLuint& texture);  // NOLINT

    afx_msg void OnMenuAddPointSymbol();
    afx_msg void OnMenuAddPoint3dsmax();
    afx_msg void OnMenuAddPoint2dImg();
    afx_msg void OnMenuAddPoint3dImg();


    /*********************************************************************************************/
    // 线符号
    /*********************************************************************************************/
  private:
    /* SimpleLine */
    std::unique_ptr<SimpleLine> pSimpleLine_;
    int32 m_LineEdit_pointNum;  // 线编辑  选择的点的个数
    Line3 m_line;
    CArray<PLine3, PLine3> m_LinesArray;  // 存放所有的线符号
    //    afx_msg void OnMenuLineAdd();
    //    afx_msg void OnMenuLineFuse();
    //    afx_msg void OnUpdateMenuLineAdd(CCmdUI* pCmdUI);
    //    afx_msg void OnMenuAddLineWidth();
    // --------------------------------------------------------------
    /* L2DRoad */
    std::unique_ptr<L2DRoad> pL2DRoad_;

    LineSymbol* pLineSymbol_;

    int32 line_selected_id;  // 鼠标右击选中的线符号id
    // 更换选中的线符号的属性
    void UpdateLineSymbol(PPR_Point _mp, CPoint point);

    // 三角化并渲染增加宽度后的线符号
    void Line_Area_Triangled(const PArea_4& _area4);

    afx_msg void OnLine2dRoadAdd();
    afx_msg void OnLine2dRoadFuse();
    afx_msg void OnLine2dRoadSet();
    afx_msg void OnUpdateLine2dRoadAdd(CCmdUI* pCmdUI);
    // --------------------------------------------------------------
    /* L3DRoad */
    std::shared_ptr<CDesingScheme> pDesingScheme_;  // 线路设计
    std::unique_ptr<L3DRoad> pL3DRoad_;
    GLuint m_Rail3DwayList;         // 线路三维模型显示列表(透视投影模式)
    CArray<PCordinate, PCordinate> m_TempPts;  // 临时点
    CTexture m_cTxtureBP;       // 路基边坡纹理
    CTexture m_cTxtureLJ;       // 路肩纹理
    CTexture m_cTxtureGdToLJ;   // 道床边坡纹理
    CTexture m_cTxtureRailway;  // 轨道纹理
    CTexture m_cTxturePT;       // 边坡平台纹理
    CTexture m_cFillFaceTxture;  // 断面纹理
    // 实现透视投影模式下的线路三维模型绘制
    void DrawRailwaythesme();
    void fun(PCordinate ppt);
    void fun(PCordinate ppt, PCurve_R_L0_Struct pcrl0);
    // 计算2个向量之间的夹角,由参数返回
    void getDegreeBetween2Vectors(CVector3& v1_Begin/*in*/, CVector3& v1_End/*in*/,  /* NOLINT */
                                  CVector3& v2_Begin/*in*/, CVector3& v2_End/*in*/, float* pDegreeRet/*out*/);  // NOLINT
    afx_msg void OnMenuClearLines();    // 清除所有线路
    void initLines();                       // 初始化线路数据
    void clearLinesData();                  // 清除所有线路数据
    int64 m_linePtnums;      // 当前线路方案设计交点总数
    int64 m_oldlinePtnums;   // 原有线路方案设计交点数
    afx_msg void OnMenuBuild3dlinemodle();
    afx_msg void OnMenuLinedesign();
    afx_msg void OnUpdateMenuLinedesign(CCmdUI* pCmdUI);


    /*********************************************************************************************/
    //        面符号
    /*********************************************************************************************/
  private:
    int32 m_Area_pointNum;                      // 面符号 选择的点的个数
    Area_4 m_area4_forScreenRecord;             // 4边形
    CArray<PArea_4, PArea_4> m_Area4_Array;     // 存放所有的面符号
    vector<Point3> Line_1_JD_vector;
    vector<Point3> Line_2_JD_vector;
    vector<Point3> Line_3_JD_vector;
    vector<Point3> Line_4_JD_vector;
    BOOL Area_fuse_Flag;
    // 多边形三角化
    void Area_Triangled(const PArea_4& _area4);


    // 五角星 ----------------------------------------------
    FiveStar fiveStarSymbol_;


    Point3 fiveStar_o_fromMouseClicked_;

    bool draw_fiveStar_5_area4_;

    CArray<PArea_4, PArea_4> fiveStar_5_area4_array_;

    // -----------------------------------------------------


    UINT m_area_texture;
    void LoadAreaTexture(CString _areaTexture_str, UINT& texture_id);  // 加载面符号纹理  // NOLINT
    // 更换选中的面符号的纹理
    void UpdateAreaTexture(PPR_Point _mp, CPoint point);
    void ScreenToGL2(CPoint point, GLdouble& wx , GLdouble& wz);  // NOLINT
    uint16 area_id;
    // 面符号 - 四边形
    std::unique_ptr<Area4Symbol> pArea4Symbol_;

  public:
    afx_msg LRESULT OnProjectSetted(WPARAM wParam, LPARAM lParam);
    afx_msg void OnMenuAddAreaSlib();
    afx_msg void OnUpdateMenuAddAreaSlib(CCmdUI* pCmdUI);
    afx_msg void OnMenuAreaFuse();
    afx_msg void OnMenuUpdateAreaTexture();
    afx_msg void OnMenuAreaDelete();

    /*********************************************************************************************/
    // Others
    /*********************************************************************************************/
  public:
    CMainFrame* pMain;  // 获取MainFrame类指针
    // 判断是否进行了坐标查询操作
    bool IsSearchPoint_;
    // 将对话框变量赋值给结构体
    void C3DModelParamSetTOPModelStruct(const C3DModelParamSet& model, const PModelStruct& pStruct);
    // 将对话框变量赋值给结构体
    void ModelParamDlgToPModelParamStruct(const ModelParam& model, PModelParamStruct pStruct);
    // 将结构体内容赋值给变量
    void PModelParamStructToModelParamDlg(ModelParam& model, PModelParamStruct pStruct);  // NOLINT
    // 滚轮控制视景窗体的大小（缩小，放大）
    afx_msg BOOL OnMouseWheel(UINT nFlags, int16 zDelta, CPoint pt);
    bool m_bIsLBtnDown;




    afx_msg void OnLine2dRoadAddEnd();
    afx_msg void OnUpdateLine2dRoadFuse(CCmdUI* pCmdUI);
    afx_msg void OnPopupLineDelete();
    afx_msg void OnPopupLineModifyTexture();
    afx_msg void OnPopupLineModifyWidth();
    afx_msg void OnTestCalcFivestarInfo();
};

#ifndef _DEBUG  // 3DSymbolLibNewView.cpp 中的调试版本
inline CMy3DSymbolLibNewDoc* CMy3DSymbolLibNewView::GetDocument() const {
    return reinterpret_cast<CMy3DSymbolLibNewDoc*>(m_pDocument);
}
#endif

#endif  // SYMBOL_LIB_NEW_VIEW_H