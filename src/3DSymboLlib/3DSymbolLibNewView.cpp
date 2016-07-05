#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "3DSymbolLibNew.h"
#endif

#include <sstream>
#include "3DSymbolLibNewDoc.h"
#include "3DSymbolLibNewView.h"
#include "Bitmap.h"
#include "ModelParam.h"
#include "DialogModelList.h"
#include "ModelListConfigureDialog.h"
#include "SystemSetting.h"



#include "AreaClassification.h"


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
    ON_COMMAND(ID_MENU_LINE_ADD, &CMy3DSymbolLibNewView::OnMenuLineAdd)
    ON_COMMAND(ID_MENU_LINE_FUSE, &CMy3DSymbolLibNewView::OnMenuLineFuse)
    ON_UPDATE_COMMAND_UI(ID_MENU_LINE_ADD, &CMy3DSymbolLibNewView::OnUpdateMenuLineAdd)
    ON_COMMAND(ID_MENU_ADD_LINE_WIDTH, &CMy3DSymbolLibNewView::OnMenuAddLineWidth)
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
END_MESSAGE_MAP()

// CMy3DSymbolLibNewView 构造/析构

CMy3DSymbolLibNewView::CMy3DSymbolLibNewView() {
    bIsSelect3DModel = false;
    bIsMouseMove3DModel = false;
}

CMy3DSymbolLibNewView::~CMy3DSymbolLibNewView() {
    // Empty
}

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

    wglMakeCurrent(pDC->m_hDC, m_hRC);  // 使 RC 与当前 DC 相关联
    DrawScene();  // 场景绘制
    glFlush();
    ::SwapBuffers(m_pDC->GetSafeHdc());  // 交换缓冲区
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
    // #ifndef SHARED_HANDLERS
    //  theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
    // #endif
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




/************************************************************************/
/* Function: 初始化相关变量                                             */
/************************************************************************/
void CMy3DSymbolLibNewView::InitData() {
    glActiveTextureARB = NULL;
    glMultiTexCoord2fARB = NULL;
    m_ViewWideNarrow = 0.0f;                            // 初始飞行视口宽窄变量
    hwnd = GetSafeHwnd();
    CDC* pDestDC = CDC::FromHandle(::GetDC(hwnd));
    m_SCREEN_WIDTH = pDestDC->GetDeviceCaps(HORZRES);   // 屏幕宽度
    m_SCREEN_HEIGHT = pDestDC->GetDeviceCaps(VERTRES);  // 屏幕高度
    m_near = 1;                                         // 观察点与近侧剪裁平面的距离
    m_far = 5000;                                      // 观察点与远侧剪裁平面的距离
    m_shizxLength = 2;                                 // 查询标志十字线长度
    m_shuzxHeight = 2;                                 // 查询标志竖直线高度
    m_QueryLineWidth = 1;                              // 查询标志线的宽度
    m_QueryColorR = 255;                               // 查询标志线的颜色(红)
    m_QueryColorG = 0;                                 // 查询标志线的颜色(绿)
    m_QueryColorB = 0;                                 // 查询标志线的颜色(蓝)
    m_bSearchDistencePtNums = 0;
    // 渲染模式
    m_Drawmode = 3;
    iTerrainType = 0;
    iSkyBoxLoaded = false;
    g_isTerrainInit = false;
    // 相机参数向上矢量
    m_vUp.x = 0;
    m_vUp.y = 1;
    m_vUp.z = 0;
    m_viewdegree = 0;  // 初始视角增量
    m_viewHeight = m_oldviewHeight = 88;  // 相机初始高度
    m_vEyePosition.x = 334;
    m_vEyePosition.z = -384;
    m_vEyePosition.y = 88;
    g_Angle = 6;                        // 视点方位角初值
    g_elev = 0;                         // 俯仰角初始值
    gao = 1.8;
    rad_xz = float (PAI_D180 * g_Angle);  // 计算左右旋转角度
    m_vLook.x = m_vEyePosition.x + 100 * cos(rad_xz);
    m_vLook.z = m_vEyePosition.z + 100 * sin(rad_xz);
    m_vLook.y = m_vEyePosition.y + g_elev;
    m_Step_X = 5.0;     // 相机在X方向移动的步长初始值(鼠标控制)
    m_Step_Z = 5.0;     // 相机在Z方向移动的步长初始值(鼠标控制)
    m_xTrans = 0;       // 在X方向上移动的步长(键盘控制)
    m_zTrans = 0;       // 在Z方向上移动的步长(键盘控制)
    derAngleY = 500.0f;
    derAngleZ = 4000.0f;
    derDisScale = 1.5;
    m_PathFlag = FALSE;
    m_flyspeed = 1000;
    m_maxHeight = -9999;
    m_minHeight = 9999;
    m_ViewUpDown = 0;
    m_FlyPause = FALSE;
    m_fly_start_pause_Enable = FALSE;  // 暂停/开始是否生效
    // 指北针初始指向角度(90度,即表示正北方向,在三维空间中则指向Z员负方向,即指向屏幕里面)
    m_NorthPtangle = 90;
    m_bShowbreviary = TRUE;
    m_i3DModelNum = 0;
    m_3ds = new CLoad3DS();
    m_bMouseMove3DModelPtNums = 0;
    m_iTreeModelNum = 0;
    m_i3DTreeModelNum = 0;
    m_iCitySymbolModelNum = 0;
    bIsWeatherLoad = false;
    IsSearchPoint = false;
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
    m_QueryType = -1;
    // checkbox,是否通过鼠标设置模型摆放位置
    m_isSetXYByMouse = 0;
    initLines();  // 初始化线路数据
    // [160220]
    // 初始化各种点模型所在路径
    m_3DModelFolder     = "3DModel";
    m_CitySymbolFolder  = "CitySymbol";
    m_TreeModelFolder   = "TreeModel";
    // [160119]
    m_LineEdit_pointNum = 0;
    fuse_Flag = FALSE;
    // [160209]
    m_Area_pointNum = 0;
    Area_fuse_Flag = FALSE;
    // 是否存在已打开的符号文件
    exist_point_flag = FALSE;
    exist_line_flag = FALSE;
    exist_area_flag = FALSE;
    m_CurrentProjectName = "";
    m_PointSymbolFile = "0";
    m_LineSymbolFile = "0";
    m_AreaSymbolFile = "0";
}


/************************************************************************/
/* Function: 初始化线路数据                                             */
/************************************************************************/
void CMy3DSymbolLibNewView::initLines() {
    //==========================================================
    b_haveMadeRail3DwayList = FALSE;  // 是否已经有三维线路显示列表(透视投影模式下)
    m_Railway.m_Railway_width = 5.0;  // 路基断面总宽度
    m_Railway.m_Lj_width = 0.8;     // 路肩宽度
    m_Railway.m_GuiMianToLujianWidth = 0.6;  // 碴肩至碴脚的高度
    m_Railway.m_Lj_Dh = m_Railway.m_GuiMianToLujianWidth * (1 / 1.75);  // 铁轨到碴肩的距离
    m_Railway.m_TieGui_width = 1.435;  // 铁轨间距
    // ==========================================================
    // 选线阈值设定(距离,夹角)
    // 用于计算2点之间线段长度
    last_x = 0, last_y = 0, last_z = 0;
    pre_x  = 0, pre_y  = 0, pre_z = 0;
    // 用于计算2线段间夹角
    v1_begin.Set(0, 0, 0);
    v1_end.Set(0, 0, 0);
    v2_begin.Set(0, 0, 0);
    v2_end.Set(0, 0, 0);
    // 记录点的个数
    p_count = 0;
    m_distance_between_2_points = 0.0;
    m_pre_distance = 0.0;
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
        return FALSE;
    }
    return TRUE;
}


BOOL CMy3DSymbolLibNewView::SetupPixelFormat() {
    // 初始化象素格式以及选取合适的格式来创建RC
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR) ,  // pfd结构的大小
        1 ,  // 版本号
        PFD_DRAW_TO_WINDOW |  // 支持在窗口中绘图
        PFD_SUPPORT_OPENGL |  // 支持 OpenGL
        PFD_DOUBLEBUFFER |  // 双缓存模式
        PFD_STEREO |  // 支持立体模式
        PFD_TYPE_RGBA ,  // RGBA 颜色模式
        24 ,  // 24 位颜色深度
        0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  // 忽略颜色位
        0 ,  // 没有非透明度缓存
        0 ,  // 忽略移位位
        0 ,  // 无累加缓存
        0 ,  0 ,  0 ,  0 ,  // 忽略累加位
        32 ,  // 32 位深度缓存
        0 ,  // 无模板缓存
        0 ,  // 无辅助缓存
        PFD_MAIN_PLANE ,  // 主层
        0 ,  // 保留
        0 ,  0 ,  0  // 忽略层 , 可见性和损毁掩模
    };
    // 在DC中选择合适的象素格式并返回索引号
    int32 pixelformat;
    pixelformat =::ChoosePixelFormat(m_pDC->GetSafeHdc() , &pfd);
    if (pixelformat == 0) {
        MessageBox("选择像素格式失败!" , "设置像素格式" , MB_ICONERROR);
        return FALSE;
    }
    // 设置指定象素格式
    if (::SetPixelFormat(m_pDC->GetSafeHdc() , pixelformat , &pfd) == FALSE) {
        MessageBox("设置像素格式失败!" , "设置像素格式" , MB_ICONERROR);
        return FALSE;
    }
    // 测试当前设置和硬件显卡是否支持立体模式
    unsigned char ucTest;
    glGetBooleanv(GL_STEREO ,  &ucTest);
    if (!ucTest) {
        return 1;
    }
    if ((pfd.dwFlags & PFD_STEREO) == 0)
        bStereoAvailable = FALSE;  // 显卡不支持立体模式
    else
        bStereoAvailable = TRUE;
    CString stt[5];
    if (bStereoAvailable == FALSE) {  // 如果显卡不支持立体模式，给出可能的错误原因
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
        WinViewX = cx;                             // 视口宽度
        WinViewY = cy;                             // 视口高度
        glViewport(0, 0, cx, cy);                // 设置视口大小
        float m_aspectRatio = static_cast<float>(cx) / static_cast<float>(cy);  // 视口的横纵比例
        glMatrixMode(GL_PROJECTION);                // 将当前矩阵设置为投影矩阵,指明当前矩阵为GL_PROJECTION
        glLoadIdentity();                           // 将当前矩阵置换为单位阵
        gluPerspective(50.0 + m_ViewWideNarrow , m_aspectRatio , m_near , m_far);  // fovy=50.0 + m_ViewWideNarrow , 是视野角度
        glMatrixMode(GL_MODELVIEW);                 // 将当前矩阵设置为模型矩阵
        glLoadIdentity();                           // 将当前矩阵置换为单位阵
    }
}


/************************************************************************/
/* Function: 导入等高线地形数据和纹理                                       */
/************************************************************************/
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


/************************************************************************/
/* Function: 调等高线地势图                                             */
/************************************************************************/
unsigned char* CMy3DSymbolLibNewView::LoadBit(char* filename, BITMAPINFOHEADER* bitmap) {
    FILE* filePtr;                                              // 定义位图结构
    BITMAPFILEHEADER  Header;                                   // 定义位图指针
    unsigned char*    Image;                                    // 图形缓存区
    uint32      imageIdx = 0;                             // 图形索引
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
    Image = (unsigned char*)malloc(bitmap->biSizeImage);            // 申请图形区
    if (!Image) {                                               // 申请图形区失败
        free(Image);                                            // 释放图形区
        fclose(filePtr);                                        // 关闭文件
        return NULL;                                            // 返回空
    }
    fread(Image, 1, bitmap->biSizeImage, filePtr);              // 将图形数据读入
    if (Image == NULL) {                                        // 数据读入为空
        fclose(filePtr);                                        // 关闭文件
        return NULL;                                            // 返回空
    }
    for (imageIdx = 0; imageIdx < bitmap->biSizeImage; imageIdx += 3) {
        tempRGB = Image[imageIdx];
        Image[imageIdx] = Image[imageIdx + 2];
        Image[imageIdx + 2] = tempRGB;
    }                                                           // 交换数据
    fclose(filePtr);                                            // 关闭文件
    return Image;                                               // 返回图形数据
}


void CMy3DSymbolLibNewView::InitTerrain() {
    int32 index = 0;
    int32 Vertex;
    for (int32 z = 0; z < MAP_W; z++)
        for (int32 x = 0; x < MAP_W; x++) {                               // MAP_W是地形块数，32行，32列的方形地形
            Vertex = z * MAP_W + x;
            g_terrain [Vertex][0] = static_cast<float>(x) * MAP_SCALE;               // 地域数组 3维，MAP_SCALE是边长
            g_terrain [Vertex][1] = static_cast<float>(g_imageData[Vertex * 3] / 3);  // 地域数组 3维 灰度等高线生成高度图，在Modelobj初始化就赋值了
            g_terrain [Vertex][2] = -static_cast<float>(z) * MAP_SCALE;                  // 地域数组 3维
            g_texcoord[Vertex][0] = static_cast<float>(x);                          // 索引数组2维，指示曲面贴图的平面坐标
            g_texcoord[Vertex][1] = static_cast<float>(z);
            g_index [index++] = Vertex;                                 // 顶点数组1维，曲面顶点，一维顶点数组加快显示
            g_index [index++] = Vertex + MAP_W;
            // 获取地形高度极值
            if (m_maxHeight < g_terrain [Vertex][1]) m_maxHeight = g_terrain [Vertex][1];
            if (m_minHeight > g_terrain [Vertex][1]) m_minHeight = g_terrain [Vertex][1];
            g_max_height = m_maxHeight;  // 保存最大高程值到全局变量中
        }
    // 顶点数组  第一步 启用数组
    glEnableClientState(GL_VERTEX_ARRAY);                   // 允许使用地域数组
    // 顶点数组  第二步 制定数组数据
    glVertexPointer(3, GL_FLOAT, 0, g_terrain);             // 装入地域数据
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);            // 允许使用索引数组
    glTexCoordPointer(2, GL_FLOAT, 0, g_texcoord);          // 装入索引数组
}


/************************************************************************/
/* Function: 三维地形绘制   ,利用glDrawElements快速绘制排列好的顶点地形     */
/************************************************************************/
void CMy3DSymbolLibNewView::DrawTerrain() {
    // glShadeModel函数用来设置阴影的效果，GL_SMOOTH为默认值，表示平滑阴影效果；
    glShadeModel(GL_SMOOTH);
    SetDrawMode();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0 + m_ViewWideNarrow , static_cast<float>(WinViewX) / static_cast<float>(WinViewY), m_near , m_far);
    glMatrixMode(GL_MODELVIEW);  // 定义矩阵为模型模型矩阵
    glLoadIdentity();           // 将当前矩阵置换为单位矩阵
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
    if (m_bShowbreviary == TRUE) {  // 显示缩略视图
        glViewport(WinViewX * 5 / 6 ,  WinViewY * 5 / 6 , WinViewX / 6 ,  WinViewY / 6);
        glBindTexture(GL_TEXTURE_2D, texTerrain);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        for (int32 z = 0; z < MAP_W - 1; z++) {
            // 顶点数组  第三步 渲染
            glDrawElements(GL_TRIANGLE_STRIP, MAP_W * 2, GL_UNSIGNED_INT, &g_index[z * MAP_W * 2]);
        }
        glViewport(0, 0, WinViewX, WinViewY);  // 重新设置视口大小
    }
}


