#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "3DSymbolLibNew.h"
#endif

#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <sstream>
#include "MFCFrameWork/3DSymbolLibNewDoc.h"
#include "3DSymbolLibNewView.h"
#include "Bitmap.h"
#include "PointSymbolLib/ModelParam.h"
#include "PointSymbolLib/DialogModelList.h"
#include "ModelListConfigureDialog.h"
#include "SystemSetting.h"
#include "AreaSymbolLib/AreaClassification.h"
#include "MathUtils/MathUtil.h"
#include "Base/ZStringUtils.h"

extern t3DModel g_3DModel[MODEL_NUM_MAX];

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy3DSymbolLibNewView

IMPLEMENT_DYNCREATE(CMy3DSymbolLibNewView, CView)

BEGIN_MESSAGE_MAP(CMy3DSymbolLibNewView, CView)
    // 标准打印命令
    ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy3DSymbolLibNewView::OnFilePrintPreview)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
    ON_COMMAND(ID_SPACEQUERY_SET, &CMy3DSymbolLibNewView::OnSpacequerySet)
    ON_WM_CREATE()
    ON_WM_DESTROY()
    ON_WM_SIZE()
    ON_COMMAND(ID_CONTOUR_TERRAIN_IMPORT, &CMy3DSymbolLibNewView::OnContourTerrainImport)
    ON_WM_CHAR()
    ON_COMMAND(ID_SKYBOX_TEX, &CMy3DSymbolLibNewView::OnSkyboxTex)
    ON_UPDATE_COMMAND_UI(ID_DRAWMODE_LINE, &CMy3DSymbolLibNewView::OnUpdateDrawmodeLine)
    ON_COMMAND(ID_DRAWMODE_RENDER, &CMy3DSymbolLibNewView::OnDrawmodeRender)
    ON_UPDATE_COMMAND_UI(ID_DRAWMODE_RENDER, &CMy3DSymbolLibNewView::OnUpdateDrawmodeRender)
    ON_UPDATE_COMMAND_UI(ID_DRAWMODE_TEXTURE, &CMy3DSymbolLibNewView::OnUpdateDrawmodeTexture)
    ON_COMMAND(ID_DRAWMODE_LINE, &CMy3DSymbolLibNewView::OnDrawmodeLine)
    ON_COMMAND(ID_DRAWMODE_TEXTURE, &CMy3DSymbolLibNewView::OnDrawmodeTexture)
    ON_COMMAND(ID_QUERY_COORDINATE, &CMy3DSymbolLibNewView::OnQueryCoordinate)
    ON_UPDATE_COMMAND_UI(ID_QUERY_COORDINATE, &CMy3DSymbolLibNewView::OnUpdateQueryCoordinate)
    ON_COMMAND(ID_QUERY_DISTENCE, &CMy3DSymbolLibNewView::OnQueryDistence)
    ON_UPDATE_COMMAND_UI(ID_QUERY_DISTENCE, &CMy3DSymbolLibNewView::OnUpdateQueryDistence)
    ON_WM_LBUTTONDOWN()
    ON_WM_RBUTTONDOWN()
    ON_WM_KEYDOWN()
    ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_CAMERA_PARAM_SET, &CMy3DSymbolLibNewView::OnCameraParamSet)
    ON_COMMAND(ID_PATH_MANUINPUT, &CMy3DSymbolLibNewView::OnPathManuinput)
    ON_COMMAND(ID_FLPPATH_INTERPOLATION, &CMy3DSymbolLibNewView::OnFlppathInterpolation)
    ON_COMMAND(ID_FLYPATH_SAVE, &CMy3DSymbolLibNewView::OnFlypathSave)
    ON_COMMAND(ID_FLY_OPENPATH, &CMy3DSymbolLibNewView::OnFlyOpenpath)
    ON_COMMAND(ID_FLY_ONOFFPATH, &CMy3DSymbolLibNewView::OnFlyOnoffpath)
    ON_UPDATE_COMMAND_UI(ID_FLY_ONOFFPATH, &CMy3DSymbolLibNewView::OnUpdateFlyOnoffpath)
    ON_COMMAND(ID_FLY_STATICHEIGHT, &CMy3DSymbolLibNewView::OnFlyStaticheight)
    ON_UPDATE_COMMAND_UI(ID_FLY_STATICHEIGHT, &CMy3DSymbolLibNewView::OnUpdateFlyStaticheight)
    ON_WM_TIMER()
    ON_COMMAND(ID_FLY_ROUTINEHEIGHT, &CMy3DSymbolLibNewView::OnFlyRoutineheight)
    ON_UPDATE_COMMAND_UI(ID_FLY_ROUTINEHEIGHT, &CMy3DSymbolLibNewView::OnUpdateFlyRoutineheight)
    ON_COMMAND(ID_FLY_PLAYPAUSE, &CMy3DSymbolLibNewView::OnFlyPlaypause)
    ON_UPDATE_COMMAND_UI(ID_FLY_PLAYPAUSE, &CMy3DSymbolLibNewView::OnUpdateFlyPlaypause)
    ON_COMMAND(ID_FLY_STOP, &CMy3DSymbolLibNewView::OnFlyStop)
    ON_COMMAND(ID_FLY_ONESTEP, &CMy3DSymbolLibNewView::OnFlyOnestep)
    ON_COMMAND(ID_FLY_VIEW_ENLARGE, &CMy3DSymbolLibNewView::OnFlyViewEnlarge)
    ON_COMMAND(ID_FLY_VIEW_SMALL, &CMy3DSymbolLibNewView::OnFlyViewSmall)
    ON_COMMAND(ID_FLY_HEIGHT_UP, &CMy3DSymbolLibNewView::OnFlyHeightUp)
    ON_COMMAND(ID_FLY_HEIGHT_DOWN, &CMy3DSymbolLibNewView::OnFlyHeightDown)
    ON_COMMAND(ID_FLY_VIEW_UP, &CMy3DSymbolLibNewView::OnFlyViewUp)
    ON_COMMAND(ID_FLY_VIEW_DOWN, &CMy3DSymbolLibNewView::OnFlyViewDown)
    ON_COMMAND(ID_FLY_SPEED_UP, &CMy3DSymbolLibNewView::OnFlySpeedUp)
    ON_COMMAND(ID_FLY_SPEED_DOWN, &CMy3DSymbolLibNewView::OnFlySpeedDown)
    ON_COMMAND(ID_3DS_MODEL_LOAD, &CMy3DSymbolLibNewView::On3dsModelLoad)
    ON_COMMAND(ID_3DS_MODEL_SELECT_SET, &CMy3DSymbolLibNewView::On3dsModelSelectSet)
    ON_UPDATE_COMMAND_UI(ID_3DS_MODEL_SELECT_SET, &CMy3DSymbolLibNewView::OnUpdate3dsModelSelectSet)
    ON_WM_LBUTTONUP()
    ON_COMMAND(ID_3DS_MODEL_MOUSE_MOVE, &CMy3DSymbolLibNewView::On3dsModelMouseMove)
    ON_UPDATE_COMMAND_UI(ID_3DS_MODEL_MOUSE_MOVE, &CMy3DSymbolLibNewView::OnUpdate3dsModelMouseMove)
    ON_COMMAND(ID_TREE_LOAD, &CMy3DSymbolLibNewView::OnTreeLoad)
    ON_COMMAND(ID_CITY_SYMBOL_LOAD, &CMy3DSymbolLibNewView::OnCitySymbolLoad)
    ON_COMMAND(ID_WEATHER_LOAD, &CMy3DSymbolLibNewView::OnWeatherLoad)
    ON_COMMAND(ID_3D_TREE_LOAD, &CMy3DSymbolLibNewView::On3dTreeLoad)
    ON_WM_MOUSEWHEEL()
    ON_WM_SETCURSOR()
    ON_COMMAND(ID_SCENE_LOAD, &CMy3DSymbolLibNewView::OnSceneLoad)
    ON_COMMAND(ID_SCENE_SAVE, &CMy3DSymbolLibNewView::OnSceneSave)
    ON_COMMAND(ID_MODEL_MOVE, &CMy3DSymbolLibNewView::OnModelMove)
    ON_COMMAND(ID_MODEL_PARAM, &CMy3DSymbolLibNewView::OnModelParam)
    ON_COMMAND(ID_MODEL_SCALE, &CMy3DSymbolLibNewView::OnModelScale)
    ON_COMMAND(ID_CONFIGURE_SYMBOL_LIST, &CMy3DSymbolLibNewView::OnConfigureSymbolList)
    ON_COMMAND(ID_SYSTEM_SETTING, &CMy3DSymbolLibNewView::OnSystemSetting)
    ON_COMMAND(ID_CLOSE_CURRENT_SCENE, &CMy3DSymbolLibNewView::OnCloseCurrentScene)
    ON_COMMAND(ID_MODEL_DELETE, &CMy3DSymbolLibNewView::OnModelDelete)
    ON_COMMAND(ID_MENU_BUILD3DLINEMODLE, &CMy3DSymbolLibNewView::OnMenuBuild3dlinemodle)
    ON_COMMAND(ID_MENU_LINEDESIGN, &CMy3DSymbolLibNewView::OnMenuLinedesign)
    ON_UPDATE_COMMAND_UI(ID_MENU_LINEDESIGN, &CMy3DSymbolLibNewView::OnUpdateMenuLinedesign)
    ON_MESSAGE(WM_GOODBYE, &CMy3DSymbolLibNewView::OnGoodBye)
    ON_COMMAND(ID_MENU_CLEAR_LINES, &CMy3DSymbolLibNewView::OnMenuClearLines)
    ON_COMMAND(ID_SCENE_NEW, &CMy3DSymbolLibNewView::OnSceneNew)
    ON_COMMAND(ID_FILE_SAVE_AS, &CMy3DSymbolLibNewView::OnSceneSaveAs)
    ON_COMMAND(ID_MENU_ADD_AREA_SLIB, &CMy3DSymbolLibNewView::OnMenuAddAreaSlib)
    ON_UPDATE_COMMAND_UI(ID_MENU_ADD_AREA_SLIB, &CMy3DSymbolLibNewView::OnUpdateMenuAddAreaSlib)
    ON_COMMAND(ID_MENU_AREA_FUSE, &CMy3DSymbolLibNewView::OnMenuAreaFuse)
    ON_COMMAND(ID_MENU_ADD_POINT_SYMBOL, &CMy3DSymbolLibNewView::OnMenuAddPointSymbol)
    ON_COMMAND(ID_MENU_ADD_POINT_3DSMAX, &CMy3DSymbolLibNewView::OnMenuAddPoint3dsmax)
    ON_COMMAND(ID_MENU_ADD_POINT_2D_IMG, &CMy3DSymbolLibNewView::OnMenuAddPoint2dImg)
    ON_COMMAND(ID_MENU_ADD_POINT_3D_IMG, &CMy3DSymbolLibNewView::OnMenuAddPoint3dImg)
    ON_MESSAGE(WM_PROJECT_SET_OK, &CMy3DSymbolLibNewView::OnProjectSetted)
    ON_COMMAND(ID_MENU_UPDATE_AREA_TEXTURE, &CMy3DSymbolLibNewView::OnMenuUpdateAreaTexture)
    ON_COMMAND(ID_MENU_AREA_DELETE, &CMy3DSymbolLibNewView::OnMenuAreaDelete)
    ON_COMMAND(ID_LINE_2D_ROAD_ADD, &CMy3DSymbolLibNewView::OnLine2dRoadAdd)
    ON_COMMAND(ID_LINE_2D_ROAD_FUSE, &CMy3DSymbolLibNewView::OnLine2dRoadFuse)
    ON_COMMAND(ID_LINE_2D_ROAD_SET, &CMy3DSymbolLibNewView::OnLine2dRoadSet)
    ON_UPDATE_COMMAND_UI(ID_LINE_2D_ROAD_ADD, &CMy3DSymbolLibNewView::OnUpdateLine2dRoadAdd)
    ON_COMMAND(ID_LINE_2D_ROAD_ADD_END, &CMy3DSymbolLibNewView::OnLine2dRoadAddEnd)
    ON_UPDATE_COMMAND_UI(ID_LINE_2D_ROAD_FUSE, &CMy3DSymbolLibNewView::OnUpdateLine2dRoadFuse)
    ON_COMMAND(ID_POPUP_LINE_DELETE, &CMy3DSymbolLibNewView::OnPopupLineDelete)
    ON_COMMAND(ID_POPUP_LINE_MODIFY_TEXTURE, &CMy3DSymbolLibNewView::OnPopupLineModifyTexture)
    ON_COMMAND(ID_POPUP_LINE_MODIFY_WIDTH, &CMy3DSymbolLibNewView::OnPopupLineModifyWidth)
END_MESSAGE_MAP()


CMy3DSymbolLibNewView::CMy3DSymbolLibNewView()
    : p3ds_(new CLoad3DS),
      bIsSelect3DModel_(false),
      bIsMouseMove3DModel_(false),
      pNClock_(new NClcok),
      pTerrainData_(new TerrainData),
      pCitySymbolData_(new CitySymbolData),
      pTreeModelData_(new TreeModelData),
      pT3DModelData_(new T3DModelData),
      pArea4Symbol_(new Area4Symbol),
      pCamera_(new Camera),
      pSkyBox_(new SkyBox),
      pDesingScheme_(new CDesingScheme),
      pSimpleLine_(new SimpleLine),
      pL3DRoad_(new L3DRoad),
      pL2DRoad_(new L2DRoad),
      pLineSymbol_(nullptr) {}

CMy3DSymbolLibNewView::~CMy3DSymbolLibNewView() {}

BOOL CMy3DSymbolLibNewView::PreCreateWindow(CREATESTRUCT& cs) {  // NOLINT
    //  CREATESTRUCT cs 来修改窗口类或样式
    return CView::PreCreateWindow(cs);
}

// CMy3DSymbolLibNewView 绘制
void CMy3DSymbolLibNewView::OnDraw(CDC* pDC) {
    CMy3DSymbolLibNewDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
    wglMakeCurrent(pDC->m_hDC, m_hRC);      // 使 RC 与当前 DC 相关联
    DrawScene();                            // 场景绘制
    glFlush();
    ::SwapBuffers(m_pDC->GetSafeHdc());     // 交换缓冲区
}

// CMy3DSymbolLibNewView 打印
void CMy3DSymbolLibNewView::OnFilePrintPreview() {
#ifndef SHARED_HANDLERS
    AFXPrintPreview(this);
#endif
}

BOOL CMy3DSymbolLibNewView::OnPreparePrinting(CPrintInfo* pInfo) {
    // 默认准备
    return DoPreparePrinting(pInfo);
}

void CMy3DSymbolLibNewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) {
}

void CMy3DSymbolLibNewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) {
}

void CMy3DSymbolLibNewView::OnRButtonUp(UINT /* nFlags */, CPoint point) {
    // m_bRbtnDown = false;
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CMy3DSymbolLibNewView::OnContextMenu(CWnd* /* pWnd */, CPoint point) {
}

// CMy3DSymbolLibNewView 诊断
#ifdef _DEBUG
void CMy3DSymbolLibNewView::AssertValid() const {
    CView::AssertValid();
}

void CMy3DSymbolLibNewView::Dump(CDumpContext& dc) const {  // NOLINT
    CView::Dump(dc);
}

CMy3DSymbolLibNewDoc* CMy3DSymbolLibNewView::GetDocument() const {  // 非调试版本是内联的
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DSymbolLibNewDoc)));
    return reinterpret_cast<CMy3DSymbolLibNewDoc*>(m_pDocument);
}
#endif  // _DEBUG




// Function: 初始化相关变量
void CMy3DSymbolLibNewView::InitData() {
    glActiveTextureARB = NULL;
    glMultiTexCoord2fARB = NULL;
    m_ViewWideNarrow = 0.0f;                            // 初始飞行视口宽窄变量
    hwnd = GetSafeHwnd();
    CDC* pDestDC = CDC::FromHandle(::GetDC(hwnd));
    m_SCREEN_WIDTH = pDestDC->GetDeviceCaps(HORZRES);   // 屏幕宽度
    m_SCREEN_HEIGHT = pDestDC->GetDeviceCaps(VERTRES);  // 屏幕高度
    m_near = 1;                                         // 观察点与近侧剪裁平面的距离
    m_far = 5000;                                       // 观察点与远侧剪裁平面的距离
    {
        spaceSearchInfo_.m_shizxLength = 2;                                 // 查询标志十字线长度
        spaceSearchInfo_.m_shuzxHeight = 2;                                 // 查询标志竖直线高度
        spaceSearchInfo_.m_QueryLineWidth = 1;                              // 查询标志线的宽度
        spaceSearchInfo_.m_QueryColorR = 255;                               // 查询标志线的颜色(红)
        spaceSearchInfo_.m_QueryColorG = 0;                                 // 查询标志线的颜色(绿)
        spaceSearchInfo_.m_QueryColorB = 0;                                 // 查询标志线的颜色(蓝)
        spaceSearchInfo_.m_bSearchDistencePtNums = 0;
        spaceSearchInfo_.m_QueryType = -1;
    }
    // 渲染模式
    m_Drawmode = 3;
    iTerrainType = 0;
    g_isTerrainInit = false;
    // 初始化相机
    pCamera_->InitCamera();
    derAngleY = 500.0f;
    derAngleZ = 4000.0f;
    derDisScale = 1.5f;
    m_PathFlag = FALSE;
    m_flyspeed = 1000;
    m_maxHeight = -9999;
    m_minHeight = 9999;
    m_ViewUpDown = 0;
    m_FlyPause = FALSE;
    m_fly_start_pause_Enable = FALSE;  // 暂停/开始是否生效
    m_bShowbreviary = TRUE;
    m_bMouseMove3DModelPtNums = 0;
    {
        m_i3DModelNum = 0;
        m_iTreeModelNum = 0;
        m_i3DTreeModelNum = 0;
        m_iCitySymbolModelNum = 0;
    }
    bIsWeatherLoad_ = false;
    IsSearchPoint_ = false;
    // 选中模型线框颜色 初始为红，选中时进行 红 白闪烁效果
    wireR = 1;
    wireG = 0;
    wireB = 0;
    m_bFlash = false;
    m_bMouseMoveSelect = false;
    m_mouseShape = MOUSE_SHAPE_SLECT;
    m_bSecneConfig = false;
    // 选中的模型的id
    m_selectedModelID = -1;
    m_OperateType = -1;
    // checkbox,是否通过鼠标设置模型摆放位置
    m_isSetXYByMouse = 0;
    initLines();  // 初始化线路数据
    // 初始化各种点模型所在路径
    {
        pT3DModelData_->m_3DModelFolder      = "3DModel";
        pCitySymbolData_->m_CitySymbolFolder = "CitySymbol";
        pTreeModelData_->m_TreeModelFolder   = "TreeModel";
    }
    m_LineEdit_pointNum = 0;
    pSimpleLine_->fuse_Flag = FALSE;
    m_Area_pointNum = 0;
    Area_fuse_Flag = FALSE;
    pL2DRoad_->Line_fuse_Flag_ = FALSE;
    m_CurrentProjectName = "";
    {
        // 是否存在已打开的符号文件
        exist_point_flag = FALSE;
        exist_line_flag = FALSE;
        exist_area_flag = FALSE;
        m_PointSymbolFile = "0";
        m_LineSymbolFile = "0";
        m_AreaSymbolFile = "0";
    }
}


// Function: 初始化线路数据
void CMy3DSymbolLibNewView::initLines() {
    pL3DRoad_->InitRoad();
}


BOOL CMy3DSymbolLibNewView::InitializeOpenGL(CDC* pDC) {
    // 进行opengl的初始化工作
    m_pDC = pDC;
    // 首先把DC的象素格式调整为指定的格式，以便后面对DC的使用
    SetupPixelFormat();
    // 根据DC来创建RC
    m_hRC =::wglCreateContext(m_pDC->GetSafeHdc());
    // 设置当前的RC，以后的画图操作都画在m_pDC指向的DC上
    ::wglMakeCurrent(m_pDC->GetSafeHdc() , m_hRC);
    // 判断当前系统的OpenGL版本是否支持多重纹理扩展  判断显卡是否支持该扩展
    glActiveTextureARB      = (PFNGLACTIVETEXTUREARBPROC)       wglGetProcAddress("glActiveTextureARB");
    glMultiTexCoord2fARB    = (PFNGLMULTITEXCOORD2FARBPROC)     wglGetProcAddress("glMultiTexCoord2fARB");
    if (!glActiveTextureARB || !glMultiTexCoord2fARB) {
        // MessageBox("当前OpenGL版本较低，不支持多重纹理\n扩展功能，请下载安装新的版本！" ,  "多重纹理扩展错误" ,  MB_ICONSTOP);
        LOGGER_WARNING << "当前OpenGL版本较低，不支持多重纹理\n扩展功能，请下载安装新的版本！";
        return FALSE;
    }
    return TRUE;
}


BOOL CMy3DSymbolLibNewView::SetupPixelFormat() {
    // 初始化象素格式以及选取合适的格式来创建RC
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR) ,     // pfd结构的大小
        1 ,                                 // 版本号
        PFD_DRAW_TO_WINDOW |                // 支持在窗口中绘图
        PFD_SUPPORT_OPENGL |                // 支持 OpenGL
        PFD_DOUBLEBUFFER |                  // 双缓存模式
        PFD_STEREO |                        // 支持立体模式
        PFD_TYPE_RGBA ,                     // RGBA 颜色模式
        24 ,                                // 24 位颜色深度
        0 ,  0 ,  0 ,  0 ,  0 ,  0 ,        // 忽略颜色位
        0 ,                                 // 没有非透明度缓存
        0 ,                                 // 忽略移位位
        0 ,                                 // 无累加缓存
        0 ,  0 ,  0 ,  0 ,                  // 忽略累加位
        32 ,                                // 32 位深度缓存
        0 ,                                 // 无模板缓存
        0 ,                                 // 无辅助缓存
        PFD_MAIN_PLANE ,                    // 主层
        0 ,                                 // 保留
        0 ,  0 ,  0                         // 忽略层 , 可见性和损毁掩模
    };
    // 在DC中选择合适的象素格式并返回索引号
    int32 pixelformat;
    pixelformat =::ChoosePixelFormat(m_pDC->GetSafeHdc() , &pfd);
    if (pixelformat == 0) {
        MessageBox("选择像素格式失败!" , "设置像素格式" , MB_ICONERROR);
        LOGGER_ERROR << "选择像素格式失败!";
        return FALSE;
    }
    // 设置指定象素格式
    if (::SetPixelFormat(m_pDC->GetSafeHdc() , pixelformat , &pfd) == FALSE) {
        MessageBox("设置像素格式失败!" , "设置像素格式" , MB_ICONERROR);
        LOGGER_ERROR << "设置像素格式失败!";
        return FALSE;
    }
    // 测试当前设置和硬件显卡是否支持立体模式
    unsigned char ucTest;
    glGetBooleanv(GL_STEREO ,  &ucTest);
    if (!ucTest) {
        return 1;
    }
    if ((pfd.dwFlags & PFD_STEREO) == 0)
        bStereoAvailable_ = FALSE;  // 显卡不支持立体模式
    else
        bStereoAvailable_ = TRUE;
    CString stt[5];
    if (bStereoAvailable_ == FALSE) {  // 如果显卡不支持立体模式，给出可能的错误原因
        stt[0] = "①.图形卡不支持立体缓冲;\n";
        stt[1] = "②.图形卡驱动程序不支持立体缓冲;\n";
        stt[2] = "③.只有在特定的解析度或刷新率设置下 , 才可以支持立体缓冲;\n";
        stt[3] = "④.立体缓冲需要特定的驱动配置以激活;";
        stt[4].Format("立体模式未被接受.可能有以下原因:\n%s%s%s%s" , stt[0] , stt[1] , stt[2] , stt[3]);
        MessageBox(stt[4] , "立体模式设置" , MB_ICONINFORMATION);
    }
    return TRUE;
}


int32 CMy3DSymbolLibNewView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;
    pMain = reinterpret_cast<CMainFrame*>(AfxGetApp()->m_pMainWnd);
    // 获取客户区的设备描述表
    m_pDC = new CClientDC(this);
    // 初始化OpenGL
    InitializeOpenGL(m_pDC);
    InitData();
    InitList();  // 初始化显示列表
    return 0;
}


void CMy3DSymbolLibNewView::OnDestroy() {
    ShowCursor(TRUE);                           // 打开鼠标
    if (wglGetCurrentContext() != NULL) {
        wglMakeCurrent(m_pDC->m_hDC, NULL);     // 释放与m_hDC对应的RC
    }
    if (m_hRC != NULL) {
        wglDeleteContext(m_hRC);                // 删除RC
    }
    if (m_pDC)
        delete m_pDC;                           // 释放当前view拥有的DC
    CView::OnDestroy();
}


void CMy3DSymbolLibNewView::OnSize(UINT nType, int32 cx, int32 cy) {
    CView::OnSize(nType, cx, cy);
    if (cy > 0) {
        WinViewX = cx;                              // 视口宽度
        WinViewY = cy;                              // 视口高度
        glViewport(0, 0, cx, cy);                   // 设置视口大小
        float m_aspectRatio = static_cast<float>(cx) / static_cast<float>(cy);  // 视口的横纵比例
        glMatrixMode(GL_PROJECTION);                // 将当前矩阵设置为投影矩阵,指明当前矩阵为GL_PROJECTION
        glLoadIdentity();                           // 将当前矩阵置换为单位阵
        gluPerspective(50.0 + m_ViewWideNarrow , m_aspectRatio , m_near , m_far);  // fovy=50.0 + m_ViewWideNarrow , 是视野角度
        glMatrixMode(GL_MODELVIEW);                 // 将当前矩阵设置为模型矩阵
        glLoadIdentity();                           // 将当前矩阵置换为单位阵
    }
}

// Function: 导入等高线地形数据和纹理
void CMy3DSymbolLibNewView::OnContourTerrainImport() {
    TerrainImportContour dlg;
    if (dlg.DoModal() == IDOK) {
        terrainTexFileName = dlg.m_TerrainContoureTex;
        terrainContourFileName = dlg.m_TerrainContour;
        LoadTerrainTex(terrainTexFileName, terrainContourFileName);
    }
}

// 天空盒 纹理 调入位图到计算机内存texture，只能用于8位（256色）的bmp图形 ,天气预报
bool CMy3DSymbolLibNewView::LoadT8(char* filename, GLuint& texture) {  // NOLINT
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



// Function: 调等高线地势图
unsigned char* CMy3DSymbolLibNewView::LoadBit(char* filename, BITMAPINFOHEADER* bitmap) {
    FILE* filePtr;                                              // 定义位图结构
    BITMAPFILEHEADER  Header;                                   // 定义位图指针
    unsigned char*    Image;                                    // 图形缓存区
    uint32      imageIdx = 0;                                   // 图形索引
    unsigned char     tempRGB;                                  // 交换变量
    filePtr = fopen(filename, "rb");                            // 读文件
    if (filePtr == NULL)    return NULL;                        // 读文件出错返回
    fread(&Header, sizeof(BITMAPFILEHEADER), 1, filePtr);       // 读位图结构
    if (Header.bfType != BITMAP_ID) {                           // 不是BMP位图
        fclose(filePtr);                                        // 关闭文件
        return NULL;                                            // 返回空
    }
    fread(bitmap, sizeof(BITMAPINFOHEADER), 1, filePtr);        // 读位图结构
    fseek(filePtr, Header.bfOffBits, SEEK_SET);                 // 移动文件指针到数据区
    Image = (unsigned char*)malloc(bitmap->biSizeImage);        // 申请图形区
    if (!Image) {                                               // 申请图形区失败
        free(Image);                                            // 释放图形区
        fclose(filePtr);                                        // 关闭文件
        return NULL;                                            // 返回空
    }
    fread(Image, 1, bitmap->biSizeImage, filePtr);              // 将图形数据读入
    for (imageIdx = 0; imageIdx < bitmap->biSizeImage; imageIdx += 3) {
        tempRGB = Image[imageIdx];
        Image[imageIdx] = Image[imageIdx + 2];
        Image[imageIdx + 2] = tempRGB;
    }                                                           // 交换数据
    fclose(filePtr);                                            // 关闭文件
    return Image;                                               // 返回图形数据
}


void CMy3DSymbolLibNewView::InitTerrain() {
    // 读取等高线数据
    terrainContourData_.clear();
    std::ifstream t("C:\\128x128.txt");
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    std::vector<std::string> row = StringUtils::split(str, '\n');
    for (auto iter = row.begin(); iter != row.end(); ++iter) {
        std::vector<std::string> tmp = StringUtils::split(*iter, ',');
        for (auto it = tmp.begin(); it != tmp.end(); ++it) {
            terrainContourData_.push_back(StringUtils::stringToFloat(*it));
        }
        cout << endl;
    }
    // init terrain
    int32 index = 0;
    int32 Vertex = 0;
    for (int32 z = 0; z < MAP_W; ++z)
        for (int32 x = 0; x < MAP_W; ++x) {                                             // MAP_W是地形块数，32行，32列的方形地形
            Vertex = z * MAP_W + x;
            g_terrain [Vertex][0] = static_cast<float>(x) * MAP_SCALE;                  // 地域数组 3维，MAP_SCALE是边长
            // g_terrain [Vertex][1] = static_cast<float>(g_imageData[Vertex * 3] / 3);    // 地域数组 3维 灰度等高线生成高度图，在Modelobj初始化就赋值了
            g_terrain [Vertex][1] = static_cast<float>(terrainContourData_.at(Vertex));    // 地域数组 3维 灰度等高线生成高度图，在Modelobj初始化就赋值了
            g_terrain [Vertex][2] = -static_cast<float>(z) * MAP_SCALE;                 // 地域数组 3维
            g_texcoord[Vertex][0] = static_cast<float>(x);                              // 索引数组2维，指示曲面贴图的平面坐标
            g_texcoord[Vertex][1] = static_cast<float>(z);
            g_index [index++] = Vertex;                                                 // 顶点数组1维，曲面顶点，一维顶点数组加快显示
            g_index [index++] = Vertex + MAP_W;
            // 获取地形高度极值
            if (m_maxHeight < g_terrain [Vertex][1]) {
                m_maxHeight = g_terrain [Vertex][1];
            }
            if (m_minHeight > g_terrain [Vertex][1]) {
                m_minHeight = g_terrain [Vertex][1];
            }
            g_max_height = m_maxHeight;  // 保存最大高程值到全局变量中
        }
    // 顶点数组  第一步 启用数组
    glEnableClientState(GL_VERTEX_ARRAY);                   // 允许使用地域数组
    // 顶点数组  第二步 制定数组数据
    glVertexPointer(3, GL_FLOAT, 0, g_terrain);             // 装入地域数据
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);            // 允许使用索引数组
    glTexCoordPointer(2, GL_FLOAT, 0, g_texcoord);          // 装入索引数组
}


// Function: 三维地形绘制   ,利用glDrawElements快速绘制排列好的顶点地形
void CMy3DSymbolLibNewView::DrawTerrain() {
    // glShadeModel函数用来设置阴影的效果，GL_SMOOTH为默认值，表示平滑阴影效果；
    glShadeModel(GL_SMOOTH);
    SetDrawMode();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0 + m_ViewWideNarrow , static_cast<float>(WinViewX) / static_cast<float>(WinViewY), m_near , m_far);
    glMatrixMode(GL_MODELVIEW);  // 定义矩阵为模型模型矩阵
    glLoadIdentity();            // 将当前矩阵置换为单位矩阵
    /*glClearDepth函数设置深度缓冲区的，它的含义就在OpenGL窗口绘制的图形深入到屏幕中的程度，
    深度的意义就是在三维空间中的z坐标的数值，z取0时表示在平面上，你就看不到窗口中的图形了，
    所以负值越小，越远离窗口平面向里，说明窗口中的图形离我们观察者的距离变远了；*/
    glClearDepth(1.0f);         // 设置初始化深度缓存值
    glEnable(GL_DEPTH_TEST);    // 启用深度测试
    glDepthFunc(GL_LESS);       // 在调用glEnable(GL_DEPTH_TEST); 开启这个功能以后，当深度变化小于当前深度值时，更新深度值。
    SetCamra();
    glViewport(0 ,  0 ,  WinViewX ,  WinViewY);  // 设置视口大小和位置
    glBindTexture(GL_TEXTURE_2D, texTerrain);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    for (int32 z = 0; z < MAP_W - 1; z++) {
        glDrawElements(GL_TRIANGLE_STRIP, MAP_W * 2, GL_UNSIGNED_INT, &g_index[z * MAP_W * 2]);
    }
    if (m_bShowbreviary) {  // 显示缩略视图
        glViewport(WinViewX * 5 / 6,  WinViewY * 5 / 6, WinViewX / 6,  WinViewY / 6);
        glBindTexture(GL_TEXTURE_2D, texTerrain);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        for (int32 z = 0; z < MAP_W - 1; ++z) {
            // 顶点数组  第三步 渲染
            glDrawElements(GL_TRIANGLE_STRIP, MAP_W * 2, GL_UNSIGNED_INT, &g_index[z * MAP_W * 2]);
        }
        glViewport(0, 0, WinViewX, WinViewY);  // 重新设置视口大小
    }
}

// Function: 获取地面高度
float CMy3DSymbolLibNewView::GetHeight(float x, float z) {
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

void CMy3DSymbolLibNewView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
    if (nChar == 'W' || nChar == 'w') {
        m_Drawmode = 1;
    }
    if (nChar == 'F' || nChar == 'f') {
        m_Drawmode = 2;
    }
    if (nChar == 'T' || nChar == 't') {
        m_Drawmode = 3;
    }
    Invalidate(FALSE);
    CView::OnChar(nChar, nRepCnt, nFlags);
}


// Function:设置绘图模式
void  CMy3DSymbolLibNewView::SetDrawMode() {
    switch (m_Drawmode) {  // 绘制模式
        case 1:  // 线框模式
            glDisable(GL_TEXTURE_2D);  // 关闭纹理功能
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        case 2:  // 渲晕模式
            glDisable(GL_TEXTURE_2D);  // 开启纹理功能
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
        case 3:  // 纹理模式
            glEnable(GL_TEXTURE_2D);  // 开启纹理功能
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
    }
}

