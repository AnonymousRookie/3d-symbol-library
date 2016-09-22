#ifndef SYMBOL_LIB_NEW_VIEW_H
#define SYMBOL_LIB_NEW_VIEW_H


#include "MainFrm.h"
#include "SpaceSearchSet.h"
#include "CameraParamSet.h"
#include "TerrainImportContour.h"
#include "SkyBoxTexLoad.h"
#include "Texture.h"
#include "Load3DS.H"
#include "C3DModelParamSet.h"
#include "ModelParam.h"
#include "GLFont.h"
#include <MMSystem.h>
#include "stdafx.h"
#include <cmath>
#include <atlimage.h>
#include <algorithm>
#include "Base/ZTypes.h"
#include "MathUtils/PointPolygonRelationship.h"
#include "MathUtils/Vec3.h"



// SkyBox Tex
enum {TP = 0, LF, BK, RT, FR};

// LINE_ADD 添加线   AREA_ADD 添加面
enum { QUERY_COORDINATE = 0, QUERY_DISTENCE, SELECTLINE, SELECTFLYPATH, LINE_ADD, AREA_ADD}; /*MOUSEMOVE_3DMODEL标识在移动模型，这是select——3dmodel模式下的操作应该暂停*/
enum { SELECT = 0, MOVE, SCALE };
enum {GIS_FLY_STATICHEIGHT = 0, GIS_FLY_PATHHEIGHT};
// model type
enum {MODEL_3DS = 0, MODEL_CITY, MODEL_TREE_3D, MODEL_TREE};
// mouse shape
enum {MOUSE_SHAPE_SLECT = 0, MOUSE_SHAPE_EDIT, MOUSE_SHAPE_ARROW};
// load model type "change parameter" "add new model"
// 新增模型，更新模型
enum {MODEL_NEW, MODEL_CHANGE};


// a 是否为0
#define DOUBLE_NUMBER_IS_ZERO(a) ( ((a)>-0.000001) && ((a)<0.000001) )



// 是否存在已经打开的符号文件
#define EXIST_OPENED_SYMBOLLIB_FILE         1
#define NOT_EXIST_OPENED_SYMBOLLIB_FILE     0


// model select struct
typedef struct {
    int32 modelType;
    int32 modelID;
} SelectedModel, *PSelectedModel;


// 模型结构体,存储各类符号状态
typedef struct {
    CString strModelPath;       // 模型路径
    int32   iModelNum;          // 模型在种类中ID
    int32   xPos;               // 平面水平位置
    int32   zPos;               // 平面Z位置
    float   hPos;               // 底面距离地面高度
    float   radiu;              // 模型旋转半径，距离中心线
    int32   angle;              // 模型绕Y轴旋转
    float   scale;              // 模型缩放因子
    bool    isSelected;         // 模型是否处于选中状态
    int32   iRotateX;           // 模型绕X轴旋转角度
    int32   iRotateY;           // 模型绕Y轴旋转角度
    int32   iRotateZ;           // 模型绕Z轴旋转角度
    int32   iDisplayType;       // 纹理映射方式： 重复  拉伸
} CModelStruct, *PModelStruct;

typedef struct {
    int32 posX;
    int32 posY;
    int32 posZ;
    int32 rotX;
    int32 rotY;
    int32 rotZ;
    float scale;
    CString modelPath;
    bool isDeleted;  // 是否被删除
    int32 modelID;
    bool modelSelected;
    // 3ds模型纹理路径及文件名
    CString m_3DS_Mode_Texture_PATH_NAME;
} CModelParamStruct, *PModelParamStruct;


// 曲线半径,缓和曲线长度(加载场景)
typedef struct Curve_R_L0_Struct {
    int64 curve_R;
    int32 curve_L0;
} Curve_R_L0_Struct, *PCurve_R_L0_Struct;


// 点
typedef struct _Point3 {
    double _x;
    double _y;
    double _z;
} Point3, *PPoint3;

// 线
typedef struct _Line3 {
    Point3 pt1;
    Point3 pt2;
} Line3, *PLine3;


/************************************************************************/
/* 面符号三角化                                                         */
/************************************************************************/