/************************************************************************/
/* Function: 获取地面高度                                                   */
/************************************************************************/
float CMy3DSymbolLibNewView::GetHeight(float x, float z) {
    float CameraX = x / MAP_SCALE;                  // 计算在哪一列
    float CameraZ = -z / MAP_SCALE;                     // 计算在哪一行
    int32 Col0 = static_cast<int32>(CameraX);                        // 块的列号
    int32 Row0 = static_cast<int32>(CameraZ);                        // 块的行号
    int32 Col1 = Col0 + 1;                            // 相邻列
    int32 Row1 = Row0 + 1;                            // 相邻块
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

/********************************************************/
/* Function:设置绘图模式                                    */
/********************************************************/
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


/********************************************************/
/* Function:场景绘制                                     */
/********************************************************/
void CMy3DSymbolLibNewView::DrawScene() {
    glClearColor(0.53, 0.81, 0.92, 0.0);                // 设置刷新背景色SkyBlue: 135,206,235
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // 刷新背景
    glLoadIdentity();                                   // 重置当前的模型观察矩阵
    SetDrawMode();
    if (m_vEyePosition.x <  MAP_SCALE) {
        m_vEyePosition.x = MAP_SCALE;
    }
    if (m_vEyePosition.x > (MAP_W - 2) * MAP_SCALE)    {
        m_vEyePosition.x = (MAP_W - 2) * MAP_SCALE;
    }
    if (m_vEyePosition.z < -(MAP_W - 2) * MAP_SCALE) {
        m_vEyePosition.z = -(MAP_W - 2) * MAP_SCALE;
    }
    if (m_vEyePosition.z > -MAP_SCALE) {
        m_vEyePosition.z = -MAP_SCALE;
    }
    SetCamra();
    if (iTerrainType != 0) {
        if (iSkyBoxLoaded) {
            DrawSky();
        }
        DrawClock();            // 绘制指北针
        DrawTerrain();
        DrawFlyPath();
        DrawRailwaythesme();    // 绘制铁路
        if (m_QueryType == QUERY_COORDINATE || m_QueryType == QUERY_DISTENCE || m_QueryType == SELECTLINE
                || m_QueryType == LINE_ADD  // Line
                || m_QueryType == AREA_ADD  // Area
           ) {
            DrawSearchPoint();  // 绘制空间查询标志
        }
        // [160120]
        if (fuse_Flag) {
            DrawJDLine(Line_a_JD_vector, Line_b_JD_vector);
        }
        if (Area_fuse_Flag) {
            int32 tmp_size = m_Area4_Array.GetSize();
            for (int32 i = 0; i < tmp_size; ++i) {
                /*  Area_4 tmp_area4;
                tmp_area4.pt1 = m_Area4_Array[i]->pt1;
                tmp_area4.pt2 = m_Area4_Array[i]->pt2;
                tmp_area4.pt3 = m_Area4_Array[i]->pt3;
                tmp_area4.pt4 = m_Area4_Array[i]->pt4;


                tmp_area4.LocalTrianglesVecotr1 = m_Area4_Array[i]->LocalTrianglesVecotr1;
                tmp_area4.LocalTrianglesVecotr1_1 = m_Area4_Array[i]->LocalTrianglesVecotr1_1;
                tmp_area4.LocalTrianglesVecotr2 = m_Area4_Array[i]->LocalTrianglesVecotr2;
                tmp_area4.LocalTrianglesVecotr2_1 = m_Area4_Array[i]->LocalTrianglesVecotr2_1;

                tmp_area4.LocalTrianglesVecotr_last = m_Area4_Array[i]->LocalTrianglesVecotr_last;
                tmp_area4.TrianglesInPolygonVecotr = m_Area4_Array[i]->TrianglesInPolygonVecotr;

                Area_Triangled(tmp_area4);
                */
                if (m_Area4_Array[i]->deleted != 1) {
                    Area_Triangled(m_Area4_Array[i]);
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
        if (bIsWeatherLoad) {
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
    GLfloat light_position[] = {m_vEyePosition.x, 300, m_vEyePosition.z - 100};
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


/********************************************************/
/* Function:天空盒纹理导入以及参数设置                      */
/********************************************************/
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


/********************************************************/
/* Function:生成天空                                        */
/********************************************************/
void CMy3DSymbolLibNewView::CreateSkyBox() {
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

void CMy3DSymbolLibNewView::SkyBoxTexture(UINT textur) {
    glBindTexture(GL_TEXTURE_2D, textur);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
}

void CMy3DSymbolLibNewView::OnDrawmodeLine() {
    m_Drawmode = 1;
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


/********************************************************/
/* Function:空间查询标志设置                                */
/********************************************************/
void CMy3DSymbolLibNewView::OnSpacequerySet() {
    CSpaceSearchSet dlg;
    dlg.m_shizxLength = m_shizxLength;      // 查询标志十字线长度
    dlg.m_shuzxHeight = m_shuzxHeight;      // 查询标志竖直线高度
    dlg.m_QueryLineWidth = m_QueryLineWidth;  // 查询标志线的宽度
    dlg.m_QueryColorR = m_QueryColorR;      // 查询标志线的颜色(红)
    dlg.m_QueryColorG = m_QueryColorG;      // 查询标志线的颜色(绿)
    dlg.m_QueryColorB = m_QueryColorB;      // 查询标志线的颜色(蓝)
    if (dlg.DoModal() == IDOK) {
        m_shizxLength = dlg.m_shizxLength;              // 得到新设置的查询标志十字线长度
        m_shuzxHeight = dlg.m_shuzxHeight;              // 得到新设置的查询标志竖直线高度
        m_QueryLineWidth = dlg.m_QueryLineWidth + 1;    // 得到新设置的查询标志线的宽度，下标从0开始
        m_QueryColorR = dlg.m_QueryColorR;              // 得到新设置的查询标志线的颜色(红)
        m_QueryColorG = dlg.m_QueryColorG;              // 得到新设置的查询标志线的颜色(绿)
        m_QueryColorB = dlg.m_QueryColorB;              // 得到新设置的//查询标志线的颜色(蓝)
    }
}


/********************************************************/
/* Function: 查询三维坐标                                   */
/********************************************************/
void CMy3DSymbolLibNewView::OnQueryCoordinate() {
    if (m_QueryType == QUERY_COORDINATE) {  // 如果当前已经是查询三维坐标状态，则关闭
        m_QueryType = -1;
    } else {                            // 如果当前已经不是查询三维坐标状态，则打开
        m_QueryType = QUERY_COORDINATE;
    }
    m_OperateType = -1;
}


/********************************************************/
/* Function: 设置是否选中状态                               */
/********************************************************/
void CMy3DSymbolLibNewView::OnUpdateQueryCoordinate(CCmdUI* pCmdUI) {
    pCmdUI->SetCheck(m_QueryType == QUERY_COORDINATE);
}

void CMy3DSymbolLibNewView::OnQueryDistence() {
    if (m_QueryType == QUERY_DISTENCE) {  // 如果当前已经是查询空间距离状态，则关闭
        m_QueryType = -1;
    } else {                            // 如果当前不是查询空间距离状态，则关闭，则打开
        m_QueryType = QUERY_DISTENCE;
    }
}

void CMy3DSymbolLibNewView::OnUpdateQueryDistence(CCmdUI* pCmdUI) {
    pCmdUI->SetCheck(m_QueryType == QUERY_DISTENCE);
}




/********************************************************/
/* Function: 屏幕坐标 ==> 三维坐标                      */
/********************************************************/
void CMy3DSymbolLibNewView::ScreenToGL(CPoint point) {
    int32 mouse_x = point.x;
    int32 mouse_y = point.y;
    GLint viewport[4];
    GLdouble modelview[16] , projection[16];
    GLdouble wx , wy , wz;
    float winX , winY , winZ;
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
        wx =  MAP_SCALE;         // X边
    }
    if (wx > (MAP_W - 1)*MAP_SCALE) {
        wx = (MAP_W - 1) * MAP_SCALE;  // X边
    }
    if (wz < -(MAP_W - 1)*MAP_SCALE) {
        wz = -(MAP_W - 1) * MAP_SCALE;  // Z边
    }
    if (wz > -MAP_SCALE) {
        wz = -MAP_SCALE;         // Z边
    }
    CMainFrame* pMainFrame = reinterpret_cast<CMainFrame*>(GetParent());
    CString strText;
    // 在状态栏指示器上显示相关信息(鼠标所点击处在三维场景中的坐标)
    strText.Format("鼠标坐标:x=%.3f , y=%.3f , z=%.3f" , wx  , wy , wz);
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
        if (m_QueryType == QUERY_COORDINATE) {  // 查询三维坐标
            tt.Format("当前坐标(x,y,z)=(%.3f,%.3f,%.3f)", wx, wy, -wz);
            pt1[0] = wx;
            pt1[1] = wy;
            pt1[2] = wz;                        // 查询获得的三维大地坐标
            Invalidate(FALSE);
            MessageBox(tt, "三维坐标查询", MB_ICONINFORMATION);     // 给出坐标查询信息
            IsSearchPoint = true;
        } else if (m_QueryType == QUERY_DISTENCE) {  // 查询空间距离
            if (m_bSearchDistencePtNums >= 2) {  // 如果选择点数2个，归零
                m_bSearchDistencePtNums = 0;
            }
            m_bSearchDistencePtNums++;         // 选择点数 + 1
            if (m_bSearchDistencePtNums == 1) {  // 如果只选择了1个点
                pt1[0] = wx;
                pt1[1] = wy;
                pt1[2] = wz;  // 将三维点坐标存储到数组 pt1[] 里面
            } else {                            // 选择了两个点，则表示可以计算空间距离了
                pt2[0] = wx;
                pt2[1] = wy;
                pt2[2] = wz;  // 将三维点坐标存储到数组 pt2[] 里面
                // 计算距离
                double mdistence;
                mdistence = sqrt((pt2[0] - pt1[0]) * (pt2[0] - pt1[0]) + (pt2[1] - pt1[1]) * (pt2[1] - pt1[1]) + (pt2[2] - pt1[2]) * (pt2[2] - pt1[2]));
                tt.Format("两点为:\n(x1,y1,z1)=(%.3f,%.3f,%.3f)\n(x2,y2,z2)=(%.3f,%.3f,%.3f)\n距离Dis=%.3f", pt1[0], pt1[1], pt1[2], pt2[0], pt2[1], pt2[2], mdistence);
            }
            Invalidate(FALSE);
            MessageBox(tt, "三维距离查询", MB_ICONINFORMATION);     // 给出距离查询信息
        } else if (m_QueryType == LINE_ADD) {  // [160119] 线编辑  添加线
            m_LineEdit_pointNum++;         // 选择点数 + 1
            if (m_LineEdit_pointNum == 1) {  // 如果只选择了1个点
                m_line.pt1._x = wx;
                m_line.pt1._y = wy;
                m_line.pt1._z = wz;
            } else if (m_LineEdit_pointNum == 2) {
                m_line.pt2._x = wx;
                m_line.pt2._y = wy;
                m_line.pt2._z = wz;
            }
            if (m_LineEdit_pointNum >= 2) {  // 如果选择点数2个，归零
                m_LineEdit_pointNum = 0;
                PLine3 line = new Line3;
                line->pt1 = m_line.pt1;
                line->pt2 = m_line.pt2;
                m_LinesArray.Add(line);
            }
        } else if (m_QueryType == AREA_ADD) {  // [160209]选取面符号上的点
            m_Area_pointNum++;         // 选择点数 + 1
            if (m_Area_pointNum == 1) {
                m_area4_forScreenRecord.pt1._x = wx;
                m_area4_forScreenRecord.pt1._y = wy;
                m_area4_forScreenRecord.pt1._z = wz;
            } else if (m_Area_pointNum == 2) {
                m_area4_forScreenRecord.pt2._x = wx;
                m_area4_forScreenRecord.pt2._y = wy;
                m_area4_forScreenRecord.pt2._z = wz;
            } else if (m_Area_pointNum == 3) {
                m_area4_forScreenRecord.pt3._x = wx;
                m_area4_forScreenRecord.pt3._y = wy;
                m_area4_forScreenRecord.pt3._z = wz;
            } else if (m_Area_pointNum == 4) {
                m_area4_forScreenRecord.pt4._x = wx;
                m_area4_forScreenRecord.pt4._y = wy;
                m_area4_forScreenRecord.pt4._z = wz;
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
        } else if (m_QueryType == SELECTLINE) {  // 如果是三维选线设计
            PCordinate ppt = new Cordinate;
            float tmpH = 0;                         // (x,z)处高程值
            float* pDegree = new float(0);          // 通过函数参数返回夹角的值
            const float threshold_distance = 100.0f;  // 2点间最短距离
            // 2线段间最小夹角
            const float threshold_degree = 20;
            CString warningMsg;                     // 提示信息
            if ((ppt == NULL)) {
                AfxMessageBox("Failed to add a new ppt");
                return;
            }
            if (1) {
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
                AfxMessageBox(warningMsg);
            } else {
                // 设计线路时确保2端点间的距离 > threshold_distance
                if (p_count == 0) {
                    pre_x = ppt->x;
                    pre_y = tmpH;
                    pre_z = ppt->z;
                    fun(ppt);
                    p_count++;
                } else if (p_count >= 1) {
                    if (m_distance_between_2_points > threshold_distance) {
                        m_pre_distance = m_distance_between_2_points;
                    }
                    last_x = ppt->x;
                    last_y = tmpH;
                    last_z = ppt->z;
                    m_distance_between_2_points = static_cast<float>(sqrt((last_x - pre_x) * (last_x - pre_x) + (last_y - pre_y) * (last_y - pre_y) + (last_z - pre_z) * (last_z - pre_z)));
                    if (m_distance_between_2_points > threshold_distance) {  // 距离阈值
                        if (p_count == 1) {
                            fun(ppt);
                            p_count++;
                            v1_end.x = pre_x;
                            v1_end.y = 0;
                            v1_end.z = pre_z;
                            v1_begin.x = last_x;
                            v1_begin.y = 0;
                            v1_begin.z = last_z;
                            pre_x = ppt->x;
                            pre_y = tmpH;
                            pre_z = ppt->z;
                        } else {
                            v2_begin = v1_begin;
                            v2_end.x = last_x;
                            v2_end.y = 0;
                            v2_end.z = last_z;
                            // 计算2个向量之间的夹角, 通过指针作函数参数返回
                            getDegreeBetween2Vectors(v1_begin, v1_end, v2_begin, v2_end, pDegree);
                            if (*pDegree > threshold_degree) {  // 夹角阈值
                                v1_end.x = pre_x;
                                v1_end.y = 0;
                                v1_end.z = pre_z;
                                v1_begin.x = last_x;
                                v1_begin.y = 0;
                                v1_begin.z = last_z;
                                float min_distance_between_2_lines = (m_pre_distance < m_distance_between_2_points ? m_pre_distance : m_distance_between_2_points);
                                if (*pDegree < 30) {
                                    m_Curve_R = 15;
                                    m_Curve_L0 = 1;
                                } else {
                                    m_Curve_R = min_distance_between_2_lines * tan((*pDegree / 2.13) * PAI / 180);
                                    m_Curve_L0 = 6 * m_Curve_R / 100;
                                    if (m_Curve_L0 < 1)
                                        m_Curve_L0 = 1;
                                }
                                fun(ppt);
                                pre_x = ppt->x;
                                pre_y = tmpH;
                                pre_z = ppt->z;
                            } else {  // 夹角阈值
                                warningMsg.Format(_T("Degree = %f度 > %f度\n线路转角太大,请重新选择!"), 180 - *pDegree, 180 - threshold_degree);
                                AfxMessageBox(warningMsg, MB_OK, MB_ICONEXCLAMATION);
                            }
                        }
                    } else {  // 距离阈值
                        warningMsg.Format(_T("Distance = %f < %f\n两点之间距离太短,请重新选择!"), m_distance_between_2_points, threshold_distance);
                        AfxMessageBox(warningMsg, MB_OK, MB_ICONEXCLAMATION);
                    }
                }
            }
        } else if (m_QueryType == SELECTFLYPATH) {  // 如果是设置飞行路径
            PCordinate ppt = new Cordinate;
            ppt->x = wx;
            ppt->y = wy;
            ppt->z = wz;                        // 记录飞行路径的三维坐标
            m_FlayPath.Add(ppt);                                    // 将飞行路径的三维坐标存储到数组m_FlayPath
            Invalidate(FALSE);
        }
        if (m_OperateType == SELECT) {                              // 如果是选择3D模型
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
            CVector3 nearPoint;
            nearPoint.x = posX;
            nearPoint.y = posY;
            nearPoint.z = posZ;
            // 获取像素对应的后裁剪面的点坐标
            bResult = gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &posX, &posY, &posZ);
            CVector3 farPoint;
            farPoint.x = posX;
            farPoint.y = posY;
            farPoint.z = posZ;
            CVector3 n_vector, resultP;
            // cal the vector of ray
            n_vector.x = farPoint.x - nearPoint.x;
            n_vector.y = farPoint.y - nearPoint.y;
            n_vector.z = farPoint.z - nearPoint.z;
            JudgeRayIntersect(nearPoint, n_vector, resultP);
            Invalidate(FALSE);
        } else if (m_OperateType == MOVE) {             // 鼠标移动3D模型
            if (m_bMouseMove3DModelPtNums >= 2)          // 如果选择点数2个，归零
                m_bMouseMove3DModelPtNums = 0;
            m_bMouseMove3DModelPtNums++;               // 选择点数 + 1
            if (m_bMouseMove3DModelPtNums == 1) {       // 如果只选择了1个点
                // JudgeRayIntersect(nearPoint, n_vector, resultP);
                PCordinate ppt = new Cordinate;
                ppt->x = wx;
                ppt->y = wy;
                ppt->z = wz;          // 三维坐标
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
                CVector3 nearPoint;
                nearPoint.x = posX;
                nearPoint.y = posY;
                nearPoint.z = posZ;
                // 获取像素对应的后裁剪面的点坐标
                bResult = gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &posX, &posY, &posZ);
                CVector3 farPoint;
                farPoint.x = posX;
                farPoint.y = posY;
                farPoint.z = posZ;
                CVector3 n_vector, resultP;
                // cal the vector of ray
                n_vector.x = farPoint.x - nearPoint.x;
                n_vector.y = farPoint.y - nearPoint.y;
                n_vector.z = farPoint.z - nearPoint.z;
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
            CVector3 nearPoint;
            nearPoint.x = posX;
            nearPoint.y = posY;
            nearPoint.z = posZ;
            // 获取像素对应的后裁剪面的点坐标
            bResult = gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &posX, &posY, &posZ);
            CVector3 farPoint;
            farPoint.x = posX;
            farPoint.y = posY;
            farPoint.z = posZ;
            CVector3 n_vector, resultP;
            // cal the vector of ray
            n_vector.x = farPoint.x - nearPoint.x;
            n_vector.y = farPoint.y - nearPoint.y;
            n_vector.z = farPoint.z - nearPoint.z;
            JudgeRayIntersect(nearPoint, n_vector, resultP);
        }
    } else if (!m_bMouseMoveSelect) {
        MessageBox("鼠标选择点不够精确 , 请精确选择点!");
        m_bSearchDistencePtNums = 0;
    }
}



void CMy3DSymbolLibNewView::ScreenToGL2(CPoint point, GLdouble& wx , GLdouble& wz) {  // NOLINT
    int32 mouse_x = point.x;
    int32 mouse_y = point.y;
    GLint viewport[4];
    GLdouble modelview[16] , projection[16];
    GLdouble  wy;
    float winX , winY , winZ;
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
        wx =  MAP_SCALE;         // X边
    }
    if (wx > (MAP_W - 1)*MAP_SCALE) {
        wx = (MAP_W - 1) * MAP_SCALE;  // X边
    }
    if (wz < -(MAP_W - 1)*MAP_SCALE) {
        wz = -(MAP_W - 1) * MAP_SCALE;  // Z边
    }
    if (wz > -MAP_SCALE) {
        wz = -MAP_SCALE;         // Z边
    }
}

/********************************************************/
/* Function: 计算2个向量之间的夹角                      */
/********************************************************/
void CMy3DSymbolLibNewView::getDegreeBetween2Vectors(CVector3 v1_Begin, CVector3 v1_End,
        CVector3 v2_Begin, CVector3 v2_End, float* pDegreeRet/*返回结果*/) {
    CVector3 v1 = v1_End - v1_Begin;
    CVector3 v2 = v2_End - v2_Begin;
    float dotProductRet = DotProduct(v1, v2);  // 点积
    float magnitudeV1 = Magnitude(v1);      // v1的模
    float magnitudeV2 = Magnitude(v2);      // v2的模
    float cosM = dotProductRet / (magnitudeV1 * magnitudeV2);
    float angleAMB = acos(cosM) * 180 / PI;
    *pDegreeRet = angleAMB;
}


void CMy3DSymbolLibNewView::fun(PCordinate ppt) {
    m_oldlinePtnums = myDesingScheme.PtS_JD.GetSize();  // 当前线路方案原有设计交点数
    if (m_oldlinePtnums == 0) {                         // 如果当前线路方案没有设计交点,即还没有进行该方案的设计
        myDesingScheme.PtS_JD.Add(ppt);                 // 加入设计交点到PtS_JD数组
        m_linePtnums = myDesingScheme.PtS_JD.GetSize();  // 当前线路方案原有设计交点数
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
        pTempCurveElements->x = myDesingScheme.PtS_JD.GetAt(0)->x;          // 交点的x坐标
        pTempCurveElements->y = fabs(myDesingScheme.PtS_JD.GetAt(0)->z);  // 交点的y坐标
        pTempCurveElements->z = -myDesingScheme.PtS_JD.GetAt(0)->y;     // 交点的z坐标
        // 加入交点元素到DCurveElementss模板数组中
        myDesingScheme.JDCurveElements.Add(pTempCurveElements);
    } else {  // 如果当前线路方案设计交点数>0,表示已经进行该方案的设计
        if (m_linePtnums <= 0) {
            m_linePtnums = myDesingScheme.PtS_JD.GetSize();
        }
        CString tt;
        tt.Format("JD%d", m_linePtnums);  // 交点ID自动增加
        if (m_oldlinePtnums == 1) {
            PLineCurve pTempCurveElements = new LineCurve;
            pTempCurveElements->R = m_Curve_R;      // 曲线半径
            pTempCurveElements->L0 = m_Curve_L0;    // 缓和曲线长
            pTempCurveElements->ID = tt;
            pTempCurveElements->P = (pTempCurveElements->L0 * pTempCurveElements->L0) / (pTempCurveElements->R * 24.0);
            pTempCurveElements->x = ppt->x;
            pTempCurveElements->y = -ppt->z;
            pTempCurveElements->z = ppt->y;
            myDesingScheme.JDCurveElements.Add(pTempCurveElements);
            myDesingScheme.PtS_JD.Add(ppt);
            m_linePtnums = myDesingScheme.PtS_JD.GetSize();
            if (myDesingScheme.PtS_JD.GetSize() > 1) {
                OnDraw(GetWindowDC());
            }
        } else if (m_oldlinePtnums >= 2) {
            myDesingScheme.JDCurveElements[m_oldlinePtnums - 1]->R = m_Curve_R;
            myDesingScheme.JDCurveElements[m_oldlinePtnums - 1]->L0 = m_Curve_L0;
            PLineCurve pTempCurveElements = new LineCurve;
            pTempCurveElements->R = m_Curve_R;      // 曲线半径
            pTempCurveElements->L0 = m_Curve_L0;    // 缓和曲线长
            pTempCurveElements->ID = tt;                // 交点ID
            pTempCurveElements->P = (pTempCurveElements->L0 * pTempCurveElements->L0) / (pTempCurveElements->R * 24.0);
            pTempCurveElements->x = ppt->x;
            pTempCurveElements->y = -ppt->z;
            pTempCurveElements->z = ppt->y;
            myDesingScheme.JDCurveElements.Add(pTempCurveElements);
            myDesingScheme.PtS_JD.Add(ppt);
            m_linePtnums = myDesingScheme.PtS_JD.GetSize();
            if (myDesingScheme.PtS_JD.GetSize() > 1) {
                OnDraw(GetWindowDC());
            }
        }
    }
}


void CMy3DSymbolLibNewView::fun(PCordinate ppt, PCurve_R_L0_Struct pcrl0) {
    m_oldlinePtnums = myDesingScheme.PtS_JD.GetSize();  // 当前线路方案原有设计交点数
    if (m_oldlinePtnums == 0) {                         // 如果当前线路方案没有设计交点,即还没有进行该方案的设计
        myDesingScheme.PtS_JD.Add(ppt);                 // 加入设计交点到PtS_JD数组
        m_linePtnums = myDesingScheme.PtS_JD.GetSize();  // 当前线路方案原有设计交点数
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
        pTempCurveElements->x = myDesingScheme.PtS_JD.GetAt(0)->x;          // 交点的x坐标
        pTempCurveElements->y = fabs(myDesingScheme.PtS_JD.GetAt(0)->z);  // 交点的y坐标
        pTempCurveElements->z = -myDesingScheme.PtS_JD.GetAt(0)->y;      // 交点的z坐标
        // 加入交点元素到DCurveElementss模板数组中
        myDesingScheme.JDCurveElements.Add(pTempCurveElements);
    } else {  // 如果当前线路方案设计交点数>0,表示已经进行该方案的设计
        if (m_linePtnums <= 0) {
            m_linePtnums = myDesingScheme.PtS_JD.GetSize();
        }
        CString tt;
        tt.Format("JD%d", m_linePtnums);  // 交点ID自动增加
        if (1) {
            PLineCurve pTempCurveElements = new LineCurve;
            pTempCurveElements->R = pcrl0->curve_R;         // 曲线半径
            pTempCurveElements->L0 = pcrl0->curve_L0;   // 缓和曲线长
            pTempCurveElements->ID = tt;
            pTempCurveElements->P = (pTempCurveElements->L0 * pTempCurveElements->L0) / (pTempCurveElements->R * 24.0);
            pTempCurveElements->x = ppt->x;
            pTempCurveElements->y = -ppt->z;
            pTempCurveElements->z = ppt->y;
            myDesingScheme.JDCurveElements.Add(pTempCurveElements);
            myDesingScheme.PtS_JD.Add(ppt);
            m_linePtnums = myDesingScheme.PtS_JD.GetSize();
            if (myDesingScheme.PtS_JD.GetSize() > 1) {
                OnDraw(GetWindowDC());
            }
        }
    }
}


/********************************************************/
/* Function: 绘制空间查询标志                               */
/********************************************************/
void CMy3DSymbolLibNewView::DrawSearchPoint() {
    glViewport(0, 0, WinViewX, WinViewY);                                               // 重新设置视口大小
    glPushAttrib(GL_CURRENT_BIT);                                                       // 保存现有颜色属性
    glDisable(GL_TEXTURE_2D);                                                           // 取消贴图
    glPushMatrix();                                                                     // 压入堆栈
    if (m_QueryType == QUERY_COORDINATE) {                                              // 三维空间坐标查询
        if (pt1[0] != -99999) {
            glLineWidth(m_QueryLineWidth);                                              // 设置查询标志线宽度
            glColor3f(m_QueryColorR / 255.0 , m_QueryColorG / 255.0 , m_QueryColorB / 255.0);  // 设置查询标志线颜色
            // 绘制十字型查询标志线
            glBegin(GL_LINES);
            glVertex3f(pt1[0] - m_shizxLength , pt1[1] , pt1[2]);
            glVertex3f(pt1[0] + m_shizxLength , pt1[1] , pt1[2]);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(pt1[0] , pt1[1] , pt1[2] - m_shizxLength);
            glVertex3f(pt1[0] , pt1[1] , pt1[2] + m_shizxLength);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(pt1[0] , pt1[1] , pt1[2]);
            glVertex3f(pt1[0] , pt1[1] + m_shuzxHeight , pt1[2]);
            glEnd();
        }
    } else if (m_QueryType == QUERY_DISTENCE) {     // 三维空间距离查询(在选择两个空间点之后才能够计算空间距离)
        glLineWidth(m_QueryLineWidth);             // 设置查询标志线宽度
        glColor3f(m_QueryColorR / 255.0 , m_QueryColorG / 255.0 , m_QueryColorB / 255.0);  // 设置查询标志线颜色
        // 绘制十字型查询标志线
        glBegin(GL_LINES);
        glVertex3f(pt1[0] - m_shizxLength, pt1[1], pt1[2]);
        glVertex3f(pt1[0] + m_shizxLength, pt1[1], pt1[2]);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(pt1[0], pt1[1], pt1[2] - m_shizxLength);
        glVertex3f(pt1[0], pt1[1], pt1[2] + m_shizxLength);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(pt1[0], pt1[1] , pt1[2]);
        glVertex3f(pt1[0], pt1[1] + m_shuzxHeight, pt1[2]);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(pt2[0] - m_shizxLength, pt2[1], pt2[2]);
        glVertex3f(pt2[0] + m_shizxLength, pt2[1], pt2[2]);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(pt2[0], pt2[1], pt2[2] - m_shizxLength);
        glVertex3f(pt2[0], pt2[1], pt2[2] + m_shizxLength);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(pt2[0], pt2[1], pt2[2]);
        glVertex3f(pt2[0], pt2[1] + m_shuzxHeight, pt2[2]);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(pt1[0], pt1[1], pt1[2]);
        glVertex3f(pt2[0], pt2[1], pt2[2]);
        glEnd();
        glLineWidth(1.0);
    } else if (m_QueryType == SELECTLINE || myDesingScheme.PtS_JD.GetSize() > 0) {  // 三维选线状态
        // 绘制选结过程中的设计交点连线
        m_oldlinePtnums = m_linePtnums;
        glColor3f(0, 0, 1);
        glLineWidth(2.0);
        for (int32 i = 0; i < myDesingScheme.PtS_JD.GetSize() - 1; i++) {
            DrawCenterLine(i, TRUE);  // 绘制线路中心线
        }
        // 绘制交点标志
        for (int32 j = 0; j <= myDesingScheme.PtS_JD.GetSize() - 1; ++j) {
            glLineWidth(m_QueryLineWidth + 1);                                          // 设置标志线宽度
            glColor3f(m_QueryColorR / 255.0 , m_QueryColorG / 255.0 , m_QueryColorB / 255.0);  // 设置标志线颜色
            float tmp_x = myDesingScheme.PtS_JD[j]->x;
            float tmp_z = myDesingScheme.PtS_JD[j]->z;
            float tmp_y = GetHeight(tmp_x, tmp_z);
            // 绘制十字型标志线
            glBegin(GL_LINES);
            glVertex3f(tmp_x - m_shizxLength , tmp_y, tmp_z);
            glVertex3f(tmp_x + m_shizxLength , tmp_y, tmp_z);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(tmp_x, tmp_y, tmp_z - m_shizxLength);
            glVertex3f(tmp_x, tmp_y, tmp_z + m_shizxLength);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(tmp_x, tmp_y, tmp_z);
            glVertex3f(tmp_x, tmp_y + m_shuzxHeight, tmp_z);
            glEnd();
        }
    } else if (m_QueryType == LINE_ADD) {  // [160119]  绘制线段
        glLineWidth(3.0);              // 设置查询标志线宽度
        glColor3f(m_QueryColorR / 255.0 , m_QueryColorG / 255.0 , m_QueryColorB / 255.0);  // 设置查询标志线颜色
        for (int32 i = 0; i < m_LinesArray.GetSize(); ++i) {
            glBegin(GL_LINES);
            glVertex3f(m_LinesArray[i]->pt1._x, m_LinesArray[i]->pt1._y, m_LinesArray[i]->pt1._z);
            glVertex3f(m_LinesArray[i]->pt2._x, m_LinesArray[i]->pt2._y, m_LinesArray[i]->pt2._z);
            glEnd();
        }
        glLineWidth(1.0);
    } else if (m_QueryType == AREA_ADD) {  // [160209] 绘制4边形
        glLineWidth(3.0);              // 设置查询标志线宽度
        glColor3f(0.3, 0.6, 0.5);  // 设置查询标志线颜色
        for (int32 i = 0; i < m_Area4_Array.GetSize(); ++i) {
            if (m_Area4_Array[i]->deleted != 1) {
                glBegin(GL_QUADS);
                glVertex3f(m_Area4_Array[i]->pt1._x, m_Area4_Array[i]->pt1._y, m_Area4_Array[i]->pt1._z);
                glVertex3f(m_Area4_Array[i]->pt2._x, m_Area4_Array[i]->pt2._y, m_Area4_Array[i]->pt2._z);
                glVertex3f(m_Area4_Array[i]->pt3._x, m_Area4_Array[i]->pt3._y, m_Area4_Array[i]->pt3._z);
                glVertex3f(m_Area4_Array[i]->pt4._x, m_Area4_Array[i]->pt4._y, m_Area4_Array[i]->pt4._z);
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
    if (m_QueryType == QUERY_COORDINATE) {  // 空间三维坐标查询
        m_bmouseView = false;
        m_oldMousePos = point;
        ScreenToGL(point);
    } else if (m_QueryType == QUERY_DISTENCE) {  // 空间距离查询
        m_bmouseView = false;               // 关闭鼠标控相机旋转
        m_oldMousePos = point;
        ScreenToGL(point);
    } else if (m_QueryType == SELECTFLYPATH) {  // 进行飞行路径选择
        m_bmouseView = false;               // 关闭鼠标控相机旋转
        m_oldMousePos = point;
        ScreenToGL(point);
    } else if (m_QueryType == SELECTLINE) {  // 进行三维选线设计
        m_bmouseView = false;               // 关闭鼠标控相机旋转
        m_oldMousePos = point;
        ScreenToGL(point);
    } else if (m_QueryType == LINE_ADD) {  // [160119]线编辑   添加线
        m_bmouseView = false;               // 关闭鼠标控相机旋转
        m_oldMousePos = point;
        ScreenToGL(point);
    } else if (m_QueryType == AREA_ADD) {  // [160209] 添加面符号 4边形
        m_bmouseView = false;               // 关闭鼠标控相机旋转
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
    if (m_QueryType == QUERY_DISTENCE || m_QueryType == QUERY_COORDINATE) {
        m_QueryType = -1;  // 关闭三维查询
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
    Invalidate(FALSE);
    CView::OnRButtonDown(nFlags, point);
}

void CMy3DSymbolLibNewView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
    m_keynumber = 0;
    CVector3 vAxis;
    switch (nChar) {            // 根据按键字符来进行相应设置
        case VK_LEFT:
            m_keynumber = 3;
            m_xTrans -= m_Step_X;   // 在X方向上移动的距离累计
            Invalidate(FALSE);      // 刷新三维场景
            break;
        case VK_RIGHT:
            m_keynumber = 4;
            m_xTrans += m_Step_X;   // 在X方向上移动的距离累计
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
                m_zTrans -= m_Step_Z;   // 在Z方向上移动的距离累计
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
                m_zTrans += m_Step_Z;   // 在Z方向上移动的距离累计
                m_keynumber = 2;
            }
            Invalidate(FALSE);          // 刷新三维场景
            break;
        case 'I':
            m_ViewWideNarrow += 1.0;    // 飞行视野增大,看见场景范围增大了,相当于相机镜头向屏幕外方向移动
            OnDraw(GetDC());            // 刷新三维场景
            break;
        case 'O':
            m_ViewWideNarrow -= 1.0;        // 飞行视野减小,看见场景范围减小了,相当于相机镜头向屏幕里方向移动
            OnDraw(GetDC());            // 刷新三维场景
            break;
        case 'J':                       // 加速
            // m_flyspeed -= 1;
            // if(m_flyspeed<=1)
            //  m_flyspeed=1;
            // SetFLyTimer();            // 设置飞行计时器
            break;
        case 'M':                   // 减速
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
            vAxis = CrossProduct(m_vLook - m_vEyePosition, m_vUp);      // 叉积计算
            vAxis = Normalize(vAxis);                                   // vAxis归一化
            RotateView(20 / derAngleZ, vAxis.x, vAxis.y, vAxis.z);      // 通过鼠标控制相机的旋转(旋转视角)
            OnDraw(GetDC());
            break;
        case 'N':
        case VK_NEXT:  // PgDn   俯仰角
            vAxis = CrossProduct(m_vLook - m_vEyePosition, m_vUp);      // 叉积计算
            vAxis = Normalize(vAxis);                                   // vAxis归一化
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
            vAxis = CrossProduct(m_vLook - m_vEyePosition, m_vUp);      // 叉积计算
            vAxis = Normalize(vAxis);                                   // vAxis归一化
            RotateView(-50 / derAngleZ,  0, 1, 0);      // 通过鼠标控制相机的旋转(旋转视角)
            OnDraw(GetDC());
            break;
        case VK_END:  // 逆时针旋转
            vAxis = CrossProduct(m_vLook - m_vEyePosition, m_vUp);      // 叉积计算
            vAxis = Normalize(vAxis);                                   // vAxis归一化
            RotateView(50 / derAngleZ,  0, 1, 0);   // 通过鼠标控制相机的旋转(旋转视角)
            OnDraw(GetDC());
            break;
    }
    CamraUpdate();              // 重新调整相机
    m_keynumber = 0;            // 恢复按键0值
    CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


/****************************************************************/
/* Function: 根据鼠标和键盘实现三维场景相机的移动和旋转控制         */
/****************************************************************/
void CMy3DSymbolLibNewView::CamraUpdate() {
    CVector3 vCross = CrossProduct(m_vLook - m_vEyePosition, m_vUp);  // 叉积计算
    m_vStrafe = Normalize(vCross);                                  // vCross归一化
    SetViewByMouse();                                               // 通过鼠标实现相机控制
    CheckForMovement();                                             // 通过键盘实现相机控制
    m_vEyePosition.y += (m_viewHeight - m_oldviewHeight);           // 新的相机视点y坐标
    m_oldviewHeight = m_viewHeight;                                 // 记录当前相机视点高度
}


/****************************************************************/
/* Function: 在X轴方向上移动时设置相机观察点和视点坐标              */
/****************************************************************/
void CMy3DSymbolLibNewView::MoveCameraX(float speed) {
    m_vEyePosition.x += m_vStrafe.x * speed;                        // 相机视点x新坐标
    m_vEyePosition.z += m_vStrafe.z * speed;                        // 相机视点z新坐标
    m_vLook.x += m_vStrafe.x * speed;                               // 相机观察点x新坐标
    m_vLook.z += m_vStrafe.z * speed;                               // 相机观察点z新坐标
}


/****************************************************************/
/* Function: 在Z轴方向上移动时设置相机观察点和视点坐标              */
/****************************************************************/
void CMy3DSymbolLibNewView::MoveCameraZ(float speed) {
    CVector3 vVector = m_vLook - m_vEyePosition;                        // 相机视点与观察点三维坐标差值
    vVector = Normalize(vVector);                                   // 相机视点与观察点三维坐标差值归一化
    m_vEyePosition.x += vVector.x * speed;                          // 相机视点x新坐标
    m_vEyePosition.z += vVector.z * speed;                          // 相机视点z新坐标
    m_vLook.x += vVector.x * speed;                                 // 相机观察点x新坐标
    m_vLook.z += vVector.z * speed;                                 // 相机观察点z新坐标
}


/****************************************************************/
/* Function: 根据键盘按键值来重新设置相机                           */
/****************************************************************/
void CMy3DSymbolLibNewView::CheckForMovement() {
    if (m_keynumber == 1) {                                         // ↑上箭头按键，向场景外移动(Z轴正方向)
        MoveCameraZ(m_Step_Z);                                      // 在Z轴方向上移动时设置相机观察点和视点坐标
    }
    if (m_keynumber == 2) {                                         // ↓下箭头按键，向场景外移动(Z轴负方向)
        MoveCameraZ(-m_Step_Z);                                     // 在Z轴方向上移动时设置相机观察点和视点坐标
    }
    if (m_keynumber == 3) {                                         // ←左箭头按键，向左方向移动场景(X轴负方向)
        MoveCameraX(-m_Step_X);                                     // 在X轴方向上移动时设置相机观察点和视点坐标
    }
    if (m_keynumber == 4) {                                         // →右箭头按键，向右方向移动场景(X轴正方向)
        MoveCameraX(m_Step_X);                                      // 在X轴方向上移动时设置相机观察点和视点坐标
    }
}


/****************************************************************/
/* Function: 设置相机                                           */
/****************************************************************/
void CMy3DSymbolLibNewView::SetCamra() {
    gluLookAt(m_vEyePosition.x, m_vEyePosition.y, m_vEyePosition.z,     // 视点
              m_vLook.x, m_vLook.y, m_vLook.z,                                // 目标点
              m_vUp.x, m_vUp.y, m_vUp.z);                                     // 视点方向
    CMainFrame* pMainFrame = reinterpret_cast<CMainFrame*>(GetParent());
    CString strText;
    float dy = m_vEyePosition.y - m_vLook.y;
    float dz = fabs(m_vEyePosition.z - m_vLook.z);
    if (fabs(dz) <= 0.000001) {
        m_viewdegree = 0;
    } else {
        m_viewdegree = HDANGLE * atan(dy / dz);
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
    strText.Format("【俯视角】A=%.2f" , m_viewdegree);
    pMainFrame->Set_BarText(1 , strText);
    strText.Format("视点坐标: X=%.3f , Y=%.3f , Z=%.3f" , m_vEyePosition.x  , m_vEyePosition.y , fabs(m_vEyePosition.z));
    pMainFrame->Set_BarText(2 , strText);
    strText.Format("观察点坐标: X=%.3f , Y=%.3f , Z=%.3f" , m_vLook.x  , m_vLook.y , fabs(m_vLook.z));
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
            HCURSOR hCur  =  LoadCursor(AfxGetInstanceHandle() ,
                                        MAKEINTRESOURCE(IDC_CURSOR_SELECT));
            ::SetCursor(hCur);
        } else {
            HCURSOR hCur  =  LoadCursor(AfxGetInstanceHandle() ,
                                        MAKEINTRESOURCE(IDC_CURSOR_EDIT));
            ::SetCursor(hCur);
        }
    }
    if (m_bmouseView == TRUE) {  // 如果鼠标控制场景打开时
        CamraUpdate();      // 根据鼠标和键盘实现三维场景相机的移动和旋转控制
    }
    Invalidate(FALSE);
    CView::OnMouseMove(nFlags, point);
}


/****************************************************************/
/* Function: 通过鼠标实现相机控制                                   */
/****************************************************************/
void CMy3DSymbolLibNewView::SetViewByMouse() {
    if (m_bmouseView == false) {    // 如果鼠标控制场景关闭时,返回
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
        CVector3 vAxis = CrossProduct(m_vLook - m_vEyePosition, m_vUp);     // 叉积计算
        vAxis = Normalize(vAxis);                                           // vAxis归一化
        RotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);      // 通过鼠标控制相机的旋转(旋转视角)
        RotateView(angleY, 0, 1, 0);                        // 通过鼠标控制相机的旋转(旋转视角)
    }
    m_oldMousePos.x = mousePos.x;                           // 记录当前鼠标x坐标
    m_oldMousePos.y = mousePos.y;                           // 记录当前鼠标y坐标
}


/****************************************************************/
/* Function: 通过鼠标控制相机的旋转(旋转视角)                       */
/****************************************************************/
void CMy3DSymbolLibNewView::RotateView(float angle, float x, float y, float z) {
    CVector3 vNewView;
    CVector3 vView = m_vLook - m_vEyePosition;          // 相机视点与观察点三维坐标差值
    float cosTheta = static_cast<float>(cos(angle));                 // 得到旋转视角的cos函数值
    float sinTheta = static_cast<float>(sin(angle));                 // 得到旋转视角的sin函数值
    vNewView.x  = (cosTheta + (1 - cosTheta) * x * x)       * vView.x;
    vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta)   * vView.y;
    vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta)   * vView.z;
    vNewView.y  = ((1 - cosTheta) * x * y + z * sinTheta)   * vView.x;
    vNewView.y += (cosTheta + (1 - cosTheta) * y * y)       * vView.y;
    vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta)   * vView.z;
    vNewView.z  = ((1 - cosTheta) * x * z - y * sinTheta)   * vView.x;
    vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta)   * vView.y;
    vNewView.z += (cosTheta + (1 - cosTheta) * z * z)       * vView.z;
    m_vLook = m_vEyePosition + vNewView;                // 得到旋转后的相机视点坐标
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
/* Function: 手动设置飞行路径                                       */
/****************************************************************/
void CMy3DSymbolLibNewView::OnPathManuinput() {
    m_ShowFlyPath = TRUE;           // 标识是否显示飞行路径
    m_QueryType = SELECTFLYPATH;    // 进行飞行路径选择
    m_FlayPath.RemoveAll();         // 存储进行飞行路径坐标数组清空
}


/****************************************************************/
/* Function: 绘制飞行路径                                           */
/****************************************************************/
void CMy3DSymbolLibNewView::DrawFlyPath() {
    // 如果显示飞行路径并且飞行路径坐标点数>1,才绘制飞行路径
    if (m_ShowFlyPath == TRUE  && m_FlayPath.GetSize() > 1) {  // 进行飞行路径选择
        glPushAttrib(GL_CURRENT_BIT);  // 保存现有颜色属性
        glPushMatrix();             // 压入矩阵堆栈
        glDisable(GL_TEXTURE_2D);   // 关闭纹理(即飞行路径不采用纹理)
        glLineWidth(10.0);          // 设置飞行路径线宽
        glColor3f(1, 0, 0);         // 设置飞行路径颜色
        glBegin(GL_LINE_STRIP);
        for (int32 i = 0; i < m_FlayPath.GetSize(); i++) {
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
/* Function: 路径坐标插值                                           */
/****************************************************************/
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
        double L = Dist(CVector3(x1, y1, z1), CVector3(x2, y2, z2));
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
/* Function: 保存飞行路径                                        */
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlypathSave() {
    CString     NeededFile;
    char        FileFilter[] = "飞行路径(*.pth)|*.pth||";
    // 设置文件对话框属性
    DWORD       FileDialogFlag = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
    CFileDialog FileDialogBoxFile(FALSE, NULL, 0, FileDialogFlag, FileFilter, this);
    FileDialogBoxFile.m_ofn.lpstrTitle = "保存飞行路径文件";
    char        FileName[200];
    CString tt[3];
    if (FileDialogBoxFile.DoModal() == IDOK) {  // 如果对话框成果打开
        NeededFile = FileDialogBoxFile.GetPathName();  // 得到文件名

        // sprintf(FileName, "%s", NeededFile);
        _snprintf_s(FileName, sizeof(FileName), sizeof(FileName)-1, "%s", NeededFile);

        if (strcmp(FileDialogBoxFile.GetFileExt(), "pth") != 0)
            strcat(FileName, ".pth");  // 添加飞行路径文件扩展名  // NOLINT
        if (FlyPathSave(FileName))  // 如果飞行路径保存成功
            MessageBox("路径点保存完毕", "保存飞行路径", MB_ICONWARNING);
    }
    Invalidate(FALSE);
}


/****************************************************************/
/* Function: 飞行路径保存                                           */
/****************************************************************/
int32 CMy3DSymbolLibNewView::FlyPathSave(char* pathfile) {
    FILE*    fpw;
    char    message[200];
    if ((fpw = fopen(pathfile, "w")) == NULL) {         // 如果写入文件失败

        // sprintf(message, "文件 %s 创建无效", pathfile);
        _snprintf_s(message, sizeof(message), sizeof(message)-1, "文件 %s 创建无效", pathfile);

        MessageBox(message, "保存飞行路径坐标到文件", MB_ICONWARNING);
        return 0;                                       // 返回失败
    }
    fprintf(fpw, "%d\n", m_FlayPath.GetSize());         // 写入飞行路径坐标点总数
    for (int32 i = 0; i < m_FlayPath.GetSize(); i++) {
        // 向文件fpw写入飞行路径坐标点的三维坐标
        fprintf(fpw, "%lf,%lf,%lf\n", m_FlayPath.GetAt(i)->x, m_FlayPath.GetAt(i)->y, m_FlayPath.GetAt(i)->z);
    }
    fclose(fpw);        // 关闭文件
    return 1;           // 返回成功
}


/****************************************************************/
/* Function: 打开飞行路径                                           */
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyOpenpath() {
    CString     NeededFile;
    char        FileFilter[] = "飞行路径(*.pth)|*.pth||";
    // 设置文件对话框属性
    DWORD       FileDialogFlag = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
    CFileDialog FileDialogBoxFile(TRUE, NULL, 0, FileDialogFlag, FileFilter, this);
    FileDialogBoxFile.m_ofn.lpstrTitle = "打开飞行路径文件";
    FileDialogBoxFile.m_ofn.lpstrInitialDir = m_AllDataPath;
    char        FileName[200];
    CString tt[3];
    if (FileDialogBoxFile.DoModal() == IDOK) {           // 如果对话框成果打开
        NeededFile = FileDialogBoxFile.GetPathName();   // 得到文件名

        // sprintf(FileName, "%s", NeededFile);
        _snprintf_s(FileName, sizeof(FileName), sizeof(FileName)-1, "%s", NeededFile);

        if (strcmp(FileDialogBoxFile.GetFileExt(), "pth") != 0)
            strcat(FileName, ".pth");                   // 添加飞行路径文件扩展名  // NOLINT
        if (FlyPathRead(FileName))  // 读取飞行路径文件数据动态数组中
            MessageBox("打开路径点完毕", "提示", MB_ICONWARNING);
        if (m_FlayPath.GetSize() > 1) {                 // 如果飞行路径数据坐标点数>1
            m_ShowFlyPath = TRUE;                       // 显示飞行路径
            m_PathFlag = TRUE;                          // 标识飞行路径打开成功
        } else {
            m_PathFlag = FALSE;                         // 标识飞行路径打开失败
        }
    }
    Invalidate(FALSE);
}


/****************************************************************/
/* Function: 读取飞行路径文件数据动态数组中                     */
/****************************************************************/
int32 CMy3DSymbolLibNewView::FlyPathRead(char* pathfile) {
    CString tt, m_strszLine;
    PCordinate ppt = new Cordinate;
    m_FlayPath.RemoveAll();                             // 飞行路径数组清空
    CStdioFile m_inFile;
    if (m_inFile.Open(pathfile, CFile::modeRead) == FALSE) {  // 打开文件
        return 0;                                       // 返回失败标志
    }
    m_inFile.ReadString(m_strszLine);                   // 读取飞行路径坐标点总数
    while (m_inFile.ReadString(m_strszLine)) {
        ppt = new Cordinate;
        m_strszLine.TrimLeft(" ");
        m_strszLine.TrimRight("	");
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
    m_inFile.Close();                                   // 关闭文件
    return 1;                                           // 返回成功标志
}


/****************************************************************/
/* Function: 显示或关闭飞行路径                                 */
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyOnoffpath() {
    if (m_ShowFlyPath == TRUE)                          // 如果当前是显示飞行路径
        m_ShowFlyPath = FALSE;                          // 标识设置为FALSE
    else
        m_ShowFlyPath = TRUE;                           // 反之,设置为TRUE
    Invalidate(FALSE);
}


/****************************************************************/
/* Function: 根据m_ShowFlyPath值修改菜单文本                        */
/****************************************************************/
void CMy3DSymbolLibNewView::OnUpdateFlyOnoffpath(CCmdUI* pCmdUI) {
    if (m_ShowFlyPath == TRUE)                      // 如果当前是显示飞行路径
        pCmdUI->SetText("关闭飞行路径");                // 将菜单名称设置为"关闭飞行路径"
    else                                            // 如果当前是关闭飞行路径
        pCmdUI->SetText("显示飞行路径");                // 将菜单名称设置为"显示飞行路径"
}


/****************************************************************/
/* Function: 按固定高度漫游                                     */
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyStaticheight() {
    if (m_FlayPath.GetSize() <= 0) {                    // 如果飞行路径坐标点数量<=0，即飞行路径为空
        MessageBox("没有输入路径文件", "飞行浏览", MB_ICONWARNING);
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
/* Function: 设置飞行计时器                                     */
/****************************************************************/
void CMy3DSymbolLibNewView::SetFLyTimer() {
    SetTimer(1, m_flyspeed, NULL);                      // m_flyspeed:飞行计时器时间间隔,
}


/****************************************************************/
/* Function: 计时器,飞行频率控制器                              */
/****************************************************************/
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
                m_flypathPtIndex++;                         // 飞行路径当前坐标索引号+1
            } else {
                m_flypathPtIndex = 0;                       // 到了飞行尾,将飞行路径当前坐标索引号重置为0,即从飞行路径起始点开始漫游
            }
            break;
        case 2:  // 模型选中进行红白颜色闪烁显示
            if (wireG == 0) {
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
/* Function: 根据漫游路径相临坐标点计算相机各参数                   */
/****************************************************************/
void CMy3DSymbolLibNewView::GetCameraCorrdinate(double x1, double y1, double z1, double x2, double y2, double z2) {
    // (x1,y1,x1):飞行路径当前点坐标
    // (x2,y2,x2):飞行路径下一点坐标
    if (m_FlyHeightType == GIS_FLY_STATICHEIGHT) {          // 固定高度飞行方式
        if (m_StaticHeight < 85)
            m_StaticHeight = 85;
        m_vLook.x = x2;  // 观察点x坐标
        m_vLook.y = m_StaticHeight;  // 观察点y坐标=y2+m_StaticHeight固定高度值
        m_vLook.z = z2;  // 观察点z坐标
        m_vEyePosition.x = x1;  // 视点x坐标
        m_vEyePosition.y = m_vLook.y;  // 视点y坐标=观察点y坐标
        m_vEyePosition.z = z1;  // 视点z坐标
    } else if (m_FlyHeightType == GIS_FLY_PATHHEIGHT) {  // 按相对高度(即沿路径)漫游时，需计算一个基本高度
        // 沿相对高度漫游
        m_vLook.x = x2;                                     // 观察点x坐标
        m_vLook.y = y2 + m_StaticHeight + 1;                    // 观察点y坐标=y2+m_StaticHeight固定高度值
        m_vLook.z = z2;                                     // 观察点z坐标
        // 求二点之间距离
        float distance = sqrt((x2 - x1) * (x2 - x1) + (z2 - z1) * (z2 - z1));
        // 根据倾角计算高度差
        float dh = distance * tan(m_ViewUpDown * PAI_D180);
        m_vEyePosition.x = x1;                              // 视点x坐标
        m_vEyePosition.y = m_vLook.y + dh;                  // 视点y坐标=观察点y坐标+高差
        m_vEyePosition.z = z1;                              // 视点z坐标
    }
}


/****************************************************************/
/* Function: 按相对高度漫游方式                                 */
/****************************************************************/
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
/* Function: 设置菜单是否设置选中标识"√"                           */
/****************************************************************/
void CMy3DSymbolLibNewView::OnUpdateFlyRoutineheight(CCmdUI* pCmdUI) {
    pCmdUI->Enable(m_PathFlag == TRUE);                  // 根据是否具有有效飞行路径值设置菜单状态
    if (m_FlyHeightType == GIS_FLY_PATHHEIGHT)              // 如果当前是"沿相对高度漫游"方式
        pCmdUI->SetCheck(TRUE);                             // 菜单前设置选中标志"√"
    else
        pCmdUI->SetCheck(FALSE);                                // 否则不设置
}


/****************************************************************/
/* Function: 开始/暂停漫游                                      */
/****************************************************************/
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
/* Function: 根据m_FlyPause值设置菜单ID_FLY_PLAYPAUSE文本           */
/****************************************************************/
void CMy3DSymbolLibNewView::OnUpdateFlyPlaypause(CCmdUI* pCmdUI) {
    pCmdUI->Enable(m_fly_start_pause_Enable == TRUE);
    if (m_FlyPause == TRUE)                     // 如果处于漫游状态
        pCmdUI->SetText("开始漫游");                // 设置菜单ID_FLY_PLAYPAUSE文本
    else                                        // 如果不是暂停漫游,即处于漫游状态
        pCmdUI->SetText("暂停漫游");                // 设置菜单ID_FLY_PLAYPAUSE文本
}


/****************************************************************/
/* Function: 停止漫游                                           */
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyStop() {
    KillTimer(1);                       // 销毁定时器1
    m_flypathPtIndex = 0;               // 飞行路径坐标索引=0
    m_FlyPause = FALSE;                 // 暂停标识为FALSE
    m_far = 10000;                      // 恢复gluPerspective()函数定义平截头体的远剪裁平面的距离
    m_fly_start_pause_Enable = FALSE;   // []
}


/****************************************************************/
/* Function: 单步前进                                           */
/****************************************************************/
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
        m_flypathPtIndex++;                         // 当前行路径坐标索引+1
    }
}


/****************************************************************/
/* Function: 飞行视野扩大                                           */
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyViewEnlarge() {
    m_ViewWideNarrow += 5.0;                        // m_ViewWideNarrow值增加
    OnDraw(GetDC());                                // 刷新三维场景
}


/****************************************************************/
/* Function: 飞行视野减小                                           */
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyViewSmall() {
    m_ViewWideNarrow -= 5.0;                        // m_ViewWideNarrow值减小
    OnDraw(GetDC());                                // 刷新三维场景
}


/****************************************************************/
/* Function: 飞行高度增加                                           */
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyHeightUp() {
    m_StaticHeight += 8;                            // 高度值增加(步长=8,可任意设定)
    OnDraw(GetDC());                                // 刷新三维场景
}


/****************************************************************/
/* Function: 飞行高度降低                                           */
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyHeightDown() {
    m_StaticHeight -= 8;                            // 高度值增加(步长=8,可任意设定)
    OnDraw(GetDC());                                // 刷新三维场景
}


/****************************************************************/
/* Function: 飞行视角上倾(仰视)                                 */
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyViewUp() {
    m_ViewUpDown += 1.0;
    OnDraw(GetDC());                                // 刷新三维场景
}


/****************************************************************/
/* Function: 飞行视角下倾(俯视)                                 */
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyViewDown() {
    m_ViewUpDown -= 1.0;
    OnDraw(GetDC());                                // 刷新三维场景
}


/****************************************************************/
/* Function: 加速                                               */
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlySpeedUp() {
    m_flyspeed -= 2;                                // 飞行时的计时器时间间隔减少
    if (m_flyspeed <= 1)                            // 如果计时器时间间隔<=1,则有
        m_flyspeed = 1;
    SetFLyTimer();                                  // 设置飞行计时器
}


/****************************************************************/
/* Function: 减速                                               */
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlySpeedDown() {
    m_flyspeed += 2;                                // 飞行时的计时器时间间隔增加
    SetFLyTimer();                                  // 设置飞行计时器
}


/****************************************************************/
/* Function: 三维漫游调整热键帮助                                   */
/****************************************************************/
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
/* Function: 初始化显示列表                                     */
/****************************************************************/
void CMy3DSymbolLibNewView::InitList() {
    m_ClockList = glGenLists(1);
    m_SkyList = m_ClockList + 1;                   // 背景天空显示列表
    MakeClockList();                                // 创建时钟指北针显示列表
    m_Rail3DwayList = m_ClockList + 2;              // 线路三维模型显示列表
}


/****************************************************************/
/* Function: 创建时钟指北针显示列表                             */
/****************************************************************/
void CMy3DSymbolLibNewView::MakeClockList() {
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
/* Function: 时钟指北针的绘制                                       */
/****************************************************************/
void CMy3DSymbolLibNewView::DrawClock() {
    glPushAttrib(GL_CURRENT_BIT);                   // 保存现有颜色属性
    glPushMatrix();                                 // 压入矩阵堆栈
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);      // 线绘制方式
    glDisable(GL_TEXTURE_2D);                       // 关闭纹理
    SetClockProjectionNavigate();                   // 设置指北针的投影参数
    glCallList(m_ClockList);                        // 调用指北针时钟的显示列表
    DrawNorthPt();                                  // 绘制指北针
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
    glMatrixMode(GL_PROJECTION);                     // 设置当前矩阵为透视矩阵
    glLoadIdentity();                               // 将当前矩阵置换为单位阵
    glOrtho(0.0f, 1.0, 0.0f, 1.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);                      // 设置当前矩阵为模型矩阵
    glLoadIdentity();                               // 将当前矩阵置换为单位阵
}


/****************************************************************/
/* Function: 绘制指北针                                         */
/****************************************************************/
void CMy3DSymbolLibNewView::DrawNorthPt() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);      // 以填充方式绘制
    glDisable(GL_TEXTURE_2D);                       // 关闭纹理
    float R = 0.5;
    float x1, y1, x2, y2, x3, y3;
    float mPtangle = 25;
    float tempangle;
    float L, L1, L2;
    L1 = 0.3;
    L2 = 0.2;
    x1 = 0.5;
    y1 = 0.5;                                // 时钟圆心点坐标，指北针围绕该点进行指向旋转
    x3 = x1 + L1 * cos((m_NorthPtangle) * PAI_D180);
    y3 = y1 + L1 * sin((m_NorthPtangle) * PAI_D180);
    // 如果指北针指向角位于第1象限
    if (m_NorthPtangle >= 0 && m_NorthPtangle <= 90) {
        tempangle = m_NorthPtangle - mPtangle;
        L = 0.1 / cos(mPtangle * PAI_D180);
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


/****************************************************************/
/* Function: 在指定位置输出文本                                 */
/****************************************************************/
void CMy3DSymbolLibNewView::PrintText(float x, float y, char* string) {
    int32 length;
    length = static_cast<int32>(strlen(string));                  // 字符串长度
    glRasterPos2f(x, y);                            // 定位当前光标
    for (int32 m = 0; m < length; m++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[m]);  // 用位图方式按指定的字体绘制一个字符串
    }
}


/****************************************************************/
/* Function: 根据相机的视点坐标和观察点坐标计算时钟指北针指向角度   */
/****************************************************************/
void CMy3DSymbolLibNewView::GetNorthPtangle() {
    float dx, dz, ar;
    dx = m_vEyePosition.x - m_vLook.x;              // 相机视点与观察点x坐标之差
    dz = m_vEyePosition.z - m_vLook.z;              // 相机视点与观察点z坐标之差
    if (dx == 0) {                                  // 如果dx==0
        if (dz >= 0)                                // 如果dz>=0
            m_NorthPtangle = 90;                    // 指北针初始指向角度=90，指向屏幕里面（Z轴负方向）
        else
            m_NorthPtangle = 270;                   // 指北针初始指向角度=270，指向屏幕外面（Z轴正方向）
    } else {
        if (dx > 0) {
            if (dz > 0) {                           // 第2象限
                ar = fabs(atan(dx / dz));
                m_NorthPtangle = 90 + ar * HDANGLE;  // 指北针初始指向角度
            } else {                                // 第3象限
                ar = fabs(atan(dx / dz));
                m_NorthPtangle = 270 - ar * HDANGLE;  // 指北针初始指向角度
            }
        }
        if (dx < 0) {
            if (dz > 0) {                           // 第1象限
                ar = fabs(atan(dx / dz));
                m_NorthPtangle = 90 - ar * HDANGLE;  // 指北针初始指向角度
            } else {                                // 第4象限
                ar = fabs(atan(dx / dz));
                m_NorthPtangle = 270 + ar * HDANGLE;  // 指北针初始指向角度
            }
        }
    }
}


/****************************************************************/
/* Function: 生成绘制背景天空显示列表                               */
/****************************************************************/
void CMy3DSymbolLibNewView::MakeSkykList() {
    glNewList(m_SkyList , GL_COMPILE);
    CreateSkyBox();
    glEndList();
}


/****************************************************************/
/* Function: 绘制天空背景                                           */
/****************************************************************/
void CMy3DSymbolLibNewView::DrawSky() {
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
    glPushMatrix();
    if (m_bShowbreviary == TRUE) {          // 如果显示导航图
        SetSkyProjectionNavigate();        // 设置导航图的背景天空投影
    }
    glPopMatrix();
    SetSkyProjection();                    // 设置背景天空投影
    glCallList(m_SkyList);
    glPopMatrix();
    glPopAttrib();
}


/****************************************************************/
/* Function: 背景天空投影设置                                       */
/****************************************************************/
void CMy3DSymbolLibNewView::SetSkyProjection() {
    glViewport(0 ,  0 ,  WinViewX ,  WinViewY);             // 设置视口大小和位置
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0 + m_ViewWideNarrow , static_cast<float>(WinViewX) / static_cast<float>(WinViewY) , m_near , m_far);
    glMatrixMode(GL_MODELVIEW);                             // 定义矩阵为模型模型矩阵
    glLoadIdentity();                                       // 将当前矩阵置换为单位矩阵
    SetCamra();
}


/****************************************************************/
/* Function: 背景天空导航图投影设置                             */
/****************************************************************/
void CMy3DSymbolLibNewView::SetSkyProjectionNavigate() {
    glClearDepth(1.0f);                             // 设置初始化深度缓存值
    glEnable(GL_DEPTH_TEST);                        // 启用深度测试
    glDepthFunc(GL_LESS);                           // 在调用glEnable(GL_DEPTH_TEST); 开启这个功能以后，当深度变化小于当前深度值时，更新深度值。
    glViewport(WinViewX * 5 / 6 ,  WinViewY * 5 / 6 , WinViewX / 6 ,  WinViewY / 6);  // 设置视口大小
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0 + m_ViewWideNarrow , static_cast<float>(WinViewX) / static_cast<float>(WinViewY) , m_near , m_far);
    // 设置正射投影视景体
    glMatrixMode(GL_MODELVIEW);                         // 定义矩阵为模型模型矩阵
    glLoadIdentity();                                   // 将当前矩阵置换为单位矩阵
    glClearColor(0.53, 0.81, 0.92, 0.0);                // 设置刷新背景色SkyBlue: 135,206,235
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // 刷新背景
    glLoadIdentity();                                   // 重置当前的模型观察矩阵
    SetCamra();
}


/****************************************************************/
/* Function: 导入3DS模型 设置参数                                   */
/****************************************************************/
void CMy3DSymbolLibNewView::On3dsModelLoad() {
    // TODO(jason): 在此添加命令处理程序代码
    CString tt, stt;
    FILE* fp;
    CString modelFileFormat = ".3DS";
    PModelParamStruct p3d;
    if (m_i3DModelNum < MODEL_NUM_MAX) {
        CDialogModelList dlg1;
        dlg1.m_Dir = m_AllDataPath + "\\" + m_3DModelFolder;
        dlg1.m_format = ".bmp";
        dlg1.m_type = "3DS";
        CString selectItem;
        if (dlg1.DoModal() == IDOK) {
            selectItem = dlg1.m_selectItem;
            m_3DModelPath = dlg1.m_Dir + "\\" + selectItem + modelFileFormat;
        } else {
            return;
        }
        if ((fp = fopen(m_3DModelPath, "r")) == NULL) {
            MessageBox("3D模型文件不存在!", "初始化3D模型", MB_ICONINFORMATION + MB_OK);
            exit(-1);
        }
        p3d = new CModelParamStruct;
        CModelParamStruct a = {0};
        *p3d = a;
        p3d->modelID = m_i3DModelNum;
        p3d->isDeleted = false;
        p3d->modelPath = m_3DModelPath;
        p3d->m_3DS_Mode_Texture_PATH_NAME = dlg1.m_Dir + "\\" + selectItem + ".bmp";
        p3d->posX = 389;
        p3d->posZ = -389;
        p3d->scale = 1;
        ModelParam dlg;
        dlg.m_strTitle = "3D模型参数初始化";
        if (m_QueryType == QUERY_COORDINATE && IsSearchPoint) {  // 当前为查询模式,并且已经查询了
            p3d->posX = pt1[0];
            p3d->posZ = pt1[2];
        }
        PModelParamStructToModelParamDlg(dlg, p3d);
        if (dlg.DoModal() == IDOK) {
            ModelParamDlgToPModelParamStruct(dlg, p3d);
            Load3DModel(p3d, MODEL_NEW);
            m_i3DModelNum++;
        }
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
    glTranslatef(model->posX, y, model->posZ);                  // 模型定位
    glRotatef(model->rotY, 0.0, 1.0, 0.0);                  // 模型旋转
    glRotatef(model->rotX, 1.0, 0.0, 0.0);                  // 模型旋转
    glRotatef(model->rotZ, 0.0, 0.0, 1.0);                  // 模型旋转
    m_3ds->Show3ds(model->modelID, 0, 0.0f, 0, model->scale);  // 显示3ds模型
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
/* Function: 3d模型选择以及参数设置                             */
/****************************************************************/
void CMy3DSymbolLibNewView::On3dsModelSelectSet() {
    // TODO(jason): 在此添加命令处理程序代码
    bIsSelect3DModel = !bIsSelect3DModel;
    if (bIsSelect3DModel) {
        m_OperateType = SELECT;
        m_mouseShape = MOUSE_SHAPE_SLECT;
        m_QueryType = -1;
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
/* Function: 移动模型,从左键按下到左键弹起的距离                    */
/****************************************************************/
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
    bIsMouseMove3DModel = !bIsMouseMove3DModel;
    if (bIsMouseMove3DModel) {
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
/* Function: 在坐标转换时判断鼠标是否落入3D模型空间范围内           */
/****************************************************************/
void CMy3DSymbolLibNewView::JudgeModelSelected(PCordinate ppt) {
    // 获取模型中三维点极值
    int32 minx, maxx, minz, maxz;
    // 遍历所有的3D模型,判断是否在范围内
    for (int32 j = 0; j < m_i3DModelNum; j++) {
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
/* Function: 导入景观树 设置参数                                    */
/****************************************************************/
void CMy3DSymbolLibNewView::OnTreeLoad() {
    // TODO(jason): 在此添加命令处理程序代码
    CString tt, stt;
    FILE* fp;
    CString treeTexPath;
    CString treeFileFormat = ".BMP";
    if (m_iTreeModelNum < 50) {
        CDialogModelList dlg1;
        dlg1.m_Dir = m_AllDataPath + "\\" + m_TreeModelFolder;
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
    } else {
        MessageBox("树木的大小超出了50!");
    }
}


/*************************************************************************/
/* Function: 树的贴图需要透明显示，透明显示要求树的图片应该是16位色的BMP位图     */
/*************************************************************************/
void CMy3DSymbolLibNewView::LoadT16(char* filename, GLuint& texture) {  // NOLINT
    glGenTextures(1, &texture);                                         // 获取1个未使用的贴图名称
    glBindTexture(GL_TEXTURE_2D, texture);                              // 选择要绑定的贴图（纹理）
    BITMAPINFOHEADER bitHeader;                                         // 定义位图结构
    unsigned char* buffer;                                              // 定义位图指针
    buffer = LoadBitmapFileWithAlpha(filename, &bitHeader);             // 调入位图
    gluBuild2DMipmaps(GL_TEXTURE_2D,                                     // 创建一个2D贴图（纹理）
                      4,                                                              // 使用3种颜色（RGB）+颜色深度
                      bitHeader.biWidth,                                              // 图像宽
                      bitHeader.biHeight,                                             // 图像高
                      GL_RGBA,                                                        // 红绿蓝顺序
                      GL_UNSIGNED_BYTE,                                               // 图像的数据类型是字节
                      buffer                                                          // 指定贴图（纹理）数据
                     );                                                              // 创建贴图（纹理）
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);                   // 缩小滤波
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);                   // 放大滤波
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);    // 双线性滤波
    free(buffer);                                                                       // 释放位图数据
}


/********************************************************************/
/* Function: 显示特殊平面树，场景旋转时树也跟着旋转，始终是正面对着用户 */
/********************************************************************/
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
/* Function: 导入城市标识,行政点,咖啡店,厕所,服务区等               */
/****************************************************************/
void CMy3DSymbolLibNewView::OnCitySymbolLoad() {
    CString tt, stt;
    FILE* fp;
    CString citySymbolTexPath;
    CString citySymbolFileFormat = ".png";
    if (m_iCitySymbolModelNum < 50) {
        CDialogModelList dlg1;
        dlg1.m_Dir = m_AllDataPath + "\\" + m_CitySymbolFolder;
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
    }
}


/****************************************************************/
/* Function: 显示普通城市符号,不随视线转化而转换角度                */
/****************************************************************/
void CMy3DSymbolLibNewView::ShowCitySymbol0(int32 i) {
    float x, y, z;
    x = m_CitySymbolModel.GetAt(i)->xPos;
    z = m_CitySymbolModel.GetAt(i)->zPos;
    float h = 0.5;
    glPushMatrix();
    y = GetHeight(x, z) + m_CitySymbolModel.GetAt(i)->hPos + h;
    glTranslatef(x, y, z);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0);
    glBindTexture(GL_TEXTURE_2D, g_citySymbolTex[i]);
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
    glDisable(GL_ALPHA);
    glDisable(GL_BLEND);
    glPopMatrix();
}


/****************************************************************/
/* Function:显示城市符号                                            */
/****************************************************************/
void CMy3DSymbolLibNewView::ShowCitySymbol(int32 i) {
    float x, y, z;
    x = m_CitySymbolModel.GetAt(i)->xPos;
    z = m_CitySymbolModel.GetAt(i)->zPos;
    float h = 3.2;
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
/* Function: 透明PNG 纹理加载                                       */
/****************************************************************/
void CMy3DSymbolLibNewView::LoadPNG(const char* fileName, GLuint& texture) {  // NOLINT
    glGenTextures(1, &texture);                     // 获取1个未使用的贴图名称
    glBindTexture(GL_TEXTURE_2D, texture);          // 选择要绑定的贴图（纹理）
    BITMAP bm;
    CImage img;                                     // 需要头文件atlimage.h
    HRESULT hr = img.Load(fileName);
    if (!SUCCEEDED(hr)) {                            // 文件加载失败
        MessageBox(NULL, "文件加载失败", MB_OK);
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
/* Function: 导入天气预报图片                                   */
/****************************************************************/
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
            exit(-1);
        }
        char cc[256];

        // sprintf(cc, weatherSymbolTexPath);
        _snprintf_s(cc, sizeof(cc), sizeof(cc)-1, weatherSymbolTexPath);

        LoadT8(cc, g_weatherTex);
        bIsWeatherLoad = true;
    }
}


/****************************************************************/
/* Function: 显示天气图标                                           */
/****************************************************************/
void CMy3DSymbolLibNewView::ShowWeather() {
    glPushAttrib(GL_CURRENT_BIT);                   // 保存现有颜色属性
    glPushMatrix();                                 // 压入矩阵堆栈
    glEnable(GL_TEXTURE_2D);
    float wh = 50;                                  // 设置时钟的高度
    glViewport(WinViewX * 5 / 6 - wh,  WinViewY - wh , wh ,  wh);       // 设置视口位置和大小
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
    glViewport(0 ,  0 ,  WinViewX ,  WinViewY);     // 设置视口大小和位置
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0 + m_ViewWideNarrow , static_cast<float>(WinViewX) / static_cast<float>(WinViewY) , m_near , m_far);
    glMatrixMode(GL_MODELVIEW);                     // 定义矩阵为模型模型矩阵
    glLoadIdentity();                               // 将当前矩阵置换为单位矩阵
}


/****************************************************************/
/* Function: 参数设置对话框内变量直接全部赋值给结构体               */
/****************************************************************/
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
/* Function: 导入3D立体景观树，实质上是将平面树纹理绕Y轴旋转90度实现二次贴纹理  */
/****************************************************************************/
void CMy3DSymbolLibNewView::On3dTreeLoad() {
    CString tt, stt;
    FILE* fp;
    CString treeTexPath;
    CString treeFileFormat = ".BMP";
    if (m_i3DTreeModelNum < 50) {
        CDialogModelList dlg1;
        dlg1.m_Dir = m_AllDataPath + "\\" + m_TreeModelFolder;
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
    } else {
        MessageBox("树木的大小超出了50!");
    }
}


/****************************************************************************/
/* Function: 自定义消息响应,非模式对话框(非3DS模型参数对话框)                   */
/****************************************************************************/
LRESULT CMy3DSymbolLibNewView::OnGoodBye(WPARAM wParam, LPARAM lParam) {
    // 确定
    if (wParam == IDOK) {
        if (paramSet_modeless_dlg->m_modeParam.type == "3dtree") {
            C3DModelParamSetTOPModelStruct(paramSet_modeless_dlg, p3dtree);
            m_3DTreeModel.Add(p3dtree);
            char cc[256];

            // sprintf(cc, p3dtree->strModelPath);
            _snprintf_s(cc, sizeof(cc), sizeof(cc)-1, p3dtree->strModelPath);

            LoadT16(cc, g_cactus3DTree[m_i3DTreeModelNum]);
            m_i3DTreeModelNum ++;
            paramSet_modeless_dlg->DestroyWindow();
            m_isSetXYByMouse = 0;
        } else if (paramSet_modeless_dlg->m_modeParam.type == "tree") {
            C3DModelParamSetTOPModelStruct(paramSet_modeless_dlg, ptree);
            m_TreeModel.Add(ptree);
            char cc[256];

            // sprintf(cc, ptree->strModelPath);
            _snprintf_s(cc, sizeof(cc), sizeof(cc)-1, ptree->strModelPath);

            LoadT16(cc, g_cactus[m_iTreeModelNum]);
            m_iTreeModelNum ++;
            paramSet_modeless_dlg->DestroyWindow();
            m_isSetXYByMouse = 0;
        } else if (paramSet_modeless_dlg->m_modeParam.type == "CitySymbol") {
            C3DModelParamSetTOPModelStruct(paramSet_modeless_dlg, pCitySymbol);
            m_CitySymbolModel.Add(pCitySymbol);
            char cc[256];

            // sprintf(cc, pCitySymbol->strModelPath);
            _snprintf_s(cc, sizeof(cc), sizeof(cc)-1, pCitySymbol->strModelPath);

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
/* Function: 显示3D立体景观树                                                   */
/****************************************************************************/
void CMy3DSymbolLibNewView::Show3DTree(int32 i) {
    float x, y, z;
    x = m_3DTreeModel.GetAt(i)->xPos;
    z = m_3DTreeModel.GetAt(i)->zPos;
    float h = 3;
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
/* Function: 滚轮缩放,当选中某个模型时就对模型进行缩放，否则是缩放整个视景窗口  */
/****************************************************************************/
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
    CVector3 rayStart,                  // 射线起点
    CVector3 rayDir,                    // 射线长度和方向
    CVector3 returnNormal,              // 可选的，相交点处法向量
    CVector3 min,
    CVector3 max
) {
    // 如果未相交则返回这个大数
    /*final*/const float kNoIntersection = 1e30f;
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
        Normalize(returnNormal);
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
    CVector3 rayStart,                  // 射线起点
    CVector3 rayDir,                    // 射线长度和方向
    CVector3 returnNormal               // 可选的，相交点处法向量
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
/* Function: 加载工程文件                                                       */
/****************************************************************************/
void CMy3DSymbolLibNewView::loadSceneFile(CString filename) {
    CStdioFile file;
    BOOL b_open = file.Open(filename, CStdioFile::modeRead);
    if ((!b_open) || (file == NULL)) {
        MessageBox(_T("工程不存在!\n") + filename, _T("打开工程文件"), MB_ICONWARNING + MB_OK);
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
        file.ReadString(m_TerrainFolder);
        // Tex Sand512.BMP
        file.ReadString(m_TerrainTextureFolder);
        int32 length = m_TerrainTextureFolder.GetLength();
        int32 i = m_TerrainTextureFolder.Find(" ");
        m_TerrainTexture = m_TerrainTextureFolder.Right(length - i - 1);
        m_TerrainTextureFolder = m_TerrainTextureFolder.Left(i);
        // Contour Terrain1.bmp
        file.ReadString(m_TerrainContourFolder);
        length = m_TerrainContourFolder.GetLength();
        i = m_TerrainContourFolder.Find(" ");
        m_TerrainContour = m_TerrainContourFolder.Right(length - i - 1);
        m_TerrainContourFolder = m_TerrainContourFolder.Left(i);
        // ----------------------------------------------------
        // 天空盒数据SkyBox
        file.ReadString(m_SkyBoxFolder);
        // default TOP.BMP LEFT.BMP BACK.BMP RIGHT.BMP FRONT.BMP
        file.ReadString(m_SkyBoxKindFolder);
        int32 curPos = 0;
        int32 tokenID = 0;
        CString temp = m_SkyBoxKindFolder.Tokenize(" ", curPos);
        CString Skyfolder = temp;
        while (temp != _T("")) {
            tokenID += 1;
            temp = m_SkyBoxKindFolder.Tokenize(" ", curPos);
            if (tokenID == 1)
                m_SkyBoxTP = temp;
            else if (tokenID == 2)
                m_SkyBoxLT = temp;
            else if (tokenID == 3)
                m_SkyBoxBK = temp;
            else if (tokenID == 4)
                m_SkyBoxRT = temp;
            else if (tokenID == 5)
                m_SkyBoxFR = temp;
        };
        m_SkyBoxKindFolder = Skyfolder;
        // ----------------------------------------------------
        // 天气数据
        file.ReadString(m_WeatherFolder);
        file.ReadString(m_WeatherTex);
        CString weatherSymbolTexPath = m_AllDataPath + "\\" + m_WeatherFolder + "\\" + m_WeatherTex;
        char cc[256];
        _snprintf_s(cc, sizeof(cc), sizeof(cc)-1, weatherSymbolTexPath);
        LoadT8(cc, g_weatherTex);
        bIsWeatherLoad = true;
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
        // 加载线文件
        if (m_LineSymbolFile != "0") {
            CString line_Path = /*m_AllDataPath + "\\" + m_SceneConfig + "\\" + */m_LineSymbolFile;
            LoadLineSymbolFile(line_Path);
            exist_line_flag = TRUE;
        }
        // 加载区文件  必须等初始化地形数据之后  (见下方)
        /**************************************/
        /* 加载线路纹理资源                   */
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
        /*
        // 线路
        CString strLine;
        CString strJDNumber;
        int32 intJDNumber;
        CString strJDPositions;

        file.ReadString(strLine);
        file.ReadString(strJDNumber);
        intJDNumber = atoi(strJDNumber);

        PCordinate tmpJD = new Cordinate;
        PCurve_R_L0_Struct tmpCurveRL0 = new Curve_R_L0_Struct;

        file.ReadString(strJDPositions);

        {
            curPos = 0; tokenID = 0;
            CString temp = "0.000";
            while (temp != _T(""))
            {
                tokenID += 1;
                temp = strJDPositions.Tokenize(" ", curPos);

                if(temp != _T(""))
                {
                    if(tokenID%5 == 1)
                    tmpJD->x = atof(temp);
                    else if(tokenID%5 == 2)
                        tmpJD->y = atof(temp);
                    else if(tokenID%5 == 3)
                        tmpJD->z = atof(temp);
                    else if(tokenID%5 == 4)
                        tmpCurveRL0->curve_R = atoi(temp);
                    else if(tokenID%5 == 0)
                    {
                        tmpCurveRL0->curve_L0 = atoi(temp);
                        fun(tmpJD, tmpCurveRL0);
                        tmpJD = new Cordinate;
                        tmpCurveRL0 = new Curve_R_L0_Struct;
                    }
                }
            }
        }

        int32 s1 = myDesingScheme.PtS_JD.GetSize();
        float a;
        for(int32 i=0;i<s1;++i)
        {
            a = myDesingScheme.PtS_JD[i]->x;
        }
        int32 s2 = myDesingScheme.JDCurveElements.GetSize();

        file.Close();
        */
        // ----------------------------------------------------
        // 开始场景渲染 配置天空盒
        CString skyBoxPathPre = m_AllDataPath + "\\" + m_SkyBoxFolder + "\\" + m_SkyBoxKindFolder + "\\";
        g_texSkyBoxFlieNameTP = skyBoxPathPre + m_SkyBoxTP;
        g_texSkyBoxFlieNameLF = skyBoxPathPre + m_SkyBoxLT;
        g_texSkyBoxFlieNameBK = skyBoxPathPre + m_SkyBoxBK;
        g_texSkyBoxFlieNameRT = skyBoxPathPre + m_SkyBoxRT;
        g_texSkyBoxFlieNameFR = skyBoxPathPre + m_SkyBoxFR;
        LoadSkyBoxTex(g_texSkyBoxFlieNameTP, g_texSkyBoxFlieNameLF, g_texSkyBoxFlieNameBK,
                      g_texSkyBoxFlieNameRT, g_texSkyBoxFlieNameFR);
        // 配置地形
        terrainTexFileName = m_AllDataPath + "\\" + m_TerrainFolder + "\\" + m_TerrainTextureFolder + "\\" + m_TerrainTexture;
        terrainContourFileName = m_AllDataPath + "\\" + m_TerrainFolder + "\\" + m_TerrainContourFolder + "\\" + m_TerrainContour;
        LoadTerrainTex(terrainTexFileName, terrainContourFileName);
        OnMenuBuild3dlinemodle();
        // 加载区文件
        if (m_AreaSymbolFile != "0") {
            CString area_Path = /*m_AllDataPath + "\\" + m_SceneConfig + "\\" + */m_AreaSymbolFile;
            LoadAreaSymbolFile(area_Path);
            exist_area_flag = TRUE;
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
        file.ReadString(m_3DModelFolder);
        CString m_3DModelNumStr;
        file.ReadString(m_3DModelNumStr);
        m_i3DModelNum = atoi(m_3DModelNumStr);
        for (int32 i = 0; i < m_i3DModelNum; ++i) {
            file.ReadString(m_3DModelPath);
            int32 curPos = 0;
            int32 tokenID = 0;
            CString temp = m_3DModelPath.Tokenize(" ", curPos);
            CString model3DFolder = temp;
            while (temp != _T("")) {
                tokenID += 1;
                temp = m_3DModelPath.Tokenize(" ", curPos);
                if (tokenID == 1)
                    m_3DModelPosX = atof(temp);
                else if (tokenID == 2)
                    m_3DModelPosY = atof(temp);
                else if (tokenID == 3)
                    m_3DModelPosZ = atof(temp);
                else if (tokenID == 4)
                    m_3DModelRotX = atof(temp);
                else if (tokenID == 5)
                    m_3DModelRotY = atof(temp);
                else if (tokenID == 6)
                    m_3DModelRotZ = atof(temp);
                else if (tokenID == 7)
                    m_3DModelScale = atof(temp);
            };
            m_3DModelPath = model3DFolder;
            PModelParamStruct p3d = new CModelParamStruct;
            p3d->modelPath = m_AllDataPath + "\\" + m_3DModelFolder + "\\" + m_3DModelPath;
            p3d->modelID = i;
            p3d->modelSelected = false;
            p3d->m_3DS_Mode_Texture_PATH_NAME = m_AllDataPath + "\\" + m_3DModelFolder + "\\" + m_3DModelPath.Left(m_3DModelPath.Find('.')) + ".bmp";
            p3d->isDeleted = false;
            p3d->posX = m_3DModelPosX;
            p3d->posY = m_3DModelPosY;
            p3d->posZ = m_3DModelPosZ;
            p3d->rotX = m_3DModelRotX;
            p3d->rotY = m_3DModelRotY;
            p3d->rotZ = m_3DModelRotZ;
            p3d->scale = m_3DModelScale;
            Load3DModel(p3d, MODEL_NEW);
        }
        // ----------------------------------------------------
        // 城市标识数据
        /*City Symbol
        2
        25 398.469 83.992 393.427
        1 386.085 83.993 387.031*/
        file.ReadString(m_CitySymbolFolder);
        CString m_CitySymbolNumStr;
        file.ReadString(m_CitySymbolNumStr);
        m_iCitySymbolModelNum = atoi(m_CitySymbolNumStr);
        for (int32 i = 0; i < m_iCitySymbolModelNum; ++i) {
            file.ReadString(m_CitySymbolTex);
            int32 curPos = 0;
            int32 tokenID = 0;
            curPos = 0;
            tokenID = 0;
            CString temp = m_CitySymbolTex.Tokenize(" ", curPos);
            CString citySymbolTex = temp;
            while (temp != _T("")) {
                tokenID += 1;
                temp = m_CitySymbolTex.Tokenize(" ", curPos);
                if (tokenID == 1)
                    m_CitySymbolPosX = atof(temp);
                else if (tokenID == 2)
                    m_CitySymbolPosY = atof(temp);
                else if (tokenID == 3)
                    m_CitySymbolPosZ = atof(temp);
            };
            m_CitySymbolTex = citySymbolTex;
            PModelStruct p3d = new CModelStruct;
            p3d->strModelPath = m_AllDataPath + "\\" + m_CitySymbolFolder + "\\" + m_CitySymbolTex;
            p3d->iModelNum = i;
            p3d->xPos = m_CitySymbolPosX;
            p3d->hPos = m_CitySymbolPosY;
            p3d->zPos = m_CitySymbolPosZ;
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
            _snprintf_s(cc, sizeof(cc), sizeof(cc)-1, p3d->strModelPath);

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
        file.ReadString(m_TreeModelFolder);
        CString m_TreeModelNumStr;
        file.ReadString(m_TreeModelNumStr);
        m_iTreeModelNum = atoi(m_TreeModelNumStr);
        for (int32 i = 0; i < m_iTreeModelNum; ++i) {
            file.ReadString(m_TreeModelTex);
            int32 curPos = 0;
            int32 tokenID = 0;
            curPos = 0;
            tokenID = 0;
            CString temp = m_TreeModelTex.Tokenize(" ", curPos);
            CString treeModelTex = temp;
            while (temp != _T("")) {
                tokenID += 1;
                temp = m_TreeModelTex.Tokenize(" ", curPos);
                if (tokenID == 1)
                    m_TreeModelPosX = atof(temp);
                else if (tokenID == 2)
                    m_TreeModelPosY = atof(temp);
                else if (tokenID == 3)
                    m_TreeModelPosZ = atof(temp);
            };
            m_TreeModelTex = treeModelTex;
            PModelStruct p3d = new CModelStruct;
            p3d->strModelPath = m_AllDataPath + "\\" + m_TreeModelFolder + "\\" + m_TreeModelTex;
            p3d->iModelNum = i;
            p3d->xPos = m_TreeModelPosX;
            p3d->hPos = m_TreeModelPosY;
            p3d->zPos = m_TreeModelPosZ;
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
            _snprintf_s(cc, sizeof(cc), sizeof(cc)-1, p3d->strModelPath);

            LoadT16(cc, g_cactus[p3d->iModelNum]);
        }
        // ----------------------------------------------------
        // 3D Tree
        file.ReadString(m_TreeModelNumStr);
        m_i3DTreeModelNum = atoi(m_TreeModelNumStr);
        for (int32 i = 0; i < m_i3DTreeModelNum; ++i) {
            file.ReadString(m_TreeModelTex);
            int32 curPos = 0;
            int32 tokenID = 0;
            curPos = 0;
            tokenID = 0;
            CString temp = m_TreeModelTex.Tokenize(" ", curPos);
            CString treeModelTex = temp;
            while (temp != _T("")) {
                tokenID += 1;
                temp = m_TreeModelTex.Tokenize(" ", curPos);
                if (tokenID == 1)
                    m_TreeModelPosX = atof(temp);
                else if (tokenID == 2)
                    m_TreeModelPosY = atof(temp);
                else if (tokenID == 3)
                    m_TreeModelPosZ = atof(temp);
            };
            m_TreeModelTex = treeModelTex;
            PModelStruct p3d = new CModelStruct;
            p3d->strModelPath = m_AllDataPath + "\\" + m_TreeModelFolder + "\\" + m_TreeModelTex;
            p3d->iModelNum = i;
            p3d->xPos = m_TreeModelPosX;
            p3d->hPos = m_TreeModelPosY;
            p3d->zPos = m_TreeModelPosZ;
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
            _snprintf_s(cc, sizeof(cc), sizeof(cc)-1, p3d->strModelPath);

            LoadT16(cc, g_cactus3DTree[p3d->iModelNum]);
        }
    }
    file.Close();
}
// 加载线文件(.ln)
void CMy3DSymbolLibNewView::LoadLineSymbolFile(CString filename) {
}
// 加载区文件(.gsf)
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
        // 点文件首部
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
                    tmp_area4.pt1._x = atof(temp);
                else if (tokenID == 2)
                    tmp_area4.pt1._y = atof(temp);
                else if (tokenID == 3)
                    tmp_area4.pt1._z = atof(temp);
                // pt2
                else if (tokenID == 4)
                    tmp_area4.pt2._x = atof(temp);
                else if (tokenID == 5)
                    tmp_area4.pt2._y = atof(temp);
                else if (tokenID == 6)
                    tmp_area4.pt2._z = atof(temp);
                // pt3
                else if (tokenID == 7)
                    tmp_area4.pt3._x = atof(temp);
                else if (tokenID == 8)
                    tmp_area4.pt3._y = atof(temp);
                else if (tokenID == 9)
                    tmp_area4.pt3._z = atof(temp);
                // pt4
                else if (tokenID == 10)
                    tmp_area4.pt4._x = atof(temp);
                else if (tokenID == 11)
                    tmp_area4.pt4._y = atof(temp);
                else if (tokenID == 12)
                    tmp_area4.pt4._z = atof(temp);
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
/* Function: 初始阶段导入场景文件                                               */
/****************************************************************************/
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
/* Function: 导入天空盒纹理                                                 */
/****************************************************************************/
void CMy3DSymbolLibNewView::LoadSkyBoxTex(CString skyTP, CString skyLF, CString skyBK, CString skyRT, CString skyFR) {
    char cc[256];
    // sprintf(cc, skyTP);
    _snprintf_s(cc, sizeof(cc), sizeof(cc)-1, skyTP);
    LoadT8(cc, g_texSkyBox[TP]);
    // sprintf(cc, skyLF);
    _snprintf_s(cc, sizeof(cc), sizeof(cc)-1, skyLF);
    LoadT8(cc, g_texSkyBox[LF]);
    // sprintf(cc, skyBK);
    _snprintf_s(cc, sizeof(cc), sizeof(cc)-1, skyBK);
    LoadT8(cc, g_texSkyBox[BK]);
    // sprintf(cc, skyRT);
    _snprintf_s(cc, sizeof(cc), sizeof(cc)-1, skyRT);
    LoadT8(cc, g_texSkyBox[RT]);
    // sprintf(cc, skyFR);
    _snprintf_s(cc, sizeof(cc), sizeof(cc)-1, skyFR);
    LoadT8(cc, g_texSkyBox[FR]);
    MakeSkykList();
    iSkyBoxLoaded = true;
}


/****************************************************************************/
/* Function: 导入地形纹理                                                       */
/****************************************************************************/
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




/****************************************************************************/
/* Function: 加载3DS模型                                                        */
/****************************************************************************/
void CMy3DSymbolLibNewView::Load3DModel(PModelParamStruct p3d, int32 iLoadModelType) {
    if (iLoadModelType == MODEL_NEW) {
        m_3DModel.Add(p3d);
    }
    char _3DSFile[256];
    // sprintf(_3DSFile, p3d->modelPath);  // "...\\3DModel\\XXX.3DS"
    _snprintf_s(_3DSFile, sizeof(_3DSFile), sizeof(_3DSFile)-1, p3d->modelPath);
    // [ADD]
    char _3DSTextureFile[256];
    // sprintf(_3DSTextureFile, p3d->m_3DS_Mode_Texture_PATH_NAME);
    _snprintf_s(_3DSTextureFile, sizeof(_3DSTextureFile), sizeof(_3DSTextureFile)-1, p3d->m_3DS_Mode_Texture_PATH_NAME);

    m_3ds->Init(_3DSFile, p3d->modelID, _3DSTextureFile);   // 调用模型调入函数
    t3DBox t3dBox;
    t3dBox.l = g_3DModel[p3d->modelID].t3DModelBox.l * p3d->scale;
    t3dBox.w = g_3DModel[p3d->modelID].t3DModelBox.w * p3d->scale;
    t3dBox.h = g_3DModel[p3d->modelID].t3DModelBox.h * p3d->scale;
    // 解决load3dsmodel时缩放比例问题
    if (p3d->scale < 0.99) {
        return;
    }
    float maxtemp = (t3dBox.l > t3dBox.w) ? t3dBox.l : t3dBox.w;
    float max = (maxtemp > t3dBox.h) ? maxtemp : t3dBox.h;
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


/****************************************************************************/
/* Function: 当前场景另存为                                                 */
/****************************************************************************/
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
        _snprintf_s(FileName, sizeof(FileName), sizeof(FileName)-1, "%s", NeededFile);

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
        return FALSE;
    } else {
        /************************************************************************/
        /*   场景配置数据                                                           */
        /************************************************************************/
        file.WriteString(m_SceneConfig + "\n");
        /************************************************************************/
        /*   地形数据 Terrain                                                   */
        /************************************************************************/
        file.WriteString(m_TerrainFolder + "\n");
        //    Tex Sand512.BMP
        file.WriteString(m_TerrainTextureFolder + " " + m_TerrainTexture + "\n");
        //    Contour Terrain1.bmp
        file.WriteString(m_TerrainContourFolder + " " + m_TerrainContour + "\n");
        /************************************************************************/
        /*   天空盒数据 SkyBox                                                  */
        /************************************************************************/
        file.WriteString(m_SkyBoxFolder + "\n");
        //    0缺省 TOP.BMP LEFT.BMP BACK.BMP RIGHT.BMP FRONT.BMP
        file.WriteString(m_SkyBoxKindFolder + " " + m_SkyBoxTP + " " + m_SkyBoxLT + " "\
                         + m_SkyBoxBK + " " + m_SkyBoxRT + " " + m_SkyBoxFR + "\n");
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
/* Function: 保存点、线、面文件                                             */
/****************************************************************************/
// 保存点文件
int32 CMy3DSymbolLibNewView::savePointSymbolFile(CString filename) {
    CStdioFile file;
    file.Open(filename, CStdioFile::modeCreate | CStdioFile::modeWrite);
    if (file == NULL) {
        MessageBox("点文件不存在!", "保存点文件", MB_ICONINFORMATION + MB_OK);
        return FALSE;
    } else {
        file.WriteString("POINT\n");
        /************************************************************************/
        /*   3DS 模型数据 3DModel                                               */
        /************************************************************************/
        file.WriteString(m_3DModelFolder + "\n");
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
        file.WriteString(m_CitySymbolFolder + "\n");
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
        file.WriteString(m_TreeModelFolder + "\n");
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
    return 0;
}
// 保存区文件
int32 CMy3DSymbolLibNewView::saveAreaSymbolFile(CString filename) {
    CStdioFile file;
    file.Open(filename, CStdioFile::modeCreate | CStdioFile::modeWrite);
    if (file == NULL) {
        MessageBox("面文件不存在!", "保存面文件", MB_ICONINFORMATION + MB_OK);
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
                                 m_Area4_Array[i]->pt1._x, m_Area4_Array[i]->pt1._y, m_Area4_Array[i]->pt1._z,
                                 m_Area4_Array[i]->pt2._x, m_Area4_Array[i]->pt2._y, m_Area4_Array[i]->pt2._z,
                                 m_Area4_Array[i]->pt3._x, m_Area4_Array[i]->pt3._y, m_Area4_Array[i]->pt3._z,
                                 m_Area4_Array[i]->pt4._x, m_Area4_Array[i]->pt4._y, m_Area4_Array[i]->pt4._z,
                                 m_Area4_Array[i]->area_texture
                                );
                file.WriteString(point_str);
            }
        }
        file.Close();
    }
    return 0;
}


/****************************************************************************/
/* Function: 选中模型之后右键弹出菜单中进行鼠标移动模型操作                     */
/****************************************************************************/
void CMy3DSymbolLibNewView::OnModelMove() {
    m_OperateType = MOVE;
}


/****************************************************************************/
/* Function: 编辑模型参数,例如模型纹理路径,大小,方向,缩放比例                   */
/****************************************************************************/
void CMy3DSymbolLibNewView::OnModelParam() {
    ModelParam dlg;
    dlg.modelFolder = m_AllDataPath + "\\" + m_3DModelFolder + "\\";
    PModelParamStructToModelParamDlg(dlg, m_3DModel.GetAt(m_selectedModelID));
    if (dlg.DoModal()) {
        ModelParamDlgToPModelParamStruct(dlg, m_3DModel.GetAt(m_selectedModelID));
    }
}


/****************************************************************************/
/* Function: 参数设置对话框内变量直接全部赋值给结构体                           */
/****************************************************************************/
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


/****************************************************************************/
/* Function: 参数传给对话框                                                 */
/****************************************************************************/
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


/****************************************************************************/
/* Function: 缩放选中模型                                                       */
/****************************************************************************/
void CMy3DSymbolLibNewView::OnModelScale() {
    m_OperateType = SCALE;
}

/**************************************/
/* Function: 配置符号列表                 */
/**************************************/
void CMy3DSymbolLibNewView::OnConfigureSymbolList() {
    // TODO(jason): 在此添加命令处理程序代码
    ModelListConfigureDialog mlcDlg;;
    if (mlcDlg.DoModal() == IDOK) {
        // null
    }
}

/**************************************/
/* Function: 系统设置                 */
/**************************************/
void CMy3DSymbolLibNewView::OnSystemSetting() {
    // TODO(jason): 在此添加命令处理程序代码
    CSystemSetting sysSetDlg;
    if (sysSetDlg.DoModal() == IDOK) {
        // null
    }
}

/**************************************/
/* Function: 关闭当前场景                 */
/**************************************/
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
/* Function: 清除所有线路数据             */
/**************************************/
void CMy3DSymbolLibNewView::clearLinesData() {
    // 交点
    myDesingScheme.PtS_JD.RemoveAll();
    // 铁路中线
    myDesingScheme.PtS_3DLineZX.RemoveAll();
    // 路肩
    myDesingScheme.PtS_RailwayLj3D.RemoveAll();
    // 轨道
    myDesingScheme.PtS_Railway3D.RemoveAll();
    // 线路设计交点
    myDesingScheme.JDCurveElements.RemoveAll();
    myDesingScheme.PtS_RailwayLjToBP3D.RemoveAll();
    myDesingScheme.PtS_RailwayBP3D.RemoveAll();
    myDesingScheme.PtS_HuPo.RemoveAll();
    myDesingScheme.PtSHuPoTemp.RemoveAll();
}


/********************************************/
/* Function: 选中模型后,右击菜单,删除模型       */
/********************************************/
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

/**************************************/
/* Function: 线路三维建模                 */
/**************************************/
void CMy3DSymbolLibNewView::OnMenuBuild3dlinemodle() {
    // TODO(jason): 在此添加命令处理程序代码
    // 鼠标光标 系统忙
    BeginWaitCursor();
    myDesingScheme.CalculateCurveData();
    myDesingScheme.PtS_Railway3D.RemoveAll();
    myDesingScheme.PtS_RailwayLj3D.RemoveAll();
    myDesingScheme.PtS_RailwayLjToBP3D.RemoveAll();
    myDesingScheme.PtS_RailwayBP3D.RemoveAll();
    myDesingScheme.PtS_HuPo.RemoveAll();
    if (myDesingScheme.PtS_3DLineZX.GetSize() < 2)
        return;
    CMainFrame* pMainFrame = reinterpret_cast<CMainFrame*>(AfxGetApp()->m_pMainWnd);
    double EndLC = 10000;
    for (int64 i = 0; i < myDesingScheme.PtS_3DLineZX.GetSize() - 1; i++) {
        if (myDesingScheme.PtS_3DLineZX.GetAt(i + 1)->Lc <= EndLC) {
            myDesingScheme.Get3DLineModel(myDesingScheme.PtS_3DLineZX.GetAt(i)->x, \
                                          myDesingScheme.PtS_3DLineZX.GetAt(i)->y, \
                                          myDesingScheme.PtS_3DLineZX.GetAt(i)->z, \
                                          myDesingScheme.PtS_3DLineZX.GetAt(i + 1)->x, \
                                          myDesingScheme.PtS_3DLineZX.GetAt(i + 1)->y, \
                                          myDesingScheme.PtS_3DLineZX.GetAt(i + 1)->z, \
                                          m_Railway.m_Railway_width, m_Railway.m_Lj_width, m_Railway.m_Lj_Dh, \
                                          m_Railway.m_GuiMianToLujianWidth, 45, \
                                          myDesingScheme.PtS_3DLineZX.GetAt(i)->strJDStyle, \
                                          myDesingScheme.PtS_3DLineZX.GetAt(i + 1)->strJDStyle, \
                                          i, \
                                          myDesingScheme.PtS_3DLineZX.GetAt(i)->Lc
                                         );
        }
    }
    if (myDesingScheme.PtS_3DLineZX.GetAt(myDesingScheme.PtS_3DLineZX.GetSize() - 1)->Lc <= EndLC) {  // myDesingScheme.SchemeDatass.EndLC)
        myDesingScheme.Get3DLineModelLast(myDesingScheme.PtS_3DLineZX.GetAt(myDesingScheme.PtS_3DLineZX.GetSize() - 2)->x, \
                                          myDesingScheme.PtS_3DLineZX.GetAt(myDesingScheme.PtS_3DLineZX.GetSize() - 2)->y, \
                                          myDesingScheme.PtS_3DLineZX.GetAt(myDesingScheme.PtS_3DLineZX.GetSize() - 2)->z, \
                                          myDesingScheme.PtS_3DLineZX.GetAt(myDesingScheme.PtS_3DLineZX.GetSize() - 1)->x, \
                                          myDesingScheme.PtS_3DLineZX.GetAt(myDesingScheme.PtS_3DLineZX.GetSize() - 1)->y, \
                                          myDesingScheme.PtS_3DLineZX.GetAt(myDesingScheme.PtS_3DLineZX.GetSize() - 1)->z, \
                                          m_Railway.m_Railway_width, m_Railway.m_Lj_width, m_Railway.m_Lj_Dh, \
                                          m_Railway.m_GuiMianToLujianWidth, 45, \
                                          myDesingScheme.PtS_3DLineZX.GetAt(myDesingScheme.PtS_3DLineZX.GetSize() - 2)->strJDStyle, \
                                          myDesingScheme.PtS_3DLineZX.GetAt(myDesingScheme.PtS_3DLineZX.GetSize() - 1)->strJDStyle, \
                                          myDesingScheme.PtS_3DLineZX.GetSize() - 2, \
                                          myDesingScheme.PtS_3DLineZX.GetAt(myDesingScheme.PtS_3DLineZX.GetSize() - 2)->Lc\
                                         );
    }
    b_haveMadeRail3DwayList = FALSE;
    OnDraw(GetDC());  // 刷新三维场景
}

/**************************************/
/* Function: 三维选线设计                 */
/**************************************/
void CMy3DSymbolLibNewView::OnMenuLinedesign() {
    // TODO(jason): 在此添加命令处理程序代码
    if (m_QueryType == SELECTLINE)  // 如果当前已经三维选线状态，则关闭
        m_QueryType = -1;
    else                            // 如果当前不是三维选线状态，则打开
        m_QueryType = SELECTLINE;
}

/****************************************************/
/* Function: 设置三维选线设计选中状态                   */
/****************************************************/
void CMy3DSymbolLibNewView::OnUpdateMenuLinedesign(CCmdUI* pCmdUI) {
    // TODO(jason): 在此添加命令更新用户界面处理程序代码
    pCmdUI->SetCheck(m_QueryType == SELECTLINE);
}


/****************************************************/
/* Function: 实现透视投影模式下的线路三维模型绘制       */
/****************************************************/
void CMy3DSymbolLibNewView::DrawRailwaythesme() {
    // 压入属性堆栈
    glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT | GL_POLYGON_BIT);
    glEnable(GL_DEPTH_TEST | GL_CULL_FACE);
    glCullFace(GL_BACK);
    CString m_style, m_stylePre, m_styleNext;
    SetDrawMode();                          // 设置绘图模式
    glViewport(0, 0, WinViewX, WinViewY);   // 重新设置视口大小
    // 如果还没有构建线路三维模型的显示列表
    if (b_haveMadeRail3DwayList == FALSE) {
        glNewList(m_Rail3DwayList, GL_COMPILE_AND_EXECUTE);  // 创建显示列表
        glColor3f(0.75, 0.75, 0.75);        // 设置颜色
        glLineWidth(2.0);                   // 设置线宽
        // 1.绘制左侧路基边坡
        glColor3f(1, 0, 0);
        glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());           // 绑定路基边坡纹理
        for (int32 i = 0; i < myDesingScheme.PtS_HuPo.GetSize() - 1; i++) {
            m_style = myDesingScheme.PtS_3DLineZX.GetAt(i)->strJDStyle;  // 交点类型
            m_styleNext = myDesingScheme.PtS_3DLineZX.GetAt(i + 1)->strJDStyle;
            // 如果交点类型是非其他的点，则绘制路基边坡
            if (m_style != "...") {
                DrawBP(i, 1);  // 绘制左侧路基边坡
            }
        }
        // 2.绘制右侧路基边坡
        glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());               // 绑定路基边坡纹理
        for (int32 i = 0; i < myDesingScheme.PtS_HuPo.GetSize() - 1; i++) {
            m_style = myDesingScheme.PtS_3DLineZX.GetAt(i)->strJDStyle;     // 交点类型
            m_styleNext = myDesingScheme.PtS_3DLineZX.GetAt(i + 1)->strJDStyle;  // 下一点的交点类型
            if (m_style != "...") {
                glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
                DrawBP(i, 2);  // 绘制右侧路基边坡
            }
        }
        // 3.绘制轨道
        glBindTexture(GL_TEXTURE_2D, m_cTxtureRailway.GetTxtID());          // 绑定轨道纹理
        glLineWidth(2.0);                                                   // 设置线宽
        for (int32 i = 0; i < myDesingScheme.PtS_Railway3D.GetSize() - 1; i++) {
            if (myDesingScheme.PtS_3DLineZX.GetAt(i)->Derh == 0)            // 如果挖为0
                glColor3f(0, 1, 1);                                         // 设置颜色
            else
                glColor3f(1, 0, 1);
            float L = myDesingScheme.GetDistenceXY(myDesingScheme.PtS_Railway3D.GetAt(i)->x1, \
                                                   myDesingScheme.PtS_Railway3D.GetAt(i)->z1, \
                                                   myDesingScheme.PtS_Railway3D.GetAt(i + 1)->x2, \
                                                   myDesingScheme.PtS_Railway3D.GetAt(i + 1)->z2);
            // 以矩形方式连接前后相临轨道断面
            glBegin(GL_POLYGON);
            glTexCoord2f(0.0f, 0.0f);  // 设置纹理坐标(当前轨道断面左侧点)
            glVertex3f(myDesingScheme.PtS_Railway3D.GetAt(i)->x1, \
                       myDesingScheme.PtS_Railway3D.GetAt(i)->y1,
                       myDesingScheme.PtS_Railway3D.GetAt(i)->z1);
            glTexCoord2f(1.0f, 0.0f);  // 设置纹理坐标(当前轨道断面右侧点)
            glVertex3f(myDesingScheme.PtS_Railway3D.GetAt(i)->x2, \
                       myDesingScheme.PtS_Railway3D.GetAt(i)->y2,
                       myDesingScheme.PtS_Railway3D.GetAt(i)->z2);
            glTexCoord2f(1.0f, L / 10);  // 设置纹理坐标(下一前轨道断面右侧点)
            glVertex3f(myDesingScheme.PtS_Railway3D.GetAt(i + 1)->x2, \
                       myDesingScheme.PtS_Railway3D.GetAt(i + 1)->y2,
                       myDesingScheme.PtS_Railway3D.GetAt(i + 1)->z2);
            glTexCoord2f(0.0f, L / 10);  // 设置纹理坐标(下一前轨道断面左侧点)
            glVertex3f(myDesingScheme.PtS_Railway3D.GetAt(i + 1)->x1, \
                       myDesingScheme.PtS_Railway3D.GetAt(i + 1)->y1,
                       myDesingScheme.PtS_Railway3D.GetAt(i + 1)->z1);
            glEnd();
        }
        // 4.绘制道床边坡
        glBindTexture(GL_TEXTURE_2D, m_cTxtureGdToLJ.GetTxtID());  // 绑定道床边坡纹理
        glColor3f(1, 1, 0);  // 设置颜色
        for (int32 i = 0; i < myDesingScheme.PtS_Railway3D.GetSize() - 1; i++) {
            // 以矩形方式连接方式绘制左侧道床边坡
            glBegin(GL_POLYGON);
            glTexCoord2f(1.0f, 0.0f);  // 设置纹理坐标(当前左侧道床边坡左侧点)
            glVertex3f(myDesingScheme.PtS_Railway3D.GetAt(i)->x1, \
                       myDesingScheme.PtS_Railway3D.GetAt(i)->y1,
                       myDesingScheme.PtS_Railway3D.GetAt(i)->z1);
            glTexCoord2f(1.0f, 1.0f);  // 设置纹理坐标(当前左侧道床边坡右侧点)
            glVertex3f(myDesingScheme.PtS_Railway3D.GetAt(i + 1)->x1, \
                       myDesingScheme.PtS_Railway3D.GetAt(i + 1)->y1,
                       myDesingScheme.PtS_Railway3D.GetAt(i + 1)->z1);
            glTexCoord2f(0.0f, 1.0f);  // 设置纹理坐标(下一左侧道床边坡右侧点)
            glVertex3f(myDesingScheme.PtS_RailwayLj3D.GetAt(i + 1)->x1, \
                       myDesingScheme.PtS_RailwayLj3D.GetAt(i + 1)->y1,
                       myDesingScheme.PtS_RailwayLj3D.GetAt(i + 1)->z1);
            glTexCoord2f(0.0f, 0.0f);  // 设置纹理坐标(下一左侧道床边坡左侧点)
            glVertex3f(myDesingScheme.PtS_RailwayLj3D.GetAt(i)->x1, \
                       myDesingScheme.PtS_RailwayLj3D.GetAt(i)->y1,
                       myDesingScheme.PtS_RailwayLj3D.GetAt(i)->z1);
            glEnd();
            // 以矩形方式连接方式绘制右侧道床边坡
            glBegin(GL_POLYGON);
            glTexCoord2f(0.0f, 0.0f);  // 设置纹理坐标(当前右侧道床边坡左侧点)
            glVertex3f(myDesingScheme.PtS_Railway3D.GetAt(i)->x2, \
                       myDesingScheme.PtS_Railway3D.GetAt(i)->y2,
                       myDesingScheme.PtS_Railway3D.GetAt(i)->z2);
            glTexCoord2f(0.0f, 1.0f);  // 设置纹理坐标(当前右侧道床边坡右侧点)
            glVertex3f(myDesingScheme.PtS_Railway3D.GetAt(i + 1)->x2, \
                       myDesingScheme.PtS_Railway3D.GetAt(i + 1)->y2,
                       myDesingScheme.PtS_Railway3D.GetAt(i + 1)->z2);
            glTexCoord2f(1.0f, 1.0f);  // 设置纹理坐标(下一右侧道床边坡右侧点)
            glVertex3f(myDesingScheme.PtS_RailwayLj3D.GetAt(i + 1)->x2, \
                       myDesingScheme.PtS_RailwayLj3D.GetAt(i + 1)->y2,
                       myDesingScheme.PtS_RailwayLj3D.GetAt(i + 1)->z2);
            glTexCoord2f(1.0f, 0.0f);  // 设置纹理坐标(下一右侧道床边坡左侧点)
            glVertex3f(myDesingScheme.PtS_RailwayLj3D.GetAt(i)->x2, \
                       myDesingScheme.PtS_RailwayLj3D.GetAt(i)->y2,
                       myDesingScheme.PtS_RailwayLj3D.GetAt(i)->z2);
            glEnd();
        }
        // 5.绘制路肩
        glBindTexture(GL_TEXTURE_2D, m_cTxtureLJ.GetTxtID());  // 绑定路肩纹理
        glColor3f(1, 0.5, 0.25);
        for (int32 i = 0; i < myDesingScheme.PtS_RailwayLj3D.GetSize() - 1; i++) {
            // 以矩形方式连接方式绘制左侧路肩
            glBegin(GL_POLYGON);
            glTexCoord2f(0.0f, 0.0f);  // 设置纹理坐标(当前左侧路肩断面左侧点)
            glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i)->x1, \
                       myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i)->y1,
                       myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i)->z1);
            glTexCoord2f(0.0f, 1.0f);  // 设置纹理坐标(当前左侧路肩断面右侧点)
            glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i + 1)->x1, \
                       myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i + 1)->y1,
                       myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i + 1)->z1);
            glTexCoord2f(1.0f, 1.0f);  // 设置纹理坐标(下一左侧路肩断面右侧点)
            glVertex3f(myDesingScheme.PtS_RailwayLj3D.GetAt(i + 1)->x1, \
                       myDesingScheme.PtS_RailwayLj3D.GetAt(i + 1)->y1,
                       myDesingScheme.PtS_RailwayLj3D.GetAt(i + 1)->z1);
            glTexCoord2f(1.0f, 0.0f);  // 设置纹理坐标(下一左侧路肩断面左侧点)
            glVertex3f(myDesingScheme.PtS_RailwayLj3D.GetAt(i)->x1, \
                       myDesingScheme.PtS_RailwayLj3D.GetAt(i)->y1,
                       myDesingScheme.PtS_RailwayLj3D.GetAt(i)->z1);
            glEnd();
            // 以矩形方式连接方式绘制右侧路肩
            glBegin(GL_POLYGON);
            glTexCoord2f(0.0f, 0.0f);  // 设置纹理坐标(当前右侧路肩断面左侧点)
            glVertex3f(myDesingScheme.PtS_RailwayLj3D.GetAt(i)->x2, \
                       myDesingScheme.PtS_RailwayLj3D.GetAt(i)->y2,
                       myDesingScheme.PtS_RailwayLj3D.GetAt(i)->z2);
            glTexCoord2f(1.0f, 0.0f);  // 设置纹理坐标(当前右侧路肩断面右侧点)
            glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i)->x2, \
                       myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i)->y2,
                       myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i)->z2);
            glTexCoord2f(1.0f, 1.0f);  // 设置纹理坐标(下一右侧路肩断面右侧点)
            glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i + 1)->x2, \
                       myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i + 1)->y2,
                       myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i + 1)->z2);
            glTexCoord2f(0.0f, 1.0f);  // 设置纹理坐标(下一右侧路肩断面左侧点)
            glVertex3f(myDesingScheme.PtS_RailwayLj3D.GetAt(i + 1)->x2, \
                       myDesingScheme.PtS_RailwayLj3D.GetAt(i + 1)->y2,
                       myDesingScheme.PtS_RailwayLj3D.GetAt(i + 1)->z2);
            glEnd();
        }
        // 6.填补断面
        int32 JD_Count = myDesingScheme.PtS_JD.GetSize();
        int32 b_pIndex = 0;
        int32 e_pIndex = JD_Count - 1;
        if (JD_Count > 0) {
            // 保存2个面上的点的坐标信息
            vector<Railway3DCordinate> rc2;
            vector<Railway3DCordinate> rc1;
            // 计算前后断面各点
            myDesingScheme.CalculateFillFacePoints(rc2, rc1);
            // 根据点绘制面
            drawFillFace(rc2);
            drawFillFace(rc1);
        }
        glLineWidth(1.0);               // 恢复线宽
        glEndList();                    // 结束显示列表
        b_haveMadeRail3DwayList = TRUE;  // 标识已经创建显示列表
    } else {                            // 如果已经构建线路三维模型的显示列表,则直接调用显示列表
        glCallList(m_Rail3DwayList);    // 调用线路三维模型显示列表
    }
    glPopAttrib();                      // 弹出属性堆栈
}