// Function:场景绘制
void CMy3DSymbolLibNewView::DrawScene() {
    glClearColor(0.53, 0.81, 0.92, 0.0);                 // 设置刷新背景色SkyBlue: 135,206,235
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // 刷新背景
    glLoadIdentity();                                    // 重置当前的模型观察矩阵
    SetDrawMode();
    if (pCamera_->m_vEyePosition.x <  MAP_SCALE) {
        pCamera_->m_vEyePosition.x = MAP_SCALE;
    }
    if (pCamera_->m_vEyePosition.x > (MAP_W - 2) * MAP_SCALE) {
        pCamera_->m_vEyePosition.x = (MAP_W - 2) * MAP_SCALE;
    }
    if (pCamera_->m_vEyePosition.z < -(MAP_W - 2) * MAP_SCALE) {
        pCamera_->m_vEyePosition.z = -(MAP_W - 2) * MAP_SCALE;
    }
    if (pCamera_->m_vEyePosition.z > -MAP_SCALE) {
        pCamera_->m_vEyePosition.z = -MAP_SCALE;
    }
    SetCamra();
    if (iTerrainType != 0) {
        if (pSkyBox_->iSkyBoxLoaded_) {
            DrawSky();
        }
        DrawClock();            // 绘制指北针
        DrawTerrain();
        DrawFlyPath();
        DrawRailwaythesme();    // 绘制铁路
        if (spaceSearchInfo_.m_QueryType == QUERY_COORDINATE || spaceSearchInfo_.m_QueryType == QUERY_DISTENCE || spaceSearchInfo_.m_QueryType == SELECTLINE
                || spaceSearchInfo_.m_QueryType == LINE_ADD  // Line
                || spaceSearchInfo_.m_QueryType == AREA_ADD  // Area
           ) {
            DrawSearchPoint();  // 绘制空间查询标志
        }
        if (pSimpleLine_->fuse_Flag) {
            pSimpleLine_->DrawJDLine(pSimpleLine_->Line_a_JD_vector, pSimpleLine_->Line_b_JD_vector);
        }
        if (Area_fuse_Flag) {
            int32 tmp_size = m_Area4_Array.GetSize();
            for (int32 i = 0; i < tmp_size; ++i) {
                if (m_Area4_Array[i]->deleted != 1) {
                    Area_Triangled(m_Area4_Array[i]);
                }
            }
        }
        // if (pL2DRoad_->Line_fuse_Flag_) {
        //    for (uint32 i = 0; i < pL2DRoad_->allLineArea4Array_.size(); ++i) {
        //        auto pLineArea4Array = pL2DRoad_->allLineArea4Array_.at(i);
        //        //
        //        int32 tmp_size = pLineArea4Array->GetSize();
        //        for (int32 i = 0; i < tmp_size; ++i) {
        //            if ((*pLineArea4Array)[i]->deleted != 1) {
        //                Line_Area_Triangled((*pLineArea4Array)[i]);
        //            }
        //        }
        //    }
        // }
        if (pL2DRoad_->Line_fuse_Flag_) {
            for (auto iter = pL2DRoad_->allLineArea4Array_.begin(); iter != pL2DRoad_->allLineArea4Array_.end(); ++iter) {
                auto pLineArea4Array = (*iter).second;
                //
                int32 tmp_size = pLineArea4Array->GetSize();
                for (int32 i = 0; i < tmp_size; ++i) {
                    if ((*pLineArea4Array)[i]->deleted != 1) {
                        Line_Area_Triangled((*pLineArea4Array)[i]);
                    }
                }
            }
        }
        // ---------------------------------------------------------
        // 显示景观树
        glPushMatrix();
        if (m_TreeModel.GetSize() > 0) {
            for (int32 i = 0; i < m_TreeModel.GetSize(); i++) {
                ShowTree(i);
            }
        }
        glPopMatrix();
        // ---------------------------------------------------------
        // 显示3D景观树
        glPushMatrix();
        if (m_3DTreeModel.GetSize() > 0) {
            for (int32 i = 0; i < m_3DTreeModel.GetSize(); i++) {
                Show3DTree(i);
            }
        }
        glPopMatrix();
        // ---------------------------------------------------------
        // 显示城市符号
        glPushMatrix();
        if (m_CitySymbolModel.GetSize() > 0) {
            for (int32 i = 0; i < m_CitySymbolModel.GetSize(); i++) {
                ShowCitySymbol(i);
            }
        }
        glPopMatrix();
        // ---------------------------------------------------------
        glPushMatrix();
        if (bIsWeatherLoad_) {
            ShowWeather();
        }
        glPopMatrix();
        // ---------------------------------------------------------
        glPushMatrix();
        glPushAttrib(GL_CURRENT_COLOR);
        if (m_3DModel.GetSize() > 0) {
            for (int32 i = 0; i < m_3DModel.GetSize(); i++)
                if (m_3DModel.GetAt(i)->isDeleted == false) {
                    Draw3DModel(m_3DModel.GetAt(i));
                }
        }
        glPopAttrib();
        glPopMatrix();
        // ---------------------------------------------------------
        if (m_flypathPtIndex > 0) {
            TextFlyHelp();
        }
    }
    GLfloat light_position[] = {pCamera_->m_vEyePosition.x, 300, pCamera_->m_vEyePosition.z - 100};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    GLfloat lightAmbient[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat lightDiffuse[]   = {1.0, 1.0, 1.0, 1.0};
    GLfloat lightSpecular[] = {0, 0, 0, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
}

// Function:天空盒纹理导入以及参数设置
void CMy3DSymbolLibNewView::OnSkyboxTex() {
    CSkyBoxTexLoad dlg;
    if (dlg.DoModal() == IDOK) {
        g_texSkyBoxFlieNameTP = dlg.m_SkyBoxTexTP;
        g_texSkyBoxFlieNameLF = dlg.m_SkyBoxTexLF;
        g_texSkyBoxFlieNameBK = dlg.m_SkyBoxTexBK;
        g_texSkyBoxFlieNameRT = dlg.m_SkyBoxTexRT;
        g_texSkyBoxFlieNameFR = dlg.m_SkyBoxTexFR;
        LoadSkyBoxTex(g_texSkyBoxFlieNameTP, g_texSkyBoxFlieNameLF, g_texSkyBoxFlieNameBK, g_texSkyBoxFlieNameRT, g_texSkyBoxFlieNameFR);
    }
}

void CMy3DSymbolLibNewView::OnDrawmodeLine() {
    m_Drawmode = 1;
    // just for test -----------------------------
    // end test -----------------------------
    Invalidate(FALSE);
}

void CMy3DSymbolLibNewView::OnUpdateDrawmodeLine(CCmdUI* pCmdUI) {
    pCmdUI->SetCheck(m_Drawmode == 1);  // 根据m_ViewType值是否设置选中标志
}

void CMy3DSymbolLibNewView::OnDrawmodeRender() {
    m_Drawmode = 2;
    Invalidate(FALSE);
}

void CMy3DSymbolLibNewView::OnUpdateDrawmodeRender(CCmdUI* pCmdUI) {
    pCmdUI->SetCheck(m_Drawmode == 2);  // 根据m_ViewType值是否设置选中标志
}

void CMy3DSymbolLibNewView::OnDrawmodeTexture() {
    m_Drawmode = 3;
    Invalidate(FALSE);
}

void CMy3DSymbolLibNewView::OnUpdateDrawmodeTexture(CCmdUI* pCmdUI) {
    pCmdUI->SetCheck(m_Drawmode == 3);  // 根据m_ViewType值是否设置选中标志
}

// Function:空间查询标志设置
void CMy3DSymbolLibNewView::OnSpacequerySet() {
    CSpaceSearchSet dlg;
    dlg.spaceSearchInfo_.m_shizxLength = spaceSearchInfo_.m_shizxLength;      // 查询标志十字线长度
    dlg.spaceSearchInfo_.m_shuzxHeight = spaceSearchInfo_.m_shuzxHeight;      // 查询标志竖直线高度
    dlg.spaceSearchInfo_.m_QueryLineWidth = spaceSearchInfo_.m_QueryLineWidth;  // 查询标志线的宽度
    dlg.spaceSearchInfo_.m_QueryColorR = spaceSearchInfo_.m_QueryColorR;      // 查询标志线的颜色(红)
    dlg.spaceSearchInfo_.m_QueryColorG = spaceSearchInfo_.m_QueryColorG;      // 查询标志线的颜色(绿)
    dlg.spaceSearchInfo_.m_QueryColorB = spaceSearchInfo_.m_QueryColorB;      // 查询标志线的颜色(蓝)
    if (dlg.DoModal() == IDOK) {
        spaceSearchInfo_.m_shizxLength = dlg.spaceSearchInfo_.m_shizxLength;              // 得到新设置的查询标志十字线长度
        spaceSearchInfo_.m_shuzxHeight = dlg.spaceSearchInfo_.m_shuzxHeight;              // 得到新设置的查询标志竖直线高度
        spaceSearchInfo_.m_QueryLineWidth = dlg.spaceSearchInfo_.m_QueryLineWidth + 1;    // 得到新设置的查询标志线的宽度，下标从0开始
        spaceSearchInfo_.m_QueryColorR = dlg.spaceSearchInfo_.m_QueryColorR;              // 得到新设置的查询标志线的颜色(红)
        spaceSearchInfo_.m_QueryColorG = dlg.spaceSearchInfo_.m_QueryColorG;              // 得到新设置的查询标志线的颜色(绿)
        spaceSearchInfo_.m_QueryColorB = dlg.spaceSearchInfo_.m_QueryColorB;              // 得到新设置的//查询标志线的颜色(蓝)
    }
}

// Function: 查询三维坐标
void CMy3DSymbolLibNewView::OnQueryCoordinate() {
    // 如果当前已经是查询三维坐标状态，则关闭; 如果当前已经不是查询三维坐标状态，则打开
    spaceSearchInfo_.m_QueryType = (QUERY_COORDINATE == spaceSearchInfo_.m_QueryType) ? -1 : QUERY_COORDINATE;
    m_OperateType = -1;
}

// Function: 设置是否选中状态
void CMy3DSymbolLibNewView::OnUpdateQueryCoordinate(CCmdUI* pCmdUI) {
    pCmdUI->SetCheck(spaceSearchInfo_.m_QueryType == QUERY_COORDINATE);
}

void CMy3DSymbolLibNewView::OnQueryDistence() {
    // 如果当前已经是查询空间距离状态，则关闭; 如果当前不是查询空间距离状态，则关闭，则打开
    spaceSearchInfo_.m_QueryType = (QUERY_DISTENCE == spaceSearchInfo_.m_QueryType) ? -1 : QUERY_DISTENCE;
}

void CMy3DSymbolLibNewView::OnUpdateQueryDistence(CCmdUI* pCmdUI) {
    pCmdUI->SetCheck(spaceSearchInfo_.m_QueryType == QUERY_DISTENCE);
}




/********************************************************/
// Function: 屏幕坐标 ==> 三维坐标
void CMy3DSymbolLibNewView::ScreenToGL(CPoint point) {
    int32 mouse_x = point.x;
    int32 mouse_y = point.y;
    GLint viewport[4];
    GLdouble modelview[16], projection[16];
    GLdouble wx, wy, wz;
    float winX, winY, winZ;
    glPushMatrix();
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);
    glPopMatrix();
    winX = static_cast<float>(mouse_x);
    winY = static_cast<float>(viewport[3]) - static_cast<float>(mouse_y) - 1;
    glReadPixels(mouse_x, static_cast<int32>(winY), 1, 1,
                 GL_DEPTH_COMPONENT, GL_FLOAT,
                 &winZ);  // 获取深度值，只有在有渲染的地方才能准确获取，一旦没有渲染点就不能获取正确值
    // 逆变换和模拟变换
    gluUnProject((GLdouble)winX, (GLdouble)winY, (GLdouble)winZ, modelview, projection, viewport, &wx, &wy, &wz);
    // 3D坐标点范围限制
    if (wx <  MAP_SCALE) {
        wx =  MAP_SCALE;                // X边
    }
    if (wx > (MAP_W - 1)*MAP_SCALE) {
        wx = (MAP_W - 1) * MAP_SCALE;   // X边
    }
    if (wz < -(MAP_W - 1)*MAP_SCALE) {
        wz = -(MAP_W - 1) * MAP_SCALE;  // Z边
    }
    if (wz > -MAP_SCALE) {
        wz = -MAP_SCALE;                // Z边
    }
    CMainFrame* pMainFrame = reinterpret_cast<CMainFrame*>(GetParent());
    CString strText;
    // 在状态栏指示器上显示相关信息(鼠标所点击处在三维场景中的坐标)
    strText.Format("鼠标坐标:x=%.3f, y=%.3f, z=%.3f", wx, wy, wz);
    pMainFrame->Set_BarText(4 , strText);
    CString tt;
    if (winZ >= 0 && winZ < 1.0) {
        if (m_isSetXYByMouse) {  // 通过鼠标设置模型摆放位置
            pt1[0] = wx;
            pt1[1] = wy;
            pt1[2] = wz;
            if (paramSet_modeless_dlg) {
                paramSet_modeless_dlg->xPos = pt1[0];
                paramSet_modeless_dlg->zPos = pt1[2];
                ::PostMessage(paramSet_modeless_dlg->GetSafeHwnd(), WM_UPDATE_EDIT_XY, 0, 0);
            }
        }
        if (spaceSearchInfo_.m_QueryType == QUERY_COORDINATE) {  // 查询三维坐标
            tt.Format("当前坐标(x,y,z)=(%.3f,%.3f,%.3f)", wx, wy, -wz);
            pt1[0] = wx;
            pt1[1] = wy;
            pt1[2] = wz;                                            // 查询获得的三维大地坐标
            Invalidate(FALSE);
            MessageBox(tt, "三维坐标查询", MB_ICONINFORMATION);      // 给出坐标查询信息
            IsSearchPoint_ = true;
        } else if (spaceSearchInfo_.m_QueryType == QUERY_DISTENCE) {                 // 查询空间距离
            if (spaceSearchInfo_.m_bSearchDistencePtNums >= 2) {                     // 如果选择点数2个，归零
                spaceSearchInfo_.m_bSearchDistencePtNums = 0;
            }
            spaceSearchInfo_.m_bSearchDistencePtNums++;                              // 选择点数 + 1
            if (spaceSearchInfo_.m_bSearchDistencePtNums == 1) {                     // 如果只选择了1个点
                pt1[0] = wx;
                pt1[1] = wy;
                pt1[2] = wz;                                        // 将三维点坐标存储到数组 pt1[] 里面
            } else {                                                // 选择了两个点，则表示可以计算空间距离了
                pt2[0] = wx;
                pt2[1] = wy;
                pt2[2] = wz;                                        // 将三维点坐标存储到数组 pt2[] 里面
                // 计算距离
                double mdistence = sqrt((pt2[0] - pt1[0]) * (pt2[0] - pt1[0]) + (pt2[1] - pt1[1]) * (pt2[1] - pt1[1]) + (pt2[2] - pt1[2]) * (pt2[2] - pt1[2]));
                tt.Format("两点为:\n(x1,y1,z1)=(%.3f,%.3f,%.3f)\n(x2,y2,z2)=(%.3f,%.3f,%.3f)\n距离Dis=%.3f", pt1[0], pt1[1], pt1[2], pt2[0], pt2[1], pt2[2], mdistence);
            }
            Invalidate(FALSE);
            MessageBox(tt, "三维距离查询", MB_ICONINFORMATION);       // 给出距离查询信息
            // SimpleLine
            // } else if (spaceSearchInfo_.m_QueryType == LINE_ADD) {                        // 线编辑  添加线
            //    ++m_LineEdit_pointNum;                                   // 选择点数 + 1
            //    if (m_LineEdit_pointNum == 1) {                          // 如果只选择了1个点
            //        m_line.pt1 = Point3(wx, wy, wz);
            //    } else if (m_LineEdit_pointNum == 2) {
            //        m_line.pt2 = Point3(wx, wy, wz);
            //    }
            //    if (m_LineEdit_pointNum >= 2) {     // 如果选择点数2个，归零
            //        m_LineEdit_pointNum = 0;
            //        PLine3 line = new Line3;
            //        line->pt1 = m_line.pt1;
            //        line->pt2 = m_line.pt2;
            //        m_LinesArray.Add(line);
            //    }
            // L2DRoad
        } else if (spaceSearchInfo_.m_QueryType == LINE_ADD) {                        // 线编辑  添加线
            Point3 p(wx, wy, wz);
            pLineSymbol_->line_type_ = 1;
            pLineSymbol_->line_points_.push_back(p);
        } else if (spaceSearchInfo_.m_QueryType == AREA_ADD) {   // 选取面符号上的点
            m_Area_pointNum++;                  // 选择点数 + 1
            if (m_Area_pointNum == 1) {
                m_area4_forScreenRecord.pt1 = Point3(wx, wy, wz);
            } else if (m_Area_pointNum == 2) {
                m_area4_forScreenRecord.pt2 = Point3(wx, wy, wz);
            } else if (m_Area_pointNum == 3) {
                m_area4_forScreenRecord.pt3 = Point3(wx, wy, wz);
            } else if (m_Area_pointNum == 4) {
                m_area4_forScreenRecord.pt4 = Point3(wx, wy, wz);
            }
            if (m_Area_pointNum >= 4) {  // 如果选择点数4个，归零
                m_Area_pointNum = 0;
                PArea_4 area = new Area_4;
                area->pt1 = m_area4_forScreenRecord.pt1;
                area->pt2 = m_area4_forScreenRecord.pt2;
                area->pt3 = m_area4_forScreenRecord.pt3;
                area->pt4 = m_area4_forScreenRecord.pt4;
                area->area_texture = "";
                area->deleted = 0;
                m_Area4_Array.Add(area);
            }
        } else if (spaceSearchInfo_.m_QueryType == SELECTLINE) {         // 如果是三维选线设计
            PCordinate ppt = new Cordinate;
            float tmpH = 0;                             // (x,z)处高程值
            float* pDegree = new float(0);              // 通过函数参数返回夹角的值
            const float threshold_distance = 100.0f;    // 2点间最短距离
            // 2线段间最小夹角
            const float threshold_degree = 20;
            CString warningMsg;
            if ((ppt == nullptr)) {
                AfxMessageBox("Failed to add a new ppt");
                LOGGER_ERROR << "Failed to add a new ppt";
                delete pDegree;
                return;
            }
            {
                // 记录设计交点三维坐标
                ppt->x = wx;
                // 设置(x,z)处的高程值
                tmpH = 70;
                ppt->y = tmpH;
                ppt->z = wz;
            }
            tmpH = GetHeight(wx, wz);
            if (m_maxHeight - tmpH < 10) {
                warningMsg.Format(_T("此处地势太高,请重新选取!"));
                LOGGER_WARNING << "此处地势太高,请重新选取!";
                AfxMessageBox(warningMsg);
            } else {
                // 设计线路时确保2端点间的距离 > threshold_distance
                if (pL3DRoad_->p_count == 0) {
                    pL3DRoad_->pre_x = ppt->x;
                    pL3DRoad_->pre_y = tmpH;
                    pL3DRoad_->pre_z = ppt->z;
                    fun(ppt);
                    ++pL3DRoad_->p_count;
                } else if (pL3DRoad_->p_count >= 1) {
                    if (pL3DRoad_->m_distance_between_2_points > threshold_distance) {
                        pL3DRoad_->m_pre_distance = pL3DRoad_->m_distance_between_2_points;
                    }
                    pL3DRoad_->last_x = ppt->x;
                    pL3DRoad_->last_y = tmpH;
                    pL3DRoad_->last_z = ppt->z;
                    pL3DRoad_->m_distance_between_2_points = static_cast<float>(sqrt((pL3DRoad_->last_x - pL3DRoad_->pre_x) * (pL3DRoad_->last_x - pL3DRoad_->pre_x) + (pL3DRoad_->last_y - pL3DRoad_->pre_y) * (pL3DRoad_->last_y - pL3DRoad_->pre_y) + (pL3DRoad_->last_z - pL3DRoad_->pre_z) * (pL3DRoad_->last_z - pL3DRoad_->pre_z)));
                    if (pL3DRoad_->m_distance_between_2_points > threshold_distance) {  // 距离阈值
                        if (pL3DRoad_->p_count == 1) {
                            fun(ppt);
                            ++pL3DRoad_->p_count;
                            pL3DRoad_->v1_end.x = pL3DRoad_->pre_x;
                            pL3DRoad_->v1_end.y = 0;
                            pL3DRoad_->v1_end.z = pL3DRoad_->pre_z;
                            pL3DRoad_->v1_begin.x = pL3DRoad_->last_x;
                            pL3DRoad_->v1_begin.y = 0;
                            pL3DRoad_->v1_begin.z = pL3DRoad_->last_z;
                            pL3DRoad_->pre_x = ppt->x;
                            pL3DRoad_->pre_y = tmpH;
                            pL3DRoad_->pre_z = ppt->z;
                        } else {
                            pL3DRoad_->v2_begin = pL3DRoad_->v1_begin;
                            pL3DRoad_->v2_end.x = pL3DRoad_->last_x;
                            pL3DRoad_->v2_end.y = 0;
                            pL3DRoad_->v2_end.z = pL3DRoad_->last_z;
                            // 计算2个向量之间的夹角, 通过指针作函数参数返回
                            getDegreeBetween2Vectors(pL3DRoad_->v1_begin, pL3DRoad_->v1_end, pL3DRoad_->v2_begin, pL3DRoad_->v2_end, pDegree);
                            if (*pDegree > threshold_degree) {  // 夹角阈值
                                pL3DRoad_->v1_end.x = pL3DRoad_->pre_x;
                                pL3DRoad_->v1_end.y = 0;
                                pL3DRoad_->v1_end.z = pL3DRoad_->pre_z;
                                pL3DRoad_->v1_begin.x = pL3DRoad_->last_x;
                                pL3DRoad_->v1_begin.y = 0;
                                pL3DRoad_->v1_begin.z = pL3DRoad_->last_z;
                                float min_distance_between_2_lines = (pL3DRoad_->m_pre_distance < pL3DRoad_->m_distance_between_2_points ? pL3DRoad_->m_pre_distance : pL3DRoad_->m_distance_between_2_points);
                                if (*pDegree < 30) {
                                    pL3DRoad_->m_Curve_R = INIT_CURVE_R;
                                    pL3DRoad_->m_Curve_L0 = INIT_CURVE_L0;
                                } else {
                                    pL3DRoad_->m_Curve_R = min_distance_between_2_lines * tan((*pDegree / 2.13) * PAI / 180);
                                    pL3DRoad_->m_Curve_L0 = 6 * pL3DRoad_->m_Curve_R / 100;
                                    if (pL3DRoad_->m_Curve_L0 < 1)
                                        pL3DRoad_->m_Curve_L0 = 1;
                                }
                                fun(ppt);
                                pL3DRoad_->pre_x = ppt->x;
                                pL3DRoad_->pre_y = tmpH;
                                pL3DRoad_->pre_z = ppt->z;
                            } else {  // 夹角阈值
                                warningMsg.Format(_T("Degree = %f度 > %f度\n线路转角太大,请重新选择!"), 180 - *pDegree, 180 - threshold_degree);
                                LOGGER_WARNING << "线路转角太大,请重新选择!";
                                AfxMessageBox(warningMsg, MB_OK, MB_ICONEXCLAMATION);
                            }
                        }
                    } else {  // 距离阈值
                        warningMsg.Format(_T("Distance = %f < %f\n两点之间距离太短,请重新选择!"), pL3DRoad_->m_distance_between_2_points, threshold_distance);
                        LOGGER_WARNING << "两点之间距离太短,请重新选择!";
                        AfxMessageBox(warningMsg, MB_OK, MB_ICONEXCLAMATION);
                    }
                }
            }
        } else if (spaceSearchInfo_.m_QueryType == SELECTFLYPATH) {  // 如果是设置飞行路径
            PCordinate ppt = new Cordinate;
            ppt->x = wx;
            ppt->y = wy;
            ppt->z = wz;                            // 记录飞行路径的三维坐标
            m_FlayPath.Add(ppt);                    // 将飞行路径的三维坐标存储到数组m_FlayPath
            Invalidate(FALSE);
        }
        if (m_OperateType == SELECT) {              // 如果是选择3D模型
            // 射线选择功能
            GLfloat  winX, winY;
            GLdouble posX, posY, posZ;
            CRect re;
            GetWindowRect(&re);
            int32 screenHeight = re.Height(), screenWidth = re.Width();  // 屏幕宽和高
            // 变换要绘图函数里的顺序一样，否则坐标转换会产生错误
            winX = point.x;
            winY = screenHeight - point.y;
            // 获取像素对应的前裁剪面的点坐标
            int32 bResult = gluUnProject(winX, winY, 0.0, modelview, projection, viewport, &posX, &posY, &posZ);
            CVector3 nearPoint(posX, posY, posZ);
            // 获取像素对应的后裁剪面的点坐标
            bResult = gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &posX, &posY, &posZ);
            CVector3 farPoint(posX, posY, posZ);
            CVector3 n_vector, resultP;
            // cal the vector of ray
            n_vector = farPoint - nearPoint;
            JudgeRayIntersect(nearPoint, n_vector, resultP);
            Invalidate(FALSE);
        } else if (m_OperateType == MOVE) {             // 鼠标移动3D模型
            if (m_bMouseMove3DModelPtNums >= 2)         // 如果选择点数2个，归零
                m_bMouseMove3DModelPtNums = 0;
            m_bMouseMove3DModelPtNums++;                // 选择点数 + 1
            if (m_bMouseMove3DModelPtNums == 1) {       // 如果只选择了1个点
                // JudgeRayIntersect(nearPoint, n_vector, resultP);
                /*PCordinate ppt = new Cordinate;
                ppt->x = wx;
                ppt->y = wy;
                ppt->z = wz;     */     // 三维坐标
                // 遍历所有的3D模型,判断是否在范围内
                // 在移动模型时，保障初始鼠标位置在模型范围内，这样有利于控制模型位置
                // 射线选择功能
                GLfloat  winX, winY;
                GLdouble posX, posY, posZ;
                CRect re;
                GetWindowRect(&re);
                int32 screenHeight = re.Height(), screenWidth = re.Width();  // 屏幕宽和高
                // 变换要绘图函数里的顺序一样，否则坐标转换会产生错误
                winX = point.x;
                winY = screenHeight - point.y;
                // 获取像素对应的前裁剪面的点坐标
                int32 bResult = gluUnProject(winX, winY, 0.0, modelview, projection, viewport, &posX, &posY, &posZ);
                CVector3 nearPoint(posX, posY, posZ);
                // 获取像素对应的后裁剪面的点坐标
                bResult = gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &posX, &posY, &posZ);
                CVector3 farPoint(posX, posY, posZ);
                CVector3 n_vector, resultP;
                // cal the vector of ray
                n_vector = farPoint - nearPoint;
                JudgeRayIntersect(nearPoint, n_vector, resultP);
                if (m_selectedModelID != -1) {
                    pt1[0] = wx;
                    pt1[1] = wy;
                    pt1[2] = wz;                // 将三维点坐标存储到数组 pt1[] 里面
                } else {
                    m_bMouseMove3DModelPtNums = 0;
                }
            } else if (m_selectedModelID != -1) {                       // 选择了两个点，则表示可以计算空间距离了
                // m_modelMoveID
                pt2[0] = wx;
                pt2[1] = wy;
                pt2[2] = wz;                    // 将三维点坐标存储到数组 pt2[] 里面
                double deltX = (pt2[0] - pt1[0]) / derDisScale;     // 400是敏感值系数，数字越大，每次移动距离就越小
                double deltZ = (pt2[2] - pt1[2]) / derDisScale;     // 设置动态修改系数
                m_3DModel.GetAt(m_selectedModelID)->posX += deltX;
                m_3DModel.GetAt(m_selectedModelID)->posZ += deltZ;
                m_selectedModelID = -1;
            }
            Invalidate(FALSE);
        } else if (m_OperateType == SCALE) {  // 鼠标缩放3D模型
            m_selectedModelID = -1;
            // 射线选择功能
            GLfloat  winX, winY;
            GLdouble posX, posY, posZ;
            CRect re;
            GetWindowRect(&re);
            int32 screenHeight = re.Height(), screenWidth = re.Width();  // 屏幕宽和高
            // 变换要绘图函数里的顺序一样，否则坐标转换会产生错误
            winX = point.x;
            winY = screenHeight - point.y;
            // 获取像素对应的前裁剪面的点坐标
            int32 bResult = gluUnProject(winX, winY, 0.0, modelview, projection, viewport, &posX, &posY, &posZ);
            CVector3 nearPoint(posX, posY, posZ);
            // 获取像素对应的后裁剪面的点坐标
            bResult = gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &posX, &posY, &posZ);
            CVector3 farPoint(posX, posY, posZ);
            CVector3 n_vector, resultP;
            // cal the vector of ray
            n_vector = farPoint - nearPoint;
            JudgeRayIntersect(nearPoint, n_vector, resultP);
        }
    } else if (!m_bMouseMoveSelect) {
        MessageBox("鼠标选择点不够精确 , 请精确选择点!");
        LOGGER_INFO << "鼠标选择点不够精确 , 请精确选择点!";
        spaceSearchInfo_.m_bSearchDistencePtNums = 0;
    }
}



void CMy3DSymbolLibNewView::ScreenToGL2(CPoint point, GLdouble& wx , GLdouble& wz) {  // NOLINT
    int32 mouse_x = point.x;
    int32 mouse_y = point.y;
    GLint viewport[4];
    GLdouble modelview[16] , projection[16];
    GLdouble  wy;
    float winX, winY, winZ;
    glPushMatrix();
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);
    glPopMatrix();
    winX = static_cast<float>(mouse_x);
    winY = static_cast<float>(viewport[3]) - static_cast<float>(mouse_y) - 1;
    glReadPixels(mouse_x, static_cast<int32>(winY), 1, 1,
                 GL_DEPTH_COMPONENT , GL_FLOAT ,
                 &winZ);  // 获取深度值，只有在有渲染的地方才能准确获取，一旦没有渲染点就不能获取正确值
    // 逆变换和模拟变换
    gluUnProject((GLdouble)winX, (GLdouble)winY, (GLdouble)winZ, modelview, projection, viewport, &wx, &wy, &wz);
    // 3D坐标点范围限制
    if (wx <  MAP_SCALE) {
        wx =  MAP_SCALE;                // X边
    }
    if (wx > (MAP_W - 1)*MAP_SCALE) {
        wx = (MAP_W - 1) * MAP_SCALE;   // X边
    }
    if (wz < -(MAP_W - 1)*MAP_SCALE) {
        wz = -(MAP_W - 1) * MAP_SCALE;  // Z边
    }
    if (wz > -MAP_SCALE) {
        wz = -MAP_SCALE;                // Z边
    }
}

/********************************************************/
// Function: 计算2个向量之间的夹角
void CMy3DSymbolLibNewView::getDegreeBetween2Vectors(CVector3& v1_Begin, CVector3& v1_End,  /* NOLINT */
        CVector3& v2_Begin, CVector3& v2_End, float* pDegreeRet/*返回结果*/) {  // NOLINT
    CVector3 v1 = v1_End - v1_Begin;
    CVector3 v2 = v2_End - v2_Begin;
    float dotProductRet = CVector3::dot(v1, v2);   // 点积
    float magnitudeV1 = v1.length();          // v1的模
    float magnitudeV2 = v2.length();          // v2的模
    float cosM = dotProductRet / (magnitudeV1 * magnitudeV2);
    float angleAMB = acos(cosM) * 180 / PI;
    *pDegreeRet = angleAMB;
}


void CMy3DSymbolLibNewView::fun(PCordinate ppt) {
    m_oldlinePtnums = pDesingScheme_->PtS_JD.GetSize();  // 当前线路方案原有设计交点数
    if (m_oldlinePtnums == 0) {                         // 如果当前线路方案没有设计交点,即还没有进行该方案的设计
        pDesingScheme_->PtS_JD.Add(ppt);                 // 加入设计交点到PtS_JD数组
        m_linePtnums = pDesingScheme_->PtS_JD.GetSize();  // 当前线路方案原有设计交点数
        PLineCurve pTempCurveElements = new LineCurve;  // 定义新的交点变量
        // 第一个设计交点
        pTempCurveElements->fwj = 0.0;
        double StartLC = 0;
        // 直缓里程=方案的起点里程   缓直里程=方案的起点里程
        pTempCurveElements->ZH = pTempCurveElements->HZ = StartLC;
        // 缓圆里程=方案的起点里程   圆缓里程=方案的起点里程
        pTempCurveElements->HY = pTempCurveElements->YH = StartLC;
        // 转向角、切线长和曲线长=0
        pTempCurveElements->Alfa = pTempCurveElements->T = pTempCurveElements->L = 0;
        // 曲线半径、旋转类型、外矢量距=0
        pTempCurveElements->R = pTempCurveElements->RoateStyle = pTempCurveElements->E = 0;
        // 坡长、缓和曲线长、圆曲线长、夹直线长=0
        pTempCurveElements->P = pTempCurveElements->L0 = pTempCurveElements->Ly = pTempCurveElements->Jzxc = 0;
        // 交点里程=方案的起点里程
        pTempCurveElements->JDLC = StartLC;
        // 交点ID="JD0";
        pTempCurveElements->ID = "JD0";
        pTempCurveElements->x = pDesingScheme_->PtS_JD.GetAt(0)->x;          // 交点的x坐标
        pTempCurveElements->y = fabs(pDesingScheme_->PtS_JD.GetAt(0)->z);  // 交点的y坐标
        pTempCurveElements->z = -pDesingScheme_->PtS_JD.GetAt(0)->y;     // 交点的z坐标
        // 加入交点元素到DCurveElementss模板数组中
        pDesingScheme_->JDCurveElements.Add(pTempCurveElements);
    } else {  // 如果当前线路方案设计交点数>0,表示已经进行该方案的设计
        if (m_linePtnums <= 0) {
            m_linePtnums = pDesingScheme_->PtS_JD.GetSize();
        }
        CString tt;
        tt.Format("JD%d", m_linePtnums);  // 交点ID自动增加
        if (m_oldlinePtnums == 1) {
            PLineCurve pTempCurveElements = new LineCurve;
            pTempCurveElements->R = pL3DRoad_->m_Curve_R;      // 曲线半径
            pTempCurveElements->L0 = pL3DRoad_->m_Curve_L0;    // 缓和曲线长
            pTempCurveElements->ID = tt;
            pTempCurveElements->P = (pTempCurveElements->L0 * pTempCurveElements->L0) / (pTempCurveElements->R * 24.0);
            pTempCurveElements->x = ppt->x;
            pTempCurveElements->y = -ppt->z;
            pTempCurveElements->z = ppt->y;
            pDesingScheme_->JDCurveElements.Add(pTempCurveElements);
            pDesingScheme_->PtS_JD.Add(ppt);
            m_linePtnums = pDesingScheme_->PtS_JD.GetSize();
            if (pDesingScheme_->PtS_JD.GetSize() > 1) {
                OnDraw(GetWindowDC());
            }
        } else if (m_oldlinePtnums >= 2) {
            pDesingScheme_->JDCurveElements[m_oldlinePtnums - 1]->R = pL3DRoad_->m_Curve_R;
            pDesingScheme_->JDCurveElements[m_oldlinePtnums - 1]->L0 = pL3DRoad_->m_Curve_L0;
            PLineCurve pTempCurveElements = new LineCurve;
            pTempCurveElements->R = pL3DRoad_->m_Curve_R;      // 曲线半径
            pTempCurveElements->L0 = pL3DRoad_->m_Curve_L0;    // 缓和曲线长
            pTempCurveElements->ID = tt;            // 交点ID
            pTempCurveElements->P = (pTempCurveElements->L0 * pTempCurveElements->L0) / (pTempCurveElements->R * 24.0);
            pTempCurveElements->x = ppt->x;
            pTempCurveElements->y = -ppt->z;
            pTempCurveElements->z = ppt->y;
            pDesingScheme_->JDCurveElements.Add(pTempCurveElements);
            pDesingScheme_->PtS_JD.Add(ppt);
            m_linePtnums = pDesingScheme_->PtS_JD.GetSize();
            if (pDesingScheme_->PtS_JD.GetSize() > 1) {
                OnDraw(GetWindowDC());
            }
        }
    }
}