typedef struct _Triangle {
    Point3 pt1;
    Point3 pt2;
    Point3 pt3;
} Triangle, *PTriangle;


// 四边形
typedef struct _Area_4 {
    Point3 pt1;
    Point3 pt2;
    Point3 pt3;
    Point3 pt4;


    // 保存所有多边形内部完整的三角形
    vector<Triangle> TrianglesInPolygonVecotr;
    // 保存所有局部三角化了的三角形(三角形只有1个点在多边形内, 且多边形的某条边与三角形有2个交点)
    vector<Triangle> LocalTrianglesVecotr1;
    // 保存所有局部三角化了的三角形(三角形只有2个点在多边形内, 且多边形的某条边与三角形有2个交点)
    vector<Triangle> LocalTrianglesVecotr2;
    // 保存所有局部三角化了的三角形(三角形只有1个点在多边形内, 且多边形的1个端点在三角形中)
    vector<Triangle> LocalTrianglesVecotr1_1;
    // 保存所有局部三角化了的三角形(三角形只有2个点在多边形内, 且多边形的1个端点在三角形中)
    vector<Triangle> LocalTrianglesVecotr2_1;
    // 保存所有局部三角化了的三角形(某三角形没有点在多边形内, 但多边形的1个端点在三角形中)
    vector<Triangle> LocalTrianglesVecotr_last;

    CString area_texture;
    UINT area_texture_rd;

    uint16 deleted;
} Area_4, *PArea_4;



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
    BOOL bStereoAvailable;      // 显卡是否支持立体显示

    GLfloat m_ViewWideNarrow;   // 用来调整gluPerspective()函数定义平截头体的视野的角度(增大或减小)
    double m_near, m_far;       // gluPerspective()函数定义平截头体的近剪裁平面和远剪裁平面的距离

    float m_FrustumAngle;

    BOOL SetupPixelFormat();
    BOOL InitializeOpenGL(CDC* pDC);

    void InitData();
    afx_msg int32 OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnSize(UINT nType, int32 cx, int32 cy);
    afx_msg void OnContourTerrainImport();

    afx_msg LRESULT OnGoodBye(WPARAM wParam, LPARAM lParam);  // 自定义响应消息,响应模型设置,非模式对话框

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


    // 相机参数变量
    CVector3    m_vEyePosition;     // 相机视点坐标
    CVector3    m_vLook;            // 相机观察点坐标
    CVector3    m_vUp;              // 相机向中三维矢量


    float       m_viewHeight;       // 视点高度
    float       m_oldviewHeight;    // 前一视点高度

    CVector3    m_originLook;       // 相机初始视点坐标
    float       m_viewdegree;       // 观察点与视点之间的俯视角


    // 漫游
    float       rad_xz;             // 角度
    float       g_Angle;            // 方位角
    float       g_elev;             // 仰俯角
    float       gao;

    // 用于计算相机事参数的CVector3类型变量
    Vec3    m_vStrafe;
    CVector3    View;

    void DrawScene();
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

    // 设置绘图模式
    int32 m_Drawmode;
    void SetDrawMode();

    // 天空盒
    bool         iSkyBoxLoaded;
    afx_msg void OnSkyboxTex();
    UINT         g_texSkyBox[5];
    void         CreateSkyBox();
    void         SkyBoxTexture(UINT textur);
    afx_msg void OnUpdateDrawmodeLine(CCmdUI* pCmdUI);
    afx_msg void OnDrawmodeRender();
    afx_msg void OnUpdateDrawmodeRender(CCmdUI* pCmdUI);
    afx_msg void OnUpdateDrawmodeTexture(CCmdUI* pCmdUI);
    afx_msg void OnDrawmodeLine();
    afx_msg void OnDrawmodeTexture();
    afx_msg void OnSpacequerySet();

    // 空间查询标志参数
    int32     m_shizxLength;      // 查询标志的十字线长度
    int32     m_shuzxHeight;      // 查询标志的竖直线长度
    int32     m_QueryLineWidth;   // 查询标志线的宽度
    int32     m_QueryColorR, m_QueryColorG, m_QueryColorB;  // 查询标志线的颜色(红,绿,蓝)

    BYTE    m_QueryType;        // 标识空间查询类别
    BYTE    m_OperateType;      // 模型操作类型

    bool    m_bmouseView;       // 是否起用鼠标控制相机
    POINT   m_oldMousePos;      // 前一鼠标位置

    double  pt1[3], pt2[3];     // 存储查询的坐标
    int32     m_bSearchDistencePtNums;  // 查询时点取的空间点数


    int64 m_linePtnums;      // 当前线路方案设计交点总数
    int64 m_oldlinePtnums;   // 原有线路方案设计交点数


    afx_msg void OnQueryCoordinate();
    afx_msg void OnUpdateQueryCoordinate(CCmdUI* pCmdUI);
    afx_msg void OnQueryDistence();
    afx_msg void OnUpdateQueryDistence(CCmdUI* pCmdUI);

    void ScreenToGL(CPoint point);
    void DrawSearchPoint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

    // 摄像机  键盘控制

    // 相机旋转参数
    float   m_Step_X;   // 相机在X方向移动的步长(鼠标控制)
    float   m_Step_Z;   // 相机在Z方向移动的步长(鼠标控制)

    float   m_xTrans;   // 在X方向上移动的距离(键盘控制)
    float   m_zTrans;   // 在Z方向上移动的距离(键盘控制)
    int32     m_keynumber;  // 标识键盘按键值
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

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

    // 三维漫游
    BOOL m_ShowFlyPath;                                 //  标识是否显示飞行路径
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

    // 显示列表参数
    GLuint m_ClockList;     // 时钟指北针显示列表
    float m_NorthPtangle;   // 指北针初始指向角度
    void InitList();
    void MakeClockList();
    void DrawClock();
    void SetClockProjectionNavigate();
    void PrintText(float x, float y, char* string);
    void GetNorthPtangle();
    void DrawNorthPt();

    GLuint m_SkyList;       // 时钟指北针显示列表
    bool m_bShowbreviary;   // 是否显示缩略视图
    void MakeSkykList();
    void DrawSky();
    void SetSkyProjection();
    void SetSkyProjectionNavigate();

    // 3DS模型
    afx_msg void On3dsModelLoad();

    int32 m_i3DModelNum;


    CArray<PModelParamStruct, PModelParamStruct> m_3DModel;


    /************************************************************************/
    /*                   线路                                               */
    /************************************************************************/

    BOOL b_haveMadeRail3DwayList;   // 是否已经有三维线路显示列表(透视投影模式下)

    Railway m_Railway;              // 线路路基结构
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

    // 绘制中心线(位于地面以下的部分不绘制)
    void DrawCenterLine(int64 index, BOOL ifSelectLine);

    // 绘制边坡
    void DrawBP(int64 index, int32 BPside);

    void fun(PCordinate ppt);
    void fun(PCordinate ppt, PCurve_R_L0_Struct pcrl0);


    // 计算2个向量之间的夹角,由参数返回
    void getDegreeBetween2Vectors(CVector3& v1_Begin/*in*/, CVector3& v1_End/*in*/,  /* NOLINT */
                                  CVector3& v2_Begin/*in*/, CVector3& v2_End/*in*/, float* pDegreeRet/*out*/);  // NOLINT

    void drawFillFace(vector<Railway3DCordinate> fillFacePoints);

    //=====================================================================================


    // 3DS模型
    CLoad3DS*   m_3ds;   // 定义3DS模型


    void Draw3DModel(PModelParamStruct model);

    afx_msg void On3dsModelSelectSet();
    afx_msg void OnUpdate3dsModelSelectSet(CCmdUI* pCmdUI);
    bool bIsSelect3DModel;

    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

    bool bIsMouseMove3DModel;
    afx_msg void On3dsModelMouseMove();
    afx_msg void OnUpdate3dsModelMouseMove(CCmdUI* pCmdUI);
    void JudgeModelSelected(PCordinate ppt);        // 判断模型组中哪些模型被选中,进行状态修改
    int32 m_bMouseMove3DModelPtNums;                // 左键按下数量加一,左键弹起再加一,到2时就可移动模型位置,移动向量为鼠标变动向量


    CMainFrame* pMain;                              // 获取MainFrame类指针

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

    // 城市符号
    afx_msg void OnCitySymbolLoad();
    int32 m_iCitySymbolModelNum;
    CArray<PModelStruct, PModelStruct> m_CitySymbolModel;   // 存储所有城市符号信息
    UINT g_citySymbolTex[50];                               // 贴图,纹理
    void ShowCitySymbol0(int32 i);
    void ShowCitySymbol(int32 i);
    void LoadPNG(const char* fileName, GLuint& texture);  // NOLINT

    // 导入天气纹理 只有一个纹理

    afx_msg void OnWeatherLoad();

    UINT g_weatherTex;          // 贴图,纹理
    void ShowWeather();
    bool bIsWeatherLoad;

    // 判断是否进行了坐标查询操作
    bool IsSearchPoint;

    // 将对话框变量赋值给结构体
    void C3DModelParamSetTOPModelStruct(const C3DModelParamSet& model, const PModelStruct& pStruct);
    // 将对话框变量赋值给结构体
    void ModelParamDlgToPModelParamStruct(const ModelParam& model, PModelParamStruct pStruct);
    // 将结构体内容赋值给变量
    void PModelParamStructToModelParamDlg(ModelParam& model, PModelParamStruct pStruct);  // NOLINT

    // 滚轮控制视景窗体的大小（缩小，放大）
    afx_msg BOOL OnMouseWheel(UINT nFlags, int16 zDelta, CPoint pt);

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

    // 场景配置文件导入
    bool m_bSecneConfig;
    afx_msg void OnSceneLoad();



    CString m_AllDataPath;  // 所有数据文件路径
    CString m_SceneConfig;  // 场景文件夹

    // 地形文件夹，地形纹理文件夹，地形等高文件夹
    CString m_TerrainFolder, m_TerrainTextureFolder, m_TerrainContourFolder;
    // 地形纹理，地形等高图
    CString m_TerrainTexture, m_TerrainContour;
    // SkyBox
    CString m_SkyBoxFolder, m_SkyBoxKindFolder, m_SkyBoxTP, m_SkyBoxLT, m_SkyBoxRT, m_SkyBoxBK, m_SkyBoxFR;

    // 3DS 模型
    CString m_3DModelFolder;
    CString m_3DModelPath;

    float m_3DModelPosX, m_3DModelPosY, m_3DModelPosZ;

    float m_3DModelRotX, m_3DModelRotY, m_3DModelRotZ;
    float m_3DModelScale;


    // 城市标识数据
    CString m_CitySymbolFolder, m_CitySymbolTex;

    float m_CitySymbolPosX, m_CitySymbolPosY, m_CitySymbolPosZ;

    // 景观树数据
    CString m_TreeModelFolder, m_TreeModelTex;

    float m_TreeModelPosX, m_TreeModelPosY, m_TreeModelPosZ;

    // 天气数据
    CString m_WeatherFolder, m_WeatherTex;

    // 天空盒纹理
    void LoadSkyBoxTex(CString skyTP, CString skyLF, CString skyBK, CString skyRT, CString skyFR);
    CString g_texSkyBoxFlieNameTP, g_texSkyBoxFlieNameLF, g_texSkyBoxFlieNameBK, g_texSkyBoxFlieNameRT, g_texSkyBoxFlieNameFR;

    // 地形纹理
    void LoadTerrainTex(CString terrainTex, CString terrainContour);

    // 3D模型设置
    void Load3DModel(PModelParamStruct p3d, int32 iLoadModelType);

    bool m_bIsLBtnDown;
    afx_msg void OnSceneSave();
    bool ScenSave(CString scenePth);

    // 控制选中模型,单个模型选择可以控制所有模型参数设置，组模型选择的话只能移动组合模型
    // 右键按下 弹起 标识

    int32 m_selectedModelID;  // 当前鼠标选中模型ID，当前默认只有3DS模型
    afx_msg void OnModelMove();
    afx_msg void OnModelParam();
    afx_msg void OnModelScale();

    afx_msg void OnConfigureSymbolList();
    afx_msg void OnSystemSetting();
    afx_msg void OnCloseCurrentScene();
    afx_msg void OnModelDelete();
    afx_msg void OnMenuBuild3dlinemodle();
    afx_msg void OnMenuLinedesign();
    afx_msg void OnUpdateMenuLinedesign(CCmdUI* pCmdUI);



    /************************************************************************/
    /* 非3DS模型参数设置的非模式对话框   函数与变量                             */
    /************************************************************************/
  public:
    C3DModelParamSet* paramSet_modeless_dlg;
    void C3DModelParamSetTOPModelStruct(C3DModelParamSet* model, PModelStruct& pStruct);  // NOLINT
    PModelStruct p3dtree;           // 3dtree
    PModelStruct ptree;             // tree
    PModelStruct pCitySymbol;       // CitySymbol
    BOOL m_isSetXYByMouse;

    /************************************************************************/
    /* Variables: 选线阈值设定(距离,夹角)                                       */
    /************************************************************************/
  private:
    // 用于计算2点之间线段长度
    float last_x, last_y, last_z;
    float pre_x,  pre_y,  pre_z;
    // 用于计算2线段间夹角
    CVector3 v1_begin, v1_end;
    CVector3 v2_begin, v2_end;
    // 记录点的个数
    int32 p_count;

    /************************************************************************/
    /* Variables: 曲线要素设定                                              */
    /************************************************************************/
  private:
    int64  m_Curve_R;    // 曲线半径
    int32  m_Curve_L0;   // 缓和曲线长

    float m_distance_between_2_points;  // 当前2点线段间的距离
    float m_pre_distance;               // 前一线段间的距离


  public:
    afx_msg void OnMenuClearLines();    // 清除所有线路

  private:
    void initLines();                       // 初始化线路数据
    void clearLinesData();                  // 清除所有线路数据
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


  private:

    void drawLine(Line3 line);

    // 空间点求投影到平面的直线方程系数ABC, Ax+By+C=0
    void getLine2ABC(double* A, double* B, double* C, Point3 p1, Point3 p2);


    int32 m_LineEdit_pointNum;  // 线编辑  选择的点的个数

    Line3 m_line;

    CArray<PLine3, PLine3> m_LinesArray;  // 存放所有的线符号


    // 计算线段_line所经过的横向和纵向格网数, 及索引范围
    void CalcuateGridNum(int32* rowNum, int32* row_index_begin, int32* row_index_end,
                         int32* colNum, int32* col_index_begin, int32* col_index_end, Line3 _line);

    // 计算平面交点坐标,并计算出交点出的高程值
    void CalcuateJD(int32 rowNum, int32 row_index_begin, int32 row_index_end,
                    int32 colNum, int32 col_index_begin, int32 col_index_end, Line3 _line, vector<Point3>& _pv);  // NOLINT

    // 计算2条直线的交点y=x+b, Ax+By+C=0, 返回-1表示无交点
    BOOL GetJDFrom2Line(PPoint3 p/*out*/, double b, double A, double B, double C);

    vector<Point3> JD_vector1;
    vector<Point3> JD_vector2;
    vector<Point3> JD_vector3;  // 斜线交点

    vector<Point3> Line_a_JD_vector;
    vector<Point3> Line_b_JD_vector;


    BOOL fuse_Flag;

    void DrawJDLine(const vector<Point3>& _pv1,  const vector<Point3>& _pv2);


    // 所有三角形顶点坐标最小最大值
    void GetMinXY(const vector<Point3>& _pv1,  const vector<Point3>& _pv2, double* _minX, double* _minY, double* _maxX, double* _maxY);

    // 线符号纹理坐标
    void GetUV(double _x, double _y, double _minX, double _minY, double _maxX, double _maxY, double* _u, double* _v);


    /************************************************************************/
    /*        面符号                                                            */
    /************************************************************************/
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

    UINT m_area_texture;
    void LoadAreaTexture(CString _areaTexture_str, UINT& texture_id);  // 加载面符号纹理  // NOLINT


    // 更换选中的面符号的纹理
    void UpdateAreaTexture(PPR_Point _mp, CPoint point);
    void ScreenToGL2(CPoint point, GLdouble& wx , GLdouble& wz);  // NOLINT


    uint16 area_id;


    // 存放多边形内的点
    vector<Point3> pointsInPolygonVector;
    vector<Point3> index_pointsInPolygonVector;

    // 计算出所有包含在多边形内的点
    int32 FindAllPointsInPolygon(const Area_4& m_area4);

    // (MAP_W * MAP_W)方阵 1:在多边形内, 0:不在
    int32 inPolygonArrayFlag[MAP_W][MAP_W];


    // 找出所有包含在多边形内的三角形(包括完整三角形和经过局部三角化的三角形)
    int32 FindAllTrianglesInPolygon(Area_4& m_area4);  // NOLINT

    // 只有1个点在多边形形内的三角形(需重新三角化)
    int32 FindTriangles_1_point_inPolygon(Area_4& m_area4);  // NOLINT

    // 只有2个点在多边形形内的三角形(需重新三角化)
    int32 FindTriangles_2_point_inPolygon(Area_4& m_area4);  // NOLINT

    // 有3个点在多边形形内的三角形
    int32 FindTriangles_3_point_inPolygon(Area_4& _area4);  // NOLINT

    // 多边形的一条边  与  三角形  有2个交点, 找出符合条件的三角形
    void Find_triangles_1_line_2_JD(Area_4& m_area4, Triangle& tmp_triangle, CPointPolygonRelationship& tmp_PPR, PPR_Point& tmp_point1, PPR_Point& tmp_point21, PPR_Point& tmp_point22);  // NOLINT



    // 多边形顶点处的三角形
    void FindTriangles_polygon_has_vertex_in_triangle(Area_4& m_area4);  // NOLINT
    void FindTriangles_polygon_has_vertex_in_triangle_1_1(Area_4& m_area4, Triangle& tmp_triangle1, Triangle& tmp_triangle2, PPR_Point& tmp_point1, PPR_Point& tmp_point21, PPR_Point& tmp_point22);  // NOLINT
    void FindTriangles_polygon_has_vertex_in_triangle_2_1(Area_4& m_area4, Triangle& tmp_triangle1, Triangle& tmp_triangle2, Triangle& tmp_triangle3, PPR_Point& tmp_point1, PPR_Point& tmp_point21, PPR_Point& tmp_point22);  // NOLINT
    void FindTriangles_polygon_has_vertex_in_triangle_last(Area_4& m_area4, Triangle& tmp_triangle1, Triangle& tmp_triangle2, Triangle& tmp_triangle3, Triangle& tmp_triangle4, PPR_Point& tmp_point0, PPR_Point& tmp_point1, PPR_Point& tmp_point21, PPR_Point& tmp_point22);  // NOLINT


  public:
    afx_msg LRESULT OnProjectSetted(WPARAM wParam, LPARAM lParam);

  public:
    afx_msg void OnSceneNew();
    afx_msg void OnSceneSaveAs();
    afx_msg void OnMenuLineAdd();
    afx_msg void OnMenuLineFuse();
    afx_msg void OnUpdateMenuLineAdd(CCmdUI* pCmdUI);
    afx_msg void OnMenuAddLineWidth();
    afx_msg void OnMenuAddAreaSlib();
    afx_msg void OnUpdateMenuAddAreaSlib(CCmdUI* pCmdUI);
    afx_msg void OnMenuAreaFuse();
    afx_msg void OnMenuAddPointSymbol();
    afx_msg void OnMenuAddPoint3dsmax();
    afx_msg void OnMenuAddPoint2dImg();
    afx_msg void OnMenuAddPoint3dImg();
    afx_msg void OnMenuUpdateAreaTexture();
    afx_msg void OnMenuAreaDelete();
};

#ifndef _DEBUG  // 3DSymbolLibNewView.cpp 中的调试版本
inline CMy3DSymbolLibNewDoc* CMy3DSymbolLibNewView::GetDocument() const {
    return reinterpret_cast<CMy3DSymbolLibNewDoc*>(m_pDocument);
}
#endif

#endif  // SYMBOL_LIB_NEW_VIEW_H