/**************************************/
/* Function: 根据点绘制面                 */
/**************************************/
void CMy3DSymbolLibNewView::drawFillFace(vector<Railway3DCordinate> fillFacePoints) {
    int32 f_size = fillFacePoints.size();
    glBindTexture(GL_TEXTURE_2D, m_cFillFaceTxture.GetTxtID());
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
/* Function: 绘制中心线               */
/**************************************/
void CMy3DSymbolLibNewView::DrawCenterLine(int64 index, BOOL ifSelectLine) {
    CString tt;
    double x1, y1, z1, x2, y2, z2;
    double x0, y0, z0;
    float DerDistence = 2.0;
    float Dh;
    m_TempPts.RemoveAll();
    if (ifSelectLine == TRUE) {  // 在选线设计
        Dh = 5;
        x1 = myDesingScheme.PtS_JD.GetAt(index)->x;
        // y1=myDesingScheme.PtS_JD.GetAt(index)->y;
        z1 = myDesingScheme.PtS_JD.GetAt(index)->z;
        y1 = GetHeight(x1, z1);
        x2 = myDesingScheme.PtS_JD.GetAt(index + 1)->x;
        // y2=myDesingScheme.PtS_JD.GetAt(index+1)->y;
        z2 = myDesingScheme.PtS_JD.GetAt(index + 1)->z;
        y2 = GetHeight(x2, z2);
    }
    glColor3f(0, 0, 1);
    PCordinate pt;
    double L = myDesingScheme.GetDistenceXYZ(x1, y1, z1, x2, y2, z2);
    double L0 = 0;
    while (L0 <= L) {
        x0 = x1 + L0 / L * (x2 - x1);
        y0 = y1 + L0 / L * (y2 - y1);
        z0 = z1 + L0 / L * (z2 - z1);
        // 地面高程
        float dmh = GetHeight(x0, -z0);
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
            dmh = GetHeight(x0, -z0);
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

/**************************************/
/* Function: 绘制边坡                 */
/**************************************/
void CMy3DSymbolLibNewView::DrawBP(int64 index, int32 BPside) {
    float mNCDistence = 4.0;
    int64 i = index;
    int32 j;
    if (1 == BPside) {  // 左边坡
        int32 N1 = myDesingScheme.PtS_HuPo.GetAt(i)->Huponums_L;
        int32 N2 = myDesingScheme.PtS_HuPo.GetAt(i + 1)->Huponums_L;
        if (myDesingScheme.PtS_HuPo.GetAt(i)->TW_left == 0 || myDesingScheme.PtS_HuPo.GetAt(i)->TW_right == 0) {
            glColor3f(0, 1, 1);
        } else {
            glColor3f(1, 0, 0);
        }
        if (N1 <= N2 && N1 > 0 && N2 > 0) {
            for (j = 0; j < N1; j++) {
                glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
                // 如果路基类型相同(同为路堑或路堤)
                if (myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].style == myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].style) {
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].z);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].z);
                    glEnd();
                } else {  // 如果路基类型相同(路堑,路堤相连)
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].z);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j + 1].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j + 1].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j + 1].Hp[2].z);
                    glEnd();
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j + 1].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j + 1].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j + 1].Hp[2].z);
                    glTexCoord2f(0.5f, 0.5f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j + 1].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j + 1].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j + 1].Hp[1].z);
                    glTexCoord2f(0.5f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].z);
                    glEnd();
                }
                if (j > 0) {
                    glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[0].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[0].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[0].z);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[0].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[0].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[0].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].z);
                    glEnd();
                }
            }
        } else {
            for (j = 0; j < N2; j++) {
                glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
                if (myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].style == \
                        myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].style) {
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].z);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].z);
                    glEnd();
                } else {
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j + 1].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j + 1].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j + 1].Hp[2].z);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[2].z);
                    glEnd();
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j + 1].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j + 1].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j + 1].Hp[2].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j + 1].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j + 1].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j + 1].Hp[1].z);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].z);
                    glEnd();
                }
                if (j > 0) {
                    glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[0].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[0].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[0].z);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[0].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[0].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[0].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_L[j].Hp[1].z);
                    glEnd();
                }
            }
        }
    } else if (BPside == 2) {
        int32 N1 = myDesingScheme.PtS_HuPo.GetAt(i)->Huponums_R;
        int32 N2 = myDesingScheme.PtS_HuPo.GetAt(i + 1)->Huponums_R;
        if (N1 <= N2 && N1 > 0 && N2 > 0) {
            for (j = 0; j < N1; j++) {
                glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
                if (myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].style == \
                        myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].style) {
                    glBegin(GL_POLYGON);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].z);
                    glEnd();
                } else {
                    glBegin(GL_POLYGON);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j + 1].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j + 1].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j + 1].Hp[2].z);
                    glEnd();
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j + 1].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j + 1].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j + 1].Hp[2].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j + 1].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j + 1].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j + 1].Hp[1].z);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].z);
                    glEnd();
                }
                if (j > 0) {
                    glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[0].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[0].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[0].z);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[0].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[0].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[0].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].z);
                    glEnd();
                }
            }
        } else {
            for (j = 0; j < N2; j++) {
                glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
                if (myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].style == \
                        myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].style) {
                    glBegin(GL_POLYGON);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].z);
                    glEnd();
                } else {
                    glBegin(GL_POLYGON);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j + 1].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j + 1].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j + 1].Hp[2].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[2].z);
                    glEnd();
                    glBegin(GL_POLYGON);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j + 1].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j + 1].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j + 1].Hp[2].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j + 1].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j + 1].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j + 1].Hp[1].z);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].z);
                    glEnd();
                }
                if (j > 0) {
                    glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());
                    glBegin(GL_POLYGON);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[0].x,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[0].y,
                               myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[0].z);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[0].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[0].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[0].z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].x,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].y,
                               myDesingScheme.PtS_HuPo.GetAt(i + 1)->HuPo_R[j].Hp[1].z);
                    glEnd();
                }
            }
        }
    }
    glLineWidth(1.0);
    glColor3f(1, 1, 1);
}