void CMy3DSymbolLibNewView::fun(PCordinate ppt, PCurve_R_L0_Struct pcrl0) {
    m_oldlinePtnums = pDesingScheme_->PtS_JD.GetSize();  // 当前线路方案原有设计交点数
    if (m_oldlinePtnums == 0) {                         // 如果当前线路方案没有设计交点,即还没有进行该方案的设计
        pDesingScheme_->PtS_JD.Add(ppt);                 // 加入设计交点到PtS_JD数组
        m_linePtnums = pDesingScheme_->PtS_JD.GetSize();  // 当前线路方案原有设计交点数
        PLineCurve pTempCurveElements = new LineCurve;  // 定义新的交点变量
        // 第一个设计交点
        pTempCurveElements->fwj = 0.0;
        double StartLC = 0;  // ...
        // 直缓里程=方案的起点里程   缓直里程=方案的起点里程
        pTempCurveElements->ZH = pTempCurveElements->HZ = StartLC;
        // 缓圆里程=方案的起点里程   圆缓里程=方案的起点里程
        pTempCurveElements->HY = pTempCurveElements->YH = StartLC;
        // 转向角、切线长和曲线长=0
        pTempCurveElements->Alfa = pTempCurveElements->T = pTempCurveElements->L = 0;
        // 曲线半径、旋转类型、外矢量距=0
        pTempCurveElements->R = pTempCurveElements->RoateStyle = pTempCurveElements->E = 0;
        // 坡长、缓和曲线长、圆曲线长、夹直线长=0
        pTempCurveElements->P = pTempCurveElements->L0 = pTempCurveElements->Ly = pTempCurveElements->Jzxc = 0;
        // 交点里程=方案的起点里程
        pTempCurveElements->JDLC = StartLC;
        // 交点ID="JD0";
        pTempCurveElements->ID = "JD0";
        pTempCurveElements->x = pDesingScheme_->PtS_JD.GetAt(0)->x;          // 交点的x坐标
        pTempCurveElements->y = fabs(pDesingScheme_->PtS_JD.GetAt(0)->z);    // 交点的y坐标
        pTempCurveElements->z = -pDesingScheme_->PtS_JD.GetAt(0)->y;         // 交点的z坐标
        // 加入交点元素到DCurveElementss模板数组中
        pDesingScheme_->JDCurveElements.Add(pTempCurveElements);
    } else {  // 如果当前线路方案设计交点数>0,表示已经进行该方案的设计
        if (m_linePtnums <= 0) {
            m_linePtnums = pDesingScheme_->PtS_JD.GetSize();
        }
        CString tt;
        tt.Format("JD%d", m_linePtnums);  // 交点ID自动增加
        if (1) {
            PLineCurve pTempCurveElements = new LineCurve;
            pTempCurveElements->R = pcrl0->curve_R;         // 曲线半径
            pTempCurveElements->L0 = pcrl0->curve_L0;       // 缓和曲线长
            pTempCurveElements->ID = tt;
            pTempCurveElements->P = (pTempCurveElements->L0 * pTempCurveElements->L0) / (pTempCurveElements->R * 24.0);
            pTempCurveElements->x = ppt->x;
            pTempCurveElements->y = -ppt->z;
            pTempCurveElements->z = ppt->y;
            pDesingScheme_->JDCurveElements.Add(pTempCurveElements);
            pDesingScheme_->PtS_JD.Add(ppt);
            m_linePtnums = pDesingScheme_->PtS_JD.GetSize();
            if (pDesingScheme_->PtS_JD.GetSize() > 1) {
                OnDraw(GetWindowDC());
            }
        }
    }
}


/********************************************************/
// Function: 绘制空间查询标志
void CMy3DSymbolLibNewView::DrawSearchPoint() {
    glViewport(0, 0, WinViewX, WinViewY);                                               // 重新设置视口大小
    glPushAttrib(GL_CURRENT_BIT);                                                       // 保存现有颜色属性
    glDisable(GL_TEXTURE_2D);                                                           // 取消贴图
    glPushMatrix();                                                                     // 压入堆栈
    if (spaceSearchInfo_.m_QueryType == QUERY_COORDINATE) {                                              // 三维空间坐标查询
        if (pt1[0] != -99999) {
            glLineWidth(spaceSearchInfo_.m_QueryLineWidth);                                              // 设置查询标志线宽度
            glColor3f(spaceSearchInfo_.m_QueryColorR / 255.0 , spaceSearchInfo_.m_QueryColorG / 255.0 , spaceSearchInfo_.m_QueryColorB / 255.0);  // 设置查询标志线颜色
            // 绘制十字型查询标志线
            glBegin(GL_LINES);
            glVertex3f(pt1[0] - spaceSearchInfo_.m_shizxLength , pt1[1] , pt1[2]);
            glVertex3f(pt1[0] + spaceSearchInfo_.m_shizxLength , pt1[1] , pt1[2]);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(pt1[0] , pt1[1] , pt1[2] - spaceSearchInfo_.m_shizxLength);
            glVertex3f(pt1[0] , pt1[1] , pt1[2] + spaceSearchInfo_.m_shizxLength);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(pt1[0] , pt1[1] , pt1[2]);
            glVertex3f(pt1[0] , pt1[1] + spaceSearchInfo_.m_shuzxHeight , pt1[2]);
            glEnd();
        }
    } else if (spaceSearchInfo_.m_QueryType == QUERY_DISTENCE) {     // 三维空间距离查询(在选择两个空间点之后才能够计算空间距离)
        glLineWidth(spaceSearchInfo_.m_QueryLineWidth);              // 设置查询标志线宽度
        glColor3f(spaceSearchInfo_.m_QueryColorR / 255.0 , spaceSearchInfo_.m_QueryColorG / 255.0 , spaceSearchInfo_.m_QueryColorB / 255.0);  // 设置查询标志线颜色
        // 绘制十字型查询标志线
        glBegin(GL_LINES);
        glVertex3f(pt1[0] - spaceSearchInfo_.m_shizxLength, pt1[1], pt1[2]);
        glVertex3f(pt1[0] + spaceSearchInfo_.m_shizxLength, pt1[1], pt1[2]);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(pt1[0], pt1[1], pt1[2] - spaceSearchInfo_.m_shizxLength);
        glVertex3f(pt1[0], pt1[1], pt1[2] + spaceSearchInfo_.m_shizxLength);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(pt1[0], pt1[1] , pt1[2]);
        glVertex3f(pt1[0], pt1[1] + spaceSearchInfo_.m_shuzxHeight, pt1[2]);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(pt2[0] - spaceSearchInfo_.m_shizxLength, pt2[1], pt2[2]);
        glVertex3f(pt2[0] + spaceSearchInfo_.m_shizxLength, pt2[1], pt2[2]);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(pt2[0], pt2[1], pt2[2] - spaceSearchInfo_.m_shizxLength);
        glVertex3f(pt2[0], pt2[1], pt2[2] + spaceSearchInfo_.m_shizxLength);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(pt2[0], pt2[1], pt2[2]);
        glVertex3f(pt2[0], pt2[1] + spaceSearchInfo_.m_shuzxHeight, pt2[2]);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(pt1[0], pt1[1], pt1[2]);
        glVertex3f(pt2[0], pt2[1], pt2[2]);
        glEnd();
        glLineWidth(1.0);
    } else if (spaceSearchInfo_.m_QueryType == SELECTLINE || pDesingScheme_->PtS_JD.GetSize() > 0) {  // 三维选线状态
        // 绘制选结过程中的设计交点连线
        m_oldlinePtnums = m_linePtnums;
        glColor3f(0, 0, 1);
        glLineWidth(2.0);
        for (int32 i = 0; i < pDesingScheme_->PtS_JD.GetSize() - 1; i++) {
            // 绘制线路中心线
            pL3DRoad_->DrawCenterLine(i,
                                      TRUE,
                                      pDesingScheme_,
                                      m_TempPts,
                                      std::bind(&CMy3DSymbolLibNewView::GetHeight, this, std::placeholders::_1, std::placeholders::_2),
                                      0, 0);
        }
        // 绘制交点标志
        for (int32 j = 0; j <= pDesingScheme_->PtS_JD.GetSize() - 1; ++j) {
            glLineWidth(spaceSearchInfo_.m_QueryLineWidth + 1);                                                  // 设置标志线宽度
            glColor3f(spaceSearchInfo_.m_QueryColorR / 255.0 , spaceSearchInfo_.m_QueryColorG / 255.0 , spaceSearchInfo_.m_QueryColorB / 255.0);   // 设置标志线颜色
            float tmp_x = pDesingScheme_->PtS_JD[j]->x;
            float tmp_z = pDesingScheme_->PtS_JD[j]->z;
            float tmp_y = GetHeight(tmp_x, tmp_z);
            // 绘制十字型标志线
            glBegin(GL_LINES);
            glVertex3f(tmp_x - spaceSearchInfo_.m_shizxLength , tmp_y, tmp_z);
            glVertex3f(tmp_x + spaceSearchInfo_.m_shizxLength , tmp_y, tmp_z);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(tmp_x, tmp_y, tmp_z - spaceSearchInfo_.m_shizxLength);
            glVertex3f(tmp_x, tmp_y, tmp_z + spaceSearchInfo_.m_shizxLength);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(tmp_x, tmp_y, tmp_z);
            glVertex3f(tmp_x, tmp_y + spaceSearchInfo_.m_shuzxHeight, tmp_z);
            glEnd();
        }
        // } else if (spaceSearchInfo_.m_QueryType == LINE_ADD) {   // 绘制线段
        //    glLineWidth(3.0);                   // 设置查询标志线宽度
        //    glColor3f(spaceSearchInfo_.m_QueryColorR / 255.0 , spaceSearchInfo_.m_QueryColorG / 255.0 , spaceSearchInfo_.m_QueryColorB / 255.0);  // 设置查询标志线颜色
        //    for (int32 i = 0; i < m_LinesArray.GetSize(); ++i) {
        //        glBegin(GL_LINES);
        //        glVertex3f(m_LinesArray[i]->pt1.x, m_LinesArray[i]->pt1.y, m_LinesArray[i]->pt1.z);
        //        glVertex3f(m_LinesArray[i]->pt2.x, m_LinesArray[i]->pt2.y, m_LinesArray[i]->pt2.z);
        //        glEnd();
        //    }
        //    glLineWidth(1.0);
        // }
    } else if (spaceSearchInfo_.m_QueryType == LINE_ADD) {   // 绘制线段
        glLineWidth(2.0);                   // 设置查询标志线宽度
        glColor3f(spaceSearchInfo_.m_QueryColorR / 255.0 , spaceSearchInfo_.m_QueryColorG / 255.0 , spaceSearchInfo_.m_QueryColorB / 255.0);  // 设置查询标志线颜色
        for (auto iter = pL2DRoad_->allLineSymbols_.begin(); iter != pL2DRoad_->allLineSymbols_.end(); ++iter) {
            LineSymbol pLs = iter->second;
            vector<Vec3> lp = pLs.line_points_;
            if (lp.size() >= 2 && !pLs.deleted_) {
                glBegin(GL_LINE_STRIP);
                for (auto it = lp.begin(); it != lp.end(); ++it) {
                    glVertex3f((*it).x, (*it).y, (*it).z);
                }
                glEnd();
            }
        }
        if (nullptr != pLineSymbol_ && pLineSymbol_->line_type_ != 0 && !pLineSymbol_->deleted_) {
            std::vector<Vec3> lintPoints = pLineSymbol_->line_points_;
            if (lintPoints.size() >= 2) {
                glBegin(GL_LINE_STRIP);
                for (auto it = lintPoints.begin(); it != lintPoints.end(); ++it) {
                    glVertex3f((*it).x, (*it).y, (*it).z);
                }
                glEnd();
            }
        }
        glLineWidth(1.0);
    } else if (spaceSearchInfo_.m_QueryType == AREA_ADD) {  // 绘制4边形
        glLineWidth(3.0);                   // 设置查询标志线宽度
        glColor3f(0.3, 0.6, 0.5);           // 设置查询标志线颜色
        for (int32 i = 0; i < m_Area4_Array.GetSize(); ++i) {
            if (m_Area4_Array[i]->deleted != 1) {
                glBegin(GL_QUADS);
                glVertex3f(m_Area4_Array[i]->pt1.x, m_Area4_Array[i]->pt1.y, m_Area4_Array[i]->pt1.z);
                glVertex3f(m_Area4_Array[i]->pt2.x, m_Area4_Array[i]->pt2.y, m_Area4_Array[i]->pt2.z);
                glVertex3f(m_Area4_Array[i]->pt3.x, m_Area4_Array[i]->pt3.y, m_Area4_Array[i]->pt3.z);
                glVertex3f(m_Area4_Array[i]->pt4.x, m_Area4_Array[i]->pt4.y, m_Area4_Array[i]->pt4.z);
                glEnd();
            }
        }
        glLineWidth(1.0);
    }
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glPopAttrib();
}

void CMy3DSymbolLibNewView::OnLButtonDown(UINT nFlags, CPoint point) {
    m_bmouseView = true;
    // 通过鼠标设置模型摆放位置
    if (m_isSetXYByMouse) {
        m_bmouseView = false;
        m_oldMousePos = point;
        ScreenToGL(point);
    }
    if (spaceSearchInfo_.m_QueryType == QUERY_COORDINATE) {  // 空间三维坐标查询
        m_bmouseView = false;
        m_oldMousePos = point;
        ScreenToGL(point);
    } else if (spaceSearchInfo_.m_QueryType == QUERY_DISTENCE) {     // 空间距离查询
        m_bmouseView = false;                       // 关闭鼠标控相机旋转
        m_oldMousePos = point;
        ScreenToGL(point);
    } else if (spaceSearchInfo_.m_QueryType == SELECTFLYPATH) {      // 进行飞行路径选择
        m_bmouseView = false;                       // 关闭鼠标控相机旋转
        m_oldMousePos = point;
        ScreenToGL(point);
    } else if (spaceSearchInfo_.m_QueryType == SELECTLINE) {         // 进行三维选线设计
        m_bmouseView = false;                       // 关闭鼠标控相机旋转
        m_oldMousePos = point;
        ScreenToGL(point);
    } else if (spaceSearchInfo_.m_QueryType == LINE_ADD) {           // 线编辑   添加线
        m_bmouseView = false;                       // 关闭鼠标控相机旋转
        m_oldMousePos = point;
        ScreenToGL(point);
    } else if (spaceSearchInfo_.m_QueryType == AREA_ADD) {           // 添加面符号 4边形
        m_bmouseView = false;                       // 关闭鼠标控相机旋转
        m_oldMousePos = point;
        ScreenToGL(point);
    }
    // ------------------------------------------
    // 操作3DS模型
    if (m_OperateType == SELECT) {  // 选中3DS模型
        m_bmouseView = false;
        m_oldMousePos = point;
        m_bIsLBtnDown = true;
        ScreenToGL(point);
    } else if (m_OperateType == MOVE) {  // 移动3DS模型
        m_bmouseView = false;
        m_oldMousePos = point;
        ScreenToGL(point);
    } else if (m_OperateType == SCALE) {  // 缩放3DS模型
        m_bmouseView = false;
        m_bIsLBtnDown = true;
        ScreenToGL(point);
    }
    // ------------------------------------------
    CView::OnLButtonDown(nFlags, point);
}

void CMy3DSymbolLibNewView::OnRButtonDown(UINT nFlags, CPoint point) {
    // 当鼠标在某个模型上，按下鼠标右键，弹出模型控制菜单
    if (m_OperateType == SELECT && !(m_pSelectedModelSet.empty()) && m_selectedModelID != -1) {
        if (m_3DModel.GetAt(m_selectedModelID)->isDeleted == false) {
            // 右键快捷菜单
            CMenu menu;
            menu.LoadMenu(IDR_POPUP_MODEL_SETTING);
            CMenu* pPopUp = menu.GetSubMenu(0);
            ClientToScreen(&point);
            pPopUp->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
        }
    }
    if (spaceSearchInfo_.m_QueryType == QUERY_DISTENCE || spaceSearchInfo_.m_QueryType == QUERY_COORDINATE) {
        spaceSearchInfo_.m_QueryType = -1;  // 关闭三维查询
    }
    if (m_OperateType == MOVE || m_OperateType == SCALE) {
        // 当在move模式下面进行右键操作，相当于回到移动操作之前的状态进行操作
        m_OperateType = SELECT;
        m_selectedModelID = -1;
    }
    GLdouble wx = 0.0;
    GLdouble wz = 0.0;
    ScreenToGL2(point, wx, wz);
    PPR_Point tmp_mp(wx, wz);
    UpdateAreaTexture(tmp_mp, point);
    UpdateLineSymbol(tmp_mp, point);
    Invalidate(FALSE);
    CView::OnRButtonDown(nFlags, point);
}

void CMy3DSymbolLibNewView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
    m_keynumber = 0;
    CVector3 vAxis;
    switch (nChar) {            // 根据按键字符来进行相应设置
        case VK_LEFT:
            m_keynumber = 3;
            pCamera_->m_xTrans -= pCamera_->m_Step_X;   // 在X方向上移动的距离累计
            Invalidate(FALSE);      // 刷新三维场景
            break;
        case VK_RIGHT:
            m_keynumber = 4;
            pCamera_->m_xTrans += pCamera_->m_Step_X;   // 在X方向上移动的距离累计
            Invalidate(FALSE);      // 刷新三维场景
            break;
        case VK_UP:
            // 选中物体时就将物体高度变化
            if (m_OperateType == SELECT) {
                for (int32 i = 0; i < m_3DModel.GetSize(); i++) {
                    if (m_3DModel.GetAt(i)->modelSelected) {
                        m_3DModel.GetAt(i)->posY++;
                    }
                }
            } else {
                // 否则就拉近视线
                pCamera_->m_zTrans -= pCamera_->m_Step_Z;   // 在Z方向上移动的距离累计
                m_keynumber = 1;
            }
            Invalidate(FALSE);          // 刷新三维场景
            break;
        case VK_DOWN:
            // 选中物体时就将物体高度变化
            if (m_OperateType == SELECT) {
                for (int32 i = 0; i < m_3DModel.GetSize(); i++) {
                    if (m_3DModel.GetAt(i)->modelSelected) {
                        m_3DModel.GetAt(i)->posY--;
                    }
                }
            } else {
                pCamera_->m_zTrans += pCamera_->m_Step_Z;   // 在Z方向上移动的距离累计
                m_keynumber = 2;
            }
            Invalidate(FALSE);          // 刷新三维场景
            break;
        case 'I':
            m_ViewWideNarrow += 1.0;    // 飞行视野增大,看见场景范围增大了,相当于相机镜头向屏幕外方向移动
            OnDraw(GetDC());            // 刷新三维场景
            break;
        case 'O':
            m_ViewWideNarrow -= 1.0;    // 飞行视野减小,看见场景范围减小了,相当于相机镜头向屏幕里方向移动
            OnDraw(GetDC());            // 刷新三维场景
            break;
        case 'J':                       // 加速
            // m_flyspeed -= 1;
            // if(m_flyspeed<=1)
            // m_flyspeed=1;
            // SetFLyTimer();            // 设置飞行计时器
            break;
        case 'M':                        // 减速
            // m_flyspeed += 1;
            // SetFLyTimer();            // 设置飞行计时器
            break;
        case 'G':
            m_StaticHeight = m_StaticHeight * 1.1;
            OnDraw(GetDC());        // 刷新三维场景
            break;
        case 'B':
            m_StaticHeight = m_StaticHeight / 1.1;  // 减少固定飞行高度
            OnDraw(GetDC());        // 刷新三维场景
            break;
        case VK_F2:                 // 显示漫游热键帮助
            DisplayHelp();
            break;
        case 'S':                   // 停止飞行
            OnFlyStop();
            break;
        case 'P':                   // 开始/暂停飞行
            OnFlyPlaypause();
            break;
        case 'H':
        case VK_PRIOR:  // PgUp   俯仰角
            vAxis = CVector3::CrossProduct(pCamera_->m_vLook - pCamera_->m_vEyePosition, pCamera_->m_vUp);      // 叉积计算
            vAxis = vAxis.getNormalized();                                   // vAxis归一化
            RotateView(20 / derAngleZ, vAxis.x, vAxis.y, vAxis.z);      // 通过鼠标控制相机的旋转(旋转视角)
            OnDraw(GetDC());
            break;
        case 'N':
        case VK_NEXT:  // PgDn   俯仰角
            vAxis = CVector3::CrossProduct(pCamera_->m_vLook - pCamera_->m_vEyePosition, pCamera_->m_vUp);      // 叉积计算
            vAxis = vAxis.getNormalized();                                      // vAxis归一化
            RotateView(-20 / derAngleZ, vAxis.x, vAxis.y, vAxis.z);     // 通过鼠标控制相机的旋转(旋转视角)
            OnDraw(GetDC());
            break;
        case 'R':  // 选中模型R键绕Y轴旋转
            for (int32 i = 0; i < m_3DModel.GetSize(); i++) {
                if (m_3DModel.GetAt(i)->modelSelected)
                    m_3DModel.GetAt(i)->rotY++;
                if (m_3DModel.GetAt(i)->rotY >= 360)
                    m_3DModel.GetAt(i)->rotY = 0;
            }
            OnDraw(GetDC());
            break;
        case VK_HOME:  // 顺时针旋转
            vAxis = CVector3::CrossProduct(pCamera_->m_vLook - pCamera_->m_vEyePosition, pCamera_->m_vUp);      // 叉积计算
            vAxis = vAxis.getNormalized();                                   // vAxis归一化
            RotateView(-50 / derAngleZ,  0, 1, 0);      // 通过鼠标控制相机的旋转(旋转视角)
            OnDraw(GetDC());
            break;
        case VK_END:  // 逆时针旋转
            vAxis = CVector3::CrossProduct(pCamera_->m_vLook - pCamera_->m_vEyePosition, pCamera_->m_vUp);      // 叉积计算
            vAxis = vAxis.getNormalized();                                   // vAxis归一化
            RotateView(50 / derAngleZ,  0, 1, 0);   // 通过鼠标控制相机的旋转(旋转视角)
            OnDraw(GetDC());
            break;
    }
    CamraUpdate();              // 重新调整相机
    m_keynumber = 0;            // 恢复按键0值
    CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


/****************************************************************/
// Function: 根据鼠标和键盘实现三维场景相机的移动和旋转控制
void CMy3DSymbolLibNewView::CamraUpdate() {
    CVector3 vCross = CVector3::CrossProduct(pCamera_->m_vLook - pCamera_->m_vEyePosition, pCamera_->m_vUp);  // 叉积计算
    m_vStrafe = vCross.getNormalized();                                  // vCross归一化
    SetViewByMouse();                                               // 通过鼠标实现相机控制
    CheckForMovement();                                             // 通过键盘实现相机控制
    pCamera_->m_vEyePosition.y += (pCamera_->m_viewHeight - pCamera_->m_oldviewHeight);           // 新的相机视点y坐标
    pCamera_->m_oldviewHeight = pCamera_->m_viewHeight;                                 // 记录当前相机视点高度
}


/****************************************************************/
// Function: 在X轴方向上移动时设置相机观察点和视点坐标
void CMy3DSymbolLibNewView::MoveCameraX(float speed) {
    pCamera_->m_vEyePosition.x += m_vStrafe.x * speed;                        // 相机视点x新坐标
    pCamera_->m_vEyePosition.z += m_vStrafe.z * speed;                        // 相机视点z新坐标
    pCamera_->m_vLook.x += m_vStrafe.x * speed;                               // 相机观察点x新坐标
    pCamera_->m_vLook.z += m_vStrafe.z * speed;                               // 相机观察点z新坐标
}


/****************************************************************/
// Function: 在Z轴方向上移动时设置相机观察点和视点坐标
void CMy3DSymbolLibNewView::MoveCameraZ(float speed) {
    CVector3 vVector = pCamera_->m_vLook - pCamera_->m_vEyePosition;                        // 相机视点与观察点三维坐标差值
    vVector = vVector.getNormalized();                              // 相机视点与观察点三维坐标差值归一化
    pCamera_->m_vEyePosition.x += vVector.x * speed;                          // 相机视点x新坐标
    pCamera_->m_vEyePosition.z += vVector.z * speed;                          // 相机视点z新坐标
    pCamera_->m_vLook.x += vVector.x * speed;                                 // 相机观察点x新坐标
    pCamera_->m_vLook.z += vVector.z * speed;                                 // 相机观察点z新坐标
}


/****************************************************************/
// Function: 根据键盘按键值来重新设置相机
void CMy3DSymbolLibNewView::CheckForMovement() {
    if (m_keynumber == 1) {                                         // ↑上箭头按键，向场景外移动(Z轴正方向)
        MoveCameraZ(pCamera_->m_Step_Z);                                      // 在Z轴方向上移动时设置相机观察点和视点坐标
    } else if (m_keynumber == 2) {                                  // ↓下箭头按键，向场景外移动(Z轴负方向)
        MoveCameraZ(-pCamera_->m_Step_Z);                                     // 在Z轴方向上移动时设置相机观察点和视点坐标
    } else if (m_keynumber == 3) {                                  // ←左箭头按键，向左方向移动场景(X轴负方向)
        MoveCameraX(-pCamera_->m_Step_X);                                     // 在X轴方向上移动时设置相机观察点和视点坐标
    } else if (m_keynumber == 4) {                                  // →右箭头按键，向右方向移动场景(X轴正方向)
        MoveCameraX(pCamera_->m_Step_X);                                      // 在X轴方向上移动时设置相机观察点和视点坐标
    }
}


/****************************************************************/
// Function: 设置相机
void CMy3DSymbolLibNewView::SetCamra() {
    gluLookAt(pCamera_->m_vEyePosition.x, pCamera_->m_vEyePosition.y, pCamera_->m_vEyePosition.z,     // 视点
              pCamera_->m_vLook.x, pCamera_->m_vLook.y, pCamera_->m_vLook.z,                          // 目标点
              pCamera_->m_vUp.x, pCamera_->m_vUp.y, pCamera_->m_vUp.z);                               // 视点方向
    CMainFrame* pMainFrame = reinterpret_cast<CMainFrame*>(GetParent());
    CString strText;
    float dy = pCamera_->m_vEyePosition.y - pCamera_->m_vLook.y;
    float dz = fabs(pCamera_->m_vEyePosition.z - pCamera_->m_vLook.z);
    if (fabs(dz) <= 0.000001) {
        pCamera_->m_viewdegree = 0;
    } else {
        pCamera_->m_viewdegree = HDANGLE * atan(dy / dz);
    }
    // 在状态栏指示器上显示相关信息
    static DWORD dwStart = 0;
    static int32 nCount = 0;
    nCount++;
    DWORD dwNow = ::GetTickCount();  // 返回从程序启动到现在所经过的毫秒数
    if (dwNow - dwStart >= 1000) {  // 每1秒计算一次帧率
        strText.Format("刷新频率: %d FPS " , nCount , 0);
        pMainFrame->Set_BarText(0 , strText);
        dwStart = dwNow;
        nCount = 0;
    }
    strText.Format("【俯视角】A=%.2f" , pCamera_->m_viewdegree);
    pMainFrame->Set_BarText(1 , strText);
    strText.Format("视点坐标: X=%.3f , Y=%.3f , Z=%.3f" , pCamera_->m_vEyePosition.x  , pCamera_->m_vEyePosition.y , fabs(pCamera_->m_vEyePosition.z));
    pMainFrame->Set_BarText(2 , strText);
    strText.Format("观察点坐标: X=%.3f , Y=%.3f , Z=%.3f" , pCamera_->m_vLook.x  , pCamera_->m_vLook.y , fabs(pCamera_->m_vLook.z));
    pMainFrame->Set_BarText(3 , strText);
}

void CMy3DSymbolLibNewView::OnMouseMove(UINT nFlags, CPoint point) {
    // 设置鼠标形状
    // 在模型选择模式下变成手型
    if (m_OperateType == SELECT) {
        m_selectedModelID = -1;
        // 如果在选择模式下，鼠标移动到的位置拾取了某个当前选中模型的模型，那就更改为Edit型号的鼠标
        if (!m_pSelectedModelSet.empty()) {
            m_bMouseMoveSelect = true;
            ScreenToGL(point);
        } else {
            m_mouseShape = MOUSE_SHAPE_SLECT;
        }
        if (m_mouseShape == MOUSE_SHAPE_SLECT) {
            HCURSOR hCur  =  LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_CURSOR_SELECT));
            ::SetCursor(hCur);
        } else {
            HCURSOR hCur  =  LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_CURSOR_EDIT));
            ::SetCursor(hCur);
        }
    }
    if (m_bmouseView) {     // 如果鼠标控制场景打开时
        CamraUpdate();              // 根据鼠标和键盘实现三维场景相机的移动和旋转控制
    }
    Invalidate(FALSE);
    CView::OnMouseMove(nFlags, point);
}


/****************************************************************/
// Function: 通过鼠标实现相机控制
void CMy3DSymbolLibNewView::SetViewByMouse() {
    if (!m_bmouseView) {    // 如果鼠标控制场景关闭时,返回
        return;
    }
    float angleY = 0.0f;
    float angleZ = 0.0f;
    static float currentRotX = 0.0f;
    POINT mousePos;
    GetCursorPos(&mousePos);        // 得到光标的位置,以屏幕坐标表示,存储到mousePos变量里
    // 如果鼠标坐标没有变化,返回
    if ((mousePos.x == m_oldMousePos.x) && (mousePos.y == m_oldMousePos.y))
        return;
    /* 对鼠标y坐标前后之差进行缩小(这里缩小500倍,这个值可根据实际地形设置),如果angleY值
    太大,表示即使鼠标y坐标前后之差很小,也会导致三维地形场景在Y方向上变化很大 */
    angleY = static_cast<float>((m_oldMousePos.x - mousePos.x)) / derAngleY;
    /* 对鼠标z坐标前后之差进行缩小(这里缩小4000倍,这个值可根据实际地形设置),如果angleZ值
    太大,表示即使鼠标z坐标前后之差很小,也会导致三维地形场景在Z方向上变化很大 */
    angleZ = static_cast<float>((m_oldMousePos.y - mousePos.y)) / derAngleZ;
    currentRotX -= angleZ;
    if (angleY >= -360 && angleY <= 360 && angleZ >= -360 && angleY <= 360) {
        CVector3 vAxis = CVector3::CrossProduct(pCamera_->m_vLook - pCamera_->m_vEyePosition, pCamera_->m_vUp);     // 叉积计算
        vAxis = vAxis.getNormalized();                                           // vAxis归一化
        RotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);      // 通过鼠标控制相机的旋转(旋转视角)
        RotateView(angleY, 0, 1, 0);                        // 通过鼠标控制相机的旋转(旋转视角)
    }
    m_oldMousePos.x = mousePos.x;                           // 记录当前鼠标x坐标
    m_oldMousePos.y = mousePos.y;                           // 记录当前鼠标y坐标
}


/****************************************************************/
// Function: 通过鼠标控制相机的旋转(旋转视角)
void CMy3DSymbolLibNewView::RotateView(float angle, float x, float y, float z) {
    CVector3 vNewView;
    CVector3 vView = pCamera_->m_vLook - pCamera_->m_vEyePosition;          // 相机视点与观察点三维坐标差值
    float cosTheta = static_cast<float>(cos(angle));    // 得到旋转视角的cos函数值
    float sinTheta = static_cast<float>(sin(angle));    // 得到旋转视角的sin函数值
    vNewView.x  = (cosTheta + (1 - cosTheta) * x * x)       * vView.x;
    vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta)   * vView.y;
    vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta)   * vView.z;
    vNewView.y  = ((1 - cosTheta) * x * y + z * sinTheta)   * vView.x;
    vNewView.y += (cosTheta + (1 - cosTheta) * y * y)       * vView.y;
    vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta)   * vView.z;
    vNewView.z  = ((1 - cosTheta) * x * z - y * sinTheta)   * vView.x;
    vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta)   * vView.y;
    vNewView.z += (cosTheta + (1 - cosTheta) * z * z)       * vView.z;
    pCamera_->m_vLook = pCamera_->m_vEyePosition + vNewView;                // 得到旋转后的相机视点坐标
    GetNorthPtangle();
}

void CMy3DSymbolLibNewView::OnCameraParamSet() {
    CCameraParamSet dlg;
    dlg.m_DerAngleY = derAngleY;
    dlg.m_DerAngleZ = derAngleZ;
    dlg.m_OriginDerAngleY = 500;    // derAngleY;
    dlg.m_OriginDerAngleZ = 4000;   // derAngleZ;
    if (dlg.DoModal() == IDOK) {
        derAngleY = dlg.m_DerAngleY;
        derAngleZ = dlg.m_DerAngleZ;
    }
}


/****************************************************************/
// Function: 手动设置飞行路径
void CMy3DSymbolLibNewView::OnPathManuinput() {
    m_ShowFlyPath = TRUE;           // 标识是否显示飞行路径
    spaceSearchInfo_.m_QueryType = SELECTFLYPATH;    // 进行飞行路径选择
    m_FlayPath.RemoveAll();         // 存储进行飞行路径坐标数组清空
}