/**************************************/
/* Function: 清除所有线路                 */
/**************************************/
void CMy3DSymbolLibNewView::OnMenuClearLines() {
    // TODO(jason): 在此添加命令处理程序代码
    clearLinesData();
    initLines();
}


/************************************************************************/
/* Function: 新建工程                                                   */
/************************************************************************/
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
        _snprintf_s(FileName, sizeof(FileName), sizeof(FileName)-1, "%s", NeededFile);

        if (strcmp(FileDialogBoxFile.GetFileExt(), "prj") != 0)
            strcat(FileName, ".prj");  // NOLINT
        {
            CStdioFile file;
            file.Open(FileName, CStdioFile::modeCreate | CStdioFile::modeWrite);
            if (file == NULL) {
                MessageBox("ERROR!", "ERROR", MB_ICONINFORMATION + MB_OK);
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
        _snprintf_s(FileName, sizeof(FileName), sizeof(FileName)-1, "%s", NeededFile);

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


//--------------------------------------------------------------------------------------



/************************************************************************/
/*                              线符号                                  */
/************************************************************************/

// 线编辑 ==》 添加线
void CMy3DSymbolLibNewView::OnMenuLineAdd() {
    // TODO(jason): 在此添加命令处理程序代码
    if (m_QueryType == LINE_ADD)
        m_QueryType = -1;
    else
        m_QueryType = LINE_ADD;
}


// 线编辑 ==》融合   线矢量与地表三角网融合
void CMy3DSymbolLibNewView::OnMenuLineFuse() {
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
        tmp_line.pt1._x -= 1;
        tmp_line.pt2._x -= 1;
    }
    // else
    // {
    //   tmp_line.pt1._z += 5;
    //   tmp_line.pt2._z += 5;
    // }
    CalcuateGridNum(&tmp_rowNum, &tmp_row_index_begin, &tmp_row_index_end,
                    &tmp_colNum, &tmp_col_index_begin, &tmp_col_index_end, tmp_line);
    CalcuateJD(tmp_rowNum, tmp_row_index_begin, tmp_row_index_end,
               tmp_colNum, tmp_col_index_begin, tmp_col_index_end, tmp_line, Line_a_JD_vector);
    tmp_line.pt1 = m_LinesArray[0]->pt1;
    tmp_line.pt2 = m_LinesArray[0]->pt2;
    // if(abs(tmp_line.pt1._x - tmp_line.pt2._x) < MAP_SCALE)
    {
        tmp_line.pt1._x += 1;
        tmp_line.pt2._x += 1;
    }
    /*else
    {
        tmp_line.pt1._z -= 5;
        tmp_line.pt2._z -= 5;
    }*/
    CalcuateGridNum(&tmp_rowNum, &tmp_row_index_begin, &tmp_row_index_end,
                    &tmp_colNum, &tmp_col_index_begin, &tmp_col_index_end, tmp_line);
    CalcuateJD(tmp_rowNum, tmp_row_index_begin, tmp_row_index_end,
               tmp_colNum, tmp_col_index_begin, tmp_col_index_end, tmp_line, Line_b_JD_vector);
    fuse_Flag = TRUE;
}


void CMy3DSymbolLibNewView::OnUpdateMenuLineAdd(CCmdUI* pCmdUI) {
    // TODO(jason): 在此添加命令更新用户界面处理程序代码
    pCmdUI->SetCheck(m_QueryType == LINE_ADD);
}


// 空间点求投影到平面的直线方程系数ABC, Ax+By+C=0
void CMy3DSymbolLibNewView::getLine2ABC(double* A, double* B, double* C, Point3 p1, Point3 p2) {
    // 直线AX+BY+C=0的一般式方程就是：
    //  A = Y2 - Y1
    //  B = X1 - X2
    //  C = X2*Y1 - X1*Y2
    *A = p2._z - p1._z;
    *B = p1._x - p2._x;
    *C = p2._x * p1._z - p1._x * p2._z;
}


// 计算线段_line所经过的横向和纵向格网数, 及索引范围
void CMy3DSymbolLibNewView::CalcuateGridNum(int32* rowNum, int32* row_index_begin, int32* row_index_end,
        int32* colNum, int32* col_index_begin, int32* col_index_end, Line3 _line) {
    int32 tmp_rowNum = 0;
    int32 tmp_row_index_begin = 0;
    int32 tmp_row_index_end = 0;
    int32 tmp_colNum = 0;
    int32 tmp_col_index_begin = 0;
    int32 tmp_col_index_end = 0;
    double r1 = abs(_line.pt1._x);
    double c1 = abs(_line.pt1._z);
    double r2 = abs(_line.pt2._x);
    double c2 = abs(_line.pt2._z);
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


// sort(_pv.begin(),_pv.end(),comp);
bool comp(Point3& p1, Point3& p2) {
    return p1._x < p2._x;
}

bool comp2(Point3& p1, Point3& p2) {
    return p1._z < p2._z;
}


// 计算平面交点坐标,并计算出交点出的高程值
void CMy3DSymbolLibNewView::CalcuateJD(int32 rowNum, int32 row_index_begin, int32 row_index_end,
                                       int32 colNum, int32 col_index_begin, int32 col_index_end, Line3 _line, vector<Point3>& _pv) {  // NOLINT
    // 直线方程系数ABC, Ax+By+C=0
    double A, B, C;
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
            tmp_point._x = static_cast<float>(r) * MAP_SCALE;  // 平面横坐标
            // 平面纵坐标
            if (DOUBLE_NUMBER_IS_ZERO(B)) {
                break;
            } else {
                tmp_point._z = ((-A) * tmp_point._x - C) / B;
            }
            tmp_point._y = GetHeight(tmp_point._x, tmp_point._z);
            JD_vector1.push_back(tmp_point);
        }
    } else if (row_index_begin > row_index_end) {
        for (int32 r = row_index_begin - 1; r > row_index_end; --r) {
            tmp_point._x = static_cast<float>(r) * MAP_SCALE;  // 平面横坐标
            // 平面纵坐标
            if (DOUBLE_NUMBER_IS_ZERO(B)) {
                break;
            } else {
                tmp_point._z = ((-A) * tmp_point._x - C) / B;
            }
            tmp_point._y = GetHeight(tmp_point._x, tmp_point._z);
            JD_vector1.push_back(tmp_point);
        }
    }
    // 交点2 ---------------------------------------------------------------------
    if (col_index_begin < col_index_end) {
        // 通过格网纵坐标 求与线段交点
        for (int32 c = col_index_begin + 1; c < col_index_end; ++c) {
            tmp_point._z = static_cast<float>(-c) * MAP_SCALE;  // 平面纵坐标
            // 平面横坐标
            if (DOUBLE_NUMBER_IS_ZERO(A)) {
                break;
            } else {
                // Ax+By+C=0
                tmp_point._x = ((-B) * tmp_point._z - C) / A;
            }
            tmp_point._y = GetHeight(tmp_point._x, tmp_point._z);
            JD_vector2.push_back(tmp_point);
        }
    } else if (col_index_begin > col_index_end) {
        // 通过格网纵坐标 求与线段交点
        for (int32 c = col_index_begin - 1; c > col_index_end; --c) {
            tmp_point._z = static_cast<float>(-c) * MAP_SCALE;  // 平面纵坐标
            // 平面横坐标
            if (DOUBLE_NUMBER_IS_ZERO(A)) {
                break;
            } else {
                // Ax+By+C=0
                tmp_point._x = ((-B) * tmp_point._z - C) / A;
            }
            tmp_point._y = GetHeight(tmp_point._x, tmp_point._z);
            JD_vector2.push_back(tmp_point);
        }
    }
    // 交点3 ---------------------------------------------------------------------
    // double line_pos_b = MAP_SCALE * (row_index_begin < row_index_end ? row_index_begin : row_index_end);
    // double line_pos_e = MAP_SCALE * (row_index_begin > row_index_end ? row_index_begin : row_index_end);
    double line_pos_b = (_line.pt1._x < _line.pt2._x) ? _line.pt1._x : _line.pt2._x;
    double line_pos_e = (_line.pt1._x >= _line.pt2._x) ? _line.pt1._x : _line.pt2._x;;
    for (int32 r = 0; r < MAP_W; ++r) {
        double b = static_cast<float>(-r) * MAP_SCALE;
        if (GetJDFrom2Line(&tmp_point, b, A, B, C)) {
            if ((line_pos_b < tmp_point._x) && (tmp_point._x < line_pos_e)) {
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
    sort(_pv.begin(), _pv.end(), comp);
}



// 计算2条直线的交点y=x+b, Ax+By+C=0, 返回0表示无交点
BOOL CMy3DSymbolLibNewView::GetJDFrom2Line(PPoint3 p/*out*/, double b, double A, double B, double C) {
    if (DOUBLE_NUMBER_IS_ZERO(A)) {  // A == 0
        p->_z = -C / B;
        p->_x = p->_z - b;
        p->_y = GetHeight(p->_x, p->_z);
    } else {
        if (!(DOUBLE_NUMBER_IS_ZERO(B))) {
            if (DOUBLE_NUMBER_IS_ZERO(-A / B - 1)) {
                return 0;  // 2直线平行无交点
            } else {
                p->_x = (-1) * (B * b + C) / (A + B);
                p->_z = p->_x + b;
                p->_y = GetHeight(p->_x, p->_z);
            }
        } else {  // B == 0
            p->_x = -C / A;
            p->_z = p->_x + b;
            p->_y = GetHeight(p->_x, p->_z);
        }
    }
    return 1;
}



// 所有三角形顶点坐标最小最大值
void CMy3DSymbolLibNewView::GetMinXY(const vector<Point3>& _pv1,  const vector<Point3>& _pv2, double* _minX, double* _minY, double* _maxX, double* _maxY) {
    vector<Point3> tmpPV;
    uint32 i = 0;
    for (i = 0; i < _pv1.size(); ++i) {
        tmpPV.push_back(_pv1[i]);
    }
    for (i = 0; i < _pv2.size(); ++i) {
        tmpPV.push_back(_pv2[i]);
    }
    sort(tmpPV.begin(), tmpPV.end(), comp);
    *_minX = abs(tmpPV[0]._x);
    *_maxX = abs(tmpPV[tmpPV.size() - 1]._x);
    sort(tmpPV.begin(), tmpPV.end(), comp2);
    *_maxY = abs(tmpPV[0]._z);
    *_minY = abs(tmpPV[tmpPV.size() - 1]._z);
}

// 线符号纹理坐标
void CMy3DSymbolLibNewView::GetUV(double _x, double _y, double _minX, double _minY, double _maxX, double _maxY, double* _u, double* _v) {
    *_u = (abs(_x) - _minX) / (_maxX - _minX);
    *_v = (abs(_y) - _minY) / (_maxY - _minY);
}


// 绘制交点连线
void CMy3DSymbolLibNewView::DrawJDLine(const vector<Point3>& _pv1, const vector<Point3>& _pv2) {
    double DD = 1.0f;
    double tmpMinX = 0.0, tmpMinY = 0.0, tmpMaxX = 0.0, tmpMaxY = 0.0, tmpU = 0.0, tmpV = 0.0;
    GetMinXY(_pv1, _pv2, &tmpMinX, &tmpMinY, &tmpMaxX, &tmpMaxY);
    // 配置地形
    double tmpX = 0.0, tmpY = 0.0, tmpZ = 0.0;
    // 三角网
    glEnable(GL_TEXTURE_2D);    // 开启纹理
    // glBindTexture(GL_TEXTURE_2D, m_cTxtureRailway.GetTxtID());
    GLuint rd;
    char cc[256] = "E:/CG/My3DSymbolLibFiles/DataFormated/RoadTexture/铁路/ww.bmp";
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
                tmpX = _pv1[i]._x;
                tmpY = _pv1[i]._y + DD;
                tmpZ = _pv1[i]._z;
            } else {
                tmpX = _pv2[j]._x;
                tmpY = _pv2[j]._y + DD;
                tmpZ = _pv2[j]._z;
            }
            tmpMinX = 0.0, tmpMinY = 0.0, tmpMaxX = 10.0, tmpMaxY = 10.0;
            GetUV(tmpX, tmpZ, tmpMinX, tmpMinY, tmpMaxX, tmpMaxY, &tmpU, &tmpV);
            glTexCoord2f(tmpU, tmpV);
            glVertex3f(tmpX, tmpY, tmpZ);
        }
        glEnd();
        glLineWidth(1.0);           // 恢复线宽
        glPopAttrib();
        glPopMatrix();              // 弹出矩阵堆栈
    }
}



// 增加线符号的宽度信息
void CMy3DSymbolLibNewView::OnMenuAddLineWidth() {
    // TODO(jason): 在此添加命令处理程序代码
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
        if (m_QueryType == AREA_ADD)
            m_QueryType = -1;
        else
            m_QueryType = AREA_ADD;
    }
}

// 更新添加面符号勾选状态
void CMy3DSymbolLibNewView::OnUpdateMenuAddAreaSlib(CCmdUI* pCmdUI) {
    // TODO(jason): 在此添加命令更新用户界面处理程序代码
    pCmdUI->SetCheck(m_QueryType == AREA_ADD);
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
        FindAllTrianglesInPolygon(tmp_area4);
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
            // static GLuint rd;
            // static char cc[256] = "";
            // CString scenePath = g_sceneDataPath.c_str();
            // CString area_texture = scenePath + "\\Terrain\\Tex\\area.bmp";
            // strcpy(cc, _area4->area_texture);
            //
            // strcpy(cc,  area_texture);
            // strcpy(cc, _area4->area_texture);
            // LoadT8(cc,    rd);
            // glBindTexture(GL_TEXTURE_2D, rd);
            // glBindTexture(GL_TEXTURE_2D, m_area_texture);
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
                    glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt1._x, _area4->TrianglesInPolygonVecotr[i].pt1._y + deta, _area4->TrianglesInPolygonVecotr[i].pt1._z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt2._x, _area4->TrianglesInPolygonVecotr[i].pt2._y + deta, _area4->TrianglesInPolygonVecotr[i].pt2._z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt3._x, _area4->TrianglesInPolygonVecotr[i].pt3._y + deta, _area4->TrianglesInPolygonVecotr[i].pt3._z);
                }
                glEnd();
            }
            // 2. 经过局部三角化的三角形
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr1.size(); ++i) {
                glColor3f(0.0980 , 0.0980 , 0.4392);
                glBegin(GL_TRIANGLES);
                {
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr1[i].pt1._x, _area4->LocalTrianglesVecotr1[i].pt1._y + deta, _area4->LocalTrianglesVecotr1[i].pt1._z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr1[i].pt2._x, _area4->LocalTrianglesVecotr1[i].pt2._y + deta, _area4->LocalTrianglesVecotr1[i].pt2._z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr1[i].pt3._x, _area4->LocalTrianglesVecotr1[i].pt3._y + deta, _area4->LocalTrianglesVecotr1[i].pt3._z);
                }
                glEnd();
            }
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr2.size(); ++i) {
                glColor3f(0.611, 0.400, 0.121);
                glBegin(GL_TRIANGLES);
                {
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr2[i].pt1._x, _area4->LocalTrianglesVecotr2[i].pt1._y + deta, _area4->LocalTrianglesVecotr2[i].pt1._z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr2[i].pt2._x, _area4->LocalTrianglesVecotr2[i].pt2._y + deta, _area4->LocalTrianglesVecotr2[i].pt2._z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr2[i].pt3._x, _area4->LocalTrianglesVecotr2[i].pt3._y + deta, _area4->LocalTrianglesVecotr2[i].pt3._z);
                }
                glEnd();
            }
            // 2.1 多边形 顶点处
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr1_1.size(); ++i) {
                glColor3f(1.0000 , 0.3882 , 0.2784);
                glBegin(GL_TRIANGLES);
                {
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt1._x, _area4->LocalTrianglesVecotr1_1[i].pt1._y + deta, _area4->LocalTrianglesVecotr1_1[i].pt1._z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt2._x, _area4->LocalTrianglesVecotr1_1[i].pt2._y + deta, _area4->LocalTrianglesVecotr1_1[i].pt2._z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt3._x, _area4->LocalTrianglesVecotr1_1[i].pt3._y + deta, _area4->LocalTrianglesVecotr1_1[i].pt3._z);
                }
                glEnd();
            }
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr2_1.size(); ++i) {
                glColor3f(0.6980 , 0.1333 , 0.1333);
                glBegin(GL_TRIANGLES);
                {
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt1._x, _area4->LocalTrianglesVecotr2_1[i].pt1._y + deta, _area4->LocalTrianglesVecotr2_1[i].pt1._z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt2._x, _area4->LocalTrianglesVecotr2_1[i].pt2._y + deta, _area4->LocalTrianglesVecotr2_1[i].pt2._z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt3._x, _area4->LocalTrianglesVecotr2_1[i].pt3._y + deta, _area4->LocalTrianglesVecotr2_1[i].pt3._z);
                }
                glEnd();
            }
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr_last.size(); ++i) {
                glColor3f(0.6275,  0.1255,  0.9412);
                glBegin(GL_TRIANGLES);
                {
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt1._x, _area4->LocalTrianglesVecotr_last[i].pt1._y + deta, _area4->LocalTrianglesVecotr_last[i].pt1._z);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt2._x, _area4->LocalTrianglesVecotr_last[i].pt2._y + deta, _area4->LocalTrianglesVecotr_last[i].pt2._z);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt3._x, _area4->LocalTrianglesVecotr_last[i].pt3._y + deta, _area4->LocalTrianglesVecotr_last[i].pt3._z);
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
        // test begin
        {
            /*uint32 i = 0;


            glColor3f(0.8,0.1,1);
            glBegin(GL_LINE_STRIP);
            for(i=0;i<Line_1_JD_vector.size();++i)
            {
                glVertex3f(Line_1_JD_vector[i]._x, Line_1_JD_vector[i]._y + l_deta, Line_1_JD_vector[i]._z);
            }
            glEnd();


            glColor3f(0.1,0.5,0.2);
            glBegin(GL_LINE_STRIP);
            for(i=0;i<Line_2_JD_vector.size();++i)
            {
                glVertex3f(Line_2_JD_vector[i]._x, Line_2_JD_vector[i]._y + l_deta, Line_2_JD_vector[i]._z);
            }
            glEnd();


            glColor3f(0.6,0.8,0.9);
            glBegin(GL_LINE_STRIP);
            for(i=0;i<Line_3_JD_vector.size();++i)
            {
                glVertex3f(Line_3_JD_vector[i]._x, Line_3_JD_vector[i]._y + l_deta, Line_3_JD_vector[i]._z);
            }
            glEnd();


            glColor3f(0.1,0.8,0.4);
            glBegin(GL_LINE_STRIP);
            for(i=0;i<Line_4_JD_vector.size();++i)
            {
                glVertex3f(Line_4_JD_vector[i]._x, Line_4_JD_vector[i]._y + l_deta, Line_4_JD_vector[i]._z);
            }
            glEnd();*/
        }
        // test end
        {
            // 1.多边形内原先完整的三角形
            for (uint32 i = 0; i < _area4->TrianglesInPolygonVecotr.size(); ++i) {
                glColor3f(1.0000 , 0.9804 , 0.9804);
                glBegin(GL_TRIANGLES);
                {
                    glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt1._x, _area4->TrianglesInPolygonVecotr[i].pt1._y , _area4->TrianglesInPolygonVecotr[i].pt1._z);
                    glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt2._x, _area4->TrianglesInPolygonVecotr[i].pt2._y , _area4->TrianglesInPolygonVecotr[i].pt2._z);
                    glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt3._x, _area4->TrianglesInPolygonVecotr[i].pt3._y , _area4->TrianglesInPolygonVecotr[i].pt3._z);
                }
                glEnd();
            }
            // 2. 经过局部三角化的三角形
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr1.size(); ++i) {
                glColor3f(1.0, 1.0, 0.1);
                glBegin(GL_TRIANGLES);
                {
                    glVertex3f(_area4->LocalTrianglesVecotr1[i].pt1._x, _area4->LocalTrianglesVecotr1[i].pt1._y , _area4->LocalTrianglesVecotr1[i].pt1._z);
                    glVertex3f(_area4->LocalTrianglesVecotr1[i].pt2._x, _area4->LocalTrianglesVecotr1[i].pt2._y , _area4->LocalTrianglesVecotr1[i].pt2._z);
                    glVertex3f(_area4->LocalTrianglesVecotr1[i].pt3._x, _area4->LocalTrianglesVecotr1[i].pt3._y , _area4->LocalTrianglesVecotr1[i].pt3._z);
                }
                glEnd();
            }
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr2.size(); ++i) {
                glColor3f(0.611, 0.400, 0.121);
                glBegin(GL_TRIANGLES);
                {
                    glVertex3f(_area4->LocalTrianglesVecotr2[i].pt1._x, _area4->LocalTrianglesVecotr2[i].pt1._y , _area4->LocalTrianglesVecotr2[i].pt1._z);
                    glVertex3f(_area4->LocalTrianglesVecotr2[i].pt2._x, _area4->LocalTrianglesVecotr2[i].pt2._y , _area4->LocalTrianglesVecotr2[i].pt2._z);
                    glVertex3f(_area4->LocalTrianglesVecotr2[i].pt3._x, _area4->LocalTrianglesVecotr2[i].pt3._y , _area4->LocalTrianglesVecotr2[i].pt3._z);
                }
                glEnd();
            }
            // 2.1 多边形 顶点处
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr1_1.size(); ++i) {
                glColor3f(1.0000 , 0.3882 , 0.2784);
                glBegin(GL_TRIANGLES);
                {
                    glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt1._x, _area4->LocalTrianglesVecotr1_1[i].pt1._y , _area4->LocalTrianglesVecotr1_1[i].pt1._z);
                    glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt2._x, _area4->LocalTrianglesVecotr1_1[i].pt2._y , _area4->LocalTrianglesVecotr1_1[i].pt2._z);
                    glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt3._x, _area4->LocalTrianglesVecotr1_1[i].pt3._y , _area4->LocalTrianglesVecotr1_1[i].pt3._z);
                }
                glEnd();
            }
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr2_1.size(); ++i) {
                glColor3f(0.6980 , 0.1333 , 0.1333);
                glBegin(GL_TRIANGLES);
                {
                    glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt1._x, _area4->LocalTrianglesVecotr2_1[i].pt1._y, _area4->LocalTrianglesVecotr2_1[i].pt1._z);
                    glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt2._x, _area4->LocalTrianglesVecotr2_1[i].pt2._y, _area4->LocalTrianglesVecotr2_1[i].pt2._z);
                    glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt3._x, _area4->LocalTrianglesVecotr2_1[i].pt3._y, _area4->LocalTrianglesVecotr2_1[i].pt3._z);
                }
                glEnd();
            }
            for (uint32 i = 0; i < _area4->LocalTrianglesVecotr_last.size(); ++i) {
                glColor3f(0.6275,  0.1255,  0.9412);
                glBegin(GL_TRIANGLES);
                {
                    glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt1._x, _area4->LocalTrianglesVecotr_last[i].pt1._y, _area4->LocalTrianglesVecotr_last[i].pt1._z);
                    glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt2._x, _area4->LocalTrianglesVecotr_last[i].pt2._y, _area4->LocalTrianglesVecotr_last[i].pt2._z);
                    glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt3._x, _area4->LocalTrianglesVecotr_last[i].pt3._y, _area4->LocalTrianglesVecotr_last[i].pt3._z);
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
    _snprintf_s(cc, sizeof(cc), sizeof(cc)-1, _areaTexture_str);
    LoadT8(cc,  texture_id);
}