/****************************************************************/
// Function: 绘制飞行路径
void CMy3DSymbolLibNewView::DrawFlyPath() {
    // 如果显示飞行路径并且飞行路径坐标点数>1,才绘制飞行路径
    if (m_ShowFlyPath == TRUE  && m_FlayPath.GetSize() > 1) {  // 进行飞行路径选择
        glPushAttrib(GL_CURRENT_BIT);  // 保存现有颜色属性
        glPushMatrix();             // 压入矩阵堆栈
        glDisable(GL_TEXTURE_2D);   // 关闭纹理(即飞行路径不采用纹理)
        glLineWidth(10.0);          // 设置飞行路径线宽
        glColor3f(1, 0, 0);         // 设置飞行路径颜色
        glBegin(GL_LINE_STRIP);
        for (int32 i = 0; i < m_FlayPath.GetSize(); ++i) {
            glVertex3f(m_FlayPath.GetAt(i)->x, m_FlayPath.GetAt(i)->y, m_FlayPath.GetAt(i)->z);
        }
        glEnd();
        glEnable(GL_TEXTURE_2D);    // 开启纹理
        glLineWidth(1.0);           // 恢复线宽
        glPopAttrib();
        glPopMatrix();              // 弹出矩阵堆栈
    }
}


/****************************************************************/
// Function: 路径坐标插值
void CMy3DSymbolLibNewView::OnFlppathInterpolation() {
    int32 i;
    float m_InsertDdis = 1;         // 插值间距
    double x1, y1, z1, x2, y2, z2;
    PCordinate ppt;
    m_FlayPathTempPts.RemoveAll();  // 临时存储飞行路径
    for (i = 0; i < m_FlayPath.GetSize() - 1; i++) {
        x1 = m_FlayPath.GetAt(i)->x;  // 获取飞行路径当前点的x坐标
        y1 = m_FlayPath.GetAt(i)->y;  // 获取飞行路径当前点的y坐标
        z1 = m_FlayPath.GetAt(i)->z;  // 获取飞行路径当前点的z坐标
        x2 = m_FlayPath.GetAt(i + 1)->x;  // 获取飞行路径下一点的x坐标
        y2 = m_FlayPath.GetAt(i + 1)->y;  // 获取飞行路径下一点的y坐标
        z2 = m_FlayPath.GetAt(i + 1)->z;  // 获取飞行路径下一点的z坐标
        if (i == 0) {  // 如果是飞行路径的起始点,则记录
            ppt = new Cordinate;
            ppt->x = x1;
            ppt->y = y1;
            ppt->z = z1;
            m_FlayPathTempPts.Add(ppt);
        }
        // 计算飞行路径当前点与下一点的距离
        double L = Vec3::distance(Vec3(x1, y1, z1), Vec3(x2, y2, z2));
        int32 M = L / m_InsertDdis;       // 计算应内插的坐标点数
        for (int32 j = 1; j <= M; j++) {
            // 线性内插计算出新的内插点的三维坐标
            ppt = new Cordinate;
            ppt->x = x1 + j * m_InsertDdis / L * (x2 - x1);
            ppt->z = z1 + j * m_InsertDdis / L * (z2 - z1);
            // ppt->y=GetHeight(ppt->x,-ppt->z);
            ppt->y = y1 + j * m_InsertDdis / L * (y2 - y1);
            m_FlayPathTempPts.Add(ppt);  // 记录内插点坐标
        }
        ppt = new Cordinate;
        ppt->x = x2;
        ppt->y = y2;
        ppt->z = z2;
        m_FlayPathTempPts.Add(ppt);     // 将飞行路径下一点的坐标也记录在内
    }
    m_FlayPath.RemoveAll();             // 飞行路径数组清空
    for (i = 0; i < m_FlayPathTempPts.GetSize(); i++) {
        ppt = new Cordinate;
        ppt->x = m_FlayPathTempPts.GetAt(i)->x;
        ppt->y = m_FlayPathTempPts.GetAt(i)->y;
        ppt->z = m_FlayPathTempPts.GetAt(i)->z;
        m_FlayPath.Add(ppt);            // 重新填充飞行路径数组
    }
    Invalidate(FALSE);
    MessageBox("路径坐标插值完成!", "路径坐标插值", MB_ICONINFORMATION);
}


/****************************************************************/
// Function: 保存飞行路径
void CMy3DSymbolLibNewView::OnFlypathSave() {
    CString     NeededFile;
    char        FileFilter[] = "飞行路径(*.pth)|*.pth||";
    // 设置文件对话框属性
    DWORD       FileDialogFlag = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
    CFileDialog FileDialogBoxFile(FALSE, NULL, 0, FileDialogFlag, FileFilter, this);
    FileDialogBoxFile.m_ofn.lpstrTitle = "保存飞行路径文件";
    char        FileName[200];
    if (FileDialogBoxFile.DoModal() == IDOK) {  // 如果对话框成果打开
        NeededFile = FileDialogBoxFile.GetPathName();  // 得到文件名
        // sprintf(FileName, "%s", NeededFile);
        _snprintf_s(FileName, sizeof(FileName), sizeof(FileName) - 1, "%s", NeededFile);
        if (strcmp(FileDialogBoxFile.GetFileExt(), "pth") != 0)
            strcat(FileName, ".pth");  // 添加飞行路径文件扩展名  // NOLINT
        if (FlyPathSave(FileName))  // 如果飞行路径保存成功
            MessageBox("路径点保存完毕", "保存飞行路径", MB_ICONWARNING);
    }
    Invalidate(FALSE);
}


/****************************************************************/
// Function: 飞行路径保存
int32 CMy3DSymbolLibNewView::FlyPathSave(char* pathfile) {
    FILE*    fpw;
    char    message[200];
    if ((fpw = fopen(pathfile, "w")) == NULL) {
        // sprintf(message, "文件 %s 创建无效", pathfile);
        _snprintf_s(message, sizeof(message), sizeof(message) - 1, "文件 %s 创建无效", pathfile);
        MessageBox(message, "保存飞行路径坐标到文件", MB_ICONWARNING);
        return 0;
    }
    fprintf(fpw, "%d\n", m_FlayPath.GetSize());         // 写入飞行路径坐标点总数
    for (int32 i = 0; i < m_FlayPath.GetSize(); ++i) {
        // 向文件fpw写入飞行路径坐标点的三维坐标
        fprintf(fpw, "%lf,%lf,%lf\n", m_FlayPath.GetAt(i)->x, m_FlayPath.GetAt(i)->y, m_FlayPath.GetAt(i)->z);
    }
    fclose(fpw);        // 关闭文件
    return 1;           // 返回成功
}


/****************************************************************/
// Function: 打开飞行路径
void CMy3DSymbolLibNewView::OnFlyOpenpath() {
    CString     NeededFile;
    char        FileFilter[] = "飞行路径(*.pth)|*.pth||";
    // 设置文件对话框属性
    DWORD       FileDialogFlag = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
    CFileDialog FileDialogBoxFile(TRUE, NULL, 0, FileDialogFlag, FileFilter, this);
    FileDialogBoxFile.m_ofn.lpstrTitle = "打开飞行路径文件";
    FileDialogBoxFile.m_ofn.lpstrInitialDir = m_AllDataPath;
    char        FileName[200];
    if (FileDialogBoxFile.DoModal() == IDOK) {           // 如果对话框成果打开
        NeededFile = FileDialogBoxFile.GetPathName();   // 得到文件名
        // sprintf(FileName, "%s", NeededFile);
        _snprintf_s(FileName, sizeof(FileName), sizeof(FileName) - 1, "%s", NeededFile);
        if (strcmp(FileDialogBoxFile.GetFileExt(), "pth") != 0)
            strcat(FileName, ".pth");                   // 添加飞行路径文件扩展名  // NOLINT
        if (FlyPathRead(FileName))  // 读取飞行路径文件数据动态数组中
            MessageBox("打开路径点完毕", "提示", MB_ICONWARNING);
        if (m_FlayPath.GetSize() > 1) {                 // 如果飞行路径数据坐标点数>1
            m_ShowFlyPath = TRUE;                       // 显示飞行路径
            m_PathFlag = TRUE;                          // 标识飞行路径打开成功
        } else {
            m_PathFlag = FALSE;
        }
    }
    Invalidate(FALSE);
}


/****************************************************************/
// Function: 读取飞行路径文件数据动态数组中
int32 CMy3DSymbolLibNewView::FlyPathRead(char* pathfile) {
    CString tt, m_strszLine;
    PCordinate ppt = new Cordinate;
    m_FlayPath.RemoveAll();                             // 飞行路径数组清空
    CStdioFile m_inFile;
    if (m_inFile.Open(pathfile, CFile::modeRead) == FALSE) {
        return 0;
    }
    m_inFile.ReadString(m_strszLine);                   // 读取飞行路径坐标点总数
    while (m_inFile.ReadString(m_strszLine)) {
        ppt = new Cordinate;
        m_strszLine.TrimLeft(" ");
        m_strszLine.TrimRight("	");  // NOLINT
        int32 nPos = m_strszLine.Find(",");
        tt = m_strszLine.Left(nPos);
        ppt->x = atof(tt);
        m_strszLine = m_strszLine.Right(m_strszLine.GetLength() - nPos - 1);
        nPos = m_strszLine.Find(",");
        tt = m_strszLine.Left(nPos);
        ppt->y = atof(tt);
        m_strszLine = m_strszLine.Right(m_strszLine.GetLength() - nPos - 1);
        ppt->z = atof(m_strszLine);
        m_FlayPath.Add(ppt);                            // 记录飞行路径坐标点
    }
    m_inFile.Close();
    return 1;
}


/****************************************************************/
// Function: 显示或关闭飞行路径
void CMy3DSymbolLibNewView::OnFlyOnoffpath() {
    m_ShowFlyPath = m_ShowFlyPath ? FALSE : TRUE;
    Invalidate(FALSE);
}


/****************************************************************/
// Function: 根据m_ShowFlyPath值修改菜单文本
void CMy3DSymbolLibNewView::OnUpdateFlyOnoffpath(CCmdUI* pCmdUI) {
    if (m_ShowFlyPath)                      // 如果当前是显示飞行路径
        pCmdUI->SetText("关闭飞行路径");     // 将菜单名称设置为"关闭飞行路径"
    else                                    // 如果当前是关闭飞行路径
        pCmdUI->SetText("显示飞行路径");     // 将菜单名称设置为"显示飞行路径"
}


/****************************************************************/
// Function: 按固定高度漫游
void CMy3DSymbolLibNewView::OnFlyStaticheight() {
    if (m_FlayPath.GetSize() <= 0) {                    // 如果飞行路径坐标点数量<=0，即飞行路径为空
        MessageBox("没有输入路径文件", "飞行浏览", MB_ICONWARNING);
        LOGGER_WARNING << "没有输入路径文件";
        return;
    }
    m_fly_start_pause_Enable = TRUE;
    m_FlyHeightType = GIS_FLY_STATICHEIGHT;             // 设置漫游类型为固定高度漫游
    m_StaticHeight = (m_maxHeight + m_minHeight) / 2.0;  // 取固定高度值=地形最大和最小高度的1/4
    m_flypathPtIndex = 0;                               // 飞行路径坐标索引=0
    SetFLyTimer();                                      // 设置三维漫游计时器
}


void CMy3DSymbolLibNewView::OnUpdateFlyStaticheight(CCmdUI* pCmdUI) {
    pCmdUI->Enable(m_PathFlag == TRUE);              // 根据是否具有有效飞行路径值设置菜单状态
    if (m_FlyHeightType == GIS_FLY_STATICHEIGHT)        // 如果当前是"沿固定高度漫游"方式
        pCmdUI->SetCheck(TRUE);                         // 菜单前设置选中标志"√"
    else
        pCmdUI->SetCheck(FALSE);                        // 否则不设置
}


/****************************************************************/
// Function: 设置飞行计时器
void CMy3DSymbolLibNewView::SetFLyTimer() {
    SetTimer(1, m_flyspeed, NULL);                      // m_flyspeed:飞行计时器时间间隔,
}


/****************************************************************/
// Function: 计时器,飞行频率控制器
void CMy3DSymbolLibNewView::OnTimer(UINT nIDEvent) {
    switch (nIDEvent) {
        case 1:  // 三维漫游
            if (m_flypathPtIndex <= m_FlayPath.GetSize() - 2) {  // 如果当前飞行路径坐标点索引<=路径坐标点总数-1
                // 根据漫游路径相临坐标点计算相机各参数
                GetCameraCorrdinate(
                    m_FlayPath.GetAt(m_flypathPtIndex)->x, \
                    m_FlayPath.GetAt(m_flypathPtIndex)->y, \
                    m_FlayPath.GetAt(m_flypathPtIndex)->z, \
                    m_FlayPath.GetAt(m_flypathPtIndex + 1)->x, \
                    m_FlayPath.GetAt(m_flypathPtIndex + 1)->y, \
                    m_FlayPath.GetAt(m_flypathPtIndex + 1)->z
                );
                Invalidate(FALSE);
                ++m_flypathPtIndex;                         // 飞行路径当前坐标索引号+1
            } else {
                m_flypathPtIndex = 0;                       // 到了飞行尾,将飞行路径当前坐标索引号重置为0,即从飞行路径起始点开始漫游
            }
            break;
        case 2:  // 模型选中进行红白颜色闪烁显示
            if (MATH_FLOAT_EQUAL_0(wireG)) {
                wireR = 1;
                wireG = 1;
                wireB = 1;
            } else {
                wireR = 1;
                wireG = 0;
                wireB = 0;
            }
            Invalidate(FALSE);
            break;
    }
    CView::OnTimer(nIDEvent);
}


/****************************************************************/
// Function: 根据漫游路径相临坐标点计算相机各参数
void CMy3DSymbolLibNewView::GetCameraCorrdinate(double x1, double y1, double z1, double x2, double y2, double z2) {
    // (x1,y1,x1):飞行路径当前点坐标
    // (x2,y2,x2):飞行路径下一点坐标
    if (m_FlyHeightType == GIS_FLY_STATICHEIGHT) {          // 固定高度飞行方式
        if (m_StaticHeight < 85)
            m_StaticHeight = 85;
        pCamera_->m_vLook.x = x2;  // 观察点x坐标
        pCamera_->m_vLook.y = m_StaticHeight;  // 观察点y坐标=y2+m_StaticHeight固定高度值
        pCamera_->m_vLook.z = z2;  // 观察点z坐标
        pCamera_->m_vEyePosition.x = x1;  // 视点x坐标
        pCamera_->m_vEyePosition.y = pCamera_->m_vLook.y;  // 视点y坐标=观察点y坐标
        pCamera_->m_vEyePosition.z = z1;  // 视点z坐标
    } else if (m_FlyHeightType == GIS_FLY_PATHHEIGHT) {  // 按相对高度(即沿路径)漫游时，需计算一个基本高度
        // 沿相对高度漫游
        pCamera_->m_vLook.x = x2;                                     // 观察点x坐标
        pCamera_->m_vLook.y = y2 + m_StaticHeight + 1;                    // 观察点y坐标=y2+m_StaticHeight固定高度值
        pCamera_->m_vLook.z = z2;                                     // 观察点z坐标
        // 求二点之间距离
        float distance = sqrt((x2 - x1) * (x2 - x1) + (z2 - z1) * (z2 - z1));
        // 根据倾角计算高度差
        float dh = distance * tan(MATH_DEG_TO_RAD(m_ViewUpDown));
        pCamera_->m_vEyePosition.x = x1;                              // 视点x坐标
        pCamera_->m_vEyePosition.y = pCamera_->m_vLook.y + dh;                  // 视点y坐标=观察点y坐标+高差
        pCamera_->m_vEyePosition.z = z1;                              // 视点z坐标
    }
}


/****************************************************************/
// Function: 按相对高度漫游方式
void CMy3DSymbolLibNewView::OnFlyRoutineheight() {
    if (m_FlayPath.GetSize() <= 0) {  // 如果飞行路径坐标点数量<=0，即飞行路径为空
        MessageBox("没有输入路径文件", "飞行浏览", MB_ICONWARNING);
        return;
    }
    m_fly_start_pause_Enable = TRUE;
    m_FlyHeightType = GIS_FLY_PATHHEIGHT;                   // 设置漫游类型为相对高度漫游
    m_StaticHeight = 0;                                     // 设置相对高差值
    m_flypathPtIndex = 0;                                   // 飞行路径坐标初始索引=0
    SetFLyTimer();                                          // 设置三维漫游计时器
}


/****************************************************************/
// Function: 设置菜单是否设置选中标识"√"
void CMy3DSymbolLibNewView::OnUpdateFlyRoutineheight(CCmdUI* pCmdUI) {
    pCmdUI->Enable(m_PathFlag == TRUE);                  // 根据是否具有有效飞行路径值设置菜单状态
    if (m_FlyHeightType == GIS_FLY_PATHHEIGHT)              // 如果当前是"沿相对高度漫游"方式
        pCmdUI->SetCheck(TRUE);                             // 菜单前设置选中标志"√"
    else
        pCmdUI->SetCheck(FALSE);                                // 否则不设置
}


/****************************************************************/
// Function: 开始/暂停漫游
void CMy3DSymbolLibNewView::OnFlyPlaypause() {
    if (m_FlyPause == FALSE) {                              // 如果不是暂停漫游,即处于漫游状态
        m_FlyPause = TRUE;                                  // 设置暂停标识m_FlyPause=TRUE
        KillTimer(1);                                       // 销毁定时器1
    } else {                                                // 如果处于漫游状态
        m_FlyPause = FALSE;                                 // 设置暂停标识m_FlyPause=FALSE
        SetFLyTimer();                                      // 设置飞行时间器,继续漫游
    }
}


/****************************************************************/
// Function: 根据m_FlyPause值设置菜单ID_FLY_PLAYPAUSE文本
void CMy3DSymbolLibNewView::OnUpdateFlyPlaypause(CCmdUI* pCmdUI) {
    pCmdUI->Enable(m_fly_start_pause_Enable == TRUE);
    if (m_FlyPause)                             // 如果处于漫游状态
        pCmdUI->SetText("开始漫游");             // 设置菜单ID_FLY_PLAYPAUSE文本
    else                                        // 如果不是暂停漫游,即处于漫游状态
        pCmdUI->SetText("暂停漫游");             // 设置菜单ID_FLY_PLAYPAUSE文本
}


/****************************************************************/
// Function: 停止漫游
void CMy3DSymbolLibNewView::OnFlyStop() {
    KillTimer(1);                       // 销毁定时器1
    m_flypathPtIndex = 0;               // 飞行路径坐标索引=0
    m_FlyPause = FALSE;                 // 暂停标识为FALSE
    m_far = 10000;                      // 恢复gluPerspective()函数定义平截头体的远剪裁平面的距离
    m_fly_start_pause_Enable = FALSE;   // []
}


/****************************************************************/
// Function: 单步前进
void CMy3DSymbolLibNewView::OnFlyOnestep() {
    // 如果飞行路径坐标索引>=0并且<飞行路径坐标总数-1,该条件表示的是
    // 只要飞行路径坐标索引没有到飞行路径尾,就可以执行单步前进
    if (m_flypathPtIndex >= 0 && m_flypathPtIndex < m_FlayPath.GetSize() - 1) {
        KillTimer(1);                               // 销毁定时器1
        m_FlyPause = TRUE;                          // 暂停标识为TRUE
        // 根据漫游路径相临坐标点计算相机各参数
        GetCameraCorrdinate(
            m_FlayPath.GetAt(m_flypathPtIndex)->x, \
            m_FlayPath.GetAt(m_flypathPtIndex)->y, \
            m_FlayPath.GetAt(m_flypathPtIndex)->z, \
            m_FlayPath.GetAt(m_flypathPtIndex + 1)->x, \
            m_FlayPath.GetAt(m_flypathPtIndex + 1)->y, \
            m_FlayPath.GetAt(m_flypathPtIndex + 1)->z
        );
        Invalidate(FALSE);
        ++m_flypathPtIndex;                         // 当前行路径坐标索引+1
    }
}


/****************************************************************/
// Function: 飞行视野扩大
void CMy3DSymbolLibNewView::OnFlyViewEnlarge() {
    m_ViewWideNarrow += 5.0f;                        // m_ViewWideNarrow值增加
    OnDraw(GetDC());                                 // 刷新三维场景
}


/****************************************************************/
// Function: 飞行视野减小
void CMy3DSymbolLibNewView::OnFlyViewSmall() {
    m_ViewWideNarrow -= 5.0f;                        // m_ViewWideNarrow值减小
    OnDraw(GetDC());                                 // 刷新三维场景
}


/****************************************************************/
// Function: 飞行高度增加
void CMy3DSymbolLibNewView::OnFlyHeightUp() {
    m_StaticHeight += 8;                            // 高度值增加(步长=8,可任意设定)
    OnDraw(GetDC());                                // 刷新三维场景
}


/****************************************************************/
// Function: 飞行高度降低
void CMy3DSymbolLibNewView::OnFlyHeightDown() {
    m_StaticHeight -= 8;                            // 高度值增加(步长=8,可任意设定)
    OnDraw(GetDC());                                // 刷新三维场景
}


/****************************************************************/
// Function: 飞行视角上倾(仰视)
void CMy3DSymbolLibNewView::OnFlyViewUp() {
    m_ViewUpDown += 1.0f;
    OnDraw(GetDC());                                // 刷新三维场景
}


/****************************************************************/
// Function: 飞行视角下倾(俯视)
void CMy3DSymbolLibNewView::OnFlyViewDown() {
    m_ViewUpDown -= 1.0f;
    OnDraw(GetDC());                                // 刷新三维场景
}


/****************************************************************/
// Function: 加速
void CMy3DSymbolLibNewView::OnFlySpeedUp() {
    m_flyspeed -= 2;                                // 飞行时的计时器时间间隔减少
    if (m_flyspeed <= 1)                            // 如果计时器时间间隔<=1,则有
        m_flyspeed = 1;
    SetFLyTimer();                                  // 设置飞行计时器
}


/****************************************************************/
// Function: 减速
void CMy3DSymbolLibNewView::OnFlySpeedDown() {
    m_flyspeed += 2;                                // 飞行时的计时器时间间隔增加
    SetFLyTimer();                                  // 设置飞行计时器
}


/****************************************************************/
// Function: 三维漫游调整热键帮助
void CMy3DSymbolLibNewView::DisplayHelp() {
    std::ostringstream help_info_str;
    help_info_str << " 向↑键   往前方向移动\n";
    help_info_str << " 向↓键   往后方向移动\n";
    help_info_str << " 向→键   往左方向移动\n";
    help_info_str << " 向←键   往右方向移动\n";
    help_info_str << "  J 键    飞行加速\n";
    help_info_str << "  M 键    飞行减速\n";
    help_info_str << "  I 键    飞行视野增大\n";
    help_info_str << "  O 键    飞行视野减小\n";
    help_info_str << "  G 键     升高飞行高度\n";
    help_info_str << "  B 键     降低飞行高度\n";
    help_info_str << "  H 键    飞行观察上倾\n";
    help_info_str << "  N 键    飞行观察下倾\n";
    help_info_str << "  P 键    开始/暂停漫游\n";
    help_info_str << "  S 键    停止漫游";
    MessageBox(help_info_str.str().c_str(), "三维漫游热键说明", MB_OK);
    // TextFlyHelp();
}

void CMy3DSymbolLibNewView::TextFlyHelp() {
    // 显示文字
    Font->Settext(350, 485, "向↑键   往前方向移动", hFont, 1, 0, 0);
    Font->Settext(350, 500, "向↓键   往后方向移动", hFont, 1, 0, 0);
    Font->Settext(350, 515, "向→键   往左方向移动", hFont, 1, 0, 0);
    Font->Settext(350, 530, "向←键   往右方向移动", hFont, 1, 0, 0);
    Font->Settext(550, 485, "J 键    飞行加速", hFont, 1, 0, 0);
    Font->Settext(550, 500, "M 键    飞行减速", hFont, 1, 0, 0);
    Font->Settext(550, 515, "I 键    飞行视野增大", hFont, 1, 0, 0);
    Font->Settext(550, 530, "O 键    飞行视野减小", hFont, 1, 0, 0);
    Font->Settext(750, 485, "H 键    飞行观察上倾", hFont, 1, 0, 0);
    Font->Settext(750, 500, "N 键    飞行观察下倾", hFont, 1, 0, 0);
    Font->Settext(750, 515, "P 键    开始/暂停漫游", hFont, 1, 0, 0);
    Font->Settext(750, 530, "S 键    停止漫游", hFont, 1, 0, 0);
}


/****************************************************************/
// Function: 初始化显示列表
void CMy3DSymbolLibNewView::InitList() {
    pNClock_->m_ClockList = glGenLists(1);
    m_SkyList = pNClock_->m_ClockList + 1;                   // 背景天空显示列表
    pNClock_->MakeClockList();                                // 创建时钟指北针显示列表
    m_Rail3DwayList = pNClock_->m_ClockList + 2;              // 线路三维模型显示列表
}


/****************************************************************/
// Function: 时钟指北针的绘制
void CMy3DSymbolLibNewView::DrawClock() {
    glPushAttrib(GL_CURRENT_BIT);                   // 保存现有颜色属性
    glPushMatrix();                                 // 压入矩阵堆栈
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);      // 线绘制方式
    glDisable(GL_TEXTURE_2D);                       // 关闭纹理
    SetClockProjectionNavigate();                   // 设置指北针的投影参数
    glCallList(pNClock_->m_ClockList);                        // 调用指北针时钟的显示列表
    pNClock_->DrawNorthPt();                                  // 绘制指北针
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);      // 填充绘制方式
    glEnable(GL_TEXTURE_2D);                        // 打开纹理
    glLineWidth(1.0);                               // 设置线宽
    glColor3f(1.0, 1.0, 1.0);                       // 设置颜色
    glPopMatrix();                                  // 弹出矩阵堆栈
    glPopAttrib();
}

void CMy3DSymbolLibNewView::SetClockProjectionNavigate() {
    float wh = 120;                                 // 设置时钟的高度
    glViewport(0, WinViewY - wh, wh, wh);           // 设置视口位置和大小
    glMatrixMode(GL_PROJECTION);                    // 设置当前矩阵为透视矩阵
    glLoadIdentity();                               // 将当前矩阵置换为单位阵
    glOrtho(0.0f, 1.0, 0.0f, 1.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);                     // 设置当前矩阵为模型矩阵
    glLoadIdentity();                               // 将当前矩阵置换为单位阵
}


/****************************************************************/
// Function: 根据相机的视点坐标和观察点坐标计算时钟指北针指向角度
void CMy3DSymbolLibNewView::GetNorthPtangle() {
    float dx, dz, ar;
    dx = pCamera_->m_vEyePosition.x - pCamera_->m_vLook.x;              // 相机视点与观察点x坐标之差
    dz = pCamera_->m_vEyePosition.z - pCamera_->m_vLook.z;              // 相机视点与观察点z坐标之差
    if (dx == 0) {                                  // 如果dx==0
        if (dz >= 0)                                // 如果dz>=0
            pNClock_->m_NorthPtangle = 90;                    // 指北针初始指向角度=90，指向屏幕里面（Z轴负方向）
        else
            pNClock_->m_NorthPtangle = 270;                   // 指北针初始指向角度=270，指向屏幕外面（Z轴正方向）
    } else {
        if (dx > 0) {
            if (dz > 0) {                           // 第2象限
                ar = fabs(atan(dx / dz));
                pNClock_->m_NorthPtangle = 90 + ar * HDANGLE;  // 指北针初始指向角度
            } else {                                // 第3象限
                ar = fabs(atan(dx / dz));
                pNClock_->m_NorthPtangle = 270 - ar * HDANGLE;  // 指北针初始指向角度
            }
        }
        if (dx < 0) {
            if (dz > 0) {                           // 第1象限
                ar = fabs(atan(dx / dz));
                pNClock_->m_NorthPtangle = 90 - ar * HDANGLE;  // 指北针初始指向角度
            } else {                                // 第4象限
                ar = fabs(atan(dx / dz));
                pNClock_->m_NorthPtangle = 270 + ar * HDANGLE;  // 指北针初始指向角度
            }
        }
    }
}


/****************************************************************/
// Function: 生成绘制背景天空显示列表
void CMy3DSymbolLibNewView::MakeSkykList() {
    glNewList(m_SkyList , GL_COMPILE);
    pSkyBox_->CreateSkyBox();
    glEndList();
}


/****************************************************************/
// Function: 绘制天空背景
void CMy3DSymbolLibNewView::DrawSky() {
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
    glPushMatrix();
    if (m_bShowbreviary) {                  // 如果显示导航图
        SetSkyProjectionNavigate();         // 设置导航图的背景天空投影
    }
    glPopMatrix();
    SetSkyProjection();                     // 设置背景天空投影
    glCallList(m_SkyList);
    glPopMatrix();
    glPopAttrib();
}


/****************************************************************/
// Function: 背景天空投影设置
void CMy3DSymbolLibNewView::SetSkyProjection() {
    glViewport(0, 0, WinViewX, WinViewY);             // 设置视口大小和位置
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0 + m_ViewWideNarrow, static_cast<float>(WinViewX) / static_cast<float>(WinViewY), m_near, m_far);
    glMatrixMode(GL_MODELVIEW);                             // 定义矩阵为模型模型矩阵
    glLoadIdentity();                                       // 将当前矩阵置换为单位矩阵
    SetCamra();
}


/****************************************************************/
// Function: 背景天空导航图投影设置
void CMy3DSymbolLibNewView::SetSkyProjectionNavigate() {
    glClearDepth(1.0f);                             // 设置初始化深度缓存值
    glEnable(GL_DEPTH_TEST);                        // 启用深度测试
    glDepthFunc(GL_LESS);                           // 在调用glEnable(GL_DEPTH_TEST); 开启这个功能以后，当深度变化小于当前深度值时，更新深度值。
    glViewport(WinViewX * 5 / 6,  WinViewY * 5 / 6, WinViewX / 6,  WinViewY / 6);  // 设置视口大小
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0 + m_ViewWideNarrow, static_cast<float>(WinViewX) / static_cast<float>(WinViewY), m_near, m_far);
    // 设置正射投影视景体
    glMatrixMode(GL_MODELVIEW);                         // 定义矩阵为模型模型矩阵
    glLoadIdentity();                                   // 将当前矩阵置换为单位矩阵
    glClearColor(0.53, 0.81, 0.92, 0.0);                // 设置刷新背景色SkyBlue: 135,206,235
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // 刷新背景
    glLoadIdentity();                                   // 重置当前的模型观察矩阵
    SetCamra();
}


/****************************************************************/
// Function: 导入3DS模型 设置参数
void CMy3DSymbolLibNewView::On3dsModelLoad() {
    // TODO(jason): 在此添加命令处理程序代码
    CString tt, stt;
    FILE* fp;
    CString modelFileFormat = ".3DS";
    PModelParamStruct p3d;
    if (m_i3DModelNum < MODEL_NUM_MAX) {
        CDialogModelList dlg1;
        dlg1.m_Dir = m_AllDataPath + "\\" + pT3DModelData_->m_3DModelFolder;
        dlg1.m_format = ".bmp";
        dlg1.m_type = "3DS";
        CString selectItem;
        if (dlg1.DoModal() == IDOK) {
            selectItem = dlg1.m_selectItem;
            pT3DModelData_->m_3DModelPath = dlg1.m_Dir + "\\" + selectItem + modelFileFormat;
        } else {
            return;
        }
        if ((fp = fopen(pT3DModelData_->m_3DModelPath, "r")) == NULL) {
            MessageBox("3D模型文件不存在!", "初始化3D模型", MB_ICONINFORMATION + MB_OK);
            LOGGER_ERROR << "3D模型文件不存在!";
            exit(-1);
        }
        p3d = new CModelParamStruct;
        CModelParamStruct a = {0};
        *p3d = a;
        p3d->modelID = m_i3DModelNum;
        p3d->isDeleted = false;
        p3d->modelPath = pT3DModelData_->m_3DModelPath;
        p3d->m_3DS_Mode_Texture_PATH_NAME = dlg1.m_Dir + "\\" + selectItem + ".bmp";
        p3d->posX = 389;
        p3d->posZ = -389;
        p3d->scale = 1;
        ModelParam dlg;
        dlg.m_strTitle = "3D模型参数初始化";
        if (spaceSearchInfo_.m_QueryType == QUERY_COORDINATE && IsSearchPoint_) {  // 当前为查询模式,并且已经查询了
            p3d->posX = pt1[0];
            p3d->posZ = pt1[2];
        }
        PModelParamStructToModelParamDlg(dlg, p3d);
        if (dlg.DoModal() == IDOK) {
            ModelParamDlgToPModelParamStruct(dlg, p3d);
            Load3DModel(p3d, MODEL_NEW);
            m_i3DModelNum++;
        }
        fclose(fp);
    }
}

void CMy3DSymbolLibNewView::Draw3DModel(PModelParamStruct model) {
    glPushMatrix();                                         // 压入堆栈
    t3DBox t3dBox;
    t3dBox.l = g_3DModel[model->modelID].t3DModelBox.l * model->scale;
    t3dBox.w = g_3DModel[model->modelID].t3DModelBox.w * model->scale;
    t3dBox.h = g_3DModel[model->modelID].t3DModelBox.h * model->scale;
    // 获取地面高度
    int32 y = GetHeight(static_cast<float>(model->posX), static_cast<float>(model->posZ)) + t3dBox.h / 2 + model->posY;
    glTranslatef(model->posX, y, model->posZ);              // 模型定位
    glRotatef(model->rotY, 0.0, 1.0, 0.0);                  // 模型旋转
    glRotatef(model->rotX, 1.0, 0.0, 0.0);                  // 模型旋转
    glRotatef(model->rotZ, 0.0, 0.0, 1.0);                  // 模型旋转
    p3ds_->Show3ds(model->modelID, 0, 0.0f, 0, model->scale);  // 显示3ds模型
    glPushAttrib(GL_CURRENT_BIT);                           // 保存现有颜色属性
    glDisable(GL_TEXTURE_2D);                               // 取消贴图
    glPushMatrix();                                         // 压入堆栈
    glLineWidth(3);                                         // 线宽2
    glPushAttrib(GL_CURRENT_COLOR);
    if (m_3DModel.GetAt(model->modelID)->modelSelected) {
        glColor3f(wireR, wireG, wireB);
        auxWireBox(t3dBox.w , t3dBox.h, t3dBox.l);
    }
    glPopMatrix();
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glPopAttrib();
    glPopMatrix();
}


/****************************************************************/
// Function: 3d模型选择以及参数设置
void CMy3DSymbolLibNewView::On3dsModelSelectSet() {
    // TODO(jason): 在此添加命令处理程序代码
    bIsSelect3DModel_ = !bIsSelect3DModel_;
    if (bIsSelect3DModel_) {
        m_OperateType = SELECT;
        m_mouseShape = MOUSE_SHAPE_SLECT;
        spaceSearchInfo_.m_QueryType = -1;
    } else {
        m_OperateType = -1;
        // 当不是选择模式时，关闭闪烁定时器
        if (m_bFlash) {
            KillTimer(2);
            m_bFlash = false;
            for (uint32 i = 0; i < m_pSelectedModelSet.size(); ++i) {  // i++ 要多一个临时变量来存储，所以使用++i
                if (m_pSelectedModelSet.at(i)->modelType == MODEL_3DS)
                    m_3DModel.GetAt(m_pSelectedModelSet.at(i)->modelID)->modelSelected = false;
            }
            m_pSelectedModelSet.clear();
        }
        m_bMouseMoveSelect = false;
        m_mouseShape = MOUSE_SHAPE_ARROW;
    }
    Invalidate(FALSE);
}

void CMy3DSymbolLibNewView::OnUpdate3dsModelSelectSet(CCmdUI* pCmdUI) {
    pCmdUI->SetCheck(m_OperateType == SELECT);
}


/****************************************************************/
// Function: 移动模型,从左键按下到左键弹起的距离
void CMy3DSymbolLibNewView::OnLButtonUp(UINT nFlags, CPoint point) {
    // TODO(jason): 在此添加消息处理程序代码和/或调用默认值
    if (m_OperateType == MOVE) {  // 移动选中3D模型
        m_oldMousePos = point;
        ScreenToGL(point);
    }
    m_bIsLBtnDown = false;
    CView::OnLButtonUp(nFlags, point);
}

void CMy3DSymbolLibNewView::On3dsModelMouseMove() {
    // TODO(jason): 在此添加命令处理程序代码
    bIsMouseMove3DModel_ = !bIsMouseMove3DModel_;
    if (bIsMouseMove3DModel_) {
        m_OperateType = MOVE;
    } else {
        m_OperateType = -1;
    }
    Invalidate(FALSE);
}

void CMy3DSymbolLibNewView::OnUpdate3dsModelMouseMove(CCmdUI* pCmdUI) {
    pCmdUI->SetCheck(m_OperateType == MOVE);
}


/****************************************************************/
// Function: 在坐标转换时判断鼠标是否落入3D模型空间范围内
void CMy3DSymbolLibNewView::JudgeModelSelected(PCordinate ppt) {
    // 获取模型中三维点极值
    int32 minx, maxx, minz, maxz;
    // 遍历所有的3D模型,判断是否在范围内
    for (int32 j = 0; j < m_i3DModelNum; ++j) {
        t3DBox t3dBox;
        t3dBox.w = m_3DModel.GetAt(j)->scale * g_3DModel[j].t3DModelBox.w;
        t3dBox.h = m_3DModel.GetAt(j)->scale * g_3DModel[j].t3DModelBox.h;
        t3dBox.l = m_3DModel.GetAt(j)->scale * g_3DModel[j].t3DModelBox.l;
        POINT pt;
        pt.x = m_3DModel.GetAt(j)->posX;
        pt.y = m_3DModel.GetAt(j)->posZ;
        minx = pt.x - (t3dBox.l * 1.5) / 2;
        maxx = pt.x + (t3dBox.l * 1.5) / 2;
        minz = pt.y - (t3dBox.w * 1.5) / 2;
        maxz = pt.y + (t3dBox.w * 1.5) / 2;
        // 因为当前模型为鼠标移动模型时就不能改变模型的选中状态
        if ((ppt->x >= minx && ppt->x <= maxx) && (ppt->z >= minz && ppt->z <= maxz)) {
            if (m_OperateType == MOVE) {
                m_3DModel.GetAt(j)->modelSelected = true;
            } else {
                m_3DModel.GetAt(j)->modelSelected = !(m_3DModel.GetAt(j)->modelSelected);
            }
        } else {
            m_3DModel.GetAt(j)->modelSelected = false;
        }
    }
}


/****************************************************************/
// Function: 导入景观树 设置参数
void CMy3DSymbolLibNewView::OnTreeLoad() {
    // TODO(jason): 在此添加命令处理程序代码
    CString tt, stt;
    FILE* fp;
    CString treeTexPath;
    CString treeFileFormat = ".BMP";
    if (m_iTreeModelNum < 50) {
        CDialogModelList dlg1;
        dlg1.m_Dir = m_AllDataPath + "\\" + pTreeModelData_->m_TreeModelFolder;
        dlg1.m_format = ".bmp";
        dlg1.m_type = "Tree";
        if (dlg1.DoModal() == IDOK) {
            CString selectItem = dlg1.m_selectItem;
            treeTexPath = dlg1.m_Dir + "\\" + selectItem + treeFileFormat;
        } else {
            return;
        }
        if ((fp = fopen(treeTexPath, "r")) == NULL) {
            MessageBox("景观树文件不存在!", "初始化景观树模型", MB_ICONINFORMATION + MB_OK);
            exit(-1);
        }
        ptree = new CModelStruct;
        ptree->iModelNum = m_iTreeModelNum;
        ptree->strModelPath = treeTexPath;
        // 非模式对话框
        paramSet_modeless_dlg = new C3DModelParamSet(this);
        paramSet_modeless_dlg->Create();
        paramSet_modeless_dlg->CenterWindow();
        paramSet_modeless_dlg->m_strTitle = "景观树模型  参数初始化";
        paramSet_modeless_dlg->m_modeParam.type = "tree";
        paramSet_modeless_dlg->ShowWindow(SW_SHOW);
        fclose(fp);
    } else {
        MessageBox("树木的大小超出了50!");
    }
    LOGGER_INFO << "OnTreeLoad( )";
}


/*************************************************************************/
// Function: 树的贴图需要透明显示，透明显示要求树的图片应该是16位色的BMP位图
void CMy3DSymbolLibNewView::LoadT16(char* filename, GLuint& texture) {  // NOLINT
    glGenTextures(1, &texture);                                         // 获取1个未使用的贴图名称
    glBindTexture(GL_TEXTURE_2D, texture);                              // 选择要绑定的贴图（纹理）
    BITMAPINFOHEADER bitHeader;                                         // 定义位图结构
    uint8* buffer;                                                      // 定义位图指针
    buffer = LoadBitmapFileWithAlpha(filename, &bitHeader);             // 调入位图
    gluBuild2DMipmaps(GL_TEXTURE_2D,                                    // 创建一个2D贴图（纹理）
                      4,                                                              // 使用3种颜色（RGB）+颜色深度
                      bitHeader.biWidth,                                              // 图像宽
                      bitHeader.biHeight,                                             // 图像高
                      GL_RGBA,                                                        // 红绿蓝顺序
                      GL_UNSIGNED_BYTE,                                               // 图像的数据类型是字节
                      buffer                                                          // 指定贴图（纹理）数据
                     );                                                               // 创建贴图（纹理）
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);                   // 缩小滤波
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);                   // 放大滤波
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);    // 双线性滤波
    free(buffer);                                                                       // 释放位图数据
}


/********************************************************************/
// Function: 显示特殊平面树，场景旋转时树也跟着旋转，始终是正面对着用户
void CMy3DSymbolLibNewView::ShowTree(int32 i) {
    float x, y, z;
    x = m_TreeModel.GetAt(i)->xPos;
    z = m_TreeModel.GetAt(i)->zPos;
    float h = 3;
    y = GetHeight(x, z) + m_TreeModel.GetAt(i)->hPos + h;
    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0);
    float mat[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, mat);              // 获取视图矩阵
    CVector3 X(mat[0], mat[4], mat[8]);
    CVector3 Z(mat[1], mat[5], mat[9]);
    glBindTexture(GL_TEXTURE_2D, g_cactus[i]);
    CVector3 pos(x, y, z);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f((pos + (X + Z) * -h).x, (pos + (X + Z) * -h).y, (pos + (X + Z) * -h).z);  // 左下点
    glTexCoord2f(1.0, 0.0);
    glVertex3f((pos + (X - Z)* h).x, (pos + (X - Z)* h).y, (pos + (X - Z)* h).z);  // 右下点
    glTexCoord2f(1.0, 1.0);
    glVertex3f((pos + (X + Z)* h).x, (pos + (X + Z)* h).y, (pos + (X + Z)* h).z);  // 右上点
    glTexCoord2f(0.0, 1.0);
    glVertex3f((pos + (Z - X)* h).x, (pos + (Z - X)* h).y, (pos + (Z - X)* h).z);  // 左上点
    glEnd();
    glDisable(GL_ALPHA);
    glDisable(GL_BLEND);
    glPopMatrix();
}


/****************************************************************/
// Function: 导入城市标识,行政点,咖啡店,厕所,服务区等
void CMy3DSymbolLibNewView::OnCitySymbolLoad() {
    CString tt, stt;
    FILE* fp;
    CString citySymbolTexPath;
    CString citySymbolFileFormat = ".png";
    if (m_iCitySymbolModelNum < 50) {
        CDialogModelList dlg1;
        dlg1.m_Dir = m_AllDataPath + "\\" + pCitySymbolData_->m_CitySymbolFolder;
        dlg1.m_format = ".png";
        dlg1.m_type = "City";
        if (dlg1.DoModal() == IDOK) {
            CString selectItem = dlg1.m_selectItem;
            citySymbolTexPath = dlg1.m_Dir + "\\" + selectItem + citySymbolFileFormat;
        } else {
            return;
        }
        if ((fp = fopen(citySymbolTexPath, "r")) == NULL) {
            MessageBox("城市标识符号文件不存在!", "初始化城市标识符号", MB_ICONINFORMATION + MB_OK);
            LOGGER_ERROR << "城市标识符号文件不存在!";
            exit(-1);
        }
        pCitySymbol = new CModelStruct;
        pCitySymbol->iModelNum = m_iCitySymbolModelNum;
        pCitySymbol->strModelPath = citySymbolTexPath;
        // 非模式对话框
        paramSet_modeless_dlg = new C3DModelParamSet(this);
        paramSet_modeless_dlg->Create();
        paramSet_modeless_dlg->CenterWindow();
        paramSet_modeless_dlg->m_strTitle = "城市标识  参数初始化";
        paramSet_modeless_dlg->m_modeParam.type = "CitySymbol";
        paramSet_modeless_dlg->ShowWindow(SW_SHOW);
        fclose(fp);
    }
}



/****************************************************************/
// Function:显示城市符号
void CMy3DSymbolLibNewView::ShowCitySymbol(int32 i) {
    float x, y, z;
    x = m_CitySymbolModel.GetAt(i)->xPos;
    z = m_CitySymbolModel.GetAt(i)->zPos;
    float h = 3.2f;
    y = GetHeight(x, z) + m_CitySymbolModel.GetAt(i)->hPos + h;
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER , 0.9);                      // 0.5可以换成任何在0~1之间的数
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  // 背景为白色
    float mat[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, mat);              // 获取视图矩阵
    CVector3 X(mat[0], mat[4], mat[8]);
    CVector3 Z(mat[1], mat[5], mat[9]);
    glBindTexture(GL_TEXTURE_2D, g_citySymbolTex[i]);
    CVector3 pos(x, y, z);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f((pos + (X + Z) * -h).x, (pos + (X + Z) * -h).y, (pos + (X + Z) * -h).z);  // 左下点
    glTexCoord2f(1.0, 0.0);
    glVertex3f((pos + (X - Z)* h).x, (pos + (X - Z)* h).y, (pos + (X - Z)* h).z);  // 右下点
    glTexCoord2f(1.0, 1.0);
    glVertex3f((pos + (X + Z)* h).x, (pos + (X + Z)* h).y, (pos + (X + Z)* h).z);  // 右上点
    glTexCoord2f(0.0, 1.0);
    glVertex3f((pos + (Z - X)* h).x, (pos + (Z - X)* h).y, (pos + (Z - X)* h).z);  // 左上点
    glEnd();
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_ALPHA);
    glDisable(GL_BLEND);
    glPopMatrix();
}


/****************************************************************/
// Function: 透明PNG 纹理加载
void CMy3DSymbolLibNewView::LoadPNG(const char* fileName, GLuint& texture) {  // NOLINT
    glGenTextures(1, &texture);                     // 获取1个未使用的贴图名称
    glBindTexture(GL_TEXTURE_2D, texture);          // 选择要绑定的贴图（纹理）
    BITMAP bm;
    CImage img;                                     // 需要头文件atlimage.h
    HRESULT hr = img.Load(fileName);
    if (!SUCCEEDED(hr)) {                            // 文件加载失败
        MessageBox(NULL, "文件加载失败", MB_OK);
        LOGGER_ERROR << "文件加载失败!";
    }
    HBITMAP hbmp = img;
    GetObject(hbmp, sizeof(bm), &bm);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glPixelStoref(GL_PACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, bm.bmWidth, bm.bmHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, bm.bmBits);  // 这里不是GL_RGB,一定要设置成4和GL_BGRA，否则不能背景透明，一般的纹理是设置为3和GL_BGR，这样就不能透明化显示
}


/****************************************************************/
// Function: 导入天气预报图片
void CMy3DSymbolLibNewView::OnWeatherLoad() {
    CString tt, stt;
    FILE* fp;
    CString weatherSymbolTexPath;
    CString weatherFileFormat = ".bmp";
    if (1) {
        CDialogModelList dlg1;
        dlg1.m_Dir = m_AllDataPath + "\\" + m_WeatherFolder;
        dlg1.m_format = ".bmp";
        dlg1.m_type = "Weather";
        if (dlg1.DoModal() == IDOK) {
            CString selectItem = dlg1.m_selectItem;
            // 修改了原程序在保存场景文件时未能保存天气信息的问题
            m_WeatherTex = selectItem + weatherFileFormat;
            weatherSymbolTexPath = dlg1.m_Dir + "\\" + selectItem + weatherFileFormat;
        } else {
            return;
        }
        if ((fp = fopen(weatherSymbolTexPath, "r")) == NULL) {
            MessageBox("天气符号文件不存在!", "初始化天气符号", MB_ICONINFORMATION + MB_OK);
            LOGGER_ERROR << "天气符号文件不存在!";
            exit(-1);
        }
        char cc[256];
        // sprintf(cc, weatherSymbolTexPath);
        _snprintf_s(cc, sizeof(cc), sizeof(cc) - 1, weatherSymbolTexPath);
        LoadT8(cc, g_weatherTex);
        bIsWeatherLoad_ = true;
        fclose(fp);
    }
}


/****************************************************************/
// Function: 显示天气图标
void CMy3DSymbolLibNewView::ShowWeather() {
    glPushAttrib(GL_CURRENT_BIT);                   // 保存现有颜色属性
    glPushMatrix();                                 // 压入矩阵堆栈
    glEnable(GL_TEXTURE_2D);
    float wh = 50;                                  // 设置时钟的高度
    glViewport(WinViewX * 5 / 6 - wh, WinViewY - wh, wh, wh);       // 设置视口位置和大小
    glMatrixMode(GL_PROJECTION);                     // 设置当前矩阵为透视矩阵
    glLoadIdentity();                               // 将当前矩阵置换为单位阵
    glOrtho(0.0f, 1.0, 0.0f, 1.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);                      // 设置当前矩阵为模型矩阵
    glLoadIdentity();                               // 将当前矩阵置换为单位阵
    // 设置BACK纹理参数
    glBindTexture(GL_TEXTURE_2D, g_weatherTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // 开始绘制
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(1, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(1, 1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(0, 1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(0, 0);
    glEnd();
    glPopMatrix();                                  // 弹出矩阵堆栈
    glPopAttrib();
    glViewport(0, 0, WinViewX, WinViewY);           // 设置视口大小和位置
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0 + m_ViewWideNarrow , static_cast<float>(WinViewX) / static_cast<float>(WinViewY) , m_near , m_far);
    glMatrixMode(GL_MODELVIEW);                     // 定义矩阵为模型模型矩阵
    glLoadIdentity();                               // 将当前矩阵置换为单位矩阵
}


/****************************************************************/
// Function: 参数设置对话框内变量直接全部赋值给结构体
void CMy3DSymbolLibNewView::C3DModelParamSetTOPModelStruct(const C3DModelParamSet& model, const PModelStruct& pStruct) {
    pStruct->angle = model.angle;
    pStruct->hPos = model.hPos;
    pStruct->iDisplayType = model.iDisplayType;
    // pStruct->iModelNum = model.
    pStruct->iRotateX = model.iRotateX;
    pStruct->iRotateY = model.iRotateY;
    pStruct->iRotateZ = model.iRotateZ;
    pStruct->isSelected = false;
    pStruct->radiu = model.radiu;
    pStruct->scale = model.scale;
    // pStruct->strModelPath =
    pStruct->xPos = model.xPos;
    pStruct->zPos = model.zPos;
}
void CMy3DSymbolLibNewView::C3DModelParamSetTOPModelStruct(C3DModelParamSet* model, PModelStruct& pStruct) {  // NOLINT
    pStruct->angle = model->angle;
    pStruct->hPos = model->hPos;
    pStruct->iDisplayType = model->iDisplayType;
    pStruct->iRotateX = model->iRotateX;
    pStruct->iRotateY = model->iRotateY;
    pStruct->iRotateZ = model->iRotateZ;
    pStruct->isSelected = false;
    pStruct->radiu = model->radiu;
    pStruct->scale = model->scale;
    pStruct->xPos = model->xPos;
    pStruct->zPos = model->zPos;
}


/****************************************************************************/
// Function: 导入3D立体景观树，实质上是将平面树纹理绕Y轴旋转90度实现二次贴纹理
void CMy3DSymbolLibNewView::On3dTreeLoad() {
    CString tt, stt;
    FILE* fp;
    CString treeTexPath;
    CString treeFileFormat = ".BMP";
    if (m_i3DTreeModelNum < 50) {
        CDialogModelList dlg1;
        dlg1.m_Dir = m_AllDataPath + "\\" + pTreeModelData_->m_TreeModelFolder;
        dlg1.m_format = ".bmp";
        dlg1.m_type = "3DTree";
        if (dlg1.DoModal() == IDOK) {
            CString selectItem = dlg1.m_selectItem;
            treeTexPath = dlg1.m_Dir + "\\" + selectItem + treeFileFormat;
        } else {
            return;
        }
        if ((fp = fopen(treeTexPath, "r")) == NULL) {
            MessageBox("景观树文件不存在!", "初始化景观树模型", MB_ICONINFORMATION + MB_OK);
            LOGGER_ERROR << "景观树文件不存在!";
            exit(-1);
        }
        p3dtree = new CModelStruct;
        p3dtree->iModelNum = m_i3DTreeModelNum;
        p3dtree->strModelPath = treeTexPath;
        // 非模式对话框
        paramSet_modeless_dlg = new C3DModelParamSet(this);
        paramSet_modeless_dlg->Create();
        paramSet_modeless_dlg->CenterWindow();
        paramSet_modeless_dlg->m_strTitle = "景观树模型  参数初始化";
        paramSet_modeless_dlg->m_modeParam.type = "3dtree";
        paramSet_modeless_dlg->ShowWindow(SW_SHOW);
        fclose(fp);
    } else {
        MessageBox("树木的大小超出了50!");
        LOGGER_WARNING << "树木的大小超出了50!";
    }
}


/****************************************************************************/
// Function: 自定义消息响应,非模式对话框(非3DS模型参数对话框)
LRESULT CMy3DSymbolLibNewView::OnGoodBye(WPARAM wParam, LPARAM lParam) {
    // 确定
    if (wParam == IDOK) {
        if (paramSet_modeless_dlg->m_modeParam.type == "3dtree") {
            C3DModelParamSetTOPModelStruct(paramSet_modeless_dlg, p3dtree);
            m_3DTreeModel.Add(p3dtree);
            char cc[256];
            // sprintf(cc, p3dtree->strModelPath);
            _snprintf_s(cc, sizeof(cc), sizeof(cc) - 1, p3dtree->strModelPath);
            LoadT16(cc, g_cactus3DTree[m_i3DTreeModelNum]);
            m_i3DTreeModelNum ++;
            paramSet_modeless_dlg->DestroyWindow();
            m_isSetXYByMouse = 0;
        } else if (paramSet_modeless_dlg->m_modeParam.type == "tree") {
            C3DModelParamSetTOPModelStruct(paramSet_modeless_dlg, ptree);
            m_TreeModel.Add(ptree);
            char cc[256];
            // sprintf(cc, ptree->strModelPath);
            _snprintf_s(cc, sizeof(cc), sizeof(cc) - 1, ptree->strModelPath);
            LoadT16(cc, g_cactus[m_iTreeModelNum]);
            m_iTreeModelNum ++;
            paramSet_modeless_dlg->DestroyWindow();
            m_isSetXYByMouse = 0;
        } else if (paramSet_modeless_dlg->m_modeParam.type == "CitySymbol") {
            C3DModelParamSetTOPModelStruct(paramSet_modeless_dlg, pCitySymbol);
            m_CitySymbolModel.Add(pCitySymbol);
            char cc[256];
            // sprintf(cc, pCitySymbol->strModelPath);
            _snprintf_s(cc, sizeof(cc), sizeof(cc) - 1, pCitySymbol->strModelPath);
            LoadPNG(cc, g_citySymbolTex[m_iCitySymbolModelNum]);
            m_iCitySymbolModelNum ++;
            paramSet_modeless_dlg->DestroyWindow();
            m_isSetXYByMouse = 0;
        }
    } else if (wParam == IDCANCEL) {  // 取消
        paramSet_modeless_dlg->DestroyWindow();
        m_isSetXYByMouse = 0;
    } else if (wParam == SET_XY_BY_MOUSE_TRUE) {  // checkbox选中状态
        m_isSetXYByMouse = paramSet_modeless_dlg->isSetXYByMouse;
    } else if (wParam == SET_XY_BY_MOUSE_FALSE) {  // checkbox非选中状态
        m_isSetXYByMouse = paramSet_modeless_dlg->isSetXYByMouse;
    }
    return 0L;
}


/****************************************************************************/
// Function: 显示3D立体景观树
void CMy3DSymbolLibNewView::Show3DTree(int32 i) {
    float x, y, z;
    x = m_3DTreeModel.GetAt(i)->xPos;
    z = m_3DTreeModel.GetAt(i)->zPos;
    float h = 3.0f;
    glPushMatrix();
    y = GetHeight(x, z) + m_3DTreeModel.GetAt(i)->hPos + h;
    glTranslatef(x, y, z);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0);
    glBindTexture(GL_TEXTURE_2D, g_cactus3DTree[i]);
    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(h, 0, 0.0f);        // 右上点
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0, 0, 0.0f);        // 右上点
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, h, 0.0f);        // 右下点
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(h, h, 0.0f);        // 左下点
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(h / 2, 0, h / 2);  // 将坐标移到树干中心位置，进行旋转，生成立体景观树
    glRotated(90, 0, 1, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(h, 0, 0.0f);        // 右上点
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0, 0, 0.0f);        // 右上点
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, h, 0.0f);        // 右下点
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(h, h, 0.0f);        // 左下点
    glEnd();
    glPopMatrix();
    glDisable(GL_ALPHA);
    glDisable(GL_BLEND);
    glPopMatrix();
}


/****************************************************************************/
// Function: 滚轮缩放,当选中某个模型时就对模型进行缩放，否则是缩放整个视景窗口
BOOL CMy3DSymbolLibNewView::OnMouseWheel(UINT nFlags, int16 zDelta, CPoint pt) {
    // 缩放选中模型大小
    if (m_OperateType == SCALE) {
        if (m_selectedModelID != -1) {  // 当前鼠标拾取某个模型
            // 缩放整个视景窗口
            if (zDelta > 0) {       // 向前滚动，放大
                m_3DModel.GetAt(m_selectedModelID)->scale *= 1.1;
            } else if (zDelta < 0) {
                float oldScale = m_3DModel.GetAt(m_selectedModelID)->scale;
                m_3DModel.GetAt(m_selectedModelID)->scale *= 0.9;
                if (m_3DModel.GetAt(m_selectedModelID)->scale <= 0) {
                    m_3DModel.GetAt(m_selectedModelID)->scale = oldScale;
                }
            }
        }
    } else {
        // 缩放整个视景窗口
        if (zDelta > 0) {           // 向前滚动，放大
            m_ViewWideNarrow += ((zDelta / 120) + 0.1);
        } else if (zDelta < 0) {
            zDelta = - zDelta;
            m_ViewWideNarrow -= ((zDelta / 120) - 0.1);
        }
    }
    InvalidateRect(NULL, false);
    return CView::OnMouseWheel(nFlags, zDelta, pt);
}


// 判断射线与AABB包围盒是否相交，以此来判断是否与场景中立体模型相交，同时需要另一个检测是否与平面模型相交
/*
* Woo提出的方法，先判断矩形边界框的哪个面会相交，
* 再检测射线与包含这个面的平面的相交性。
* 如果交点在盒子中，那么射线与矩形边界框相交，
* 否则不存在相交
*/
// 和参数射线的相交性测试，如果不相交则返回值是一个非常大的数(大于1)
// 如果相交，返回相交时间t
// t为0-1之间的值
float CMy3DSymbolLibNewView::RayIntersect(
    CVector3& rayStart,                  // 射线起点
    CVector3& rayDir,                    // 射线长度和方向
    CVector3& returnNormal,              // 可选的，相交点处法向量
    CVector3& min,
    CVector3& max
) {
    // 如果未相交则返回这个大数
    const float kNoIntersection = 1e30f;
    // 检查点在矩形边界内的情况，并计算到每个面的距离
    bool inside = true;  // 点在矩形边界内的情况,是指射线起点在边界内么？
    float xt, xn = 0.0f;
    if (rayStart.x < min.x) {  // 如果射线的起点在左边界以左
        xt = min.x - rayStart.x;  // 求得从射线起点到左边界的向量的x分量
        if (xt > rayDir.x) {
            return kNoIntersection;    // 如果射线更偏左则无法相交
        }
        // 这里是什么意思？
        // 是指从射线起点到物体包围盒边界处向量偏移射线方向的比例么？
        xt /= rayDir.x;
        inside = false;  // 是指射线的起点不在矩形边界内么？
        xn = -1.0f;
    } else if (rayStart.x > max.x) {  // 如果射线的起点在左边界以右
        xt = max.x - rayStart.x;  // 求得从射线起点到右边界的xt
        if (xt < rayDir.x) {
            return kNoIntersection;    // 如果射线更偏右则无法相交
        }
        xt /= rayDir.x;
        inside = false;
        xn = 1.0f;
    } else {
        xt = -1.0f;  // 是指射线起点在物体包围盒内么？
    }
    float yt, yn = 0.0f;
    if (rayStart.y < min.y) {
        yt = min.y - rayStart.y;
        if (yt > rayDir.y) {
            return kNoIntersection;
        }
        yt /= rayDir.y;
        inside = false;
        yn = -1.0f;
    } else if (rayStart.y > max.y) {
        yt = max.y - rayStart.y;
        if (yt < rayDir.y) {
            return kNoIntersection;
        }
        yt /= rayDir.y;
        inside = false;
        yn = 1.0f;
    } else {
        yt = -1.0f;
    }
    float zt, zn = 0.0f;
    if (rayStart.z < min.z) {
        zt = min.z - rayStart.z;
        if (zt > rayDir.z) {
            return kNoIntersection;
        }
        zt /= rayDir.z;
        inside = false;
        zn = -1.0f;
    } else if (rayStart.z > max.z) {
        zt = max.z - rayStart.z;
        if (zt < rayDir.z) {
            return kNoIntersection;
        }
        zt /= rayDir.z;
        inside = false;
        zn = 1.0f;
    } else {
        zt = -1.0f;
    }
    // 是否在矩形边界框内？
    if (inside) {
        /*if(returnNormal != NULL){  */
        // returnNormal = rayDir.multiK(-1);
        // returnNormal.normalize();
        returnNormal = CVector3(0, 0, 0) - rayDir;
        returnNormal.getNormalized();
        /*  }  */
        return 0.0f;  // 起点在矩形边界框内，确定相交时间最短？
    }
    // 选择最远的平面————发生相交的地方
    int32 which = 0;
    float t = xt;  // 选择最远的平面是什么意思？是指射线方向偏移物体包围盒边界最远么？（最远是指与包围盒某面中点相交？）
    if (yt > t) {
        which = 1;
        t = yt;
    }
    if (zt > t) {
        which = 2;
        t = zt;
    }
    switch (which) {
        case 0: {  // 和yz平面相交
                float y = rayStart.y + rayDir.y * t;  // 此时 t = xt，xt /= rayDir.x;此处又是什么意思？
                if (y < min.y || y > max.y) {
                    return kNoIntersection;
                }
                float z = rayStart.z + rayDir.z * t;
                if (z < min.z || z > max.z) {
                    return kNoIntersection;
                }
                // if(/*returnNormal != NULL*/){
                returnNormal.x = xn;
                returnNormal.y = 0.0f;
                returnNormal.z = 0.0f;
                /*} */
            }
            break;
        case 1: {  // 和xz平面相交
                float x = rayStart.x + rayDir.x * t;
                if (x < min.x || x > max.x) {
                    return kNoIntersection;
                }
                float z = rayStart.z + rayDir.z * t;
                if (z < min.z || z > max.z) {
                    return kNoIntersection;
                }
                /*  if(returnNormal != NULL){  */
                returnNormal.x = 0.0f;
                returnNormal.y = yn;
                returnNormal.z = 0.0f;
                /*  }      */
            }
            break;
        case 2: {  // 和xy平面相交
                float x = rayStart.x + rayDir.x * t;
                if (x < min.x || x > max.x) {
                    return kNoIntersection;
                }
                float y = rayStart.y + rayDir.y * t;
                if (y < min.y || y > max.y) {
                    return kNoIntersection;
                }
                /*if(returnNormal != NULL){*/
                returnNormal.x = 0.0f;
                returnNormal.y = 0.0f;
                returnNormal.z = zn;
                /*} */
            }
            break;
    }
    return t;  // 返回相交点参数值
}

void CMy3DSymbolLibNewView::JudgeRayIntersect(
    CVector3& rayStart,                  // 射线起点
    CVector3& rayDir,                    // 射线长度和方向
    CVector3& returnNormal               // 可选的，相交点处法向量
) {
    // 获取模型中三维点极值
    int32 minx, maxx, miny, maxy, minz, maxz;
    float t;
    // 如果是在选择模式下鼠标移动拾取对象，就只对已经拾取了的物体进行匹配
    if (m_bMouseMoveSelect) {
        for (uint32 i = 0; i < m_pSelectedModelSet.size(); ++i) {
            if (m_pSelectedModelSet.at(i)->modelType == MODEL_3DS) {
                int32 j = m_pSelectedModelSet.at(i)->modelID;
                // t = -1;
                t3DBox t3dBox;
                t3dBox.w = m_3DModel.GetAt(j)->scale * g_3DModel[j].t3DModelBox.w;
                t3dBox.h = m_3DModel.GetAt(j)->scale * g_3DModel[j].t3DModelBox.h;
                t3dBox.l = m_3DModel.GetAt(j)->scale * g_3DModel[j].t3DModelBox.l;
                POINT pt;
                pt.x = m_3DModel.GetAt(j)->posX;
                pt.y = m_3DModel.GetAt(j)->posZ;
                minx = pt.x - (t3dBox.l * 1.5) / 2;
                maxx = pt.x + (t3dBox.l * 1.5) / 2;
                minz = pt.y - (t3dBox.w * 1.5) / 2;
                maxz = pt.y + (t3dBox.w * 1.5) / 2;
                // int32 y = GetHeight(x,z) + h + t3dBox.h/2;             // 获取地面高度
                // 之所以高度最低是地面高度，是因为在渲染模型时已经将模型提高了最低高度到地表
                miny = GetHeight(pt.x, pt.y);
                maxy = GetHeight(pt.x, pt.y) + (t3dBox.h * 1.5);
                CVector3 returnNormal, min, max;
                min = CVector3(minx, miny, minz);
                max = CVector3(maxx, maxy, maxz);
                t = RayIntersect(rayStart, rayDir, returnNormal, min, max);
                if (t >= 0 && t <= 1) {
                    // 如果鼠标位置拾取了当前的选中模型，鼠标改变形态
                    m_mouseShape = MOUSE_SHAPE_EDIT;
                    m_selectedModelID = j;
                } else {
                    m_mouseShape = MOUSE_SHAPE_SLECT;
                }
            }
        }
    }
    if (m_bIsLBtnDown) {
        // 遍历所有的3D模型,判断是否在范围内
        for (int32 j = 0; j < m_i3DModelNum; j++) {
            // t = -1;
            t3DBox t3dBox;
            float scale = m_3DModel.GetAt(j)->scale;
            t3dBox.w = m_3DModel.GetAt(j)->scale * g_3DModel[j].t3DModelBox.w;
            t3dBox.h = m_3DModel.GetAt(j)->scale * g_3DModel[j].t3DModelBox.h;
            t3dBox.l = m_3DModel.GetAt(j)->scale * g_3DModel[j].t3DModelBox.l;
            POINT pt;
            pt.x = m_3DModel.GetAt(j)->posX;
            pt.y = m_3DModel.GetAt(j)->posZ;
            minx = pt.x - (t3dBox.l * 1.5) / 2;
            maxx = pt.x + (t3dBox.l * 1.5) / 2;
            minz = pt.y - (t3dBox.w * 1.5) / 2;
            maxz = pt.y + (t3dBox.w * 1.5) / 2;
            // int32 y = GetHeight(x,z) + h + t3dBox.h/2;             // 获取地面高度
            // 之所以高度最低是地面高度，是因为在渲染模型时已经将模型提高了最低高度到地表
            miny = GetHeight(pt.x, pt.y);
            maxy = GetHeight(pt.x, pt.y) + (t3dBox.h * 1.5);
            CVector3 returnNormal, min, max;
            min = CVector3(minx, miny, minz);
            max = CVector3(maxx, maxy, maxz);
            t = RayIntersect(rayStart, rayDir, returnNormal, min, max);
            if (t >= 0 && t <= 1) {
                CVector3 DotC = rayStart + CVector3(t * rayDir.x, t * rayDir.y, t * rayDir.z);
                CString strText;
                strText.Format("交点在  X=%.3f , Y=%.3f , Z=%.3f" , DotC.x, DotC.y, DotC.z);
                // 选中模型
                // AfxMessageBox(strText,MB_OK);
                // Set3dsModelParam(j);
                // 如果模型当前本身就是选中状态，那再次拾取到的时候就是从选中队列中删除出去
                if (m_OperateType == SELECT && m_3DModel.GetAt(j)->modelSelected) {
                    m_3DModel.GetAt(j)->modelSelected = false;
                    vector<PSelectedModel>::iterator ite;
                    for (vector<PSelectedModel>::iterator it = m_pSelectedModelSet.begin(); it != m_pSelectedModelSet.end(); ++it) {
                        /*
                        此处迭代器变量iterator可以简单的理解为vetor的指针，所以用*iterator对其进行解引用操作就返回了一个PSelectedModel类型
                        的对象*/
                        if ((*it)->modelID == (m_3DModel.GetAt(j)->modelID)/* && it != m_pSelectedModelSet.end()*/) {
                            ite = it;
                            // it = m_pSelectedModelSet.end();
                        }
                    }
                    m_pSelectedModelSet.erase(ite);
                } else {
                    if (m_3DModel.GetAt(j)->isDeleted == false) {
                        m_3DModel.GetAt(j)->modelSelected = true;
                        PSelectedModel selectedModel = new SelectedModel;
                        selectedModel->modelID = m_3DModel.GetAt(j)->modelID;
                        selectedModel->modelType = MODEL_3DS;
                        m_pSelectedModelSet.push_back(selectedModel);
                    }
                }
                if (!m_bFlash && !m_pSelectedModelSet.empty()) {
                    SetTimer(2, 500, NULL);
                    m_bFlash = true;
                }
            }
        }
    }
}