// 计算出所有包含在多边形内的点
int32 CMy3DSymbolLibNewView::FindAllPointsInPolygon(const Area_4& m_area4) {
    CPointPolygonRelationship tmp_ppr;
    PPR_Polygon tmp_polygon;
    PPR_Point tmp_point;
    tmp_point.x = m_area4.pt1._x;
    tmp_point.y = m_area4.pt1._z;
    tmp_polygon.push_back(tmp_point);
    tmp_point.x = m_area4.pt2._x;
    tmp_point.y = m_area4.pt2._z;
    tmp_polygon.push_back(tmp_point);
    tmp_point.x = m_area4.pt3._x;
    tmp_point.y = m_area4.pt3._z;
    tmp_polygon.push_back(tmp_point);
    tmp_point.x = m_area4.pt4._x;
    tmp_point.y = m_area4.pt4._z;
    tmp_polygon.push_back(tmp_point);
    PPR_Point tmp_dem_point;
    pointsInPolygonVector.clear();
    int32 Vertex = 0;
    for (int32 z = 0; z < MAP_W; z++) {
        for (int32 x = 0; x < MAP_W; x++) {
            Vertex = z * MAP_W + x;
            tmp_dem_point.x = g_terrain [Vertex][0];
            tmp_dem_point.y = g_terrain [Vertex][2];
            int32 inPolygonFlag = tmp_ppr.InPolygon(tmp_polygon, tmp_dem_point);
            if (inPolygonFlag == 0) {  // 点在多边形内
                Point3 tmp_point3;
                tmp_point3._x = g_terrain [Vertex][0];
                tmp_point3._y = g_terrain [Vertex][1];
                tmp_point3._z = g_terrain [Vertex][2];
                pointsInPolygonVector.push_back(tmp_point3);
                inPolygonArrayFlag[x][z] = 1;
            } else {
                inPolygonArrayFlag[x][z] = 0;
            }
        }
    }
    return 0;
}


// 找出所有包含在多边形内的三角形(包括完整三角形和经过局部三角化的三角形)
int32 CMy3DSymbolLibNewView::FindAllTrianglesInPolygon(Area_4& m_area4) {  // NOLINT
    FindAllPointsInPolygon(m_area4);
    // 1.多边形内完整的三角形
    m_area4.TrianglesInPolygonVecotr.clear();
    FindTriangles_3_point_inPolygon(m_area4);
    // 2.经过局部三角化的三角形
    m_area4.LocalTrianglesVecotr1.clear();
    FindTriangles_1_point_inPolygon(m_area4);
    m_area4.LocalTrianglesVecotr2.clear();
    FindTriangles_2_point_inPolygon(m_area4);
    // 2.1 多边形顶点处
    m_area4.LocalTrianglesVecotr1_1.clear();
    m_area4.LocalTrianglesVecotr2_1.clear();
    m_area4.LocalTrianglesVecotr_last.clear();
    FindTriangles_polygon_has_vertex_in_triangle(m_area4);
    return 0;
}



// 有3个点在多边形形内的三角形
int32 CMy3DSymbolLibNewView::FindTriangles_3_point_inPolygon(Area_4& _area4) {  // NOLINT
    int32 Vertex = 0;
    for (int32 z = 0; z < MAP_W - 1; z++) {
        for (int32 x = 0; x < MAP_W - 1; x++) {
            Vertex = z * MAP_W + x;
            Triangle tmp_triangle;
            // 3个点都在多边形内
            if (inPolygonArrayFlag[x][z] == 1 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 1) {
                Vertex = z * MAP_W + x;
                tmp_triangle.pt1._x = g_terrain [Vertex][0];
                tmp_triangle.pt1._y = g_terrain [Vertex][1];
                tmp_triangle.pt1._z = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + x;
                tmp_triangle.pt2._x = g_terrain [Vertex][0];
                tmp_triangle.pt2._y = g_terrain [Vertex][1];
                tmp_triangle.pt2._z = g_terrain [Vertex][2];
                Vertex = z * MAP_W + (x + 1);
                tmp_triangle.pt3._x = g_terrain [Vertex][0];
                tmp_triangle.pt3._y = g_terrain [Vertex][1];
                tmp_triangle.pt3._z = g_terrain [Vertex][2];
                _area4.TrianglesInPolygonVecotr.push_back(tmp_triangle);
            }
            // 3个点都在多边形内
            if (inPolygonArrayFlag[x + 1][z] == 1 && inPolygonArrayFlag[x + 1][z + 1] == 1  && inPolygonArrayFlag[x][z + 1] == 1) {
                Vertex = z * MAP_W + (x + 1);
                tmp_triangle.pt1._x = g_terrain [Vertex][0];
                tmp_triangle.pt1._y = g_terrain [Vertex][1];
                tmp_triangle.pt1._z = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_triangle.pt2._x = g_terrain [Vertex][0];
                tmp_triangle.pt2._y = g_terrain [Vertex][1];
                tmp_triangle.pt2._z = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + x;
                tmp_triangle.pt3._x = g_terrain [Vertex][0];
                tmp_triangle.pt3._y = g_terrain [Vertex][1];
                tmp_triangle.pt3._z = g_terrain [Vertex][2];
                _area4.TrianglesInPolygonVecotr.push_back(tmp_triangle);
            }
        }
    }
    return 0;
}


// 只有1个点在多边形形内的三角形(需重新三角化)
int32 CMy3DSymbolLibNewView::FindTriangles_1_point_inPolygon(Area_4& m_area4) {  // NOLINT
    {
        int32 Vertex;
        for (int32 z = 0; z < MAP_W - 1; z++) {
            for (int32 x = 0; x < MAP_W - 1; x++) {
                Vertex = z * MAP_W + x;
                Triangle tmp_triangle;
                // 三角形只有1个点在多边形内
                if (inPolygonArrayFlag[x][z] == 1 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 0) {
                    Vertex = (z) * MAP_W + (x);
                    tmp_triangle.pt1._x = g_terrain [Vertex][0];
                    tmp_triangle.pt1._y = g_terrain [Vertex][1];
                    tmp_triangle.pt1._z = g_terrain [Vertex][2];
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    Find_triangles_1_line_2_JD(m_area4, tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);
                }
                if (inPolygonArrayFlag[x][z] == 0 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 0) {
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_triangle.pt1._x = g_terrain [Vertex][0];
                    tmp_triangle.pt1._y = g_terrain [Vertex][1];
                    tmp_triangle.pt1._z = g_terrain [Vertex][2];
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    Find_triangles_1_line_2_JD(m_area4, tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);
                }
                // 三角形只有1个点在多边形内
                if (inPolygonArrayFlag[x][z] == 0 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 1) {
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_triangle.pt1._x = g_terrain [Vertex][0];
                    tmp_triangle.pt1._y = g_terrain [Vertex][1];
                    tmp_triangle.pt1._z = g_terrain [Vertex][2];
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    Find_triangles_1_line_2_JD(m_area4, tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);
                }
                // ==========================================================================================
                // 三角形只有1个点在多边形内
                if (inPolygonArrayFlag[x + 1][z + 1] == 1 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 0) {
                    Vertex = (z + 1) * MAP_W + (x + 1);
                    tmp_triangle.pt1._x = g_terrain [Vertex][0];
                    tmp_triangle.pt1._y = g_terrain [Vertex][1];
                    tmp_triangle.pt1._z = g_terrain [Vertex][2];
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    Find_triangles_1_line_2_JD(m_area4, tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);
                }
                if (inPolygonArrayFlag[x + 1][z + 1] == 0 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 0) {
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_triangle.pt1._x = g_terrain [Vertex][0];
                    tmp_triangle.pt1._y = g_terrain [Vertex][1];
                    tmp_triangle.pt1._z = g_terrain [Vertex][2];
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x + 1);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    Find_triangles_1_line_2_JD(m_area4, tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);
                }
                // 三角形只有1个点在多边形内
                if (inPolygonArrayFlag[x + 1][z + 1] == 0 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 1) {
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_triangle.pt1._x = g_terrain [Vertex][0];
                    tmp_triangle.pt1._y = g_terrain [Vertex][1];
                    tmp_triangle.pt1._z = g_terrain [Vertex][2];
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    Find_triangles_1_line_2_JD(m_area4, tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);
                }
            }
        }
    }
    return 0;
}


// 只有2个点在多边形形内的三角形(需重新三角化)
int32 CMy3DSymbolLibNewView::FindTriangles_2_point_inPolygon(Area_4& m_area4) {
    {
        int32 Vertex;
        for (int32 z = 0; z < MAP_W - 1; z++) {
            for (int32 x = 0; x < MAP_W - 1; x++) {
                Vertex = z * MAP_W + x;
                Triangle tmp_triangle1;
                Triangle tmp_triangle2;
                // ok1
                if (inPolygonArrayFlag[x][z] == 1 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 0) {
                    Vertex = (z) * MAP_W + (x);
                    tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                    tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                    tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                    tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                    tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                    tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_triangle1.pt2._x = g_terrain [Vertex][0];
                    tmp_triangle1.pt2._y = g_terrain [Vertex][1];
                    tmp_triangle1.pt2._z = g_terrain [Vertex][2];
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    // Find_triangles_1_line_2_JD(tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);
                    PPR_Point tmp_point3, tmp_point4;  // 多边形边的端点
                    PPR_Point JD1, JD2;
                    // CString msg;
                    bool intersectFlag1 = false;
                    bool intersectFlag2 = false;
                    int16 tmp_cout = 4;
                    while (tmp_cout > 0) {
                        if (4 == tmp_cout) {
                            tmp_point3.x = m_area4.pt1._x;
                            tmp_point3.y = m_area4.pt1._z;
                            tmp_point4.x = m_area4.pt2._x;
                            tmp_point4.y = m_area4.pt2._z;
                        } else if (3 == tmp_cout) {
                            tmp_point3.x = m_area4.pt2._x;
                            tmp_point3.y = m_area4.pt2._z;
                            tmp_point4.x = m_area4.pt3._x;
                            tmp_point4.y = m_area4.pt3._z;
                        } else if (2 == tmp_cout) {
                            tmp_point3.x = m_area4.pt3._x;
                            tmp_point3.y = m_area4.pt3._z;
                            tmp_point4.x = m_area4.pt4._x;
                            tmp_point4.y = m_area4.pt4._z;
                        } else if (1 == tmp_cout) {
                            tmp_point3.x = m_area4.pt4._x;
                            tmp_point3.y = m_area4.pt4._z;
                            tmp_point4.x = m_area4.pt1._x;
                            tmp_point4.y = m_area4.pt1._z;
                        }
                        intersectFlag1 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                        intersectFlag2 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                        if (intersectFlag1 && intersectFlag2) {
                            JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                            JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                            double tmp_min_y = (tmp_triangle1.pt1._z < tmp_triangle1.pt2._z) ? tmp_triangle1.pt1._z : tmp_triangle1.pt2._z;
                            double tmp_max_y = (tmp_triangle1.pt1._z > tmp_triangle1.pt2._z) ? tmp_triangle1.pt1._z : tmp_triangle1.pt2._z;
                            double tmp_min_x = (tmp_triangle1.pt1._x < tmp_point1.x) ? tmp_triangle1.pt1._z : tmp_point1.x;
                            double tmp_max_x = (tmp_triangle1.pt1._x > tmp_point1.x) ? tmp_triangle1.pt1._z : tmp_point1.x;
                            bool b11 = (JD1.y > (tmp_min_y + 0.01)) && (JD1.y < (tmp_max_y - 0.01));
                            bool b21 = (JD2.y > (tmp_min_y + 0.01)) && (JD2.y < (tmp_max_y - 0.01));
                            bool b12 = (JD1.x > (tmp_min_x + 0.01)) && (JD1.x < (tmp_max_x - 0.01));
                            bool b22 = (JD2.x > (tmp_min_x + 0.01)) && (JD2.x < (tmp_max_x - 0.01));
                            if (b11 && b12) {
                                tmp_triangle1.pt3._x = JD1.x;
                                tmp_triangle1.pt3._y = GetHeight(JD1.x, JD1.y);
                                tmp_triangle1.pt3._z = JD1.y;
                            } else if (b21 && b22) {
                                tmp_triangle1.pt3._x = JD2.x;
                                tmp_triangle1.pt3._y = GetHeight(JD2.x, JD2.y);
                                tmp_triangle1.pt3._z = JD2.y;
                            } else {
                                AfxMessageBox("warning: ");
                            }
                            tmp_triangle2.pt2._x = JD1.x;
                            tmp_triangle2.pt2._y = GetHeight(JD1.x, JD1.y);
                            tmp_triangle2.pt2._z = JD1.y;
                            tmp_triangle2.pt3._x = JD2.x;
                            tmp_triangle2.pt3._y = GetHeight(JD2.x, JD2.y);
                            tmp_triangle2.pt3._z = JD2.y;
                            // AfxMessageBox("1");
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle1);
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle2);
                        }
                        tmp_cout--;
                    }
                }
                // ok2
                if (inPolygonArrayFlag[x][z] == 1 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 1) {
                    Vertex = (z) * MAP_W + (x);
                    tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                    tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                    tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                    tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                    tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                    tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_triangle1.pt2._x = g_terrain [Vertex][0];
                    tmp_triangle1.pt2._y = g_terrain [Vertex][1];
                    tmp_triangle1.pt2._z = g_terrain [Vertex][2];
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    // Find_triangles_1_line_2_JD(tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);
                    PPR_Point tmp_point3, tmp_point4;  // 多边形边的端点
                    PPR_Point JD1, JD2;
                    CString msg;
                    bool intersectFlag1 = false;
                    bool intersectFlag2 = false;
                    int32 tmp_cout = 4;
                    while (tmp_cout > 0) {
                        if (4 == tmp_cout) {
                            tmp_point3.x = m_area4.pt1._x;
                            tmp_point3.y = m_area4.pt1._z;
                            tmp_point4.x = m_area4.pt2._x;
                            tmp_point4.y = m_area4.pt2._z;
                        } else if (3 == tmp_cout) {
                            tmp_point3.x = m_area4.pt2._x;
                            tmp_point3.y = m_area4.pt2._z;
                            tmp_point4.x = m_area4.pt3._x;
                            tmp_point4.y = m_area4.pt3._z;
                        } else if (2 == tmp_cout) {
                            tmp_point3.x = m_area4.pt3._x;
                            tmp_point3.y = m_area4.pt3._z;
                            tmp_point4.x = m_area4.pt4._x;
                            tmp_point4.y = m_area4.pt4._z;
                        } else if (1 == tmp_cout) {
                            tmp_point3.x = m_area4.pt4._x;
                            tmp_point3.y = m_area4.pt4._z;
                            tmp_point4.x = m_area4.pt1._x;
                            tmp_point4.y = m_area4.pt1._z;
                        }
                        intersectFlag1 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                        intersectFlag2 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                        if (intersectFlag1 && intersectFlag2) {
                            JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                            JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                            double tmp_min_y = (tmp_triangle1.pt1._z < tmp_point1.y) ? tmp_triangle1.pt1._z : tmp_point1.y;
                            double tmp_max_y = (tmp_triangle1.pt1._z > tmp_point1.y) ? tmp_triangle1.pt1._z : tmp_point1.y;
                            double tmp_min_x = (tmp_triangle1.pt1._x < tmp_triangle1.pt2._x) ? tmp_triangle1.pt1._x : tmp_triangle1.pt2._x;
                            double tmp_max_x = (tmp_triangle1.pt1._x > tmp_triangle1.pt2._x) ? tmp_triangle1.pt1._x : tmp_triangle1.pt2._x;
                            bool b11 = (JD1.y > (tmp_min_y + 0.01)) && (JD1.y < (tmp_max_y - 0.01));
                            bool b21 = (JD2.y > (tmp_min_y + 0.01)) && (JD2.y < (tmp_max_y - 0.01));
                            bool b12 = (JD1.x > (tmp_min_x + 0.01)) && (JD1.x < (tmp_max_x - 0.01));
                            bool b22 = (JD2.x > (tmp_min_x + 0.01)) && (JD2.x < (tmp_max_x - 0.01));
                            if (b11 && b12) {
                                tmp_triangle1.pt3._x = JD1.x;
                                tmp_triangle1.pt3._y = GetHeight(JD1.x, JD1.y);
                                tmp_triangle1.pt3._z = JD1.y;
                            } else if (b21 && b22) {
                                tmp_triangle1.pt3._x = JD2.x;
                                tmp_triangle1.pt3._y = GetHeight(JD2.x, JD2.y);
                                tmp_triangle1.pt3._z = JD2.y;
                            } else {
                                AfxMessageBox("warning: ");
                                // AfxMessageBox(__LINE__);
                            }
                            tmp_triangle2.pt2._x = JD1.x;
                            tmp_triangle2.pt2._y = GetHeight(JD1.x, JD1.y);
                            tmp_triangle2.pt2._z = JD1.y;
                            tmp_triangle2.pt3._x = JD2.x;
                            tmp_triangle2.pt3._y = GetHeight(JD2.x, JD2.y);
                            tmp_triangle2.pt3._z = JD2.y;
                            // AfxMessageBox("2");
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle1);
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle2);
                        }
                        tmp_cout--;
                    }
                }
                // ok3
                if (inPolygonArrayFlag[x][z] == 0 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 1) {
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                    tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                    tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_triangle1.pt2._x = g_terrain [Vertex][0];
                    tmp_triangle1.pt2._y = g_terrain [Vertex][1];
                    tmp_triangle1.pt2._z = g_terrain [Vertex][2];
                    tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                    tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                    tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
                    Vertex = (z) * MAP_W + (x);
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    // Find_triangles_1_line_2_JD(tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);
                    PPR_Point tmp_point3, tmp_point4;  // 多边形边的端点
                    PPR_Point JD1, JD2;
                    CString msg;
                    bool intersectFlag1 = false;
                    bool intersectFlag2 = false;
                    int32 tmp_cout = 4;
                    while (tmp_cout > 0) {
                        if (4 == tmp_cout) {
                            tmp_point3.x = m_area4.pt1._x;
                            tmp_point3.y = m_area4.pt1._z;
                            tmp_point4.x = m_area4.pt2._x;
                            tmp_point4.y = m_area4.pt2._z;
                        } else if (3 == tmp_cout) {
                            tmp_point3.x = m_area4.pt2._x;
                            tmp_point3.y = m_area4.pt2._z;
                            tmp_point4.x = m_area4.pt3._x;
                            tmp_point4.y = m_area4.pt3._z;
                        } else if (2 == tmp_cout) {
                            tmp_point3.x = m_area4.pt3._x;
                            tmp_point3.y = m_area4.pt3._z;
                            tmp_point4.x = m_area4.pt4._x;
                            tmp_point4.y = m_area4.pt4._z;
                        } else if (1 == tmp_cout) {
                            tmp_point3.x = m_area4.pt4._x;
                            tmp_point3.y = m_area4.pt4._z;
                            tmp_point4.x = m_area4.pt1._x;
                            tmp_point4.y = m_area4.pt1._z;
                        }
                        intersectFlag1 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                        intersectFlag2 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                        if (intersectFlag1 && intersectFlag2) {
                            JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                            JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                            double len1 = (tmp_triangle1.pt1._x - JD1.x) * (tmp_triangle1.pt1._x - JD1.x) + (tmp_triangle1.pt1._z - JD1.y) * (tmp_triangle1.pt1._z - JD1.y);
                            double len2 = (tmp_triangle1.pt1._x - JD2.x) * (tmp_triangle1.pt1._x - JD2.x) + (tmp_triangle1.pt1._z - JD2.y) * (tmp_triangle1.pt1._z - JD2.y);
                            if (len1 < len2) {
                                tmp_triangle1.pt3._x = JD1.x;
                                tmp_triangle1.pt3._y = GetHeight(JD1.x, JD1.y);
                                tmp_triangle1.pt3._z = JD1.y;
                            } else if (len1 > len2) {
                                tmp_triangle1.pt3._x = JD2.x;
                                tmp_triangle1.pt3._y = GetHeight(JD2.x, JD2.y);
                                tmp_triangle1.pt3._z = JD2.y;
                            } else {
                                AfxMessageBox("warning");
                            }
                            tmp_triangle2.pt2._x = JD1.x;
                            tmp_triangle2.pt2._y = GetHeight(JD1.x, JD1.y);
                            tmp_triangle2.pt2._z = JD1.y;
                            tmp_triangle2.pt3._x = JD2.x;
                            tmp_triangle2.pt3._y = GetHeight(JD2.x, JD2.y);
                            tmp_triangle2.pt3._z = JD2.y;
                            // AfxMessageBox("3");
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle1);
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle2);
                        }
                        tmp_cout--;
                    }
                }
                // ========================================================================================
                // ok - 1
                if (inPolygonArrayFlag[x + 1][z + 1] == 1 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 0) {
                    Vertex = (z + 1) * MAP_W + (x + 1);
                    tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                    tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                    tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                    tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                    tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                    tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_triangle1.pt2._x = g_terrain [Vertex][0];
                    tmp_triangle1.pt2._y = g_terrain [Vertex][1];
                    tmp_triangle1.pt2._z = g_terrain [Vertex][2];
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    // Find_triangles_1_line_2_JD(tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);
                    PPR_Point tmp_point3, tmp_point4;  // 多边形边的端点
                    PPR_Point JD1, JD2;
                    CString msg;
                    bool intersectFlag1 = false;
                    bool intersectFlag2 = false;
                    int32 tmp_cout = 4;
                    while (tmp_cout > 0) {
                        if (4 == tmp_cout) {
                            tmp_point3.x = m_area4.pt1._x;
                            tmp_point3.y = m_area4.pt1._z;
                            tmp_point4.x = m_area4.pt2._x;
                            tmp_point4.y = m_area4.pt2._z;
                        } else if (3 == tmp_cout) {
                            tmp_point3.x = m_area4.pt2._x;
                            tmp_point3.y = m_area4.pt2._z;
                            tmp_point4.x = m_area4.pt3._x;
                            tmp_point4.y = m_area4.pt3._z;
                        } else if (2 == tmp_cout) {
                            tmp_point3.x = m_area4.pt3._x;
                            tmp_point3.y = m_area4.pt3._z;
                            tmp_point4.x = m_area4.pt4._x;
                            tmp_point4.y = m_area4.pt4._z;
                        } else if (1 == tmp_cout) {
                            tmp_point3.x = m_area4.pt4._x;
                            tmp_point3.y = m_area4.pt4._z;
                            tmp_point4.x = m_area4.pt1._x;
                            tmp_point4.y = m_area4.pt1._z;
                        }
                        intersectFlag1 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                        intersectFlag2 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                        if (intersectFlag1 && intersectFlag2) {
                            JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                            JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                            double tmp_min_x = (tmp_triangle1.pt1._x < tmp_triangle1.pt2._x) ? tmp_triangle1.pt1._x : tmp_triangle1.pt2._x;
                            double tmp_max_x = (tmp_triangle1.pt1._x > tmp_triangle1.pt2._x) ? tmp_triangle1.pt1._x : tmp_triangle1.pt2._x;
                            double tmp_min_y = (tmp_triangle1.pt1._z < tmp_point1.y) ? tmp_triangle1.pt1._z : tmp_point1.y;
                            double tmp_max_y = (tmp_triangle1.pt1._z > tmp_point1.y) ? tmp_triangle1.pt1._z : tmp_point1.y;
                            bool b11 = (JD1.y > (tmp_min_y + 0.01)) && (JD1.y < (tmp_max_y - 0.01));
                            bool b21 = (JD2.y > (tmp_min_y + 0.01)) && (JD2.y < (tmp_max_y - 0.01));
                            bool b12 = (JD1.x > (tmp_min_x + 0.01)) && (JD1.x < (tmp_max_x - 0.01));
                            bool b22 = (JD2.x > (tmp_min_x + 0.01)) && (JD2.x < (tmp_max_x - 0.01));
                            if (b11 && b12) {
                                tmp_triangle1.pt3._x = JD1.x;
                                tmp_triangle1.pt3._y = GetHeight(JD1.x, JD1.y);
                                tmp_triangle1.pt3._z = JD1.y;
                            } else if (b21 && b22) {
                                tmp_triangle1.pt3._x = JD2.x;
                                tmp_triangle1.pt3._y = GetHeight(JD2.x, JD2.y);
                                tmp_triangle1.pt3._z = JD2.y;
                            } else {
                                AfxMessageBox("warning... ");
                                // AfxMessageBox(__LINE__);
                            }
                            tmp_triangle2.pt2._x = JD1.x;
                            tmp_triangle2.pt2._y = GetHeight(JD1.x, JD1.y);
                            tmp_triangle2.pt2._z = JD1.y;
                            tmp_triangle2.pt3._x = JD2.x;
                            tmp_triangle2.pt3._y = GetHeight(JD2.x, JD2.y);
                            tmp_triangle2.pt3._z = JD2.y;
                            // AfxMessageBox(" - 1");
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle1);
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle2);
                        }
                        tmp_cout--;
                    }
                }
                // ok - 2
                if (inPolygonArrayFlag[x + 1][z + 1] == 1 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 1) {
                    Vertex = (z + 1) * MAP_W + (x + 1);
                    tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                    tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                    tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                    tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                    tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                    tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_triangle1.pt2._x = g_terrain [Vertex][0];
                    tmp_triangle1.pt2._y = g_terrain [Vertex][1];
                    tmp_triangle1.pt2._z = g_terrain [Vertex][2];
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    // Find_triangles_1_line_2_JD(tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);
                    PPR_Point tmp_point3, tmp_point4;  // 多边形边的端点
                    PPR_Point JD1, JD2;
                    CString msg;
                    bool intersectFlag1 = false;
                    bool intersectFlag2 = false;
                    int32 tmp_cout = 4;
                    while (tmp_cout > 0) {
                        if (4 == tmp_cout) {
                            tmp_point3.x = m_area4.pt1._x;
                            tmp_point3.y = m_area4.pt1._z;
                            tmp_point4.x = m_area4.pt2._x;
                            tmp_point4.y = m_area4.pt2._z;
                        } else if (3 == tmp_cout) {
                            tmp_point3.x = m_area4.pt2._x;
                            tmp_point3.y = m_area4.pt2._z;
                            tmp_point4.x = m_area4.pt3._x;
                            tmp_point4.y = m_area4.pt3._z;
                        } else if (2 == tmp_cout) {
                            tmp_point3.x = m_area4.pt3._x;
                            tmp_point3.y = m_area4.pt3._z;
                            tmp_point4.x = m_area4.pt4._x;
                            tmp_point4.y = m_area4.pt4._z;
                        } else if (1 == tmp_cout) {
                            tmp_point3.x = m_area4.pt4._x;
                            tmp_point3.y = m_area4.pt4._z;
                            tmp_point4.x = m_area4.pt1._x;
                            tmp_point4.y = m_area4.pt1._z;
                        }
                        intersectFlag1 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                        intersectFlag2 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                        if (intersectFlag1 && intersectFlag2) {
                            JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                            JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                            double tmp_min_x = (tmp_triangle1.pt1._x < tmp_point1.x) ? tmp_triangle1.pt1._x : tmp_point1.x;
                            double tmp_max_x = (tmp_triangle1.pt1._x > tmp_point1.x) ? tmp_triangle1.pt1._x : tmp_point1.x;
                            double tmp_min_y = (tmp_triangle1.pt1._z < tmp_triangle1.pt2._z) ? tmp_triangle1.pt1._z : tmp_triangle1.pt2._z;
                            double tmp_max_y = (tmp_triangle1.pt1._z > tmp_triangle1.pt2._z) ? tmp_triangle1.pt1._z : tmp_triangle1.pt2._z;
                            bool b11 = (JD1.y > (tmp_min_y + 0.01)) && (JD1.y < (tmp_max_y - 0.01));
                            bool b21 = (JD2.y > (tmp_min_y + 0.01)) && (JD2.y < (tmp_max_y - 0.01));
                            bool b12 = (JD1.x > (tmp_min_x + 0.01)) && (JD1.x < (tmp_max_x - 0.01));
                            bool b22 = (JD2.x > (tmp_min_x + 0.01)) && (JD2.x < (tmp_max_x - 0.01));
                            if (b11 && b12) {
                                tmp_triangle1.pt3._x = JD1.x;
                                tmp_triangle1.pt3._y = GetHeight(JD1.x, JD1.y);
                                tmp_triangle1.pt3._z = JD1.y;
                            } else if (b21 && b22) {
                                tmp_triangle1.pt3._x = JD2.x;
                                tmp_triangle1.pt3._y = GetHeight(JD2.x, JD2.y);
                                tmp_triangle1.pt3._z = JD2.y;
                            } else {
                                AfxMessageBox("warning... ");
                                // AfxMessageBox(__LINE__);
                            }
                            tmp_triangle2.pt2._x = JD1.x;
                            tmp_triangle2.pt2._y = GetHeight(JD1.x, JD1.y);
                            tmp_triangle2.pt2._z = JD1.y;
                            tmp_triangle2.pt3._x = JD2.x;
                            tmp_triangle2.pt3._y = GetHeight(JD2.x, JD2.y);
                            tmp_triangle2.pt3._z = JD2.y;
                            // AfxMessageBox(" - 2");
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle1);
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle2);
                        }
                        tmp_cout--;
                    }
                }
                // ok - 3
                if (inPolygonArrayFlag[x + 1][z + 1] == 0 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 1) {
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                    tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                    tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_triangle1.pt2._x = g_terrain [Vertex][0];
                    tmp_triangle1.pt2._y = g_terrain [Vertex][1];
                    tmp_triangle1.pt2._z = g_terrain [Vertex][2];
                    tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                    tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                    tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                    // 求多边形边界与三角形边的交点
                    CPointPolygonRelationship tmp_PPR;
                    PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
                    Vertex = (z + 1) * MAP_W + (x + 1);
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    // Find_triangles_1_line_2_JD(tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);
                    PPR_Point tmp_point3, tmp_point4;  // 多边形边的端点
                    PPR_Point JD1, JD2;
                    CString msg;
                    bool intersectFlag1 = false;
                    bool intersectFlag2 = false;
                    int32 tmp_cout = 4;
                    while (tmp_cout > 0) {
                        if (4 == tmp_cout) {
                            tmp_point3.x = m_area4.pt1._x;
                            tmp_point3.y = m_area4.pt1._z;
                            tmp_point4.x = m_area4.pt2._x;
                            tmp_point4.y = m_area4.pt2._z;
                        } else if (3 == tmp_cout) {
                            tmp_point3.x = m_area4.pt2._x;
                            tmp_point3.y = m_area4.pt2._z;
                            tmp_point4.x = m_area4.pt3._x;
                            tmp_point4.y = m_area4.pt3._z;
                        } else if (2 == tmp_cout) {
                            tmp_point3.x = m_area4.pt3._x;
                            tmp_point3.y = m_area4.pt3._z;
                            tmp_point4.x = m_area4.pt4._x;
                            tmp_point4.y = m_area4.pt4._z;
                        } else if (1 == tmp_cout) {
                            tmp_point3.x = m_area4.pt4._x;
                            tmp_point3.y = m_area4.pt4._z;
                            tmp_point4.x = m_area4.pt1._x;
                            tmp_point4.y = m_area4.pt1._z;
                        }
                        intersectFlag1 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                        intersectFlag2 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                        if (intersectFlag1 && intersectFlag2) {
                            JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
                            JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
                            double len1 = (tmp_triangle1.pt1._x - JD1.x) * (tmp_triangle1.pt1._x - JD1.x) + (tmp_triangle1.pt1._z - JD1.y) * (tmp_triangle1.pt1._z - JD1.y);
                            double len2 = (tmp_triangle1.pt1._x - JD2.x) * (tmp_triangle1.pt1._x - JD2.x) + (tmp_triangle1.pt1._z - JD2.y) * (tmp_triangle1.pt1._z - JD2.y);
                            if (len1 < len2) {
                                tmp_triangle1.pt3._x = JD1.x;
                                tmp_triangle1.pt3._y = GetHeight(JD1.x, JD1.y);
                                tmp_triangle1.pt3._z = JD1.y;
                            } else if (len1 > len2) {
                                tmp_triangle1.pt3._x = JD2.x;
                                tmp_triangle1.pt3._y = GetHeight(JD2.x, JD2.y);
                                tmp_triangle1.pt3._z = JD2.y;
                            } else {
                                AfxMessageBox("...warning!");
                            }
                            tmp_triangle2.pt2._x = JD1.x;
                            tmp_triangle2.pt2._y = GetHeight(JD1.x, JD1.y);
                            tmp_triangle2.pt2._z = JD1.y;
                            tmp_triangle2.pt3._x = JD2.x;
                            tmp_triangle2.pt3._y = GetHeight(JD2.x, JD2.y);
                            tmp_triangle2.pt3._z = JD2.y;
                            // AfxMessageBox(" - 3");
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle1);
                            m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle2);
                        }
                        tmp_cout--;
                    }
                }
            }
        }
    }
    return 0;
}



// 找出符合条件的三角形(三角形只有1个点在多边形内, 且多边形的某条边与三角形有2个交点)
void CMy3DSymbolLibNewView::Find_triangles_1_line_2_JD(Area_4& m_area4, Triangle& tmp_triangle, CPointPolygonRelationship& tmp_PPR, PPR_Point& tmp_point1, PPR_Point& tmp_point21, PPR_Point& tmp_point22) {  // NOLINT
    PPR_Point tmp_point3, tmp_point4;  // 多边形边的端点
    PPR_Point JD1, JD2;
    // CString msg;
    bool intersectFlag1 = false;
    bool intersectFlag2 = false;
    int16 tmp_cout = 4;
    while (tmp_cout > 0) {
        if (4 == tmp_cout) {
            tmp_point3.x = m_area4.pt1._x;
            tmp_point3.y = m_area4.pt1._z;
            tmp_point4.x = m_area4.pt2._x;
            tmp_point4.y = m_area4.pt2._z;
        } else if (3 == tmp_cout) {
            tmp_point3.x = m_area4.pt2._x;
            tmp_point3.y = m_area4.pt2._z;
            tmp_point4.x = m_area4.pt3._x;
            tmp_point4.y = m_area4.pt3._z;
        } else if (2 == tmp_cout) {
            tmp_point3.x = m_area4.pt3._x;
            tmp_point3.y = m_area4.pt3._z;
            tmp_point4.x = m_area4.pt4._x;
            tmp_point4.y = m_area4.pt4._z;
        } else if (1 == tmp_cout) {
            tmp_point3.x = m_area4.pt4._x;
            tmp_point3.y = m_area4.pt4._z;
            tmp_point4.x = m_area4.pt1._x;
            tmp_point4.y = m_area4.pt1._z;
        }
        intersectFlag1 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
        intersectFlag2 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
        if (intersectFlag1 && intersectFlag2) {
            JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_point3, tmp_point4);
            JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_point3, tmp_point4);
            tmp_triangle.pt2._x = JD1.x;
            tmp_triangle.pt2._y = GetHeight(JD1.x, JD1.y);
            tmp_triangle.pt2._z = JD1.y;
            tmp_triangle.pt3._x = JD2.x;
            tmp_triangle.pt3._y = GetHeight(JD2.x, JD2.y);
            tmp_triangle.pt3._z = JD2.y;
            m_area4.LocalTrianglesVecotr1.push_back(tmp_triangle);
        }
        tmp_cout--;
    }
}