/****************************************************************************/
// Function: 加载工程文件
void CMy3DSymbolLibNewView::loadSceneFile(CString filename) {
    CStdioFile file;
    BOOL b_open = file.Open(filename, CStdioFile::modeRead);
    if ((!b_open) || (file == NULL)) {
        MessageBox(_T("工程不存在!\n") + filename, _T("打开工程文件"), MB_ICONWARNING + MB_OK);
        LOGGER_ERROR << "工程不存在!";
        return;
    } else {
        CString tmpStr = filename.Right(4);
        // 添加到注册表， 最近打开的文件列表
        if (tmpStr == _T(".prj"))
            theApp.AddToRecentFileList(filename);
        // 关闭当前场景
        OnCloseCurrentScene();
        // 读取所有数据文件路径
        m_AllDataPath = g_sceneDataPath.c_str();
        // 场景配置数据
        file.ReadString(m_SceneConfig);
        // ----------------------------------------------------
        // 地形数据, Terrain
        file.ReadString(pTerrainData_->m_TerrainFolder);
        // Tex Sand512.BMP
        file.ReadString(pTerrainData_->m_TerrainTextureFolder);
        int32 length = pTerrainData_->m_TerrainTextureFolder.GetLength();
        int32 i = pTerrainData_->m_TerrainTextureFolder.Find(" ");
        pTerrainData_->m_TerrainTexture = pTerrainData_->m_TerrainTextureFolder.Right(length - i - 1);
        pTerrainData_->m_TerrainTextureFolder = pTerrainData_->m_TerrainTextureFolder.Left(i);
        // Contour Terrain1.bmp
        file.ReadString(pTerrainData_->m_TerrainContourFolder);
        length = pTerrainData_->m_TerrainContourFolder.GetLength();
        i = pTerrainData_->m_TerrainContourFolder.Find(" ");
        pTerrainData_->m_TerrainContour = pTerrainData_->m_TerrainContourFolder.Right(length - i - 1);
        pTerrainData_->m_TerrainContourFolder = pTerrainData_->m_TerrainContourFolder.Left(i);
        // ----------------------------------------------------
        // 天空盒数据SkyBox
        file.ReadString(pSkyBox_->m_SkyBoxFolder);
        // default TOP.BMP LEFT.BMP BACK.BMP RIGHT.BMP FRONT.BMP
        file.ReadString(pSkyBox_->m_SkyBoxKindFolder);
        int32 curPos = 0;
        int32 tokenID = 0;
        CString temp = pSkyBox_->m_SkyBoxKindFolder.Tokenize(" ", curPos);
        CString Skyfolder = temp;
        while (temp != _T("")) {
            tokenID += 1;
            temp = pSkyBox_->m_SkyBoxKindFolder.Tokenize(" ", curPos);
            if (tokenID == 1)
                pSkyBox_->m_SkyBoxTP = temp;
            else if (tokenID == 2)
                pSkyBox_->m_SkyBoxLT = temp;
            else if (tokenID == 3)
                pSkyBox_->m_SkyBoxBK = temp;
            else if (tokenID == 4)
                pSkyBox_->m_SkyBoxRT = temp;
            else if (tokenID == 5)
                pSkyBox_->m_SkyBoxFR = temp;
        };
        pSkyBox_->m_SkyBoxKindFolder = Skyfolder;
        // ----------------------------------------------------
        // 天气数据
        file.ReadString(m_WeatherFolder);
        file.ReadString(m_WeatherTex);
        CString weatherSymbolTexPath = m_AllDataPath + "\\" + m_WeatherFolder + "\\" + m_WeatherTex;
        char cc[256];
        _snprintf_s(cc, sizeof(cc), sizeof(cc) - 1, weatherSymbolTexPath);
        LoadT8(cc, g_weatherTex);
        bIsWeatherLoad_ = true;
        // ----------------------------------------------------
        // 符号文件个数
        file.ReadString(m_CurrentSymbolTypeNum);
        file.ReadString(m_PointSymbolFile);
        file.ReadString(m_LineSymbolFile);
        file.ReadString(m_AreaSymbolFile);
        file.Close();
        // 加载点文件
        if (m_PointSymbolFile != "0") {
            CString point_Path = /*m_AllDataPath + "\\" + m_SceneConfig + "\\" + */m_PointSymbolFile;
            LoadPointSymbolFile(point_Path);
            exist_point_flag = TRUE;
        }
        // 加载区文件  必须等初始化地形数据之后  (见下方)
        /**************************************/
        /* 加载线路纹理资源                    */
        /**************************************/
        CString scenePath = g_sceneDataPath.c_str();
        CString tmpPath = scenePath + "\\RoadTexture";
        CString txtureRailway = tmpPath + "\\铁路\\doubleway5.bmp";
        // 加载铁路纹理
        m_cTxtureRailway.LoadGLTextures(txtureRailway.GetBuffer(0));
        CString txtureBP = tmpPath + "\\边坡防护\\拱形护坡1.bmp";
        m_cTxtureBP.LoadGLTextures(txtureBP.GetBuffer(0));
        CString txtureLJ = tmpPath + "\\路肩\\1.bmp";
        m_cTxtureLJ.LoadGLTextures(txtureLJ.GetBuffer(0));
        CString txtureGdToLJ = tmpPath + "\\路肩\\10.bmp";
        m_cTxtureGdToLJ.LoadGLTextures(txtureGdToLJ.GetBuffer(0));
        CString txturePT = tmpPath + "\\边坡平台\\边坡平台1.bmp";
        m_cTxturePT.LoadGLTextures(txturePT.GetBuffer(0));
        // 断面纹理
        CString txtureFF = tmpPath + "\\边坡平台\\边坡平台2.bmp";
        m_cFillFaceTxture.LoadGLTextures(txtureFF.GetBuffer(0));
        //==========================================================
        // ----------------------------------------------------
        // 开始场景渲染 配置天空盒
        CString skyBoxPathPre = m_AllDataPath + "\\" + pSkyBox_->m_SkyBoxFolder + "\\" + pSkyBox_->m_SkyBoxKindFolder + "\\";
        g_texSkyBoxFlieNameTP = skyBoxPathPre + pSkyBox_->m_SkyBoxTP;
        g_texSkyBoxFlieNameLF = skyBoxPathPre + pSkyBox_->m_SkyBoxLT;
        g_texSkyBoxFlieNameBK = skyBoxPathPre + pSkyBox_->m_SkyBoxBK;
        g_texSkyBoxFlieNameRT = skyBoxPathPre + pSkyBox_->m_SkyBoxRT;
        g_texSkyBoxFlieNameFR = skyBoxPathPre + pSkyBox_->m_SkyBoxFR;
        LoadSkyBoxTex(g_texSkyBoxFlieNameTP, g_texSkyBoxFlieNameLF, g_texSkyBoxFlieNameBK,
                      g_texSkyBoxFlieNameRT, g_texSkyBoxFlieNameFR);
        // 配置地形
        terrainTexFileName = m_AllDataPath + "\\" + pTerrainData_->m_TerrainFolder + "\\" + pTerrainData_->m_TerrainTextureFolder + "\\" + pTerrainData_->m_TerrainTexture;
        terrainContourFileName = m_AllDataPath + "\\" + pTerrainData_->m_TerrainFolder + "\\" + pTerrainData_->m_TerrainContourFolder + "\\" + pTerrainData_->m_TerrainContour;
        LoadTerrainTex(terrainTexFileName, terrainContourFileName);
        OnMenuBuild3dlinemodle();
        // 加载区文件
        if (m_AreaSymbolFile != "0") {
            CString area_Path = m_AreaSymbolFile;
            LoadAreaSymbolFile(area_Path);
            exist_area_flag = TRUE;
        }
        // 加载线文件
        if (m_LineSymbolFile != "0") {
            CString line_Path = /*m_AllDataPath + "\\" + m_SceneConfig + "\\" + */m_LineSymbolFile;
            LoadLineSymbolFile(line_Path);
            exist_line_flag = TRUE;
        }
    }
}


// 加载点文件(.pt)
void CMy3DSymbolLibNewView::LoadPointSymbolFile(CString filename) {
    CStdioFile file;
    BOOL b_open = file.Open(filename, CStdioFile::modeRead);
    if ((!b_open) || (file == NULL)) {
        MessageBox(_T("点文件!\n") + filename, _T("打开点文件"), MB_ICONWARNING + MB_OK);
        return;
    } else {
        // 读取所有数据文件路径
        m_AllDataPath = g_sceneDataPath.c_str();
        CString tmp_pointHeader;
        // 点文件首部
        file.ReadString(tmp_pointHeader);
        // ----------------------------------------------------
        // 3DS 模型数据
        /*3DModel
        2
        房子1 399.921 83.990 384.101
        航天发射台 397.700 83.991 373.560*/
        file.ReadString(pT3DModelData_->m_3DModelFolder);
        CString m_3DModelNumStr;
        file.ReadString(m_3DModelNumStr);
        m_i3DModelNum = atoi(m_3DModelNumStr);
        for (int32 i = 0; i < m_i3DModelNum; ++i) {
            file.ReadString(pT3DModelData_->m_3DModelPath);
            int32 curPos = 0;
            int32 tokenID = 0;
            CString temp = pT3DModelData_->m_3DModelPath.Tokenize(" ", curPos);
            CString model3DFolder = temp;
            while (temp != _T("")) {
                tokenID += 1;
                temp = pT3DModelData_->m_3DModelPath.Tokenize(" ", curPos);
                if (tokenID == 1)
                    pT3DModelData_->m_3DModelPosX = atof(temp);
                else if (tokenID == 2)
                    pT3DModelData_->m_3DModelPosY = atof(temp);
                else if (tokenID == 3)
                    pT3DModelData_->m_3DModelPosZ = atof(temp);
                else if (tokenID == 4)
                    pT3DModelData_->m_3DModelRotX = atof(temp);
                else if (tokenID == 5)
                    pT3DModelData_->m_3DModelRotY = atof(temp);
                else if (tokenID == 6)
                    pT3DModelData_->m_3DModelRotZ = atof(temp);
                else if (tokenID == 7)
                    pT3DModelData_->m_3DModelScale = atof(temp);
            };
            pT3DModelData_->m_3DModelPath = model3DFolder;
            PModelParamStruct p3d = new CModelParamStruct;
            p3d->modelPath = m_AllDataPath + "\\" + pT3DModelData_->m_3DModelFolder + "\\" + pT3DModelData_->m_3DModelPath;
            p3d->modelID = i;
            p3d->modelSelected = false;
            p3d->m_3DS_Mode_Texture_PATH_NAME = m_AllDataPath + "\\" + pT3DModelData_->m_3DModelFolder + "\\" + pT3DModelData_->m_3DModelPath.Left(pT3DModelData_->m_3DModelPath.Find('.')) + ".bmp";
            p3d->isDeleted = false;
            p3d->posX = pT3DModelData_->m_3DModelPosX;
            p3d->posY = pT3DModelData_->m_3DModelPosY;
            p3d->posZ = pT3DModelData_->m_3DModelPosZ;
            p3d->rotX = pT3DModelData_->m_3DModelRotX;
            p3d->rotY = pT3DModelData_->m_3DModelRotY;
            p3d->rotZ = pT3DModelData_->m_3DModelRotZ;
            p3d->scale = pT3DModelData_->m_3DModelScale;
            Load3DModel(p3d, MODEL_NEW);
        }
        // ----------------------------------------------------
        // 城市标识数据
        /*City Symbol
        2
        25 398.469 83.992 393.427
        1 386.085 83.993 387.031*/
        file.ReadString(pCitySymbolData_->m_CitySymbolFolder);
        CString m_CitySymbolNumStr;
        file.ReadString(m_CitySymbolNumStr);
        m_iCitySymbolModelNum = atoi(m_CitySymbolNumStr);
        for (int32 i = 0; i < m_iCitySymbolModelNum; ++i) {
            file.ReadString(pCitySymbolData_->m_CitySymbolTex);
            int32 curPos = 0;
            int32 tokenID = 0;
            curPos = 0;
            tokenID = 0;
            CString temp = pCitySymbolData_->m_CitySymbolTex.Tokenize(" ", curPos);
            CString citySymbolTex = temp;
            while (temp != _T("")) {
                tokenID += 1;
                temp = pCitySymbolData_->m_CitySymbolTex.Tokenize(" ", curPos);
                if (tokenID == 1)
                    pCitySymbolData_->m_CitySymbolPosX = atof(temp);
                else if (tokenID == 2)
                    pCitySymbolData_->m_CitySymbolPosY = atof(temp);
                else if (tokenID == 3)
                    pCitySymbolData_->m_CitySymbolPosZ = atof(temp);
            };
            pCitySymbolData_->m_CitySymbolTex = citySymbolTex;
            PModelStruct p3d = new CModelStruct;
            p3d->strModelPath = m_AllDataPath + "\\" + pCitySymbolData_->m_CitySymbolFolder + "\\" + pCitySymbolData_->m_CitySymbolTex;
            p3d->iModelNum = i;
            p3d->xPos = pCitySymbolData_->m_CitySymbolPosX;
            p3d->hPos = pCitySymbolData_->m_CitySymbolPosY;
            p3d->zPos = pCitySymbolData_->m_CitySymbolPosZ;
            p3d->radiu = 0;
            p3d->angle = 0;
            p3d->scale = 1;
            p3d->isSelected = false;
            p3d->iRotateX = 0;
            p3d->iRotateY = 0;
            p3d->iRotateZ = 0;
            m_CitySymbolModel.Add(p3d);
            char cc[256];
            // sprintf(cc, p3d->strModelPath);
            _snprintf_s(cc, sizeof(cc), sizeof(cc) - 1, p3d->strModelPath);
            LoadPNG(cc, g_citySymbolTex[i]);
        }
        // ----------------------------------------------------
        // 景观树数据
        /*TreeModel
        2
        CACTUS3 400.574 82.159 354.653
        CACTUS5 449.065 76.690 329.477
        1
        CACTUS5 665.527 56.000 315.917*/
        file.ReadString(pTreeModelData_->m_TreeModelFolder);
        CString m_TreeModelNumStr;
        file.ReadString(m_TreeModelNumStr);
        m_iTreeModelNum = atoi(m_TreeModelNumStr);
        for (int32 i = 0; i < m_iTreeModelNum; ++i) {
            file.ReadString(pTreeModelData_->m_TreeModelTex);
            int32 curPos = 0;
            int32 tokenID = 0;
            curPos = 0;
            tokenID = 0;
            CString temp = pTreeModelData_->m_TreeModelTex.Tokenize(" ", curPos);
            CString treeModelTex = temp;
            while (temp != _T("")) {
                tokenID += 1;
                temp = pTreeModelData_->m_TreeModelTex.Tokenize(" ", curPos);
                if (tokenID == 1)
                    pTreeModelData_->m_TreeModelPosX = atof(temp);
                else if (tokenID == 2)
                    pTreeModelData_->m_TreeModelPosY = atof(temp);
                else if (tokenID == 3)
                    pTreeModelData_->m_TreeModelPosZ = atof(temp);
            };
            pTreeModelData_->m_TreeModelTex = treeModelTex;
            PModelStruct p3d = new CModelStruct;
            p3d->strModelPath = m_AllDataPath + "\\" + pTreeModelData_->m_TreeModelFolder + "\\" + pTreeModelData_->m_TreeModelTex;
            p3d->iModelNum = i;
            p3d->xPos = pTreeModelData_->m_TreeModelPosX;
            p3d->hPos = pTreeModelData_->m_TreeModelPosY;
            p3d->zPos = pTreeModelData_->m_TreeModelPosZ;
            p3d->radiu = 0;
            p3d->angle = 0;
            p3d->scale = 1;
            p3d->isSelected = false;
            p3d->iRotateX = 0;
            p3d->iRotateY = 0;
            p3d->iRotateZ = 0;
            m_TreeModel.Add(p3d);
            char cc[256];
            // sprintf(cc, p3d->strModelPath);
            _snprintf_s(cc, sizeof(cc), sizeof(cc) - 1, p3d->strModelPath);
            LoadT16(cc, g_cactus[p3d->iModelNum]);
        }
        // ----------------------------------------------------
        // 3D Tree
        file.ReadString(m_TreeModelNumStr);
        m_i3DTreeModelNum = atoi(m_TreeModelNumStr);
        for (int32 i = 0; i < m_i3DTreeModelNum; ++i) {
            file.ReadString(pTreeModelData_->m_TreeModelTex);
            int32 curPos = 0;
            int32 tokenID = 0;
            curPos = 0;
            tokenID = 0;
            CString temp = pTreeModelData_->m_TreeModelTex.Tokenize(" ", curPos);
            CString treeModelTex = temp;
            while (temp != _T("")) {
                tokenID += 1;
                temp = pTreeModelData_->m_TreeModelTex.Tokenize(" ", curPos);
                if (tokenID == 1)
                    pTreeModelData_->m_TreeModelPosX = atof(temp);
                else if (tokenID == 2)
                    pTreeModelData_->m_TreeModelPosY = atof(temp);
                else if (tokenID == 3)
                    pTreeModelData_->m_TreeModelPosZ = atof(temp);
            };
            pTreeModelData_->m_TreeModelTex = treeModelTex;
            PModelStruct p3d = new CModelStruct;
            p3d->strModelPath = m_AllDataPath + "\\" + pTreeModelData_->m_TreeModelFolder + "\\" + pTreeModelData_->m_TreeModelTex;
            p3d->iModelNum = i;
            p3d->xPos = pTreeModelData_->m_TreeModelPosX;
            p3d->hPos = pTreeModelData_->m_TreeModelPosY;
            p3d->zPos = pTreeModelData_->m_TreeModelPosZ;
            p3d->radiu = 0;
            p3d->angle = 0;
            p3d->scale = 1;
            p3d->isSelected = false;
            p3d->iRotateX = 0;
            p3d->iRotateY = 0;
            p3d->iRotateZ = 0;
            m_3DTreeModel.Add(p3d);
            char cc[256];
            // sprintf(cc, p3d->strModelPath);
            _snprintf_s(cc, sizeof(cc), sizeof(cc) - 1, p3d->strModelPath);
            LoadT16(cc, g_cactus3DTree[p3d->iModelNum]);
        }
    }
    file.Close();
}
// 加载线文件(.ln)
void CMy3DSymbolLibNewView::LoadLineSymbolFile(CString filename) {
    CStdioFile file;
    BOOL b_open = file.Open(filename, CStdioFile::modeRead);
    if ((!b_open) || (file == NULL)) {
        MessageBox(_T("线文件!\n") + filename, _T("打开线文件"), MB_ICONWARNING + MB_OK);
        return;
    } else {
        // 读取所有数据
        CString tmp_lineHeader;
        // 线文件首部
        file.ReadString(tmp_lineHeader);
        // ----------------------------------------------------
        // 线符号的个数
        CString line_count_str;
        file.ReadString(line_count_str);
        int32 line_num = atoi(line_count_str);
        // 依次读取所有的线数据
        CString lineInfoStr = "";  // 线数据(线的类型 线段端点的个数 端点坐标 线段宽度 线段纹理)
        // 细分信息
        CString lineTypeStr = "";  // 线的类型
        CString linePointsCountStr = "";  // 线段端点的个数
        CString linePointsPosStr = "";  // 端点坐标
        CString lineWidthStr = "";  // 线段宽度
        CString lineTextureStr = "";  // 线段纹理
        for (int32 line_index = 0; line_index < line_num; ++line_index) {
            file.ReadString(lineInfoStr);
            LOGGER_INFO << "lineInfoStr = " << lineInfoStr;
            std::ostringstream lineInfoSS;
            lineInfoSS << (LPSTR)(LPCTSTR)lineInfoStr;
            std::string line_info = lineInfoSS.str();
            std::vector<std::string> lineInfoVector = StringUtils::split(StringUtils::split(line_info, '\n').at(0), ' ');
            // 线数据(线的类型 线段端点的个数 端点坐标 线段宽度 线段纹理)
            LineSymbol l_lineSymbol;
            // 线的类型
            l_lineSymbol.line_type_ = StringUtils::stringToFloat(lineInfoVector.at(0));
            // 线段端点的个数
            int32 line_points_num = StringUtils::stringToInt32(lineInfoVector.at(1));
            // 端点坐标
            for (int32 lp_index = 0; lp_index < line_points_num; ++lp_index) {
                Vec3 l_point(StringUtils::stringToFloat(lineInfoVector.at(2 + lp_index * 3)),
                             StringUtils::stringToFloat(lineInfoVector.at(3 + lp_index * 3)),
                             StringUtils::stringToFloat(lineInfoVector.at(4 + lp_index * 3)));
                l_lineSymbol.line_points_.push_back(l_point);
            }
            // 线段宽度
            l_lineSymbol.line_width_ = StringUtils::stringToFloat(lineInfoVector.at(2 + 3 * line_points_num));
            // 线段纹理
            l_lineSymbol.line_texture_ = lineInfoVector.at(3 + 3 * line_points_num);
            pL2DRoad_->SaveLineSymbol(&l_lineSymbol, g_terrain);
        }
        OnLine2dRoadFuse();
        file.Close();
    }
}
// 加载面文件(.gsf)
void CMy3DSymbolLibNewView::LoadAreaSymbolFile(CString filename) {
    CStdioFile file;
    BOOL b_open = file.Open(filename, CStdioFile::modeRead);
    if ((!b_open) || (file == NULL)) {
        MessageBox(_T("面文件!\n") + filename, _T("打开面文件"), MB_ICONWARNING + MB_OK);
        return;
    } else {
        // 读取所有数据文件路径
        // m_AllDataPath = g_sceneDataPath.c_str();
        CString tmp_areaHeader;
        // 面文件首部
        file.ReadString(tmp_areaHeader);
        // ----------------------------------------------------
        // 面符号的个数
        CString area_count_str;
        file.ReadString(area_count_str);
        int32 area_num = atoi(area_count_str);
        // 多边形的边数
        CString area_edge_num_str;
        CString area_info_str;
        for (int32 i = 0; i < area_num; ++i) {
            file.ReadString(area_info_str);
            int32 curPos = 0;
            int32 tokenID = 0;
            CString temp = area_info_str.Tokenize(" ", curPos);
            CString area_edge_num_str = temp;
            int32 area_edges = atoi(area_edge_num_str);
            Area_4 tmp_area4;
            while (temp != _T("") && (4 == area_edges)) {
                tokenID += 1;
                temp = area_info_str.Tokenize(" ", curPos);
                // pt1
                if (tokenID == 1)
                    tmp_area4.pt1.x = atof(temp);
                else if (tokenID == 2)
                    tmp_area4.pt1.y = atof(temp);
                else if (tokenID == 3)
                    tmp_area4.pt1.z = atof(temp);
                // pt2
                else if (tokenID == 4)
                    tmp_area4.pt2.x = atof(temp);
                else if (tokenID == 5)
                    tmp_area4.pt2.y = atof(temp);
                else if (tokenID == 6)
                    tmp_area4.pt2.z = atof(temp);
                // pt3
                else if (tokenID == 7)
                    tmp_area4.pt3.x = atof(temp);
                else if (tokenID == 8)
                    tmp_area4.pt3.y = atof(temp);
                else if (tokenID == 9)
                    tmp_area4.pt3.z = atof(temp);
                // pt4
                else if (tokenID == 10)
                    tmp_area4.pt4.x = atof(temp);
                else if (tokenID == 11)
                    tmp_area4.pt4.y = atof(temp);
                else if (tokenID == 12)
                    tmp_area4.pt4.z = atof(temp);
                else if (tokenID == 13)
                    tmp_area4.area_texture = temp;
            }
            PArea_4 area = new Area_4;
            area->pt1 = tmp_area4.pt1;
            area->pt2 = tmp_area4.pt2;
            area->pt3 = tmp_area4.pt3;
            area->pt4 = tmp_area4.pt4;
            area->area_texture = tmp_area4.area_texture;
            area->deleted = 0;
            m_Area4_Array.Add(area);
        }
        OnMenuAreaFuse();
    }
    file.Close();
}


/****************************************************************************/
// Function: 初始阶段导入场景文件
void CMy3DSymbolLibNewView::OnSceneLoad() {
    CString sceneConfigPath;
    CFileDialog FileDialog(TRUE, "打开工程", NULL, OFN_HIDEREADONLY \
                           | OFN_OVERWRITEPROMPT, \
                           "工程文件(*.prj)|*.prj|", NULL);
    // 默认打开配置中的文件路径
    FileDialog.m_ofn.lpstrInitialDir = g_sceneDataPath.c_str();
    FileDialog.m_ofn.lpstrTitle = "打开工程文件";
    if (FileDialog.DoModal() == IDOK) {
        sceneConfigPath = FileDialog.GetPathName();
    } else {
        return;
    }
    // 加载场景文件
    loadSceneFile(sceneConfigPath);
    m_CurrentProjectName = sceneConfigPath;
}


/****************************************************************************/
// Function: 导入天空盒纹理
void CMy3DSymbolLibNewView::LoadSkyBoxTex(CString skyTP, CString skyLF, CString skyBK, CString skyRT, CString skyFR) {
    char cc[256];
    // sprintf(cc, skyTP);
    _snprintf_s(cc, sizeof(cc), sizeof(cc) - 1, skyTP);
    LoadT8(cc, pSkyBox_->g_texSkyBox[TP]);
    // sprintf(cc, skyLF);
    _snprintf_s(cc, sizeof(cc), sizeof(cc) - 1, skyLF);
    LoadT8(cc, pSkyBox_->g_texSkyBox[LF]);
    // sprintf(cc, skyBK);
    _snprintf_s(cc, sizeof(cc), sizeof(cc) - 1, skyBK);
    LoadT8(cc, pSkyBox_->g_texSkyBox[BK]);
    // sprintf(cc, skyRT);
    _snprintf_s(cc, sizeof(cc), sizeof(cc) - 1, skyRT);
    LoadT8(cc, pSkyBox_->g_texSkyBox[RT]);
    // sprintf(cc, skyFR);
    _snprintf_s(cc, sizeof(cc), sizeof(cc) - 1, skyFR);
    LoadT8(cc, pSkyBox_->g_texSkyBox[FR]);
    MakeSkykList();
    pSkyBox_->iSkyBoxLoaded_ = true;
}


// Function: 导入地形纹理
void CMy3DSymbolLibNewView::LoadTerrainTex(CString terrainTex, CString terrainContour) {
    char cc[256];
    strcpy(cc, terrainTex);             // 地面贴图  // NOLINT
    LoadT8(cc,  texTerrain);
    strcpy(cc, terrainContour);         // 等高地势图  // NOLINT
    g_imageData = LoadBit(cc, &g_bit);  // 调等高线地势图
    InitTerrain(/*5*/);                 // 初始化地面，地面起伏高度为5，只有在随机地势高度设置才有用
    g_isTerrainInit = true;
    iTerrainType = 1;
}

// Function: 加载3DS模型
void CMy3DSymbolLibNewView::Load3DModel(PModelParamStruct p3d, int32 iLoadModelType) {
    if (iLoadModelType == MODEL_NEW) {
        m_3DModel.Add(p3d);
    }
    char _3DSFile[256];
    // sprintf(_3DSFile, p3d->modelPath);  // "...\\3DModel\\XXX.3DS"
    _snprintf_s(_3DSFile, sizeof(_3DSFile), sizeof(_3DSFile) - 1, p3d->modelPath);
    char _3DSTextureFile[256];
    // sprintf(_3DSTextureFile, p3d->m_3DS_Mode_Texture_PATH_NAME);
    _snprintf_s(_3DSTextureFile, sizeof(_3DSTextureFile), sizeof(_3DSTextureFile) - 1, p3d->m_3DS_Mode_Texture_PATH_NAME);
    p3ds_->Init(_3DSFile, p3d->modelID, _3DSTextureFile);   // 调用模型调入函数
    t3DBox t3dBox;
    t3dBox.l = g_3DModel[p3d->modelID].t3DModelBox.l * p3d->scale;
    t3dBox.w = g_3DModel[p3d->modelID].t3DModelBox.w * p3d->scale;
    t3dBox.h = g_3DModel[p3d->modelID].t3DModelBox.h * p3d->scale;
    // 解决load3dsmodel时缩放比例问题
    if (p3d->scale < 0.99) {
        return;
    }
    float maxtemp = MATH_MAX(t3dBox.l, t3dBox.w);
    float max = MATH_MAX(maxtemp, t3dBox.h);
    float scale = 0.0f;
    if (max > 10) {
        scale = 10 / max;
        m_3DModel.GetAt(p3d->modelID)->scale = scale;
    }
}

void CMy3DSymbolLibNewView::OnSceneSave() {
    if (ScenSave(m_CurrentProjectName))
        MessageBox("场景配置文件保存完毕", "保存场景配置方案", MB_ICONWARNING);
}

// Function: 当前场景另存为
void CMy3DSymbolLibNewView::OnSceneSaveAs() {
    // TODO(jason): 在此添加命令处理程序代码
    CString     NeededFile;
    char        FileFilter[] = "工程文件(*.prj)|*.prj|";
    // 设置文件对话框属性
    DWORD       FileDialogFlag = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
    CFileDialog FileDialogBoxFile(FALSE, NULL, 0, FileDialogFlag, FileFilter, this);
    FileDialogBoxFile.m_ofn.lpstrTitle = "保存工程文件";
    char        FileName[200];
    CString sceneDir = m_AllDataPath + "\\" + m_SceneConfig;
    FileDialogBoxFile.m_ofn.lpstrInitialDir = sceneDir;
    CString tt[3];
    if (FileDialogBoxFile.DoModal() == IDOK) {           // 如果对话框成果打开
        NeededFile = FileDialogBoxFile.GetPathName();   // 得到文件名
        // sprintf(FileName, "%s", NeededFile);
        _snprintf_s(FileName, sizeof(FileName), sizeof(FileName) - 1, "%s", NeededFile);
        if (strcmp(FileDialogBoxFile.GetFileExt(), "prj") != 0)
            strcat(FileName, ".prj");  // NOLINT
        if (ScenSave(FileName))
            MessageBox("场景配置文件保存完毕", "保存场景配置方案", MB_ICONWARNING);
    }
}


bool CMy3DSymbolLibNewView::ScenSave(CString scenePth) {
    CStdioFile file;
    BOOL openFlag = file.Open(scenePth, CStdioFile::modeCreate | CStdioFile::modeWrite);
    if (file == NULL || openFlag == FALSE) {
        MessageBox("无效的工程文件名!", "保存工程", MB_ICONINFORMATION + MB_OK);
        LOGGER_WARNING << "无效的工程文件名!";
        return FALSE;
    } else {
        /************************************************************************/
        /*   场景配置数据                                                           */
        /************************************************************************/
        file.WriteString(m_SceneConfig + "\n");
        /************************************************************************/
        /*   地形数据 Terrain                                                   */
        /************************************************************************/
        file.WriteString(pTerrainData_->m_TerrainFolder + "\n");
        //    Tex Sand512.BMP
        file.WriteString(pTerrainData_->m_TerrainTextureFolder + " " + pTerrainData_->m_TerrainTexture + "\n");
        //    Contour Terrain1.bmp
        file.WriteString(pTerrainData_->m_TerrainContourFolder + " " + pTerrainData_->m_TerrainContour + "\n");
        /************************************************************************/
        /*   天空盒数据 SkyBox                                                  */
        /************************************************************************/
        file.WriteString(pSkyBox_->m_SkyBoxFolder + "\n");
        //    0缺省 TOP.BMP LEFT.BMP BACK.BMP RIGHT.BMP FRONT.BMP
        file.WriteString(pSkyBox_->m_SkyBoxKindFolder + " " + pSkyBox_->m_SkyBoxTP + " " + pSkyBox_->m_SkyBoxLT + " "\
                         + pSkyBox_->m_SkyBoxBK + " " + pSkyBox_->m_SkyBoxRT + " " + pSkyBox_->m_SkyBoxFR + "\n");
        /************************************************************************/
        /*   天气数据                                                           */
        /************************************************************************/
        file.WriteString(m_WeatherFolder + "\n");
        file.WriteString(m_WeatherTex + "\n");
        // 写入点线面文件链接
        file.WriteString("3\n");
        file.WriteString(m_PointSymbolFile + "\n");
        file.WriteString(m_LineSymbolFile + "\n");
        file.WriteString(m_AreaSymbolFile);
        file.Close();
        // 保存点线面文件
        if (m_PointSymbolFile != "0")
            savePointSymbolFile(m_PointSymbolFile);
        if (m_LineSymbolFile != "0")
            saveLineSymbolFile(m_LineSymbolFile);
        if (m_AreaSymbolFile != "0")
            saveAreaSymbolFile(m_AreaSymbolFile);
        return TRUE;
    }
}