// 多边形顶点处的三角形
void CMy3DSymbolLibNewView::FindTriangles_polygon_has_vertex_in_triangle(Area_4& m_area4) {  // NOLINT
    int32 Vertex;
    for (int32 z = 0; z < MAP_W - 1; z++) {
        for (int32 x = 0; x < MAP_W - 1; x++) {
            Vertex = z * MAP_W + x;
            Triangle tmp_triangle1;
            Triangle tmp_triangle2;
            PPR_Point tmp_point1, tmp_point21, tmp_point22;  // 三角形三点
            /************************************************************************/
            /*       三角形只有1个点在多边形内                                          */
            /************************************************************************/
            // ------------------------------------
            if (inPolygonArrayFlag[x][z] == 0 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 1) {
                Vertex = (z) * MAP_W + (x + 1);
                tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_1_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_point1, tmp_point21, tmp_point22);
            }
            // 三角形只有1个点在多边形内
            if (inPolygonArrayFlag[x][z] == 0 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 0) {
                Vertex = (z + 1) * MAP_W + (x);
                tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_1_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_point1, tmp_point21, tmp_point22);
            }
            // 三角形只有1个点在多边形内
            if (inPolygonArrayFlag[x][z] == 1 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 0) {
                Vertex = (z) * MAP_W + (x);
                tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                // 求多边形边界与三角形边的交点
                Vertex = (z) * MAP_W + (x);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_1_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_point1, tmp_point21, tmp_point22);
            }
            // ------------------------------------
            // 三角形只有1个点在多边形内
            if (inPolygonArrayFlag[x + 1][z + 1] == 0 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 1) {
                Vertex = (z) * MAP_W + (x + 1);
                tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_1_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_point1, tmp_point21, tmp_point22);
            }
            // 三角形只有1个点在多边形内
            if (inPolygonArrayFlag[x + 1][z + 1] == 0 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 0) {
                Vertex = (z + 1) * MAP_W + (x);
                tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_1_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_point1, tmp_point21, tmp_point22);
            }
            // 三角形只有1个点在多边形内
            if (inPolygonArrayFlag[x + 1][z + 1] == 1 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 0) {
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                // 求多边形边界与三角形边的交点
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_1_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_point1, tmp_point21, tmp_point22);
            }
            /************************************************************************/
            /*       三角形只有2个点在多边形内                                          */
            /************************************************************************/
            // 三角化将后产生3个小三角形
            Triangle tmp_triangle3;
            // ------------------------------------
            // 1-1
            if (inPolygonArrayFlag[x][z] == 1 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 0) {
                Vertex = (z + 1) * MAP_W + (x);
                tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                tmp_triangle3.pt1._x = g_terrain [Vertex][0];
                tmp_triangle3.pt1._y = g_terrain [Vertex][1];
                tmp_triangle3.pt1._z = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x);
                tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                tmp_triangle3.pt2._x = g_terrain [Vertex][0];
                tmp_triangle3.pt2._y = g_terrain [Vertex][1];
                tmp_triangle3.pt2._z = g_terrain [Vertex][2];
                // 此时 tmp_point1应为在多边形外的一点
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_2_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_point1, tmp_point21, tmp_point22);
            }
            // 1-2
            if (inPolygonArrayFlag[x][z] == 1 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 1) {
                Vertex = (z) * MAP_W + (x + 1);
                tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                tmp_triangle3.pt1._x = g_terrain [Vertex][0];
                tmp_triangle3.pt1._y = g_terrain [Vertex][1];
                tmp_triangle3.pt1._z = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x);
                tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                tmp_triangle3.pt2._x = g_terrain [Vertex][0];
                tmp_triangle3.pt2._y = g_terrain [Vertex][1];
                tmp_triangle3.pt2._z = g_terrain [Vertex][2];
                // 此时 tmp_point1应为在多边形外的一点
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_2_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_point1, tmp_point21, tmp_point22);
            }
            // 1-3
            if (inPolygonArrayFlag[x][z] == 0 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 1) {
                Vertex = (z) * MAP_W + (x + 1);
                tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                tmp_triangle3.pt1._x = g_terrain [Vertex][0];
                tmp_triangle3.pt1._y = g_terrain [Vertex][1];
                tmp_triangle3.pt1._z = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                tmp_triangle3.pt2._x = g_terrain [Vertex][0];
                tmp_triangle3.pt2._y = g_terrain [Vertex][1];
                tmp_triangle3.pt2._z = g_terrain [Vertex][2];
                // 此时 tmp_point1应为在多边形外的一点
                Vertex = (z) * MAP_W + (x);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_2_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_point1, tmp_point21, tmp_point22);
            }
            // 2-1
            if (inPolygonArrayFlag[x + 1][z + 1] == 1 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 0) {
                Vertex = (z + 1) * MAP_W + (x);
                tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                tmp_triangle3.pt1._x = g_terrain [Vertex][0];
                tmp_triangle3.pt1._y = g_terrain [Vertex][1];
                tmp_triangle3.pt1._z = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                tmp_triangle3.pt2._x = g_terrain [Vertex][0];
                tmp_triangle3.pt2._y = g_terrain [Vertex][1];
                tmp_triangle3.pt2._z = g_terrain [Vertex][2];
                // 此时 tmp_point1应为在多边形外的一点
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_2_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_point1, tmp_point21, tmp_point22);
            }
            // 2-2
            if (inPolygonArrayFlag[x + 1][z + 1] == 1 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 1) {
                Vertex = (z) * MAP_W + (x + 1);
                tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                tmp_triangle3.pt1._x = g_terrain [Vertex][0];
                tmp_triangle3.pt1._y = g_terrain [Vertex][1];
                tmp_triangle3.pt1._z = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                tmp_triangle3.pt2._x = g_terrain [Vertex][0];
                tmp_triangle3.pt2._y = g_terrain [Vertex][1];
                tmp_triangle3.pt2._z = g_terrain [Vertex][2];
                // 此时 tmp_point1应为在多边形外的一点
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_2_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_point1, tmp_point21, tmp_point22);
            }
            // 2-3
            if (inPolygonArrayFlag[x + 1][z + 1] == 0 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 1) {
                Vertex = (z) * MAP_W + (x + 1);
                tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                tmp_triangle3.pt1._x = g_terrain [Vertex][0];
                tmp_triangle3.pt1._y = g_terrain [Vertex][1];
                tmp_triangle3.pt1._z = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                tmp_triangle3.pt2._x = g_terrain [Vertex][0];
                tmp_triangle3.pt2._y = g_terrain [Vertex][1];
                tmp_triangle3.pt2._z = g_terrain [Vertex][2];
                // 此时 tmp_point1应为在多边形外的一点
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_2_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_point1, tmp_point21, tmp_point22);
            }
            /************************************************************************/
            /* 多边形的1个顶点在某个三角形中，但该三角形的3个顶点都在多边形外               */
            /************************************************************************/
            // 此时三角化后将产生4个三角形
            Triangle tmp_triangle4;
            // 1- 1
            if (inPolygonArrayFlag[x][z] == 1 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 0) {
                Vertex = (z) * MAP_W + (x);
                tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                tmp_triangle3.pt1._x = g_terrain [Vertex][0];
                tmp_triangle3.pt1._y = g_terrain [Vertex][1];
                tmp_triangle3.pt1._z = g_terrain [Vertex][2];
                // 三角形共斜边的对角三角形
                PPR_Point tmp_point0;
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_point0.x = g_terrain [Vertex][0];
                tmp_point0.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_last(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_triangle4, tmp_point0, tmp_point1, tmp_point21, tmp_point22);
            }
            // 1-2
            if (inPolygonArrayFlag[x][z] == 0 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 0) {
                Vertex = (z + 1) * MAP_W + (x);
                tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                tmp_triangle3.pt1._x = g_terrain [Vertex][0];
                tmp_triangle3.pt1._y = g_terrain [Vertex][1];
                tmp_triangle3.pt1._z = g_terrain [Vertex][2];
                // 对角三角形
                if (z >= 1) {
                    PPR_Point tmp_point0;
                    Vertex = (z - 1) * MAP_W + (x + 1);
                    tmp_point0.x = g_terrain [Vertex][0];
                    tmp_point0.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    FindTriangles_polygon_has_vertex_in_triangle_last(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_triangle4, tmp_point0, tmp_point1, tmp_point21, tmp_point22);
                }
            }
            // 1-3
            if (inPolygonArrayFlag[x][z] == 0 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 1) {
                Vertex = (z) * MAP_W + (x + 1);
                tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                tmp_triangle3.pt1._x = g_terrain [Vertex][0];
                tmp_triangle3.pt1._y = g_terrain [Vertex][1];
                tmp_triangle3.pt1._z = g_terrain [Vertex][2];
                // 对角三角形
                if (x >= 1) {
                    PPR_Point tmp_point0;
                    Vertex = (z + 1) * MAP_W + (x - 1);
                    tmp_point0.x = g_terrain [Vertex][0];
                    tmp_point0.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    FindTriangles_polygon_has_vertex_in_triangle_last(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_triangle4, tmp_point0, tmp_point1, tmp_point21, tmp_point22);
                }
            }
            // 2-1
            if (inPolygonArrayFlag[x + 1][z + 1] == 1 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 0) {
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                tmp_triangle3.pt1._x = g_terrain [Vertex][0];
                tmp_triangle3.pt1._y = g_terrain [Vertex][1];
                tmp_triangle3.pt1._z = g_terrain [Vertex][2];
                // 三角形共斜边的对角三角形
                PPR_Point tmp_point0;
                Vertex = (z) * MAP_W + (x);
                tmp_point0.x = g_terrain [Vertex][0];
                tmp_point0.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x + 1);
                tmp_point1.x = g_terrain [Vertex][0];
                tmp_point1.y = g_terrain [Vertex][2];
                Vertex = (z) * MAP_W + (x + 1);
                tmp_point21.x = g_terrain [Vertex][0];
                tmp_point21.y = g_terrain [Vertex][2];
                Vertex = (z + 1) * MAP_W + (x);
                tmp_point22.x = g_terrain [Vertex][0];
                tmp_point22.y = g_terrain [Vertex][2];
                FindTriangles_polygon_has_vertex_in_triangle_last(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_triangle4, tmp_point0, tmp_point1, tmp_point21, tmp_point22);
            }
            // 2-2
            if (inPolygonArrayFlag[x + 1][z + 1] == 0 && inPolygonArrayFlag[x][z + 1] == 1  && inPolygonArrayFlag[x + 1][z] == 0) {
                Vertex = (z + 1) * MAP_W + (x);
                tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                tmp_triangle3.pt1._x = g_terrain [Vertex][0];
                tmp_triangle3.pt1._y = g_terrain [Vertex][1];
                tmp_triangle3.pt1._z = g_terrain [Vertex][2];
                // 对角三角形
                if (x < MAP_W - 2) {
                    PPR_Point tmp_point0;
                    Vertex = (z) * MAP_W + (x + 2);
                    tmp_point0.x = g_terrain [Vertex][0];
                    tmp_point0.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x + 1);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    FindTriangles_polygon_has_vertex_in_triangle_last(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_triangle4, tmp_point0, tmp_point1, tmp_point21, tmp_point22);
                }
            }
            // 2-3
            if (inPolygonArrayFlag[x + 1][z + 1] == 0 && inPolygonArrayFlag[x][z + 1] == 0  && inPolygonArrayFlag[x + 1][z] == 1) {
                Vertex = (z) * MAP_W + (x + 1);
                tmp_triangle1.pt1._x = g_terrain [Vertex][0];
                tmp_triangle1.pt1._y = g_terrain [Vertex][1];
                tmp_triangle1.pt1._z = g_terrain [Vertex][2];
                tmp_triangle2.pt1._x = g_terrain [Vertex][0];
                tmp_triangle2.pt1._y = g_terrain [Vertex][1];
                tmp_triangle2.pt1._z = g_terrain [Vertex][2];
                tmp_triangle3.pt1._x = g_terrain [Vertex][0];
                tmp_triangle3.pt1._y = g_terrain [Vertex][1];
                tmp_triangle3.pt1._z = g_terrain [Vertex][2];
                // 对角三角形
                if (z < MAP_W - 2) {
                    PPR_Point tmp_point0;
                    Vertex = (z + 2) * MAP_W + (x);
                    tmp_point0.x = g_terrain [Vertex][0];
                    tmp_point0.y = g_terrain [Vertex][2];
                    Vertex = (z) * MAP_W + (x + 1);
                    tmp_point1.x = g_terrain [Vertex][0];
                    tmp_point1.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x);
                    tmp_point21.x = g_terrain [Vertex][0];
                    tmp_point21.y = g_terrain [Vertex][2];
                    Vertex = (z + 1) * MAP_W + (x + 1);
                    tmp_point22.x = g_terrain [Vertex][0];
                    tmp_point22.y = g_terrain [Vertex][2];
                    FindTriangles_polygon_has_vertex_in_triangle_last(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_triangle4, tmp_point0, tmp_point1, tmp_point21, tmp_point22);
                }
            }
        }
    }
}


void CMy3DSymbolLibNewView::FindTriangles_polygon_has_vertex_in_triangle_1_1(Area_4& m_area4, Triangle& tmp_triangle1, Triangle& tmp_triangle2, PPR_Point& tmp_point1, PPR_Point& tmp_point21, PPR_Point& tmp_point22) {  // NOLINT
    CPointPolygonRelationship tmp_PPR;
    // 有1个顶点在多边形内的三角形
    PPR_Polygon tmp_polygon_tri;
    tmp_polygon_tri.push_back(tmp_point1);
    tmp_polygon_tri.push_back(tmp_point21);
    tmp_polygon_tri.push_back(tmp_point22);
    PPR_Point tmp_polygon_point;    // 多边形顶点
    PPR_Point tmp_polygon_point_ra;  // 多边形顶点 相邻的 一个顶点
    PPR_Point tmp_polygon_point_rb;  // 多边形顶点 相邻的 另一个顶点
    PPR_Point JD1, JD2;
    // CString msg;
    bool intersectFlag11 = false;
    bool intersectFlag12 = false;
    bool intersectFlag21 = false;
    bool intersectFlag22 = false;
    int16 tmp_cout = 4;
    while (tmp_cout > 0) {
        if (4 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt1._x;
            tmp_polygon_point.y = m_area4.pt1._z;
            tmp_polygon_point_ra.x = m_area4.pt2._x;
            tmp_polygon_point_ra.y = m_area4.pt2._z;
            tmp_polygon_point_rb.x = m_area4.pt4._x;
            tmp_polygon_point_rb.y = m_area4.pt4._z;
        } else if (3 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt2._x;
            tmp_polygon_point.y = m_area4.pt2._z;
            tmp_polygon_point_ra.x = m_area4.pt1._x;
            tmp_polygon_point_ra.y = m_area4.pt1._z;
            tmp_polygon_point_rb.x = m_area4.pt3._x;
            tmp_polygon_point_rb.y = m_area4.pt3._z;
        } else if (2 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt3._x;
            tmp_polygon_point.y = m_area4.pt3._z;
            tmp_polygon_point_ra.x = m_area4.pt2._x;
            tmp_polygon_point_ra.y = m_area4.pt2._z;
            tmp_polygon_point_rb.x = m_area4.pt4._x;
            tmp_polygon_point_rb.y = m_area4.pt4._z;
        } else if (1 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt4._x;
            tmp_polygon_point.y = m_area4.pt4._z;
            tmp_polygon_point_ra.x = m_area4.pt1._x;
            tmp_polygon_point_ra.y = m_area4.pt1._z;
            tmp_polygon_point_rb.x = m_area4.pt3._x;
            tmp_polygon_point_rb.y = m_area4.pt3._z;
        }
        int32 inTriangleFlag = -1;
        inTriangleFlag = tmp_PPR.InPolygon(tmp_polygon_tri, tmp_polygon_point);
        // 如果多边形的顶点也在三角形中
        if (inTriangleFlag == 0) {
            intersectFlag11 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_ra);
            intersectFlag12 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_rb);
            intersectFlag21 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
            intersectFlag22 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);
            if ((intersectFlag11 || intersectFlag12) && (intersectFlag21 || intersectFlag22)) {
                if (intersectFlag11)
                    JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_ra);
                if (intersectFlag12)
                    JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_rb);
                if (intersectFlag21)
                    JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
                if (intersectFlag22)
                    JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);
                tmp_triangle1.pt2._x = JD1.x;
                tmp_triangle1.pt2._y = GetHeight(JD1.x, JD1.y);
                tmp_triangle1.pt2._z = JD1.y;
                tmp_triangle1.pt3._x = tmp_polygon_point.x;
                tmp_triangle1.pt3._y = GetHeight(tmp_polygon_point.x, tmp_polygon_point.y);
                tmp_triangle1.pt3._z = tmp_polygon_point.y;
                tmp_triangle2.pt2._x = tmp_polygon_point.x;
                tmp_triangle2.pt2._y = GetHeight(tmp_polygon_point.x, tmp_polygon_point.y);
                tmp_triangle2.pt2._z = tmp_polygon_point.y;
                tmp_triangle2.pt3._x = JD2.x;
                tmp_triangle2.pt3._y = GetHeight(JD2.x, JD2.y);
                tmp_triangle2.pt3._z = JD2.y;
                m_area4.LocalTrianglesVecotr1_1.push_back(tmp_triangle1);
                m_area4.LocalTrianglesVecotr1_1.push_back(tmp_triangle2);
            }
        }
        tmp_cout--;
    }
}



void CMy3DSymbolLibNewView::FindTriangles_polygon_has_vertex_in_triangle_2_1(Area_4& m_area4, Triangle& tmp_triangle1, Triangle& tmp_triangle2, Triangle& tmp_triangle3, PPR_Point& tmp_point1, PPR_Point& tmp_point21, PPR_Point& tmp_point22) {  // NOLINT
    CPointPolygonRelationship tmp_PPR;
    // 有2个顶点在多边形内的三角形
    PPR_Polygon tmp_polygon_tri;
    tmp_polygon_tri.push_back(tmp_point1);
    tmp_polygon_tri.push_back(tmp_point21);
    tmp_polygon_tri.push_back(tmp_point22);
    PPR_Point tmp_polygon_point;    // 多边形顶点
    PPR_Point tmp_polygon_point_ra;  // 多边形顶点 相邻的 一个顶点
    PPR_Point tmp_polygon_point_rb;  // 多边形顶点 相邻的 另一个顶点
    PPR_Point JD1, JD2;
    // CString msg;
    bool intersectFlag11 = false;
    bool intersectFlag12 = false;
    bool intersectFlag21 = false;
    bool intersectFlag22 = false;
    int16 tmp_cout = 4;
    while (tmp_cout > 0) {
        if (4 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt1._x;
            tmp_polygon_point.y = m_area4.pt1._z;
            tmp_polygon_point_ra.x = m_area4.pt2._x;
            tmp_polygon_point_ra.y = m_area4.pt2._z;
            tmp_polygon_point_rb.x = m_area4.pt4._x;
            tmp_polygon_point_rb.y = m_area4.pt4._z;
        } else if (3 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt2._x;
            tmp_polygon_point.y = m_area4.pt2._z;
            tmp_polygon_point_ra.x = m_area4.pt1._x;
            tmp_polygon_point_ra.y = m_area4.pt1._z;
            tmp_polygon_point_rb.x = m_area4.pt3._x;
            tmp_polygon_point_rb.y = m_area4.pt3._z;
        } else if (2 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt3._x;
            tmp_polygon_point.y = m_area4.pt3._z;
            tmp_polygon_point_ra.x = m_area4.pt2._x;
            tmp_polygon_point_ra.y = m_area4.pt2._z;
            tmp_polygon_point_rb.x = m_area4.pt4._x;
            tmp_polygon_point_rb.y = m_area4.pt4._z;
        } else if (1 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt4._x;
            tmp_polygon_point.y = m_area4.pt4._z;
            tmp_polygon_point_ra.x = m_area4.pt1._x;
            tmp_polygon_point_ra.y = m_area4.pt1._z;
            tmp_polygon_point_rb.x = m_area4.pt3._x;
            tmp_polygon_point_rb.y = m_area4.pt3._z;
        }
        int32 inTriangleFlag = -1;
        inTriangleFlag = tmp_PPR.InPolygon(tmp_polygon_tri, tmp_polygon_point);
        // 如果多边形的顶点也在三角形中
        if (inTriangleFlag == 0) {
            intersectFlag11 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_ra);
            intersectFlag12 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_rb);
            intersectFlag21 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
            intersectFlag22 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);
            if ((intersectFlag11 || intersectFlag12) && (intersectFlag21 || intersectFlag22)) {
                if (intersectFlag11)
                    JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_ra);
                if (intersectFlag12)
                    JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_rb);
                if (intersectFlag21)
                    JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
                if (intersectFlag22)
                    JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);
                tmp_triangle1.pt2._x = JD1.x;
                tmp_triangle1.pt2._y = GetHeight(JD1.x, JD1.y);
                tmp_triangle1.pt2._z = JD1.y;
                tmp_triangle1.pt3._x = tmp_polygon_point.x;
                tmp_triangle1.pt3._y = GetHeight(tmp_polygon_point.x, tmp_polygon_point.y);
                tmp_triangle1.pt3._z = tmp_polygon_point.y;
                tmp_triangle2.pt2._x = tmp_polygon_point.x;
                tmp_triangle2.pt2._y = GetHeight(tmp_polygon_point.x, tmp_polygon_point.y);
                tmp_triangle2.pt2._z = tmp_polygon_point.y;
                tmp_triangle2.pt3._x = JD2.x;
                tmp_triangle2.pt3._y = GetHeight(JD2.x, JD2.y);
                tmp_triangle2.pt3._z = JD2.y;
                tmp_triangle3.pt3._x = tmp_polygon_point.x;
                tmp_triangle3.pt3._y = GetHeight(tmp_polygon_point.x, tmp_polygon_point.y);
                tmp_triangle3.pt3._z = tmp_polygon_point.y;
                // AfxMessageBox("21");
                m_area4.LocalTrianglesVecotr2_1.push_back(tmp_triangle1);
                m_area4.LocalTrianglesVecotr2_1.push_back(tmp_triangle2);
                m_area4.LocalTrianglesVecotr2_1.push_back(tmp_triangle3);
            }
        }
        tmp_cout--;
    }
}



void CMy3DSymbolLibNewView::FindTriangles_polygon_has_vertex_in_triangle_last(Area_4& m_area4, Triangle& tmp_triangle1, Triangle& tmp_triangle2, Triangle& tmp_triangle3, Triangle& tmp_triangle4, PPR_Point& tmp_point0, PPR_Point& tmp_point1, PPR_Point& tmp_point21, PPR_Point& tmp_point22) {  // NOLINT
    CPointPolygonRelationship tmp_PPR;
    PPR_Polygon tmp_polygon_tri;
    tmp_polygon_tri.push_back(tmp_point0);
    tmp_polygon_tri.push_back(tmp_point21);
    tmp_polygon_tri.push_back(tmp_point22);
    PPR_Point tmp_polygon_point;    // 多边形顶点
    PPR_Point tmp_polygon_point_ra;  // 多边形顶点 相邻的 一个顶点
    PPR_Point tmp_polygon_point_rb;  // 多边形顶点 相邻的 另一个顶点
    PPR_Point JD1, JD2 , JD3, JD4;
    // CString msg;
    int16 tmp_cout = 4;
    while (tmp_cout > 0) {
        if (4 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt1._x;
            tmp_polygon_point.y = m_area4.pt1._z;
            tmp_polygon_point_ra.x = m_area4.pt2._x;
            tmp_polygon_point_ra.y = m_area4.pt2._z;
            tmp_polygon_point_rb.x = m_area4.pt4._x;
            tmp_polygon_point_rb.y = m_area4.pt4._z;
        } else if (3 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt2._x;
            tmp_polygon_point.y = m_area4.pt2._z;
            tmp_polygon_point_ra.x = m_area4.pt1._x;
            tmp_polygon_point_ra.y = m_area4.pt1._z;
            tmp_polygon_point_rb.x = m_area4.pt3._x;
            tmp_polygon_point_rb.y = m_area4.pt3._z;
        } else if (2 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt3._x;
            tmp_polygon_point.y = m_area4.pt3._z;
            tmp_polygon_point_ra.x = m_area4.pt2._x;
            tmp_polygon_point_ra.y = m_area4.pt2._z;
            tmp_polygon_point_rb.x = m_area4.pt4._x;
            tmp_polygon_point_rb.y = m_area4.pt4._z;
        } else if (1 == tmp_cout) {
            tmp_polygon_point.x = m_area4.pt4._x;
            tmp_polygon_point.y = m_area4.pt4._z;
            tmp_polygon_point_ra.x = m_area4.pt1._x;
            tmp_polygon_point_ra.y = m_area4.pt1._z;
            tmp_polygon_point_rb.x = m_area4.pt3._x;
            tmp_polygon_point_rb.y = m_area4.pt3._z;
        }
        int32 inTriangleFlag = -1;
        inTriangleFlag = tmp_PPR.InPolygon(tmp_polygon_tri, tmp_polygon_point);
        bool intersectFlag11 = false;
        bool intersectFlag12 = false;
        bool intersectFlag21 = false;
        bool intersectFlag22 = false;
        bool intersectFlag31 = false;
        bool intersectFlag32 = false;
        // 如果多边形的顶点也在对角三角形中
        if (inTriangleFlag == 0) {
            // 与三角形斜边有交点
            intersectFlag31 = tmp_PPR.Meet(tmp_point21, tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
            intersectFlag32 = tmp_PPR.Meet(tmp_point21, tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);
            intersectFlag11 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_ra);
            intersectFlag12 = tmp_PPR.Meet(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_rb);
            intersectFlag21 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
            intersectFlag22 = tmp_PPR.Meet(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);
            if ((intersectFlag31 && intersectFlag32) && (intersectFlag11 || intersectFlag12) && (intersectFlag21 || intersectFlag22)) {
                if (intersectFlag11)
                    JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_ra);
                if (intersectFlag12)
                    JD1 = tmp_PPR.getJD(tmp_point1, tmp_point21, tmp_polygon_point, tmp_polygon_point_rb);
                if (intersectFlag21)
                    JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
                if (intersectFlag22)
                    JD2 = tmp_PPR.getJD(tmp_point1, tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);
                JD3 = tmp_PPR.getJD(tmp_point21, tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
                JD4 = tmp_PPR.getJD(tmp_point21, tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);
                PPR_Point tmp;
                float len1 = (JD3.x - tmp_point21.x) * (JD3.x - tmp_point21.x) + (JD3.y - tmp_point21.y);
                float len2 = (JD4.x - tmp_point21.x) * (JD4.x - tmp_point21.x) + (JD4.y - tmp_point21.y);
                if (len1 > len2) {
                    tmp = PPR_Point(JD3.x, JD3.y);
                    JD3 = PPR_Point(JD4.x, JD4.y);
                    JD4 = PPR_Point(tmp.x, tmp.y);
                }
                tmp_triangle4.pt1._x = tmp_polygon_point.x;
                tmp_triangle4.pt1._y = GetHeight(tmp_polygon_point.x, tmp_polygon_point.y);
                tmp_triangle4.pt1._z = tmp_polygon_point.y;
                tmp_triangle4.pt2._x = JD3.x;
                tmp_triangle4.pt2._y = GetHeight(JD3.x, JD3.y);
                tmp_triangle4.pt2._z = JD3.y;
                tmp_triangle4.pt3._x = JD4.x;
                tmp_triangle4.pt3._y = GetHeight(JD4.x, JD4.y);
                tmp_triangle4.pt3._z = JD4.y;
                tmp_triangle1.pt2._x = JD1.x;
                tmp_triangle1.pt2._y = GetHeight(JD1.x, JD1.y);
                tmp_triangle1.pt2._z = JD1.y;
                tmp_triangle1.pt3._x = JD3.x;
                tmp_triangle1.pt3._y = GetHeight(JD3.x, JD3.y);
                tmp_triangle1.pt3._z = JD3.y;
                tmp_triangle2.pt2._x = JD2.x;
                tmp_triangle2.pt2._y = GetHeight(JD2.x, JD2.y);
                tmp_triangle2.pt2._z = JD2.y;
                tmp_triangle2.pt3._x = JD4.x;
                tmp_triangle2.pt3._y = GetHeight(JD4.x, JD4.y);
                tmp_triangle2.pt3._z = JD4.y;
                tmp_triangle3.pt2._x = JD3.x;
                tmp_triangle3.pt2._y = GetHeight(JD3.x, JD3.y);
                tmp_triangle3.pt2._z = JD3.y;
                tmp_triangle3.pt3._x = JD4.x;
                tmp_triangle3.pt3._y = GetHeight(JD4.x, JD4.y);
                tmp_triangle3.pt3._z = JD4.y;
                // AfxMessageBox("last2");
                m_area4.LocalTrianglesVecotr_last.push_back(tmp_triangle1);
                m_area4.LocalTrianglesVecotr_last.push_back(tmp_triangle2);
                m_area4.LocalTrianglesVecotr_last.push_back(tmp_triangle3);
                m_area4.LocalTrianglesVecotr_last.push_back(tmp_triangle4);
            }
        }
        tmp_cout--;
    }
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
        tmp_point.x = m_area4.pt1._x;
        tmp_point.y = m_area4.pt1._z;
        tmp_polygon.push_back(tmp_point);
        tmp_point.x = m_area4.pt2._x;
        tmp_point.y = m_area4.pt2._z;
        tmp_polygon.push_back(tmp_point);
        tmp_point.x = m_area4.pt3._x;
        tmp_point.y = m_area4.pt3._z;
        tmp_polygon.push_back(tmp_point);
        tmp_point.x = m_area4.pt4._x;
        tmp_point.y = m_area4.pt4._z;
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