/****************************************************************************/
// Function: 保存点、线、面文件
// 保存点文件
int32 CMy3DSymbolLibNewView::savePointSymbolFile(CString filename) {
    CStdioFile file;
    file.Open(filename, CStdioFile::modeCreate | CStdioFile::modeWrite);
    if (file == NULL) {
        MessageBox("点文件不存在!", "保存点文件", MB_ICONINFORMATION + MB_OK);
        LOGGER_ERROR << "点文件不存在!";
        return FALSE;
    } else {
        file.WriteString("POINT\n");
        /************************************************************************/
        /*   3DS 模型数据 3DModel                                               */
        /************************************************************************/
        file.WriteString(pT3DModelData_->m_3DModelFolder + "\n");
        int32 count_model_existed = 0;
        for (int32 i = 0; i < m_i3DModelNum; ++i) {
            if (m_3DModel.GetAt(i)->isDeleted == false) {
                count_model_existed++;
            }
        }
        CString m_3DModelNumStr;
        m_3DModelNumStr.Format("%d", count_model_existed);
        file.WriteString(m_3DModelNumStr + "\n");
        for (int32 i = 0; i < m_i3DModelNum; ++i) {
            if (m_3DModel.GetAt(i)->isDeleted == false) {
                CString model;
                CString path = m_3DModel.GetAt(i)->modelPath;
                CString temp;
                int32 n = path.ReverseFind('\\');  // 从后往前寻找
                temp = path.Right(path.GetLength() - n - 1);
                float pos_x = m_3DModel.GetAt(i)->posX;
                float pos_z = m_3DModel.GetAt(i)->posZ;
                float pos_y = m_3DModel.GetAt(i)->posY;
                float rot_x = m_3DModel.GetAt(i)->rotX;
                float rot_z = m_3DModel.GetAt(i)->rotZ;
                float rot_y = m_3DModel.GetAt(i)->rotY;
                float model_scale = m_3DModel.GetAt(i)->scale;
                model.Format("%s %.3f %.3f %.3f %.3f %.3f %.3f %.13f", temp, pos_x, pos_y, pos_z, rot_x, rot_y, rot_z, model_scale);
                file.WriteString(model + "\n");
            }
        }
        /************************************************************************/
        /*   城市标识数据 City Symbol                                               */
        /************************************************************************/
        file.WriteString(pCitySymbolData_->m_CitySymbolFolder + "\n");
        CString m_CitySymbolNumStr;
        m_CitySymbolNumStr.Format("%d", m_iCitySymbolModelNum);
        file.WriteString(m_CitySymbolNumStr + "\n");
        for (int32 i = 0; i < m_iCitySymbolModelNum; ++i) {
            CString model;
            CString path = m_CitySymbolModel.GetAt(i)->strModelPath;
            CString temp;
            int32 n = path.ReverseFind('\\');  // 从后往前寻找
            temp = path.Right(path.GetLength() - n - 1);
            model.Format("%s %d %.3f %d", temp, \
                         m_CitySymbolModel.GetAt(i)->xPos, m_CitySymbolModel.GetAt(i)->hPos, m_CitySymbolModel.GetAt(i)->zPos);
            file.WriteString(model + "\n");
        }
        /************************************************************************/
        /*   景观树数据 TreeModel                                               */
        /************************************************************************/
        file.WriteString(pTreeModelData_->m_TreeModelFolder + "\n");
        CString m_TreeModelNumStr;
        m_TreeModelNumStr.Format("%d", m_iTreeModelNum);
        file.WriteString(m_TreeModelNumStr + "\n");
        for (int32 i = 0; i < m_iTreeModelNum; ++i) {
            CString model;
            CString path = m_TreeModel.GetAt(i)->strModelPath;
            CString temp;
            int32 n = path.ReverseFind('\\');  // 从后往前寻找
            temp = path.Right(path.GetLength() - n - 1);
            model.Format("%s %d %.3f %d", temp, \
                         m_TreeModel.GetAt(i)->xPos, m_TreeModel.GetAt(i)->hPos, m_TreeModel.GetAt(i)->zPos);
            file.WriteString(model + "\n");
        }
        /************************************************************************/
        /*   3D景观树 3D Tree                                                   */
        /************************************************************************/
        CString m_3DTreeModelNumStr;
        m_3DTreeModelNumStr.Format("%d", m_i3DTreeModelNum);
        file.WriteString(m_3DTreeModelNumStr + "\n");
        for (int32 i = 0; i < m_i3DTreeModelNum; ++i) {
            CString model;
            CString path = m_3DTreeModel.GetAt(i)->strModelPath;
            CString temp;
            int32 n = path.ReverseFind('\\');  // 从后往前寻找
            temp = path.Right(path.GetLength() - n - 1);
            model.Format("%s %d %.3f %d", temp, \
                         m_3DTreeModel.GetAt(i)->xPos, m_3DTreeModel.GetAt(i)->hPos, m_3DTreeModel.GetAt(i)->zPos);
            file.WriteString(model + "\n");
        }
        file.Close();
    }
    return 0;
}
// 保存线文件
int32 CMy3DSymbolLibNewView::saveLineSymbolFile(CString filename) {
    CStdioFile file;
    file.Open(filename, CStdioFile::modeCreate | CStdioFile::modeWrite);
    if (NULL == file) {
        MessageBox("线文件不存在！", "保存线文件", MB_ICONINFORMATION + MB_OK);
        LOGGER_ERROR << "线文件不存在！";
        return FALSE;
    } else {
        file.WriteString("LINE\n");
        int32 lineSize = pL2DRoad_->allLineSymbols_.size();
        int32 lineSize_Save = pL2DRoad_->allLineSymbols_.size();
        // 已经删除掉的不做保存
        for (int32 i = 0; i < lineSize; ++i) {
            if (pL2DRoad_->allLineSymbols_.at(i).deleted_) {
                --lineSize_Save;
            }
        }
        // save line 的个数
        CString lineCountStr;
        lineCountStr.Format("%d\n", lineSize_Save);
        file.WriteString(lineCountStr);
        // save all Lines one by one
        for (int line_index = 0; line_index < lineSize; ++line_index) {
            auto tt = pL2DRoad_->allLineSymbols_.at(line_index).deleted_;
            if (pL2DRoad_->allLineSymbols_.at(line_index).deleted_) {
                continue;
            }
            // 线段上点的个数
            int32 line_points_count = pL2DRoad_->allLineSymbols_.at(line_index).line_points_.size();
            // 线的类型 线段端点的个数 端点坐标 线段宽度 线段纹理
            std::ostringstream lineFormatInfoStr;
            lineFormatInfoStr << pL2DRoad_->allLineSymbols_.at(line_index).line_type_ << " "
                              << line_points_count << " ";
            for (int32 p_index = 0; p_index < line_points_count; ++p_index) {
                lineFormatInfoStr << pL2DRoad_->allLineSymbols_.at(line_index).line_points_.at(p_index).x << " "
                                  << pL2DRoad_->allLineSymbols_.at(line_index).line_points_.at(p_index).y << " "
                                  << pL2DRoad_->allLineSymbols_.at(line_index).line_points_.at(p_index).z << " ";
            }
            lineFormatInfoStr << pL2DRoad_->allLineSymbols_.at(line_index).line_width_ << " "
                              << pL2DRoad_->allLineSymbols_.at(line_index).line_texture_ << "\n";
            // auto ss = lineFormatInfoStr.str();
            // LOGGER_INFO << "[" << lineFormatInfoStr.str() << "]";
            CString lineFormatInfoStr2;
            lineFormatInfoStr2.Format("%s", lineFormatInfoStr.str().c_str());
            file.WriteString(lineFormatInfoStr2);
        }
        file.Close();
    }
    return 0;
}
// 保存区文件
int32 CMy3DSymbolLibNewView::saveAreaSymbolFile(CString filename) {
    CStdioFile file;
    file.Open(filename, CStdioFile::modeCreate | CStdioFile::modeWrite);
    if (file == NULL) {
        MessageBox("面文件不存在!", "保存面文件", MB_ICONINFORMATION + MB_OK);
        LOGGER_ERROR << "面文件不存在!";
        return FALSE;
    } else {
        file.WriteString("AREA\n");
        int32 size = m_Area4_Array.GetSize();
        for (int32 i = 0; i < size; ++i) {
            if (m_Area4_Array[i]->deleted == 1) {
                size--;
            }
        }
        CString polygon_count_str;
        polygon_count_str.Format("%d\n", size);
        file.WriteString(polygon_count_str);
        int32 polygon4_edges = 4;
        for (int32 i = 0; i < m_Area4_Array.GetSize(); ++i) {
            if (m_Area4_Array[i]->deleted != 1) {
                CString point_str;
                point_str.Format("%d %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %s\n",
                                 polygon4_edges,
                                 m_Area4_Array[i]->pt1.x, m_Area4_Array[i]->pt1.y, m_Area4_Array[i]->pt1.z,
                                 m_Area4_Array[i]->pt2.x, m_Area4_Array[i]->pt2.y, m_Area4_Array[i]->pt2.z,
                                 m_Area4_Array[i]->pt3.x, m_Area4_Array[i]->pt3.y, m_Area4_Array[i]->pt3.z,
                                 m_Area4_Array[i]->pt4.x, m_Area4_Array[i]->pt4.y, m_Area4_Array[i]->pt4.z,
                                 m_Area4_Array[i]->area_texture
                                );
                file.WriteString(point_str);
            }
        }
        file.Close();
    }
    return 0;
}


// Function: 选中模型之后右键弹出菜单中进行鼠标移动模型操作
void CMy3DSymbolLibNewView::OnModelMove() {
    m_OperateType = MOVE;
}


// Function: 编辑模型参数,例如模型纹理路径,大小,方向,缩放比例
void CMy3DSymbolLibNewView::OnModelParam() {
    ModelParam dlg;
    dlg.modelFolder = m_AllDataPath + "\\" + pT3DModelData_->m_3DModelFolder + "\\";
    PModelParamStructToModelParamDlg(dlg, m_3DModel.GetAt(m_selectedModelID));
    if (dlg.DoModal()) {
        ModelParamDlgToPModelParamStruct(dlg, m_3DModel.GetAt(m_selectedModelID));
    }
}



// Function: 参数设置对话框内变量直接全部赋值给结构体
void CMy3DSymbolLibNewView::ModelParamDlgToPModelParamStruct(const ModelParam& model, PModelParamStruct pStruct) {
    pStruct->posX = model.posX;
    pStruct->posY = model.posY;
    pStruct->posZ = model.posZ;
    pStruct->rotX = model.rotX;
    pStruct->rotY = model.rotY;
    pStruct->rotZ = model.rotZ;
    pStruct->scale = model.scale;
    // 更新3DS模型
    if ((model.modelChanged || model.isModelTextureUpdated)) {  // && (pStruct->modelPath.Compare(model.modelPath) != 0))
        pStruct->modelPath = model.modelPath;
        pStruct->m_3DS_Mode_Texture_PATH_NAME = model.m_TexturePathAndName;
        Load3DModel(pStruct, MODEL_CHANGE);
    }
}



// Function: 参数传给对话框
void CMy3DSymbolLibNewView::PModelParamStructToModelParamDlg(ModelParam& model, PModelParamStruct pStruct) {  // NOLINT
    model.posX = pStruct->posX;
    model.posY = pStruct->posY;
    model.posZ = pStruct->posZ;
    model.rotX = pStruct->rotX;
    model.rotY = pStruct->rotY;
    model.rotZ = pStruct->rotZ;
    model.scale = pStruct->scale;
    CString path = pStruct->modelPath;
    int32 index = path.ReverseFind('\\');
    int32 index1 = path.ReverseFind('.');
    CString path1 = pStruct->modelPath.Mid(index + 1, index1 - index - 1);
    model.displayPath = path1;
    model.modelPath = pStruct->modelPath;
    CString texturePath = pStruct->m_3DS_Mode_Texture_PATH_NAME;
    index = texturePath.ReverseFind('\\');
    index1 = texturePath.ReverseFind('.');
    CString texture_format = ".bmp";
    model.m_TextureName = pStruct->m_3DS_Mode_Texture_PATH_NAME.Mid(index + 1, index1 - index - 1) + texture_format;
}



// Function: 缩放选中模型
void CMy3DSymbolLibNewView::OnModelScale() {
    m_OperateType = SCALE;
}

// Function: 配置符号列表
void CMy3DSymbolLibNewView::OnConfigureSymbolList() {
    // TODO(jason): 在此添加命令处理程序代码
    ModelListConfigureDialog mlcDlg;
    if (mlcDlg.DoModal() == IDOK) {
        // null
    }
}

// Function: 系统设置
void CMy3DSymbolLibNewView::OnSystemSetting() {
    // TODO(jason): 在此添加命令处理程序代码
    CSystemSetting sysSetDlg;
    if (sysSetDlg.DoModal() == IDOK) {
        // null
    }
}

// Function: 关闭当前场景
void CMy3DSymbolLibNewView::OnCloseCurrentScene() {
    // TODO(jason): 在此添加命令处理程序代码
    InitData();
    // 清空场景中的景观树
    m_TreeModel.RemoveAll();
    // 清空场景中的3D景观树
    m_3DTreeModel.RemoveAll();
    // 清空场景中的城市符号
    m_CitySymbolModel.RemoveAll();
    // 清空场景中的3DS模型
    m_3DModel.RemoveAll();
    // 清除所有线路数据
    clearLinesData();
    // 清空所有的面符号
    m_Area4_Array.RemoveAll();
    // 清除漫游数据
    OnFlyStop();
    if (m_ShowFlyPath == TRUE)
        m_ShowFlyPath = FALSE;
    m_FlayPath.RemoveAll();
}


/**************************************/
// Function: 清除所有线路数据
void CMy3DSymbolLibNewView::clearLinesData() {
    // 交点
    pDesingScheme_->PtS_JD.RemoveAll();
    // 铁路中线
    pDesingScheme_->PtS_3DLineZX.RemoveAll();
    // 路肩
    pDesingScheme_->PtS_RailwayLj3D.RemoveAll();
    // 轨道
    pDesingScheme_->PtS_Railway3D.RemoveAll();
    // 线路设计交点
    pDesingScheme_->JDCurveElements.RemoveAll();
    pDesingScheme_->PtS_RailwayLjToBP3D.RemoveAll();
    pDesingScheme_->PtS_RailwayBP3D.RemoveAll();
    pDesingScheme_->PtS_HuPo.RemoveAll();
    pDesingScheme_->PtSHuPoTemp.RemoveAll();
}



// Function: 选中模型后,右击菜单,删除模型
void CMy3DSymbolLibNewView::OnModelDelete() {
    m_3DModel.GetAt(m_selectedModelID)->isDeleted = true;
    m_3DModel.GetAt(m_selectedModelID)->modelSelected = false;
    vector<PSelectedModel>::iterator ite;
    for (vector<PSelectedModel>::iterator it = m_pSelectedModelSet.begin(); it != m_pSelectedModelSet.end(); ++it) {
        if ((*it)->modelID == (m_3DModel.GetAt(m_selectedModelID)->modelID)) {
            ite = it;
            m_pSelectedModelSet.erase(ite);
            break;
        }
    }
}


/************************************************************************/
/*                        线路设计                                       */
/************************************************************************/

// Function: 线路三维建模
void CMy3DSymbolLibNewView::OnMenuBuild3dlinemodle() {
    // TODO(jason): 在此添加命令处理程序代码
    // 鼠标光标 系统忙
    BeginWaitCursor();
    pDesingScheme_->CalculateCurveData();
    pDesingScheme_->PtS_Railway3D.RemoveAll();
    pDesingScheme_->PtS_RailwayLj3D.RemoveAll();
    pDesingScheme_->PtS_RailwayLjToBP3D.RemoveAll();
    pDesingScheme_->PtS_RailwayBP3D.RemoveAll();
    pDesingScheme_->PtS_HuPo.RemoveAll();
    if (pDesingScheme_->PtS_3DLineZX.GetSize() < 2)
        return;
    CMainFrame* pMainFrame = reinterpret_cast<CMainFrame*>(AfxGetApp()->m_pMainWnd);
    double EndLC = 10000.0;
    for (int64 i = 0; i < pDesingScheme_->PtS_3DLineZX.GetSize() - 1; ++i) {
        if (pDesingScheme_->PtS_3DLineZX.GetAt(i + 1)->Lc <= EndLC) {
            pDesingScheme_->Get3DLineModel(pDesingScheme_->PtS_3DLineZX.GetAt(i)->x, \
                                           pDesingScheme_->PtS_3DLineZX.GetAt(i)->y, \
                                           pDesingScheme_->PtS_3DLineZX.GetAt(i)->z, \
                                           pDesingScheme_->PtS_3DLineZX.GetAt(i + 1)->x, \
                                           pDesingScheme_->PtS_3DLineZX.GetAt(i + 1)->y, \
                                           pDesingScheme_->PtS_3DLineZX.GetAt(i + 1)->z, \
                                           pL3DRoad_->pRailWay_->m_Railway_width, pL3DRoad_->pRailWay_->m_Lj_width, pL3DRoad_->pRailWay_->m_Lj_Dh, \
                                           pL3DRoad_->pRailWay_->m_GuiMianToLujianWidth, 45, \
                                           pDesingScheme_->PtS_3DLineZX.GetAt(i)->strJDStyle, \
                                           pDesingScheme_->PtS_3DLineZX.GetAt(i + 1)->strJDStyle, \
                                           i, \
                                           pDesingScheme_->PtS_3DLineZX.GetAt(i)->Lc
                                          );
        }
    }
    if (pDesingScheme_->PtS_3DLineZX.GetAt(pDesingScheme_->PtS_3DLineZX.GetSize() - 1)->Lc <= EndLC) {  // pDesingScheme_->SchemeDatass.EndLC)
        pDesingScheme_->Get3DLineModelLast(pDesingScheme_->PtS_3DLineZX.GetAt(pDesingScheme_->PtS_3DLineZX.GetSize() - 2)->x, \
                                           pDesingScheme_->PtS_3DLineZX.GetAt(pDesingScheme_->PtS_3DLineZX.GetSize() - 2)->y, \
                                           pDesingScheme_->PtS_3DLineZX.GetAt(pDesingScheme_->PtS_3DLineZX.GetSize() - 2)->z, \
                                           pDesingScheme_->PtS_3DLineZX.GetAt(pDesingScheme_->PtS_3DLineZX.GetSize() - 1)->x, \
                                           pDesingScheme_->PtS_3DLineZX.GetAt(pDesingScheme_->PtS_3DLineZX.GetSize() - 1)->y, \
                                           pDesingScheme_->PtS_3DLineZX.GetAt(pDesingScheme_->PtS_3DLineZX.GetSize() - 1)->z, \
                                           pL3DRoad_->pRailWay_->m_Railway_width, pL3DRoad_->pRailWay_->m_Lj_width, pL3DRoad_->pRailWay_->m_Lj_Dh, \
                                           pL3DRoad_->pRailWay_->m_GuiMianToLujianWidth, 45, \
                                           pDesingScheme_->PtS_3DLineZX.GetAt(pDesingScheme_->PtS_3DLineZX.GetSize() - 2)->strJDStyle, \
                                           pDesingScheme_->PtS_3DLineZX.GetAt(pDesingScheme_->PtS_3DLineZX.GetSize() - 1)->strJDStyle, \
                                           pDesingScheme_->PtS_3DLineZX.GetSize() - 2, \
                                           pDesingScheme_->PtS_3DLineZX.GetAt(pDesingScheme_->PtS_3DLineZX.GetSize() - 2)->Lc\
                                          );
    }
    pL3DRoad_->b_haveMadeRail3DwayList = FALSE;
    OnDraw(GetDC());  // 刷新三维场景
}

// Function: 三维选线设计
void CMy3DSymbolLibNewView::OnMenuLinedesign() {
    // TODO(jason): 在此添加命令处理程序代码
    if (spaceSearchInfo_.m_QueryType == SELECTLINE)  // 如果当前已经三维选线状态，则关闭
        spaceSearchInfo_.m_QueryType = -1;
    else                            // 如果当前不是三维选线状态，则打开
        spaceSearchInfo_.m_QueryType = SELECTLINE;
}

// Function: 设置三维选线设计选中状态
void CMy3DSymbolLibNewView::OnUpdateMenuLinedesign(CCmdUI* pCmdUI) {
    // TODO(jason): 在此添加命令更新用户界面处理程序代码
    pCmdUI->SetCheck(spaceSearchInfo_.m_QueryType == SELECTLINE);
}

// Function: 实现透视投影模式下的线路三维模型绘制
void CMy3DSymbolLibNewView::DrawRailwaythesme() {
    // 压入属性堆栈
    glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT | GL_POLYGON_BIT);
    glEnable(GL_DEPTH_TEST | GL_CULL_FACE);
    glCullFace(GL_BACK);
    SetDrawMode();                          // 设置绘图模式
    glViewport(0, 0, WinViewX, WinViewY);   // 重新设置视口大小
    //=======================================================
    pL3DRoad_->DrawRailwaythesme(pDesingScheme_,
                                 &m_cFillFaceTxture,
                                 m_Rail3DwayList,
                                 &m_cTxtureBP,
                                 &m_cTxturePT,
                                 &m_cTxtureRailway,
                                 &m_cTxtureGdToLJ,
                                 &m_cTxtureLJ);
}

// 清除所有线路
void CMy3DSymbolLibNewView::OnMenuClearLines() {
    // TODO(jason): 在此添加命令处理程序代码
    clearLinesData();
    initLines();
}

// 新建工程
void CMy3DSymbolLibNewView::OnSceneNew() {
    // TODO(jason): 在此添加命令处理程序代码
    // step 1 : 设置工程文件名, 创建该文件
    CString     NeededFile;
    char        FileFilter[] = "工程文件(*.prj)|*.prj|";
    // 设置文件对话框属性
    DWORD       FileDialogFlag = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
    CFileDialog FileDialogBoxFile(FALSE, NULL, 0, FileDialogFlag, FileFilter, this);
    FileDialogBoxFile.m_ofn.lpstrTitle = "新建工程";
    char        FileName[200];
    CString sceneDir = m_AllDataPath + "\\" + m_SceneConfig;
    FileDialogBoxFile.m_ofn.lpstrInitialDir = sceneDir;
    CString tt[3];
    if (FileDialogBoxFile.DoModal() == IDOK) {           // 如果对话框成果打开
        NeededFile = FileDialogBoxFile.GetPathName();   // 得到文件名
        // sprintf(FileName, "%s", NeededFile);
        _snprintf_s(FileName, sizeof(FileName), sizeof(FileName) - 1, "%s", NeededFile);
        if (strcmp(FileDialogBoxFile.GetFileExt(), "prj") != 0)
            strcat(FileName, ".prj");  // NOLINT
        {
            CStdioFile file;
            file.Open(FileName, CStdioFile::modeCreate | CStdioFile::modeWrite);
            if (file == NULL) {
                MessageBox("ERROR!", "ERROR", MB_ICONINFORMATION + MB_OK);
                LOGGER_ERROR << "ERROR!";
                return;
            } else {
                CString tmpSceneConfig = "SceneConfig";
                CString tmpTerrainFolder = "Terrain";
                CString tmpTerrainTextureFolder = "Tex";
                CString tmpTerrainTexture = "Sand512.BMP";
                CString tmpTerrainContourFolder = "Contour";
                CString tmpTerrainContour = "Terrain1.bmp";
                CString tmpSkyBoxFolder = "SkyBox";
                CString tmpSkyBoxKindFolder = "default";
                CString tmpSkyBoxTP = "TOP.BMP";
                CString tmpSkyBoxLT = "LEFT.BMP";
                CString tmpSkyBoxBK = "BACK.BMP";
                CString tmpSkyBoxRT = "RIGHT.BMP";
                CString tmpSkyBoxFR = "FRONT.BMP";
                CString tmpWeatherFolder = "Weather";
                CString tmpWeatherTex = "a0.bmp";
                /************************************************************************/
                /*   场景配置数据                                                           */
                /************************************************************************/
                file.WriteString(tmpSceneConfig + "\n");
                /************************************************************************/
                /*   地形数据 Terrain                                                   */
                /************************************************************************/
                file.WriteString(tmpTerrainFolder + "\n");
                //    Tex Sand512.BMP
                file.WriteString(tmpTerrainTextureFolder + " " + tmpTerrainTexture + "\n");
                //    Contour Terrain1.bmp
                file.WriteString(tmpTerrainContourFolder + " " + tmpTerrainContour + "\n");
                /************************************************************************/
                /*   天空盒数据 SkyBox                                                  */
                /************************************************************************/
                file.WriteString(tmpSkyBoxFolder + "\n");
                //    0缺省 TOP.BMP LEFT.BMP BACK.BMP RIGHT.BMP FRONT.BMP
                file.WriteString(tmpSkyBoxKindFolder + " " + tmpSkyBoxTP + " " + tmpSkyBoxLT + " "\
                                 + tmpSkyBoxBK + " " + tmpSkyBoxRT + " " + tmpSkyBoxFR + "\n");
                /************************************************************************/
                /*   天气数据                                                           */
                /************************************************************************/
                file.WriteString(tmpWeatherFolder + "\n");
                file.WriteString(tmpWeatherTex + "\n");
                // 点线面符号文件链接
                file.WriteString("3\n");    // 个数
                file.WriteString("0\n");    // point  (0表示暂无该文件)
                file.WriteString("0\n");    // line
                file.WriteString("0");      // area
                file.Close();
            }
        }
    } else {
        return;
    }
    // step 2 : 通过新建的工程文件加载该工程到视图窗口中
    loadSceneFile(FileName);
    m_CurrentProjectName = FileName;
    OnDraw(GetDC());  // 刷新三维场景
}

// 判断当前工程中是否存在已经打开的点、线、面文件
BOOL CMy3DSymbolLibNewView::exist_point_file() {
    return exist_point_flag;
}
BOOL CMy3DSymbolLibNewView::exist_line_file() {
    return exist_line_flag;
}
BOOL CMy3DSymbolLibNewView::exist_area_file() {
    return exist_area_flag;
}

// 成功返回0 ,否则返回-1; type:0-点, 1-线, 2-面, _fileName:创建的文件名通过函数参数传出来
int32 CMy3DSymbolLibNewView::new_symbol_file(uint32 type, char* _fileName) {
    CString     NeededFile;
    char FileFilter[32] = {0};
    char* tmpAgrs[3][5] = { {"点文件(*.pt)|*.pt|",  "新建点文件",   "pt",   ".pt",  "POINT\n"   },
        {"线文件(*.ln)|*.ln|",  "新建线文件",   "ln",   ".ln",  "LINE\n"    },
        {"面文件(*.gsf)|*.gsf|",    "新建面文件",   "gsf",  ".gsf", "AREA\n"    }
    };
    strcpy_s(FileFilter, tmpAgrs[type][0]);
    // 设置文件对话框属性
    DWORD       FileDialogFlag = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
    CFileDialog FileDialogBoxFile(FALSE, NULL, 0, FileDialogFlag, FileFilter, this);
    LPCSTR tmpLpcstrTitle = "新建点文件";
    tmpLpcstrTitle = tmpAgrs[type][1];
    FileDialogBoxFile.m_ofn.lpstrTitle = tmpLpcstrTitle;
    char        FileName[200];
    CString sceneDir = m_AllDataPath + "\\" + m_SceneConfig;
    FileDialogBoxFile.m_ofn.lpstrInitialDir = sceneDir;
    CString tt[3];
    if (FileDialogBoxFile.DoModal() == IDOK) {           // 如果对话框成果打开
        NeededFile = FileDialogBoxFile.GetPathName();   // 得到文件名
        // sprintf(FileName, "%s", NeededFile);
        _snprintf_s(FileName, sizeof(FileName), sizeof(FileName) - 1, "%s", NeededFile);
        if (strcmp(FileDialogBoxFile.GetFileExt(), tmpAgrs[type][2]) != 0)
            strcat(FileName, tmpAgrs[type][3]);  // NOLINT
        {
            CStdioFile file;
            file.Open(FileName, CStdioFile::modeCreate | CStdioFile::modeWrite);
            if (file == NULL) {
                MessageBox("ERROR!", "ERROR", MB_ICONINFORMATION + MB_OK);
                return -1;
            } else {
                strcpy(_fileName, FileName);  // NOLINT
                // file.WriteString( tmpAgrs[type][4] );
                file.Close();
            }
        }
        return 0;
    }
    return -1;
}

// 新建符号文件, 0-点, 1-线, 2-面
int32 CMy3DSymbolLibNewView::new_point_file() {
    int32 newFileFlag = 0;
    char tmpPointFileName[200] = {0};
    newFileFlag = new_symbol_file(0, tmpPointFileName);
    m_PointSymbolFile = tmpPointFileName;
    return newFileFlag;
}
int32 CMy3DSymbolLibNewView::new_line_file() {
    int32 newFileFlag = 0;
    char tmpLineFileName[200] = {0};
    newFileFlag = new_symbol_file(1, tmpLineFileName);
    m_LineSymbolFile = tmpLineFileName;
    return newFileFlag;
}
int32 CMy3DSymbolLibNewView::new_area_file() {
    int32 newFileFlag = 0;
    char tmpAreaFileName[200] = {0};
    newFileFlag = new_symbol_file(2, tmpAreaFileName);
    m_AreaSymbolFile = tmpAreaFileName;
    return newFileFlag;
}




/************************************************************************/
/*                              面符号                                  */
/************************************************************************/

// 添加面符号
void CMy3DSymbolLibNewView::OnMenuAddAreaSlib() {
    // TODO(jason): 在此添加命令处理程序代码
    int32 newFlag = 0;
    if (!exist_area_file()) {
        INT_PTR nRes;
        nRes = MessageBox("没有打开的面文件，需要新建文件吗？", "找不到面文件", MB_YESNO | MB_ICONQUESTION);
        if (nRes == IDYES) {
            newFlag = new_area_file();
            if (0 == newFlag) {
                exist_area_flag = TRUE;
            }
        }
    } else {
        if (spaceSearchInfo_.m_QueryType == AREA_ADD)
            spaceSearchInfo_.m_QueryType = -1;
        else
            spaceSearchInfo_.m_QueryType = AREA_ADD;
    }
}

// 更新添加面符号勾选状态
void CMy3DSymbolLibNewView::OnUpdateMenuAddAreaSlib(CCmdUI* pCmdUI) {
    // TODO(jason): 在此添加命令更新用户界面处理程序代码
    pCmdUI->SetCheck(spaceSearchInfo_.m_QueryType == AREA_ADD);
}

// 多边形矢量与DEM融合
void CMy3DSymbolLibNewView::OnMenuAreaFuse() {
    // TODO(jason): 在此添加命令处理程序代码
    int32 tmp_rowNum = 0;
    int32 tmp_row_index_begin = 0;
    int32 tmp_row_index_end = 0;
    int32 tmp_colNum = 0;
    int32 tmp_col_index_begin = 0;
    int32 tmp_col_index_end = 0;
    Area_4 tmp_area4;
    if (m_Area4_Array.GetSize() <= 0) {
        return;
    }
    // =========================================================================================
    uint32 tmp_size = m_Area4_Array.GetSize();
    for (uint32 i = 0; i < tmp_size; ++i) {
        Area_4 tmp_area4;
        tmp_area4.pt1 = m_Area4_Array[i]->pt1;
        tmp_area4.pt2 = m_Area4_Array[i]->pt2;
        tmp_area4.pt3 = m_Area4_Array[i]->pt3;
        tmp_area4.pt4 = m_Area4_Array[i]->pt4;
        pArea4Symbol_->FindAllTrianglesInPolygon(tmp_area4, g_terrain);
        m_Area4_Array[i]->pt1 = tmp_area4.pt1;
        m_Area4_Array[i]->pt2 = tmp_area4.pt2;
        m_Area4_Array[i]->pt3 = tmp_area4.pt3;
        m_Area4_Array[i]->pt4 = tmp_area4.pt4;
        m_Area4_Array[i]->LocalTrianglesVecotr1 = tmp_area4.LocalTrianglesVecotr1;
        m_Area4_Array[i]->LocalTrianglesVecotr1_1 = tmp_area4.LocalTrianglesVecotr1_1;
        m_Area4_Array[i]->LocalTrianglesVecotr2 = tmp_area4.LocalTrianglesVecotr2;
        m_Area4_Array[i]->LocalTrianglesVecotr2_1 = tmp_area4.LocalTrianglesVecotr2_1;
        m_Area4_Array[i]->LocalTrianglesVecotr_last = tmp_area4.LocalTrianglesVecotr_last;
        m_Area4_Array[i]->TrianglesInPolygonVecotr = tmp_area4.TrianglesInPolygonVecotr;
        // ==================================================================================
        CString scenePath = g_sceneDataPath.c_str();
        CString area_texture = scenePath + "\\AreaTexture\\grassland\\area.bmp";
        // 面符号纹理
        // m_Area4_Array[i]->area_texture = area_texture;
        /*  if(i == 1)
        {
        area_texture = scenePath + "\\Terrain\\Tex\\cd5.bmp";

        m_Area4_Array[i]->area_texture = area_texture;
        }
        else if(i == 2)
        {
        area_texture = scenePath + "\\Terrain\\Tex\\cd4.bmp";

        m_Area4_Array[i]->area_texture = area_texture;
        }
        else
        {
        m_Area4_Array[i]->area_texture = area_texture;
        }*/
        if (m_Area4_Array[i]->area_texture == "") {
            // AfxMessageBox("texture == NULL");
            m_Area4_Array[i]->area_texture = area_texture;
            LoadAreaTexture(area_texture, m_Area4_Array[i]->area_texture_rd);
        } else {
            LoadAreaTexture(m_Area4_Array[i]->area_texture, m_Area4_Array[i]->area_texture_rd);
        }
    }
    Area_fuse_Flag = TRUE;
}

// 多边形三角化
void CMy3DSymbolLibNewView::Area_Triangled(const PArea_4& _area4) {
    if (Area_fuse_Flag == TRUE && m_Drawmode == 3) {
        glPushAttrib(GL_CURRENT_BIT);  // 保存现有颜色属性
        glPushMatrix();             // 压入矩阵堆栈
        glLineWidth(3.0);           // 设置线宽
        glColor3f(0, 0.5, 1);       // 设置颜色
        {
            glBindTexture(GL_TEXTURE_2D, _area4->area_texture_rd);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
            static const double deta = 1.00;
            // 1.多边形内原先完整的三角形
            for (uint32 i = 0; i < _area4->TrianglesInPolygonVecotr.size(); ++i) {
                glColor3f(1.0000 , 0.9804 , 0.9804);
                glBegin(GL_TRIANGLES);
                {
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt1.x, _area4->TrianglesInPolygonVecotr[i].pt1.y + deta, _area4->TrianglesInPolygonVecotr[i].pt1.z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt2.x, _area4->TrianglesInPolygonVecotr[i].pt2.y + deta, _area4->TrianglesInPolygonVecotr[i].pt2.z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt3.x, _area4->TrianglesInPolygonVecotr[i].pt3.y + deta, _area4->TrianglesInPolygonVecotr[i].pt3.z);
                }
                glEnd();
            }
            // 2. 经过局部三角化的三角形
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr1.size(); ++i) {
                glColor3f(0.0980 , 0.0980 , 0.4392);
                glBegin(GL_TRIANGLES);
                {
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr1[i].pt1.x, _area4->LocalTrianglesVecotr1[i].pt1.y + deta, _area4->LocalTrianglesVecotr1[i].pt1.z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr1[i].pt2.x, _area4->LocalTrianglesVecotr1[i].pt2.y + deta, _area4->LocalTrianglesVecotr1[i].pt2.z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr1[i].pt3.x, _area4->LocalTrianglesVecotr1[i].pt3.y + deta, _area4->LocalTrianglesVecotr1[i].pt3.z);
                }
                glEnd();
            }
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr2.size(); ++i) {
                glColor3f(0.611, 0.400, 0.121);
                glBegin(GL_TRIANGLES);
                {
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr2[i].pt1.x, _area4->LocalTrianglesVecotr2[i].pt1.y + deta, _area4->LocalTrianglesVecotr2[i].pt1.z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr2[i].pt2.x, _area4->LocalTrianglesVecotr2[i].pt2.y + deta, _area4->LocalTrianglesVecotr2[i].pt2.z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr2[i].pt3.x, _area4->LocalTrianglesVecotr2[i].pt3.y + deta, _area4->LocalTrianglesVecotr2[i].pt3.z);
                }
                glEnd();
            }
            // 2.1 多边形 顶点处
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr1_1.size(); ++i) {
                glColor3f(1.0000 , 0.3882 , 0.2784);
                glBegin(GL_TRIANGLES);
                {
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt1.x, _area4->LocalTrianglesVecotr1_1[i].pt1.y + deta, _area4->LocalTrianglesVecotr1_1[i].pt1.z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt2.x, _area4->LocalTrianglesVecotr1_1[i].pt2.y + deta, _area4->LocalTrianglesVecotr1_1[i].pt2.z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt3.x, _area4->LocalTrianglesVecotr1_1[i].pt3.y + deta, _area4->LocalTrianglesVecotr1_1[i].pt3.z);
                }
                glEnd();
            }
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr2_1.size(); ++i) {
                glColor3f(0.6980 , 0.1333 , 0.1333);
                glBegin(GL_TRIANGLES);
                {
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt1.x, _area4->LocalTrianglesVecotr2_1[i].pt1.y + deta, _area4->LocalTrianglesVecotr2_1[i].pt1.z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt2.x, _area4->LocalTrianglesVecotr2_1[i].pt2.y + deta, _area4->LocalTrianglesVecotr2_1[i].pt2.z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt3.x, _area4->LocalTrianglesVecotr2_1[i].pt3.y + deta, _area4->LocalTrianglesVecotr2_1[i].pt3.z);
                }
                glEnd();
            }
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr_last.size(); ++i) {
                glColor3f(0.6275,  0.1255,  0.9412);
                glBegin(GL_TRIANGLES);
                {
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt1.x, _area4->LocalTrianglesVecotr_last[i].pt1.y + deta, _area4->LocalTrianglesVecotr_last[i].pt1.z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt2.x, _area4->LocalTrianglesVecotr_last[i].pt2.y + deta, _area4->LocalTrianglesVecotr_last[i].pt2.z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt3.x, _area4->LocalTrianglesVecotr_last[i].pt3.y + deta, _area4->LocalTrianglesVecotr_last[i].pt3.z);
                }
                glEnd();
            }
        }
        glLineWidth(1.0);           // 恢复线宽
        glPopAttrib();
        glPopMatrix();              // 弹出矩阵堆栈
    }
    // ...............................................................
    if (Area_fuse_Flag == TRUE && m_Drawmode == 1) {
        glPushAttrib(GL_CURRENT_BIT);  // 保存现有颜色属性
        glPushMatrix();             // 压入矩阵堆栈
        glLineWidth(3.0);           // 设置线宽
        glColor3f(0, 0.5, 1);       // 设置颜色
        {
            // 1.多边形内原先完整的三角形
            for (uint32 i = 0; i < _area4->TrianglesInPolygonVecotr.size(); ++i) {
                glColor3f(1.0000, 0.9804, 0.9804);
                glBegin(GL_TRIANGLES);
                {
                    glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt1.x, _area4->TrianglesInPolygonVecotr[i].pt1.y , _area4->TrianglesInPolygonVecotr[i].pt1.z);
                    glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt2.x, _area4->TrianglesInPolygonVecotr[i].pt2.y , _area4->TrianglesInPolygonVecotr[i].pt2.z);
                    glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt3.x, _area4->TrianglesInPolygonVecotr[i].pt3.y , _area4->TrianglesInPolygonVecotr[i].pt3.z);
                }
                glEnd();
            }
            // 2. 经过局部三角化的三角形
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr1.size(); ++i) {
                glColor3f(1.0, 1.0, 0.1);
                glBegin(GL_TRIANGLES);
                {
                    glVertex3f(_area4->LocalTrianglesVecotr1[i].pt1.x, _area4->LocalTrianglesVecotr1[i].pt1.y , _area4->LocalTrianglesVecotr1[i].pt1.z);
                    glVertex3f(_area4->LocalTrianglesVecotr1[i].pt2.x, _area4->LocalTrianglesVecotr1[i].pt2.y , _area4->LocalTrianglesVecotr1[i].pt2.z);
                    glVertex3f(_area4->LocalTrianglesVecotr1[i].pt3.x, _area4->LocalTrianglesVecotr1[i].pt3.y , _area4->LocalTrianglesVecotr1[i].pt3.z);
                }
                glEnd();
            }
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr2.size(); ++i) {
                glColor3f(0.611, 0.400, 0.121);
                glBegin(GL_TRIANGLES);
                {
                    glVertex3f(_area4->LocalTrianglesVecotr2[i].pt1.x, _area4->LocalTrianglesVecotr2[i].pt1.y , _area4->LocalTrianglesVecotr2[i].pt1.z);
                    glVertex3f(_area4->LocalTrianglesVecotr2[i].pt2.x, _area4->LocalTrianglesVecotr2[i].pt2.y , _area4->LocalTrianglesVecotr2[i].pt2.z);
                    glVertex3f(_area4->LocalTrianglesVecotr2[i].pt3.x, _area4->LocalTrianglesVecotr2[i].pt3.y , _area4->LocalTrianglesVecotr2[i].pt3.z);
                }
                glEnd();
            }
            // 2.1 多边形 顶点处
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr1_1.size(); ++i) {
                glColor3f(1.0000, 0.3882, 0.2784);
                glBegin(GL_TRIANGLES);
                {
                    glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt1.x, _area4->LocalTrianglesVecotr1_1[i].pt1.y , _area4->LocalTrianglesVecotr1_1[i].pt1.z);
                    glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt2.x, _area4->LocalTrianglesVecotr1_1[i].pt2.y , _area4->LocalTrianglesVecotr1_1[i].pt2.z);
                    glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt3.x, _area4->LocalTrianglesVecotr1_1[i].pt3.y , _area4->LocalTrianglesVecotr1_1[i].pt3.z);
                }
                glEnd();
            }
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr2_1.size(); ++i) {
                glColor3f(0.6980, 0.1333, 0.1333);
                glBegin(GL_TRIANGLES);
                {
                    glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt1.x, _area4->LocalTrianglesVecotr2_1[i].pt1.y, _area4->LocalTrianglesVecotr2_1[i].pt1.z);
                    glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt2.x, _area4->LocalTrianglesVecotr2_1[i].pt2.y, _area4->LocalTrianglesVecotr2_1[i].pt2.z);
                    glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt3.x, _area4->LocalTrianglesVecotr2_1[i].pt3.y, _area4->LocalTrianglesVecotr2_1[i].pt3.z);
                }
                glEnd();
            }
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr_last.size(); ++i) {
                glColor3f(0.6275, 0.1255, 0.9412);
                glBegin(GL_TRIANGLES);
                {
                    glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt1.x, _area4->LocalTrianglesVecotr_last[i].pt1.y, _area4->LocalTrianglesVecotr_last[i].pt1.z);
                    glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt2.x, _area4->LocalTrianglesVecotr_last[i].pt2.y, _area4->LocalTrianglesVecotr_last[i].pt2.z);
                    glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt3.x, _area4->LocalTrianglesVecotr_last[i].pt3.y, _area4->LocalTrianglesVecotr_last[i].pt3.z);
                }
                glEnd();
            }
        }
        glLineWidth(1.0);           // 恢复线宽
        glPopAttrib();
        glPopMatrix();              // 弹出矩阵堆栈
    }
}


void CMy3DSymbolLibNewView::Line_Area_Triangled(const PArea_4& _area4) {
    if (pL2DRoad_->Line_fuse_Flag_ == TRUE && m_Drawmode == 3) {
        glPushAttrib(GL_CURRENT_BIT);  // 保存现有颜色属性
        glPushMatrix();             // 压入矩阵堆栈
        glLineWidth(1.0);           // 设置线宽
        glColor3f(0, 0.5, 1);       // 设置颜色
        {
            glBindTexture(GL_TEXTURE_2D, _area4->area_texture_rd);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
            static const double deta = 0.1;
            // 1.多边形内原先完整的三角形
            for (uint32 i = 0; i < _area4->TrianglesInPolygonVecotr.size(); ++i) {
                glColor3f(1.0000 , 0.9804 , 0.9804);
                glBegin(GL_TRIANGLES);
                {
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt1.x, _area4->TrianglesInPolygonVecotr[i].pt1.y + deta, _area4->TrianglesInPolygonVecotr[i].pt1.z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt2.x, _area4->TrianglesInPolygonVecotr[i].pt2.y + deta, _area4->TrianglesInPolygonVecotr[i].pt2.z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt3.x, _area4->TrianglesInPolygonVecotr[i].pt3.y + deta, _area4->TrianglesInPolygonVecotr[i].pt3.z);
                }
                glEnd();
            }
            // 2. 经过局部三角化的三角形
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr1.size(); ++i) {
                glColor3f(0.0980 , 0.0980 , 0.4392);
                glBegin(GL_TRIANGLES);
                {
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr1[i].pt1.x, _area4->LocalTrianglesVecotr1[i].pt1.y + deta, _area4->LocalTrianglesVecotr1[i].pt1.z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr1[i].pt2.x, _area4->LocalTrianglesVecotr1[i].pt2.y + deta, _area4->LocalTrianglesVecotr1[i].pt2.z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr1[i].pt3.x, _area4->LocalTrianglesVecotr1[i].pt3.y + deta, _area4->LocalTrianglesVecotr1[i].pt3.z);
                }
                glEnd();
            }
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr2.size(); ++i) {
                glColor3f(0.611, 0.400, 0.121);
                glBegin(GL_TRIANGLES);
                {
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr2[i].pt1.x, _area4->LocalTrianglesVecotr2[i].pt1.y + deta, _area4->LocalTrianglesVecotr2[i].pt1.z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr2[i].pt2.x, _area4->LocalTrianglesVecotr2[i].pt2.y + deta, _area4->LocalTrianglesVecotr2[i].pt2.z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr2[i].pt3.x, _area4->LocalTrianglesVecotr2[i].pt3.y + deta, _area4->LocalTrianglesVecotr2[i].pt3.z);
                }
                glEnd();
            }
            // 2.1 多边形 顶点处
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr1_1.size(); ++i) {
                glColor3f(1.0000 , 0.3882 , 0.2784);
                glBegin(GL_TRIANGLES);
                {
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt1.x, _area4->LocalTrianglesVecotr1_1[i].pt1.y + deta, _area4->LocalTrianglesVecotr1_1[i].pt1.z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt2.x, _area4->LocalTrianglesVecotr1_1[i].pt2.y + deta, _area4->LocalTrianglesVecotr1_1[i].pt2.z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt3.x, _area4->LocalTrianglesVecotr1_1[i].pt3.y + deta, _area4->LocalTrianglesVecotr1_1[i].pt3.z);
                }
                glEnd();
            }
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr2_1.size(); ++i) {
                glColor3f(0.6980 , 0.1333 , 0.1333);
                glBegin(GL_TRIANGLES);
                {
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt1.x, _area4->LocalTrianglesVecotr2_1[i].pt1.y + deta, _area4->LocalTrianglesVecotr2_1[i].pt1.z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt2.x, _area4->LocalTrianglesVecotr2_1[i].pt2.y + deta, _area4->LocalTrianglesVecotr2_1[i].pt2.z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt3.x, _area4->LocalTrianglesVecotr2_1[i].pt3.y + deta, _area4->LocalTrianglesVecotr2_1[i].pt3.z);
                }
                glEnd();
            }
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr_last.size(); ++i) {
                glColor3f(0.6275,  0.1255,  0.9412);
                glBegin(GL_TRIANGLES);
                {
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt1.x, _area4->LocalTrianglesVecotr_last[i].pt1.y + deta, _area4->LocalTrianglesVecotr_last[i].pt1.z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt2.x, _area4->LocalTrianglesVecotr_last[i].pt2.y + deta, _area4->LocalTrianglesVecotr_last[i].pt2.z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt3.x, _area4->LocalTrianglesVecotr_last[i].pt3.y + deta, _area4->LocalTrianglesVecotr_last[i].pt3.z);
                }
                glEnd();
            }
        }
        glLineWidth(1.0);           // 恢复线宽
        glPopAttrib();
        glPopMatrix();              // 弹出矩阵堆栈
    }
    // ...............................................................
    if (pL2DRoad_->Line_fuse_Flag_ == TRUE && m_Drawmode == 1) {
        glPushAttrib(GL_CURRENT_BIT);  // 保存现有颜色属性
        glPushMatrix();             // 压入矩阵堆栈
        glLineWidth(3.0);           // 设置线宽
        glColor3f(0, 0.5, 1);       // 设置颜色
        {
            // 1.多边形内原先完整的三角形
            for (uint32 i = 0; i < _area4->TrianglesInPolygonVecotr.size(); ++i) {
                glColor3f(1.0000, 0.9804, 0.9804);
                glBegin(GL_TRIANGLES);
                {
                    glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt1.x, _area4->TrianglesInPolygonVecotr[i].pt1.y , _area4->TrianglesInPolygonVecotr[i].pt1.z);
                    glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt2.x, _area4->TrianglesInPolygonVecotr[i].pt2.y , _area4->TrianglesInPolygonVecotr[i].pt2.z);
                    glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt3.x, _area4->TrianglesInPolygonVecotr[i].pt3.y , _area4->TrianglesInPolygonVecotr[i].pt3.z);
                }
                glEnd();
            }
            Vec3 tmpRGB(0.1, 0.1, 0.5);
            // 2. 经过局部三角化的三角形
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr1.size(); ++i) {
                glColor3f(1.0, 1.0, 0.1);
                glBegin(GL_TRIANGLES);
                {
                    glVertex3f(_area4->LocalTrianglesVecotr1[i].pt1.x, _area4->LocalTrianglesVecotr1[i].pt1.y , _area4->LocalTrianglesVecotr1[i].pt1.z);
                    glVertex3f(_area4->LocalTrianglesVecotr1[i].pt2.x, _area4->LocalTrianglesVecotr1[i].pt2.y , _area4->LocalTrianglesVecotr1[i].pt2.z);
                    glVertex3f(_area4->LocalTrianglesVecotr1[i].pt3.x, _area4->LocalTrianglesVecotr1[i].pt3.y , _area4->LocalTrianglesVecotr1[i].pt3.z);
                }
                glEnd();
            }
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr2.size(); ++i) {
                glColor3f(0.611, 0.400, 0.121);
                glBegin(GL_TRIANGLES);
                {
                    glVertex3f(_area4->LocalTrianglesVecotr2[i].pt1.x, _area4->LocalTrianglesVecotr2[i].pt1.y , _area4->LocalTrianglesVecotr2[i].pt1.z);
                    glVertex3f(_area4->LocalTrianglesVecotr2[i].pt2.x, _area4->LocalTrianglesVecotr2[i].pt2.y , _area4->LocalTrianglesVecotr2[i].pt2.z);
                    glVertex3f(_area4->LocalTrianglesVecotr2[i].pt3.x, _area4->LocalTrianglesVecotr2[i].pt3.y , _area4->LocalTrianglesVecotr2[i].pt3.z);
                }
                glEnd();
            }
            // 2.1 多边形 顶点处
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr1_1.size(); ++i) {
                glColor3f(1.0000, 0.3882, 0.2784);
                glBegin(GL_TRIANGLES);
                {
                    glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt1.x, _area4->LocalTrianglesVecotr1_1[i].pt1.y , _area4->LocalTrianglesVecotr1_1[i].pt1.z);
                    glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt2.x, _area4->LocalTrianglesVecotr1_1[i].pt2.y , _area4->LocalTrianglesVecotr1_1[i].pt2.z);
                    glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt3.x, _area4->LocalTrianglesVecotr1_1[i].pt3.y , _area4->LocalTrianglesVecotr1_1[i].pt3.z);
                }
                glEnd();
            }
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr2_1.size(); ++i) {
                glColor3f(0.6980, 0.1333, 0.1333);
                glBegin(GL_TRIANGLES);
                {
                    glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt1.x, _area4->LocalTrianglesVecotr2_1[i].pt1.y, _area4->LocalTrianglesVecotr2_1[i].pt1.z);
                    glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt2.x, _area4->LocalTrianglesVecotr2_1[i].pt2.y, _area4->LocalTrianglesVecotr2_1[i].pt2.z);
                    glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt3.x, _area4->LocalTrianglesVecotr2_1[i].pt3.y, _area4->LocalTrianglesVecotr2_1[i].pt3.z);
                }
                glEnd();
            }
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr_last.size(); ++i) {
                // glColor3f(0.6275, 0.1255, 0.9412);
                glColor3f(0.511, 0.300, 0.221);
                glBegin(GL_TRIANGLES);
                {
                    glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt1.x, _area4->LocalTrianglesVecotr_last[i].pt1.y, _area4->LocalTrianglesVecotr_last[i].pt1.z);
                    glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt2.x, _area4->LocalTrianglesVecotr_last[i].pt2.y, _area4->LocalTrianglesVecotr_last[i].pt2.z);
                    glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt3.x, _area4->LocalTrianglesVecotr_last[i].pt3.y, _area4->LocalTrianglesVecotr_last[i].pt3.z);
                }
                glEnd();
            }
        }
        glLineWidth(1.0);           // 恢复线宽
        glPopAttrib();
        glPopMatrix();              // 弹出矩阵堆栈
    }
}




void CMy3DSymbolLibNewView::LoadAreaTexture(CString _areaTexture_str, UINT& texture_id) {  // 加载面符号纹理  // NOLINT
    char cc[256] = "";
    // strcpy(cc,  _areaTexture_str);
    _snprintf_s(cc, sizeof(cc), sizeof(cc) - 1, _areaTexture_str);
    LoadT8(cc,  texture_id);
}

// 更换选中的面符号的纹理
void CMy3DSymbolLibNewView::UpdateAreaTexture(PPR_Point _mp, CPoint point) {
    uint32 tmp_size = m_Area4_Array.GetSize();
    for (uint32 i = 0; i < tmp_size; ++i) {
        Area_4 m_area4;
        m_area4.pt1 = m_Area4_Array[i]->pt1;
        m_area4.pt2 = m_Area4_Array[i]->pt2;
        m_area4.pt3 = m_Area4_Array[i]->pt3;
        m_area4.pt4 = m_Area4_Array[i]->pt4;
        CPointPolygonRelationship tmp_ppr;
        PPR_Polygon tmp_polygon;
        PPR_Point tmp_point;
        tmp_point.x = m_area4.pt1.x;
        tmp_point.y = m_area4.pt1.z;
        tmp_polygon.push_back(tmp_point);
        tmp_point.x = m_area4.pt2.x;
        tmp_point.y = m_area4.pt2.z;
        tmp_polygon.push_back(tmp_point);
        tmp_point.x = m_area4.pt3.x;
        tmp_point.y = m_area4.pt3.z;
        tmp_polygon.push_back(tmp_point);
        tmp_point.x = m_area4.pt4.x;
        tmp_point.y = m_area4.pt4.z;
        tmp_polygon.push_back(tmp_point);
        PPR_Point tmp_dem_point;
        int32 inPolygonFlag = tmp_ppr.InPolygon(tmp_polygon, _mp);
        if (inPolygonFlag == 0) {  // 点在多边形内
            // 右键快捷菜单
            CMenu menu;
            menu.LoadMenu(IDR_POPUP_MENU_AREA_TEXTURE_UPDATE);
            CMenu* pPopUp = menu.GetSubMenu(0);
            ClientToScreen(&point);
            pPopUp->TrackPopupMenu(/*TPM_LEFTALIGN | */TPM_RIGHTBUTTON, point.x, point.y, this);
            area_id = i;
        } else {
            // AfxMessageBox("点不在多边形内!");
        }
    }
}



// 更换选中的线符号的属性
void CMy3DSymbolLibNewView::UpdateLineSymbol(PPR_Point _mp, CPoint point) {
    for (auto it = pL2DRoad_->allLineArea4Array_.begin(); it != pL2DRoad_->allLineArea4Array_.end(); ++it) {
        auto pOneLineAllArea = (*it).second;
        line_selected_id = -1;
        int32 inPolygonFlag = -1;
        uint32 tmp_size = (*pOneLineAllArea).GetSize();
        for (uint32 i = 0; i < tmp_size; ++i) {
            Area_4 m_area4;
            m_area4.pt1 = (*pOneLineAllArea)[i]->pt1;
            m_area4.pt2 = (*pOneLineAllArea)[i]->pt2;
            m_area4.pt3 = (*pOneLineAllArea)[i]->pt3;
            m_area4.pt4 = (*pOneLineAllArea)[i]->pt4;
            CPointPolygonRelationship tmp_ppr;
            PPR_Polygon tmp_polygon;
            PPR_Point tmp_point;
            tmp_point.x = m_area4.pt1.x;
            tmp_point.y = m_area4.pt1.z;
            tmp_polygon.push_back(tmp_point);
            tmp_point.x = m_area4.pt2.x;
            tmp_point.y = m_area4.pt2.z;
            tmp_polygon.push_back(tmp_point);
            tmp_point.x = m_area4.pt3.x;
            tmp_point.y = m_area4.pt3.z;
            tmp_polygon.push_back(tmp_point);
            tmp_point.x = m_area4.pt4.x;
            tmp_point.y = m_area4.pt4.z;
            tmp_polygon.push_back(tmp_point);
            PPR_Point tmp_dem_point;
            inPolygonFlag = tmp_ppr.InPolygon(tmp_polygon, _mp);
            if (inPolygonFlag == 0) {
                break;
            }
        }
        if (inPolygonFlag == 0) {  // 点在多边形内
            // 右键快捷菜单
            CMenu menu;
            menu.LoadMenu(IDR_POPUP_MENU_LINE_OPERATE);
            CMenu* pPopUp = menu.GetSubMenu(0);
            ClientToScreen(&point);
            pPopUp->TrackPopupMenu(/*TPM_LEFTALIGN | */TPM_RIGHTBUTTON, point.x, point.y, this);
            line_selected_id = (*it).first;
            // LOGGER_INFO << "[D] line_selected_id = " << line_selected_id;
            break;
        } else {
            // AfxMessageBox("点不在多边形内!");
        }
    }
}

/************************************************************************/
/* 点符号模型                                                            */
/************************************************************************/
// 菜单 ==》添加点符号模型
void CMy3DSymbolLibNewView::OnMenuAddPointSymbol() {
    // TODO(jason): 在此添加命令处理程序代码
}

// 3dsMax 标记符号
void CMy3DSymbolLibNewView::OnMenuAddPoint3dsmax() {
    // TODO(jason): 在此添加命令处理程序代码
    int32 newFlag = 0;
    if (!exist_point_file()) {
        INT_PTR nRes;
        nRes = MessageBox("没有打开的点文件，需要新建文件吗？", "找不到点文件", MB_YESNO | MB_ICONQUESTION);
        if (nRes == IDYES) {
            newFlag = new_point_file();
            if (0 == newFlag) {
                exist_point_flag = TRUE;
            }
        }
    } else {
        On3dsModelLoad();
    }
}

// 2D 图片标记符号
void CMy3DSymbolLibNewView::OnMenuAddPoint2dImg() {
    // TODO(jason): 在此添加命令处理程序代码
    int32 newFlag = 0;
    if (!exist_point_file()) {
        INT_PTR nRes;
        nRes = MessageBox("没有打开的点文件，需要新建文件吗？", "找不到点文件", MB_YESNO | MB_ICONQUESTION);
        if (nRes == IDYES) {
            newFlag = new_point_file();
            if (0 == newFlag) {
                exist_point_flag = TRUE;
            }
        }
    } else {
        OnTreeLoad();
    }
}

// 3D 图片标记符号
void CMy3DSymbolLibNewView::OnMenuAddPoint3dImg() {
    // TODO(jason): 在此添加命令处理程序代码
    int32 newFlag = 0;
    if (!exist_point_file()) {
        INT_PTR nRes;
        nRes = MessageBox("没有打开的点文件，需要新建文件吗？", "找不到点文件", MB_YESNO | MB_ICONQUESTION);
        if (nRes == IDYES) {
            newFlag = new_point_file();
            if (0 == newFlag) {
                exist_point_flag = TRUE;
            }
        }
    } else {
        On3dTreeLoad();
    }
}

// 新建工程/打开工程 对话框, 消息响应
LRESULT CMy3DSymbolLibNewView::OnProjectSetted(WPARAM wParam, LPARAM lParam) {
    if (1 == wParam) {      // new project
        OnSceneNew();
    } else if (0 == wParam) {  // open project
        if (g_recentlyOpenedProjectName == "") {
            AfxMessageBox(_T("请选择需要打开的工程!"));
        } else if (g_recentlyOpenedProjectName == _T("更多工程...")) {
            OnSceneLoad();
        } else {
            // 加载选中的工程文件
            CString tmpName = g_recentlyOpenedProjectName.c_str();
            loadSceneFile(tmpName);
            m_CurrentProjectName = tmpName;
        }
    }
    return 0;
}


// 鼠标移到面符号多边形上右击弹出菜单单击响应
void CMy3DSymbolLibNewView::OnMenuUpdateAreaTexture() {
    // TODO(jason): 在此添加命令处理程序代码
    // AfxMessageBox("点在多边形内.");
    CAreaClassification ac_dlg;
    CString selectItem = "";
    if (ac_dlg.DoModal() == IDOK) {
        selectItem = ac_dlg.m_selectItem;
        CString m_areaTexturePath = ac_dlg.m_Dir + "\\" + selectItem;
        if (area_id >= 0 && area_id < m_Area4_Array.GetSize()) {
            m_Area4_Array[area_id]->area_texture = m_areaTexturePath;
            LoadAreaTexture(m_areaTexturePath, m_Area4_Array[area_id]->area_texture_rd);
        }
    } else {
        return;
    }
}

// 删除指定面符号
void CMy3DSymbolLibNewView::OnMenuAreaDelete() {
    // TODO(jason): 在此添加命令处理程序代码
    m_Area4_Array[area_id]->deleted = 1;
}

/************************************************************************/
/*                              线符号                                  */
/************************************************************************/

// 二维道路矢量与三维地形融合
void CMy3DSymbolLibNewView::OnLine2dRoadAdd() {
    int32 newFlag = 0;
    if (!exist_line_file()) {
        INT_PTR nRes;
        nRes = MessageBox("没有打开的线文件，需要新建文件吗？", "找不到线文件", MB_YESNO | MB_ICONQUESTION);
        if (nRes == IDYES) {
            newFlag = new_line_file();
            if (0 == newFlag) {
                exist_line_flag = TRUE;
            }
        }
    } else {
        if (spaceSearchInfo_.m_QueryType == LINE_ADD) {
            spaceSearchInfo_.m_QueryType = -1;
            //
            if (nullptr != pLineSymbol_) {
                delete pLineSymbol_;
                pLineSymbol_ = nullptr;
            }
        } else {
            spaceSearchInfo_.m_QueryType = LINE_ADD;
            // 创建新的线符号
            pLineSymbol_ = new LineSymbol;
        }
    }
}


void CMy3DSymbolLibNewView::OnLine2dRoadFuse() {
    if (pL2DRoad_->allLineArea4Array_.empty()) {
        return;
    }
    // =========================================================================================
    for (auto it = pL2DRoad_->allLineArea4Array_.begin(); it != pL2DRoad_->allLineArea4Array_.end(); ++it) {
        // for (uint32 k = 0; k < pL2DRoad_->allLineArea4Array_.size(); ++k) {
        auto pLineArea4Array = (*it).second;
        uint32 tmp_size = (*pLineArea4Array).GetSize();
        for (uint32 i = 0; i < tmp_size; ++i) {
            Area_4 tmp_area4;
            tmp_area4.pt1 = (*pLineArea4Array)[i]->pt1;
            tmp_area4.pt2 = (*pLineArea4Array)[i]->pt2;
            tmp_area4.pt3 = (*pLineArea4Array)[i]->pt3;
            tmp_area4.pt4 = (*pLineArea4Array)[i]->pt4;
            pArea4Symbol_->FindAllTrianglesInPolygon(tmp_area4, g_terrain);
            (*pLineArea4Array)[i]->pt1 = tmp_area4.pt1;
            (*pLineArea4Array)[i]->pt2 = tmp_area4.pt2;
            (*pLineArea4Array)[i]->pt3 = tmp_area4.pt3;
            (*pLineArea4Array)[i]->pt4 = tmp_area4.pt4;
            (*pLineArea4Array)[i]->LocalTrianglesVecotr1 = tmp_area4.LocalTrianglesVecotr1;
            (*pLineArea4Array)[i]->LocalTrianglesVecotr1_1 = tmp_area4.LocalTrianglesVecotr1_1;
            (*pLineArea4Array)[i]->LocalTrianglesVecotr2 = tmp_area4.LocalTrianglesVecotr2;
            (*pLineArea4Array)[i]->LocalTrianglesVecotr2_1 = tmp_area4.LocalTrianglesVecotr2_1;
            (*pLineArea4Array)[i]->LocalTrianglesVecotr_last = tmp_area4.LocalTrianglesVecotr_last;
            (*pLineArea4Array)[i]->TrianglesInPolygonVecotr = tmp_area4.TrianglesInPolygonVecotr;
            // ==================================================================================
            CString scenePath = g_sceneDataPath.c_str();
            CString area_texture = scenePath + "\\SymbolTexture\\LineSymbolTexture\\LINE_TEXTURE_06.bmp";
            if ((*pLineArea4Array)[i]->area_texture == "NONE") {
                // AfxMessageBox("texture == NULL");
                (*pLineArea4Array)[i]->area_texture = area_texture;
                LoadAreaTexture(area_texture, (*pLineArea4Array)[i]->area_texture_rd);
                LOGGER_INFO << "texture = " << (*pLineArea4Array)[i]->area_texture;
            } else {
                LoadAreaTexture((*pLineArea4Array)[i]->area_texture, (*pLineArea4Array)[i]->area_texture_rd);
                LOGGER_INFO << "texture2 = " << (*pLineArea4Array)[i]->area_texture;
            }
        }
    }
    pL2DRoad_->Line_fuse_Flag_ = TRUE;
    if (nullptr != pLineSymbol_) {
        delete pLineSymbol_;
        pLineSymbol_ = nullptr;
    }
    // 取消添加线前面的勾选状态
    spaceSearchInfo_.m_QueryType = -1;
}


void CMy3DSymbolLibNewView::OnLine2dRoadSet() {
}


void CMy3DSymbolLibNewView::OnUpdateLine2dRoadAdd(CCmdUI* pCmdUI) {
    pCmdUI->SetCheck(spaceSearchInfo_.m_QueryType == LINE_ADD);
}


// 结束选线(一条线路结束)
void CMy3DSymbolLibNewView::OnLine2dRoadAddEnd() {
    if (nullptr == pLineSymbol_) {
        return;
    }
    if (false == pLineSymbol_->inserted_) {
        pL2DRoad_->SaveLineSymbol(pLineSymbol_, g_terrain);
        pLineSymbol_->inserted_ = true;
    } else {
        return;
    }
}


void CMy3DSymbolLibNewView::OnUpdateLine2dRoadFuse(CCmdUI* pCmdUI) {
}

// 右击菜单(LineDelete)
void CMy3DSymbolLibNewView::OnPopupLineDelete() {
    if (line_selected_id >= 0) {
        // 更新线符号属性中的纹理信息
        auto it = pL2DRoad_->allLineSymbols_.find(line_selected_id);
        if (it != pL2DRoad_->allLineSymbols_.end()) {
            (*it).second.deleted_ = true;
            // LOGGER_INFO << "[D] allLineSymbols_ find "<< lineTexturePathStr;
        } else {
            // LOGGER_INFO << "[D] allLineSymbols_ NOT  find ...."<< lineTexturePathStr;
        }
        // 更新线符号上所有面的纹理
        auto it2 = pL2DRoad_->allLineArea4Array_.find(line_selected_id);
        if (it2 != pL2DRoad_->allLineArea4Array_.end()) {
            auto pOneLineAllArea = (*it2).second;
            // LOGGER_INFO << "[D] allLineArea4Array_ find "<< lineTexturePathStr << "  " << line_selected_id;
            for (int32 i = 0; i < pOneLineAllArea->GetSize(); ++i) {
                auto pArea = pOneLineAllArea->GetAt(i);
                pArea->deleted = 1;
            }
        } else {
            // LOGGER_INFO << "[D] allLineArea4Array_ NOT  find ...."<< lineTexturePathStr;
        }
    }
}

// 右击菜单(LineModifyTexture)
void CMy3DSymbolLibNewView::OnPopupLineModifyTexture() {
    CAreaClassification ac_dlg;
    CString selectItem = "";
    if (ac_dlg.DoModal() == IDOK) {
        selectItem = ac_dlg.m_selectItem;
        CString lineTexturePath = ac_dlg.m_Dir + "\\" + selectItem;
        std::ostringstream lineTexturePathSS;
        lineTexturePathSS << (LPSTR)(LPCTSTR)lineTexturePath;
        std::string lineTexturePathStr = lineTexturePathSS.str();
        // LOGGER_INFO << "[D ]OnPopupLineModifyTexture = " << line_selected_id;
        if (line_selected_id >= 0) {
            // 更新线符号属性中的纹理信息
            auto it = pL2DRoad_->allLineSymbols_.find(line_selected_id);
            if (it != pL2DRoad_->allLineSymbols_.end()) {
                (*it).second.line_texture_ = lineTexturePathStr;
                // LOGGER_INFO << "[D] allLineSymbols_ find "<< lineTexturePathStr;
            } else {
                // LOGGER_INFO << "[D] allLineSymbols_ NOT  find ...."<< lineTexturePathStr;
            }
            // 更新线符号上所有面的纹理
            auto it2 = pL2DRoad_->allLineArea4Array_.find(line_selected_id);
            if (it2 != pL2DRoad_->allLineArea4Array_.end()) {
                auto pOneLineAllArea = (*it2).second;
                // LOGGER_INFO << "[D] allLineArea4Array_ find "<< lineTexturePathStr << "  " << line_selected_id;
                for (int32 i = 0; i < pOneLineAllArea->GetSize(); ++i) {
                    auto pArea = pOneLineAllArea->GetAt(i);
                    pArea->area_texture = lineTexturePath;
                    LoadAreaTexture(lineTexturePath, pArea->area_texture_rd);
                }
            } else {
                // LOGGER_INFO << "[D] allLineArea4Array_ NOT  find ...."<< lineTexturePathStr;
            }
        }
    } else {
        return;
    }
}

// 右击菜单(LineModifyWidth)
void CMy3DSymbolLibNewView::OnPopupLineModifyWidth() {
}
