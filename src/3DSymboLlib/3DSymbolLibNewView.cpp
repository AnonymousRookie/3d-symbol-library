#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "3DSymbolLibNew.h"
#endif

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
	// ��׼��ӡ����
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
	ON_MESSAGE(WM_GOODBYE,&CMy3DSymbolLibNewView::OnGoodBye)
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

// CMy3DSymbolLibNewView ����/����

CMy3DSymbolLibNewView::CMy3DSymbolLibNewView()
{
	bIsSelect3DModel = false;
	bIsMouseMove3DModel = false;

	
}

CMy3DSymbolLibNewView::~CMy3DSymbolLibNewView()
{
	// Empty
}

BOOL CMy3DSymbolLibNewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	return CView::PreCreateWindow(cs);
}

// CMy3DSymbolLibNewView ����
void CMy3DSymbolLibNewView::OnDraw(CDC* pDC)
{
	CMy3DSymbolLibNewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	wglMakeCurrent( pDC->m_hDC, m_hRC );// ʹ RC �뵱ǰ DC �����
	DrawScene(); // ��������
	glFlush();	
	::SwapBuffers(m_pDC->GetSafeHdc());	//����������	 
}

// CMy3DSymbolLibNewView ��ӡ
void CMy3DSymbolLibNewView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy3DSymbolLibNewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy3DSymbolLibNewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy3DSymbolLibNewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CMy3DSymbolLibNewView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//m_bRbtnDown = false;

	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy3DSymbolLibNewView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	//#ifndef SHARED_HANDLERS
	//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
	//#endif
}

// CMy3DSymbolLibNewView ���
#ifdef _DEBUG
void CMy3DSymbolLibNewView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3DSymbolLibNewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3DSymbolLibNewDoc* CMy3DSymbolLibNewView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DSymbolLibNewDoc)));
	return (CMy3DSymbolLibNewDoc*)m_pDocument;
}
#endif //_DEBUG




/************************************************************************/
/* Function: ��ʼ����ر���												*/
/************************************************************************/
void CMy3DSymbolLibNewView::InitData()
{
	glActiveTextureARB = NULL;
	glMultiTexCoord2fARB = NULL;	

	m_ViewWideNarrow = 0.0f;							//��ʼ�����ӿڿ�խ���� 

	hwnd = GetSafeHwnd(); 
	CDC *pDestDC = CDC::FromHandle(::GetDC(hwnd));
	m_SCREEN_WIDTH = pDestDC->GetDeviceCaps(HORZRES);	//��Ļ���
	m_SCREEN_HEIGHT = pDestDC->GetDeviceCaps(VERTRES);	//��Ļ�߶�
	m_near = 1;											//�۲����������ƽ��ľ���
	m_far = 5000 ;										// �۲����Զ�����ƽ��ľ���

	m_shizxLength = 2 ;									// ��ѯ��־ʮ���߳���
	m_shuzxHeight = 2 ;									// ��ѯ��־��ֱ�߸߶�
	m_QueryLineWidth = 1 ;								// ��ѯ��־�ߵĿ��
	m_QueryColorR = 255 ;								// ��ѯ��־�ߵ���ɫ(��)
	m_QueryColorG = 0 ;									// ��ѯ��־�ߵ���ɫ(��)
	m_QueryColorB = 0 ;									// ��ѯ��־�ߵ���ɫ(��)
	m_bSearchDistencePtNums=0;

	// ��Ⱦģʽ
	m_Drawmode = 3;

	iTerrainType = 0;  
	iSkyBoxLoaded = false;
	g_isTerrainInit = false;

	//�����������ʸ��
	m_vUp.x = 0; 
	m_vUp.y = 1;
	m_vUp.z = 0;

	m_viewdegree = 0 ; // ��ʼ�ӽ����� 
	m_viewHeight = m_oldviewHeight = 88 ; // �����ʼ�߶�

	m_vEyePosition.x = 334;
	m_vEyePosition.z = -384;
	m_vEyePosition.y = 88;

	g_Angle = 6;						// �ӵ㷽λ�ǳ�ֵ		
	g_elev = 0;							// �����ǳ�ʼֵ
	gao = 1.8; 

	rad_xz = float (PAI_D180* g_Angle);	// ����������ת�Ƕ�

	m_vLook.x = m_vEyePosition.x + 100 * cos(rad_xz);
	m_vLook.z = m_vEyePosition.z + 100 * sin(rad_xz);
	m_vLook.y = m_vEyePosition.y + g_elev;

	m_Step_X = 5.0;		//�����X�����ƶ��Ĳ�����ʼֵ(������)
	m_Step_Z = 5.0;		//�����Z�����ƶ��Ĳ�����ʼֵ(������)
	m_xTrans = 0;		//��X�������ƶ��Ĳ���(���̿���)
	m_zTrans = 0;		//��Z�������ƶ��Ĳ���(���̿���)

	derAngleY = 500.0f;
	derAngleZ = 4000.0f;

	derDisScale = 1.5;

	m_PathFlag = FALSE;

	m_flyspeed = 1000;
	m_maxHeight = -9999;
	m_minHeight = 9999;

	m_ViewUpDown = 0;
	m_FlyPause = FALSE;

	m_fly_start_pause_Enable = FALSE;  // ��ͣ/��ʼ�Ƿ���Ч

	//ָ�����ʼָ��Ƕ�(90��,����ʾ��������,����ά�ռ�����ָ��ZԱ������,��ָ����Ļ����)
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

	// ѡ��ģ���߿���ɫ ��ʼΪ�죬ѡ��ʱ���� �� ����˸Ч��
	wireR = 1;
	wireG = 0;
	wireB = 0;

	m_bFlash = false;

	m_bMouseMoveSelect = false;

	m_mouseShape = MOUSE_SHAPE_SLECT;

	m_bSecneConfig = false;

	// ѡ�е�ģ�͵�id
	m_selectedModelID = -1;
	m_OperateType = -1;

	m_QueryType = -1;

	// checkbox,�Ƿ�ͨ���������ģ�Ͱڷ�λ��
	m_isSetXYByMouse = 0;


	initLines();// ��ʼ����·����




	// [160220]
	// ��ʼ�����ֵ�ģ������·��
	m_3DModelFolder		= "3DModel";
	m_CitySymbolFolder	= "CitySymbol";
	m_TreeModelFolder	= "TreeModel";




	//[160119]
	m_LineEdit_pointNum = 0;


	fuse_Flag = FALSE;


	// [160209]
	m_Area_pointNum = 0;

	Area_fuse_Flag = FALSE;


	// �Ƿ�����Ѵ򿪵ķ����ļ�
	exist_point_flag = FALSE;
	exist_line_flag = FALSE;
	exist_area_flag = FALSE;


	m_CurrentProjectName = "";
	m_PointSymbolFile = "0";  m_LineSymbolFile = "0";	m_AreaSymbolFile = "0";





}


/************************************************************************/
/* Function: ��ʼ����·����												*/
/************************************************************************/
void CMy3DSymbolLibNewView::initLines()
{
	//========================================================== 

	b_haveMadeRail3DwayList=FALSE;	//�Ƿ��Ѿ�����ά��·��ʾ�б�(͸��ͶӰģʽ��)
	m_Railway.m_Railway_width=5.0;	//·�������ܿ��
	m_Railway.m_Lj_width=0.8;		//·����
	m_Railway.m_GuiMianToLujianWidth=0.6;//�������ŵĸ߶�
	m_Railway.m_Lj_Dh=m_Railway.m_GuiMianToLujianWidth*(1/1.75);//���쵽���ľ���
	m_Railway.m_TieGui_width=1.435;//������	

	//==========================================================

	// ѡ����ֵ�趨(����,�н�)

	// ���ڼ���2��֮���߶γ���
	last_x = 0, last_y = 0, last_z = 0;
	pre_x  = 0, pre_y  = 0, pre_z = 0;
	// ���ڼ���2�߶μ�н�	
	v1_begin.Set(0,0,0); v1_end.Set(0,0,0);
	v2_begin.Set(0,0,0); v2_end.Set(0,0,0);
	// ��¼��ĸ���
	p_count = 0;	


	m_distance_between_2_points = 0.0;
	m_pre_distance = 0.0;
}


BOOL CMy3DSymbolLibNewView::InitializeOpenGL(CDC *pDC)
{
	//����opengl�ĳ�ʼ������
	m_pDC=pDC; 
	//���Ȱ�DC�����ظ�ʽ����Ϊָ���ĸ�ʽ���Ա�����DC��ʹ��
	SetupPixelFormat(); 
	//����DC������RC
	m_hRC=::wglCreateContext(m_pDC->GetSafeHdc()); 
	//���õ�ǰ��RC���Ժ�Ļ�ͼ����������m_pDCָ���DC��
	::wglMakeCurrent(m_pDC->GetSafeHdc() , m_hRC); 

	//�жϵ�ǰϵͳ��OpenGL�汾�Ƿ�֧�ֶ���������չ  �ж��Կ��Ƿ�֧�ָ���չ
	glActiveTextureARB		= (PFNGLACTIVETEXTUREARBPROC)		wglGetProcAddress("glActiveTextureARB");
	glMultiTexCoord2fARB	= (PFNGLMULTITEXCOORD2FARBPROC)		wglGetProcAddress("glMultiTexCoord2fARB");
	if(!glActiveTextureARB || !glMultiTexCoord2fARB)
	{
		//MessageBox("��ǰOpenGL�汾�ϵͣ���֧�ֶ�������\n��չ���ܣ������ذ�װ�µİ汾��" ,  "����������չ����" ,  MB_ICONSTOP);
		return FALSE;
	} 

	return TRUE;
}


BOOL CMy3DSymbolLibNewView::SetupPixelFormat()
{
	//��ʼ�����ظ�ʽ�Լ�ѡȡ���ʵĸ�ʽ������RC
	PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR) ,  // pfd�ṹ�Ĵ�С 
		1 ,  // �汾��
		PFD_DRAW_TO_WINDOW | // ֧���ڴ����л�ͼ 
		PFD_SUPPORT_OPENGL | // ֧�� OpenGL 
		PFD_DOUBLEBUFFER| // ˫����ģʽ
		PFD_STEREO |  //֧������ģʽ
		PFD_TYPE_RGBA ,  // RGBA ��ɫģʽ 
		24 ,  // 24 λ��ɫ���
		0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  // ������ɫλ 
		0 ,  // û�з�͸���Ȼ��� 
		0 ,  // ������λλ 
		0 ,  // ���ۼӻ��� 
		0 ,  0 ,  0 ,  0 ,  // �����ۼ�λ 
		32 ,  // 32 λ��Ȼ��� 
		0 ,  // ��ģ�建�� 
		0 ,  // �޸������� 
		PFD_MAIN_PLANE ,  // ���� 
		0 ,  // ���� 
		0 ,  0 ,  0 // ���Բ� , �ɼ��Ժ������ģ 
	}; 
	//��DC��ѡ����ʵ����ظ�ʽ������������
	int pixelformat;
	pixelformat=::ChoosePixelFormat(m_pDC->GetSafeHdc() , &pfd);
	if (pixelformat==0)
	{
		MessageBox("ѡ�����ظ�ʽʧ��!" , "�������ظ�ʽ" , MB_ICONERROR);
		return FALSE;
	}
	//����ָ�����ظ�ʽ
	if (::SetPixelFormat(m_pDC->GetSafeHdc() , pixelformat , &pfd)==FALSE)
	{
		MessageBox("�������ظ�ʽʧ��!" , "�������ظ�ʽ" , MB_ICONERROR);
		return FALSE;
	}

	//���Ե�ǰ���ú�Ӳ���Կ��Ƿ�֧������ģʽ
	unsigned char ucTest;
	glGetBooleanv (GL_STEREO ,  &ucTest);  
	if (!ucTest) 
	{
		return 1;
	}

	if((pfd.dwFlags & PFD_STEREO)==0)
		bStereoAvailable=FALSE ; // �Կ���֧������ģʽ
	else
		bStereoAvailable=TRUE;

	CString stt[5];
	if(bStereoAvailable==FALSE) //����Կ���֧������ģʽ���������ܵĴ���ԭ��
	{
		stt[0]="��.ͼ�ο���֧�����建��;\n";
		stt[1]="��.ͼ�ο���������֧�����建��;\n";
		stt[2]="��.ֻ�����ض��Ľ����Ȼ�ˢ���������� , �ſ���֧�����建��;\n";
		stt[3]="��.���建����Ҫ�ض������������Լ���;";
		stt[4].Format("����ģʽδ������.����������ԭ��:\n%s%s%s%s" , stt[0] , stt[1] , stt[2] , stt[3]);
		MessageBox(stt[4] , "����ģʽ����" , MB_ICONINFORMATION);
	}
	return TRUE;
}


int CMy3DSymbolLibNewView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	pMain =(CMainFrame *)AfxGetApp()->m_pMainWnd;

	// ��ȡ�ͻ������豸������
	m_pDC=new CClientDC(this); 

	// ��ʼ��OpenGL
	InitializeOpenGL(m_pDC);
	InitData();

	InitList() ; // ��ʼ����ʾ�б�	




	return 0;
}


void CMy3DSymbolLibNewView::OnDestroy()
{
	ShowCursor(TRUE);	                        //�����
	if(wglGetCurrentContext() != NULL)
	{
		wglMakeCurrent(m_pDC->m_hDC,NULL);		//�ͷ���m_hDC��Ӧ��RC
	}
	if(m_hRC != NULL)
	{
		wglDeleteContext(m_hRC);				// ɾ��RC
	}
	if(m_pDC)
		delete m_pDC;							//�ͷŵ�ǰviewӵ�е�DC
	CView::OnDestroy();
}


void CMy3DSymbolLibNewView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if(cy>0)
	{
		WinViewX = cx ;								// �ӿڿ��
		WinViewY = cy ;								// �ӿڸ߶�
		glViewport(0 , 0 , cx , cy);				// �����ӿڴ�С
		float m_aspectRatio = (float)cx/(float)cy ; // �ӿڵĺ��ݱ���
		glMatrixMode(GL_PROJECTION);				// ����ǰ��������ΪͶӰ����,ָ����ǰ����ΪGL_PROJECTION 
		glLoadIdentity();							// ����ǰ�����û�Ϊ��λ��        
		gluPerspective(50.0 + m_ViewWideNarrow , m_aspectRatio , m_near , m_far);// fovy=50.0 + m_ViewWideNarrow , ����Ұ�Ƕ�
		glMatrixMode(GL_MODELVIEW);					// ����ǰ��������Ϊģ�;���		
		glLoadIdentity();							// ����ǰ�����û�Ϊ��λ�� 
	}		
}


/************************************************************************/
/* Function: ����ȸ��ߵ������ݺ�����										*/
/************************************************************************/
void CMy3DSymbolLibNewView::OnContourTerrainImport()
{
	TerrainImportContour dlg;
	if(dlg.DoModal()==IDOK)
	{
		terrainTexFileName = dlg.m_TerrainContoureTex;
		terrainContourFileName = dlg.m_TerrainContour;
		LoadTerrainTex(terrainTexFileName, terrainContourFileName);
	}
}

// ��պ� ���� ����λͼ��������ڴ�texture��ֻ������8λ��256ɫ����bmpͼ�� ,����Ԥ��
bool CMy3DSymbolLibNewView::LoadT8(char *filename, GLuint &texture)	
{
	AUX_RGBImageRec *pImage = NULL;
	pImage = auxDIBImageLoad(filename);			// װ��λͼ
	if(pImage == NULL)	return false;			// λͼûװ�룬���ش���
	glGenTextures(1, &texture);					// ������ͼ������
	glBindTexture    (GL_TEXTURE_2D,texture);			
	gluBuild2DMipmaps(GL_TEXTURE_2D,4,  
		pImage->sizeX,									
		pImage->sizeY,									
		GL_RGB, GL_UNSIGNED_BYTE,
		pImage->data								
		);
	free(pImage->data);							// �ͷ�λͼ����ռ�ݵ��ڴ���Դ
	free(pImage);	
	return true;
}


/************************************************************************/
/* Function: ���ȸ��ߵ���ͼ												*/
/************************************************************************/
unsigned char * CMy3DSymbolLibNewView::LoadBit(char *filename, BITMAPINFOHEADER *bitmap)
{
	FILE *filePtr;												// ����λͼ�ṹ
	BITMAPFILEHEADER  Header;									// ����λͼָ��
	unsigned char    *Image;									// ͼ�λ�����
	unsigned int      imageIdx = 0;								// ͼ������
	unsigned char     tempRGB;									// ��������
	filePtr = fopen(filename, "rb");							// ���ļ�
	if (filePtr == NULL)    return NULL;						// ���ļ�������
	fread(&Header, sizeof(BITMAPFILEHEADER), 1, filePtr);		// ��λͼ�ṹ
	if (Header.bfType != BITMAP_ID)								// ����BMPλͼ
	{		
		fclose(filePtr);										// �ر��ļ�
		return NULL;											// ���ؿ�
	}
	fread(bitmap, sizeof(BITMAPINFOHEADER), 1, filePtr);		// ��λͼ�ṹ
	fseek(filePtr, Header.bfOffBits, SEEK_SET);					// �ƶ��ļ�ָ�뵽������
	Image = (unsigned char*)malloc(bitmap->biSizeImage);			// ����ͼ����
	if (!Image)													// ����ͼ����ʧ��
	{ 
		free(Image);											// �ͷ�ͼ����
		fclose(filePtr);										// �ر��ļ�
		return NULL;											// ���ؿ�
	}
	fread(Image, 1, bitmap->biSizeImage, filePtr);				// ��ͼ�����ݶ���
	if (Image == NULL)											// ���ݶ���Ϊ��
	{ 
		fclose(filePtr);										// �ر��ļ�
		return NULL;											// ���ؿ�
	}
	for (imageIdx = 0; imageIdx < bitmap->biSizeImage; imageIdx+=3)
	{ 
		tempRGB = Image[imageIdx];
		Image[imageIdx] = Image[imageIdx + 2];
		Image[imageIdx + 2] = tempRGB;
	}															// ��������
	fclose(filePtr);											// �ر��ļ�
	return Image;												// ����ͼ������
}


void CMy3DSymbolLibNewView::InitTerrain()
{
	int index = 0;
	int Vertex;
	for (int z = 0; z < MAP_W; z++)
		for (int x = 0; x < MAP_W; x++)									// MAP_W�ǵ��ο�����32�У�32�еķ��ε���
		{
			Vertex = z * MAP_W + x;
			g_terrain [Vertex][0] = float(x)*MAP_SCALE;					// �������� 3ά��MAP_SCALE�Ǳ߳�
			g_terrain [Vertex][1] = (float)(g_imageData[Vertex*3] / 3);	// �������� 3ά �Ҷȵȸ������ɸ߶�ͼ����Modelobj��ʼ���͸�ֵ��
				
			
			g_terrain [Vertex][2] = -float(z)*MAP_SCALE;					// �������� 3ά

			g_texcoord[Vertex][0] = (float) x;							// ��������2ά��ָʾ������ͼ��ƽ������
			g_texcoord[Vertex][1] = (float) z;	

			g_index [index++] = Vertex;									// ��������1ά�����涥�㣬һά��������ӿ���ʾ
			g_index [index++] = Vertex + MAP_W;

			// ��ȡ���θ߶ȼ�ֵ
			if(m_maxHeight < g_terrain [Vertex][1]) m_maxHeight = g_terrain [Vertex][1];
			if(m_minHeight > g_terrain [Vertex][1]) m_minHeight = g_terrain [Vertex][1];

			g_max_height = m_maxHeight; // �������߳�ֵ��ȫ�ֱ�����
		}
		
		// ��������  ��һ�� ��������
		glEnableClientState(GL_VERTEX_ARRAY);					// ����ʹ�õ�������
		// ��������  �ڶ��� �ƶ���������
		glVertexPointer    (3,GL_FLOAT,0,g_terrain);			// װ���������

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);			// ����ʹ����������
		glTexCoordPointer  (2,GL_FLOAT,0,g_texcoord);			// װ����������
}

   
/************************************************************************/
/* Function: ��ά���λ���	,����glDrawElements���ٻ������кõĶ������		*/
/************************************************************************/
void CMy3DSymbolLibNewView::DrawTerrain()
{	
	//glShadeModel��������������Ӱ��Ч����GL_SMOOTHΪĬ��ֵ����ʾƽ����ӰЧ����
	glShadeModel(GL_SMOOTH);
	SetDrawMode();	
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();          
	

	gluPerspective(50.0 + m_ViewWideNarrow , (float)WinViewX/(float)WinViewY , m_near , m_far);		
	glMatrixMode(GL_MODELVIEW); // �������Ϊģ��ģ�;���
	glLoadIdentity();			// ����ǰ�����û�Ϊ��λ����       	
	/*glClearDepth����������Ȼ������ģ����ĺ������OpenGL���ڻ��Ƶ�ͼ�����뵽��Ļ�еĳ̶ȣ�
	��ȵ������������ά�ռ��е�z�������ֵ��zȡ0ʱ��ʾ��ƽ���ϣ���Ϳ����������е�ͼ���ˣ�
	���Ը�ֵԽС��ԽԶ�봰��ƽ�����˵�������е�ͼ�������ǹ۲��ߵľ����Զ�ˣ�*/
	glClearDepth(1.0f);			// ���ó�ʼ����Ȼ���ֵ
	glEnable(GL_DEPTH_TEST);	// ������Ȳ���
	glDepthFunc(GL_LESS);		// �ڵ���glEnable(GL_DEPTH_TEST); ������������Ժ󣬵���ȱ仯С�ڵ�ǰ���ֵʱ���������ֵ��
	SetCamra();
	glViewport(0 ,  0 ,  WinViewX ,  WinViewY); //�����ӿڴ�С��λ��
	glBindTexture(GL_TEXTURE_2D, texTerrain);
	glTexEnvf    (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	for (int z = 0; z < MAP_W-1; z++)
	{
		glDrawElements(GL_TRIANGLE_STRIP,MAP_W*2,GL_UNSIGNED_INT,&g_index[z*MAP_W*2]); 
	}


	if(m_bShowbreviary==TRUE)	// ��ʾ������ͼ
	{
		glViewport	   (WinViewX*5/6 ,  WinViewY*5/6 , WinViewX/6 ,  WinViewY/6);
		glBindTexture  (GL_TEXTURE_2D, texTerrain);
		glTexEnvf      (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		for (int z = 0; z < MAP_W-1; z++)
		{
			// ��������  ������ ��Ⱦ
			glDrawElements(GL_TRIANGLE_STRIP,MAP_W*2,GL_UNSIGNED_INT,&g_index[z*MAP_W*2]);   
		}
		glViewport(0, 0, WinViewX, WinViewY); // ���������ӿڴ�С
	}



 
}


/************************************************************************/
/* Function: ��ȡ����߶�													*/
/************************************************************************/
float CMy3DSymbolLibNewView::GetHeight(float x, float z)
{
	float CameraX = x/MAP_SCALE;					// ��������һ��
	float CameraZ =-z/MAP_SCALE;						// ��������һ��
	int Col0 = int(CameraX);						// ����к�
	int Row0 = int(CameraZ);						// ����к�
	int Col1 = Col0 + 1;							// ������
	int Row1 = Row0 + 1;							// ���ڿ�
	if (Col1 > MAP_W)	Col1 = 0;					// �����д��ڵؿ�����ȡ����
	if (Row1 > MAP_W)	Row1 = 0;					// �����д��ڵؿ�����ȡ����

	float h00=g_terrain[Col0 + Row0*MAP_W][1];		// ��ȡ���Ľǵĸ߶�
	float h01=g_terrain[Col1 + Row0*MAP_W][1];
	float h11=g_terrain[Col1 + Row1*MAP_W][1];
	float h10=g_terrain[Col0 + Row1*MAP_W][1];

	float tx =CameraX - int(CameraX);				// �����Xƫ��λ��
	float ty =CameraZ - int(CameraZ);				// �����Zƫ��λ��

	float txty = tx * ty;							// ����Ϊ˫���Բ�ֵ���ڲ壩����

	// ���ز�ֵ����ֵ��Ϊ�����ĸ߶�
	return h00*(1.0f-ty-tx+txty) + h01*(tx-txty) + h11*txty + h10*(ty-txty);						
}

void CMy3DSymbolLibNewView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nChar =='W'|| nChar =='w'){
		m_Drawmode = 1;
	}
	if(nChar =='F'|| nChar =='f'){
		m_Drawmode = 2;
	}
	if(nChar =='T'|| nChar =='t'){
		m_Drawmode = 3;
	}
	Invalidate(FALSE);
	CView::OnChar(nChar, nRepCnt, nFlags);
}

/********************************************************/
/* Function:���û�ͼģʽ									*/
/********************************************************/
void  CMy3DSymbolLibNewView::SetDrawMode()
{
	switch(m_Drawmode)//����ģʽ 
	{
	case 1://�߿�ģʽ
		glDisable(GL_TEXTURE_2D) ; // �ر�������
		glPolygonMode(GL_FRONT_AND_BACK , GL_LINE);
		break;
	case 2://����ģʽ
		glDisable(GL_TEXTURE_2D) ; // ����������
		glPolygonMode(GL_FRONT_AND_BACK , GL_FILL);
		break;
	case 3://����ģʽ
		glEnable(GL_TEXTURE_2D) ; // ����������
		glPolygonMode(GL_FRONT_AND_BACK , GL_FILL);
		break;
	}
}


/********************************************************/
/* Function:��������										*/
/********************************************************/
void CMy3DSymbolLibNewView::DrawScene()
{
	glClearColor(0.53, 0.81, 0.92, 0.0);				// ����ˢ�±���ɫSkyBlue: 135,206,235
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	// ˢ�±���
	glLoadIdentity();									// ���õ�ǰ��ģ�͹۲����
	SetDrawMode();

	if(m_vEyePosition.x <  MAP_SCALE){			
		m_vEyePosition.x = MAP_SCALE;
	}
	if(m_vEyePosition.x > (MAP_W-2) * MAP_SCALE)	{
		m_vEyePosition.x = (MAP_W-2) * MAP_SCALE;
	}
	if(m_vEyePosition.z < -(MAP_W-2) * MAP_SCALE){
		m_vEyePosition.z = -(MAP_W-2) * MAP_SCALE;
	}
	if(m_vEyePosition.z > -MAP_SCALE){
		m_vEyePosition.z = -MAP_SCALE;
	}

	SetCamra();

	

	if(iTerrainType != 0)
	{
		if(iSkyBoxLoaded){
			DrawSky();
		}
		
		DrawClock();			// ����ָ����
		DrawTerrain();
		DrawFlyPath();
		DrawRailwaythesme();	// ������·

		if(m_QueryType==QUERY_COORDINATE || m_QueryType==QUERY_DISTENCE || m_QueryType==SELECTLINE
			|| m_QueryType==LINE_ADD //Line
			|| m_QueryType==AREA_ADD //Area
		){
			DrawSearchPoint();	// ���ƿռ��ѯ��־ 
		}


		//[160120]
		if(fuse_Flag)
		{
			DrawJDLine(Line_a_JD_vector, Line_b_JD_vector);
		}


		if(Area_fuse_Flag)
		{
			int tmp_size = m_Area4_Array.GetSize();

			for(int i=0; i<tmp_size; ++i)
			{
				/*	Area_4 tmp_area4;
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

				if(m_Area4_Array[i]->deleted != 1)
				{
					Area_Triangled( m_Area4_Array[i]);
				}
				
			}
			
		}


		// ---------------------------------------------------------

		// ��ʾ������
		glPushMatrix();
		if(m_TreeModel.GetSize() > 0)
		{
			for(int i =0; i < m_TreeModel.GetSize(); i++)
			{
				ShowTree(i);
			}
		}
		glPopMatrix();
		// ---------------------------------------------------------

		// ��ʾ3D������
		glPushMatrix();
		if(m_3DTreeModel.GetSize() > 0)
		{
			for(int i =0; i < m_3DTreeModel.GetSize(); i++)
			{
				Show3DTree(i);
			}
		}
		glPopMatrix();
		// ---------------------------------------------------------

		// ��ʾ���з���
		glPushMatrix();
		if(m_CitySymbolModel.GetSize() > 0)
		{
			for(int i =0; i < m_CitySymbolModel.GetSize(); i++)
			{
				ShowCitySymbol(i);
			}
		}
		glPopMatrix();
		// ---------------------------------------------------------
		glPushMatrix();
		if(bIsWeatherLoad)
		{
			ShowWeather();
		}
		glPopMatrix();
		// ---------------------------------------------------------
		glPushMatrix();
		glPushAttrib(GL_CURRENT_COLOR);
			
		if(m_3DModel.GetSize() > 0)
		{ 
			for(int i = 0; i < m_3DModel.GetSize(); i++)
					
				if(m_3DModel.GetAt(i)->isDeleted == false)
				{
					Draw3DModel(m_3DModel.GetAt(i));
				}	
		}
		glPopAttrib();
		glPopMatrix();
		// ---------------------------------------------------------
		if(m_flypathPtIndex > 0)
		{
			TextFlyHelp();
		}
	} 

	GLfloat light_position[] = {m_vEyePosition.x,300,m_vEyePosition.z-100};
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
/* Function:��պ��������Լ���������						*/
/********************************************************/
void CMy3DSymbolLibNewView::OnSkyboxTex()
{
	CSkyBoxTexLoad dlg;
	if(dlg.DoModal()==IDOK)
	{
		g_texSkyBoxFlieNameTP = dlg.m_SkyBoxTexTP; 
		g_texSkyBoxFlieNameLF = dlg.m_SkyBoxTexLF; 
		g_texSkyBoxFlieNameBK = dlg.m_SkyBoxTexBK; 
		g_texSkyBoxFlieNameRT = dlg.m_SkyBoxTexRT; 
		g_texSkyBoxFlieNameFR = dlg.m_SkyBoxTexFR; 
		LoadSkyBoxTex(g_texSkyBoxFlieNameTP, g_texSkyBoxFlieNameLF, g_texSkyBoxFlieNameBK, g_texSkyBoxFlieNameRT, g_texSkyBoxFlieNameFR);
	}
}


/********************************************************/
/* Function:�������										*/
/********************************************************/
void CMy3DSymbolLibNewView::CreateSkyBox()
{	
	glPushMatrix(); 

	int a = 3, wi =3, he=1, le=3;
	float width =MAP*wi;
	float height=MAP*he;
	float length=MAP*le;

	int x0 = MAP - width / 2;
	int x1 = MAP + width / 2;

	int y0 = MAP/a - height / 3;
	int y1 = MAP/a + height / 3;

	int z0 = -MAP - length / 2;
	int z1 = -MAP + length / 2;

	// ����BACK�������
	glBindTexture  (GL_TEXTURE_2D, g_texSkyBox[BK]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  

	// ��ʼ����
	glBegin(GL_QUADS);		
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x1, y0, z0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x1, y1, z0); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x0, y1, z0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x0, y0, z0);		
	glEnd();

	// ����FRONT���ֵ��������
	glBindTexture  (GL_TEXTURE_2D, g_texSkyBox[FR]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// ��ʼ����
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x0, y0, z1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x0, y1, z1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x1, y1, z1); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y0, z1);
	glEnd();

	// ����TOP���ֵ��������
	glBindTexture  (GL_TEXTURE_2D, g_texSkyBox[TP]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// ��ʼ����
	glBegin(GL_QUADS);		
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x0, y1, z1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x0, y1, z0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x1, y1, z0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x1, y1, z1);  
	glEnd();

	// ����LEFT���ֵ��������
	glBindTexture  (GL_TEXTURE_2D, g_texSkyBox[LF]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// ��ʼ����
	glBegin(GL_QUADS);		
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x0, y1, z0);	
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x0, y1, z1); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x0, y0, z1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x0, y0, z0);		
	glEnd();

	// ����RIGHT���ֵ��������
	glBindTexture  (GL_TEXTURE_2D, g_texSkyBox[RT]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// ��ʼ����
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y0, z0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x1, y0, z1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x1, y1, z1); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x1, y1, z0);
	glEnd();
	glPopMatrix();
}

void CMy3DSymbolLibNewView::SkyBoxTexture(UINT textur)
{	
	glBindTexture  (GL_TEXTURE_2D, textur);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
}

void CMy3DSymbolLibNewView::OnDrawmodeLine()
{
	// TODO: �ڴ���������������
	m_Drawmode = 1;
	Invalidate(FALSE);
}

void CMy3DSymbolLibNewView::OnUpdateDrawmodeLine(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_Drawmode == 1);//����m_ViewTypeֵ�Ƿ�����ѡ�б�־
}

void CMy3DSymbolLibNewView::OnDrawmodeRender()
{
	// TODO: �ڴ���������������
	m_Drawmode = 2;
	Invalidate(FALSE);
}

void CMy3DSymbolLibNewView::OnUpdateDrawmodeRender(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_Drawmode == 2);//����m_ViewTypeֵ�Ƿ�����ѡ�б�־
}

void CMy3DSymbolLibNewView::OnDrawmodeTexture()
{
	// TODO: �ڴ���������������
	m_Drawmode = 3;
	Invalidate(FALSE);
}

void CMy3DSymbolLibNewView::OnUpdateDrawmodeTexture(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_Drawmode == 3);//����m_ViewTypeֵ�Ƿ�����ѡ�б�־
}


/********************************************************/
/* Function:�ռ��ѯ��־����								*/
/********************************************************/
void CMy3DSymbolLibNewView::OnSpacequerySet() 
{
	CSpaceSearchSet dlg;

	dlg.m_shizxLength = m_shizxLength;		// ��ѯ��־ʮ���߳���
	dlg.m_shuzxHeight = m_shuzxHeight;		// ��ѯ��־��ֱ�߸߶�
	dlg.m_QueryLineWidth = m_QueryLineWidth;// ��ѯ��־�ߵĿ��
	dlg.m_QueryColorR = m_QueryColorR;		// ��ѯ��־�ߵ���ɫ(��)
	dlg.m_QueryColorG = m_QueryColorG;		// ��ѯ��־�ߵ���ɫ(��)
	dlg.m_QueryColorB = m_QueryColorB;		// ��ѯ��־�ߵ���ɫ(��)
	if(dlg.DoModal() == IDOK)
	{
		m_shizxLength = dlg.m_shizxLength;				// �õ������õĲ�ѯ��־ʮ���߳���
		m_shuzxHeight = dlg.m_shuzxHeight;				// �õ������õĲ�ѯ��־��ֱ�߸߶�
		m_QueryLineWidth = dlg.m_QueryLineWidth + 1;	// �õ������õĲ�ѯ��־�ߵĿ�ȣ��±��0��ʼ
		m_QueryColorR = dlg.m_QueryColorR;				// �õ������õĲ�ѯ��־�ߵ���ɫ(��)
		m_QueryColorG = dlg.m_QueryColorG;				// �õ������õĲ�ѯ��־�ߵ���ɫ(��)
		m_QueryColorB = dlg.m_QueryColorB;				// �õ������õ�//��ѯ��־�ߵ���ɫ(��)
	}	
}


/********************************************************/
/* Function: ��ѯ��ά����									*/
/********************************************************/
void CMy3DSymbolLibNewView::OnQueryCoordinate()
{
	if(m_QueryType==QUERY_COORDINATE){	// �����ǰ�Ѿ��ǲ�ѯ��ά����״̬����ر�
		m_QueryType = -1;
	}
	else{								// �����ǰ�Ѿ����ǲ�ѯ��ά����״̬�����
		m_QueryType = QUERY_COORDINATE;
	}
	m_OperateType = -1;
}


/********************************************************/
/* Function: �����Ƿ�ѡ��״̬								*/
/********************************************************/
void CMy3DSymbolLibNewView::OnUpdateQueryCoordinate(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_QueryType==QUERY_COORDINATE);
}

void CMy3DSymbolLibNewView::OnQueryDistence()
{
	// TODO: �ڴ���������������
	if(m_QueryType == QUERY_DISTENCE){	//�����ǰ�Ѿ��ǲ�ѯ�ռ����״̬����ر�
		m_QueryType = -1;
	}
	else{								// �����ǰ���ǲ�ѯ�ռ����״̬����رգ����
		m_QueryType = QUERY_DISTENCE;
	}
}

void CMy3DSymbolLibNewView::OnUpdateQueryDistence(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_QueryType==QUERY_DISTENCE);
}




/********************************************************/
/* Function: ��Ļ���� ==> ��ά����						*/
/********************************************************/
void CMy3DSymbolLibNewView::ScreenToGL(CPoint point)
{
	int mouse_x=point.x;
	int mouse_y=point.y;

	GLint viewport[4];
	GLdouble modelview[16] , projection[16];
	GLdouble wx , wy , wz;
	float winX , winY , winZ;

	glPushMatrix();
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	glPopMatrix();

	winX=(float)mouse_x;
	winY=(float)viewport[3]-(float)mouse_y-1;
	glReadPixels(mouse_x, int(winY), 1, 1, 
		GL_DEPTH_COMPONENT , GL_FLOAT , 
		&winZ);// ��ȡ���ֵ��ֻ��������Ⱦ�ĵط�����׼ȷ��ȡ��һ��û����Ⱦ��Ͳ��ܻ�ȡ��ȷֵ

	// ��任��ģ��任
	gluUnProject((GLdouble)winX, (GLdouble)winY, (GLdouble)winZ, modelview, projection, viewport, &wx, &wy, &wz);

	// 3D����㷶Χ����
	if(wx<  MAP_SCALE){		
		wx =  MAP_SCALE;         // X��
	}
	if(wx> (MAP_W-1)*MAP_SCALE){
		wx = (MAP_W-1)*MAP_SCALE;// X��
	}
	if(wz<-(MAP_W-1)*MAP_SCALE){
		wz =-(MAP_W-1)*MAP_SCALE;// Z��
	}
	if(wz> -MAP_SCALE){	
		wz = -MAP_SCALE;         // Z��
	}

	CMainFrame *pMainFrame=(CMainFrame*)GetParent(); 
	CString strText; 

	// ��״̬��ָʾ������ʾ�����Ϣ(��������������ά�����е�����)
	strText.Format("�������:x=%.3f , y=%.3f , z=%.3f" , wx  , wy , wz);
	pMainFrame->Set_BarText(4 , strText);  
	

	CString tt;

	if(winZ>=0 && winZ<1.0) 
	{
		if(m_isSetXYByMouse)	//ͨ���������ģ�Ͱڷ�λ��
		{
			pt1[0]=wx;pt1[1]=wy;pt1[2]=wz;
			if(paramSet_modeless_dlg)
			{
				paramSet_modeless_dlg->xPos = pt1[0];
				paramSet_modeless_dlg->zPos = pt1[2];
				::PostMessage(paramSet_modeless_dlg->GetSafeHwnd(),WM_UPDATE_EDIT_XY,0,0);
			}
			
		}

		if(m_QueryType==QUERY_COORDINATE)//��ѯ��ά����
		{
			tt.Format("��ǰ����(x,y,z)=(%.3f,%.3f,%.3f)",wx,wy,-wz);	
			pt1[0]=wx;pt1[1]=wy;pt1[2]=wz;							//��ѯ��õ���ά������� 
			Invalidate(FALSE);
			MessageBox(tt,"��ά�����ѯ",MB_ICONINFORMATION);		//���������ѯ��Ϣ
			IsSearchPoint = true;
		}
		else if(m_QueryType==QUERY_DISTENCE)	// ��ѯ�ռ����
		{
			if(	m_bSearchDistencePtNums>=2){	// ���ѡ�����2��������
				m_bSearchDistencePtNums=0;
			}
			m_bSearchDistencePtNums++ ;			// ѡ����� + 1
			
			if(m_bSearchDistencePtNums==1){		// ���ֻѡ����1����
				pt1[0]=wx;pt1[1]=wy;pt1[2]=wz;	// ����ά������洢������ pt1[] ����
			}
			else								// ѡ���������㣬���ʾ���Լ���ռ������		 		
			{
				pt2[0]=wx;pt2[1]=wy;pt2[2]=wz;	// ����ά������洢������ pt2[] ����

				//�������
				double mdistence;
				mdistence=sqrt((pt2[0]-pt1[0])*(pt2[0]-pt1[0])+(pt2[1]-pt1[1])*(pt2[1]-pt1[1])+(pt2[2]-pt1[2])*(pt2[2]-pt1[2])); 
				tt.Format("����Ϊ:\n(x1,y1,z1)=(%.3f,%.3f,%.3f)\n(x2,y2,z2)=(%.3f,%.3f,%.3f)\n����Dis=%.3f", pt1[0],pt1[1],pt1[2],pt2[0],pt2[1],pt2[2],mdistence);
			}

			Invalidate(FALSE);
			MessageBox(tt,"��ά�����ѯ",MB_ICONINFORMATION);		//���������ѯ��Ϣ
		}

		//[160119] �߱༭  �����
		else if(m_QueryType == LINE_ADD)
		{ 
			m_LineEdit_pointNum++ ;			// ѡ����� + 1

			if(m_LineEdit_pointNum==1){		// ���ֻѡ����1����
				m_line.pt1._x = wx; 
				m_line.pt1._y = wy;
				m_line.pt1._z = wz; 
			}
			else if(m_LineEdit_pointNum==2)						 		
			{
				m_line.pt2._x = wx; 
				m_line.pt2._y = wy;
				m_line.pt2._z = wz;
			}

			if(	m_LineEdit_pointNum >= 2 ){	// ���ѡ�����2��������
				m_LineEdit_pointNum=0;

				PLine3 line = new Line3;
				line->pt1 = m_line.pt1;
				line->pt2 = m_line.pt2;

				m_LinesArray.Add(line);
			}
		}

		// [160209]ѡȡ������ϵĵ�
		else if(m_QueryType == AREA_ADD)
		{
			m_Area_pointNum++ ;			// ѡ����� + 1

			if(m_Area_pointNum == 1){
				m_area4_forScreenRecord.pt1._x = wx; 
				m_area4_forScreenRecord.pt1._y = wy;
				m_area4_forScreenRecord.pt1._z = wz; 
			}
			else if(m_Area_pointNum == 2)						 		
			{
				m_area4_forScreenRecord.pt2._x = wx; 
				m_area4_forScreenRecord.pt2._y = wy;
				m_area4_forScreenRecord.pt2._z = wz;
			}
			else if(m_Area_pointNum == 3)						 		
			{
				m_area4_forScreenRecord.pt3._x = wx; 
				m_area4_forScreenRecord.pt3._y = wy;
				m_area4_forScreenRecord.pt3._z = wz;
			}
			else if(m_Area_pointNum == 4)						 		
			{
				m_area4_forScreenRecord.pt4._x = wx; 
				m_area4_forScreenRecord.pt4._y = wy;
				m_area4_forScreenRecord.pt4._z = wz;
			}

			if(	m_Area_pointNum >= 4 ){	// ���ѡ�����4��������
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
		}
		
		//�������άѡ�����
		else if(m_QueryType==SELECTLINE) 
		{
			PCordinate ppt = new Cordinate;

			float tmpH = 0;							// (x,z)���߳�ֵ

			float *pDegree = new float(0);			// ͨ�������������ؼнǵ�ֵ

			const float threshold_distance = 100.0f;// 2�����̾���
			
			
			// 2�߶μ���С�н�
			const float threshold_degree = 20;

			CString warningMsg;						// ��ʾ��Ϣ

			if((ppt==NULL)) 
			{  
				AfxMessageBox( "Failed to add a new ppt"); 
				return ;        
			}
			if(1)
			{
				// ��¼��ƽ�����ά����	
				ppt->x = wx;
				// ����(x,z)���ĸ߳�ֵ
				tmpH = 70;

				ppt->y = tmpH;
				
				ppt->z = wz;	
			}


			tmpH = GetHeight(wx,wz);
			if(m_maxHeight - tmpH < 10)
			{
				warningMsg.Format(_T("�˴�����̫��,������ѡȡ!"));
				AfxMessageBox(warningMsg);
			}
			else
			{
				// �����·ʱȷ��2�˵��ľ��� > threshold_distance
				if(p_count == 0)
				{
					pre_x = ppt->x; pre_y = tmpH; pre_z = ppt->z;
					fun(ppt);
					p_count++;
				}
				else if(p_count>=1)
				{
					if(m_distance_between_2_points > threshold_distance)
					{
						m_pre_distance = m_distance_between_2_points;
					}
					last_x = ppt->x; last_y = tmpH; last_z = ppt->z;
					m_distance_between_2_points = (float)sqrt((last_x-pre_x)*(last_x-pre_x) + (last_y-pre_y)*(last_y-pre_y) + (last_z-pre_z)*(last_z-pre_z));
					if(m_distance_between_2_points > threshold_distance) // ������ֵ
					{
						if(p_count == 1)
						{
							fun(ppt);
							p_count++;

							v1_end.x = pre_x; v1_end.y = 0; v1_end.z = pre_z;
							v1_begin.x = last_x; v1_begin.y = 0; v1_begin.z = last_z;

							pre_x = ppt->x; pre_y = tmpH; pre_z = ppt->z;
						}
						else
						{
							v2_begin = v1_begin;
							v2_end.x = last_x; v2_end.y = 0; v2_end.z = last_z;

							// ����2������֮��ļн�, ͨ��ָ����������������
							getDegreeBetween2Vectors(v1_begin,v1_end,v2_begin,v2_end,pDegree);

							if(*pDegree > threshold_degree) // �н���ֵ
							{
								v1_end.x = pre_x; v1_end.y = 0; v1_end.z = pre_z;
								v1_begin.x = last_x; v1_begin.y = 0; v1_begin.z = last_z;


								float min_distance_between_2_lines = (m_pre_distance < m_distance_between_2_points ? m_pre_distance : m_distance_between_2_points);
								
								if(*pDegree < 30)
								{
									m_Curve_R = 15;
									m_Curve_L0 = 1;
								}
								else
								{
									m_Curve_R = min_distance_between_2_lines * tan((*pDegree / 2.13)*PAI / 180);
									m_Curve_L0 = 6*m_Curve_R / 100;
									if(m_Curve_L0 < 1)
										m_Curve_L0 = 1;
								}


								fun(ppt);

								pre_x = ppt->x; pre_y = tmpH; pre_z = ppt->z;
							}
							else // �н���ֵ
							{
								warningMsg.Format(_T("Degree = %f�� > %f��\n��·ת��̫��,������ѡ��!"),180-*pDegree,180-threshold_degree);
								AfxMessageBox(warningMsg,MB_OK,MB_ICONEXCLAMATION );
							}
						}	
					}
					else // ������ֵ
					{
						warningMsg.Format(_T("Distance = %f < %f\n����֮�����̫��,������ѡ��!"),m_distance_between_2_points,threshold_distance);
						AfxMessageBox(warningMsg,MB_OK,MB_ICONEXCLAMATION );
					}
				}
			}

		}// End ��άѡ�����

		// ----------------------------------------------------------

		// ��������÷���·��
		else if(m_QueryType==SELECTFLYPATH)							
		{
			PCordinate ppt = new Cordinate;  
			ppt->x=wx;ppt->y=wy;ppt->z=wz;							//��¼����·������ά����
			m_FlayPath.Add(ppt);									//������·������ά����洢������m_FlayPath 
			Invalidate(FALSE);
		} 	  
		if(m_OperateType == SELECT)									// �����ѡ��3Dģ��
		{ 
			//����ѡ����
			GLfloat  winX, winY; 
			GLdouble posX, posY, posZ; 
			CRect re;
			GetWindowRect(&re); 
			int screenHeight = re.Height(),screenWidth = re.Width();//��Ļ��͸�

			//�任Ҫ��ͼ�������˳��һ������������ת�����������
			winX = point.x; 
			winY = screenHeight - point.y;
			//��ȡ���ض�Ӧ��ǰ�ü���ĵ�����
			int bResult = gluUnProject(winX, winY, 0.0, modelview, projection, viewport, &posX, &posY, &posZ); 
			CVector3 nearPoint;
			nearPoint.x = posX; 
			nearPoint.y = posY; 
			nearPoint.z = posZ;

			//��ȡ���ض�Ӧ�ĺ�ü���ĵ�����
			bResult = gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &posX, &posY, &posZ); 
			CVector3 farPoint;
			farPoint.x = posX; 
			farPoint.y = posY; 
			farPoint.z = posZ;

			CVector3 n_vector,resultP;
				 
			//cal the vector of ray
			n_vector.x=farPoint.x-nearPoint.x;
			n_vector.y=farPoint.y-nearPoint.y;
			n_vector.z=farPoint.z-nearPoint.z; 

			JudgeRayIntersect(nearPoint, n_vector, resultP); 

			Invalidate(FALSE);
		}
		else if(m_OperateType == MOVE)					// ����ƶ�3Dģ��
		{ 			
			if(	m_bMouseMove3DModelPtNums>=2)			// ���ѡ�����2��������
				m_bMouseMove3DModelPtNums=0;

			m_bMouseMove3DModelPtNums++ ;				// ѡ����� + 1

			if(m_bMouseMove3DModelPtNums == 1)			// ���ֻѡ����1����
			{
				// JudgeRayIntersect(nearPoint, n_vector, resultP);
				PCordinate ppt = new Cordinate;  
				ppt->x=wx; ppt->y=wy; ppt->z=wz;			// ��ά����

				// �������е�3Dģ��,�ж��Ƿ��ڷ�Χ��
				// ���ƶ�ģ��ʱ�����ϳ�ʼ���λ����ģ�ͷ�Χ�ڣ����������ڿ���ģ��λ��
				// ����ѡ����
				GLfloat  winX, winY; 
				GLdouble posX, posY, posZ; 
				CRect re;
				GetWindowRect(&re); 
				int screenHeight = re.Height(),screenWidth = re.Width();//��Ļ��͸�

				//�任Ҫ��ͼ�������˳��һ������������ת�����������

				winX = point.x; 
				winY = screenHeight - point.y;
				//��ȡ���ض�Ӧ��ǰ�ü���ĵ�����
				int bResult = gluUnProject(winX, winY, 0.0, modelview, projection, viewport, &posX, &posY, &posZ); 
				CVector3 nearPoint;
				nearPoint.x = posX; 
				nearPoint.y = posY; 
				nearPoint.z = posZ;

				//��ȡ���ض�Ӧ�ĺ�ü���ĵ�����
				bResult = gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &posX, &posY, &posZ); 
				CVector3 farPoint;
				farPoint.x = posX; 
				farPoint.y = posY; 
				farPoint.z = posZ;

				CVector3 n_vector,resultP;
					 
				//cal the vector of ray
				n_vector.x = farPoint.x-nearPoint.x;
				n_vector.y = farPoint.y-nearPoint.y;
				n_vector.z = farPoint.z-nearPoint.z; 

				JudgeRayIntersect(nearPoint, n_vector, resultP);  
				if( m_selectedModelID != -1)
				{
					pt1[0]=wx;pt1[1]=wy;pt1[2]=wz;					// ����ά������洢������ pt1[] ����
				}
				else
				{
				m_bMouseMove3DModelPtNums = 0;
				}
			}
			else if(m_selectedModelID != -1)							// ѡ���������㣬���ʾ���Լ���ռ������		 		
			{
				// m_modelMoveID
				pt2[0]=wx;pt2[1]=wy;pt2[2]=wz;						// ����ά������洢������ pt2[] ����

				double deltX = (pt2[0] - pt1[0]) / derDisScale;		// 400������ֵϵ��������Խ��ÿ���ƶ������ԽС
				double deltZ = (pt2[2] - pt1[2]) / derDisScale;		// ���ö�̬�޸�ϵ��

				m_3DModel.GetAt(m_selectedModelID)->posX += deltX;
				m_3DModel.GetAt(m_selectedModelID)->posZ += deltZ;

				m_selectedModelID = -1;
			}

			Invalidate(FALSE);
		}  

		// ---------------------------------------

		// �������3Dģ��
		else if(m_OperateType == SCALE)					
		{
			m_selectedModelID = -1;

			//����ѡ����
			GLfloat  winX, winY; 
			GLdouble posX, posY, posZ; 
			CRect re;
			GetWindowRect(&re); 
			int screenHeight = re.Height(),screenWidth = re.Width();//��Ļ��͸�

			//�任Ҫ��ͼ�������˳��һ������������ת�����������
			winX = point.x; 
			winY = screenHeight - point.y;
			//��ȡ���ض�Ӧ��ǰ�ü���ĵ�����
			int bResult = gluUnProject(winX, winY, 0.0, modelview, projection, viewport, &posX, &posY, &posZ); 
			CVector3 nearPoint;
			nearPoint.x = posX; 
			nearPoint.y = posY; 
			nearPoint.z = posZ;
			//��ȡ���ض�Ӧ�ĺ�ü���ĵ�����
			bResult = gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &posX, &posY, &posZ); 
			CVector3 farPoint;
			farPoint.x = posX; 
			farPoint.y = posY; 
			farPoint.z = posZ;

			CVector3 n_vector,resultP;
			 
			//cal the vector of ray
			n_vector.x=farPoint.x-nearPoint.x;
			n_vector.y=farPoint.y-nearPoint.y;
			n_vector.z=farPoint.z-nearPoint.z; 

			JudgeRayIntersect(nearPoint, n_vector, resultP); 
		}
	}

	else if(!m_bMouseMoveSelect)
	{
		MessageBox("���ѡ��㲻����ȷ , �뾫ȷѡ���!");
		m_bSearchDistencePtNums = 0;
	}
}



void CMy3DSymbolLibNewView::ScreenToGL2(CPoint point, GLdouble &wx , GLdouble &wz)
{
	int mouse_x=point.x;
	int mouse_y=point.y;

	GLint viewport[4];
	GLdouble modelview[16] , projection[16];
	GLdouble  wy ;
	float winX , winY , winZ;

	glPushMatrix();
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	glPopMatrix();

	winX=(float)mouse_x;
	winY=(float)viewport[3]-(float)mouse_y-1;
	glReadPixels(mouse_x, int(winY), 1, 1, 
		GL_DEPTH_COMPONENT , GL_FLOAT , 
		&winZ);// ��ȡ���ֵ��ֻ��������Ⱦ�ĵط�����׼ȷ��ȡ��һ��û����Ⱦ��Ͳ��ܻ�ȡ��ȷֵ

	// ��任��ģ��任
	gluUnProject((GLdouble)winX, (GLdouble)winY, (GLdouble)winZ, modelview, projection, viewport, &wx, &wy, &wz);

	// 3D����㷶Χ����
	if(wx<  MAP_SCALE){		
		wx =  MAP_SCALE;         // X��
	}
	if(wx> (MAP_W-1)*MAP_SCALE){
		wx = (MAP_W-1)*MAP_SCALE;// X��
	}
	if(wz<-(MAP_W-1)*MAP_SCALE){
		wz =-(MAP_W-1)*MAP_SCALE;// Z��
	}
	if(wz> -MAP_SCALE){	
		wz = -MAP_SCALE;         // Z��
	}

	 
}

/********************************************************/
/* Function: ����2������֮��ļн�						*/
/********************************************************/
void CMy3DSymbolLibNewView::getDegreeBetween2Vectors(CVector3 v1_Begin,CVector3 v1_End,
			CVector3 v2_Begin,CVector3 v2_End, float *pDegreeRet/*���ؽ��*/)
{
	CVector3 v1 = v1_End - v1_Begin;
	CVector3 v2 = v2_End - v2_Begin;

	float dotProductRet = DotProduct(v1,v2);// ���
	float magnitudeV1 = Magnitude(v1);		// v1��ģ
	float magnitudeV2 = Magnitude(v2);		// v2��ģ

	float cosM = dotProductRet / (magnitudeV1*magnitudeV2);  
	float angleAMB = acos(cosM) * 180 / PI;  
	 
	*pDegreeRet = angleAMB;
}


void CMy3DSymbolLibNewView::fun(PCordinate ppt)
{
	m_oldlinePtnums=myDesingScheme.PtS_JD.GetSize();	//��ǰ��·����ԭ����ƽ�����

	if(m_oldlinePtnums==0)								//�����ǰ��·����û����ƽ���,����û�н��и÷��������
	{
		myDesingScheme.PtS_JD.Add(ppt);					//������ƽ��㵽PtS_JD����
		m_linePtnums=myDesingScheme.PtS_JD.GetSize();	//��ǰ��·����ԭ����ƽ�����
				
		PLineCurve pTempCurveElements = new LineCurve;	//�����µĽ������
		
		//��һ����ƽ���
				
		pTempCurveElements->fwj = 0.0;

		double StartLC = 0;//...

		//ֱ�����=������������   ��ֱ���=������������
		pTempCurveElements->ZH=pTempCurveElements->HZ = StartLC;

		//��Բ���=������������   Բ�����=������������
		pTempCurveElements->HY=pTempCurveElements->YH = StartLC;
				
		//ת��ǡ����߳������߳�=0
		pTempCurveElements->Alfa=pTempCurveElements->T=pTempCurveElements->L=0;
			
		//���߰뾶����ת���͡���ʸ����=0
		pTempCurveElements->R=pTempCurveElements->RoateStyle=pTempCurveElements->E=0;
				
		//�³����������߳���Բ���߳�����ֱ�߳�=0
		pTempCurveElements->P=pTempCurveElements->L0=pTempCurveElements->Ly=pTempCurveElements->Jzxc=0;

		//�������=������������
		pTempCurveElements->JDLC = StartLC;

		//����ID="JD0";
		pTempCurveElements->ID="JD0";

		pTempCurveElements->x=myDesingScheme.PtS_JD.GetAt(0)->x;			//�����x����				
		pTempCurveElements->y=fabs(myDesingScheme.PtS_JD.GetAt(0)->z);	//�����y����				
		pTempCurveElements->z=-myDesingScheme.PtS_JD.GetAt(0)->y;		//�����z����

		//���뽻��Ԫ�ص�DCurveElementssģ��������
		myDesingScheme.JDCurveElements.Add(pTempCurveElements);

	}
	else  //�����ǰ��·������ƽ�����>0,��ʾ�Ѿ����и÷��������
	{
		if(m_linePtnums<=0){
			m_linePtnums=myDesingScheme.PtS_JD.GetSize();
		}
		CString tt;
		tt.Format("JD%d",m_linePtnums); //����ID�Զ�����
				
		
		if(m_oldlinePtnums == 1)
		{
			PLineCurve pTempCurveElements = new LineCurve; 
					

			pTempCurveElements->R = m_Curve_R; 		// ���߰뾶
			pTempCurveElements->L0 = m_Curve_L0; 	// �������߳�

			pTempCurveElements->ID = tt;
			pTempCurveElements->P = (pTempCurveElements->L0*pTempCurveElements->L0)/(pTempCurveElements->R*24.0); 
					
			pTempCurveElements->x=ppt->x;
			pTempCurveElements->y=-ppt->z;
			pTempCurveElements->z=ppt->y;
			myDesingScheme.JDCurveElements.Add(pTempCurveElements);
			myDesingScheme.PtS_JD.Add(ppt);
					
			m_linePtnums=myDesingScheme.PtS_JD.GetSize();
					
			if(myDesingScheme.PtS_JD.GetSize()>1){
				OnDraw(GetWindowDC());
			}
		}
		else if(m_oldlinePtnums >= 2)
		{

			myDesingScheme.JDCurveElements[m_oldlinePtnums-1]->R = m_Curve_R;
			myDesingScheme.JDCurveElements[m_oldlinePtnums-1]->L0 = m_Curve_L0;

			PLineCurve pTempCurveElements = new LineCurve; 

			pTempCurveElements->R = m_Curve_R; 		// ���߰뾶
			pTempCurveElements->L0 = m_Curve_L0; 	// �������߳�

			pTempCurveElements->ID = tt;				// ����ID
			pTempCurveElements->P = (pTempCurveElements->L0*pTempCurveElements->L0)/(pTempCurveElements->R*24.0); 

			pTempCurveElements->x=ppt->x;
			pTempCurveElements->y=-ppt->z;
			pTempCurveElements->z=ppt->y;
			myDesingScheme.JDCurveElements.Add(pTempCurveElements);
			myDesingScheme.PtS_JD.Add(ppt);

			m_linePtnums=myDesingScheme.PtS_JD.GetSize();

			if(myDesingScheme.PtS_JD.GetSize()>1){
				OnDraw(GetWindowDC());
			}
		}
	}
}


void CMy3DSymbolLibNewView::fun(PCordinate ppt, PCurve_R_L0_Struct pcrl0)
{
	m_oldlinePtnums=myDesingScheme.PtS_JD.GetSize();	//��ǰ��·����ԭ����ƽ�����
	
	if(m_oldlinePtnums==0)								//�����ǰ��·����û����ƽ���,����û�н��и÷��������
	{
		myDesingScheme.PtS_JD.Add(ppt);					//������ƽ��㵽PtS_JD����
		m_linePtnums=myDesingScheme.PtS_JD.GetSize();	//��ǰ��·����ԭ����ƽ�����
				
		PLineCurve pTempCurveElements = new LineCurve;	//�����µĽ������
		
		//��һ����ƽ���
				
		pTempCurveElements->fwj = 0.0;

		double StartLC = 0;//...

		//ֱ�����=������������   ��ֱ���=������������
		pTempCurveElements->ZH=pTempCurveElements->HZ = StartLC;

		//��Բ���=������������   Բ�����=������������
		pTempCurveElements->HY=pTempCurveElements->YH = StartLC;
				
		//ת��ǡ����߳������߳�=0
		pTempCurveElements->Alfa=pTempCurveElements->T=pTempCurveElements->L=0;
			
		//���߰뾶����ת���͡���ʸ����=0
		pTempCurveElements->R=pTempCurveElements->RoateStyle=pTempCurveElements->E=0;
				
		//�³����������߳���Բ���߳�����ֱ�߳�=0
		pTempCurveElements->P=pTempCurveElements->L0=pTempCurveElements->Ly=pTempCurveElements->Jzxc=0;

		//�������=������������
		pTempCurveElements->JDLC = StartLC;

		//����ID="JD0";
		pTempCurveElements->ID="JD0";

		pTempCurveElements->x=myDesingScheme.PtS_JD.GetAt(0)->x;			//�����x����				
		pTempCurveElements->y=fabs(myDesingScheme.PtS_JD.GetAt(0)->z);	//�����y����				
		pTempCurveElements->z=-myDesingScheme.PtS_JD.GetAt(0)->y;		//�����z����

		//���뽻��Ԫ�ص�DCurveElementssģ��������
		myDesingScheme.JDCurveElements.Add(pTempCurveElements);

	}
	else  //�����ǰ��·������ƽ�����>0,��ʾ�Ѿ����и÷��������
	{
		if(m_linePtnums<=0){
			m_linePtnums=myDesingScheme.PtS_JD.GetSize();
		}
		CString tt;
		tt.Format("JD%d",m_linePtnums); //����ID�Զ�����


		if(1)
		{
			PLineCurve pTempCurveElements = new LineCurve; 
					
			pTempCurveElements->R = pcrl0->curve_R; 		// ���߰뾶
			pTempCurveElements->L0 = pcrl0->curve_L0; 	// �������߳�

			pTempCurveElements->ID = tt;
			pTempCurveElements->P = (pTempCurveElements->L0*pTempCurveElements->L0)/(pTempCurveElements->R*24.0); 
					
			pTempCurveElements->x=ppt->x;
			pTempCurveElements->y=-ppt->z;
			pTempCurveElements->z=ppt->y;
			myDesingScheme.JDCurveElements.Add(pTempCurveElements);
			myDesingScheme.PtS_JD.Add(ppt);
					
			m_linePtnums=myDesingScheme.PtS_JD.GetSize();
					
			if(myDesingScheme.PtS_JD.GetSize()>1){
				OnDraw(GetWindowDC());
			}
		}
	}
}


/********************************************************/
/* Function: ���ƿռ��ѯ��־								*/
/********************************************************/
void CMy3DSymbolLibNewView::DrawSearchPoint()
{
	glViewport(0, 0, WinViewX, WinViewY);												// ���������ӿڴ�С

	glPushAttrib(GL_CURRENT_BIT);														// ����������ɫ����
	glDisable(GL_TEXTURE_2D);															// ȡ����ͼ
	glPushMatrix();																		// ѹ���ջ
	if(m_QueryType==QUERY_COORDINATE)													//��ά�ռ������ѯ
	{
		if(pt1[0]!=-99999)
		{
			glLineWidth(m_QueryLineWidth);												// ���ò�ѯ��־�߿��
			glColor3f(m_QueryColorR/255.0 , m_QueryColorG/255.0 , m_QueryColorB/255.0);	// ���ò�ѯ��־����ɫ

			//����ʮ���Ͳ�ѯ��־��
			glBegin(GL_LINES);
			glVertex3f(pt1[0]-m_shizxLength , pt1[1] , pt1[2]);
			glVertex3f(pt1[0]+m_shizxLength , pt1[1] , pt1[2]);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(pt1[0] , pt1[1] , pt1[2]-m_shizxLength);
			glVertex3f(pt1[0] , pt1[1] , pt1[2]+m_shizxLength);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(pt1[0] , pt1[1] , pt1[2]);
			glVertex3f(pt1[0] , pt1[1]+m_shuzxHeight , pt1[2]);
			glEnd();
		}

	}
	else if(m_QueryType==QUERY_DISTENCE )			//��ά�ռ�����ѯ(��ѡ�������ռ��֮����ܹ�����ռ����)
	{
		glLineWidth(m_QueryLineWidth) ;				// ���ò�ѯ��־�߿��
		glColor3f(m_QueryColorR/255.0 , m_QueryColorG/255.0 , m_QueryColorB/255.0) ; // ���ò�ѯ��־����ɫ

		//����ʮ���Ͳ�ѯ��־��
		glBegin(GL_LINES);
		glVertex3f(pt1[0]-m_shizxLength , pt1[1] , pt1[2]);
		glVertex3f(pt1[0]+m_shizxLength , pt1[1] , pt1[2]);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(pt1[0] , pt1[1] , pt1[2]-m_shizxLength);
		glVertex3f(pt1[0] , pt1[1] , pt1[2]+m_shizxLength);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(pt1[0] , pt1[1] , pt1[2]);
		glVertex3f(pt1[0] , pt1[1]+m_shuzxHeight , pt1[2]);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(pt2[0]-m_shizxLength , pt2[1] , pt2[2]);
		glVertex3f(pt2[0]+m_shizxLength , pt2[1] , pt2[2]);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f (pt2[0] , pt2[1] , pt2[2]-m_shizxLength);
		glVertex3f (pt2[0] , pt2[1] , pt2[2]+m_shizxLength);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(pt2[0] , pt2[1] , pt2[2]);
		glVertex3f(pt2[0] , pt2[1]+m_shuzxHeight , pt2[2]);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(pt1[0] , pt1[1] , pt1[2]);
		glVertex3f(pt2[0] , pt2[1] , pt2[2]);
		glEnd();

		glLineWidth(1.0);
	}
	
	// ��άѡ��״̬
	else if(m_QueryType==SELECTLINE || myDesingScheme.PtS_JD.GetSize()>0 )
	{
		// ����ѡ������е���ƽ�������
		m_oldlinePtnums = m_linePtnums;
		glColor3f(0,0,1);
		glLineWidth(2.0);
		
		for(int i=0;i<myDesingScheme.PtS_JD.GetSize()-1;i++)
		{
			DrawCenterLine(i,TRUE); // ������·������
		}

		// ���ƽ����־
		for(int j=0;j<=myDesingScheme.PtS_JD.GetSize()-1;++j)
		{
			glLineWidth(m_QueryLineWidth+1);											// ���ñ�־�߿��
			glColor3f(m_QueryColorR/255.0 , m_QueryColorG/255.0 , m_QueryColorB/255.0);	// ���ñ�־����ɫ

			float tmp_x = myDesingScheme.PtS_JD[j]->x;
			float tmp_z = myDesingScheme.PtS_JD[j]->z;
			float tmp_y = GetHeight(tmp_x,tmp_z);
			//����ʮ���ͱ�־��
			glBegin(GL_LINES);
			glVertex3f(tmp_x-m_shizxLength ,tmp_y, tmp_z);
			glVertex3f(tmp_x+m_shizxLength ,tmp_y, tmp_z);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(tmp_x, tmp_y, tmp_z-m_shizxLength);
			glVertex3f(tmp_x, tmp_y, tmp_z+m_shizxLength);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(tmp_x, tmp_y, tmp_z);
			glVertex3f(tmp_x, tmp_y+m_shuzxHeight, tmp_z);
			glEnd();
		}
	}


	//[160119]  �����߶�
	else if( m_QueryType == LINE_ADD )	 
	{
		glLineWidth(3.0) ;				// ���ò�ѯ��־�߿��
		glColor3f(m_QueryColorR/255.0 , m_QueryColorG/255.0 , m_QueryColorB/255.0) ; // ���ò�ѯ��־����ɫ

		for(int i=0;i<m_LinesArray.GetSize();++i)
		{			
			glBegin(GL_LINES);
			glVertex3f(m_LinesArray[i]->pt1._x , m_LinesArray[i]->pt1._y , m_LinesArray[i]->pt1._z);
			glVertex3f(m_LinesArray[i]->pt2._x , m_LinesArray[i]->pt2._y , m_LinesArray[i]->pt2._z);
			glEnd();
		}
		glLineWidth(1.0);
	}

	//[160209] ����4����
	else if( m_QueryType == AREA_ADD )	 
	{
		glLineWidth(3.0) ;				// ���ò�ѯ��־�߿��
		glColor3f(0.3 , 0.6 , 0.5) ; // ���ò�ѯ��־����ɫ


		for(int i=0; i<m_Area4_Array.GetSize(); ++i)
		{
			if(m_Area4_Array[i]->deleted != 1)
			{
				glBegin(GL_QUADS);
				glVertex3f(m_Area4_Array[i]->pt1._x , m_Area4_Array[i]->pt1._y , m_Area4_Array[i]->pt1._z);
				glVertex3f(m_Area4_Array[i]->pt2._x , m_Area4_Array[i]->pt2._y , m_Area4_Array[i]->pt2._z);
				glVertex3f(m_Area4_Array[i]->pt3._x , m_Area4_Array[i]->pt3._y , m_Area4_Array[i]->pt3._z);
				glVertex3f(m_Area4_Array[i]->pt4._x , m_Area4_Array[i]->pt4._y , m_Area4_Array[i]->pt4._z);
				glEnd();
			}
			

		}
		glLineWidth(1.0);
	}





	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glPopAttrib();
}

void CMy3DSymbolLibNewView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bmouseView = true;

	// ͨ���������ģ�Ͱڷ�λ��
	if(m_isSetXYByMouse)
	{
		m_bmouseView = false;
		m_oldMousePos=point;
		ScreenToGL(point);
	}
		
	if(m_QueryType == QUERY_COORDINATE)		// �ռ���ά�����ѯ
	{
		m_bmouseView = false;
		m_oldMousePos=point;
		ScreenToGL(point);
	}
	else if(m_QueryType==QUERY_DISTENCE)	// �ռ�����ѯ
	{
		m_bmouseView = false;				// �ر����������ת
		m_oldMousePos=point;
		ScreenToGL(point);
	}
	// ���з���·��ѡ��
	else if(m_QueryType==SELECTFLYPATH)		
	{
		m_bmouseView=false;					// �ر����������ת
		m_oldMousePos=point;
		ScreenToGL(point);
	}
	// ������άѡ�����
	else if(m_QueryType==SELECTLINE) 
	{
		m_bmouseView=false;					// �ر����������ת
		m_oldMousePos=point;
		ScreenToGL(point); 
	}

	//[160119]�߱༭   �����
	else if(m_QueryType==LINE_ADD)
	{
		m_bmouseView = false;				// �ر����������ת
		m_oldMousePos=point;
		ScreenToGL(point);
	}
	//[160209] �������� 4����
	else if(m_QueryType == AREA_ADD)
	{
		m_bmouseView = false;				// �ر����������ת
		m_oldMousePos=point;
		ScreenToGL(point);
	}

	// ------------------------------------------

	// ����3DSģ��
	if(m_OperateType == SELECT)	// ѡ��3DSģ��
	{
		m_bmouseView=false;
		m_oldMousePos=point;
		m_bIsLBtnDown = true;
		ScreenToGL(point);
	}
	else if(m_OperateType == MOVE) // �ƶ�3DSģ��
	{
		m_bmouseView=false;
		m_oldMousePos=point; 
		ScreenToGL(point);
	}
	else if(m_OperateType == SCALE) // ����3DSģ��
	{
		m_bmouseView=false;
		m_bIsLBtnDown = true;
		ScreenToGL(point);
	}		
	// ------------------------------------------
	CView::OnLButtonDown(nFlags, point);
}

void CMy3DSymbolLibNewView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// �������ĳ��ģ���ϣ���������Ҽ�������ģ�Ϳ��Ʋ˵�
	if(m_OperateType == SELECT && !(m_pSelectedModelSet.empty()) && m_selectedModelID != -1)
	{
		if(m_3DModel.GetAt(m_selectedModelID)->isDeleted==false)
		{
			// �Ҽ���ݲ˵�
			CMenu menu;
			menu.LoadMenu(IDR_POPUP_MODEL_SETTING);
			CMenu *pPopUp = menu.GetSubMenu(0);
			ClientToScreen(&point);
			pPopUp->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		}
	}
	if(m_QueryType == QUERY_DISTENCE || m_QueryType == QUERY_COORDINATE)
	{
		m_QueryType = -1; // �ر���ά��ѯ					
	}
	if(m_OperateType == MOVE || m_OperateType == SCALE)
	{
		// ����moveģʽ��������Ҽ��������൱�ڻص��ƶ�����֮ǰ��״̬���в���
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

void CMy3DSymbolLibNewView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	m_keynumber = 0;
	CVector3 vAxis;

	switch (nChar)				// ���ݰ����ַ���������Ӧ����
	{
	case VK_LEFT:  
		m_keynumber = 3;
		m_xTrans -= m_Step_X;	// ��X�������ƶ��ľ����ۼ�
		Invalidate(FALSE);		// ˢ����ά����
		break;
	case VK_RIGHT:
		m_keynumber = 4;
		m_xTrans += m_Step_X;	// ��X�������ƶ��ľ����ۼ�
		Invalidate(FALSE);		// ˢ����ά����
		break;
	case VK_UP:
		// ѡ������ʱ�ͽ�����߶ȱ仯
		if(m_OperateType == SELECT)
		{
			for(int i = 0; i < m_3DModel.GetSize(); i++)
			{
				if(m_3DModel.GetAt(i)->modelSelected){
					m_3DModel.GetAt(i)->posY++;
				}
			}
		}
		else
		{
			// �������������
			m_zTrans -= m_Step_Z;	// ��Z�������ƶ��ľ����ۼ�
			m_keynumber=1;
		}			
		Invalidate(FALSE);			// ˢ����ά����			
		break;
	case VK_DOWN:
		// ѡ������ʱ�ͽ�����߶ȱ仯
		if(m_OperateType == SELECT)
		{
			for(int i = 0; i < m_3DModel.GetSize(); i++)
			{
				if(m_3DModel.GetAt(i)->modelSelected){
					m_3DModel.GetAt(i)->posY--;
				}
			}
		}
		else
		{
			m_zTrans += m_Step_Z;	// ��Z�������ƶ��ľ����ۼ�
			m_keynumber=2;
		}
		Invalidate(FALSE);			// ˢ����ά����
		break;
	case 'I':     
		m_ViewWideNarrow += 1.0;	// ������Ұ����,����������Χ������,�൱�������ͷ����Ļ�ⷽ���ƶ�	
		OnDraw (GetDC());			// ˢ����ά����
		break;
	case 'O':     
		m_ViewWideNarrow -= 1.0;		// ������Ұ��С,����������Χ��С��,�൱�������ͷ����Ļ�﷽���ƶ�
		OnDraw (GetDC());			// ˢ����ά����
		break;
	case 'J':     					// ����
		//m_flyspeed -= 1;
		//if(m_flyspeed<=1)
		//	m_flyspeed=1;
		//SetFLyTimer();			// ���÷��м�ʱ��
		break;
	case 'M':     				// ����
		//m_flyspeed += 1;
		//SetFLyTimer();			// ���÷��м�ʱ��
		break;
	case 'G':     
		m_StaticHeight=m_StaticHeight*1.1;
		OnDraw (GetDC());		// ˢ����ά����
		break;
	case 'B':     
		m_StaticHeight=m_StaticHeight/1.1; // ���ٹ̶����и߶�
		OnDraw (GetDC());		// ˢ����ά����
		break;
	case VK_F2:					// ��ʾ�����ȼ�����
		DisplayHelp();					   
		break;
	case 'S':					// ֹͣ����
		OnFlyStop();					   
		break;
	case 'P':					// ��ʼ/��ͣ����
		OnFlyPlaypause();					   
		break;
	case 'H':
	case VK_PRIOR: // PgUp   ������
		vAxis = CrossProduct(m_vLook - m_vEyePosition, m_vUp);		// �������
		vAxis = Normalize(vAxis);									// vAxis��һ��
		RotateView(20/derAngleZ, vAxis.x, vAxis.y, vAxis.z);		// ͨ���������������ת(��ת�ӽ�)
		OnDraw(GetDC());
		break;
	case 'N':
	case VK_NEXT: // PgDn	������
		vAxis = CrossProduct(m_vLook - m_vEyePosition, m_vUp);		// �������
		vAxis = Normalize(vAxis);									// vAxis��һ��
		RotateView(-20/derAngleZ, vAxis.x, vAxis.y, vAxis.z);		// ͨ���������������ת(��ת�ӽ�)
		OnDraw(GetDC());
		break;
	case 'R':// ѡ��ģ��R����Y����ת
		for(int i = 0; i < m_3DModel.GetSize(); i++)
		{
			if(m_3DModel.GetAt(i)->modelSelected)
				m_3DModel.GetAt(i)->rotY++;
			if(m_3DModel.GetAt(i)->rotY >= 360)
				m_3DModel.GetAt(i)->rotY = 0;
		}
		OnDraw(GetDC());
		break;

	case VK_HOME: // ˳ʱ����ת
		vAxis = CrossProduct(m_vLook - m_vEyePosition, m_vUp);		// �������
		vAxis = Normalize(vAxis);									// vAxis��һ��
		RotateView(-50/derAngleZ,  0, 1, 0);		// ͨ���������������ת(��ת�ӽ�)
		OnDraw(GetDC());
		break;
	case VK_END: // ��ʱ����ת
		vAxis = CrossProduct(m_vLook - m_vEyePosition, m_vUp);		// �������
		vAxis = Normalize(vAxis);									// vAxis��һ��
		RotateView(50/derAngleZ,  0, 1, 0);		// ͨ���������������ת(��ת�ӽ�)
		OnDraw(GetDC());
		break;


	}
	CamraUpdate();				// ���µ������
	m_keynumber = 0;			// �ָ�����0ֵ

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


/****************************************************************/
/* Function: �������ͼ���ʵ����ά����������ƶ�����ת����			*/
/****************************************************************/
void CMy3DSymbolLibNewView::CamraUpdate()
{
	CVector3 vCross = CrossProduct(m_vLook - m_vEyePosition, m_vUp);// �������
	m_vStrafe = Normalize(vCross);									// vCross��һ��
	SetViewByMouse();												// ͨ�����ʵ���������
	CheckForMovement();												// ͨ������ʵ���������
	m_vEyePosition.y+=(m_viewHeight-m_oldviewHeight);				// �µ�����ӵ�y����
	m_oldviewHeight=m_viewHeight;									// ��¼��ǰ����ӵ�߶�
}


/****************************************************************/
/* Function: ��X�᷽�����ƶ�ʱ��������۲����ӵ�����				*/
/****************************************************************/
void CMy3DSymbolLibNewView::MoveCameraX(float speed)
{
	m_vEyePosition.x += m_vStrafe.x * speed;						// ����ӵ�x������
	m_vEyePosition.z += m_vStrafe.z * speed;						// ����ӵ�z������
	m_vLook.x += m_vStrafe.x * speed;								// ����۲��x������
	m_vLook.z += m_vStrafe.z * speed;								// ����۲��z������
}


/****************************************************************/
/* Function: ��Z�᷽�����ƶ�ʱ��������۲����ӵ�����				*/
/****************************************************************/
void CMy3DSymbolLibNewView::MoveCameraZ(float speed)
{
	CVector3 vVector = m_vLook - m_vEyePosition;						// ����ӵ���۲����ά�����ֵ
	vVector = Normalize(vVector);									// ����ӵ���۲����ά�����ֵ��һ��
	m_vEyePosition.x += vVector.x * speed;							// ����ӵ�x������	
	m_vEyePosition.z += vVector.z * speed;							// ����ӵ�z������	
	m_vLook.x += vVector.x * speed;									// ����۲��x������
	m_vLook.z += vVector.z * speed;									// ����۲��z������
}


/****************************************************************/
/* Function: ���ݼ��̰���ֵ�������������							*/
/****************************************************************/
void CMy3DSymbolLibNewView::CheckForMovement()
{
	if(m_keynumber ==1)												// ���ϼ�ͷ�������򳡾����ƶ�(Z��������)
	{		
		MoveCameraZ(m_Step_Z);										// ��Z�᷽�����ƶ�ʱ��������۲����ӵ�����
	}

	if(m_keynumber ==2) 											// ���¼�ͷ�������򳡾����ƶ�(Z�Ḻ����)
	{
		MoveCameraZ(-m_Step_Z);										// ��Z�᷽�����ƶ�ʱ��������۲����ӵ�����
	}

	if(m_keynumber ==3)												// �����ͷ�������������ƶ�����(X�Ḻ����)
	{
		MoveCameraX(-m_Step_X);										// ��X�᷽�����ƶ�ʱ��������۲����ӵ�����
	}

	if(m_keynumber ==4)												// ���Ҽ�ͷ���������ҷ����ƶ�����(X��������)
	{
		MoveCameraX(m_Step_X);										// ��X�᷽�����ƶ�ʱ��������۲����ӵ�����
	}
}


/****************************************************************/
/* Function: �������											*/
/****************************************************************/
void CMy3DSymbolLibNewView::SetCamra()
{
	gluLookAt(m_vEyePosition.x, m_vEyePosition.y, m_vEyePosition.z, 	// �ӵ�
		m_vLook.x, m_vLook.y, m_vLook.z, 								// Ŀ���
		m_vUp.x, m_vUp.y, m_vUp.z);										// �ӵ㷽��

	CMainFrame *pMainFrame=(CMainFrame*)GetParent();
	

	CString strText;
	float dy=m_vEyePosition.y-m_vLook.y;
	float dz=fabs(m_vEyePosition.z-m_vLook.z);

	if(fabs(dz)<=0.000001){
		m_viewdegree=0;
	}
	else{
		m_viewdegree=HDANGLE*atan(dy/dz);
	}

	// ��״̬��ָʾ������ʾ�����Ϣ
	static DWORD dwStart = 0;
	static int nCount = 0;
	nCount++;
	DWORD dwNow = ::GetTickCount();	// ���شӳ��������������������ĺ�����

	if(dwNow-dwStart>=1000)			// ÿ1�����һ��֡��
	{
		strText.Format("ˢ��Ƶ��: %d FPS " , nCount , 0);
		pMainFrame->Set_BarText(0 , strText);  
		dwStart = dwNow;
		nCount = 0;
	}

	strText.Format("�����ӽǡ�A=%.2f" , m_viewdegree);
	pMainFrame->Set_BarText(1 , strText);  

	strText.Format("�ӵ�����: X=%.3f , Y=%.3f , Z=%.3f" , m_vEyePosition.x  , m_vEyePosition.y , fabs(m_vEyePosition.z));
	pMainFrame->Set_BarText(2 , strText);  

	strText.Format("�۲������: X=%.3f , Y=%.3f , Z=%.3f" , m_vLook.x  , m_vLook.y , fabs(m_vLook.z));
	pMainFrame->Set_BarText(3 , strText);  
}

void CMy3DSymbolLibNewView::OnMouseMove(UINT nFlags, CPoint point)
{
	// ���������״
	
	// ��ģ��ѡ��ģʽ�±������
	if(m_OperateType == SELECT)
	{
		m_selectedModelID = -1;

		// �����ѡ��ģʽ�£�����ƶ�����λ��ʰȡ��ĳ����ǰѡ��ģ�͵�ģ�ͣ��Ǿ͸���ΪEdit�ͺŵ����
		if(!m_pSelectedModelSet.empty())
		{
			m_bMouseMoveSelect = true;
			ScreenToGL(point);
		}	
		else
			m_mouseShape = MOUSE_SHAPE_SLECT; 

		if(m_mouseShape == MOUSE_SHAPE_SLECT)
		{
			HCURSOR hCur  =  LoadCursor(AfxGetInstanceHandle() , 
				MAKEINTRESOURCE(IDC_CURSOR_SELECT));
			::SetCursor(hCur);
		}
		else
		{
			HCURSOR hCur  =  LoadCursor(AfxGetInstanceHandle() , 
				MAKEINTRESOURCE(IDC_CURSOR_EDIT));
			::SetCursor(hCur);
		}

	}

	if(m_bmouseView==TRUE)	// ��������Ƴ�����ʱ
	{
		CamraUpdate();		// �������ͼ���ʵ����ά����������ƶ�����ת����

	}

	Invalidate(FALSE);

	CView::OnMouseMove(nFlags, point);
}


/****************************************************************/
/* Function: ͨ�����ʵ���������									*/
/****************************************************************/
void CMy3DSymbolLibNewView::SetViewByMouse()
{
	if(m_bmouseView==false){		// ��������Ƴ����ر�ʱ,����
		return;
	}

	float angleY = 0.0f;							
	float angleZ = 0.0f;							
	static float currentRotX = 0.0f;

	POINT mousePos;									
	GetCursorPos(&mousePos);		// �õ�����λ��,����Ļ�����ʾ,�洢��mousePos������			

	//����������û�б仯,����
	if( (mousePos.x == m_oldMousePos.x) && (mousePos.y == m_oldMousePos.y) )
		return;

	/* �����y����ǰ��֮�������С(������С500��,���ֵ�ɸ���ʵ�ʵ�������),���angleYֵ
	̫��,��ʾ��ʹ���y����ǰ��֮���С,Ҳ�ᵼ����ά���γ�����Y�����ϱ仯�ܴ� */
	angleY = (float)( (m_oldMousePos.x - mousePos.x) ) / derAngleY;

	/* �����z����ǰ��֮�������С(������С4000��,���ֵ�ɸ���ʵ�ʵ�������),���angleZֵ
	̫��,��ʾ��ʹ���z����ǰ��֮���С,Ҳ�ᵼ����ά���γ�����Z�����ϱ仯�ܴ� */
	angleZ = (float)( (m_oldMousePos.y - mousePos.y) ) / derAngleZ;

	currentRotX -= angleZ;  

	if(angleY >=-360 && angleY <= 360 && angleZ >=-360 && angleY <= 360)
	{
		CVector3 vAxis = CrossProduct(m_vLook - m_vEyePosition, m_vUp);		// �������
		vAxis = Normalize(vAxis);											// vAxis��һ��

		RotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);		// ͨ���������������ת(��ת�ӽ�)
		RotateView(angleY, 0, 1, 0);						// ͨ���������������ת(��ת�ӽ�)
	}

	m_oldMousePos.x=mousePos.x;								// ��¼��ǰ���x����
	m_oldMousePos.y=mousePos.y;								// ��¼��ǰ���y����
}


/****************************************************************/
/* Function: ͨ���������������ת(��ת�ӽ�)						*/
/****************************************************************/
void CMy3DSymbolLibNewView::RotateView(float angle, float x, float y, float z)
{
	CVector3 vNewView;

	CVector3 vView = m_vLook - m_vEyePosition;			// ����ӵ���۲����ά�����ֵ	

	float cosTheta = (float)cos(angle);					// �õ���ת�ӽǵ�cos����ֵ
	float sinTheta = (float)sin(angle);					// �õ���ת�ӽǵ�sin����ֵ

	vNewView.x  = (cosTheta + (1 - cosTheta) * x * x)		* vView.x;
	vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta)	* vView.y;
	vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta)	* vView.z;

	vNewView.y  = ((1 - cosTheta) * x * y + z * sinTheta)	* vView.x;
	vNewView.y += (cosTheta + (1 - cosTheta) * y * y)		* vView.y;
	vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta)	* vView.z;

	vNewView.z  = ((1 - cosTheta) * x * z - y * sinTheta)	* vView.x;
	vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta)	* vView.y;
	vNewView.z += (cosTheta + (1 - cosTheta) * z * z)		* vView.z;

	m_vLook = m_vEyePosition + vNewView;				// �õ���ת�������ӵ�����

	GetNorthPtangle();
}

void CMy3DSymbolLibNewView::OnCameraParamSet()
{
	// TODO: �ڴ���������������
	CCameraParamSet dlg;
	dlg.m_DerAngleY = derAngleY;
	dlg.m_DerAngleZ = derAngleZ;
	dlg.m_OriginDerAngleY = 500;	// derAngleY;
	dlg.m_OriginDerAngleZ = 4000;	// derAngleZ;

	if(dlg.DoModal() == IDOK)
	{
		derAngleY = dlg.m_DerAngleY;
		derAngleZ = dlg.m_DerAngleZ;
	}
}


/****************************************************************/
/* Function: �ֶ����÷���·��										*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnPathManuinput()
{
	// TODO: �ڴ���������������
	m_ShowFlyPath=TRUE;				// ��ʶ�Ƿ���ʾ����·��
	m_QueryType=SELECTFLYPATH;		// ���з���·��ѡ��
	m_FlayPath.RemoveAll();			// �洢���з���·�������������
}


/****************************************************************/
/* Function: ���Ʒ���·��											*/
/****************************************************************/
void CMy3DSymbolLibNewView::DrawFlyPath()
{
	//�����ʾ����·�����ҷ���·���������>1,�Ż��Ʒ���·��
	if(m_ShowFlyPath==TRUE  && m_FlayPath.GetSize()>1)//���з���·��ѡ��
	{
		glPushAttrib(GL_CURRENT_BIT);// ����������ɫ����
		

		glPushMatrix();				// ѹ������ջ
		glDisable(GL_TEXTURE_2D);	// �ر�����(������·������������)
		glLineWidth(10.0);			// ���÷���·���߿�
		glColor3f(1,0,0);			// ���÷���·����ɫ

		glBegin(GL_LINE_STRIP);
		for(int i=0;i<m_FlayPath.GetSize();i++){
			glVertex3f(m_FlayPath.GetAt(i)->x, m_FlayPath.GetAt(i)->y, m_FlayPath.GetAt(i)->z);
		}
		glEnd();

		glEnable(GL_TEXTURE_2D);	// ��������
		glLineWidth(1.0);			// �ָ��߿�
		glPopAttrib();					
		
		glPopMatrix();				// ���������ջ
	}
}


/****************************************************************/
/* Function: ·�������ֵ											*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlppathInterpolation() 
{
	int i;
	
	float m_InsertDdis=1;			// ��ֵ��� 

	double x1,y1,z1,x2,y2,z2;
	PCordinate ppt ;  

	m_FlayPathTempPts.RemoveAll();	// ��ʱ�洢����·��
	for(i=0;i<m_FlayPath.GetSize()-1;i++)
	{
		x1=m_FlayPath.GetAt(i)->x;	// ��ȡ����·����ǰ���x����
		y1=m_FlayPath.GetAt(i)->y;	// ��ȡ����·����ǰ���y����
		z1=m_FlayPath.GetAt(i)->z;	// ��ȡ����·����ǰ���z����

		x2=m_FlayPath.GetAt(i+1)->x; // ��ȡ����·����һ���x����
		y2=m_FlayPath.GetAt(i+1)->y; // ��ȡ����·����һ���y����
		z2=m_FlayPath.GetAt(i+1)->z; // ��ȡ����·����һ���z����

		if(i==0) //����Ƿ���·������ʼ��,���¼
		{
			ppt = new Cordinate;
			ppt->x=x1;
			ppt->y=y1;
			ppt->z=z1;
			m_FlayPathTempPts.Add(ppt);
		}

		//�������·����ǰ������һ��ľ���

		double L = Dist(CVector3(x1,y1,z1),CVector3(x2,y2,z2));
		int M=L/m_InsertDdis;			// ����Ӧ�ڲ���������
		for(int j=1;j<=M;j++)
		{
			//�����ڲ������µ��ڲ�����ά����
			ppt = new Cordinate;
			ppt->x=x1+j*m_InsertDdis/L*(x2-x1);
			ppt->z=z1+j*m_InsertDdis/L*(z2-z1);
			//ppt->y=GetHeight(ppt->x,-ppt->z);
			ppt->y=y1+j*m_InsertDdis/L*(y2-y1);
			m_FlayPathTempPts.Add(ppt); // ��¼�ڲ������
		}

		ppt = new Cordinate;
		ppt->x=x2;
		ppt->y=y2;
		ppt->z=z2;
		m_FlayPathTempPts.Add(ppt);		// ������·����һ�������Ҳ��¼����

	}

	m_FlayPath.RemoveAll();				// ����·���������
	for(i=0;i<m_FlayPathTempPts.GetSize();i++)
	{
		ppt = new Cordinate;
		ppt->x=m_FlayPathTempPts.GetAt(i)->x;
		ppt->y=m_FlayPathTempPts.GetAt(i)->y;
		ppt->z=m_FlayPathTempPts.GetAt(i)->z;
		m_FlayPath.Add(ppt);			// ����������·������

	}
	Invalidate(FALSE);
	MessageBox("·�������ֵ���!","·�������ֵ",MB_ICONINFORMATION);	
}


/****************************************************************/
/* Function: �������·��											*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlypathSave() 
{
	CString 	NeededFile;
	char 		FileFilter[] = "����·��(*.pth)|*.pth||";

	//�����ļ��Ի�������
	DWORD 		FileDialogFlag = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog FileDialogBoxFile(FALSE, NULL, 0, FileDialogFlag, FileFilter, this);
	FileDialogBoxFile.m_ofn.lpstrTitle = "�������·���ļ�";
	char		FileName[200];

	CString tt[3];
	if( FileDialogBoxFile.DoModal() == IDOK ) //����Ի���ɹ���
	{	
		NeededFile = FileDialogBoxFile.GetPathName(); //�õ��ļ���
		sprintf(FileName, "%s", NeededFile);
		if(strcmp(FileDialogBoxFile.GetFileExt(),"pth")!=0) 
			strcat(FileName,".pth"); //��ӷ���·���ļ���չ��

		if(FlyPathSave(FileName)) //�������·������ɹ�
			MessageBox("·���㱣�����","�������·��",MB_ICONWARNING);

	}		
	Invalidate(FALSE);

}


/****************************************************************/
/* Function: ����·������											*/
/****************************************************************/
int CMy3DSymbolLibNewView::FlyPathSave(char *pathfile)
{
	FILE	*fpw;
	char	message[200];

	if((fpw = fopen(pathfile, "w")) == NULL)			// ���д���ļ�ʧ��
	{ 
		sprintf(message, "�ļ� %s ������Ч", pathfile);
		MessageBox(message,"�������·�����굽�ļ�",MB_ICONWARNING);
		return 0;										// ����ʧ��
	}

	fprintf(fpw, "%d\n", m_FlayPath.GetSize());			// д�����·�����������
	for(int i=0;i<m_FlayPath.GetSize();i++)
	{
		// ���ļ�fpwд�����·����������ά����
		fprintf(fpw, "%lf,%lf,%lf\n",m_FlayPath.GetAt(i)->x, m_FlayPath.GetAt(i)->y, m_FlayPath.GetAt(i)->z);
	}
	fclose(fpw);		// �ر��ļ�
	return 1;			// ���سɹ�
}


/****************************************************************/
/* Function: �򿪷���·��											*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyOpenpath() 
{
	CString 	NeededFile;
	char 		FileFilter[] = "����·��(*.pth)|*.pth||";
	//�����ļ��Ի�������
	DWORD 		FileDialogFlag = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog FileDialogBoxFile(TRUE, NULL, 0, FileDialogFlag, FileFilter, this);
	FileDialogBoxFile.m_ofn.lpstrTitle = "�򿪷���·���ļ�";
	FileDialogBoxFile.m_ofn.lpstrInitialDir = m_AllDataPath;
	char		FileName[200];

	CString tt[3];
	if( FileDialogBoxFile.DoModal() == IDOK )			// ����Ի���ɹ���
	{	
		NeededFile = FileDialogBoxFile.GetPathName();	// �õ��ļ���
		sprintf(FileName, "%s", NeededFile);
		if(strcmp(FileDialogBoxFile.GetFileExt(),"pth")!=0) 
			strcat(FileName,".pth");					// ��ӷ���·���ļ���չ��

		if(FlyPathRead(FileName)) //��ȡ����·���ļ����ݶ�̬������
			MessageBox("��·�������","��ʾ",MB_ICONWARNING);
		if(m_FlayPath.GetSize()>1)						// �������·�������������>1
		{
			m_ShowFlyPath=TRUE;							// ��ʾ����·��
			m_PathFlag=TRUE;							// ��ʶ����·���򿪳ɹ�
		}
		else
			m_PathFlag=FALSE;							// ��ʶ����·����ʧ��
	}		

	Invalidate(FALSE);
}


/****************************************************************/
/* Function: ��ȡ����·���ļ����ݶ�̬������						*/
/****************************************************************/
int CMy3DSymbolLibNewView::FlyPathRead(char *pathfile)
{
	CString tt,m_strszLine;
	PCordinate ppt = new Cordinate;  

	m_FlayPath.RemoveAll();								// ����·���������

	CStdioFile m_inFile;	

	if(m_inFile.Open (pathfile,CFile::modeRead)==FALSE) // ���ļ�
	{
		return 0;										// ����ʧ�ܱ�־
	}
	m_inFile.ReadString(m_strszLine);					// ��ȡ����·�����������
	while( m_inFile.ReadString(m_strszLine))
	{
		ppt = new Cordinate;

		m_strszLine.TrimLeft(" ");
		m_strszLine.TrimRight("	");
		int nPos=m_strszLine.Find(",");
		tt=m_strszLine.Left(nPos);
		ppt->x=atof(tt);
		m_strszLine=m_strszLine.Right(m_strszLine.GetLength()-nPos-1);
		nPos=m_strszLine.Find(",");
		tt=m_strszLine.Left(nPos);
		ppt->y=atof(tt); 
		m_strszLine=m_strszLine.Right(m_strszLine.GetLength()-nPos-1);
		ppt->z=atof(m_strszLine);
		m_FlayPath.Add(ppt);							// ��¼����·�������

	}
	m_inFile.Close();									// �ر��ļ�

	return 1;											// ���سɹ���־
}


/****************************************************************/
/* Function: ��ʾ��رշ���·��									*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyOnoffpath() 
{
	if(m_ShowFlyPath==TRUE)								// �����ǰ����ʾ����·��
		m_ShowFlyPath=FALSE;							// ��ʶ����ΪFALSE
	else
		m_ShowFlyPath=TRUE;								// ��֮,����ΪTRUE	

	Invalidate(FALSE);
}


/****************************************************************/
/* Function: ����m_ShowFlyPathֵ�޸Ĳ˵��ı�						*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnUpdateFlyOnoffpath(CCmdUI* pCmdUI) 
{
	if(m_ShowFlyPath==TRUE)							// �����ǰ����ʾ����·��
		pCmdUI->SetText("�رշ���·��");				// ���˵���������Ϊ"�رշ���·��"
	else											// �����ǰ�ǹرշ���·��
		pCmdUI->SetText("��ʾ����·��");				// ���˵���������Ϊ"��ʾ����·��"
}


/****************************************************************/
/* Function: ���̶��߶�����										*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyStaticheight() 
{
	if(m_FlayPath.GetSize()<=0)							// �������·�����������<=0��������·��Ϊ��
	{
		MessageBox("û������·���ļ�","�������",MB_ICONWARNING);
		return;
	}

	m_fly_start_pause_Enable = TRUE;//[]

	m_FlyHeightType = GIS_FLY_STATICHEIGHT;				// ������������Ϊ�̶��߶�����
	m_StaticHeight = (m_maxHeight+m_minHeight)/2.0;	// ȡ�̶��߶�ֵ=����������С�߶ȵ�1/4
	
	m_flypathPtIndex=0;									// ����·����������=0

	SetFLyTimer();										// ������ά���μ�ʱ��
}


void CMy3DSymbolLibNewView::OnUpdateFlyStaticheight(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(	m_PathFlag == TRUE);				// �����Ƿ������Ч����·��ֵ���ò˵�״̬
	if (m_FlyHeightType==GIS_FLY_STATICHEIGHT)			// �����ǰ��"�ع̶��߶�����"��ʽ
		pCmdUI->SetCheck(TRUE);							// �˵�ǰ����ѡ�б�־"��"
	else
		pCmdUI->SetCheck(FALSE);						// ��������		
}


/****************************************************************/
/* Function: ���÷��м�ʱ��										*/
/****************************************************************/
void CMy3DSymbolLibNewView::SetFLyTimer()
{
	SetTimer(1,m_flyspeed,NULL);						// m_flyspeed:���м�ʱ��ʱ����,
}


/****************************************************************/
/* Function: ��ʱ��,����Ƶ�ʿ�����								*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case 1:  // ��ά����
		if(m_flypathPtIndex<=m_FlayPath.GetSize()-2)	// �����ǰ����·�����������<=·�����������-1
		{
			// ��������·�����������������������
			GetCameraCorrdinate(
				m_FlayPath.GetAt(m_flypathPtIndex)->x,\
				m_FlayPath.GetAt(m_flypathPtIndex)->y,\
				m_FlayPath.GetAt(m_flypathPtIndex)->z,\
				m_FlayPath.GetAt(m_flypathPtIndex+1)->x,\
				m_FlayPath.GetAt(m_flypathPtIndex+1)->y,\
				m_FlayPath.GetAt(m_flypathPtIndex+1)->z
				);
			Invalidate(FALSE);
			m_flypathPtIndex++;							// ����·����ǰ����������+1
		}
		else
		{
			m_flypathPtIndex=0;							// ���˷���β,������·����ǰ��������������Ϊ0,���ӷ���·����ʼ�㿪ʼ����
		}
		break;  

	case 2: // ģ��ѡ�н��к����ɫ��˸��ʾ
		if(wireG == 0)
		{
			wireR = 1;
			wireG = 1;
			wireB = 1;
		}
		else
		{
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
/* Function: ��������·�����������������������					*/
/****************************************************************/
void CMy3DSymbolLibNewView::GetCameraCorrdinate(double x1, double y1, double z1, double x2, double y2, double z2)
{
	//(x1,y1,x1):����·����ǰ������

	//(x2,y2,x2):����·����һ������ 

	if(m_FlyHeightType == GIS_FLY_STATICHEIGHT)				// �̶��߶ȷ��з�ʽ
	{
		if(m_StaticHeight < 85)
			m_StaticHeight = 85;
		m_vLook.x = x2;//�۲��x����
		m_vLook.y = m_StaticHeight;//�۲��y����=y2+m_StaticHeight�̶��߶�ֵ
		m_vLook.z = z2;//�۲��z����

		m_vEyePosition.x = x1;//�ӵ�x����
		m_vEyePosition.y = m_vLook.y;//�ӵ�y����=�۲��y����
		m_vEyePosition.z = z1;//�ӵ�z���� 

	}
	//����Ը߶�(����·��)����ʱ�������һ�������߶�
	else if(m_FlyHeightType == GIS_FLY_PATHHEIGHT)
	{
		//����Ը߶�����
		m_vLook.x=x2;										// �۲��x����
		m_vLook.y=y2+m_StaticHeight + 1;						// �۲��y����=y2+m_StaticHeight�̶��߶�ֵ
		m_vLook.z=z2;										// �۲��z����

		//�����֮�����
		float distance = sqrt((x2-x1)*(x2-x1)+(z2-z1)*(z2-z1));
		//������Ǽ���߶Ȳ�
		float dh = distance * tan(m_ViewUpDown * PAI_D180);

		m_vEyePosition.x=x1;								// �ӵ�x����
		m_vEyePosition.y=m_vLook.y+dh;						// �ӵ�y����=�۲��y����+�߲�
		m_vEyePosition.z=z1;								// �ӵ�z����

	}
}


/****************************************************************/
/* Function: ����Ը߶����η�ʽ									*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyRoutineheight() 
{
	if(m_FlayPath.GetSize()<=0)//�������·�����������<=0��������·��Ϊ��
	{
		MessageBox("û������·���ļ�","�������",MB_ICONWARNING);
		return;
	}

	m_fly_start_pause_Enable = TRUE;//[]

	m_FlyHeightType = GIS_FLY_PATHHEIGHT;					// ������������Ϊ��Ը߶�����

	
	m_StaticHeight = 0;										// ������Ը߲�ֵ

	m_flypathPtIndex=0;										// ����·�������ʼ����=0
	SetFLyTimer();											// ������ά���μ�ʱ��
}


/****************************************************************/
/* Function: ���ò˵��Ƿ�����ѡ�б�ʶ"��"							*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnUpdateFlyRoutineheight(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(	m_PathFlag == TRUE);					// �����Ƿ������Ч����·��ֵ���ò˵�״̬
	if (m_FlyHeightType==GIS_FLY_PATHHEIGHT)				// �����ǰ��"����Ը߶�����"��ʽ
		pCmdUI->SetCheck(TRUE);								// �˵�ǰ����ѡ�б�־"��"
	else
		pCmdUI->SetCheck(FALSE);								// ��������	
}


/****************************************************************/
/* Function: ��ʼ/��ͣ����										*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyPlaypause() 
{
	if(m_FlyPause==FALSE)									// ���������ͣ����,����������״̬
	{
		m_FlyPause=TRUE;									// ������ͣ��ʶm_FlyPause=TRUE
		KillTimer(1);										// ���ٶ�ʱ��1
	}
	else													// �����������״̬
	{
		m_FlyPause=FALSE;									// ������ͣ��ʶm_FlyPause=FALSE
		SetFLyTimer();										// ���÷���ʱ����,��������
	}
}


/****************************************************************/
/* Function: ����m_FlyPauseֵ���ò˵�ID_FLY_PLAYPAUSE�ı�			*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnUpdateFlyPlaypause(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_fly_start_pause_Enable==TRUE);//[]
	if(m_FlyPause==TRUE)						// �����������״̬
		pCmdUI->SetText("��ʼ����");				// ���ò˵�ID_FLY_PLAYPAUSE�ı�
	else										// ���������ͣ����,����������״̬
		pCmdUI->SetText("��ͣ����");				// ���ò˵�ID_FLY_PLAYPAUSE�ı�
} 


/****************************************************************/
/* Function: ֹͣ����											*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyStop() 
{
	KillTimer(1);						// ���ٶ�ʱ��1
	m_flypathPtIndex=0;					// ����·����������=0
	m_FlyPause=FALSE;					// ��ͣ��ʶΪFALSE
	m_far=10000;						// �ָ�gluPerspective()��������ƽ��ͷ���Զ����ƽ��ľ���
	m_fly_start_pause_Enable = FALSE;	//[]
}


/****************************************************************/
/* Function: ����ǰ��											*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyOnestep() 
{
	//�������·����������>=0����<����·����������-1,��������ʾ����
	//ֻҪ����·����������û�е�����·��β,�Ϳ���ִ�е���ǰ��
	if(m_flypathPtIndex>=0 && m_flypathPtIndex<m_FlayPath.GetSize()-1)
	{

		KillTimer(1);								// ���ٶ�ʱ��1	
		m_FlyPause=TRUE;							// ��ͣ��ʶΪTRUE
		//��������·�����������������������
		GetCameraCorrdinate(
			m_FlayPath.GetAt(m_flypathPtIndex)->x,\
			m_FlayPath.GetAt(m_flypathPtIndex)->y,\
			m_FlayPath.GetAt(m_flypathPtIndex)->z,\
			m_FlayPath.GetAt(m_flypathPtIndex+1)->x,\
			m_FlayPath.GetAt(m_flypathPtIndex+1)->y,\
			m_FlayPath.GetAt(m_flypathPtIndex+1)->z
			);

		Invalidate(FALSE);
		m_flypathPtIndex++;							// ��ǰ��·����������+1
	}	
} 


/****************************************************************/
/* Function: ������Ұ����											*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyViewEnlarge() 
{
	m_ViewWideNarrow += 5.0;						// m_ViewWideNarrowֵ����
	OnDraw (GetDC());								// ˢ����ά����
}


/****************************************************************/
/* Function: ������Ұ��С											*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyViewSmall() 
{
	m_ViewWideNarrow -= 5.0;						// m_ViewWideNarrowֵ��С
	OnDraw (GetDC());								// ˢ����ά����
}


/****************************************************************/
/* Function: ���и߶�����											*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyHeightUp() 
{
	m_StaticHeight += 8;							// �߶�ֵ����(����=8,�������趨)
	OnDraw (GetDC());								// ˢ����ά����	
}


/****************************************************************/
/* Function: ���и߶Ƚ���											*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyHeightDown() 
{
	m_StaticHeight -= 8;							// �߶�ֵ����(����=8,�������趨)
	OnDraw (GetDC());								// ˢ����ά����	

}


/****************************************************************/
/* Function: �����ӽ�����(����)									*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyViewUp() 
{
	m_ViewUpDown += 1.0;
	OnDraw (GetDC());								// ˢ����ά����	
}


/****************************************************************/
/* Function: �����ӽ�����(����)									*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlyViewDown() 
{
	m_ViewUpDown -= 1.0;
	OnDraw (GetDC());								// ˢ����ά����	
}


/****************************************************************/
/* Function: ����												*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlySpeedUp() 
{
	m_flyspeed-=2;									// ����ʱ�ļ�ʱ��ʱ�������� 
	if(m_flyspeed<=1)								// �����ʱ��ʱ����<=1,����
		m_flyspeed=1;
	SetFLyTimer();									// ���÷��м�ʱ��
}


/****************************************************************/
/* Function: ����												*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnFlySpeedDown() 
{
	m_flyspeed+=2;									// ����ʱ�ļ�ʱ��ʱ�������� 
	SetFLyTimer();									// ���÷��м�ʱ��
}


/****************************************************************/
/* Function: ��ά���ε����ȼ�����									*/
/****************************************************************/
void CMy3DSymbolLibNewView::DisplayHelp()
{
	char str[20][50],strdis[2000];

	strdis[0]='\0';

	strcpy(str[0]," �����   ��ǰ�����ƶ�\n");
	strcpy(str[1]," �����   �������ƶ�\n");
	strcpy(str[2]," �����   �������ƶ�\n");
	strcpy(str[3]," �����   ���ҷ����ƶ�\n");
	strcpy(str[4],"  J ��    ���м���\n");
	strcpy(str[5],"  M ��    ���м���\n");
	strcpy(str[6],"  I ��    ������Ұ����\n");
	strcpy(str[7],"  O ��    ������Ұ��С\n");
	strcpy(str[8],"  G ��     ���߷��и߶�\n");
	strcpy(str[9],"  B ��     ���ͷ��и߶�\n");
	strcpy(str[10],"  H ��    ���й۲�����\n");
	strcpy(str[11],"  N ��    ���й۲�����\n");
	strcpy(str[12],"  P ��    ��ʼ/��ͣ����\n");
	strcpy(str[13],"  S ��    ֹͣ����"); 

	for(int i=0;i<14; i++)
		strcat(strdis,str[i]);
	MessageBox(strdis,"��ά�����ȼ�˵��",MB_OK);

	//TextFlyHelp();
}

void CMy3DSymbolLibNewView::TextFlyHelp()
{
	// ��ʾ����
	
	Font->Settext(350,485,"�����   ��ǰ�����ƶ�", hFont, 1, 0,0);
	Font->Settext(350,500,"�����   �������ƶ�", hFont, 1, 0,0);
	Font->Settext(350,515,"�����   �������ƶ�", hFont, 1, 0,0);
	Font->Settext(350,530,"�����   ���ҷ����ƶ�", hFont, 1, 0,0);

	Font->Settext(550,485,"J ��    ���м���", hFont, 1, 0,0);
	Font->Settext(550,500,"M ��    ���м���", hFont, 1, 0,0);
	Font->Settext(550,515,"I ��    ������Ұ����", hFont, 1, 0,0);
	Font->Settext(550,530,"O ��    ������Ұ��С", hFont, 1, 0,0);

	Font->Settext(750,485,"H ��    ���й۲�����", hFont, 1, 0,0);
	Font->Settext(750,500,"N ��    ���й۲�����", hFont, 1, 0,0);
	Font->Settext(750,515,"P ��    ��ʼ/��ͣ����", hFont, 1, 0,0);
	Font->Settext(750,530,"S ��    ֹͣ����", hFont, 1, 0,0); 
}


/****************************************************************/
/* Function: ��ʼ����ʾ�б�										*/
/****************************************************************/
void CMy3DSymbolLibNewView::InitList()
{
	m_ClockList=glGenLists(1);   
	m_SkyList=m_ClockList+1 ;						// ���������ʾ�б�

	MakeClockList();								// ����ʱ��ָ������ʾ�б� 
	
		
	m_Rail3DwayList=m_ClockList+2;					//��·��άģ����ʾ�б�

}


/****************************************************************/
/* Function: ����ʱ��ָ������ʾ�б�								*/
/****************************************************************/
void CMy3DSymbolLibNewView::MakeClockList()
{
	glNewList(m_ClockList,GL_COMPILE);				// ������ʾ�б�
	float R=0.5,x,y;								// ʱ��Բ�̰뾶
	int i;

	glColor3f(0.0, 1.0, 1.0);						// ����������ɫ

	x=R*cos((0)*PAI_D180)+0.37;						// ����ƫ������׼��д����ĸ"E"����ʾ�̶�3
	y=R*sin((0)*PAI_D180)+0.48;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"E");			// ����������λ��д��E����ʾ���򡰶���

	x=R*cos((90)*PAI_D180)+0.47;					// ����ƫ������׼��д����ĸ"N"����ʾ�̶�12
	y=R*sin((90)*PAI_D180)+0.36;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"N");			// ����������λ��д��N����ʾ���򡰱���

	x=R*cos((180)*PAI_D180)+0.59;					// ����ƫ������׼��д����ĸ"W" ����ʾ�̶�9
	y=R*sin((180)*PAI_D180)+0.48;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"W");			// ����������λ��д��W����ʾ��������

	x=R*cos((270)*PAI_D180)+0.48;					// ����ƫ������׼��д����ĸ"S" ����ʾ�̶�6
	y=R*sin((270)*PAI_D180)+0.58;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"S");			// ����������λ��д��S����ʾ�����ϡ�

	glColor3f(1.0, 1.0, 1.0);						// ����ʱ�ӿ̶�������ɫ

	x=R*cos((30)*PAI_D180)+0.39;					// ��������
	y=R*sin((30)*PAI_D180)+0.43;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"2");			// д�����̶ֿ�


	x=R*cos((60)*PAI_D180)+0.42;
	y=R*sin((60)*PAI_D180)+0.40;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"1");			// д�����̶ֿ�1


	x=R*cos((120)*PAI_D180)+0.49;
	y=R*sin((120)*PAI_D180)+0.38;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"11");			// д�����̶ֿ�11

	x=R*cos((150)*PAI_D180)+0.55;
	y=R*sin((150)*PAI_D180)+0.42;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"10");			// д�����̶ֿ�10


	x=R*cos((210)*PAI_D180)+0.58;
	y=R*sin((210)*PAI_D180)+0.53;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"8");			// д�����̶ֿ�8

	x=R*cos((240)*PAI_D180)+0.54;
	y=R*sin((240)*PAI_D180)+0.58;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"7");			// д�����̶ֿ�7


	x=R*cos((300)*PAI_D180)+0.43;
	y=R*sin((300)*PAI_D180)+0.58;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"5");			// д�����̶ֿ�5

	x=R*cos((330)*PAI_D180)+0.40;
	y=R*sin((330)*PAI_D180)+0.52;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"4");			// д�����̶ֿ�4

	//����ʱ��Բ��Բ�̵���ɫ
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(2.0);								// �����߿�

	// ����ʱ��Բ��Բ��
	glBegin(GL_LINE_STRIP);
	for ( i=0;i<=360;i++)
	{
		x=R*cos(i*PAI_D180)+0.5;
		y=R*sin(i*PAI_D180)+0.5;
		glVertex2f(x,y);
	}
	glEnd();

	// ����ʱ���ڱ�ʾСʱ֮��Ŀ̶�,��Բ���ʾ	
	float d;
	for (i=0;i<=360;i+=6)
	{

		switch(i)
		{
		case 0:										// ��N(12��)��
			glColor3f(0.0, 1.0, 1.0);				// ������ɫ
			glPointSize(4.0);						// ���õ�Ĵ�С
			break;
		case 90:									// ��W(9��)��
			glColor3f(0.0, 1.0, 1.0);				// ������ɫ
			glPointSize(4.0);						// ���õ�Ĵ�С
			break;
		case 180:									// ��S(6��)��
			glColor3f(0.0, 1.0, 1.0);				// ������ɫ
			glPointSize(4.0);						// ���õ�Ĵ�С
			break;
		case 270:									// ��E(3��)��
			glColor3f(0.0, 1.0, 1.0);				// ������ɫ
			glPointSize(4.0);						// ���õ�Ĵ�С
			break;
		default:
			glColor3f(0.77, 0.67, 0.95);			// ������ɫ
			glPointSize(2.0);						// ���õ�Ĵ�С
			break;
		}

		if(i%30==0 && i%90!=0)						// ����ʱ�̴�(��7��,8���)
		{	 
			glColor3f(1.0, 0.0, 1.0);				// ������ɫ
			glPointSize(3.0);						// ���õ�Ĵ�С
		}

		d=0.04;										// ƫ����
		x=R*cos(i*PAI_D180)+0.5;					// ����x����
		y=R*sin(i*PAI_D180)+0.5;					// ����y����

		//���Ƶ��־
		glBegin(GL_POINTS);
		x=x-d*cos(i*PAI_D180);
		y=y-d*sin(i*PAI_D180);
		glVertex2f(x,y);
		glEnd();
	}
	glLineWidth(1.0);								// �����߿�
	glEndList();									// ������ʾ�б�

}


/****************************************************************/
/* Function: ʱ��ָ����Ļ���										*/
/****************************************************************/
void CMy3DSymbolLibNewView::DrawClock()
{
	glPushAttrib(GL_CURRENT_BIT);					// ����������ɫ����
	glPushMatrix();									// ѹ������ջ
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);		// �߻��Ʒ�ʽ
	glDisable(GL_TEXTURE_2D);						// �ر�����	
	SetClockProjectionNavigate();					// ����ָ�����ͶӰ����
	glCallList(m_ClockList);						// ����ָ����ʱ�ӵ���ʾ�б�
	DrawNorthPt();									// ����ָ����

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);		// �����Ʒ�ʽ
	glEnable(GL_TEXTURE_2D);						// ������	
	glLineWidth(1.0);								// �����߿�
	glColor3f(1.0, 1.0, 1.0);						// ������ɫ
	glPopMatrix();									// ���������ջ
	glPopAttrib();

}

void CMy3DSymbolLibNewView::SetClockProjectionNavigate()
{
	float wh=120;									// ����ʱ�ӵĸ߶�
	glViewport(0, WinViewY-wh,wh, wh);				// �����ӿ�λ�úʹ�С
	glMatrixMode( GL_PROJECTION );					// ���õ�ǰ����Ϊ͸�Ӿ���
	glLoadIdentity();								// ����ǰ�����û�Ϊ��λ�� 
	glOrtho (0.0f,1.0,0.0f, 1.0f, -1.0f, 1.0f);
	glMatrixMode( GL_MODELVIEW );					// ���õ�ǰ����Ϊģ�;���
	glLoadIdentity ();								// ����ǰ�����û�Ϊ��λ�� 
}

 
/****************************************************************/
/* Function: ����ָ����											*/
/****************************************************************/
void CMy3DSymbolLibNewView::DrawNorthPt()
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);		// ����䷽ʽ����
	glDisable(GL_TEXTURE_2D);						// �ر�����		
	float R=0.5;

	float x1,y1,x2,y2,x3,y3;
	float mPtangle=25;
	float tempangle;
	float L,L1,L2;
	L1=0.3; 
	L2=0.2;
	x1=0.5;y1=0.5;									// ʱ��Բ�ĵ����ָ꣬����Χ�Ƹõ����ָ����ת
	x3=x1+L1*cos((m_NorthPtangle)*PAI_D180);
	y3=y1+L1*sin((m_NorthPtangle)*PAI_D180);

	//���ָ����ָ���λ�ڵ�1����
	if(m_NorthPtangle>=0 && m_NorthPtangle<=90)
	{	
		tempangle=m_NorthPtangle-mPtangle;
		L=0.1/cos(mPtangle*PAI_D180);
		x2=x1-L2*cos(tempangle*PAI_D180);
		y2=y1-L2*sin(tempangle*PAI_D180);

		glColor3f(1.0, 1.0, 0.0);						// ������ɫ
		glBegin(GL_TRIANGLES);							// �������������
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
		glEnd();

		glColor3f(1.0, 0.0, 0.0);						// ������ɫ
		tempangle=m_NorthPtangle+mPtangle;
		x2=x1-L2*cos(tempangle*PAI_D180);
		y2=y1-L2*sin(tempangle*PAI_D180);
		glBegin(GL_TRIANGLES);							// �����Ҳ�������
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
		glEnd();
	}

	//���ָ����ָ���λ�ڵ�2����
	if(m_NorthPtangle>90 && m_NorthPtangle<=180)
	{	

		tempangle=180-m_NorthPtangle-mPtangle;
		x2=x1+L2*cos(tempangle*PAI_D180);
		y2=y1-L2*sin(tempangle*PAI_D180);

		glColor3f(1.0, 1.0, 0.0);					// ������ɫ
		glBegin(GL_TRIANGLES);						// �������������
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
		glEnd();

		glColor3f(1.0, 0.0, 0.0);					// ������ɫ
		tempangle=180-m_NorthPtangle+mPtangle;
		x2=x1+L2*cos(tempangle*PAI_D180);
		y2=y1-L2*sin(tempangle*PAI_D180);
		glBegin(GL_TRIANGLES);						// �����Ҳ�������
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
		glEnd();
	}

	//���ָ����ָ���λ�ڵ�3����
	if(m_NorthPtangle>180 && m_NorthPtangle<=270)
	{	

		tempangle=m_NorthPtangle-180-mPtangle;
		x2=x1+L2*cos(tempangle*PAI_D180);
		y2=y1+L2*sin(tempangle*PAI_D180);

		glColor3f(1.0, 1.0, 0.0);					// ������ɫ
		glBegin(GL_TRIANGLES);						// �������������
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
		glEnd();

		glColor3f(1.0, 0.0, 0.0);					// ������ɫ
		tempangle=m_NorthPtangle-180+mPtangle;
		x2=x1+L2*cos(tempangle*PAI_D180);
		y2=y1+L2*sin(tempangle*PAI_D180);
		glBegin(GL_TRIANGLES);						// �����Ҳ�������
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
		glEnd();
	}

	//���ָ����ָ���λ�ڵ�4����
	if(m_NorthPtangle>270 && m_NorthPtangle<=360)
	{	

		tempangle=360-m_NorthPtangle-mPtangle;
		x2=x1-L2*cos(tempangle*PAI_D180);
		y2=y1+L2*sin(tempangle*PAI_D180);

		glColor3f(1.0, 1.0, 0.0);					// ������ɫ
		glBegin(GL_TRIANGLES);						// �������������
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
		glEnd();

		glColor3f(1.0, 0.0, 0.0);					// ������ɫ
		tempangle=360-m_NorthPtangle+mPtangle;
		x2=x1-L2*cos(tempangle*PAI_D180);
		y2=y1+L2*sin(tempangle*PAI_D180);
		glBegin(GL_TRIANGLES);						// �����Ҳ�������
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
		glEnd();
	}

	glColor3f(0.4, 0.47, 0.72);						// ������ɫ
	glLineWidth(2.0);								// �����߿�
	glBegin(GL_LINES);								// ָ�����¶�ֱ��
	glVertex2f(x1,y1);
	x2=x1-0.1*cos((m_NorthPtangle)*PAI_D180);
	y2=y1-0.1*sin((m_NorthPtangle)*PAI_D180);
	glVertex2f(x2,y2);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); 
	glEnable(GL_TEXTURE_2D);						// ��������		
	glLineWidth(1.0);								// �����߿�
}


/****************************************************************/
/* Function: ��ָ��λ������ı�									*/
/****************************************************************/
void CMy3DSymbolLibNewView::PrintText(float x, float y, char *string)
{
	int length;
	length = (int) strlen(string);					// �ַ�������
	glRasterPos2f(x,y);								// ��λ��ǰ���
	for (int m=0;m<length;m++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[m]); // ��λͼ��ʽ��ָ�����������һ���ַ���
	}

}


/****************************************************************/
/* Function: ����������ӵ�����͹۲���������ʱ��ָ����ָ��Ƕ�	*/
/****************************************************************/
void CMy3DSymbolLibNewView::GetNorthPtangle()
{
	float dx,dz,ar;
	dx=m_vEyePosition.x-m_vLook.x;					// ����ӵ���۲��x����֮��
	dz=m_vEyePosition.z-m_vLook.z;					// ����ӵ���۲��z����֮��

	if(dx==0)										// ���dx==0
	{
		if(dz>=0)									// ���dz>=0
			m_NorthPtangle=90;						// ָ�����ʼָ��Ƕ�=90��ָ����Ļ���棨Z�Ḻ����
		else
			m_NorthPtangle=270;						// ָ�����ʼָ��Ƕ�=270��ָ����Ļ���棨Z��������
	}
	else
	{
		if(dx>0) 
		{
			if(dz>0)								// ��2����
			{
				ar=fabs(atan(dx/dz));
				m_NorthPtangle=90+ar*HDANGLE;		// ָ�����ʼָ��Ƕ�
			}
			else									// ��3����
			{
				ar=fabs(atan(dx/dz));
				m_NorthPtangle=270-ar*HDANGLE;		// ָ�����ʼָ��Ƕ�
			}
		}

		if(dx<0)
		{
			if(dz>0)								// ��1����
			{
				ar=fabs(atan(dx/dz));
				m_NorthPtangle=90-ar*HDANGLE;		// ָ�����ʼָ��Ƕ�
			}
			else									// ��4����
			{
				ar=fabs(atan(dx/dz));
				m_NorthPtangle=270+ar*HDANGLE;		// ָ�����ʼָ��Ƕ�
			}
		}

	}
}


/****************************************************************/
/* Function: ���ɻ��Ʊ��������ʾ�б�								*/
/****************************************************************/
void CMy3DSymbolLibNewView::MakeSkykList()
{
	glNewList(m_SkyList , GL_COMPILE);
	
	CreateSkyBox();
	glEndList();
}


/****************************************************************/
/* Function: ������ձ���											*/
/****************************************************************/
void CMy3DSymbolLibNewView::DrawSky()
{
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glPushMatrix();
	if(m_bShowbreviary==TRUE)				//�����ʾ����ͼ
	{
		SetSkyProjectionNavigate() ;		// ���õ���ͼ�ı������ͶӰ
	}
	glPopMatrix();

	SetSkyProjection() ;					// ���ñ������ͶӰ
	glCallList(m_SkyList);

	glPopMatrix();
	glPopAttrib();
}


/****************************************************************/
/* Function: �������ͶӰ����										*/
/****************************************************************/
void CMy3DSymbolLibNewView::SetSkyProjection()
{
	glViewport(0 ,  0 ,  WinViewX ,  WinViewY);				// �����ӿڴ�С��λ��

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();            
	gluPerspective(50.0 + m_ViewWideNarrow , (float)WinViewX/(float)WinViewY , m_near , m_far);		

	glMatrixMode(GL_MODELVIEW);								// �������Ϊģ��ģ�;���

	glLoadIdentity();										// ����ǰ�����û�Ϊ��λ����       

	SetCamra();
}


/****************************************************************/
/* Function: ������յ���ͼͶӰ����								*/
/****************************************************************/
void CMy3DSymbolLibNewView::SetSkyProjectionNavigate()
{
	glClearDepth(1.0f);								// ���ó�ʼ����Ȼ���ֵ
	glEnable(GL_DEPTH_TEST);						// ������Ȳ���
	glDepthFunc(GL_LESS);							// �ڵ���glEnable(GL_DEPTH_TEST); ������������Ժ󣬵���ȱ仯С�ڵ�ǰ���ֵʱ���������ֵ��

	glViewport(WinViewX*5/6 ,  WinViewY*5/6 , WinViewX/6 ,  WinViewY/6) ; // �����ӿڴ�С

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();            
	gluPerspective(50.0 + m_ViewWideNarrow , (float)WinViewX/(float)WinViewY , m_near , m_far);		

	//��������ͶӰ�Ӿ���
	
	glMatrixMode(GL_MODELVIEW);							// �������Ϊģ��ģ�;���
	glLoadIdentity();									// ����ǰ�����û�Ϊ��λ����       

	glClearColor(0.53, 0.81, 0.92, 0.0);				// ����ˢ�±���ɫSkyBlue: 135,206,235
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	// ˢ�±���
	glLoadIdentity();									// ���õ�ǰ��ģ�͹۲����

	SetCamra();
}


/****************************************************************/
/* Function: ����3DSģ�� ���ò���									*/
/****************************************************************/
void CMy3DSymbolLibNewView::On3dsModelLoad()
{
	// TODO: �ڴ���������������

	CString tt,stt;
	FILE *fp;

	CString modelFileFormat = ".3DS";

	PModelParamStruct p3d;

	if(m_i3DModelNum < MODEL_NUM_MAX)
	{
		CDialogModelList dlg1;
		dlg1.m_Dir = m_AllDataPath + "\\" + m_3DModelFolder;
		dlg1.m_format = ".bmp";
		dlg1.m_type = "3DS";

		CString selectItem;
		if(dlg1.DoModal() == IDOK)
		{
			selectItem = dlg1.m_selectItem;
			m_3DModelPath = dlg1.m_Dir + "\\" + selectItem + modelFileFormat;
		}

		else
			return;	


		if((fp=fopen(m_3DModelPath,"r"))==NULL)
		{
			MessageBox("3Dģ���ļ�������!","��ʼ��3Dģ��",MB_ICONINFORMATION+MB_OK);
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
		
		dlg.m_strTitle = "3Dģ�Ͳ�����ʼ��";

		if(m_QueryType==QUERY_COORDINATE && IsSearchPoint) // ��ǰΪ��ѯģʽ,�����Ѿ���ѯ��
		{
			p3d->posX = pt1[0];
			p3d->posZ = pt1[2];
		} 		

		PModelParamStructToModelParamDlg(dlg, p3d);

		if(dlg.DoModal()==IDOK)
		{ 
			ModelParamDlgToPModelParamStruct(dlg, p3d);

			Load3DModel(p3d, MODEL_NEW);

			m_i3DModelNum++;
		}
	} 
}

void CMy3DSymbolLibNewView::Draw3DModel(PModelParamStruct model)
{		
	glPushMatrix();											// ѹ���ջ

	t3DBox t3dBox;
	t3dBox.l = g_3DModel[model->modelID].t3DModelBox.l * model->scale;
	t3dBox.w = g_3DModel[model->modelID].t3DModelBox.w * model->scale;
	t3dBox.h = g_3DModel[model->modelID].t3DModelBox.h * model->scale;

	// ��ȡ����߶�
	int y = GetHeight((float)model->posX,(float)model->posZ) + t3dBox.h/2 + model->posY;		 

	glTranslatef(model->posX,y,model->posZ);					// ģ�Ͷ�λ
	glRotatef(model->rotY, 0.0, 1.0, 0.0);					// ģ����ת	
	glRotatef(model->rotX, 1.0, 0.0, 0.0);					// ģ����ת	
	glRotatef(model->rotZ, 0.0, 0.0, 1.0);					// ģ����ת	
	
		
	m_3ds->Show3ds(model->modelID,0,0.0f,0,model->scale);	// ��ʾ3dsģ��
	

	glPushAttrib(GL_CURRENT_BIT);							// ����������ɫ����
	glDisable(GL_TEXTURE_2D);					 			// ȡ����ͼ
	glPushMatrix();											// ѹ���ջ
	glLineWidth(3);											// �߿�2

	glPushAttrib(GL_CURRENT_COLOR);

	if(m_3DModel.GetAt(model->modelID)->modelSelected)
	{
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
/* Function: 3dģ��ѡ���Լ���������								*/
/****************************************************************/
void CMy3DSymbolLibNewView::On3dsModelSelectSet()
{
	// TODO: �ڴ���������������

	bIsSelect3DModel = !bIsSelect3DModel;
	if(bIsSelect3DModel)
	{
		m_OperateType = SELECT;
		m_mouseShape = MOUSE_SHAPE_SLECT;

		m_QueryType = -1;
	}
	else
	{
		m_OperateType = -1;

		// ������ѡ��ģʽʱ���ر���˸��ʱ��
		if(m_bFlash)
		{
			KillTimer(2);
			m_bFlash = false;
			for(unsigned int i = 0; i < m_pSelectedModelSet.size(); ++i)// i++ Ҫ��һ����ʱ�������洢������ʹ��++i
			{
				if(m_pSelectedModelSet.at(i)->modelType == MODEL_3DS)
					m_3DModel.GetAt(m_pSelectedModelSet.at(i)->modelID)->modelSelected = false;
			}
			m_pSelectedModelSet.clear();
		}

		m_bMouseMoveSelect = false;
		m_mouseShape = MOUSE_SHAPE_ARROW;
	}

	Invalidate(FALSE);
}

void CMy3DSymbolLibNewView::OnUpdate3dsModelSelectSet(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_OperateType == SELECT);
}


/****************************************************************/
/* Function: �ƶ�ģ��,��������µ��������ľ���					*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_OperateType ==MOVE)	// �ƶ�ѡ��3Dģ��
	{
		m_oldMousePos=point;
		ScreenToGL(point);
	}

	m_bIsLBtnDown = false;
	CView::OnLButtonUp(nFlags, point);
}

void CMy3DSymbolLibNewView::On3dsModelMouseMove()
{
	// TODO: �ڴ���������������
	bIsMouseMove3DModel = !bIsMouseMove3DModel;
	if(bIsMouseMove3DModel) 
	{
		m_OperateType = MOVE;
	}
	else
		m_OperateType = -1;

	Invalidate(FALSE);
}

void CMy3DSymbolLibNewView::OnUpdate3dsModelMouseMove(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_OperateType == MOVE);
}


/****************************************************************/
/* Function: ������ת��ʱ�ж�����Ƿ�����3Dģ�Ϳռ䷶Χ��			*/
/****************************************************************/
void CMy3DSymbolLibNewView::JudgeModelSelected(PCordinate ppt)
{
	// ��ȡģ������ά�㼫ֵ
	int minx,maxx,minz,maxz;

	// �������е�3Dģ��,�ж��Ƿ��ڷ�Χ�� 
	for(int j = 0; j < m_i3DModelNum; j++)
	{		
		t3DBox t3dBox;
		t3dBox.w = m_3DModel.GetAt(j)->scale * g_3DModel[j].t3DModelBox.w;
		t3dBox.h = m_3DModel.GetAt(j)->scale * g_3DModel[j].t3DModelBox.h;
		t3dBox.l = m_3DModel.GetAt(j)->scale * g_3DModel[j].t3DModelBox.l;

		POINT pt;
		pt.x = m_3DModel.GetAt(j)->posX;
		pt.y = m_3DModel.GetAt(j)->posZ;

		minx = pt.x - (t3dBox.l * 1.5 )/2;
		maxx = pt.x + (t3dBox.l * 1.5 )/2;
		minz = pt.y - (t3dBox.w * 1.5 )/2;
		maxz = pt.y + (t3dBox.w * 1.5 )/2;

		// ��Ϊ��ǰģ��Ϊ����ƶ�ģ��ʱ�Ͳ��ܸı�ģ�͵�ѡ��״̬
		if((ppt->x >= minx && ppt->x <= maxx ) &&(ppt->z >= minz && ppt->z <= maxz))
		{				
			if(m_OperateType == MOVE)
			{
				m_3DModel.GetAt(j)->modelSelected = true;
			}
			else
			{
				m_3DModel.GetAt(j)->modelSelected = !(m_3DModel.GetAt(j)->modelSelected);	
			}
		} 
		else 
			m_3DModel.GetAt(j)->modelSelected = false;
	}			
}


/****************************************************************/
/* Function: ���뾰���� ���ò���									*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnTreeLoad()
{
	// TODO: �ڴ���������������

	CString tt,stt;
	FILE *fp;
	CString treeTexPath;
	CString treeFileFormat = ".BMP";

	if(m_iTreeModelNum < 50)
	{
		CDialogModelList dlg1;
		dlg1.m_Dir = m_AllDataPath + "\\" + m_TreeModelFolder;
		dlg1.m_format = ".bmp";
		dlg1.m_type = "Tree";

		if(dlg1.DoModal() == IDOK)
		{
			CString selectItem = dlg1.m_selectItem;
			treeTexPath = dlg1.m_Dir + "\\" + selectItem + treeFileFormat;
		}
		else
			return;	

		if((fp=fopen(treeTexPath,"r"))==NULL)
		{
			MessageBox("�������ļ�������!","��ʼ��������ģ��",MB_ICONINFORMATION+MB_OK);
			exit(-1);
		}

		ptree = new CModelStruct;
		ptree->iModelNum = m_iTreeModelNum;
		ptree->strModelPath = treeTexPath;


		// ��ģʽ�Ի���
		paramSet_modeless_dlg = new C3DModelParamSet(this);
		paramSet_modeless_dlg->Create();
		paramSet_modeless_dlg->CenterWindow();


		paramSet_modeless_dlg->m_strTitle = "������ģ��  ������ʼ��";

		paramSet_modeless_dlg->m_modeParam.type = "tree";


		paramSet_modeless_dlg->ShowWindow(SW_SHOW);
	}
	else
	{
		MessageBox("��ľ�Ĵ�С������50!");
	}
}


/*************************************************************************/
/* Function: ������ͼ��Ҫ͸����ʾ��͸����ʾҪ������ͼƬӦ����16λɫ��BMPλͼ	 */
/*************************************************************************/
void CMy3DSymbolLibNewView::LoadT16(char *filename, GLuint &texture)
{  
	glGenTextures(1, &texture);											// ��ȡ1��δʹ�õ���ͼ����
	glBindTexture(GL_TEXTURE_2D, texture);								// ѡ��Ҫ�󶨵���ͼ������
	BITMAPINFOHEADER bitHeader;											// ����λͼ�ṹ
	unsigned char *buffer;												// ����λͼָ��
	buffer=LoadBitmapFileWithAlpha(filename,&bitHeader);				// ����λͼ
	gluBuild2DMipmaps( GL_TEXTURE_2D,									// ����һ��2D��ͼ������
		4,																// ʹ��3����ɫ��RGB��+��ɫ���
		bitHeader.biWidth,												// ͼ���
		bitHeader.biHeight,												// ͼ���
		GL_RGBA,														// ������˳��
		GL_UNSIGNED_BYTE,												// ͼ��������������ֽ�
		buffer															// ָ����ͼ����������
		);																// ������ͼ������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);					// ��С�˲�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);					// �Ŵ��˲�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);	// ˫�����˲�
	free(buffer);																		// �ͷ�λͼ����
} 


/********************************************************************/
/* Function: ��ʾ����ƽ������������תʱ��Ҳ������ת��ʼ������������û�	*/
/********************************************************************/
void CMy3DSymbolLibNewView::ShowTree(int i)
{ 
	float x, y, z;
	x = m_TreeModel.GetAt(i)->xPos;
	z = m_TreeModel.GetAt(i)->zPos;
	float h = 3;

	y = GetHeight(x,z) + m_TreeModel.GetAt(i)->hPos + h; 

	glPushMatrix();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	float mat[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);				// ��ȡ��ͼ����
	CVector3 X(mat[0], mat[4], mat[8]);
	CVector3 Z(mat[1], mat[5], mat[9]); 
	glBindTexture(GL_TEXTURE_2D, g_cactus[i]);
	CVector3 pos(x,y,z);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);glVertex3f((pos+(X+Z)*-h).x, (pos+(X+Z)*-h).y, (pos+(X+Z)*-h).z);	// ���µ�
	glTexCoord2f(1.0,0.0);glVertex3f((pos+(X-Z)* h).x, (pos+(X-Z)* h).y, (pos+(X-Z)* h).z);	// ���µ�
	glTexCoord2f(1.0,1.0);glVertex3f((pos+(X+Z)* h).x, (pos+(X+Z)* h).y, (pos+(X+Z)* h).z);	// ���ϵ�
	glTexCoord2f(0.0,1.0);glVertex3f((pos+(Z-X)* h).x, (pos+(Z-X)* h).y, (pos+(Z-X)* h).z);	// ���ϵ�
	glEnd();
	glDisable(GL_ALPHA);
	glDisable(GL_BLEND);

	glPopMatrix();
}


/****************************************************************/
/* Function: ������б�ʶ,������,���ȵ�,����,��������				*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnCitySymbolLoad()
{
	CString tt,stt;
	FILE *fp;
	CString citySymbolTexPath;
	CString citySymbolFileFormat = ".png";

	if(m_iCitySymbolModelNum < 50)
	{	
		CDialogModelList dlg1;
		dlg1.m_Dir = m_AllDataPath + "\\" + m_CitySymbolFolder;
		dlg1.m_format = ".png";
		dlg1.m_type = "City";

		if(dlg1.DoModal() == IDOK)
		{
			CString selectItem = dlg1.m_selectItem;
			citySymbolTexPath = dlg1.m_Dir + "\\" + selectItem + citySymbolFileFormat;
		}
		else
			return;	

		if((fp=fopen(citySymbolTexPath,"r"))==NULL)
		{
			MessageBox("���б�ʶ�����ļ�������!","��ʼ�����б�ʶ����",MB_ICONINFORMATION+MB_OK);
			exit(-1);
		}

		pCitySymbol = new CModelStruct;
		pCitySymbol->iModelNum = m_iCitySymbolModelNum;
		pCitySymbol->strModelPath = citySymbolTexPath;



		// ��ģʽ�Ի���
		paramSet_modeless_dlg = new C3DModelParamSet(this);
		paramSet_modeless_dlg->Create();
		paramSet_modeless_dlg->CenterWindow();


		paramSet_modeless_dlg->m_strTitle = "���б�ʶ  ������ʼ��";

		paramSet_modeless_dlg->m_modeParam.type = "CitySymbol";
	
		paramSet_modeless_dlg->ShowWindow(SW_SHOW);

	} 
}


/****************************************************************/
/* Function: ��ʾ��ͨ���з���,��������ת����ת���Ƕ�				*/
/****************************************************************/
void CMy3DSymbolLibNewView::ShowCitySymbol0(int i)
{ 
	float x, y, z;
	x = m_CitySymbolModel.GetAt(i)->xPos;
	z = m_CitySymbolModel.GetAt(i)->zPos;
	float h = 0.5;

	glPushMatrix();  
	y = GetHeight(x,z) + m_CitySymbolModel.GetAt(i)->hPos + h;
	glTranslatef(x,y, z); 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	glBindTexture(GL_TEXTURE_2D, g_citySymbolTex[i]); 
	glBegin(GL_QUADS); 

	glTexCoord2f(1.0f, 0.0f); glVertex3f( h, 0, 0.0f);		// ���ϵ�
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 0, 0, 0.0f);		// ���ϵ�
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 0, h, 0.0f);		// ���µ�
	glTexCoord2f(1.0f, 1.0f); glVertex3f( h, h, 0.0f);		// ���µ�

	glEnd();
	glDisable(GL_ALPHA);
	glDisable(GL_BLEND);
	glPopMatrix();
}


/****************************************************************/
/* Function:��ʾ���з���											*/
/****************************************************************/
void CMy3DSymbolLibNewView::ShowCitySymbol(int i)
{ 
	float x, y, z;
	x = m_CitySymbolModel.GetAt(i)->xPos;
	z = m_CitySymbolModel.GetAt(i)->zPos;
	float h = 3.2;

	y = GetHeight(x,z) + m_CitySymbolModel.GetAt(i)->hPos + h; 

	glPushMatrix();

	glEnable(GL_TEXTURE_2D); 
	glEnable(GL_BLEND); 
	glEnable(GL_ALPHA_TEST); 
	glAlphaFunc(GL_GREATER ,0.9);						//0.5���Ի����κ���0~1֮����� 


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// ����Ϊ��ɫ

	float mat[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);				// ��ȡ��ͼ����
	CVector3 X(mat[0], mat[4], mat[8]);
	CVector3 Z(mat[1], mat[5], mat[9]); 
	glBindTexture(GL_TEXTURE_2D, g_citySymbolTex[i]);
	CVector3 pos(x,y,z);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0,0.0);glVertex3f((pos+(X+Z)*-h).x, (pos+(X+Z)*-h).y, (pos+(X+Z)*-h).z);	// ���µ�
	glTexCoord2f(1.0,0.0);glVertex3f((pos+(X-Z)* h).x, (pos+(X-Z)* h).y, (pos+(X-Z)* h).z);	// ���µ�
	glTexCoord2f(1.0,1.0);glVertex3f((pos+(X+Z)* h).x, (pos+(X+Z)* h).y, (pos+(X+Z)* h).z);	// ���ϵ�
	glTexCoord2f(0.0,1.0);glVertex3f((pos+(Z-X)* h).x, (pos+(Z-X)* h).y, (pos+(Z-X)* h).z);	// ���ϵ�

	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_ALPHA);
	glDisable(GL_BLEND);

	glPopMatrix();
}


/****************************************************************/
/* Function: ͸��PNG �������										*/
/****************************************************************/
void CMy3DSymbolLibNewView::LoadPNG(const char *fileName, GLuint &texture) 
{  
	glGenTextures(1, &texture);						// ��ȡ1��δʹ�õ���ͼ����
	glBindTexture(GL_TEXTURE_2D, texture);			// ѡ��Ҫ�󶨵���ͼ������

	BITMAP bm; 
	CImage img;										// ��Ҫͷ�ļ�atlimage.h 
	HRESULT hr = img.Load(fileName); 
	if ( !SUCCEEDED(hr) )							//�ļ�����ʧ�� 
	{ 
		MessageBox(NULL, "�ļ�����ʧ��", MB_OK);
	} 
	HBITMAP hbmp = img; 
	GetObject(hbmp, sizeof(bm), &bm);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glPixelStoref(GL_PACK_ALIGNMENT, 1); 

	glTexImage2D(GL_TEXTURE_2D, 0, 4, bm.bmWidth, bm.bmHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE,bm.bmBits);	//���ﲻ��GL_RGB,һ��Ҫ���ó�4��GL_BGRA�������ܱ���͸����һ�������������Ϊ3��GL_BGR�������Ͳ���͸������ʾ
}


/****************************************************************/
/* Function: ��������Ԥ��ͼƬ 									*/
/****************************************************************/
void CMy3DSymbolLibNewView::OnWeatherLoad()
{
	CString tt,stt;
	FILE *fp;
	CString weatherSymbolTexPath;

	CString weatherFileFormat = ".bmp";

	if(1)
	{	
		CDialogModelList dlg1;
		dlg1.m_Dir = m_AllDataPath + "\\" + m_WeatherFolder;
		dlg1.m_format = ".bmp";
		dlg1.m_type = "Weather";

		if(dlg1.DoModal() == IDOK)
		{
			CString selectItem = dlg1.m_selectItem;
		

			// �޸���ԭ�����ڱ��泡���ļ�ʱδ�ܱ���������Ϣ������
			m_WeatherTex = selectItem + weatherFileFormat;

			weatherSymbolTexPath = dlg1.m_Dir + "\\" + selectItem + weatherFileFormat;
		}
		else
			return;	

		if((fp=fopen(weatherSymbolTexPath,"r"))==NULL)
		{
			MessageBox("���������ļ�������!","��ʼ����������",MB_ICONINFORMATION+MB_OK);
			exit(-1);
		} 

		char cc[256]; 
		sprintf(cc,weatherSymbolTexPath);
		LoadT8(cc,g_weatherTex); 
		bIsWeatherLoad = true; 
	}
}


/****************************************************************/
/* Function: ��ʾ����ͼ��											*/
/****************************************************************/
void CMy3DSymbolLibNewView::ShowWeather()
{
	glPushAttrib(GL_CURRENT_BIT);					// ����������ɫ����
	glPushMatrix();									// ѹ������ջ
	glEnable(GL_TEXTURE_2D);

	float wh=50;									// ����ʱ�ӵĸ߶�
	glViewport(WinViewX*5/6 -wh,  WinViewY - wh ,wh ,  wh);				// �����ӿ�λ�úʹ�С
	glMatrixMode( GL_PROJECTION );					// ���õ�ǰ����Ϊ͸�Ӿ���
	glLoadIdentity();								// ����ǰ�����û�Ϊ��λ�� 
	glOrtho (0.0f,1.0,0.0f, 1.0f, -1.0f, 1.0f);
	glMatrixMode( GL_MODELVIEW );					// ���õ�ǰ����Ϊģ�;���
	glLoadIdentity ();								// ����ǰ�����û�Ϊ��λ�� 

	// ����BACK�������
	glBindTexture(GL_TEXTURE_2D, g_weatherTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  

	// ��ʼ����
	glBegin(GL_QUADS);		
	glTexCoord2f(1.0f, 0.0f); glVertex2f(1, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(1, 1); 
	glTexCoord2f(0.0f, 1.0f); glVertex2f(0, 1);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);		
	glEnd();

	glPopMatrix();									// ���������ջ
	glPopAttrib();

	glViewport(0 ,  0 ,  WinViewX ,  WinViewY);		//�����ӿڴ�С��λ��
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();          
	gluPerspective(50.0 + m_ViewWideNarrow , (float)WinViewX/(float)WinViewY , m_near , m_far);		
	glMatrixMode(GL_MODELVIEW);						// �������Ϊģ��ģ�;���
	glLoadIdentity();								// ����ǰ�����û�Ϊ��λ����   
}

  
/****************************************************************/
/* Function: �������öԻ����ڱ���ֱ��ȫ����ֵ���ṹ��				*/
/****************************************************************/
void CMy3DSymbolLibNewView::C3DModelParamSetTOPModelStruct(C3DModelParamSet &model, PModelStruct &pStruct)
{
	pStruct->angle = model.angle;
	pStruct->hPos = model.hPos;
	pStruct->iDisplayType = model.iDisplayType;
	//pStruct->iModelNum = model.
	pStruct->iRotateX = model.iRotateX;
	pStruct->iRotateY = model.iRotateY;
	pStruct->iRotateZ = model.iRotateZ;
	pStruct->isSelected = false;
	pStruct->radiu = model.radiu;
	pStruct->scale = model.scale;
	//pStruct->strModelPath =
	pStruct->xPos = model.xPos;
	pStruct->zPos = model.zPos;
} 
void CMy3DSymbolLibNewView::C3DModelParamSetTOPModelStruct(C3DModelParamSet *model, PModelStruct &pStruct)
{
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
/* Function: ����3D���徰������ʵ�����ǽ�ƽ����������Y����ת90��ʵ�ֶ���������	*/
/****************************************************************************/
void CMy3DSymbolLibNewView::On3dTreeLoad()
{	
	CString tt,stt;
	FILE *fp;
	CString treeTexPath;
	CString treeFileFormat = ".BMP";

	if(m_i3DTreeModelNum < 50)
	{
		CDialogModelList dlg1;
		dlg1.m_Dir = m_AllDataPath + "\\" + m_TreeModelFolder;
		dlg1.m_format = ".bmp";
		dlg1.m_type = "3DTree";

		if(dlg1.DoModal() == IDOK)
		{
			CString selectItem = dlg1.m_selectItem;
			treeTexPath = dlg1.m_Dir + "\\" + selectItem + treeFileFormat;
		}
		else
			return;	

		if((fp=fopen(treeTexPath,"r"))==NULL)
		{
			MessageBox("�������ļ�������!","��ʼ��������ģ��",MB_ICONINFORMATION+MB_OK);
			exit(-1);
		}

		p3dtree = new CModelStruct;
		p3dtree->iModelNum = m_i3DTreeModelNum;
		p3dtree->strModelPath = treeTexPath;



		// ��ģʽ�Ի���
		paramSet_modeless_dlg = new C3DModelParamSet(this);
		paramSet_modeless_dlg->Create();
		paramSet_modeless_dlg->CenterWindow();
		

		paramSet_modeless_dlg->m_strTitle = "������ģ��  ������ʼ��";

		paramSet_modeless_dlg->m_modeParam.type = "3dtree";

		paramSet_modeless_dlg->ShowWindow(SW_SHOW);

	} 
	else
	{
		MessageBox("��ľ�Ĵ�С������50!");
	}
} 


/****************************************************************************/
/* Function: �Զ�����Ϣ��Ӧ,��ģʽ�Ի���(��3DSģ�Ͳ����Ի���)					*/
/****************************************************************************/
LRESULT CMy3DSymbolLibNewView::OnGoodBye(WPARAM wParam,LPARAM lParam)
{
	// ȷ��
	if(wParam == IDOK)
	{	
		if(paramSet_modeless_dlg->m_modeParam.type == "3dtree")
		{
			C3DModelParamSetTOPModelStruct(paramSet_modeless_dlg, p3dtree);

			m_3DTreeModel.Add(p3dtree); 

			char cc[256]; 
			sprintf(cc,p3dtree->strModelPath);
			LoadT16(cc,g_cactus3DTree[m_i3DTreeModelNum]); 
			m_i3DTreeModelNum ++;

			paramSet_modeless_dlg->DestroyWindow();

			m_isSetXYByMouse = 0;
		}
		else if(paramSet_modeless_dlg->m_modeParam.type == "tree")
		{
			C3DModelParamSetTOPModelStruct(paramSet_modeless_dlg, ptree);

			m_TreeModel.Add(ptree); 

			char cc[256]; 
			sprintf(cc,ptree->strModelPath);
			LoadT16(cc,g_cactus[m_iTreeModelNum]); 

			m_iTreeModelNum ++;

			paramSet_modeless_dlg->DestroyWindow();

			m_isSetXYByMouse = 0;
		}
		else if(paramSet_modeless_dlg->m_modeParam.type == "CitySymbol")
		{
			C3DModelParamSetTOPModelStruct(paramSet_modeless_dlg, pCitySymbol);

			m_CitySymbolModel.Add(pCitySymbol); 

			char cc[256]; 
			sprintf(cc,pCitySymbol->strModelPath);
			LoadPNG(cc, g_citySymbolTex[m_iCitySymbolModelNum]);

			m_iCitySymbolModelNum ++;

			paramSet_modeless_dlg->DestroyWindow();

			m_isSetXYByMouse = 0;
		}
	}
	// ȡ��
	else if(wParam == IDCANCEL)
	{
		paramSet_modeless_dlg->DestroyWindow();
		m_isSetXYByMouse = 0;
	}
	// checkboxѡ��״̬
	else if(wParam == SET_XY_BY_MOUSE_TRUE)
	{
		m_isSetXYByMouse = paramSet_modeless_dlg->isSetXYByMouse;
	}
	// checkbox��ѡ��״̬
	else if(wParam == SET_XY_BY_MOUSE_FALSE)
	{
		m_isSetXYByMouse = paramSet_modeless_dlg->isSetXYByMouse; 
	}

	return 0L;
}


/****************************************************************************/
/* Function: ��ʾ3D���徰����													*/
/****************************************************************************/
void CMy3DSymbolLibNewView::Show3DTree(int i)
{ 
	float x, y, z;
	x = m_3DTreeModel.GetAt(i)->xPos;
	z = m_3DTreeModel.GetAt(i)->zPos;
	float h = 3;

	glPushMatrix();  
	y = GetHeight(x,z) + m_3DTreeModel.GetAt(i)->hPos + h;

	glTranslatef(x,y, z); 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	glBindTexture(GL_TEXTURE_2D, g_cactus3DTree[i]); 

	glPushMatrix();
	glBegin(GL_QUADS); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f( h, 0, 0.0f);		// ���ϵ�
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 0, 0, 0.0f);		// ���ϵ�
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 0, h, 0.0f);		// ���µ�
	glTexCoord2f(1.0f, 1.0f); glVertex3f( h, h, 0.0f);		// ���µ�
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(h/2,0, h/2); // �������Ƶ���������λ�ã�������ת���������徰����
	glRotated(90,0,1,0);
	glBegin(GL_QUADS); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f( h, 0, 0.0f);		// ���ϵ�
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 0, 0, 0.0f);		// ���ϵ�
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 0, h, 0.0f);		// ���µ�
	glTexCoord2f(1.0f, 1.0f); glVertex3f( h, h, 0.0f);		// ���µ�
	glEnd();
	glPopMatrix();
	glDisable(GL_ALPHA);
	glDisable(GL_BLEND);
	glPopMatrix();
}


/****************************************************************************/
/* Function: ��������,��ѡ��ĳ��ģ��ʱ�Ͷ�ģ�ͽ������ţ����������������Ӿ�����	*/
/****************************************************************************/
BOOL CMy3DSymbolLibNewView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// ����ѡ��ģ�ʹ�С
	if(m_OperateType == SCALE)
	{
		if(m_selectedModelID != -1) // ��ǰ���ʰȡĳ��ģ��
		{
			// ���������Ӿ�����
			if (zDelta > 0)			//��ǰ�������Ŵ�
			{
				m_3DModel.GetAt(m_selectedModelID)->scale *= 1.1;
			}
			else if (zDelta < 0)
			{
				float oldScale = m_3DModel.GetAt(m_selectedModelID)->scale;
				m_3DModel.GetAt(m_selectedModelID)->scale *= 0.9;
				if(m_3DModel.GetAt(m_selectedModelID)->scale <= 0)
				{
					m_3DModel.GetAt(m_selectedModelID)->scale = oldScale;
				}
			}
		}
	}
	else
	{
		// ���������Ӿ�����
		if (zDelta > 0)				//��ǰ�������Ŵ�
		{
			m_ViewWideNarrow += ((zDelta/120)+0.1);
		}
		else if (zDelta < 0)
		{
			zDelta = - zDelta;
			m_ViewWideNarrow -= ( ( zDelta/120)-0.1);
		}
	}

	InvalidateRect(NULL,false);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


// �ж�������AABB��Χ���Ƿ��ཻ���Դ����ж��Ƿ��볡��������ģ���ཻ��ͬʱ��Ҫ��һ������Ƿ���ƽ��ģ���ཻ
/* 
* Woo����ķ��������жϾ��α߽����ĸ�����ཻ�� 
* �ټ�����������������ƽ����ཻ�ԡ� 
* ��������ں����У���ô��������α߽���ཻ�� 
* ���򲻴����ཻ  
*/  
//�Ͳ������ߵ��ཻ�Բ��ԣ�������ཻ�򷵻�ֵ��һ���ǳ������(����1)  
//����ཻ�������ཻʱ��t  
//tΪ0-1֮���ֵ  
float CMy3DSymbolLibNewView::RayIntersect(
	CVector3 rayStart,					// �������  
	CVector3 rayDir,					// ���߳��Ⱥͷ���  
	CVector3 returnNormal,				// ��ѡ�ģ��ཻ�㴦������  
	CVector3 min,
	CVector3 max
	){  
		//���δ�ཻ�򷵻��������  
		/*final*/const float kNoIntersection = 1e30f;  
		//�����ھ��α߽��ڵ�����������㵽ÿ����ľ���  
		bool inside = true;//���ھ��α߽��ڵ����,��ָ��������ڱ߽���ô��  
		float xt, xn = 0.0f;  
		if(rayStart.x<min.x){//������ߵ��������߽�����  
			xt = min.x - rayStart.x;//��ô�������㵽��߽��������x����  
			if(xt>rayDir.x){ return kNoIntersection; }//������߸�ƫ�����޷��ཻ  
			//������ʲô��˼��������������������������������������������  
			//����������ʲô��������ɣ�����λ����֪������������������������  
			//��ָ��������㵽�����Χ�б߽紦����ƫ�����߷���ı���ô����������  
			xt /= rayDir.x;  
			inside = false;//��ָ���ߵ���㲻�ھ��α߽���ô��  
			xn = -1.0f;  
		}  
		else if(rayStart.x>max.x){//������ߵ��������߽�����  
			xt = max.x - rayStart.x;//��ô�������㵽�ұ߽��xt  
			if(xt<rayDir.x){ return kNoIntersection; }//������߸�ƫ�����޷��ཻ  
			xt /= rayDir.x;  
			inside = false;  
			xn = 1.0f;  
		}  
		else{  
			xt = -1.0f;//��ָ��������������Χ����ô��  
		}  

		float yt, yn = 0.0f;  
		if(rayStart.y<min.y){  
			yt = min.y - rayStart.y;  
			if(yt>rayDir.y){ return kNoIntersection; }  
			yt /= rayDir.y;  
			inside = false;  
			yn = -1.0f;  
		}  
		else if(rayStart.y>max.y){  
			yt = max.y - rayStart.y;  
			if(yt<rayDir.y){ return kNoIntersection; }  
			yt /= rayDir.y;  
			inside = false;  
			yn = 1.0f;  
		}  
		else{  
			yt = -1.0f;  
		}  

		float zt, zn = 0.0f;  
		if(rayStart.z<min.z){  
			zt = min.z - rayStart.z;  
			if(zt>rayDir.z){ return kNoIntersection; }  
			zt /= rayDir.z;  
			inside = false;  
			zn = -1.0f;  
		}  
		else if(rayStart.z>max.z){  
			zt = max.z - rayStart.z;  
			if(zt<rayDir.z){ return kNoIntersection; }  
			zt /= rayDir.z;  
			inside = false;  
			zn = 1.0f;  
		}  
		else{  
			zt = -1.0f;  
		}  
		//�Ƿ��ھ��α߽���ڣ�  
		if(inside){  
			/*if(returnNormal != NULL){  */
			//returnNormal = rayDir.multiK(-1);  
			//returnNormal.normalize();  
			returnNormal = CVector3(0,0,0) - rayDir;
			Normalize(returnNormal);

			/*	}  */
			return 0.0f;//����ھ��α߽���ڣ�ȷ���ཻʱ����̣�  
		}  
		//ѡ����Զ��ƽ�桪�����������ཻ�ĵط�  
		int which = 0;  
		float t = xt;//ѡ����Զ��ƽ����ʲô��˼����ָ���߷���ƫ�������Χ�б߽���Զô������Զ��ָ���Χ��ĳ���е��ཻ����  
		if(yt>t){  
			which = 1;  
			t=yt;  
		}  
		if(zt>t){  
			which = 2;  
			t=zt;  
		}  
		switch(which){  
		case 0://��yzƽ���ཻ  
			{  
				float y=rayStart.y+rayDir.y*t;//��ʱ t = xt��xt /= rayDir.x;�˴�����ʲô��˼�� 
				if(y<min.y||y>max.y){return kNoIntersection;}  
				float z=rayStart.z+rayDir.z*t;  
				if(z<min.z||z>max.z){return kNoIntersection;}  
				//if(/*returnNormal != NULL*/){  
				returnNormal.x = xn;  
				returnNormal.y = 0.0f;  
				returnNormal.z = 0.0f;  
				/*} */                
			}  
			break;  
		case 1://��xzƽ���ཻ  
			{  
				float x=rayStart.x+rayDir.x*t;  
				if(x<min.x||x>max.x){return kNoIntersection;}  
				float z=rayStart.z+rayDir.z*t;  
				if(z<min.z||z>max.z){return kNoIntersection;}  
				/*	if(returnNormal != NULL){  */
				returnNormal.x = 0.0f;  
				returnNormal.y = yn;  
				returnNormal.z = 0.0f;  
				/*	}      */           
			}  
			break;  
		case 2://��xyƽ���ཻ  
			{  
				float x=rayStart.x+rayDir.x*t;  
				if(x<min.x||x>max.x){return kNoIntersection;}  
				float y=rayStart.y+rayDir.y*t;  
				if(y<min.y||y>max.y){return kNoIntersection;}  
				/*if(returnNormal != NULL){*/  
				returnNormal.x = 0.0f;  
				returnNormal.y = 0.0f;  
				returnNormal.z = zn;  
				/*} */                
			}  
			break;  
		}  
		return t;//�����ཻ�����ֵ  
}  

void CMy3DSymbolLibNewView::JudgeRayIntersect(
	CVector3 rayStart,					// �������  
	CVector3 rayDir,					// ���߳��Ⱥͷ���  
	CVector3 returnNormal				// ��ѡ�ģ��ཻ�㴦������
	)
{
	// ��ȡģ������ά�㼫ֵ
	int minx,maxx,miny,maxy,minz,maxz;
	float t;

	// �������ѡ��ģʽ������ƶ�ʰȡ���󣬾�ֻ���Ѿ�ʰȡ�˵��������ƥ��
	if(m_bMouseMoveSelect)
	{
		for(unsigned int i = 0; i < m_pSelectedModelSet.size(); ++i)
		{
			if(m_pSelectedModelSet.at(i)->modelType == MODEL_3DS)
			{
				int j = m_pSelectedModelSet.at(i)->modelID;

				//t = -1;
				t3DBox t3dBox;
				t3dBox.w = m_3DModel.GetAt(j)->scale * g_3DModel[j].t3DModelBox.w;
				t3dBox.h = m_3DModel.GetAt(j)->scale * g_3DModel[j].t3DModelBox.h;
				t3dBox.l = m_3DModel.GetAt(j)->scale * g_3DModel[j].t3DModelBox.l;

				POINT pt;
				pt.x = m_3DModel.GetAt(j)->posX;
				pt.y = m_3DModel.GetAt(j)->posZ;

				minx = pt.x - (t3dBox.l * 1.5 )/2;
				maxx = pt.x + (t3dBox.l * 1.5 )/2;
				minz = pt.y - (t3dBox.w * 1.5 )/2;
				maxz = pt.y + (t3dBox.w * 1.5 )/2;

				// int y = GetHeight(x,z) + h + t3dBox.h/2;				// ��ȡ����߶�
				// ֮���Ը߶�����ǵ���߶ȣ�����Ϊ����Ⱦģ��ʱ�Ѿ���ģ���������͸߶ȵ��ر�
				miny = GetHeight(pt.x, pt.y);
				maxy = GetHeight(pt.x, pt.y) + (t3dBox.h * 1.5 );

				CVector3 returnNormal,min,max;
				min = CVector3(minx, miny, minz);
				max = CVector3(maxx, maxy, maxz);

				t = RayIntersect(rayStart, rayDir,returnNormal,min,max);

				if(t>= 0 && t <= 1)
				{
					// ������λ��ʰȡ�˵�ǰ��ѡ��ģ�ͣ����ı���̬
					m_mouseShape = MOUSE_SHAPE_EDIT; 	
					m_selectedModelID = j;
				}
				else
					m_mouseShape = MOUSE_SHAPE_SLECT;
			}
		}
	}

	if(m_bIsLBtnDown)
	{
		// �������е�3Dģ��,�ж��Ƿ��ڷ�Χ�� 
		for(int j = 0; j < m_i3DModelNum; j++)
		{		
			//t = -1;
			t3DBox t3dBox;
			float scale = m_3DModel.GetAt(j)->scale;
			t3dBox.w = m_3DModel.GetAt(j)->scale * g_3DModel[j].t3DModelBox.w;
			t3dBox.h = m_3DModel.GetAt(j)->scale * g_3DModel[j].t3DModelBox.h;
			t3dBox.l = m_3DModel.GetAt(j)->scale * g_3DModel[j].t3DModelBox.l;

			POINT pt;
			pt.x = m_3DModel.GetAt(j)->posX;
			pt.y = m_3DModel.GetAt(j)->posZ;

			minx = pt.x - (t3dBox.l * 1.5 )/2;
			maxx = pt.x + (t3dBox.l * 1.5 )/2;
			minz = pt.y - (t3dBox.w * 1.5 )/2;
			maxz = pt.y + (t3dBox.w * 1.5 )/2; 

			// int y = GetHeight(x,z) + h + t3dBox.h/2;				// ��ȡ����߶�
			// ֮���Ը߶�����ǵ���߶ȣ�����Ϊ����Ⱦģ��ʱ�Ѿ���ģ���������͸߶ȵ��ر�
			miny = GetHeight(pt.x, pt.y);
			maxy = GetHeight(pt.x, pt.y) + (t3dBox.h * 1.5);

			CVector3 returnNormal,min,max;
			min = CVector3(minx, miny, minz);
			max = CVector3(maxx, maxy, maxz);

			t = RayIntersect(rayStart, rayDir,returnNormal,min,max);

			if(t>= 0 && t <= 1)
			{
				CVector3 DotC = rayStart + CVector3(t* rayDir.x, t * rayDir.y, t*rayDir.z);

				CString strText;
				strText.Format("������  X=%.3f , Y=%.3f , Z=%.3f" , DotC.x, DotC.y, DotC.z);

				
				// ѡ��ģ��
				//AfxMessageBox(strText,MB_OK);
				//Set3dsModelParam(j);
				// ���ģ�͵�ǰ�������ѡ��״̬�����ٴ�ʰȡ����ʱ����Ǵ�ѡ�ж�����ɾ����ȥ
				if(m_OperateType == SELECT && m_3DModel.GetAt(j)->modelSelected)
				{
					m_3DModel.GetAt(j)->modelSelected = false;

					vector<PSelectedModel>::iterator ite; 
					for(vector<PSelectedModel>::iterator it = m_pSelectedModelSet.begin(); it != m_pSelectedModelSet.end(); ++it)
					{ 
						/*
						�˴�����������iterator���Լ򵥵����Ϊvetor��ָ�룬������*iterator������н����ò����ͷ�����һ��PSelectedModel����
						�Ķ���*/
						if((*it)->modelID == (m_3DModel.GetAt(j)->modelID)/* && it != m_pSelectedModelSet.end()*/)
						{ 
							ite = it;
							//it = m_pSelectedModelSet.end();
						}
					}

					m_pSelectedModelSet.erase(ite); 
				}
				else
				{
					if(m_3DModel.GetAt(j)->isDeleted == false)
					{
						m_3DModel.GetAt(j)->modelSelected = true;

						PSelectedModel selectedModel = new SelectedModel;
						selectedModel->modelID = m_3DModel.GetAt(j)->modelID;
						selectedModel->modelType = MODEL_3DS;

						
						m_pSelectedModelSet.push_back(selectedModel); 
					}
				}
				
				if(!m_bFlash && !m_pSelectedModelSet.empty())
				{
					SetTimer(2, 500, NULL);
					m_bFlash = true;
				}
			}
		} 
	} 
}



/****************************************************************************/
/* Function: ���ع����ļ�														*/
/****************************************************************************/
void CMy3DSymbolLibNewView::loadSceneFile(CString filename)
{
	CStdioFile file;
	BOOL b_open = file.Open(filename, CStdioFile::modeRead);
	if((!b_open) || (file==NULL))
	{
		MessageBox(_T("���̲�����!\n")+filename, _T("�򿪹����ļ�"), MB_ICONWARNING + MB_OK);
		return;
	}
	else
	{
		CString tmpStr = filename.Right(4);

		// ��ӵ�ע��� ����򿪵��ļ��б� 
		if(tmpStr == _T(".prj"))
			theApp.AddToRecentFileList(filename);


		// �رյ�ǰ����
		OnCloseCurrentScene();

		// ��ȡ���������ļ�·��
		m_AllDataPath = g_sceneDataPath.c_str();


		// ������������
		file.ReadString(m_SceneConfig);

		// ----------------------------------------------------

		// ��������, Terrain
		file.ReadString(m_TerrainFolder);
		// Tex Sand512.BMP
		file.ReadString(m_TerrainTextureFolder);
		int length = m_TerrainTextureFolder.GetLength();
		int i = m_TerrainTextureFolder.Find(" ");
		m_TerrainTexture = m_TerrainTextureFolder.Right(length - i - 1);
		m_TerrainTextureFolder = m_TerrainTextureFolder.Left(i);
		// Contour Terrain1.bmp
		file.ReadString(m_TerrainContourFolder);
		length = m_TerrainContourFolder.GetLength();
		i = m_TerrainContourFolder.Find(" ");
		m_TerrainContour = m_TerrainContourFolder.Right(length - i - 1);
		m_TerrainContourFolder = m_TerrainContourFolder.Left(i);

		// ----------------------------------------------------

		// ��պ�����SkyBox
		file.ReadString(m_SkyBoxFolder);
		// default TOP.BMP LEFT.BMP BACK.BMP RIGHT.BMP FRONT.BMP
		file.ReadString(m_SkyBoxKindFolder);
		int curPos = 0; 
		int tokenID = 0;
		CString temp = m_SkyBoxKindFolder.Tokenize(" ", curPos);
		CString Skyfolder = temp;
		while (temp != _T(""))
		{		
			tokenID += 1;	
			temp = m_SkyBoxKindFolder.Tokenize(" ", curPos); 

			if(tokenID == 1)
				m_SkyBoxTP = temp;
			else if(tokenID == 2)
				m_SkyBoxLT = temp;
			else if(tokenID == 3)
				m_SkyBoxBK = temp;
			else if(tokenID == 4)
				m_SkyBoxRT = temp;
			else if(tokenID == 5)
				m_SkyBoxFR = temp;
		};   
		m_SkyBoxKindFolder = Skyfolder;

		// ----------------------------------------------------

		// ��������
		file.ReadString(m_WeatherFolder);
		file.ReadString(m_WeatherTex);

		CString weatherSymbolTexPath = m_AllDataPath + "\\" + m_WeatherFolder + "\\" + m_WeatherTex;

		char cc[256]; 
		sprintf(cc,weatherSymbolTexPath);
		LoadT8(cc,g_weatherTex); 
		bIsWeatherLoad = true; 

		// ----------------------------------------------------
		// �����ļ�����
		file.ReadString(m_CurrentSymbolTypeNum);

		file.ReadString(m_PointSymbolFile);
		file.ReadString(m_LineSymbolFile);
		file.ReadString(m_AreaSymbolFile);


		file.Close();


		


		// ���ص��ļ�
		if(m_PointSymbolFile != "0")
		{
			 CString point_Path = /*m_AllDataPath + "\\" + m_SceneConfig + "\\" + */m_PointSymbolFile;
			 LoadPointSymbolFile(point_Path);
			 exist_point_flag = TRUE;
		}
		// �������ļ�
		if(m_LineSymbolFile != "0")
		{
			CString line_Path = /*m_AllDataPath + "\\" + m_SceneConfig + "\\" + */m_LineSymbolFile;
			LoadLineSymbolFile(line_Path);
			exist_line_flag = TRUE;
		}
		
		// �������ļ�  ����ȳ�ʼ����������֮��  (���·�)



		/**************************************/
		/* ������·������Դ					  */
		/**************************************/
		CString scenePath = g_sceneDataPath.c_str();
		CString tmpPath = scenePath + "\\RoadTexture";

	
		CString txtureRailway = tmpPath + "\\��·\\doubleway5.bmp";

		// ������·����
		m_cTxtureRailway.LoadGLTextures(txtureRailway.GetBuffer(0));

		CString txtureBP = tmpPath + "\\���·���\\���λ���1.bmp";
		m_cTxtureBP.LoadGLTextures(txtureBP.GetBuffer(0));

		CString txtureLJ = tmpPath + "\\·��\\1.bmp";
		m_cTxtureLJ.LoadGLTextures(txtureLJ.GetBuffer(0));

		CString txtureGdToLJ = tmpPath + "\\·��\\10.bmp";
		m_cTxtureGdToLJ.LoadGLTextures(txtureGdToLJ.GetBuffer(0));

		CString txturePT = tmpPath + "\\����ƽ̨\\����ƽ̨1.bmp";
		m_cTxturePT.LoadGLTextures(txturePT.GetBuffer(0));


		// ��������
		CString txtureFF = tmpPath + "\\����ƽ̨\\����ƽ̨2.bmp";
		m_cFillFaceTxture.LoadGLTextures(txtureFF.GetBuffer(0));
		//==========================================================

		// ----------------------------------------------------
		/*
		// ��·
		CString strLine;
		CString strJDNumber;
		int intJDNumber;
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

		int s1 = myDesingScheme.PtS_JD.GetSize();
		float a ;
		for(int i=0;i<s1;++i)
		{
			a = myDesingScheme.PtS_JD[i]->x;
		}
		int s2 = myDesingScheme.JDCurveElements.GetSize();

		file.Close();
		*/

		// ----------------------------------------------------

		// ��ʼ������Ⱦ ������պ�
		CString skyBoxPathPre = m_AllDataPath + "\\" + m_SkyBoxFolder + "\\" + m_SkyBoxKindFolder + "\\";
		g_texSkyBoxFlieNameTP = skyBoxPathPre + m_SkyBoxTP; 
		g_texSkyBoxFlieNameLF = skyBoxPathPre + m_SkyBoxLT; 
		g_texSkyBoxFlieNameBK = skyBoxPathPre + m_SkyBoxBK; 
		g_texSkyBoxFlieNameRT = skyBoxPathPre + m_SkyBoxRT; 
		g_texSkyBoxFlieNameFR = skyBoxPathPre + m_SkyBoxFR; 

		LoadSkyBoxTex(g_texSkyBoxFlieNameTP, g_texSkyBoxFlieNameLF, g_texSkyBoxFlieNameBK,
			g_texSkyBoxFlieNameRT, g_texSkyBoxFlieNameFR);

		// ���õ���
		terrainTexFileName = m_AllDataPath + "\\" + m_TerrainFolder + "\\" + m_TerrainTextureFolder + "\\" + m_TerrainTexture;
		terrainContourFileName = m_AllDataPath + "\\" + m_TerrainFolder + "\\" + m_TerrainContourFolder + "\\" + m_TerrainContour;
		LoadTerrainTex(terrainTexFileName, terrainContourFileName);

		OnMenuBuild3dlinemodle();







		// �������ļ�
		if(m_AreaSymbolFile != "0")
		{
			CString area_Path = /*m_AllDataPath + "\\" + m_SceneConfig + "\\" + */m_AreaSymbolFile;
			LoadAreaSymbolFile(area_Path);
			exist_area_flag = TRUE;
		}






	} 
}


// ���ص��ļ�(.pt)
void CMy3DSymbolLibNewView::LoadPointSymbolFile(CString filename)
{
	CStdioFile file;
	BOOL b_open = file.Open(filename, CStdioFile::modeRead);
	if((!b_open) || (file==NULL))
	{
		MessageBox(_T("���ļ�!\n")+filename, _T("�򿪵��ļ�"), MB_ICONWARNING + MB_OK);
		return;
	}
	else
	{
		// ��ȡ���������ļ�·��
		m_AllDataPath = g_sceneDataPath.c_str();

		CString tmp_pointHeader;
		// ���ļ��ײ�
		file.ReadString(tmp_pointHeader);

		// ----------------------------------------------------

		// 3DS ģ������

		/*3DModel
		2
		����1 399.921 83.990 384.101
		���췢��̨ 397.700 83.991 373.560*/
		file.ReadString(m_3DModelFolder);
		CString m_3DModelNumStr;
		file.ReadString(m_3DModelNumStr);
		m_i3DModelNum = atoi(m_3DModelNumStr);

		for(int i = 0; i <m_i3DModelNum; ++i)
		{
			file.ReadString(m_3DModelPath);

			int curPos = 0; 
			int tokenID = 0;
			CString temp = m_3DModelPath.Tokenize(" ", curPos);
			CString model3DFolder = temp;
			while (temp != _T(""))
			{		
				tokenID += 1;	
				temp = m_3DModelPath.Tokenize(" ", curPos); 

				if(tokenID == 1)
					m_3DModelPosX = atof(temp);
				else if(tokenID == 2)
					m_3DModelPosY = atof(temp);
				else if(tokenID == 3)
					m_3DModelPosZ = atof(temp);			

				else if(tokenID == 4)
					m_3DModelRotX = atof(temp);	
				else if(tokenID == 5)
					m_3DModelRotY = atof(temp);	
				else if(tokenID == 6)
					m_3DModelRotZ = atof(temp);	
				else if(tokenID == 7)
					m_3DModelScale = atof(temp);	
			};   
			m_3DModelPath = model3DFolder;

			PModelParamStruct p3d = new CModelParamStruct;
			p3d->modelPath = m_AllDataPath + "\\" + m_3DModelFolder + "\\"+ m_3DModelPath;
			p3d->modelID = i;
			p3d->modelSelected = false;

			p3d->m_3DS_Mode_Texture_PATH_NAME = m_AllDataPath + "\\" + m_3DModelFolder + "\\"+ m_3DModelPath.Left(m_3DModelPath.Find('.')) + ".bmp";

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

		// ���б�ʶ����
		/*City Symbol
		2
		25 398.469 83.992 393.427
		1 386.085 83.993 387.031*/
		file.ReadString(m_CitySymbolFolder);
		CString m_CitySymbolNumStr;
		file.ReadString(m_CitySymbolNumStr);
		m_iCitySymbolModelNum = atoi(m_CitySymbolNumStr);

		for(int i = 0; i <m_iCitySymbolModelNum; ++i)
		{
			file.ReadString(m_CitySymbolTex);
			int curPos = 0; 
			int tokenID = 0;
			curPos = 0; tokenID = 0;
			CString temp = m_CitySymbolTex.Tokenize(" ", curPos);
			CString citySymbolTex = temp;
			while (temp != _T(""))
			{		
				tokenID += 1;	
				temp = m_CitySymbolTex.Tokenize(" ", curPos); 

				if(tokenID == 1)
					m_CitySymbolPosX = atof(temp);
				else if(tokenID == 2)
					m_CitySymbolPosY = atof(temp);
				else if(tokenID == 3)
					m_CitySymbolPosZ = atof(temp);					
			};   
			m_CitySymbolTex = citySymbolTex;

			PModelStruct p3d = new CModelStruct;
			p3d->strModelPath = m_AllDataPath + "\\" + m_CitySymbolFolder + "\\"+ m_CitySymbolTex;
			p3d->iModelNum = i;

			p3d->xPos = m_CitySymbolPosX;
			p3d->hPos = m_CitySymbolPosY;
			p3d->zPos = m_CitySymbolPosZ;

			p3d->radiu = 0;	p3d->angle = 0; p3d->scale = 1;	p3d->isSelected = false; 
			p3d->iRotateX = 0; p3d->iRotateY = 0; p3d->iRotateZ = 0;  

			m_CitySymbolModel.Add(p3d); 

			char cc[256]; 
			sprintf(cc,p3d->strModelPath);
			LoadPNG(cc, g_citySymbolTex[i]);
		}


		// ----------------------------------------------------

		// ����������
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

		for(int i = 0; i <m_iTreeModelNum; ++i)
		{
			file.ReadString(m_TreeModelTex);
			int curPos = 0; 
			int tokenID = 0;
			curPos = 0; tokenID = 0;
			CString temp = m_TreeModelTex.Tokenize(" ", curPos);
			CString treeModelTex = temp;
			while (temp != _T(""))
			{		
				tokenID += 1;	
				temp = m_TreeModelTex.Tokenize(" ", curPos); 

				if(tokenID == 1)
					m_TreeModelPosX = atof(temp);
				else if(tokenID == 2)
					m_TreeModelPosY = atof(temp);
				else if(tokenID == 3)
					m_TreeModelPosZ = atof(temp);					
			};   
			m_TreeModelTex = treeModelTex;

			PModelStruct p3d = new CModelStruct;
			p3d->strModelPath = m_AllDataPath + "\\" + m_TreeModelFolder + "\\"+ m_TreeModelTex;
			p3d->iModelNum = i;

			p3d->xPos = m_TreeModelPosX;
			p3d->hPos = m_TreeModelPosY;
			p3d->zPos = m_TreeModelPosZ;

			p3d->radiu = 0;	p3d->angle = 0; p3d->scale = 1;	p3d->isSelected = false; 
			p3d->iRotateX = 0; p3d->iRotateY = 0; p3d->iRotateZ = 0;  

			m_TreeModel.Add(p3d); 

			char cc[256]; 
			sprintf(cc,p3d->strModelPath);
			LoadT16(cc,g_cactus[p3d->iModelNum]); 
		}

		// ----------------------------------------------------

		// 3D Tree
		file.ReadString(m_TreeModelNumStr);
		m_i3DTreeModelNum = atoi(m_TreeModelNumStr);
		for(int i = 0; i <m_i3DTreeModelNum; ++i)
		{
			file.ReadString(m_TreeModelTex);
			int curPos = 0; 
			int tokenID = 0;
			curPos = 0; tokenID = 0;
			CString temp = m_TreeModelTex.Tokenize(" ", curPos);
			CString treeModelTex = temp;
			while (temp != _T(""))
			{		
				tokenID += 1;	
				temp = m_TreeModelTex.Tokenize(" ", curPos); 

				if(tokenID == 1)
					m_TreeModelPosX = atof(temp);
				else if(tokenID == 2)
					m_TreeModelPosY = atof(temp);
				else if(tokenID == 3)
					m_TreeModelPosZ = atof(temp);					
			};   
			m_TreeModelTex = treeModelTex;

			PModelStruct p3d = new CModelStruct;
			p3d->strModelPath = m_AllDataPath + "\\" + m_TreeModelFolder + "\\"+ m_TreeModelTex;
			p3d->iModelNum = i;

			p3d->xPos = m_TreeModelPosX;
			p3d->hPos = m_TreeModelPosY;
			p3d->zPos = m_TreeModelPosZ;

			p3d->radiu = 0;	p3d->angle = 0; p3d->scale = 1;	p3d->isSelected = false; 
			p3d->iRotateX = 0; p3d->iRotateY = 0; p3d->iRotateZ = 0;  

			m_3DTreeModel.Add(p3d); 

			char cc[256]; 
			sprintf(cc,p3d->strModelPath);
			LoadT16(cc,g_cactus3DTree[p3d->iModelNum]); 
		}
	}

	file.Close();
}
// �������ļ�(.ln)
void CMy3DSymbolLibNewView::LoadLineSymbolFile(CString filename)
{

}
// �������ļ�(.gsf)
void CMy3DSymbolLibNewView::LoadAreaSymbolFile(CString filename)
{
	CStdioFile file;
	BOOL b_open = file.Open(filename, CStdioFile::modeRead);
	if((!b_open) || (file==NULL))
	{
		MessageBox(_T("���ļ�!\n")+filename, _T("�����ļ�"), MB_ICONWARNING + MB_OK);
		return;
	}
	else
	{
		// ��ȡ���������ļ�·��
		//m_AllDataPath = g_sceneDataPath.c_str();

		CString tmp_areaHeader;
		// ���ļ��ײ�
		file.ReadString(tmp_areaHeader);

		// ----------------------------------------------------

		// ����ŵĸ���
		CString area_count_str;
		file.ReadString(area_count_str);
		int area_num = atoi(area_count_str);

		// ����εı���
		CString area_edge_num_str;
		


		CString area_info_str;
 
		for(int i=0; i<area_num; ++i)
		{
			file.ReadString(area_info_str);

			int curPos = 0; 
			int tokenID = 0;
			CString temp = area_info_str.Tokenize(" ", curPos);

			CString area_edge_num_str = temp;
			int area_edges = atoi(area_edge_num_str);


			Area_4 tmp_area4; 
			

			while (temp != _T("") && (4==area_edges) )
			{		
				tokenID += 1;	
				temp = area_info_str.Tokenize(" ", curPos); 

				//pt1
				if(tokenID == 1)
					tmp_area4.pt1._x = atof(temp);
				else if(tokenID == 2)
					tmp_area4.pt1._y = atof(temp);
				else if(tokenID == 3)
					tmp_area4.pt1._z = atof(temp);			

				//pt2
				else if(tokenID == 4)
					tmp_area4.pt2._x = atof(temp);	
				else if(tokenID == 5)
					tmp_area4.pt2._y = atof(temp);	
				else if(tokenID == 6)
					tmp_area4.pt2._z = atof(temp);	

				//pt3
				else if(tokenID == 7)
					tmp_area4.pt3._x = atof(temp);	
				else if(tokenID == 8)
					tmp_area4.pt3._y = atof(temp);	
				else if(tokenID == 9)
					tmp_area4.pt3._z = atof(temp);	


				//pt4
				else if(tokenID == 10)
					tmp_area4.pt4._x = atof(temp);	
				else if(tokenID == 11)
					tmp_area4.pt4._y = atof(temp);
				else if(tokenID == 12)
					tmp_area4.pt4._z = atof(temp);
				else if(tokenID == 13)
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
/* Function: ��ʼ�׶ε��볡���ļ�												*/
/****************************************************************************/
void CMy3DSymbolLibNewView::OnSceneLoad()
{
	CString sceneConfigPath;

	CFileDialog FileDialog(TRUE,"�򿪹���",NULL,OFN_HIDEREADONLY \
		| OFN_OVERWRITEPROMPT,\
		"�����ļ�(*.prj)|*.prj|",NULL);
	
	// Ĭ�ϴ������е��ļ�·��
	FileDialog.m_ofn.lpstrInitialDir = g_sceneDataPath.c_str();
	FileDialog.m_ofn.lpstrTitle="�򿪹����ļ�";	
	if(FileDialog.DoModal() == IDOK)
	{
		sceneConfigPath = FileDialog.GetPathName();
	}
	else
		return;	

	// ���س����ļ�
	loadSceneFile(sceneConfigPath);
	m_CurrentProjectName = sceneConfigPath;
}





/****************************************************************************/
/* Function: ������պ�����													*/
/****************************************************************************/
void CMy3DSymbolLibNewView::LoadSkyBoxTex(CString skyTP, CString skyLF, CString skyBK, CString skyRT, CString skyFR)
{
	char cc[256];
	sprintf(cc,skyTP);
	LoadT8(cc,g_texSkyBox[TP]);

	sprintf(cc,skyLF);
	LoadT8(cc,g_texSkyBox[LF]);

	sprintf(cc,skyBK);
	LoadT8(cc,g_texSkyBox[BK]);

	sprintf(cc,skyRT);
	LoadT8(cc,g_texSkyBox[RT]);

	sprintf(cc,skyFR);
	LoadT8(cc,g_texSkyBox[FR]);

	MakeSkykList();
	iSkyBoxLoaded = true;
}


/****************************************************************************/
/* Function: �����������														*/
/****************************************************************************/
void CMy3DSymbolLibNewView::LoadTerrainTex(CString terrainTex, CString terrainContour)
{
	char cc[256];
	strcpy(cc,terrainTex);				// ������ͼ
	LoadT8(cc,	texTerrain);	

	strcpy(cc,terrainContour);			// �ȸߵ���ͼ
	g_imageData = LoadBit(cc,&g_bit);	// ���ȸ��ߵ���ͼ

	InitTerrain(/*5*/);					// ��ʼ�����棬��������߶�Ϊ5��ֻ����������Ƹ߶����ò�����
	g_isTerrainInit = true;
	iTerrainType = 1;
}




/****************************************************************************/
/* Function: ����3DSģ��														*/
/****************************************************************************/
void CMy3DSymbolLibNewView::Load3DModel(PModelParamStruct p3d, int iLoadModelType)
{
	if(iLoadModelType == MODEL_NEW)
	{
		m_3DModel.Add(p3d);
	}

	char _3DSFile[256]; 
	sprintf(_3DSFile,p3d->modelPath); // "...\\3DModel\\XXX.3DS" 

	// [ADD]
	char _3DSTextureFile[256]; 
	sprintf(_3DSTextureFile,p3d->m_3DS_Mode_Texture_PATH_NAME);

	m_3ds->Init(_3DSFile, p3d->modelID, _3DSTextureFile);	// ����ģ�͵��뺯��

	t3DBox t3dBox;

	t3dBox.l = g_3DModel[p3d->modelID].t3DModelBox.l * p3d->scale;
	t3dBox.w = g_3DModel[p3d->modelID].t3DModelBox.w * p3d->scale;
	t3dBox.h = g_3DModel[p3d->modelID].t3DModelBox.h * p3d->scale;

	// ���load3dsmodelʱ���ű�������
	if(p3d->scale < 0.99)
	{
		return;
	}

	float maxtemp = (t3dBox.l > t3dBox.w) ? t3dBox.l : t3dBox.w;
	float max = (maxtemp > t3dBox.h) ? maxtemp : t3dBox.h;

	float scale = 0.0f;
	if(max > 10)
	{
		scale = 10 / max;
		m_3DModel.GetAt(p3d->modelID)->scale = scale;
	}
}


/****************************************************************************/
/* Function: ���浱ǰ����														*/
/****************************************************************************/
//void CMy3DSymbolLibNewView::OnSceneSave()
//{ 
//	// ��FlyPathSave����һ��
//	CString 	NeededFile;
//	char 		FileFilter[] = "�����ļ�(*.prj)|*.prj|";
//
//	//�����ļ��Ի�������
//	DWORD 		FileDialogFlag = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
//	CFileDialog FileDialogBoxFile(FALSE, NULL, 0, FileDialogFlag, FileFilter, this);
//	FileDialogBoxFile.m_ofn.lpstrTitle = "���湤���ļ�";
//	char		FileName[200];
//
//	
//	CString sceneDir = m_AllDataPath + "\\" + m_SceneConfig;
//	FileDialogBoxFile.m_ofn.lpstrInitialDir = sceneDir;
//
//	CString tt[3];
//	if( FileDialogBoxFile.DoModal() == IDOK )			//����Ի���ɹ���
//	{	
//		NeededFile = FileDialogBoxFile.GetPathName();	//�õ��ļ���
//		sprintf(FileName, "%s", NeededFile);
//		if(strcmp(FileDialogBoxFile.GetFileExt(),"prj")!=0) 
//			strcat(FileName,".prj");				 
//
//		if(ScenSave(FileName))
//			MessageBox("���������ļ��������","���泡�����÷���",MB_ICONWARNING);
//	}		
//}


void CMy3DSymbolLibNewView::OnSceneSave()
{ 
	if(ScenSave(m_CurrentProjectName))
		MessageBox("���������ļ��������","���泡�����÷���",MB_ICONWARNING);
}


/****************************************************************************/
/* Function: ��ǰ�������Ϊ													*/
/****************************************************************************/
void CMy3DSymbolLibNewView::OnSceneSaveAs()
{
	// TODO: �ڴ���������������
	CString 	NeededFile;
	char 		FileFilter[] = "�����ļ�(*.prj)|*.prj|";

	//�����ļ��Ի�������
	DWORD 		FileDialogFlag = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
	CFileDialog FileDialogBoxFile(FALSE, NULL, 0, FileDialogFlag, FileFilter, this);
	FileDialogBoxFile.m_ofn.lpstrTitle = "���湤���ļ�";
	char		FileName[200];


	CString sceneDir = m_AllDataPath + "\\" + m_SceneConfig;
	FileDialogBoxFile.m_ofn.lpstrInitialDir = sceneDir;

	CString tt[3];
	if( FileDialogBoxFile.DoModal() == IDOK )			//����Ի���ɹ���
	{	
		NeededFile = FileDialogBoxFile.GetPathName();	//�õ��ļ���
		sprintf(FileName, "%s", NeededFile);
		if(strcmp(FileDialogBoxFile.GetFileExt(),"prj")!=0) 
			strcat(FileName,".prj");				 

		if(ScenSave(FileName))
			MessageBox("���������ļ��������","���泡�����÷���",MB_ICONWARNING);
	}		
}


/****************************************************************************/
/* Function: ���泡������														*/
/****************************************************************************/
//bool CMy3DSymbolLibNewView::ScenSave(CString scenePth)
//{
//	CStdioFile file; 
//	file.Open(scenePth, CStdioFile::modeCreate | CStdioFile::modeWrite);
//	if(file == NULL)
//	{
//		MessageBox("���������ļ�������!", "���������ļ�����", MB_ICONINFORMATION + MB_OK);
//		return FALSE;
//	}
//	else
//	{ 
//		/************************************************************************/
//		/*   ������������															*/
//		/************************************************************************/
//		file.WriteString(m_SceneConfig + "\n");
//
//
//		/************************************************************************/
//		/*   �������� Terrain													*/
//		/************************************************************************/
//		file.WriteString(m_TerrainFolder + "\n");
//		//	  Tex Sand512.BMP
//		file.WriteString(m_TerrainTextureFolder + " " + m_TerrainTexture + "\n"); 
//		//	  Contour Terrain1.bmp
//		file.WriteString(m_TerrainContourFolder + " " + m_TerrainContour + "\n"); 
//
// 
//		/************************************************************************/
//		/*   ��պ����� SkyBox													*/
//		/************************************************************************/
//		file.WriteString(m_SkyBoxFolder + "\n");
//		//	  0ȱʡ TOP.BMP LEFT.BMP BACK.BMP RIGHT.BMP FRONT.BMP
//		file.WriteString(m_SkyBoxKindFolder + " " + m_SkyBoxTP + " " + m_SkyBoxLT + " "\
//			+ m_SkyBoxBK + " " + m_SkyBoxRT + " " + m_SkyBoxFR + "\n"); 
//
//
//		/************************************************************************/
//		/*   3DS ģ������ 3DModel												*/
//		/************************************************************************/
//		file.WriteString(m_3DModelFolder + "\n");
//		
//		int count_model_existed = 0;
//		for(int i = 0; i <m_i3DModelNum; ++i)
//		{
//			if(m_3DModel.GetAt(i)->isDeleted == false)
//			{
//				count_model_existed++;
//			}
//		}
//
//		CString m_3DModelNumStr;
//		m_3DModelNumStr.Format("%d", count_model_existed);
//		file.WriteString(m_3DModelNumStr + "\n");
//	
//
//		for(int i = 0; i <m_i3DModelNum; ++i)
//		{
//			if(m_3DModel.GetAt(i)->isDeleted == false)
//			{
//				CString model; 
//				CString path = m_3DModel.GetAt(i)->modelPath; 		
//				CString temp;					
//				int n = path.ReverseFind('\\');//�Ӻ���ǰѰ��
//				temp = path.Right(path.GetLength() - n - 1);
//
//				float pos_x = m_3DModel.GetAt(i)->posX;
//				float pos_z = m_3DModel.GetAt(i)->posZ;
//				float pos_y = m_3DModel.GetAt(i)->posY;
//
//				float rot_x = m_3DModel.GetAt(i)->rotX;
//				float rot_z = m_3DModel.GetAt(i)->rotZ;
//				float rot_y = m_3DModel.GetAt(i)->rotY;
//
//				float model_scale = m_3DModel.GetAt(i)->scale;
//
//				model.Format("%s %.3f %.3f %.3f %.3f %.3f %.3f %.13f",temp, pos_x, pos_y, pos_z,rot_x,rot_y,rot_z,model_scale);
//
//				file.WriteString(model + "\n"); 
//			}
//				
//		}
//
//
//		/************************************************************************/
//		/*   ���б�ʶ���� City Symbol												*/
//		/************************************************************************/
//		file.WriteString(m_CitySymbolFolder + "\n");
//		CString m_CitySymbolNumStr;
//		m_CitySymbolNumStr.Format("%d", m_iCitySymbolModelNum);
//		file.WriteString(m_CitySymbolNumStr + "\n");
//
//		for(int i = 0; i <m_iCitySymbolModelNum; ++i)
//		{
//			CString model; 
//
//			CString path = m_CitySymbolModel.GetAt(i)->strModelPath; 		
//			CString temp;					
//			int n = path.ReverseFind('\\');//�Ӻ���ǰѰ��
//			temp = path.Right(path.GetLength() - n - 1);
//
//			model.Format("%s %d %.3f %d", temp,\
//				m_CitySymbolModel.GetAt(i)->xPos, m_CitySymbolModel.GetAt(i)->hPos, m_CitySymbolModel.GetAt(i)->zPos);
//
//			file.WriteString(model + "\n"); 
//		}
//
//
//		/************************************************************************/
//		/*   ���������� TreeModel												*/
//		/************************************************************************/
//		file.WriteString(m_TreeModelFolder + "\n");
//		CString m_TreeModelNumStr;
//		m_TreeModelNumStr.Format("%d", m_iTreeModelNum);
//		file.WriteString(m_TreeModelNumStr + "\n");
//
//		for(int i = 0; i <m_iTreeModelNum; ++i)
//		{ 
//			CString model;
//
//			CString path = m_TreeModel.GetAt(i)->strModelPath; 		
//			CString temp;					
//			int n = path.ReverseFind('\\');//�Ӻ���ǰѰ��
//			temp = path.Right(path.GetLength() - n - 1);
//
//
//			model.Format("%s %d %.3f %d", temp,\
//				m_TreeModel.GetAt(i)->xPos, m_TreeModel.GetAt(i)->hPos, m_TreeModel.GetAt(i)->zPos);
//
//			file.WriteString(model + "\n");  
//		}
//
//	
//		/************************************************************************/
//		/*   3D������ 3D Tree													*/
//		/************************************************************************/
//		CString m_3DTreeModelNumStr;
//		m_3DTreeModelNumStr.Format("%d", m_i3DTreeModelNum);
//		file.WriteString(m_3DTreeModelNumStr + "\n");
//		
//		for(int i = 0; i <m_i3DTreeModelNum; ++i)
//		{
//			CString model;
//
//			CString path = m_3DTreeModel.GetAt(i)->strModelPath; 		
//			CString temp;					
//			int n = path.ReverseFind('\\');//�Ӻ���ǰѰ��
//			temp = path.Right(path.GetLength() - n - 1);
//
//
//			model.Format("%s %d %.3f %d", temp,\
//				m_3DTreeModel.GetAt(i)->xPos, m_3DTreeModel.GetAt(i)->hPos, m_3DTreeModel.GetAt(i)->zPos);
//
//			file.WriteString(model + "\n");   
//		} 
//
//	
//		/************************************************************************/
//		/*   ��������															*/
//		/************************************************************************/
//		file.WriteString(m_WeatherFolder + "\n");
//		file.WriteString(m_WeatherTex + "\n");
//		
//
//		/************************************************************************/
//		/*     ������·����														*/
//		/************************************************************************/
//		int JD_Count = myDesingScheme.PtS_JD.GetSize();
//		CString lineStr = "Line";
//		file.WriteString(lineStr + "\n");
//		// д�뽻�����
//		CString m_JDNumStr;
//		m_JDNumStr.Format("%d", JD_Count);
//		file.WriteString(m_JDNumStr + "\n");
//
//		if(JD_Count > 0)
//		{ 
//			// д�뽻������
//			CString str_JD_Position;
//			int JD_index = 0;
//			for(JD_index=0;JD_index<JD_Count-1;++JD_index)
//			{
//				str_JD_Position.Format("%.3f %.3f %.3f %ld %d ",myDesingScheme.PtS_JD[JD_index]->x,
//					myDesingScheme.PtS_JD[JD_index]->y,
//					myDesingScheme.PtS_JD[JD_index]->z,
//					myDesingScheme.JDCurveElements[JD_index]->R, 
//					myDesingScheme.JDCurveElements[JD_index]->L0
//					);
//				file.WriteString(str_JD_Position);
//			}
//			str_JD_Position.Format("%.3f %.3f %.3f %ld %d",myDesingScheme.PtS_JD[JD_index]->x,
//				myDesingScheme.PtS_JD[JD_index]->y,
//				myDesingScheme.PtS_JD[JD_index]->z,
//				0, 0
//				);
//			file.WriteString(str_JD_Position + "\n");
//		}
//		
//
//		file.Close();
//
//		return TRUE;
//	} 
//}

bool CMy3DSymbolLibNewView::ScenSave(CString scenePth)
{
	CStdioFile file; 
	BOOL openFlag = file.Open(scenePth, CStdioFile::modeCreate | CStdioFile::modeWrite);
	if(file == NULL || openFlag == FALSE)
	{
		MessageBox("��Ч�Ĺ����ļ���!", "���湤��", MB_ICONINFORMATION + MB_OK);
		return FALSE;
	}
	else
	{ 
		/************************************************************************/
		/*   ������������															*/
		/************************************************************************/
		file.WriteString(m_SceneConfig + "\n");


		/************************************************************************/
		/*   �������� Terrain													*/
		/************************************************************************/
		file.WriteString(m_TerrainFolder + "\n");
		//	  Tex Sand512.BMP
		file.WriteString(m_TerrainTextureFolder + " " + m_TerrainTexture + "\n"); 
		//	  Contour Terrain1.bmp
		file.WriteString(m_TerrainContourFolder + " " + m_TerrainContour + "\n"); 


		/************************************************************************/
		/*   ��պ����� SkyBox													*/
		/************************************************************************/
		file.WriteString(m_SkyBoxFolder + "\n");
		//	  0ȱʡ TOP.BMP LEFT.BMP BACK.BMP RIGHT.BMP FRONT.BMP
		file.WriteString(m_SkyBoxKindFolder + " " + m_SkyBoxTP + " " + m_SkyBoxLT + " "\
			+ m_SkyBoxBK + " " + m_SkyBoxRT + " " + m_SkyBoxFR + "\n"); 




		/************************************************************************/
		/*   ��������															*/
		/************************************************************************/
		file.WriteString(m_WeatherFolder + "\n");
		file.WriteString(m_WeatherTex + "\n");


		
		// д��������ļ�����
		file.WriteString("3\n");
		
		file.WriteString(m_PointSymbolFile + "\n");
		file.WriteString(m_LineSymbolFile + "\n");
		file.WriteString(m_AreaSymbolFile);


		file.Close();


		// ����������ļ�
		if(m_PointSymbolFile != "0")
			savePointSymbolFile(m_PointSymbolFile);
		if(m_LineSymbolFile != "0")
			saveLineSymbolFile(m_LineSymbolFile);
		if(m_AreaSymbolFile != "0")
			saveAreaSymbolFile(m_AreaSymbolFile);


		return TRUE;
	} 
}

/****************************************************************************/
/* Function: ����㡢�ߡ����ļ�												*/
/****************************************************************************/
// ������ļ�
int CMy3DSymbolLibNewView::savePointSymbolFile(CString filename)
{
	CStdioFile file; 
	file.Open(filename, CStdioFile::modeCreate | CStdioFile::modeWrite);
	if(file == NULL)
	{
		MessageBox("���ļ�������!", "������ļ�", MB_ICONINFORMATION + MB_OK);
		return FALSE;
	}
	else
	{ 
		file.WriteString("POINT\n");
		/************************************************************************/
		/*   3DS ģ������ 3DModel												*/
		/************************************************************************/
		file.WriteString(m_3DModelFolder + "\n");

		int count_model_existed = 0;
		for(int i = 0; i <m_i3DModelNum; ++i)
		{
			if(m_3DModel.GetAt(i)->isDeleted == false)
			{
				count_model_existed++;
			}
		}

		CString m_3DModelNumStr;
		m_3DModelNumStr.Format("%d", count_model_existed);
		file.WriteString(m_3DModelNumStr + "\n");


		for(int i = 0; i <m_i3DModelNum; ++i)
		{
			if(m_3DModel.GetAt(i)->isDeleted == false)
			{
				CString model; 
				CString path = m_3DModel.GetAt(i)->modelPath; 		
				CString temp;					
				int n = path.ReverseFind('\\');//�Ӻ���ǰѰ��
				temp = path.Right(path.GetLength() - n - 1);

				float pos_x = m_3DModel.GetAt(i)->posX;
				float pos_z = m_3DModel.GetAt(i)->posZ;
				float pos_y = m_3DModel.GetAt(i)->posY;

				float rot_x = m_3DModel.GetAt(i)->rotX;
				float rot_z = m_3DModel.GetAt(i)->rotZ;
				float rot_y = m_3DModel.GetAt(i)->rotY;

				float model_scale = m_3DModel.GetAt(i)->scale;

				model.Format("%s %.3f %.3f %.3f %.3f %.3f %.3f %.13f",temp, pos_x, pos_y, pos_z,rot_x,rot_y,rot_z,model_scale);

				file.WriteString(model + "\n"); 
			}

		}


		/************************************************************************/
		/*   ���б�ʶ���� City Symbol												*/
		/************************************************************************/
		file.WriteString(m_CitySymbolFolder + "\n");
		CString m_CitySymbolNumStr;
		m_CitySymbolNumStr.Format("%d", m_iCitySymbolModelNum);
		file.WriteString(m_CitySymbolNumStr + "\n");

		for(int i = 0; i <m_iCitySymbolModelNum; ++i)
		{
			CString model; 

			CString path = m_CitySymbolModel.GetAt(i)->strModelPath; 		
			CString temp;					
			int n = path.ReverseFind('\\');//�Ӻ���ǰѰ��
			temp = path.Right(path.GetLength() - n - 1);

			model.Format("%s %d %.3f %d", temp,\
				m_CitySymbolModel.GetAt(i)->xPos, m_CitySymbolModel.GetAt(i)->hPos, m_CitySymbolModel.GetAt(i)->zPos);

			file.WriteString(model + "\n"); 
		}


		/************************************************************************/
		/*   ���������� TreeModel												*/
		/************************************************************************/
		file.WriteString(m_TreeModelFolder + "\n");
		CString m_TreeModelNumStr;
		m_TreeModelNumStr.Format("%d", m_iTreeModelNum);
		file.WriteString(m_TreeModelNumStr + "\n");

		for(int i = 0; i <m_iTreeModelNum; ++i)
		{ 
			CString model;

			CString path = m_TreeModel.GetAt(i)->strModelPath; 		
			CString temp;					
			int n = path.ReverseFind('\\');//�Ӻ���ǰѰ��
			temp = path.Right(path.GetLength() - n - 1);


			model.Format("%s %d %.3f %d", temp,\
				m_TreeModel.GetAt(i)->xPos, m_TreeModel.GetAt(i)->hPos, m_TreeModel.GetAt(i)->zPos);

			file.WriteString(model + "\n");  
		}


		/************************************************************************/
		/*   3D������ 3D Tree													*/
		/************************************************************************/
		CString m_3DTreeModelNumStr;
		m_3DTreeModelNumStr.Format("%d", m_i3DTreeModelNum);
		file.WriteString(m_3DTreeModelNumStr + "\n");

		for(int i = 0; i <m_i3DTreeModelNum; ++i)
		{
			CString model;

			CString path = m_3DTreeModel.GetAt(i)->strModelPath; 		
			CString temp;					
			int n = path.ReverseFind('\\');//�Ӻ���ǰѰ��
			temp = path.Right(path.GetLength() - n - 1);


			model.Format("%s %d %.3f %d", temp,\
				m_3DTreeModel.GetAt(i)->xPos, m_3DTreeModel.GetAt(i)->hPos, m_3DTreeModel.GetAt(i)->zPos);

			file.WriteString(model + "\n");   
		} 



		file.Close();

	} 
	return 0;
}
// �������ļ�
int CMy3DSymbolLibNewView::saveLineSymbolFile(CString filename)
{

	return 0;
}
// �������ļ�
int CMy3DSymbolLibNewView::saveAreaSymbolFile(CString filename)
{
	CStdioFile file; 
	file.Open(filename, CStdioFile::modeCreate | CStdioFile::modeWrite);
	if(file == NULL)
	{
		MessageBox("���ļ�������!", "�������ļ�", MB_ICONINFORMATION + MB_OK);
		return FALSE;
	}
	else
	{ 
		file.WriteString("AREA\n");
		
		int size = m_Area4_Array.GetSize();
		for(int i=0;i<size;++i)
		{
			if(m_Area4_Array[i]->deleted == 1)
			{
				size--;
			}
		}

		CString polygon_count_str;
		polygon_count_str.Format("%d\n", size);


		file.WriteString(polygon_count_str);

		int polygon4_edges = 4;

		for(int i=0; i<m_Area4_Array.GetSize(); ++i)
		{
			if(m_Area4_Array[i]->deleted != 1)
			{
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
/* Function: ѡ��ģ��֮���Ҽ������˵��н�������ƶ�ģ�Ͳ���						*/
/****************************************************************************/
void CMy3DSymbolLibNewView::OnModelMove()
{
	m_OperateType = MOVE;
}


/****************************************************************************/
/* Function: �༭ģ�Ͳ���,����ģ������·��,��С,����,���ű���					*/
/****************************************************************************/
void CMy3DSymbolLibNewView::OnModelParam()
{
	ModelParam dlg;
	dlg.modelFolder = m_AllDataPath + "\\" + m_3DModelFolder + "\\";
		
	PModelParamStructToModelParamDlg(dlg, m_3DModel.GetAt(m_selectedModelID));
	if(dlg.DoModal())
	{
		ModelParamDlgToPModelParamStruct(dlg, m_3DModel.GetAt(m_selectedModelID));
	}
}


/****************************************************************************/
/* Function: �������öԻ����ڱ���ֱ��ȫ����ֵ���ṹ��							*/
/****************************************************************************/
void CMy3DSymbolLibNewView::ModelParamDlgToPModelParamStruct(ModelParam &model, PModelParamStruct pStruct)
{
	pStruct->posX = model.posX;
	pStruct->posY = model.posY;
	pStruct->posZ = model.posZ;

	pStruct->rotX = model.rotX;
	pStruct->rotY = model.rotY;
	pStruct->rotZ = model.rotZ;

	pStruct->scale = model.scale; 


	// ����3DSģ��
	if((model.modelChanged || model.isModelTextureUpdated))// && (pStruct->modelPath.Compare(model.modelPath) != 0))
	{
		pStruct->modelPath = model.modelPath;

		pStruct->m_3DS_Mode_Texture_PATH_NAME = model.m_TexturePathAndName;
	
		Load3DModel(pStruct, MODEL_CHANGE);
	}

}


/****************************************************************************/
/* Function: ���������Ի���													*/
/****************************************************************************/
void CMy3DSymbolLibNewView::PModelParamStructToModelParamDlg(ModelParam &model, PModelParamStruct pStruct)
{
	model.posX = pStruct->posX;
	model.posY = pStruct->posY;
	model.posZ = pStruct->posZ;

	model.rotX = pStruct->rotX;
	model.rotY = pStruct->rotY;
	model.rotZ = pStruct->rotZ;

	model.scale = pStruct->scale;

	CString path = pStruct->modelPath;
	int index = path.ReverseFind('\\');
	int index1 = path.ReverseFind('.');
	
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
/* Function: ����ѡ��ģ��														*/
/****************************************************************************/
void CMy3DSymbolLibNewView::OnModelScale()
{
	m_OperateType = SCALE;
}

/**************************************/
/* Function: ���÷����б�				  */
/**************************************/
void CMy3DSymbolLibNewView::OnConfigureSymbolList()
{
	// TODO: �ڴ���������������
	ModelListConfigureDialog mlcDlg;;
	if(mlcDlg.DoModal() == IDOK)
	{
		// null
	}

}

/**************************************/
/* Function: ϵͳ����				  */
/**************************************/
void CMy3DSymbolLibNewView::OnSystemSetting()
{
	// TODO: �ڴ���������������
	CSystemSetting sysSetDlg;
	if(sysSetDlg.DoModal() == IDOK)
	{
		// null	
	}
		
}

/**************************************/
/* Function: �رյ�ǰ����				  */
/**************************************/
void CMy3DSymbolLibNewView::OnCloseCurrentScene()
{
	// TODO: �ڴ���������������
	InitData();

	// ��ճ����еľ�����
	m_TreeModel.RemoveAll();
	// ��ճ����е�3D������
	m_3DTreeModel.RemoveAll();
	// ��ճ����еĳ��з���
	m_CitySymbolModel.RemoveAll();
	// ��ճ����е�3DSģ��
	m_3DModel.RemoveAll();

	// ���������·����
	clearLinesData();

	// ������е������
	m_Area4_Array.RemoveAll();


	// �����������
	OnFlyStop();
	if(m_ShowFlyPath==TRUE)
		m_ShowFlyPath=FALSE;
	m_FlayPath.RemoveAll();

}


/**************************************/
/* Function: ���������·����			  */
/**************************************/
void CMy3DSymbolLibNewView::clearLinesData()
{
	// ����
	myDesingScheme.PtS_JD.RemoveAll();
	// ��·����
	myDesingScheme.PtS_3DLineZX.RemoveAll();
	// ·��
	myDesingScheme.PtS_RailwayLj3D.RemoveAll();
	// ���
	myDesingScheme.PtS_Railway3D.RemoveAll();
	// ��·��ƽ���
	myDesingScheme.JDCurveElements.RemoveAll();
	myDesingScheme.PtS_RailwayLjToBP3D.RemoveAll();
	myDesingScheme.PtS_RailwayBP3D.RemoveAll();
	myDesingScheme.PtS_HuPo.RemoveAll();
	myDesingScheme.PtSHuPoTemp.RemoveAll();
}


/********************************************/
/* Function: ѡ��ģ�ͺ�,�һ��˵�,ɾ��ģ��		*/
/********************************************/
void CMy3DSymbolLibNewView::OnModelDelete()
{
	m_3DModel.GetAt(m_selectedModelID)->isDeleted = true;

	m_3DModel.GetAt(m_selectedModelID)->modelSelected = false;

	vector<PSelectedModel>::iterator ite; 
	for(vector<PSelectedModel>::iterator it = m_pSelectedModelSet.begin(); it != m_pSelectedModelSet.end(); ++it)
	{ 
		if((*it)->modelID == (m_3DModel.GetAt(m_selectedModelID)->modelID))
		{ 
			ite = it;
			m_pSelectedModelSet.erase(ite); 
			break;
		}
	}
}


/************************************************************************/
/*                        ��·���                                       */
/************************************************************************/

/**************************************/
/* Function: ��·��ά��ģ				  */
/**************************************/
void CMy3DSymbolLibNewView::OnMenuBuild3dlinemodle()
{
	// TODO: �ڴ���������������

	// ����� ϵͳæ
	BeginWaitCursor();

	myDesingScheme.CalculateCurveData();
	
	myDesingScheme.PtS_Railway3D.RemoveAll();

	myDesingScheme.PtS_RailwayLj3D.RemoveAll();
	myDesingScheme.PtS_RailwayLjToBP3D.RemoveAll();
	myDesingScheme.PtS_RailwayBP3D.RemoveAll();
	myDesingScheme.PtS_HuPo.RemoveAll();
		 
	if(myDesingScheme.PtS_3DLineZX.GetSize()<2)
		return;

	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;

	double EndLC = 10000;
	
	for(long i=0;i<myDesingScheme.PtS_3DLineZX.GetSize()-1;i++)
	{	
		if(myDesingScheme.PtS_3DLineZX.GetAt(i+1)->Lc <= EndLC)
		{

			myDesingScheme.Get3DLineModel(myDesingScheme.PtS_3DLineZX.GetAt(i)->x,\
				myDesingScheme.PtS_3DLineZX.GetAt(i)->y,\
				myDesingScheme.PtS_3DLineZX.GetAt(i)->z,\
				myDesingScheme.PtS_3DLineZX.GetAt(i+1)->x,\
				myDesingScheme.PtS_3DLineZX.GetAt(i+1)->y,\
				myDesingScheme.PtS_3DLineZX.GetAt(i+1)->z,\
				m_Railway.m_Railway_width,m_Railway.m_Lj_width,m_Railway.m_Lj_Dh,\
				m_Railway.m_GuiMianToLujianWidth,45,\
				myDesingScheme.PtS_3DLineZX.GetAt(i)->strJDStyle,\
				myDesingScheme.PtS_3DLineZX.GetAt(i+1)->strJDStyle,\
				i,\
				myDesingScheme.PtS_3DLineZX.GetAt(i)->Lc
				);
		}
	}
	if(myDesingScheme.PtS_3DLineZX.GetAt(myDesingScheme.PtS_3DLineZX.GetSize()-1)->Lc <= EndLC)//myDesingScheme.SchemeDatass.EndLC)
	{
		myDesingScheme.Get3DLineModelLast(myDesingScheme.PtS_3DLineZX.GetAt(myDesingScheme.PtS_3DLineZX.GetSize()-2)->x,\
			myDesingScheme.PtS_3DLineZX.GetAt(myDesingScheme.PtS_3DLineZX.GetSize()-2)->y,\
			myDesingScheme.PtS_3DLineZX.GetAt(myDesingScheme.PtS_3DLineZX.GetSize()-2)->z,\
			myDesingScheme.PtS_3DLineZX.GetAt(myDesingScheme.PtS_3DLineZX.GetSize()-1)->x,\
			myDesingScheme.PtS_3DLineZX.GetAt(myDesingScheme.PtS_3DLineZX.GetSize()-1)->y,\
			myDesingScheme.PtS_3DLineZX.GetAt(myDesingScheme.PtS_3DLineZX.GetSize()-1)->z,\
			m_Railway.m_Railway_width,m_Railway.m_Lj_width,m_Railway.m_Lj_Dh,\
			m_Railway.m_GuiMianToLujianWidth,45,\
			myDesingScheme.PtS_3DLineZX.GetAt(myDesingScheme.PtS_3DLineZX.GetSize()-2)->strJDStyle,\
			myDesingScheme.PtS_3DLineZX.GetAt(myDesingScheme.PtS_3DLineZX.GetSize()-1)->strJDStyle,\
			myDesingScheme.PtS_3DLineZX.GetSize()-2,\
			myDesingScheme.PtS_3DLineZX.GetAt(myDesingScheme.PtS_3DLineZX.GetSize()-2)->Lc\
			);
	}
	b_haveMadeRail3DwayList=FALSE;

	OnDraw (GetDC()); //ˢ����ά����
}

/**************************************/
/* Function: ��άѡ�����				  */
/**************************************/
void CMy3DSymbolLibNewView::OnMenuLinedesign()
{
	// TODO: �ڴ���������������
	if(m_QueryType==SELECTLINE)		//�����ǰ�Ѿ���άѡ��״̬����ر�
		m_QueryType=-1;
	else							//�����ǰ������άѡ��״̬�����
		m_QueryType=SELECTLINE;
}

/****************************************************/
/* Function: ������άѡ�����ѡ��״̬					*/
/****************************************************/
void CMy3DSymbolLibNewView::OnUpdateMenuLinedesign(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_QueryType==SELECTLINE);
}


/****************************************************/
/* Function: ʵ��͸��ͶӰģʽ�µ���·��άģ�ͻ���		*/
/****************************************************/
void CMy3DSymbolLibNewView::DrawRailwaythesme()
{ 
	//ѹ�����Զ�ջ
	glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT | GL_POLYGON_BIT );
	glEnable(GL_DEPTH_TEST | GL_CULL_FACE);
	glCullFace(GL_BACK);

	CString m_style,m_stylePre,m_styleNext;
	
	SetDrawMode();							//���û�ͼģʽ
	glViewport(0, 0, WinViewX, WinViewY);	//���������ӿڴ�С

	//�����û�й�����·��άģ�͵���ʾ�б�
	if(b_haveMadeRail3DwayList == FALSE )  
	{			
		glNewList(m_Rail3DwayList,GL_COMPILE_AND_EXECUTE); //������ʾ�б�
		
		glColor3f(0.75,0.75,0.75);			//������ɫ
		glLineWidth(2.0);					//�����߿�

		// 1.�������·������
		glColor3f(1,0,0);		
		glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());			//��·����������

		for(int i=0;i<myDesingScheme.PtS_HuPo.GetSize()-1;i++)
		{
			m_style=myDesingScheme.PtS_3DLineZX.GetAt(i)->strJDStyle;	//��������
			m_styleNext=myDesingScheme.PtS_3DLineZX.GetAt(i+1)->strJDStyle;	
		
			//������������Ƿ������ĵ㣬�����·������
			if(m_style != "...")
			{	
				DrawBP(i,1); //�������·������
			}
		
		}

		// 2.�����Ҳ�·������
		glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());				//��·����������
		
		for (int i=0;i<myDesingScheme.PtS_HuPo.GetSize()-1;i++)
		{
			m_style=myDesingScheme.PtS_3DLineZX.GetAt(i)->strJDStyle;		//��������
			m_styleNext=myDesingScheme.PtS_3DLineZX.GetAt(i+1)->strJDStyle;	//��һ��Ľ�������
			
			if(m_style != "...")
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				DrawBP(i,2);//�����Ҳ�·������
			}
			 
		}
		
		// 3.���ƹ��
		glBindTexture(GL_TEXTURE_2D, m_cTxtureRailway.GetTxtID());			// �󶨹������
	 	glLineWidth(2.0);													// �����߿�
		for (int i=0;i<myDesingScheme.PtS_Railway3D.GetSize()-1;i++)
		{
			
			if(myDesingScheme.PtS_3DLineZX.GetAt(i)->Derh==0)				// �����Ϊ0
				glColor3f(0,1,1);											// ������ɫ
			else
				glColor3f(1,0,1);
			float L=myDesingScheme.GetDistenceXY(myDesingScheme.PtS_Railway3D.GetAt(i)->x1,\
				myDesingScheme.PtS_Railway3D.GetAt(i)->z1,\
				myDesingScheme.PtS_Railway3D.GetAt(i+1)->x2,\
				myDesingScheme.PtS_Railway3D.GetAt(i+1)->z2);
		
			// �Ծ��η�ʽ����ǰ�����ٹ������	
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f); // ������������(��ǰ�����������)
			glVertex3f(myDesingScheme.PtS_Railway3D.GetAt(i)->x1,\
				myDesingScheme.PtS_Railway3D.GetAt(i)->y1,
				myDesingScheme.PtS_Railway3D.GetAt(i)->z1);
			glTexCoord2f(1.0f,0.0f); // ������������(��ǰ��������Ҳ��)
			glVertex3f(myDesingScheme.PtS_Railway3D.GetAt(i)->x2,\
				myDesingScheme.PtS_Railway3D.GetAt(i)->y2,
				myDesingScheme.PtS_Railway3D.GetAt(i)->z2);
			glTexCoord2f(1.0f,L/10);// ������������(��һǰ��������Ҳ��)
			glVertex3f(myDesingScheme.PtS_Railway3D.GetAt(i+1)->x2,\
				myDesingScheme.PtS_Railway3D.GetAt(i+1)->y2,
				myDesingScheme.PtS_Railway3D.GetAt(i+1)->z2);
			glTexCoord2f(0.0f,L/10); // ������������(��һǰ�����������)
			glVertex3f(myDesingScheme.PtS_Railway3D.GetAt(i+1)->x1,\
				myDesingScheme.PtS_Railway3D.GetAt(i+1)->y1,
				myDesingScheme.PtS_Railway3D.GetAt(i+1)->z1);
			glEnd();
		}		

		// 4.���Ƶ�������
		glBindTexture(GL_TEXTURE_2D, m_cTxtureGdToLJ.GetTxtID());// �󶨵�����������
		glColor3f(1,1,0);// ������ɫ
		for (int i=0;i<myDesingScheme.PtS_Railway3D.GetSize()-1;i++)
		{
			// �Ծ��η�ʽ���ӷ�ʽ��������������	
			glBegin(GL_POLYGON);
			glTexCoord2f(1.0f,0.0f);// ������������(��ǰ��������������)
			glVertex3f(myDesingScheme.PtS_Railway3D.GetAt(i)->x1,\
				myDesingScheme.PtS_Railway3D.GetAt(i)->y1,
				myDesingScheme.PtS_Railway3D.GetAt(i)->z1);
			glTexCoord2f(1.0f,1.0f);// ������������(��ǰ�����������Ҳ��)
			glVertex3f(myDesingScheme.PtS_Railway3D.GetAt(i+1)->x1,\
				myDesingScheme.PtS_Railway3D.GetAt(i+1)->y1,
				myDesingScheme.PtS_Railway3D.GetAt(i+1)->z1);
			glTexCoord2f(0.0f,1.0f);// ������������(��һ�����������Ҳ��)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D.GetAt(i+1)->x1,\
				myDesingScheme.PtS_RailwayLj3D.GetAt(i+1)->y1,
				myDesingScheme.PtS_RailwayLj3D.GetAt(i+1)->z1);
			glTexCoord2f(0.0f,0.0f);// ������������(��һ��������������)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D.GetAt(i)->x1,\
				myDesingScheme.PtS_RailwayLj3D.GetAt(i)->y1,
				myDesingScheme.PtS_RailwayLj3D.GetAt(i)->z1);
			glEnd();
			
			// �Ծ��η�ʽ���ӷ�ʽ�����Ҳ��������
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f);// ������������(��ǰ�Ҳ������������)
			glVertex3f(myDesingScheme.PtS_Railway3D.GetAt(i)->x2,\
				myDesingScheme.PtS_Railway3D.GetAt(i)->y2,
				myDesingScheme.PtS_Railway3D.GetAt(i)->z2);
			glTexCoord2f(0.0f,1.0f);// ������������(��ǰ�Ҳ���������Ҳ��)
			glVertex3f(myDesingScheme.PtS_Railway3D.GetAt(i+1)->x2,\
				myDesingScheme.PtS_Railway3D.GetAt(i+1)->y2,
				myDesingScheme.PtS_Railway3D.GetAt(i+1)->z2);
			glTexCoord2f(1.0f,1.0f);// ������������(��һ�Ҳ���������Ҳ��)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D.GetAt(i+1)->x2,\
				myDesingScheme.PtS_RailwayLj3D.GetAt(i+1)->y2,
				myDesingScheme.PtS_RailwayLj3D.GetAt(i+1)->z2);
			glTexCoord2f(1.0f,0.0f);// ������������(��һ�Ҳ������������)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D.GetAt(i)->x2,\
				myDesingScheme.PtS_RailwayLj3D.GetAt(i)->y2,
				myDesingScheme.PtS_RailwayLj3D.GetAt(i)->z2);
			glEnd();
		}		
		
		// 5.����·��
		glBindTexture(GL_TEXTURE_2D, m_cTxtureLJ.GetTxtID());//��·������
		glColor3f(1,0.5,0.25);
		for (int i=0;i<myDesingScheme.PtS_RailwayLj3D.GetSize()-1;i++)
		{
			//�Ծ��η�ʽ���ӷ�ʽ�������·��	
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f);// ������������(��ǰ���·���������)
			glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i)->x1,\
				myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i)->y1,
				myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i)->z1);
			glTexCoord2f(0.0f,1.0f);// ������������(��ǰ���·������Ҳ��)	
			glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i+1)->x1,\
				myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i+1)->y1,
				myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i+1)->z1);
			glTexCoord2f(1.0f,1.0f);// ������������(��һ���·������Ҳ��)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D.GetAt(i+1)->x1,\
				myDesingScheme.PtS_RailwayLj3D.GetAt(i+1)->y1,
				myDesingScheme.PtS_RailwayLj3D.GetAt(i+1)->z1);
			glTexCoord2f(1.0f,0.0f);// ������������(��һ���·���������)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D.GetAt(i)->x1,\
				myDesingScheme.PtS_RailwayLj3D.GetAt(i)->y1,
				myDesingScheme.PtS_RailwayLj3D.GetAt(i)->z1);
			glEnd();			

			// �Ծ��η�ʽ���ӷ�ʽ�����Ҳ�·��	
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f);// ������������(��ǰ�Ҳ�·���������)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D.GetAt(i)->x2,\
				myDesingScheme.PtS_RailwayLj3D.GetAt(i)->y2,
				myDesingScheme.PtS_RailwayLj3D.GetAt(i)->z2);
			glTexCoord2f(1.0f,0.0f);// ������������(��ǰ�Ҳ�·������Ҳ��)
			glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i)->x2,\
				myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i)->y2,
				myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i)->z2);
			glTexCoord2f(1.0f,1.0f);// ������������(��һ�Ҳ�·������Ҳ��)
			glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i+1)->x2,\
				myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i+1)->y2,
				myDesingScheme.PtS_RailwayLjToBP3D.GetAt(i+1)->z2);
			glTexCoord2f(0.0f,1.0f);// ������������(��һ�Ҳ�·���������)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D.GetAt(i+1)->x2,\
				myDesingScheme.PtS_RailwayLj3D.GetAt(i+1)->y2,
				myDesingScheme.PtS_RailwayLj3D.GetAt(i+1)->z2);
			glEnd();
		}

		// 6.�����
		int JD_Count = myDesingScheme.PtS_JD.GetSize();
		int b_pIndex = 0;
		int e_pIndex = JD_Count - 1;

		if(JD_Count > 0)
		{
			// ����2�����ϵĵ��������Ϣ
			vector<Railway3DCordinate> rc2;
			vector<Railway3DCordinate> rc1;

			// ����ǰ��������
			myDesingScheme.CalculateFillFacePoints(rc2,rc1);

			// ���ݵ������
			drawFillFace(rc2);
			drawFillFace(rc1);
		}
		

		glLineWidth(1.0);				// �ָ��߿�
		glEndList();					// ������ʾ�б�
	
		b_haveMadeRail3DwayList=TRUE;	// ��ʶ�Ѿ�������ʾ�б�
	}
	else								//����Ѿ�������·��άģ�͵���ʾ�б�,��ֱ�ӵ�����ʾ�б�
	{ 
		glCallList(m_Rail3DwayList);	//������·��άģ����ʾ�б�
	}
	glPopAttrib();						//�������Զ�ջ
}
	
/**************************************/
/* Function: ���ݵ������				  */
/**************************************/
void CMy3DSymbolLibNewView::drawFillFace(vector<Railway3DCordinate> fillFacePoints)
{
	int f_size = fillFacePoints.size();
	
	glBindTexture(GL_TEXTURE_2D, m_cFillFaceTxture.GetTxtID());
	glColor3f(0.5, 0.6, 0.3);  
	// ���ı���Ϊ��λ���ϵ����������
	for(int i=0;i<7;i+=2)
	{
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f,1.0f);
			glVertex3f(fillFacePoints[i].x1,fillFacePoints[i].y1,fillFacePoints[i].z1);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(fillFacePoints[i+1].x1,fillFacePoints[i+1].y1,fillFacePoints[i+1].z1);

			glTexCoord2f(1.0f,0.0f);
			glVertex3f(fillFacePoints[i+1].x2,fillFacePoints[i+1].y2,fillFacePoints[i+1].z2);
			glTexCoord2f(1.0f,1.0f);
			glVertex3f(fillFacePoints[i].x2,fillFacePoints[i].y2,fillFacePoints[i].z2);
			
		}
		glEnd();
	}
}

/**************************************/
/* Function: ����������				  */
/**************************************/
void CMy3DSymbolLibNewView::DrawCenterLine(long index, BOOL ifSelectLine)
{
	CString tt;
	double x1,y1,z1,x2,y2,z2;
	double x0,y0,z0;
	float DerDistence=2.0;

	float Dh;
	
	m_TempPts.RemoveAll();
	
	if(ifSelectLine==TRUE) //��ѡ�����
	{
		Dh=5;
		x1=myDesingScheme.PtS_JD.GetAt(index)->x;
		//y1=myDesingScheme.PtS_JD.GetAt(index)->y;
		z1=myDesingScheme.PtS_JD.GetAt(index)->z;
		y1=GetHeight(x1,z1);

		x2=myDesingScheme.PtS_JD.GetAt(index+1)->x;
		//y2=myDesingScheme.PtS_JD.GetAt(index+1)->y;
		z2=myDesingScheme.PtS_JD.GetAt(index+1)->z;
		y2=GetHeight(x2,z2);
	}
	glColor3f(0,0,1);

	PCordinate pt;
	
	double L=myDesingScheme.GetDistenceXYZ(x1,y1,z1,x2,y2,z2);
	double L0=0;

	while(L0<=L)
	{
		x0=x1+L0/L*(x2-x1); y0=y1+L0/L*(y2-y1); z0=z1+L0/L*(z2-z1);		
		//����߳�
		float dmh = GetHeight(x0,-z0);
		if(y0>=dmh-Dh)  //����ߵ�̴߳��ڵ���߳�
		{
			pt=new Cordinate;
			pt->x =x0; pt->y=y0; pt->z =z0;
			m_TempPts.Add(pt);
		}
		else
		{
			if(m_TempPts.GetSize()>1)
			{		
				glBegin(GL_LINE_STRIP);
				for(int k=0;k<m_TempPts.GetSize();k++){
					glVertex3f(m_TempPts.GetAt(k)->x, m_TempPts.GetAt(k)->y, m_TempPts.GetAt(k)->z);
				}
				glEnd();
				m_TempPts.RemoveAll();
				L0-=DerDistence;
			}
		}
		L0 += DerDistence;
		if(L0 >= L)
		{
			x0 = x2; y0 = y2; z0 = z2;
			dmh = GetHeight(x0,-z0);
			if(y0 >= dmh-Dh )// ����ߵ�̴߳��ڵ���߳�
			{
				pt=new Cordinate;
				pt->x = x0; pt->y = y0; pt->z = z0;
				m_TempPts.Add(pt);
				if(m_TempPts.GetSize()>1)
				{	
					glBegin(GL_LINE_STRIP);
					for(int k=0;k<m_TempPts.GetSize();k++){
						glVertex3f(m_TempPts.GetAt(k)->x, m_TempPts.GetAt(k)->y, m_TempPts.GetAt(k)->z);
					}
					glEnd();
					m_TempPts.RemoveAll();
				}
			}
			break;
		}
	}
	if(m_TempPts.GetSize()>1)
	{			
		glBegin(GL_LINE_STRIP);
		for(int k=0;k<m_TempPts.GetSize();k++)
		{
			glVertex3f(m_TempPts.GetAt(k)->x, m_TempPts.GetAt(k)->y, m_TempPts.GetAt(k)->z);
		}
		glEnd();
		m_TempPts.RemoveAll();
	}
}

/**************************************/
/* Function: ���Ʊ���				  */
/**************************************/
void CMy3DSymbolLibNewView::DrawBP(long index, int BPside)
{
	float mNCDistence = 4.0;
	long i = index;
	int j;
	if(1 == BPside) //�����
	{
		int N1 = myDesingScheme.PtS_HuPo.GetAt(i)->Huponums_L;
		int N2 = myDesingScheme.PtS_HuPo.GetAt(i+1)->Huponums_L;

		if(myDesingScheme.PtS_HuPo.GetAt(i)->TW_left==0 || myDesingScheme.PtS_HuPo.GetAt(i)->TW_right==0){
			glColor3f(0,1,1);
		}
		else{
			glColor3f(1,0,0);
		}
		if(N1<=N2 && N1>0 && N2>0)
		{
			for(j=0;j<N1;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				
				//���·��������ͬ(ͬΪ·ǵ��·��)
				if(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].style == myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].style)
				{
					glBegin		(GL_POLYGON);
					glTexCoord2f(0.0f,1.0f); 
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].z);
					glTexCoord2f(0.0f,0.0f); 
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f); 
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,1.0f); 
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[2].z);
					glEnd();
				}
				else  //���·��������ͬ(·ǵ,·������)
				{
					glBegin		(GL_POLYGON);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j+1].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j+1].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j+1].Hp[2].z);
					glEnd();
					
					glBegin(GL_POLYGON);
						glTexCoord2f(0.0f,0.0f);
						glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j+1].Hp[2].x,
							myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j+1].Hp[2].y,
							myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j+1].Hp[2].z);
						glTexCoord2f(0.5f,0.5f);
						glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j+1].Hp[1].x,
							myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j+1].Hp[1].y,
							myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j+1].Hp[1].z);
						glTexCoord2f(0.5f,1.0f);
						glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[2].x,
							myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[2].y,
							myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[2].z);
						glTexCoord2f(1.0f,0.0f);
						glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[1].x,
							myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[1].y,
							myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[1].z);
						glEnd();
				}
				if(j>0) 
				{
					glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[0].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[0].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[0].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[0].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[0].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[0].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[1].z);
					glEnd();
				}
			}
		}
		else 
		{
			for(j=0;j<N2;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				
				if(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].style==\
					myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].style)
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[2].z);
					glEnd();
				}
				else
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j+1].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j+1].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j+1].Hp[2].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[2].z);
					glEnd();
					
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j+1].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j+1].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j+1].Hp[2].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j+1].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j+1].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j+1].Hp[1].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[2].z);
					glEnd();
					
				}
			
				if(j>0) 
				{
					glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());
					
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[0].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[0].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_L[j].Hp[0].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[0].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[0].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[0].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_L[j].Hp[1].z);
					glEnd();
				}
			}
		}
	}
	else if(BPside == 2) 
	{
		int N1 = myDesingScheme.PtS_HuPo.GetAt(i)->Huponums_R;
		int N2 = myDesingScheme.PtS_HuPo.GetAt(i+1)->Huponums_R;
		if(N1<=N2 && N1>0 && N2>0)
		{
			for(j=0;j<N1;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				if(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].style==\
					myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].style)
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[2].z);
					glEnd();
				}
				else
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j+1].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j+1].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j+1].Hp[2].z);
					glEnd();
					
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j+1].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j+1].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j+1].Hp[2].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j+1].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j+1].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j+1].Hp[1].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[2].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[1].z);
					glEnd();
				}
				
				if(j>0) 
				{
					glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());

					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[0].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[0].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[0].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[0].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[0].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[0].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[1].z);
					glEnd();
				}
			}
		}
		else 
		{
			for(j=0;j<N2;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				if(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].style==\
					myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].style)
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[2].z);
					glEnd();
				}
				else
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j+1].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j+1].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j+1].Hp[2].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[2].z);
					glEnd();
					
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j+1].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j+1].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j+1].Hp[2].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j+1].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j+1].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j+1].Hp[1].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[2].z);
					glEnd();
				}
				
				if(j>0) 
				{
					glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[0].x,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[0].y,
						myDesingScheme.PtS_HuPo.GetAt(i)->HuPo_R[j].Hp[0].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[0].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[0].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[0].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f	(myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo.GetAt(i+1)->HuPo_R[j].Hp[1].z);
					glEnd();
				}
			}
		}
	}
	glLineWidth(1.0);
	glColor3f(1,1,1);
}

/**************************************/
/* Function: ���������·				  */
/**************************************/
void CMy3DSymbolLibNewView::OnMenuClearLines()
{
	// TODO: �ڴ���������������
	clearLinesData();
	initLines();
}


/************************************************************************/
/* Function: �½�����							                        */
/************************************************************************/
void CMy3DSymbolLibNewView::OnSceneNew()
{
	// TODO: �ڴ���������������
	
	//step 1 : ���ù����ļ���, �������ļ�
	CString 	NeededFile;
	char 		FileFilter[] = "�����ļ�(*.prj)|*.prj|";

	//�����ļ��Ի�������
	DWORD 		FileDialogFlag = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
	CFileDialog FileDialogBoxFile(FALSE, NULL, 0, FileDialogFlag, FileFilter, this);
	FileDialogBoxFile.m_ofn.lpstrTitle = "�½�����";
	char		FileName[200];


	CString sceneDir = m_AllDataPath + "\\" + m_SceneConfig;
	FileDialogBoxFile.m_ofn.lpstrInitialDir = sceneDir;

	CString tt[3];
	if( FileDialogBoxFile.DoModal() == IDOK )			//����Ի���ɹ���
	{	
		NeededFile = FileDialogBoxFile.GetPathName();	//�õ��ļ���
		sprintf(FileName, "%s", NeededFile);
		if(strcmp(FileDialogBoxFile.GetFileExt(),"prj")!=0) 
			strcat(FileName,".prj");				 

		{
			CStdioFile file; 
			file.Open(FileName, CStdioFile::modeCreate | CStdioFile::modeWrite);
			if(file == NULL)
			{
				MessageBox("ERROR!","ERROR", MB_ICONINFORMATION + MB_OK);
				return;
			}
			else
			{ 
				CString tmpSceneConfig = "SceneConfig";
				CString tmpTerrainFolder = "Terrain";
				CString tmpTerrainTextureFolder = "Tex";		CString tmpTerrainTexture = "Sand512.BMP";
				CString tmpTerrainContourFolder = "Contour";	CString tmpTerrainContour = "Terrain1.bmp";

				CString tmpSkyBoxFolder = "SkyBox";		CString tmpSkyBoxKindFolder = "default"; 
				CString tmpSkyBoxTP = "TOP.BMP";		CString tmpSkyBoxLT = "LEFT.BMP";
				CString tmpSkyBoxBK = "BACK.BMP";		CString tmpSkyBoxRT = "RIGHT.BMP"; 
				CString tmpSkyBoxFR = "FRONT.BMP";

				CString tmpWeatherFolder = "Weather"; CString tmpWeatherTex = "a0.bmp";


				/************************************************************************/
				/*   ������������															*/
				/************************************************************************/
				file.WriteString(tmpSceneConfig + "\n");


				/************************************************************************/
				/*   �������� Terrain													*/
				/************************************************************************/
				file.WriteString(tmpTerrainFolder + "\n");
				//	  Tex Sand512.BMP
				file.WriteString(tmpTerrainTextureFolder + " " + tmpTerrainTexture + "\n"); 
				//	  Contour Terrain1.bmp
				file.WriteString(tmpTerrainContourFolder + " " + tmpTerrainContour + "\n"); 


				/************************************************************************/
				/*   ��պ����� SkyBox													*/
				/************************************************************************/
				file.WriteString(tmpSkyBoxFolder + "\n");
				//	  0ȱʡ TOP.BMP LEFT.BMP BACK.BMP RIGHT.BMP FRONT.BMP
				file.WriteString(tmpSkyBoxKindFolder + " " + tmpSkyBoxTP + " " + tmpSkyBoxLT + " "\
					+ tmpSkyBoxBK + " " + tmpSkyBoxRT + " " + tmpSkyBoxFR + "\n"); 


				/************************************************************************/
				/*   ��������															*/
				/************************************************************************/
				file.WriteString(tmpWeatherFolder + "\n");
				file.WriteString(tmpWeatherTex + "\n");


				//����������ļ�����
				file.WriteString("3\n");	//����
				file.WriteString("0\n");	//point  (0��ʾ���޸��ļ�)
				file.WriteString("0\n");	//line
				file.WriteString("0");		//area


				file.Close();
			} 
		}
	}	
	else
		return;

	//step 2 : ͨ���½��Ĺ����ļ����ظù��̵���ͼ������

	loadSceneFile(FileName);
	m_CurrentProjectName = FileName;

	OnDraw (GetDC()); //ˢ����ά����
}


// �жϵ�ǰ�������Ƿ�����Ѿ��򿪵ĵ㡢�ߡ����ļ�
BOOL CMy3DSymbolLibNewView::exist_point_file()
{
	return exist_point_flag;
}
BOOL CMy3DSymbolLibNewView::exist_line_file()
{
	return exist_line_flag;
}
BOOL CMy3DSymbolLibNewView::exist_area_file()
{
	return exist_area_flag;
}


// �ɹ�����0 ,���򷵻�-1; type:0-��, 1-��, 2-��, _fileName:�������ļ���ͨ����������������
int CMy3DSymbolLibNewView::new_symbol_file(unsigned int type, char *_fileName)
{
	CString 	NeededFile;
	char FileFilter[32] = {0};

	char *tmpAgrs[3][5] = {	{"���ļ�(*.pt)|*.pt|",	"�½����ļ�",	"pt",	".pt",	"POINT\n"	},
							{"���ļ�(*.ln)|*.ln|",	"�½����ļ�",	"ln",	".ln",	"LINE\n"	},
							{"���ļ�(*.gsf)|*.gsf|",	"�½����ļ�",	"gsf",	".gsf",	"AREA\n"	}
					   };

	
	strcpy_s(FileFilter, tmpAgrs[type][0]);
	

	

	//�����ļ��Ի�������
	DWORD 		FileDialogFlag = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
	CFileDialog FileDialogBoxFile(FALSE, NULL, 0, FileDialogFlag, FileFilter, this);

	LPCSTR tmpLpcstrTitle = "�½����ļ�";

	tmpLpcstrTitle = tmpAgrs[type][1];
	 
	FileDialogBoxFile.m_ofn.lpstrTitle = tmpLpcstrTitle;
	char		FileName[200];


	CString sceneDir = m_AllDataPath + "\\" + m_SceneConfig;
	FileDialogBoxFile.m_ofn.lpstrInitialDir = sceneDir;

	CString tt[3];
	if( FileDialogBoxFile.DoModal() == IDOK )			//����Ի���ɹ���
	{	
		NeededFile = FileDialogBoxFile.GetPathName();	//�õ��ļ���
		sprintf(FileName, "%s", NeededFile);
		if(strcmp(FileDialogBoxFile.GetFileExt(), tmpAgrs[type][2])!=0) 
			strcat(FileName, tmpAgrs[type][3]);				 

		{
			CStdioFile file; 
			file.Open(FileName, CStdioFile::modeCreate | CStdioFile::modeWrite);
			if(file == NULL)
			{
				MessageBox("ERROR!","ERROR", MB_ICONINFORMATION + MB_OK);
				return -1;
			}
			else
			{ 
				strcpy(_fileName, FileName);
				//file.WriteString( tmpAgrs[type][4] );
				file.Close();
			} 
		} 
		return 0;
	}		

	return -1;
}


// �½������ļ�, 0-��, 1-��, 2-��
int CMy3DSymbolLibNewView::new_point_file()
{
	int newFileFlag = 0;
	char tmpPointFileName[200] = {0};
	newFileFlag = new_symbol_file(0, tmpPointFileName);
	m_PointSymbolFile = tmpPointFileName;
	return newFileFlag;
}
int CMy3DSymbolLibNewView::new_line_file()
{
	int newFileFlag = 0;
	char tmpLineFileName[200] = {0};
	newFileFlag = new_symbol_file(1, tmpLineFileName);
	m_LineSymbolFile = tmpLineFileName;
	return newFileFlag;
}
int CMy3DSymbolLibNewView::new_area_file()
{
	int newFileFlag = 0;
	char tmpAreaFileName[200] = {0};
	newFileFlag = new_symbol_file(2, tmpAreaFileName);
	m_AreaSymbolFile = tmpAreaFileName;
	return newFileFlag;
}


//--------------------------------------------------------------------------------------



/************************************************************************/
/*								�߷���									*/
/************************************************************************/

// �߱༭ ==�� �����
void CMy3DSymbolLibNewView::OnMenuLineAdd()
{
	// TODO: �ڴ���������������
	if(m_QueryType==LINE_ADD)	 
		m_QueryType=-1;
	else							 
		m_QueryType=LINE_ADD;
}


// �߱༭ ==���ں�   ��ʸ����ر��������ں�
void CMy3DSymbolLibNewView::OnMenuLineFuse()
{
	// TODO: �ڴ���������������
	int tmp_rowNum = 0;
	int tmp_row_index_begin = 0;
	int tmp_row_index_end = 0;

	int tmp_colNum = 0;
	int tmp_col_index_begin = 0; 
	int tmp_col_index_end = 0;

	Line3 tmp_line;
	tmp_line.pt1 = m_LinesArray[0]->pt1;
	tmp_line.pt2 = m_LinesArray[0]->pt2;

	//1
	tmp_line.pt1 = m_LinesArray[0]->pt1;
	tmp_line.pt2 = m_LinesArray[0]->pt2;



	//if(abs(tmp_line.pt1._x - tmp_line.pt2._x) < MAP_SCALE)
	{
		tmp_line.pt1._x -= 1;
		tmp_line.pt2._x -= 1;
	}
	//else
	//{
	//	tmp_line.pt1._z += 5;
	//	tmp_line.pt2._z += 5;
	//}
	
	

	CalcuateGridNum(&tmp_rowNum, &tmp_row_index_begin, &tmp_row_index_end,
		&tmp_colNum, &tmp_col_index_begin, &tmp_col_index_end, tmp_line);
	

	CalcuateJD(tmp_rowNum, tmp_row_index_begin, tmp_row_index_end,
		tmp_colNum, tmp_col_index_begin, tmp_col_index_end, tmp_line, Line_a_JD_vector);



	tmp_line.pt1 = m_LinesArray[0]->pt1;
	tmp_line.pt2 = m_LinesArray[0]->pt2;

	//if(abs(tmp_line.pt1._x - tmp_line.pt2._x) < MAP_SCALE)
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


void CMy3DSymbolLibNewView::OnUpdateMenuLineAdd(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_QueryType==LINE_ADD);
}


//�ռ����ͶӰ��ƽ���ֱ�߷���ϵ��ABC, Ax+By+C=0
void CMy3DSymbolLibNewView::getLine2ABC(double *A, double *B, double *C, Point3 p1, Point3 p2)
{
	// ֱ��AX+BY+C=0��һ��ʽ���̾��ǣ�
	//	A = Y2 - Y1
	//	B = X1 - X2
	//	C = X2*Y1 - X1*Y2

	*A = p2._z - p1._z;
	*B = p1._x - p2._x;
	*C = p2._x*p1._z - p1._x*p2._z;
}


// �����߶�_line�������ĺ�������������, ��������Χ
void CMy3DSymbolLibNewView::CalcuateGridNum(int *rowNum, int *row_index_begin, int *row_index_end, 
					 int *colNum, int *col_index_begin, int *col_index_end, Line3 _line)
{
	int tmp_rowNum = 0;
	int tmp_row_index_begin = 0;
	int tmp_row_index_end = 0;

	int tmp_colNum = 0;
	int tmp_col_index_begin = 0;
	int tmp_col_index_end = 0;


	double r1 = abs(_line.pt1._x);
	double c1 = abs(_line.pt1._z);


	double r2 = abs(_line.pt2._x);
	double c2 = abs(_line.pt2._z);


	tmp_row_index_begin =  (int)r1 / (int)MAP_SCALE;
	tmp_row_index_end = (int)r2 / (int)MAP_SCALE;


	tmp_col_index_begin = (int)c1 / (int)MAP_SCALE;
	tmp_col_index_end = (int)c2 / (int)MAP_SCALE;


	*rowNum = abs(tmp_row_index_end - tmp_row_index_begin);
	*row_index_begin = tmp_row_index_begin;
	*row_index_end = tmp_row_index_end;

	*colNum = abs(tmp_col_index_end - tmp_col_index_begin);
	*col_index_begin = tmp_col_index_begin;
	*col_index_end = tmp_col_index_end;

}


// sort(_pv.begin(),_pv.end(),comp);
bool comp(Point3 &p1, Point3 &p2)
{
	return p1._x < p2._x;
}

bool comp2(Point3 &p1, Point3 &p2)
{
	return p1._z < p2._z;
}


// ����ƽ�潻������,�������������ĸ߳�ֵ
void CMy3DSymbolLibNewView::CalcuateJD(int rowNum, int row_index_begin, int row_index_end, 
				int colNum, int col_index_begin, int col_index_end, Line3 _line, vector<Point3> &_pv)
{
	// ֱ�߷���ϵ��ABC, Ax+By+C=0
	double A, B, C;
	getLine2ABC(&A, &B, &C, _line.pt1, _line.pt2);
	
	Point3 tmp_point;

	JD_vector1.clear();
	JD_vector2.clear();
	JD_vector3.clear();
	_pv.clear();

	// ����1 ---------------------------------------------------------------------
	// ͨ������������ �����߶ν���
	if(row_index_begin < row_index_end)
	{
		for(int r=row_index_begin+1; r<row_index_end; ++r)
		{

			tmp_point._x = float(r)*MAP_SCALE;	// ƽ�������

			// ƽ��������
			if(DOUBLE_NUMBER_IS_ZERO(B))
			{
				
				break;
			}
			else
			{
				tmp_point._z = ((-A) * tmp_point._x -C) / B;
			}

			tmp_point._y = GetHeight(tmp_point._x, tmp_point._z);


			JD_vector1.push_back(tmp_point);
		}
	}
	else if(row_index_begin > row_index_end)
	{
		for(int r=row_index_begin-1; r>row_index_end; --r)
		{

			tmp_point._x = float(r)*MAP_SCALE;	// ƽ�������

			// ƽ��������
			if(DOUBLE_NUMBER_IS_ZERO(B))
			{

				break;
			}
			else
			{
				tmp_point._z = ((-A) * tmp_point._x -C) / B;
			}

			tmp_point._y = GetHeight(tmp_point._x, tmp_point._z);


			JD_vector1.push_back(tmp_point);
		}
		
	}
	

	// ����2 ---------------------------------------------------------------------
	if(col_index_begin < col_index_end)
	{
		// ͨ������������ �����߶ν���
		for(int c=col_index_begin+1; c<col_index_end; ++c)
		{
			tmp_point._z = float(-c)*MAP_SCALE;	// ƽ��������


			// ƽ�������
			if(DOUBLE_NUMBER_IS_ZERO(A))
			{
				break;
			}
			else
			{
				//Ax+By+C=0
				tmp_point._x =  ((-B) * tmp_point._z - C) / A;
			}

			tmp_point._y = GetHeight(tmp_point._x, tmp_point._z);



			JD_vector2.push_back(tmp_point);
		}
	}
	else if(col_index_begin > col_index_end)
	{
		// ͨ������������ �����߶ν���
		for(int c=col_index_begin-1; c>col_index_end; --c)
		{
			tmp_point._z = float(-c)*MAP_SCALE;	// ƽ��������


			// ƽ�������
			if(DOUBLE_NUMBER_IS_ZERO(A))
			{
				break;
			}
			else
			{
				//Ax+By+C=0
				tmp_point._x =  ((-B) * tmp_point._z -C) / A;
			}

			tmp_point._y = GetHeight(tmp_point._x, tmp_point._z);



			JD_vector2.push_back(tmp_point);
		}
	}

	// ����3 ---------------------------------------------------------------------
	 
	//double line_pos_b = MAP_SCALE * (row_index_begin < row_index_end ? row_index_begin : row_index_end);
	//double line_pos_e = MAP_SCALE * (row_index_begin > row_index_end ? row_index_begin : row_index_end);

	double line_pos_b =  (_line.pt1._x < _line.pt2._x) ? _line.pt1._x : _line.pt2._x;
	double line_pos_e =  (_line.pt1._x >= _line.pt2._x) ? _line.pt1._x : _line.pt2._x;;

	for(int r=0; r<MAP_W; ++r)
	{
		double b = float(-r)*MAP_SCALE;
		if(GetJDFrom2Line(&tmp_point, b, A, B, C))
		{
			if( (line_pos_b < tmp_point._x) && (tmp_point._x < line_pos_e) )
			{
				JD_vector3.push_back(tmp_point);
			}
		}
	}
	

	// 2�˵�
	_pv.push_back( _line.pt1);
	_pv.push_back( _line.pt2);

	//----------------------------------------------
	for(unsigned int i=0;i<JD_vector1.size();++i)
	{
		_pv.push_back(JD_vector1[i]);
	}
	for(unsigned int i=0;i<JD_vector2.size();++i)
	{
		_pv.push_back(JD_vector2[i]);
	}

	// б�߽���
	for(unsigned int i=0;i<JD_vector3.size();++i)
	{
		_pv.push_back(JD_vector3[i]);
	}

	sort(_pv.begin(),_pv.end(),comp);
}



// ����2��ֱ�ߵĽ���y=x+b, Ax+By+C=0, ����0��ʾ�޽���
BOOL CMy3DSymbolLibNewView::GetJDFrom2Line(PPoint3 p/*out*/,double b, double A, double B, double C)
{ 
	if(DOUBLE_NUMBER_IS_ZERO(A)) // A == 0
	{
		p->_z = -C/B;
		p->_x = p->_z - b;
		p->_y = GetHeight(p->_x, p->_z);
	}
	else
	{
		if(!(DOUBLE_NUMBER_IS_ZERO(B)))
		{ 
			if( DOUBLE_NUMBER_IS_ZERO(-A/B - 1) )
			{
				return 0; // 2ֱ��ƽ���޽���
			}
			else
			{
				p->_x = (-1)*(B*b+C)/(A+B);
				p->_z = p->_x + b;
				p->_y = GetHeight(p->_x, p->_z);
			}

		}
		else // B == 0
		{
			p->_x = -C/A;
			p->_z = p->_x + b;
			p->_y = GetHeight(p->_x, p->_z);
		}
	}
	

	return 1;
}



// ���������ζ���������С���ֵ
void CMy3DSymbolLibNewView::GetMinXY(vector<Point3> &_pv1,  vector<Point3> &_pv2, double *_minX, double *_minY, double *_maxX, double *_maxY)
{
	vector<Point3> tmpPV;
	unsigned int i = 0;
	for(i=0;i<_pv1.size();++i)
	{
		tmpPV.push_back(_pv1[i]);
	}
	for(i=0;i<_pv2.size();++i)
	{
		tmpPV.push_back(_pv2[i]);
	}
	sort(tmpPV.begin(), tmpPV.end(), comp);

	*_minX = abs(tmpPV[0]._x);
	*_maxX = abs(tmpPV[tmpPV.size()-1]._x);

	sort(tmpPV.begin(), tmpPV.end(), comp2);
	*_maxY = abs(tmpPV[0]._z);
	*_minY = abs(tmpPV[tmpPV.size()-1]._z);
}

// �߷�����������
void CMy3DSymbolLibNewView::GetUV(double _x, double _y, double _minX, double _minY, double _maxX, double _maxY, double *_u, double *_v)
{
	*_u = (abs(_x) - _minX) / (_maxX - _minX);
	*_v = (abs(_y) - _minY) / (_maxY - _minY);
}


// ���ƽ�������
void CMy3DSymbolLibNewView::DrawJDLine(vector<Point3> &_pv1, vector<Point3> &_pv2)
{
	 
	double DD = 1.0f;

	double tmpMinX = 0.0, tmpMinY = 0.0, tmpMaxX = 0.0, tmpMaxY = 0.0, tmpU = 0.0, tmpV = 0.0;
	GetMinXY(_pv1, _pv2, &tmpMinX, &tmpMinY, &tmpMaxX, &tmpMaxY);


	// ���õ���
	
	double tmpX = 0.0, tmpY = 0.0, tmpZ=0.0;
	// ������
	
	glEnable(GL_TEXTURE_2D);	// ��������
	//glBindTexture(GL_TEXTURE_2D, m_cTxtureRailway.GetTxtID());

	GLuint rd;
	char cc[256] = "E:/CG/My3DSymbolLibFiles/DataFormated/RoadTexture/��·/ww.bmp";
	LoadT8(cc,	rd);	

	glBindTexture(GL_TEXTURE_2D, rd);
	glTexEnvf    (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);


	if(fuse_Flag == TRUE) 
	{
		glPushAttrib(GL_CURRENT_BIT);// ����������ɫ����

		glPushMatrix();				// ѹ������ջ
		glLineWidth(2.0);			// �����߿�
		glColor3f(0,0.5,1);			// ������ɫ

		glBegin(GL_TRIANGLE_STRIP);

		for(unsigned int i = 0, j = 0, k = 0; i < _pv1.size(), j < _pv2.size(); ++i, ++j, ++k)
		{
			if(k % 2 == 0){
				tmpX = _pv1[i]._x; tmpY = _pv1[i]._y + DD; tmpZ = _pv1[i]._z;
			}
			else{
				tmpX = _pv2[j]._x; tmpY = _pv2[j]._y + DD; tmpZ = _pv2[j]._z;
			}
			
			tmpMinX = 0.0, tmpMinY = 0.0, tmpMaxX = 10.0, tmpMaxY = 10.0;

			GetUV(tmpX, tmpZ, tmpMinX, tmpMinY, tmpMaxX, tmpMaxY, &tmpU, &tmpV);

			glTexCoord2f(tmpU, tmpV);

			glVertex3f(tmpX, tmpY, tmpZ);
		}


		glEnd();

		glLineWidth(1.0);			// �ָ��߿�
		glPopAttrib();					

		glPopMatrix();				// ���������ջ
	}




	
}



// �����߷��ŵĿ����Ϣ
void CMy3DSymbolLibNewView::OnMenuAddLineWidth()
{
	// TODO: �ڴ���������������
	
}


/************************************************************************/
/*								�����									*/
/************************************************************************/


// ��������
void CMy3DSymbolLibNewView::OnMenuAddAreaSlib()
{
	// TODO: �ڴ���������������

	int newFlag = 0;

	if(!exist_area_file())
	{	
		INT_PTR nRes;
		nRes = MessageBox("û�д򿪵����ļ�����Ҫ�½��ļ���", "�Ҳ������ļ�", MB_YESNO | MB_ICONQUESTION);
		if(nRes == IDYES)
		{
			newFlag = new_area_file();
			if(0 == newFlag)
			{
				exist_area_flag = TRUE;
			}
		}	
	}
	else
	{
		if(m_QueryType == AREA_ADD)	 
			m_QueryType = -1;
		else							 
			m_QueryType = AREA_ADD;
	}
}

// �����������Ź�ѡ״̬
void CMy3DSymbolLibNewView::OnUpdateMenuAddAreaSlib(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_QueryType == AREA_ADD);
}


// �����ʸ����DEM�ں�
void CMy3DSymbolLibNewView::OnMenuAreaFuse()
{
	// TODO: �ڴ���������������
	
	int tmp_rowNum = 0;
	int tmp_row_index_begin = 0;
	int tmp_row_index_end = 0;

	int tmp_colNum = 0;
	int tmp_col_index_begin = 0; 
	int tmp_col_index_end = 0;

	
	Area_4 tmp_area4;

	if(m_Area4_Array.GetSize() <= 0)
	{
		return;
	}

	//Line3 tmp_line;
	//tmp_area4.pt1 = m_Area4_Array[0]->pt1;
	//tmp_area4.pt2 = m_Area4_Array[0]->pt2;
	//tmp_area4.pt3 = m_Area4_Array[0]->pt3;
	//tmp_area4.pt4 = m_Area4_Array[0]->pt4;
	////1 -------------------12-----------------------------------------------
	//tmp_line.pt1 = tmp_area4.pt1;
	//tmp_line.pt2 = tmp_area4.pt2;
	//
	//CalcuateGridNum(&tmp_rowNum, &tmp_row_index_begin, &tmp_row_index_end,
	//	&tmp_colNum, &tmp_col_index_begin, &tmp_col_index_end, tmp_line);
	//
	//CalcuateJD(tmp_rowNum, tmp_row_index_begin, tmp_row_index_end,
	//	tmp_colNum, tmp_col_index_begin, tmp_col_index_end, tmp_line, Line_1_JD_vector);
	////2 -----------------23-------------------------------------------------
	//tmp_line.pt1 = tmp_area4.pt2;
	//tmp_line.pt2 = tmp_area4.pt3;
	// 
	//CalcuateGridNum(&tmp_rowNum, &tmp_row_index_begin, &tmp_row_index_end,
	//	&tmp_colNum, &tmp_col_index_begin, &tmp_col_index_end, tmp_line);
	//
	//CalcuateJD(tmp_rowNum, tmp_row_index_begin, tmp_row_index_end,
	//	tmp_colNum, tmp_col_index_begin, tmp_col_index_end, tmp_line, Line_2_JD_vector);
	//
	//
	////3 -----------------34-------------------------------------------------
	//tmp_line.pt1 = tmp_area4.pt3;
	//tmp_line.pt2 = tmp_area4.pt4;
	//
	// 
	//CalcuateGridNum(&tmp_rowNum, &tmp_row_index_begin, &tmp_row_index_end,
	//	&tmp_colNum, &tmp_col_index_begin, &tmp_col_index_end, tmp_line);
	//
	//CalcuateJD(tmp_rowNum, tmp_row_index_begin, tmp_row_index_end,
	//	tmp_colNum, tmp_col_index_begin, tmp_col_index_end, tmp_line, Line_3_JD_vector);
	//
	//
	////4 -----------------41-------------------------------------------------
	//tmp_line.pt1 = tmp_area4.pt4;
	//tmp_line.pt2 = tmp_area4.pt1;
	//
	// 
	//CalcuateGridNum(&tmp_rowNum, &tmp_row_index_begin, &tmp_row_index_end,
	//	&tmp_colNum, &tmp_col_index_begin, &tmp_col_index_end, tmp_line);
	//
	//CalcuateJD(tmp_rowNum, tmp_row_index_begin, tmp_row_index_end,
	//	tmp_colNum, tmp_col_index_begin, tmp_col_index_end, tmp_line, Line_4_JD_vector);





	// =========================================================================================


	


	unsigned int tmp_size = m_Area4_Array.GetSize();
 
	for(unsigned int i=0; i<tmp_size; ++i)
	{
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

		// ���������
		//m_Area4_Array[i]->area_texture = area_texture;

	
		
		

		/*	if(i == 1)
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



		if(m_Area4_Array[i]->area_texture == "")
		{
			//AfxMessageBox("texture == NULL");
			m_Area4_Array[i]->area_texture = area_texture;
			LoadAreaTexture(area_texture, m_Area4_Array[i]->area_texture_rd);

		}
		else
		{
			LoadAreaTexture(m_Area4_Array[i]->area_texture, m_Area4_Array[i]->area_texture_rd);
		}

	}
	
	Area_fuse_Flag = TRUE;


}

// ��������ǻ�
void CMy3DSymbolLibNewView::Area_Triangled(PArea_4 &_area4)
{ 
	if(Area_fuse_Flag == TRUE && m_Drawmode == 3) 
	{
		glPushAttrib(GL_CURRENT_BIT);// ����������ɫ����

		glPushMatrix();				// ѹ������ջ
		glLineWidth(3.0);			// �����߿�
		glColor3f(0,0.5,1);			// ������ɫ
 
		{
			//static GLuint rd;
			//static char cc[256] = "";

			//CString scenePath = g_sceneDataPath.c_str();
			//CString area_texture = scenePath + "\\Terrain\\Tex\\area.bmp";

			//strcpy(cc, _area4->area_texture);

			//

			//strcpy(cc,  area_texture);
			////strcpy(cc, _area4->area_texture);

			//LoadT8(cc,	rd);	

			//glBindTexture(GL_TEXTURE_2D, rd);
			//glBindTexture(GL_TEXTURE_2D, m_area_texture);


			glBindTexture(GL_TEXTURE_2D, _area4->area_texture_rd);

			glTexEnvf    (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); 


			static const double deta = 1.00;

			// 1.�������ԭ��������������
			for(unsigned int i=0;i<_area4->TrianglesInPolygonVecotr.size();++i)
			{
				glColor3f( 1.0000 , 0.9804 , 0.9804); 
				glBegin(GL_TRIANGLES);
				{
					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt1._x, _area4->TrianglesInPolygonVecotr[i].pt1._y+deta, _area4->TrianglesInPolygonVecotr[i].pt1._z);					
					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt2._x, _area4->TrianglesInPolygonVecotr[i].pt2._y+deta, _area4->TrianglesInPolygonVecotr[i].pt2._z);
					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt3._x, _area4->TrianglesInPolygonVecotr[i].pt3._y+deta, _area4->TrianglesInPolygonVecotr[i].pt3._z);
				}
				glEnd();
			}


			// 2. �����ֲ����ǻ���������
			for(unsigned int i=0;i<_area4->LocalTrianglesVecotr1.size();++i)
			{
				glColor3f(0.0980 , 0.0980 , 0.4392); 
				glBegin(GL_TRIANGLES);
				{
					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(_area4->LocalTrianglesVecotr1[i].pt1._x, _area4->LocalTrianglesVecotr1[i].pt1._y+deta, _area4->LocalTrianglesVecotr1[i].pt1._z);					
					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(_area4->LocalTrianglesVecotr1[i].pt2._x, _area4->LocalTrianglesVecotr1[i].pt2._y+deta, _area4->LocalTrianglesVecotr1[i].pt2._z);
					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(_area4->LocalTrianglesVecotr1[i].pt3._x, _area4->LocalTrianglesVecotr1[i].pt3._y+deta, _area4->LocalTrianglesVecotr1[i].pt3._z);
				}
				glEnd();
			}

			for(unsigned int i=0;i<_area4->LocalTrianglesVecotr2.size();++i)
			{
				glColor3f(0.611, 0.400, 0.121); 
				glBegin(GL_TRIANGLES);
				{
					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(_area4->LocalTrianglesVecotr2[i].pt1._x, _area4->LocalTrianglesVecotr2[i].pt1._y+deta, _area4->LocalTrianglesVecotr2[i].pt1._z);					
					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(_area4->LocalTrianglesVecotr2[i].pt2._x, _area4->LocalTrianglesVecotr2[i].pt2._y+deta, _area4->LocalTrianglesVecotr2[i].pt2._z);
					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(_area4->LocalTrianglesVecotr2[i].pt3._x, _area4->LocalTrianglesVecotr2[i].pt3._y+deta, _area4->LocalTrianglesVecotr2[i].pt3._z);
				}
				glEnd();
			}


			// 2.1 ����� ���㴦
			for(unsigned int i=0;i<_area4->LocalTrianglesVecotr1_1.size();++i)
			{
				glColor3f( 1.0000 , 0.3882 , 0.2784); 
				glBegin(GL_TRIANGLES);
				{
					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt1._x, _area4->LocalTrianglesVecotr1_1[i].pt1._y+deta, _area4->LocalTrianglesVecotr1_1[i].pt1._z);					
					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt2._x, _area4->LocalTrianglesVecotr1_1[i].pt2._y+deta, _area4->LocalTrianglesVecotr1_1[i].pt2._z);
					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt3._x, _area4->LocalTrianglesVecotr1_1[i].pt3._y+deta, _area4->LocalTrianglesVecotr1_1[i].pt3._z);
				}
				glEnd();
			}

			for(unsigned int i=0;i<_area4->LocalTrianglesVecotr2_1.size();++i)
			{
				glColor3f(  0.6980 , 0.1333 , 0.1333); 
				glBegin(GL_TRIANGLES);
				{
					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt1._x, _area4->LocalTrianglesVecotr2_1[i].pt1._y+deta, _area4->LocalTrianglesVecotr2_1[i].pt1._z);					
					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt2._x, _area4->LocalTrianglesVecotr2_1[i].pt2._y+deta, _area4->LocalTrianglesVecotr2_1[i].pt2._z);
					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt3._x, _area4->LocalTrianglesVecotr2_1[i].pt3._y+deta, _area4->LocalTrianglesVecotr2_1[i].pt3._z);
				}
				glEnd();
			}


			for(unsigned int i=0;i<_area4->LocalTrianglesVecotr_last.size();++i)
			{
				glColor3f( 0.6275,  0.1255,  0.9412); 
				glBegin(GL_TRIANGLES);
				{
					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt1._x, _area4->LocalTrianglesVecotr_last[i].pt1._y+deta, _area4->LocalTrianglesVecotr_last[i].pt1._z);					
					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt2._x, _area4->LocalTrianglesVecotr_last[i].pt2._y+deta, _area4->LocalTrianglesVecotr_last[i].pt2._z);
					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt3._x, _area4->LocalTrianglesVecotr_last[i].pt3._y+deta, _area4->LocalTrianglesVecotr_last[i].pt3._z);
				}
				glEnd();
			}
		}

		glLineWidth(1.0);			// �ָ��߿�
		glPopAttrib();					

		glPopMatrix();				// ���������ջ
	}

	//...............................................................
	
	if(Area_fuse_Flag == TRUE && m_Drawmode == 1) 
	{
		glPushAttrib(GL_CURRENT_BIT);// ����������ɫ����

		glPushMatrix();				// ѹ������ջ
		glLineWidth(3.0);			// �����߿�
		glColor3f(0,0.5,1);			// ������ɫ

		//test begin
		{
			/*unsigned int i = 0;
			

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
		//test end


		{
 
			// 1.�������ԭ��������������
			for(unsigned int i=0;i<_area4->TrianglesInPolygonVecotr.size();++i)
			{
				glColor3f( 1.0000 , 0.9804 , 0.9804); 
				glBegin(GL_TRIANGLES);
				{
					 
					glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt1._x, _area4->TrianglesInPolygonVecotr[i].pt1._y , _area4->TrianglesInPolygonVecotr[i].pt1._z);					
					 
					glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt2._x, _area4->TrianglesInPolygonVecotr[i].pt2._y , _area4->TrianglesInPolygonVecotr[i].pt2._z);
					 
					glVertex3f(_area4->TrianglesInPolygonVecotr[i].pt3._x, _area4->TrianglesInPolygonVecotr[i].pt3._y , _area4->TrianglesInPolygonVecotr[i].pt3._z);
				}
				glEnd();
			}


			// 2. �����ֲ����ǻ���������
			for(unsigned int i=0;i<_area4->LocalTrianglesVecotr1.size();++i)
			{
				glColor3f(1.0,1.0,0.1); 
				glBegin(GL_TRIANGLES);
				{

					glVertex3f(_area4->LocalTrianglesVecotr1[i].pt1._x, _area4->LocalTrianglesVecotr1[i].pt1._y , _area4->LocalTrianglesVecotr1[i].pt1._z);					

					glVertex3f(_area4->LocalTrianglesVecotr1[i].pt2._x, _area4->LocalTrianglesVecotr1[i].pt2._y , _area4->LocalTrianglesVecotr1[i].pt2._z);

					glVertex3f(_area4->LocalTrianglesVecotr1[i].pt3._x, _area4->LocalTrianglesVecotr1[i].pt3._y , _area4->LocalTrianglesVecotr1[i].pt3._z);
				}
				glEnd();
			}

			for(unsigned int i=0;i<_area4->LocalTrianglesVecotr2.size();++i)
			{
				glColor3f(0.611, 0.400, 0.121); 
				glBegin(GL_TRIANGLES);
				{

					glVertex3f(_area4->LocalTrianglesVecotr2[i].pt1._x, _area4->LocalTrianglesVecotr2[i].pt1._y , _area4->LocalTrianglesVecotr2[i].pt1._z);					

					glVertex3f(_area4->LocalTrianglesVecotr2[i].pt2._x, _area4->LocalTrianglesVecotr2[i].pt2._y , _area4->LocalTrianglesVecotr2[i].pt2._z);

					glVertex3f(_area4->LocalTrianglesVecotr2[i].pt3._x, _area4->LocalTrianglesVecotr2[i].pt3._y , _area4->LocalTrianglesVecotr2[i].pt3._z);
				}
				glEnd();
			}


			// 2.1 ����� ���㴦
			for(unsigned int i=0;i<_area4->LocalTrianglesVecotr1_1.size();++i)
			{
				glColor3f( 1.0000 , 0.3882 , 0.2784); 
				glBegin(GL_TRIANGLES);
				{

					glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt1._x, _area4->LocalTrianglesVecotr1_1[i].pt1._y , _area4->LocalTrianglesVecotr1_1[i].pt1._z);					

					glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt2._x, _area4->LocalTrianglesVecotr1_1[i].pt2._y , _area4->LocalTrianglesVecotr1_1[i].pt2._z);

					glVertex3f(_area4->LocalTrianglesVecotr1_1[i].pt3._x, _area4->LocalTrianglesVecotr1_1[i].pt3._y , _area4->LocalTrianglesVecotr1_1[i].pt3._z);
				}
				glEnd();
			}

			for(unsigned int i=0;i<_area4->LocalTrianglesVecotr2_1.size();++i)
			{
				glColor3f(  0.6980 , 0.1333 , 0.1333); 
				glBegin(GL_TRIANGLES);
				{

					glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt1._x, _area4->LocalTrianglesVecotr2_1[i].pt1._y, _area4->LocalTrianglesVecotr2_1[i].pt1._z);					

					glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt2._x, _area4->LocalTrianglesVecotr2_1[i].pt2._y, _area4->LocalTrianglesVecotr2_1[i].pt2._z);

					glVertex3f(_area4->LocalTrianglesVecotr2_1[i].pt3._x, _area4->LocalTrianglesVecotr2_1[i].pt3._y, _area4->LocalTrianglesVecotr2_1[i].pt3._z);
				}
				glEnd();
			}


			for(unsigned int i=0;i<_area4->LocalTrianglesVecotr_last.size();++i)
			{
				glColor3f( 0.6275,  0.1255,  0.9412); 
				glBegin(GL_TRIANGLES);
				{

					glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt1._x, _area4->LocalTrianglesVecotr_last[i].pt1._y, _area4->LocalTrianglesVecotr_last[i].pt1._z);					

					glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt2._x, _area4->LocalTrianglesVecotr_last[i].pt2._y, _area4->LocalTrianglesVecotr_last[i].pt2._z);

					glVertex3f(_area4->LocalTrianglesVecotr_last[i].pt3._x, _area4->LocalTrianglesVecotr_last[i].pt3._y, _area4->LocalTrianglesVecotr_last[i].pt3._z);
				}
				glEnd();
			}
 
		}

		glLineWidth(1.0);			// �ָ��߿�
		glPopAttrib();					

		glPopMatrix();				// ���������ջ
	}

}



void CMy3DSymbolLibNewView::LoadAreaTexture(CString _areaTexture_str, UINT &texture_id)// �������������
{
	 
	char cc[256] = "";

	strcpy(cc,  _areaTexture_str);
	 

	LoadT8(cc,	texture_id);	

}

// ��������а����ڶ�����ڵĵ�
int CMy3DSymbolLibNewView::FindAllPointsInPolygon(Area_4 &m_area4)
{
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

	
	int Vertex = 0;
	for (int z = 0; z < MAP_W; z++)
	{
		for (int x = 0; x < MAP_W; x++)		
		{
			Vertex = z * MAP_W + x;

			tmp_dem_point.x = g_terrain [Vertex][0];
			tmp_dem_point.y = g_terrain [Vertex][2];


			int inPolygonFlag = tmp_ppr.InPolygon(tmp_polygon, tmp_dem_point);

			if(inPolygonFlag == 0) // ���ڶ������
			{
				Point3 tmp_point3;
				tmp_point3._x = g_terrain [Vertex][0];
				tmp_point3._y = g_terrain [Vertex][1];
				tmp_point3._z = g_terrain [Vertex][2];
				pointsInPolygonVector.push_back(tmp_point3);

				inPolygonArrayFlag[x][z] = 1;
			}
			else
			{
				inPolygonArrayFlag[x][z] = 0;
			}


		}
	}


	return 0;
}


// �ҳ����а����ڶ�����ڵ�������(�������������κ;����ֲ����ǻ���������)
int CMy3DSymbolLibNewView::FindAllTrianglesInPolygon(Area_4 &m_area4)
{
	FindAllPointsInPolygon(m_area4);


	// 1.�������������������
	m_area4.TrianglesInPolygonVecotr.clear();
	FindTriangles_3_point_inPolygon(m_area4);


	// 2.�����ֲ����ǻ���������
	m_area4.LocalTrianglesVecotr1.clear();
	FindTriangles_1_point_inPolygon(m_area4);

	m_area4.LocalTrianglesVecotr2.clear();
	FindTriangles_2_point_inPolygon(m_area4);




	// 2.1 ����ζ��㴦

	m_area4.LocalTrianglesVecotr1_1.clear();
	m_area4.LocalTrianglesVecotr2_1.clear();
	m_area4.LocalTrianglesVecotr_last.clear();



	FindTriangles_polygon_has_vertex_in_triangle(m_area4);


	return 0;
}



// ��3�����ڶ�������ڵ�������
int CMy3DSymbolLibNewView::FindTriangles_3_point_inPolygon(Area_4 &_area4)
{
	int Vertex = 0;
	for (int z = 0; z < MAP_W-1; z++)
	{
		for (int x = 0; x < MAP_W-1; x++)					
		{
			Vertex = z * MAP_W + x;
			Triangle tmp_triangle;
			// 3���㶼�ڶ������
			if(inPolygonArrayFlag[x][z]==1 && inPolygonArrayFlag[x][z+1]==1  && inPolygonArrayFlag[x+1][z]==1)
			{
				Vertex = z * MAP_W + x;

				tmp_triangle.pt1._x = g_terrain [Vertex][0];
				tmp_triangle.pt1._y = g_terrain [Vertex][1];
				tmp_triangle.pt1._z = g_terrain [Vertex][2];

				Vertex = (z+1) * MAP_W + x;
				tmp_triangle.pt2._x = g_terrain [Vertex][0];
				tmp_triangle.pt2._y = g_terrain [Vertex][1];
				tmp_triangle.pt2._z = g_terrain [Vertex][2];


				Vertex = z * MAP_W + (x+1);
				tmp_triangle.pt3._x = g_terrain [Vertex][0];
				tmp_triangle.pt3._y = g_terrain [Vertex][1];
				tmp_triangle.pt3._z = g_terrain [Vertex][2];

				_area4.TrianglesInPolygonVecotr.push_back(tmp_triangle); 
			}
			// 3���㶼�ڶ������
			if(inPolygonArrayFlag[x+1][z]==1 && inPolygonArrayFlag[x+1][z+1]==1  && inPolygonArrayFlag[x][z+1]==1)
			{
				Vertex = z * MAP_W + (x+1);
				tmp_triangle.pt1._x = g_terrain [Vertex][0];
				tmp_triangle.pt1._y = g_terrain [Vertex][1];
				tmp_triangle.pt1._z = g_terrain [Vertex][2];


				Vertex = (z+1) * MAP_W + (x+1);
				tmp_triangle.pt2._x = g_terrain [Vertex][0];
				tmp_triangle.pt2._y = g_terrain [Vertex][1];
				tmp_triangle.pt2._z = g_terrain [Vertex][2];


				Vertex = (z+1) * MAP_W + x;
				tmp_triangle.pt3._x = g_terrain [Vertex][0];
				tmp_triangle.pt3._y = g_terrain [Vertex][1];
				tmp_triangle.pt3._z = g_terrain [Vertex][2];

				_area4.TrianglesInPolygonVecotr.push_back(tmp_triangle); 
			}

		}
	}
	return 0;
}


// ֻ��1�����ڶ�������ڵ�������(���������ǻ�)
int CMy3DSymbolLibNewView::FindTriangles_1_point_inPolygon(Area_4 &m_area4)
{
	{
		int Vertex;
		for (int z = 0; z < MAP_W-1; z++)
		{
			for (int x = 0; x < MAP_W-1; x++)						
			{
				Vertex = z * MAP_W + x;
				Triangle tmp_triangle;

				// ������ֻ��1�����ڶ������
				if(inPolygonArrayFlag[x][z]==1 && inPolygonArrayFlag[x][z+1]==0  && inPolygonArrayFlag[x+1][z]==0)
				{
					Vertex = (z) * MAP_W + (x);
					tmp_triangle.pt1._x = g_terrain [Vertex][0];
					tmp_triangle.pt1._y = g_terrain [Vertex][1];
					tmp_triangle.pt1._z = g_terrain [Vertex][2];

					// �����α߽��������αߵĽ���
					CPointPolygonRelationship tmp_PPR;
					PPR_Point tmp_point1, tmp_point21, tmp_point22; // ����������
					
					tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

					Vertex = (z+1) * MAP_W + (x);
					tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

					Vertex = (z) * MAP_W + (x+1);
					tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];

					Find_triangles_1_line_2_JD(m_area4, tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);
				}


				if(inPolygonArrayFlag[x][z]==0 && inPolygonArrayFlag[x][z+1]==1  && inPolygonArrayFlag[x+1][z]==0)
				{
					Vertex = (z+1) * MAP_W + (x);
					tmp_triangle.pt1._x = g_terrain [Vertex][0];
					tmp_triangle.pt1._y = g_terrain [Vertex][1];
					tmp_triangle.pt1._z = g_terrain [Vertex][2];

					// �����α߽��������αߵĽ���
					CPointPolygonRelationship tmp_PPR;
					PPR_Point tmp_point1, tmp_point21, tmp_point22; // ����������


					tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

					Vertex = (z) * MAP_W + (x);
					tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

					Vertex = (z) * MAP_W + (x+1);
					tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];

					Find_triangles_1_line_2_JD(m_area4, tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);

				}


				// ������ֻ��1�����ڶ������
				if(inPolygonArrayFlag[x][z]==0 && inPolygonArrayFlag[x][z+1]==0  && inPolygonArrayFlag[x+1][z]==1)
				{
					Vertex = (z) * MAP_W + (x+1);
					tmp_triangle.pt1._x = g_terrain [Vertex][0];
					tmp_triangle.pt1._y = g_terrain [Vertex][1];
					tmp_triangle.pt1._z = g_terrain [Vertex][2];

					// �����α߽��������αߵĽ���
					CPointPolygonRelationship tmp_PPR;
					PPR_Point tmp_point1, tmp_point21, tmp_point22; // ����������

					tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

					Vertex = (z+1) * MAP_W + (x);
					tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

					Vertex = (z) * MAP_W + (x);
					tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];


					Find_triangles_1_line_2_JD(m_area4, tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);

				}

				
				// ==========================================================================================


				// ������ֻ��1�����ڶ������
				if(inPolygonArrayFlag[x+1][z+1]==1 && inPolygonArrayFlag[x][z+1]==0  && inPolygonArrayFlag[x+1][z]==0)
				{
					Vertex = (z+1) * MAP_W + (x+1);
					tmp_triangle.pt1._x = g_terrain [Vertex][0];
					tmp_triangle.pt1._y = g_terrain [Vertex][1];
					tmp_triangle.pt1._z = g_terrain [Vertex][2];

					// �����α߽��������αߵĽ���
					CPointPolygonRelationship tmp_PPR;
					PPR_Point tmp_point1, tmp_point21, tmp_point22; // ����������


					tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

					Vertex = (z+1) * MAP_W + (x);
					tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

					Vertex = (z) * MAP_W + (x+1);
					tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];

					Find_triangles_1_line_2_JD(m_area4, tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);
				}


				if(inPolygonArrayFlag[x+1][z+1]==0 && inPolygonArrayFlag[x][z+1]==1  && inPolygonArrayFlag[x+1][z]==0)
				{
					Vertex = (z+1) * MAP_W + (x);
					tmp_triangle.pt1._x = g_terrain [Vertex][0];
					tmp_triangle.pt1._y = g_terrain [Vertex][1];
					tmp_triangle.pt1._z = g_terrain [Vertex][2];

					// �����α߽��������αߵĽ���
					CPointPolygonRelationship tmp_PPR;
					PPR_Point tmp_point1, tmp_point21, tmp_point22; // ����������

					tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

					Vertex = (z+1) * MAP_W + (x+1);
					tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

					Vertex = (z) * MAP_W + (x+1);
					tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];

					Find_triangles_1_line_2_JD(m_area4, tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);
				}


				// ������ֻ��1�����ڶ������
				if(inPolygonArrayFlag[x+1][z+1]==0 && inPolygonArrayFlag[x][z+1]==0  && inPolygonArrayFlag[x+1][z]==1)
				{
					Vertex = (z) * MAP_W + (x+1);
					tmp_triangle.pt1._x = g_terrain [Vertex][0];
					tmp_triangle.pt1._y = g_terrain [Vertex][1];
					tmp_triangle.pt1._z = g_terrain [Vertex][2];

					// �����α߽��������αߵĽ���
					CPointPolygonRelationship tmp_PPR;
					PPR_Point tmp_point1, tmp_point21, tmp_point22; // ����������

					tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

					Vertex = (z+1) * MAP_W + (x);
					tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

					Vertex = (z+1) * MAP_W + (x+1);
					tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];

					
					Find_triangles_1_line_2_JD(m_area4, tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);

				}
			}
		}
	}

	return 0;
}


// ֻ��2�����ڶ�������ڵ�������(���������ǻ�)
int CMy3DSymbolLibNewView::FindTriangles_2_point_inPolygon(Area_4 &m_area4)
{
	{
		int Vertex;
		for (int z = 0; z < MAP_W-1; z++)
		{
			for (int x = 0; x < MAP_W-1; x++)						
			{
				Vertex = z * MAP_W + x;
				Triangle tmp_triangle1;
				Triangle tmp_triangle2;

				//ok1

				if(inPolygonArrayFlag[x][z]==1 && inPolygonArrayFlag[x][z+1]==1  && inPolygonArrayFlag[x+1][z]==0)
				{
					Vertex = (z) * MAP_W + (x);
					tmp_triangle1.pt1._x = g_terrain [Vertex][0];
					tmp_triangle1.pt1._y = g_terrain [Vertex][1];
					tmp_triangle1.pt1._z = g_terrain [Vertex][2];

					tmp_triangle2.pt1._x = g_terrain [Vertex][0];
					tmp_triangle2.pt1._y = g_terrain [Vertex][1];
					tmp_triangle2.pt1._z = g_terrain [Vertex][2];



					Vertex = (z+1) * MAP_W + (x);
					tmp_triangle1.pt2._x = g_terrain [Vertex][0];
					tmp_triangle1.pt2._y = g_terrain [Vertex][1];
					tmp_triangle1.pt2._z = g_terrain [Vertex][2];



					// �����α߽��������αߵĽ���
					CPointPolygonRelationship tmp_PPR;
					PPR_Point tmp_point1, tmp_point21, tmp_point22; // ����������


					Vertex = (z) * MAP_W + (x+1);
					tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

					Vertex = (z+1) * MAP_W + (x);
					tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

					Vertex = (z) * MAP_W + (x);
					tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];

					

					//Find_triangles_1_line_2_JD(tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);

					PPR_Point tmp_point3, tmp_point4; // ����αߵĶ˵�

					PPR_Point JD1, JD2;

					//CString msg;
					bool intersectFlag1 = false;  bool intersectFlag2 = false;

					short tmp_cout = 4;
					while(tmp_cout > 0)
					{
						if(4 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt1._x;	tmp_point3.y = m_area4.pt1._z;
							tmp_point4.x = m_area4.pt2._x;	tmp_point4.y = m_area4.pt2._z;
						}else if(3 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt2._x;  tmp_point3.y = m_area4.pt2._z;
							tmp_point4.x = m_area4.pt3._x;  tmp_point4.y = m_area4.pt3._z;
						}else if(2 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt3._x;  tmp_point3.y = m_area4.pt3._z;
							tmp_point4.x = m_area4.pt4._x;  tmp_point4.y = m_area4.pt4._z;
						}else if(1 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt4._x;  tmp_point3.y = m_area4.pt4._z;
							tmp_point4.x = m_area4.pt1._x;  tmp_point4.y = m_area4.pt1._z;
						}

						intersectFlag1 = tmp_PPR.Meet(tmp_point1,tmp_point21, tmp_point3, tmp_point4);
						intersectFlag2 = tmp_PPR.Meet(tmp_point1,tmp_point22, tmp_point3, tmp_point4);


						if(intersectFlag1 && intersectFlag2)
						{
							JD1 = tmp_PPR.getJD(tmp_point1,tmp_point21, tmp_point3, tmp_point4);

							JD2 = tmp_PPR.getJD(tmp_point1,tmp_point22, tmp_point3, tmp_point4);


							double tmp_min_y = (tmp_triangle1.pt1._z < tmp_triangle1.pt2._z) ? tmp_triangle1.pt1._z : tmp_triangle1.pt2._z;
							double tmp_max_y = (tmp_triangle1.pt1._z > tmp_triangle1.pt2._z) ? tmp_triangle1.pt1._z : tmp_triangle1.pt2._z;

							double tmp_min_x = (tmp_triangle1.pt1._x < tmp_point1.x) ? tmp_triangle1.pt1._z : tmp_point1.x;
							double tmp_max_x = (tmp_triangle1.pt1._x > tmp_point1.x) ? tmp_triangle1.pt1._z : tmp_point1.x;

							bool b11 = (JD1.y > (tmp_min_y + 0.01)) && (JD1.y < (tmp_max_y - 0.01));
							bool b21 = (JD2.y > (tmp_min_y + 0.01)) && (JD2.y < (tmp_max_y - 0.01));


							bool b12 = (JD1.x > (tmp_min_x + 0.01)) && (JD1.x < (tmp_max_x - 0.01));
							bool b22 = (JD2.x > (tmp_min_x + 0.01)) && (JD2.x < (tmp_max_x - 0.01));


							if(b11 && b12)
							{
								tmp_triangle1.pt3._x = JD1.x; tmp_triangle1.pt3._y = GetHeight(JD1.x, JD1.y); tmp_triangle1.pt3._z = JD1.y;
							}
							else if(b21 && b22)
							{
								tmp_triangle1.pt3._x = JD2.x; tmp_triangle1.pt3._y = GetHeight(JD2.x, JD2.y); tmp_triangle1.pt3._z = JD2.y;
							}
							else
							{
								AfxMessageBox("warning: ");
								
							}


							tmp_triangle2.pt2._x = JD1.x; tmp_triangle2.pt2._y = GetHeight(JD1.x, JD1.y); tmp_triangle2.pt2._z = JD1.y;
							tmp_triangle2.pt3._x = JD2.x; tmp_triangle2.pt3._y = GetHeight(JD2.x, JD2.y); tmp_triangle2.pt3._z = JD2.y;
							//AfxMessageBox("1");

							m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle1);
							m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle2);
							

						}
						tmp_cout--;
					}
					
				}



				//ok2

				if(inPolygonArrayFlag[x][z]==1 && inPolygonArrayFlag[x][z+1]==0  && inPolygonArrayFlag[x+1][z]==1)
				{
					
					Vertex = (z) * MAP_W + (x);
					tmp_triangle1.pt1._x = g_terrain [Vertex][0];
					tmp_triangle1.pt1._y = g_terrain [Vertex][1];
					tmp_triangle1.pt1._z = g_terrain [Vertex][2];

					tmp_triangle2.pt1._x = g_terrain [Vertex][0];
					tmp_triangle2.pt1._y = g_terrain [Vertex][1];
					tmp_triangle2.pt1._z = g_terrain [Vertex][2];



					Vertex = (z) * MAP_W + (x+1);
					tmp_triangle1.pt2._x = g_terrain [Vertex][0];
					tmp_triangle1.pt2._y = g_terrain [Vertex][1];
					tmp_triangle1.pt2._z = g_terrain [Vertex][2];



					// �����α߽��������αߵĽ���
					CPointPolygonRelationship tmp_PPR;
					PPR_Point tmp_point1, tmp_point21, tmp_point22; // ����������

					

					Vertex = (z+1) * MAP_W + (x);
					tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

					Vertex = (z) * MAP_W + (x+1);
					tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

					Vertex = (z) * MAP_W + (x);
					tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];

					

					//Find_triangles_1_line_2_JD(tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);

					PPR_Point tmp_point3, tmp_point4; // ����αߵĶ˵�

					PPR_Point JD1, JD2;

					CString msg;
					bool intersectFlag1 = false;  bool intersectFlag2 = false;

					int tmp_cout = 4;
					while(tmp_cout > 0)
					{
						if(4 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt1._x;	tmp_point3.y = m_area4.pt1._z;
							tmp_point4.x = m_area4.pt2._x;	tmp_point4.y = m_area4.pt2._z;
						}else if(3 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt2._x;  tmp_point3.y = m_area4.pt2._z;
							tmp_point4.x = m_area4.pt3._x;  tmp_point4.y = m_area4.pt3._z;
						}else if(2 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt3._x;  tmp_point3.y = m_area4.pt3._z;
							tmp_point4.x = m_area4.pt4._x;  tmp_point4.y = m_area4.pt4._z;
						}else if(1 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt4._x;  tmp_point3.y = m_area4.pt4._z;
							tmp_point4.x = m_area4.pt1._x;  tmp_point4.y = m_area4.pt1._z;
						}

						intersectFlag1 = tmp_PPR.Meet(tmp_point1,tmp_point21, tmp_point3, tmp_point4);
						intersectFlag2 = tmp_PPR.Meet(tmp_point1,tmp_point22, tmp_point3, tmp_point4);


						if(intersectFlag1 && intersectFlag2)
						{
							JD1 = tmp_PPR.getJD(tmp_point1,tmp_point21, tmp_point3, tmp_point4);

							JD2 = tmp_PPR.getJD(tmp_point1,tmp_point22, tmp_point3, tmp_point4);


							double tmp_min_y = (tmp_triangle1.pt1._z < tmp_point1.y) ? tmp_triangle1.pt1._z : tmp_point1.y;
							double tmp_max_y = (tmp_triangle1.pt1._z > tmp_point1.y) ? tmp_triangle1.pt1._z : tmp_point1.y;

							double tmp_min_x = (tmp_triangle1.pt1._x < tmp_triangle1.pt2._x) ? tmp_triangle1.pt1._x : tmp_triangle1.pt2._x;
							double tmp_max_x = (tmp_triangle1.pt1._x > tmp_triangle1.pt2._x) ? tmp_triangle1.pt1._x : tmp_triangle1.pt2._x;

							bool b11 = (JD1.y > (tmp_min_y + 0.01)) && (JD1.y < (tmp_max_y - 0.01));
							bool b21 = (JD2.y > (tmp_min_y + 0.01)) && (JD2.y < (tmp_max_y - 0.01));


							bool b12 = (JD1.x > (tmp_min_x + 0.01)) && (JD1.x < (tmp_max_x - 0.01));
							bool b22 = (JD2.x > (tmp_min_x + 0.01)) && (JD2.x < (tmp_max_x - 0.01));


							if(b11 && b12)
							{
								tmp_triangle1.pt3._x = JD1.x; tmp_triangle1.pt3._y = GetHeight(JD1.x, JD1.y); tmp_triangle1.pt3._z = JD1.y;
							}
							else if(b21 && b22)
							{
								tmp_triangle1.pt3._x = JD2.x; tmp_triangle1.pt3._y = GetHeight(JD2.x, JD2.y); tmp_triangle1.pt3._z = JD2.y;
							}
							else
							{
								AfxMessageBox("warning: ");
								//AfxMessageBox(__LINE__);
							}


							tmp_triangle2.pt2._x = JD1.x; tmp_triangle2.pt2._y = GetHeight(JD1.x, JD1.y); tmp_triangle2.pt2._z = JD1.y;
							tmp_triangle2.pt3._x = JD2.x; tmp_triangle2.pt3._y = GetHeight(JD2.x, JD2.y); tmp_triangle2.pt3._z = JD2.y;
							//AfxMessageBox("2");

							m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle1);
							m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle2);
							

						}
						tmp_cout--;
					}
					
				}

				//ok3

				if(inPolygonArrayFlag[x][z]==0 && inPolygonArrayFlag[x][z+1]==1  && inPolygonArrayFlag[x+1][z]==1)
				{
					Vertex = (z) * MAP_W + (x+1);
					tmp_triangle1.pt1._x = g_terrain [Vertex][0];
					tmp_triangle1.pt1._y = g_terrain [Vertex][1];
					tmp_triangle1.pt1._z = g_terrain [Vertex][2];

		
					Vertex = (z+1) * MAP_W + (x);
					tmp_triangle1.pt2._x = g_terrain [Vertex][0];
					tmp_triangle1.pt2._y = g_terrain [Vertex][1];
					tmp_triangle1.pt2._z = g_terrain [Vertex][2];


					tmp_triangle2.pt1._x = g_terrain [Vertex][0];
					tmp_triangle2.pt1._y = g_terrain [Vertex][1];
					tmp_triangle2.pt1._z = g_terrain [Vertex][2];


					// �����α߽��������αߵĽ���
					CPointPolygonRelationship tmp_PPR;
					PPR_Point tmp_point1, tmp_point21, tmp_point22; // ����������

					

					Vertex = (z) * MAP_W + (x);
					tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

					Vertex = (z+1) * MAP_W + (x);
					tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

					Vertex = (z) * MAP_W + (x+1);
					tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];

					

					//Find_triangles_1_line_2_JD(tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);

					PPR_Point tmp_point3, tmp_point4; // ����αߵĶ˵�

					PPR_Point JD1, JD2;

					CString msg;
					bool intersectFlag1 = false;  bool intersectFlag2 = false;

					int tmp_cout = 4;
					while(tmp_cout > 0)
					{
						if(4 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt1._x;	tmp_point3.y = m_area4.pt1._z;
							tmp_point4.x = m_area4.pt2._x;	tmp_point4.y = m_area4.pt2._z;
						}else if(3 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt2._x;  tmp_point3.y = m_area4.pt2._z;
							tmp_point4.x = m_area4.pt3._x;  tmp_point4.y = m_area4.pt3._z;
						}else if(2 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt3._x;  tmp_point3.y = m_area4.pt3._z;
							tmp_point4.x = m_area4.pt4._x;  tmp_point4.y = m_area4.pt4._z;
						}else if(1 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt4._x;  tmp_point3.y = m_area4.pt4._z;
							tmp_point4.x = m_area4.pt1._x;  tmp_point4.y = m_area4.pt1._z;
						}

						intersectFlag1 = tmp_PPR.Meet(tmp_point1,tmp_point21, tmp_point3, tmp_point4);
						intersectFlag2 = tmp_PPR.Meet(tmp_point1,tmp_point22, tmp_point3, tmp_point4);


						if(intersectFlag1 && intersectFlag2)
						{
							JD1 = tmp_PPR.getJD(tmp_point1,tmp_point21, tmp_point3, tmp_point4);

							JD2 = tmp_PPR.getJD(tmp_point1,tmp_point22, tmp_point3, tmp_point4);


							
							double len1 = (tmp_triangle1.pt1._x - JD1.x)*(tmp_triangle1.pt1._x - JD1.x) + (tmp_triangle1.pt1._z - JD1.y)*(tmp_triangle1.pt1._z - JD1.y);
							double len2 = (tmp_triangle1.pt1._x - JD2.x)*(tmp_triangle1.pt1._x - JD2.x) + (tmp_triangle1.pt1._z - JD2.y)*(tmp_triangle1.pt1._z - JD2.y);


							if(len1 < len2)
							{
								tmp_triangle1.pt3._x = JD1.x; tmp_triangle1.pt3._y = GetHeight(JD1.x, JD1.y); tmp_triangle1.pt3._z = JD1.y;
							}
							else if(len1 > len2)
							{
								tmp_triangle1.pt3._x = JD2.x; tmp_triangle1.pt3._y = GetHeight(JD2.x, JD2.y); tmp_triangle1.pt3._z = JD2.y;
							}
							else
							{
								AfxMessageBox("warning");
							}


							tmp_triangle2.pt2._x = JD1.x; tmp_triangle2.pt2._y = GetHeight(JD1.x, JD1.y); tmp_triangle2.pt2._z = JD1.y;
							tmp_triangle2.pt3._x = JD2.x; tmp_triangle2.pt3._y = GetHeight(JD2.x, JD2.y); tmp_triangle2.pt3._z = JD2.y;

							//AfxMessageBox("3");
							m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle1);
							m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle2);
							

						}
						tmp_cout--;
					}
					
				}



				// ========================================================================================

				 
				//ok - 1

				if(inPolygonArrayFlag[x+1][z+1]==1 && inPolygonArrayFlag[x][z+1]==1  && inPolygonArrayFlag[x+1][z]==0)
				{
					 
					Vertex = (z+1) * MAP_W + (x+1);
					tmp_triangle1.pt1._x = g_terrain [Vertex][0];
					tmp_triangle1.pt1._y = g_terrain [Vertex][1];
					tmp_triangle1.pt1._z = g_terrain [Vertex][2];

					tmp_triangle2.pt1._x = g_terrain [Vertex][0];
					tmp_triangle2.pt1._y = g_terrain [Vertex][1];
					tmp_triangle2.pt1._z = g_terrain [Vertex][2];



					Vertex = (z+1) * MAP_W + (x);
					tmp_triangle1.pt2._x = g_terrain [Vertex][0];
					tmp_triangle1.pt2._y = g_terrain [Vertex][1];
					tmp_triangle1.pt2._z = g_terrain [Vertex][2];



					// �����α߽��������αߵĽ���
					CPointPolygonRelationship tmp_PPR;
					PPR_Point tmp_point1, tmp_point21, tmp_point22; // ����������
 

					Vertex = (z) * MAP_W + (x+1);
					tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

					Vertex = (z+1) * MAP_W + (x);
					tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

					Vertex = (z+1) * MAP_W + (x+1);
					tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];

					

					//Find_triangles_1_line_2_JD(tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);

					PPR_Point tmp_point3, tmp_point4; // ����αߵĶ˵�

					PPR_Point JD1, JD2;

					CString msg;
					bool intersectFlag1 = false;  bool intersectFlag2 = false;

					int tmp_cout = 4;
					while(tmp_cout > 0)
					{
						if(4 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt1._x;	tmp_point3.y = m_area4.pt1._z;
							tmp_point4.x = m_area4.pt2._x;	tmp_point4.y = m_area4.pt2._z;
						}else if(3 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt2._x;  tmp_point3.y = m_area4.pt2._z;
							tmp_point4.x = m_area4.pt3._x;  tmp_point4.y = m_area4.pt3._z;
						}else if(2 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt3._x;  tmp_point3.y = m_area4.pt3._z;
							tmp_point4.x = m_area4.pt4._x;  tmp_point4.y = m_area4.pt4._z;
						}else if(1 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt4._x;  tmp_point3.y = m_area4.pt4._z;
							tmp_point4.x = m_area4.pt1._x;  tmp_point4.y = m_area4.pt1._z;
						}

						intersectFlag1 = tmp_PPR.Meet(tmp_point1,tmp_point21, tmp_point3, tmp_point4);
						intersectFlag2 = tmp_PPR.Meet(tmp_point1,tmp_point22, tmp_point3, tmp_point4);


						if(intersectFlag1 && intersectFlag2)
						{
							JD1 = tmp_PPR.getJD(tmp_point1,tmp_point21, tmp_point3, tmp_point4);

							JD2 = tmp_PPR.getJD(tmp_point1,tmp_point22, tmp_point3, tmp_point4);


							double tmp_min_x = (tmp_triangle1.pt1._x < tmp_triangle1.pt2._x) ? tmp_triangle1.pt1._x : tmp_triangle1.pt2._x;
							double tmp_max_x = (tmp_triangle1.pt1._x > tmp_triangle1.pt2._x) ? tmp_triangle1.pt1._x : tmp_triangle1.pt2._x;

							double tmp_min_y = (tmp_triangle1.pt1._z < tmp_point1.y) ? tmp_triangle1.pt1._z : tmp_point1.y;
							double tmp_max_y = (tmp_triangle1.pt1._z > tmp_point1.y) ? tmp_triangle1.pt1._z : tmp_point1.y;

							bool b11 = (JD1.y > (tmp_min_y + 0.01)) && (JD1.y < (tmp_max_y - 0.01));
							bool b21 = (JD2.y > (tmp_min_y + 0.01)) && (JD2.y < (tmp_max_y - 0.01));


							bool b12 = (JD1.x > (tmp_min_x + 0.01)) && (JD1.x < (tmp_max_x - 0.01));
							bool b22 = (JD2.x > (tmp_min_x + 0.01)) && (JD2.x < (tmp_max_x - 0.01));


							if(b11 && b12)
							{
								tmp_triangle1.pt3._x = JD1.x; tmp_triangle1.pt3._y = GetHeight(JD1.x, JD1.y); tmp_triangle1.pt3._z = JD1.y;
							}
							else if(b21 && b22)
							{
								tmp_triangle1.pt3._x = JD2.x; tmp_triangle1.pt3._y = GetHeight(JD2.x, JD2.y); tmp_triangle1.pt3._z = JD2.y;
							}
							else
							{
								AfxMessageBox("warning... ");
								//AfxMessageBox(__LINE__);
							}


							tmp_triangle2.pt2._x = JD1.x; tmp_triangle2.pt2._y = GetHeight(JD1.x, JD1.y); tmp_triangle2.pt2._z = JD1.y;
							tmp_triangle2.pt3._x = JD2.x; tmp_triangle2.pt3._y = GetHeight(JD2.x, JD2.y); tmp_triangle2.pt3._z = JD2.y;
						//	AfxMessageBox(" - 1");

							m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle1);
							m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle2);
							

						}
						tmp_cout--;
					}
					
				}



				//ok - 2

				if(inPolygonArrayFlag[x+1][z+1]==1 && inPolygonArrayFlag[x][z+1]==0  && inPolygonArrayFlag[x+1][z]==1)
				{
					 
					Vertex = (z+1) * MAP_W + (x+1);
					tmp_triangle1.pt1._x = g_terrain [Vertex][0];
					tmp_triangle1.pt1._y = g_terrain [Vertex][1];
					tmp_triangle1.pt1._z = g_terrain [Vertex][2];

					tmp_triangle2.pt1._x = g_terrain [Vertex][0];
					tmp_triangle2.pt1._y = g_terrain [Vertex][1];
					tmp_triangle2.pt1._z = g_terrain [Vertex][2];



					Vertex = (z) * MAP_W + (x+1);
					tmp_triangle1.pt2._x = g_terrain [Vertex][0];
					tmp_triangle1.pt2._y = g_terrain [Vertex][1];
					tmp_triangle1.pt2._z = g_terrain [Vertex][2];



					// �����α߽��������αߵĽ���
					CPointPolygonRelationship tmp_PPR;
					PPR_Point tmp_point1, tmp_point21, tmp_point22; // ����������

					 

					Vertex = (z+1) * MAP_W + (x);
					tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

					Vertex = (z) * MAP_W + (x+1);
					tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

					Vertex = (z+1) * MAP_W + (x+1);
					tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];

					

					//Find_triangles_1_line_2_JD(tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);

					PPR_Point tmp_point3, tmp_point4; // ����αߵĶ˵�

					PPR_Point JD1, JD2;

					CString msg;
					bool intersectFlag1 = false;  bool intersectFlag2 = false;

					int tmp_cout = 4;
					while(tmp_cout > 0)
					{
						if(4 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt1._x;	tmp_point3.y = m_area4.pt1._z;
							tmp_point4.x = m_area4.pt2._x;	tmp_point4.y = m_area4.pt2._z;
						}else if(3 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt2._x;  tmp_point3.y = m_area4.pt2._z;
							tmp_point4.x = m_area4.pt3._x;  tmp_point4.y = m_area4.pt3._z;
						}else if(2 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt3._x;  tmp_point3.y = m_area4.pt3._z;
							tmp_point4.x = m_area4.pt4._x;  tmp_point4.y = m_area4.pt4._z;
						}else if(1 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt4._x;  tmp_point3.y = m_area4.pt4._z;
							tmp_point4.x = m_area4.pt1._x;  tmp_point4.y = m_area4.pt1._z;
						}

						intersectFlag1 = tmp_PPR.Meet(tmp_point1,tmp_point21, tmp_point3, tmp_point4);
						intersectFlag2 = tmp_PPR.Meet(tmp_point1,tmp_point22, tmp_point3, tmp_point4);


						if(intersectFlag1 && intersectFlag2)
						{
							JD1 = tmp_PPR.getJD(tmp_point1,tmp_point21, tmp_point3, tmp_point4);

							JD2 = tmp_PPR.getJD(tmp_point1,tmp_point22, tmp_point3, tmp_point4);


							double tmp_min_x = (tmp_triangle1.pt1._x < tmp_point1.x) ? tmp_triangle1.pt1._x : tmp_point1.x;
							double tmp_max_x = (tmp_triangle1.pt1._x > tmp_point1.x) ? tmp_triangle1.pt1._x : tmp_point1.x;

							double tmp_min_y = (tmp_triangle1.pt1._z < tmp_triangle1.pt2._z) ? tmp_triangle1.pt1._z : tmp_triangle1.pt2._z;
							double tmp_max_y = (tmp_triangle1.pt1._z > tmp_triangle1.pt2._z) ? tmp_triangle1.pt1._z : tmp_triangle1.pt2._z;

							bool b11 = (JD1.y > (tmp_min_y + 0.01)) && (JD1.y < (tmp_max_y - 0.01));
							bool b21 = (JD2.y > (tmp_min_y + 0.01)) && (JD2.y < (tmp_max_y - 0.01));


							bool b12 = (JD1.x > (tmp_min_x + 0.01)) && (JD1.x < (tmp_max_x - 0.01));
							bool b22 = (JD2.x > (tmp_min_x + 0.01)) && (JD2.x < (tmp_max_x - 0.01));


							if(b11 && b12)
							{
								tmp_triangle1.pt3._x = JD1.x; tmp_triangle1.pt3._y = GetHeight(JD1.x, JD1.y); tmp_triangle1.pt3._z = JD1.y;
							}
							else if(b21 && b22)
							{
								tmp_triangle1.pt3._x = JD2.x; tmp_triangle1.pt3._y = GetHeight(JD2.x, JD2.y); tmp_triangle1.pt3._z = JD2.y;
							}
							else
							{
								AfxMessageBox("warning... ");
								//AfxMessageBox(__LINE__);
							}


							tmp_triangle2.pt2._x = JD1.x; tmp_triangle2.pt2._y = GetHeight(JD1.x, JD1.y); tmp_triangle2.pt2._z = JD1.y;
							tmp_triangle2.pt3._x = JD2.x; tmp_triangle2.pt3._y = GetHeight(JD2.x, JD2.y); tmp_triangle2.pt3._z = JD2.y;
							//AfxMessageBox(" - 2");

							m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle1);
							m_area4.LocalTrianglesVecotr2.push_back(tmp_triangle2);
							

						}
						tmp_cout--;
					}
					
				}

				//ok - 3

				if(inPolygonArrayFlag[x+1][z+1]==0 && inPolygonArrayFlag[x][z+1]==1  && inPolygonArrayFlag[x+1][z]==1)
				{
					Vertex = (z) * MAP_W + (x+1);
					tmp_triangle1.pt1._x = g_terrain [Vertex][0];
					tmp_triangle1.pt1._y = g_terrain [Vertex][1];
					tmp_triangle1.pt1._z = g_terrain [Vertex][2];


					Vertex = (z+1) * MAP_W + (x);
					tmp_triangle1.pt2._x = g_terrain [Vertex][0];
					tmp_triangle1.pt2._y = g_terrain [Vertex][1];
					tmp_triangle1.pt2._z = g_terrain [Vertex][2];


					tmp_triangle2.pt1._x = g_terrain [Vertex][0];
					tmp_triangle2.pt1._y = g_terrain [Vertex][1];
					tmp_triangle2.pt1._z = g_terrain [Vertex][2];


					// �����α߽��������αߵĽ���
					CPointPolygonRelationship tmp_PPR;
					PPR_Point tmp_point1, tmp_point21, tmp_point22; // ����������

					

					Vertex = (z+1) * MAP_W + (x+1);
					tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

					Vertex = (z+1) * MAP_W + (x);
					tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

					Vertex = (z) * MAP_W + (x+1);
					tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];

					

					//Find_triangles_1_line_2_JD(tmp_triangle, tmp_PPR, tmp_point1, tmp_point21, tmp_point22);

					PPR_Point tmp_point3, tmp_point4; // ����αߵĶ˵�

					PPR_Point JD1, JD2;

					CString msg;
					bool intersectFlag1 = false;  bool intersectFlag2 = false;

					int tmp_cout = 4;
					while(tmp_cout > 0)
					{
						if(4 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt1._x;	tmp_point3.y = m_area4.pt1._z;
							tmp_point4.x = m_area4.pt2._x;	tmp_point4.y = m_area4.pt2._z;
						}else if(3 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt2._x;  tmp_point3.y = m_area4.pt2._z;
							tmp_point4.x = m_area4.pt3._x;  tmp_point4.y = m_area4.pt3._z;
						}else if(2 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt3._x;  tmp_point3.y = m_area4.pt3._z;
							tmp_point4.x = m_area4.pt4._x;  tmp_point4.y = m_area4.pt4._z;
						}else if(1 == tmp_cout)
						{
							tmp_point3.x = m_area4.pt4._x;  tmp_point3.y = m_area4.pt4._z;
							tmp_point4.x = m_area4.pt1._x;  tmp_point4.y = m_area4.pt1._z;
						}

						intersectFlag1 = tmp_PPR.Meet(tmp_point1,tmp_point21, tmp_point3, tmp_point4);
						intersectFlag2 = tmp_PPR.Meet(tmp_point1,tmp_point22, tmp_point3, tmp_point4);


						if(intersectFlag1 && intersectFlag2)
						{
							JD1 = tmp_PPR.getJD(tmp_point1,tmp_point21, tmp_point3, tmp_point4);

							JD2 = tmp_PPR.getJD(tmp_point1,tmp_point22, tmp_point3, tmp_point4);


							
							double len1 = (tmp_triangle1.pt1._x - JD1.x)*(tmp_triangle1.pt1._x - JD1.x) + (tmp_triangle1.pt1._z - JD1.y)*(tmp_triangle1.pt1._z - JD1.y);
							double len2 = (tmp_triangle1.pt1._x - JD2.x)*(tmp_triangle1.pt1._x - JD2.x) + (tmp_triangle1.pt1._z - JD2.y)*(tmp_triangle1.pt1._z - JD2.y);


							if(len1 < len2)
							{
								tmp_triangle1.pt3._x = JD1.x; tmp_triangle1.pt3._y = GetHeight(JD1.x, JD1.y); tmp_triangle1.pt3._z = JD1.y;
							}
							else if(len1 > len2)
							{
								tmp_triangle1.pt3._x = JD2.x; tmp_triangle1.pt3._y = GetHeight(JD2.x, JD2.y); tmp_triangle1.pt3._z = JD2.y;
							}
							else
							{
								AfxMessageBox("...warning!");
							}


							tmp_triangle2.pt2._x = JD1.x; tmp_triangle2.pt2._y = GetHeight(JD1.x, JD1.y); tmp_triangle2.pt2._z = JD1.y;
							tmp_triangle2.pt3._x = JD2.x; tmp_triangle2.pt3._y = GetHeight(JD2.x, JD2.y); tmp_triangle2.pt3._z = JD2.y;

							//AfxMessageBox(" - 3");
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



//�ҳ�����������������(������ֻ��1�����ڶ������, �Ҷ���ε�ĳ��������������2������)
void CMy3DSymbolLibNewView::Find_triangles_1_line_2_JD(Area_4 &m_area4, Triangle &tmp_triangle, CPointPolygonRelationship &tmp_PPR, const PPR_Point &tmp_point1, const PPR_Point &tmp_point21, const PPR_Point &tmp_point22)
{
 

	PPR_Point tmp_point3, tmp_point4; // ����αߵĶ˵�

	PPR_Point JD1, JD2;

	//CString msg;
	bool intersectFlag1 = false;  bool intersectFlag2 = false;

	short tmp_cout = 4;
	while(tmp_cout > 0)
	{
		if(4 == tmp_cout)
		{
			tmp_point3.x = m_area4.pt1._x;	tmp_point3.y = m_area4.pt1._z;
			tmp_point4.x = m_area4.pt2._x;	tmp_point4.y = m_area4.pt2._z;
		}else if(3 == tmp_cout)
		{
			tmp_point3.x = m_area4.pt2._x;  tmp_point3.y = m_area4.pt2._z;
			tmp_point4.x = m_area4.pt3._x;  tmp_point4.y = m_area4.pt3._z;
		}else if(2 == tmp_cout)
		{
			tmp_point3.x = m_area4.pt3._x;  tmp_point3.y = m_area4.pt3._z;
			tmp_point4.x = m_area4.pt4._x;  tmp_point4.y = m_area4.pt4._z;
		}else if(1 == tmp_cout)
		{
			tmp_point3.x = m_area4.pt4._x;  tmp_point3.y = m_area4.pt4._z;
			tmp_point4.x = m_area4.pt1._x;  tmp_point4.y = m_area4.pt1._z;
		}

		intersectFlag1 = tmp_PPR.Meet(tmp_point1,tmp_point21, tmp_point3, tmp_point4);
		intersectFlag2 = tmp_PPR.Meet(tmp_point1,tmp_point22, tmp_point3, tmp_point4);


		if(intersectFlag1 && intersectFlag2)
		{
			JD1 = tmp_PPR.getJD(tmp_point1,tmp_point21, tmp_point3, tmp_point4);

			JD2 = tmp_PPR.getJD(tmp_point1,tmp_point22, tmp_point3, tmp_point4);

			tmp_triangle.pt2._x = JD1.x; tmp_triangle.pt2._y = GetHeight(JD1.x, JD1.y); tmp_triangle.pt2._z = JD1.y;
			tmp_triangle.pt3._x = JD2.x; tmp_triangle.pt3._y = GetHeight(JD2.x, JD2.y); tmp_triangle.pt3._z = JD2.y;
			m_area4.LocalTrianglesVecotr1.push_back(tmp_triangle);

			
		}
		tmp_cout--;
	}
}



// ����ζ��㴦��������
void CMy3DSymbolLibNewView::FindTriangles_polygon_has_vertex_in_triangle(Area_4 &m_area4)
{
	int Vertex;
	for (int z = 0; z < MAP_W-1; z++)
	{
		for (int x = 0; x < MAP_W-1; x++)		
		{
			Vertex = z * MAP_W + x;

			Triangle tmp_triangle1;
			Triangle tmp_triangle2;


			PPR_Point tmp_point1, tmp_point21, tmp_point22; // ����������

			/************************************************************************/
			/*       ������ֻ��1�����ڶ������											*/
			/************************************************************************/

			// ------------------------------------

			if(inPolygonArrayFlag[x][z]==0 && inPolygonArrayFlag[x][z+1]==0  && inPolygonArrayFlag[x+1][z]==1)
			{				
				Vertex = (z) * MAP_W + (x+1);
				tmp_triangle1.pt1._x = g_terrain [Vertex][0];
				tmp_triangle1.pt1._y = g_terrain [Vertex][1];
				tmp_triangle1.pt1._z = g_terrain [Vertex][2];

				tmp_triangle2.pt1._x = g_terrain [Vertex][0];
				tmp_triangle2.pt1._y = g_terrain [Vertex][1];
				tmp_triangle2.pt1._z = g_terrain [Vertex][2];
				 
				

				Vertex = (z) * MAP_W + (x+1);
				tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

				Vertex = (z+1) * MAP_W + (x);
				tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

				Vertex = (z) * MAP_W + (x);
				tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];

				FindTriangles_polygon_has_vertex_in_triangle_1_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_point1, tmp_point21, tmp_point22);
			}

			// ������ֻ��1�����ڶ������
			if(inPolygonArrayFlag[x][z]==0 && inPolygonArrayFlag[x][z+1]==1  && inPolygonArrayFlag[x+1][z]==0)
			{
				Vertex = (z+1) * MAP_W + (x);
				tmp_triangle1.pt1._x = g_terrain [Vertex][0];
				tmp_triangle1.pt1._y = g_terrain [Vertex][1];
				tmp_triangle1.pt1._z = g_terrain [Vertex][2];

				tmp_triangle2.pt1._x = g_terrain [Vertex][0];
				tmp_triangle2.pt1._y = g_terrain [Vertex][1];
				tmp_triangle2.pt1._z = g_terrain [Vertex][2];


				Vertex = (z+1) * MAP_W + (x);
				tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

				Vertex = (z) * MAP_W + (x+1);
				tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

				Vertex = (z) * MAP_W + (x);
				tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];


				FindTriangles_polygon_has_vertex_in_triangle_1_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_point1, tmp_point21, tmp_point22);

			}


			// ������ֻ��1�����ڶ������
			if(inPolygonArrayFlag[x][z]==1 && inPolygonArrayFlag[x][z+1]==0  && inPolygonArrayFlag[x+1][z]==0)
			{
				Vertex = (z) * MAP_W + (x);
				tmp_triangle1.pt1._x = g_terrain [Vertex][0];
				tmp_triangle1.pt1._y = g_terrain [Vertex][1];
				tmp_triangle1.pt1._z = g_terrain [Vertex][2];

				tmp_triangle2.pt1._x = g_terrain [Vertex][0];
				tmp_triangle2.pt1._y = g_terrain [Vertex][1];
				tmp_triangle2.pt1._z = g_terrain [Vertex][2];

				// �����α߽��������αߵĽ���
				 

				Vertex = (z) * MAP_W + (x);
				tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

				Vertex = (z) * MAP_W + (x+1);
				tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

				Vertex = (z+1) * MAP_W + (x);
				tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];

				FindTriangles_polygon_has_vertex_in_triangle_1_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_point1, tmp_point21, tmp_point22);
			}




			// ------------------------------------

			// ������ֻ��1�����ڶ������
			if(inPolygonArrayFlag[x+1][z+1]==0 && inPolygonArrayFlag[x][z+1]==0  && inPolygonArrayFlag[x+1][z]==1)
			{				
				Vertex = (z) * MAP_W + (x+1);
				tmp_triangle1.pt1._x = g_terrain [Vertex][0];
				tmp_triangle1.pt1._y = g_terrain [Vertex][1];
				tmp_triangle1.pt1._z = g_terrain [Vertex][2];

				tmp_triangle2.pt1._x = g_terrain [Vertex][0];
				tmp_triangle2.pt1._y = g_terrain [Vertex][1];
				tmp_triangle2.pt1._z = g_terrain [Vertex][2];


				Vertex = (z) * MAP_W + (x+1);
				tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

				Vertex = (z+1) * MAP_W + (x);
				tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

				Vertex = (z+1) * MAP_W + (x+1);
				tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];

				FindTriangles_polygon_has_vertex_in_triangle_1_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_point1, tmp_point21, tmp_point22);
			}

			// ������ֻ��1�����ڶ������
			if(inPolygonArrayFlag[x+1][z+1]==0 && inPolygonArrayFlag[x][z+1]==1  && inPolygonArrayFlag[x+1][z]==0)
			{
				Vertex = (z+1) * MAP_W + (x);
				tmp_triangle1.pt1._x = g_terrain [Vertex][0];
				tmp_triangle1.pt1._y = g_terrain [Vertex][1];
				tmp_triangle1.pt1._z = g_terrain [Vertex][2];

				tmp_triangle2.pt1._x = g_terrain [Vertex][0];
				tmp_triangle2.pt1._y = g_terrain [Vertex][1];
				tmp_triangle2.pt1._z = g_terrain [Vertex][2];


				Vertex = (z+1) * MAP_W + (x);
				tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

				Vertex = (z) * MAP_W + (x+1);
				tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

				Vertex = (z+1) * MAP_W + (x+1);
				tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];


				FindTriangles_polygon_has_vertex_in_triangle_1_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_point1, tmp_point21, tmp_point22);

			}


			// ������ֻ��1�����ڶ������
			if(inPolygonArrayFlag[x+1][z+1]==1 && inPolygonArrayFlag[x][z+1]==0  && inPolygonArrayFlag[x+1][z]==0)
			{
				Vertex = (z+1) * MAP_W + (x+1);
				tmp_triangle1.pt1._x = g_terrain [Vertex][0];
				tmp_triangle1.pt1._y = g_terrain [Vertex][1];
				tmp_triangle1.pt1._z = g_terrain [Vertex][2];

				tmp_triangle2.pt1._x = g_terrain [Vertex][0];
				tmp_triangle2.pt1._y = g_terrain [Vertex][1];
				tmp_triangle2.pt1._z = g_terrain [Vertex][2];

				// �����α߽��������αߵĽ���


				Vertex = (z+1) * MAP_W + (x+1);
				tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

				Vertex = (z) * MAP_W + (x+1);
				tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

				Vertex = (z+1) * MAP_W + (x);
				tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];

				FindTriangles_polygon_has_vertex_in_triangle_1_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_point1, tmp_point21, tmp_point22);
			}
		




			/************************************************************************/
			/*       ������ֻ��2�����ڶ������											*/
			/************************************************************************/

			// ���ǻ��������3��С������

			Triangle tmp_triangle3;

			// ------------------------------------

			//1-1
			if(inPolygonArrayFlag[x][z]==1 && inPolygonArrayFlag[x][z+1]==1  && inPolygonArrayFlag[x+1][z]==0)
			{				
				Vertex = (z+1) * MAP_W + (x);
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


				// ��ʱ tmp_point1ӦΪ�ڶ�������һ��
				Vertex = (z) * MAP_W + (x+1);
				tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

				Vertex = (z+1) * MAP_W + (x);
				tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

				Vertex = (z) * MAP_W + (x);
				tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];

				FindTriangles_polygon_has_vertex_in_triangle_2_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_point1, tmp_point21, tmp_point22);
			}

			//1-2
			if(inPolygonArrayFlag[x][z]==1 && inPolygonArrayFlag[x][z+1]==0  && inPolygonArrayFlag[x+1][z]==1)
			{				
				Vertex = (z) * MAP_W + (x+1);
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


				// ��ʱ tmp_point1ӦΪ�ڶ�������һ��
				Vertex = (z+1) * MAP_W + (x);
				tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

				Vertex = (z) * MAP_W + (x+1);
				tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

				Vertex = (z) * MAP_W + (x);
				tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];

				FindTriangles_polygon_has_vertex_in_triangle_2_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_point1, tmp_point21, tmp_point22);
			}


			//1-3
			if(inPolygonArrayFlag[x][z]==0 && inPolygonArrayFlag[x][z+1]==1  && inPolygonArrayFlag[x+1][z]==1)
			{				
				Vertex = (z) * MAP_W + (x+1);
				tmp_triangle1.pt1._x = g_terrain [Vertex][0];
				tmp_triangle1.pt1._y = g_terrain [Vertex][1];
				tmp_triangle1.pt1._z = g_terrain [Vertex][2];

				tmp_triangle3.pt1._x = g_terrain [Vertex][0];
				tmp_triangle3.pt1._y = g_terrain [Vertex][1];
				tmp_triangle3.pt1._z = g_terrain [Vertex][2];



				Vertex = (z+1) * MAP_W + (x);
				tmp_triangle2.pt1._x = g_terrain [Vertex][0];
				tmp_triangle2.pt1._y = g_terrain [Vertex][1];
				tmp_triangle2.pt1._z = g_terrain [Vertex][2];

				tmp_triangle3.pt2._x = g_terrain [Vertex][0];
				tmp_triangle3.pt2._y = g_terrain [Vertex][1];
				tmp_triangle3.pt2._z = g_terrain [Vertex][2];


				// ��ʱ tmp_point1ӦΪ�ڶ�������һ��
				Vertex = (z) * MAP_W + (x);
				tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

				Vertex = (z) * MAP_W + (x+1);
				tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

				Vertex = (z+1) * MAP_W + (x);
				tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];

				FindTriangles_polygon_has_vertex_in_triangle_2_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_point1, tmp_point21, tmp_point22);
			}



			//2-1
			if(inPolygonArrayFlag[x+1][z+1]==1 && inPolygonArrayFlag[x][z+1]==1  && inPolygonArrayFlag[x+1][z]==0)
			{				
				Vertex = (z+1) * MAP_W + (x);
				tmp_triangle1.pt1._x = g_terrain [Vertex][0];
				tmp_triangle1.pt1._y = g_terrain [Vertex][1];
				tmp_triangle1.pt1._z = g_terrain [Vertex][2];

				tmp_triangle3.pt1._x = g_terrain [Vertex][0];
				tmp_triangle3.pt1._y = g_terrain [Vertex][1];
				tmp_triangle3.pt1._z = g_terrain [Vertex][2];



				Vertex = (z+1) * MAP_W + (x+1);
				tmp_triangle2.pt1._x = g_terrain [Vertex][0];
				tmp_triangle2.pt1._y = g_terrain [Vertex][1];
				tmp_triangle2.pt1._z = g_terrain [Vertex][2];

				tmp_triangle3.pt2._x = g_terrain [Vertex][0];
				tmp_triangle3.pt2._y = g_terrain [Vertex][1];
				tmp_triangle3.pt2._z = g_terrain [Vertex][2];


				// ��ʱ tmp_point1ӦΪ�ڶ�������һ��
				Vertex = (z) * MAP_W + (x+1);
				tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

				Vertex = (z+1) * MAP_W + (x);
				tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

				Vertex = (z+1) * MAP_W + (x+1);
				tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];

				FindTriangles_polygon_has_vertex_in_triangle_2_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_point1, tmp_point21, tmp_point22);
			}

			//2-2
			if(inPolygonArrayFlag[x+1][z+1]==1 && inPolygonArrayFlag[x][z+1]==0  && inPolygonArrayFlag[x+1][z]==1)
			{				
				Vertex = (z) * MAP_W + (x+1);
				tmp_triangle1.pt1._x = g_terrain [Vertex][0];
				tmp_triangle1.pt1._y = g_terrain [Vertex][1];
				tmp_triangle1.pt1._z = g_terrain [Vertex][2];

				tmp_triangle3.pt1._x = g_terrain [Vertex][0];
				tmp_triangle3.pt1._y = g_terrain [Vertex][1];
				tmp_triangle3.pt1._z = g_terrain [Vertex][2];



				Vertex = (z+1) * MAP_W + (x+1);
				tmp_triangle2.pt1._x = g_terrain [Vertex][0];
				tmp_triangle2.pt1._y = g_terrain [Vertex][1];
				tmp_triangle2.pt1._z = g_terrain [Vertex][2];

				tmp_triangle3.pt2._x = g_terrain [Vertex][0];
				tmp_triangle3.pt2._y = g_terrain [Vertex][1];
				tmp_triangle3.pt2._z = g_terrain [Vertex][2];


				// ��ʱ tmp_point1ӦΪ�ڶ�������һ��
				Vertex = (z+1) * MAP_W + (x);
				tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

				Vertex = (z) * MAP_W + (x+1);
				tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

				Vertex = (z+1) * MAP_W + (x+1);
				tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];

				FindTriangles_polygon_has_vertex_in_triangle_2_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_point1, tmp_point21, tmp_point22);
			}


			//2-3
			if(inPolygonArrayFlag[x+1][z+1]==0 && inPolygonArrayFlag[x][z+1]==1  && inPolygonArrayFlag[x+1][z]==1)
			{				
				Vertex = (z) * MAP_W + (x+1);
				tmp_triangle1.pt1._x = g_terrain [Vertex][0];
				tmp_triangle1.pt1._y = g_terrain [Vertex][1];
				tmp_triangle1.pt1._z = g_terrain [Vertex][2];

				tmp_triangle3.pt1._x = g_terrain [Vertex][0];
				tmp_triangle3.pt1._y = g_terrain [Vertex][1];
				tmp_triangle3.pt1._z = g_terrain [Vertex][2];



				Vertex = (z+1) * MAP_W + (x);
				tmp_triangle2.pt1._x = g_terrain [Vertex][0];
				tmp_triangle2.pt1._y = g_terrain [Vertex][1];
				tmp_triangle2.pt1._z = g_terrain [Vertex][2];

				tmp_triangle3.pt2._x = g_terrain [Vertex][0];
				tmp_triangle3.pt2._y = g_terrain [Vertex][1];
				tmp_triangle3.pt2._z = g_terrain [Vertex][2];


				// ��ʱ tmp_point1ӦΪ�ڶ�������һ��
				Vertex = (z+1) * MAP_W + (x+1);
				tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

				Vertex = (z) * MAP_W + (x+1);
				tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

				Vertex = (z+1) * MAP_W + (x);
				tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];

				FindTriangles_polygon_has_vertex_in_triangle_2_1(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3, tmp_point1, tmp_point21, tmp_point22);
			}







			/************************************************************************/
			/* ����ε�1��������ĳ���������У����������ε�3�����㶼�ڶ������				*/
			/************************************************************************/

			// ��ʱ���ǻ��󽫲���4��������
			Triangle tmp_triangle4;
			//1- 1
			if(inPolygonArrayFlag[x][z]==1 && inPolygonArrayFlag[x][z+1]==0  && inPolygonArrayFlag[x+1][z]==0)
			{		

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


 
				// �����ι�б�ߵĶԽ�������
				PPR_Point tmp_point0;
				Vertex = (z+1) * MAP_W + (x+1);
				tmp_point0.x = g_terrain [Vertex][0];   tmp_point0.y = g_terrain [Vertex][2];

				 
				Vertex = (z) * MAP_W + (x);
				tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

				Vertex = (z) * MAP_W + (x+1);
				tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

				Vertex = (z+1) * MAP_W + (x);
				tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];


				
				FindTriangles_polygon_has_vertex_in_triangle_last(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3,tmp_triangle4, tmp_point0, tmp_point1, tmp_point21, tmp_point22);

			}
			//1-2
			if(inPolygonArrayFlag[x][z]==0 && inPolygonArrayFlag[x][z+1]==1  && inPolygonArrayFlag[x+1][z]==0)
			{		

				Vertex = (z+1) * MAP_W + (x);
				tmp_triangle1.pt1._x = g_terrain [Vertex][0];
				tmp_triangle1.pt1._y = g_terrain [Vertex][1];
				tmp_triangle1.pt1._z = g_terrain [Vertex][2];

				tmp_triangle2.pt1._x = g_terrain [Vertex][0];
				tmp_triangle2.pt1._y = g_terrain [Vertex][1];
				tmp_triangle2.pt1._z = g_terrain [Vertex][2];

				tmp_triangle3.pt1._x = g_terrain [Vertex][0];
				tmp_triangle3.pt1._y = g_terrain [Vertex][1];
				tmp_triangle3.pt1._z = g_terrain [Vertex][2];



				// �Խ�������
				if(z >= 1)
				{
					PPR_Point tmp_point0;
					Vertex = (z-1) * MAP_W + (x+1);
					tmp_point0.x = g_terrain [Vertex][0];   tmp_point0.y = g_terrain [Vertex][2];


					Vertex = (z+1) * MAP_W + (x);
					tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

					Vertex = (z) * MAP_W + (x+1);
					tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

					Vertex = (z) * MAP_W + (x);
					tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];



					FindTriangles_polygon_has_vertex_in_triangle_last(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3,tmp_triangle4, tmp_point0, tmp_point1, tmp_point21, tmp_point22);

				}
				
			}

			//1-3
			if(inPolygonArrayFlag[x][z]==0 && inPolygonArrayFlag[x][z+1]==0  && inPolygonArrayFlag[x+1][z]==1)
			{		

				Vertex = (z) * MAP_W + (x+1);
				tmp_triangle1.pt1._x = g_terrain [Vertex][0];
				tmp_triangle1.pt1._y = g_terrain [Vertex][1];
				tmp_triangle1.pt1._z = g_terrain [Vertex][2];

				tmp_triangle2.pt1._x = g_terrain [Vertex][0];
				tmp_triangle2.pt1._y = g_terrain [Vertex][1];
				tmp_triangle2.pt1._z = g_terrain [Vertex][2];

				tmp_triangle3.pt1._x = g_terrain [Vertex][0];
				tmp_triangle3.pt1._y = g_terrain [Vertex][1];
				tmp_triangle3.pt1._z = g_terrain [Vertex][2];



				// �Խ�������
				if(x >= 1)
				{
					PPR_Point tmp_point0;
					Vertex = (z+1) * MAP_W + (x-1);
					tmp_point0.x = g_terrain [Vertex][0];   tmp_point0.y = g_terrain [Vertex][2];


					Vertex = (z) * MAP_W + (x+1);
					tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

					Vertex = (z+1) * MAP_W + (x);
					tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

					Vertex = (z) * MAP_W + (x);
					tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];



					FindTriangles_polygon_has_vertex_in_triangle_last(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3,tmp_triangle4, tmp_point0, tmp_point1, tmp_point21, tmp_point22);

				}

			}








			// 2-1
			if(inPolygonArrayFlag[x+1][z+1]==1 && inPolygonArrayFlag[x][z+1]==0  && inPolygonArrayFlag[x+1][z]==0)
			{		

				Vertex = (z+1) * MAP_W + (x+1);
				tmp_triangle1.pt1._x = g_terrain [Vertex][0];
				tmp_triangle1.pt1._y = g_terrain [Vertex][1];
				tmp_triangle1.pt1._z = g_terrain [Vertex][2];

				tmp_triangle2.pt1._x = g_terrain [Vertex][0];
				tmp_triangle2.pt1._y = g_terrain [Vertex][1];
				tmp_triangle2.pt1._z = g_terrain [Vertex][2];

				tmp_triangle3.pt1._x = g_terrain [Vertex][0];
				tmp_triangle3.pt1._y = g_terrain [Vertex][1];
				tmp_triangle3.pt1._z = g_terrain [Vertex][2];



				// �����ι�б�ߵĶԽ�������
				PPR_Point tmp_point0;
				Vertex = (z) * MAP_W + (x);
				tmp_point0.x = g_terrain [Vertex][0];   tmp_point0.y = g_terrain [Vertex][2];


				Vertex = (z+1) * MAP_W + (x+1);
				tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

				Vertex = (z) * MAP_W + (x+1);
				tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

				Vertex = (z+1) * MAP_W + (x);
				tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];


				
				FindTriangles_polygon_has_vertex_in_triangle_last(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3,tmp_triangle4, tmp_point0, tmp_point1, tmp_point21, tmp_point22);
				
			}



			//2-2
			if(inPolygonArrayFlag[x+1][z+1]==0 && inPolygonArrayFlag[x][z+1]==1  && inPolygonArrayFlag[x+1][z]==0)
			{		
				
				Vertex = (z+1) * MAP_W + (x);
				tmp_triangle1.pt1._x = g_terrain [Vertex][0];
				tmp_triangle1.pt1._y = g_terrain [Vertex][1];
				tmp_triangle1.pt1._z = g_terrain [Vertex][2];

				tmp_triangle2.pt1._x = g_terrain [Vertex][0];
				tmp_triangle2.pt1._y = g_terrain [Vertex][1];
				tmp_triangle2.pt1._z = g_terrain [Vertex][2];

				tmp_triangle3.pt1._x = g_terrain [Vertex][0];
				tmp_triangle3.pt1._y = g_terrain [Vertex][1];
				tmp_triangle3.pt1._z = g_terrain [Vertex][2];



				// �Խ�������
				if(x < MAP_W-2)
				{
					PPR_Point tmp_point0;
					Vertex = (z) * MAP_W + (x+2);
					tmp_point0.x = g_terrain [Vertex][0];   tmp_point0.y = g_terrain [Vertex][2];


					Vertex = (z+1) * MAP_W + (x);
					tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

					Vertex = (z+1) * MAP_W + (x+1);
					tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

					Vertex = (z) * MAP_W + (x+1);
					tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];



					FindTriangles_polygon_has_vertex_in_triangle_last(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3,tmp_triangle4, tmp_point0, tmp_point1, tmp_point21, tmp_point22);

				}

			}

			//2-3
			if(inPolygonArrayFlag[x+1][z+1]==0 && inPolygonArrayFlag[x][z+1]==0  && inPolygonArrayFlag[x+1][z]==1)
			{		

				Vertex = (z) * MAP_W + (x+1);
				tmp_triangle1.pt1._x = g_terrain [Vertex][0];
				tmp_triangle1.pt1._y = g_terrain [Vertex][1];
				tmp_triangle1.pt1._z = g_terrain [Vertex][2];

				tmp_triangle2.pt1._x = g_terrain [Vertex][0];
				tmp_triangle2.pt1._y = g_terrain [Vertex][1];
				tmp_triangle2.pt1._z = g_terrain [Vertex][2];

				tmp_triangle3.pt1._x = g_terrain [Vertex][0];
				tmp_triangle3.pt1._y = g_terrain [Vertex][1];
				tmp_triangle3.pt1._z = g_terrain [Vertex][2];



				// �Խ�������
				if(z < MAP_W-2)
				{
					PPR_Point tmp_point0;
					Vertex = (z+2) * MAP_W + (x);
					tmp_point0.x = g_terrain [Vertex][0];   tmp_point0.y = g_terrain [Vertex][2];


					Vertex = (z) * MAP_W + (x+1);
					tmp_point1.x = g_terrain [Vertex][0];   tmp_point1.y = g_terrain [Vertex][2];

					Vertex = (z+1) * MAP_W + (x);
					tmp_point21.x = g_terrain [Vertex][0];  tmp_point21.y = g_terrain [Vertex][2];

					Vertex = (z+1) * MAP_W + (x+1);
					tmp_point22.x = g_terrain [Vertex][0];  tmp_point22.y = g_terrain [Vertex][2];



					FindTriangles_polygon_has_vertex_in_triangle_last(m_area4, tmp_triangle1, tmp_triangle2, tmp_triangle3,tmp_triangle4, tmp_point0, tmp_point1, tmp_point21, tmp_point22);

				}

			}

		}
	}
}


void CMy3DSymbolLibNewView::FindTriangles_polygon_has_vertex_in_triangle_1_1(Area_4 &m_area4, Triangle &tmp_triangle1, Triangle &tmp_triangle2, const PPR_Point &tmp_point1, const PPR_Point &tmp_point21, const PPR_Point &tmp_point22)
{
	CPointPolygonRelationship tmp_PPR;

	// ��1�������ڶ�����ڵ�������
	PPR_Polygon tmp_polygon_tri;
	tmp_polygon_tri.push_back(tmp_point1);
	tmp_polygon_tri.push_back(tmp_point21);
	tmp_polygon_tri.push_back(tmp_point22);

	PPR_Point tmp_polygon_point;	// ����ζ���
	PPR_Point tmp_polygon_point_ra; // ����ζ��� ���ڵ� һ������
	PPR_Point tmp_polygon_point_rb; // ����ζ��� ���ڵ� ��һ������

	PPR_Point JD1, JD2;

	//CString msg;
	bool intersectFlag11 = false;  bool intersectFlag12 = false;
	bool intersectFlag21 = false;  bool intersectFlag22 = false;

	short tmp_cout = 4;
	while(tmp_cout > 0)
	{
		if(4 == tmp_cout)
		{
			tmp_polygon_point.x = m_area4.pt1._x;	tmp_polygon_point.y = m_area4.pt1._z;

			tmp_polygon_point_ra.x = m_area4.pt2._x;	tmp_polygon_point_ra.y = m_area4.pt2._z;
			tmp_polygon_point_rb.x = m_area4.pt4._x;	tmp_polygon_point_rb.y = m_area4.pt4._z;
		}else if(3 == tmp_cout)
		{
			tmp_polygon_point.x = m_area4.pt2._x;  tmp_polygon_point.y = m_area4.pt2._z;

			tmp_polygon_point_ra.x = m_area4.pt1._x;	tmp_polygon_point_ra.y = m_area4.pt1._z;
			tmp_polygon_point_rb.x = m_area4.pt3._x;	tmp_polygon_point_rb.y = m_area4.pt3._z;
		}else if(2 == tmp_cout)
		{
			tmp_polygon_point.x = m_area4.pt3._x;  tmp_polygon_point.y = m_area4.pt3._z;

			tmp_polygon_point_ra.x = m_area4.pt2._x;	tmp_polygon_point_ra.y = m_area4.pt2._z;
			tmp_polygon_point_rb.x = m_area4.pt4._x;	tmp_polygon_point_rb.y = m_area4.pt4._z;
		}else if(1 == tmp_cout)
		{
			tmp_polygon_point.x = m_area4.pt4._x;  tmp_polygon_point.y = m_area4.pt4._z;

			tmp_polygon_point_ra.x = m_area4.pt1._x;	tmp_polygon_point_ra.y = m_area4.pt1._z;
			tmp_polygon_point_rb.x = m_area4.pt3._x;	tmp_polygon_point_rb.y = m_area4.pt3._z;
		}



		int inTriangleFlag = -1;
		inTriangleFlag = tmp_PPR.InPolygon(tmp_polygon_tri, tmp_polygon_point);

		// �������εĶ���Ҳ����������
		if(inTriangleFlag == 0)
		{
			
			intersectFlag11 = tmp_PPR.Meet(tmp_point1,tmp_point21, tmp_polygon_point, tmp_polygon_point_ra);
			intersectFlag12 = tmp_PPR.Meet(tmp_point1,tmp_point21, tmp_polygon_point, tmp_polygon_point_rb);


			intersectFlag21 = tmp_PPR.Meet(tmp_point1,tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
			intersectFlag22 = tmp_PPR.Meet(tmp_point1,tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);

			if( (intersectFlag11 || intersectFlag12) && (intersectFlag21 || intersectFlag22) )
			{
				if(intersectFlag11)
					JD1 = tmp_PPR.getJD(tmp_point1,tmp_point21, tmp_polygon_point, tmp_polygon_point_ra);
				if(intersectFlag12)
					JD1 = tmp_PPR.getJD(tmp_point1,tmp_point21, tmp_polygon_point, tmp_polygon_point_rb);

				if(intersectFlag21)
					JD2 = tmp_PPR.getJD(tmp_point1,tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
				if(intersectFlag22)
					JD2 = tmp_PPR.getJD(tmp_point1,tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);

				tmp_triangle1.pt2._x = JD1.x; tmp_triangle1.pt2._y = GetHeight(JD1.x, JD1.y); tmp_triangle1.pt2._z = JD1.y;
				tmp_triangle1.pt3._x = tmp_polygon_point.x; tmp_triangle1.pt3._y = GetHeight(tmp_polygon_point.x, tmp_polygon_point.y); tmp_triangle1.pt3._z = tmp_polygon_point.y;


				tmp_triangle2.pt2._x = tmp_polygon_point.x; tmp_triangle2.pt2._y = GetHeight(tmp_polygon_point.x, tmp_polygon_point.y); tmp_triangle2.pt2._z = tmp_polygon_point.y;
				tmp_triangle2.pt3._x = JD2.x; tmp_triangle2.pt3._y = GetHeight(JD2.x, JD2.y); tmp_triangle2.pt3._z = JD2.y;


				m_area4.LocalTrianglesVecotr1_1.push_back(tmp_triangle1);
				m_area4.LocalTrianglesVecotr1_1.push_back(tmp_triangle2);

			}

		}
		tmp_cout--;
	}
}



void CMy3DSymbolLibNewView::FindTriangles_polygon_has_vertex_in_triangle_2_1(Area_4 &m_area4, Triangle &tmp_triangle1, Triangle &tmp_triangle2, Triangle &tmp_triangle3, const PPR_Point &tmp_point1, const PPR_Point &tmp_point21, const PPR_Point &tmp_point22)
{
	CPointPolygonRelationship tmp_PPR;

	// ��2�������ڶ�����ڵ�������
	PPR_Polygon tmp_polygon_tri;
	tmp_polygon_tri.push_back(tmp_point1);
	tmp_polygon_tri.push_back(tmp_point21);
	tmp_polygon_tri.push_back(tmp_point22);

	PPR_Point tmp_polygon_point;	// ����ζ���
	PPR_Point tmp_polygon_point_ra; // ����ζ��� ���ڵ� һ������
	PPR_Point tmp_polygon_point_rb; // ����ζ��� ���ڵ� ��һ������

	PPR_Point JD1, JD2;

	//CString msg;
	bool intersectFlag11 = false;  bool intersectFlag12 = false;
	bool intersectFlag21 = false;  bool intersectFlag22 = false;

	short tmp_cout = 4;
	while(tmp_cout > 0)
	{
		if(4 == tmp_cout)
		{
			tmp_polygon_point.x = m_area4.pt1._x;	tmp_polygon_point.y = m_area4.pt1._z;

			tmp_polygon_point_ra.x = m_area4.pt2._x;	tmp_polygon_point_ra.y = m_area4.pt2._z;
			tmp_polygon_point_rb.x = m_area4.pt4._x;	tmp_polygon_point_rb.y = m_area4.pt4._z;
		}else if(3 == tmp_cout)
		{
			tmp_polygon_point.x = m_area4.pt2._x;  tmp_polygon_point.y = m_area4.pt2._z;

			tmp_polygon_point_ra.x = m_area4.pt1._x;	tmp_polygon_point_ra.y = m_area4.pt1._z;
			tmp_polygon_point_rb.x = m_area4.pt3._x;	tmp_polygon_point_rb.y = m_area4.pt3._z;
		}else if(2 == tmp_cout)
		{
			tmp_polygon_point.x = m_area4.pt3._x;  tmp_polygon_point.y = m_area4.pt3._z;

			tmp_polygon_point_ra.x = m_area4.pt2._x;	tmp_polygon_point_ra.y = m_area4.pt2._z;
			tmp_polygon_point_rb.x = m_area4.pt4._x;	tmp_polygon_point_rb.y = m_area4.pt4._z;
		}else if(1 == tmp_cout)
		{
			tmp_polygon_point.x = m_area4.pt4._x;  tmp_polygon_point.y = m_area4.pt4._z;

			tmp_polygon_point_ra.x = m_area4.pt1._x;	tmp_polygon_point_ra.y = m_area4.pt1._z;
			tmp_polygon_point_rb.x = m_area4.pt3._x;	tmp_polygon_point_rb.y = m_area4.pt3._z;
		}



		int inTriangleFlag = -1;
		inTriangleFlag = tmp_PPR.InPolygon(tmp_polygon_tri, tmp_polygon_point);

		// �������εĶ���Ҳ����������
		if(inTriangleFlag == 0)
		{

			intersectFlag11 = tmp_PPR.Meet(tmp_point1,tmp_point21, tmp_polygon_point, tmp_polygon_point_ra);
			intersectFlag12 = tmp_PPR.Meet(tmp_point1,tmp_point21, tmp_polygon_point, tmp_polygon_point_rb);


			intersectFlag21 = tmp_PPR.Meet(tmp_point1,tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
			intersectFlag22 = tmp_PPR.Meet(tmp_point1,tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);

			if( (intersectFlag11 || intersectFlag12) && (intersectFlag21 || intersectFlag22) )
			{
				if(intersectFlag11)
					JD1 = tmp_PPR.getJD(tmp_point1,tmp_point21, tmp_polygon_point, tmp_polygon_point_ra);
				if(intersectFlag12)
					JD1 = tmp_PPR.getJD(tmp_point1,tmp_point21, tmp_polygon_point, tmp_polygon_point_rb);

				if(intersectFlag21)
					JD2 = tmp_PPR.getJD(tmp_point1,tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
				if(intersectFlag22)
					JD2 = tmp_PPR.getJD(tmp_point1,tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);


	 
				tmp_triangle1.pt2._x = JD1.x; tmp_triangle1.pt2._y = GetHeight(JD1.x, JD1.y); tmp_triangle1.pt2._z = JD1.y;
				tmp_triangle1.pt3._x = tmp_polygon_point.x; tmp_triangle1.pt3._y = GetHeight(tmp_polygon_point.x, tmp_polygon_point.y); tmp_triangle1.pt3._z = tmp_polygon_point.y;


				tmp_triangle2.pt2._x = tmp_polygon_point.x; tmp_triangle2.pt2._y = GetHeight(tmp_polygon_point.x, tmp_polygon_point.y); tmp_triangle2.pt2._z = tmp_polygon_point.y;
				tmp_triangle2.pt3._x = JD2.x; tmp_triangle2.pt3._y = GetHeight(JD2.x, JD2.y); tmp_triangle2.pt3._z = JD2.y;


				tmp_triangle3.pt3._x = tmp_polygon_point.x; tmp_triangle3.pt3._y = GetHeight(tmp_polygon_point.x, tmp_polygon_point.y); tmp_triangle3.pt3._z = tmp_polygon_point.y;
				


				//AfxMessageBox("21");

				m_area4.LocalTrianglesVecotr2_1.push_back(tmp_triangle1);
				m_area4.LocalTrianglesVecotr2_1.push_back(tmp_triangle2);
				m_area4.LocalTrianglesVecotr2_1.push_back(tmp_triangle3);
			}

		}
		tmp_cout--;
	}
}



void CMy3DSymbolLibNewView::FindTriangles_polygon_has_vertex_in_triangle_last(Area_4 &m_area4, Triangle &tmp_triangle1, Triangle &tmp_triangle2, Triangle &tmp_triangle3, Triangle &tmp_triangle4, const PPR_Point &tmp_point0, const PPR_Point &tmp_point1, const PPR_Point &tmp_point21, const PPR_Point &tmp_point22)
{
	CPointPolygonRelationship tmp_PPR;


	PPR_Polygon tmp_polygon_tri;
	tmp_polygon_tri.push_back(tmp_point0);
	tmp_polygon_tri.push_back(tmp_point21);
	tmp_polygon_tri.push_back(tmp_point22);

	PPR_Point tmp_polygon_point;	// ����ζ���
	PPR_Point tmp_polygon_point_ra; // ����ζ��� ���ڵ� һ������
	PPR_Point tmp_polygon_point_rb; // ����ζ��� ���ڵ� ��һ������

	PPR_Point JD1, JD2 , JD3, JD4;

	//CString msg;


	short tmp_cout = 4;
	while(tmp_cout > 0)
	{
		if(4 == tmp_cout)
		{
			tmp_polygon_point.x = m_area4.pt1._x;	tmp_polygon_point.y = m_area4.pt1._z;

			tmp_polygon_point_ra.x = m_area4.pt2._x;	tmp_polygon_point_ra.y = m_area4.pt2._z;
			tmp_polygon_point_rb.x = m_area4.pt4._x;	tmp_polygon_point_rb.y = m_area4.pt4._z;
		}else if(3 == tmp_cout)
		{
			tmp_polygon_point.x = m_area4.pt2._x;  tmp_polygon_point.y = m_area4.pt2._z;

			tmp_polygon_point_ra.x = m_area4.pt1._x;	tmp_polygon_point_ra.y = m_area4.pt1._z;
			tmp_polygon_point_rb.x = m_area4.pt3._x;	tmp_polygon_point_rb.y = m_area4.pt3._z;
		}else if(2 == tmp_cout)
		{
			tmp_polygon_point.x = m_area4.pt3._x;  tmp_polygon_point.y = m_area4.pt3._z;

			tmp_polygon_point_ra.x = m_area4.pt2._x;	tmp_polygon_point_ra.y = m_area4.pt2._z;
			tmp_polygon_point_rb.x = m_area4.pt4._x;	tmp_polygon_point_rb.y = m_area4.pt4._z;
		}else if(1 == tmp_cout)
		{
			tmp_polygon_point.x = m_area4.pt4._x;  tmp_polygon_point.y = m_area4.pt4._z;

			tmp_polygon_point_ra.x = m_area4.pt1._x;	tmp_polygon_point_ra.y = m_area4.pt1._z;
			tmp_polygon_point_rb.x = m_area4.pt3._x;	tmp_polygon_point_rb.y = m_area4.pt3._z;
		}



		int inTriangleFlag = -1;
		inTriangleFlag = tmp_PPR.InPolygon(tmp_polygon_tri, tmp_polygon_point);


		bool intersectFlag11 = false;  bool intersectFlag12 = false;
		bool intersectFlag21 = false;  bool intersectFlag22 = false;

		bool intersectFlag31 = false;  bool intersectFlag32 = false;

		// �������εĶ���Ҳ�ڶԽ���������
		if(inTriangleFlag == 0)
		{


			// ��������б���н���
			intersectFlag31 = tmp_PPR.Meet(tmp_point21,tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
			intersectFlag32 = tmp_PPR.Meet(tmp_point21,tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);



			intersectFlag11 = tmp_PPR.Meet(tmp_point1,tmp_point21, tmp_polygon_point, tmp_polygon_point_ra);
			intersectFlag12 = tmp_PPR.Meet(tmp_point1,tmp_point21, tmp_polygon_point, tmp_polygon_point_rb);


			intersectFlag21 = tmp_PPR.Meet(tmp_point1,tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
			intersectFlag22 = tmp_PPR.Meet(tmp_point1,tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);

			if( (intersectFlag31 && intersectFlag32) && (intersectFlag11 || intersectFlag12) && (intersectFlag21 || intersectFlag22) )
			{
				if(intersectFlag11)
					JD1 = tmp_PPR.getJD(tmp_point1,tmp_point21, tmp_polygon_point, tmp_polygon_point_ra);
				if(intersectFlag12)
					JD1 = tmp_PPR.getJD(tmp_point1,tmp_point21, tmp_polygon_point, tmp_polygon_point_rb);

				if(intersectFlag21)
					JD2 = tmp_PPR.getJD(tmp_point1,tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
				if(intersectFlag22)
					JD2 = tmp_PPR.getJD(tmp_point1,tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);



				JD3 = tmp_PPR.getJD(tmp_point21,tmp_point22, tmp_polygon_point, tmp_polygon_point_ra);
				JD4 = tmp_PPR.getJD(tmp_point21,tmp_point22, tmp_polygon_point, tmp_polygon_point_rb);

				PPR_Point tmp;

				float len1 = (JD3.x - tmp_point21.x)*(JD3.x - tmp_point21.x) + (JD3.y - tmp_point21.y);
				float len2 = (JD4.x - tmp_point21.x)*(JD4.x - tmp_point21.x) + (JD4.y - tmp_point21.y);

				if(len1 > len2)
				{
					tmp = PPR_Point(JD3.x, JD3.y);
					JD3 = PPR_Point(JD4.x, JD4.y);
					JD4 = PPR_Point(tmp.x, tmp.y);
				}


				tmp_triangle4.pt1._x = tmp_polygon_point.x; tmp_triangle4.pt1._y = GetHeight(tmp_polygon_point.x, tmp_polygon_point.y); tmp_triangle4.pt1._z = tmp_polygon_point.y;
				tmp_triangle4.pt2._x = JD3.x; tmp_triangle4.pt2._y = GetHeight(JD3.x, JD3.y); tmp_triangle4.pt2._z = JD3.y;
				tmp_triangle4.pt3._x = JD4.x; tmp_triangle4.pt3._y = GetHeight(JD4.x, JD4.y); tmp_triangle4.pt3._z = JD4.y;




				tmp_triangle1.pt2._x = JD1.x; tmp_triangle1.pt2._y = GetHeight(JD1.x, JD1.y); tmp_triangle1.pt2._z = JD1.y;
				tmp_triangle1.pt3._x = JD3.x; tmp_triangle1.pt3._y = GetHeight(JD3.x, JD3.y); tmp_triangle1.pt3._z = JD3.y;


				tmp_triangle2.pt2._x = JD2.x; tmp_triangle2.pt2._y = GetHeight(JD2.x, JD2.y); tmp_triangle2.pt2._z = JD2.y;
				tmp_triangle2.pt3._x = JD4.x; tmp_triangle2.pt3._y = GetHeight(JD4.x, JD4.y); tmp_triangle2.pt3._z = JD4.y;


				tmp_triangle3.pt2._x = JD3.x; tmp_triangle3.pt2._y = GetHeight(JD3.x, JD3.y); tmp_triangle3.pt2._z = JD3.y;
				tmp_triangle3.pt3._x = JD4.x; tmp_triangle3.pt3._y = GetHeight(JD4.x, JD4.y); tmp_triangle3.pt3._z = JD4.y;



				//AfxMessageBox("last2");

				m_area4.LocalTrianglesVecotr_last.push_back(tmp_triangle1);
				m_area4.LocalTrianglesVecotr_last.push_back(tmp_triangle2);
				m_area4.LocalTrianglesVecotr_last.push_back(tmp_triangle3);
				m_area4.LocalTrianglesVecotr_last.push_back(tmp_triangle4);
			}

		}
		tmp_cout--;
	}
}





// ����ѡ�е�����ŵ�����
void CMy3DSymbolLibNewView::UpdateAreaTexture(PPR_Point _mp, CPoint point)
{
	unsigned int tmp_size = m_Area4_Array.GetSize();

	for(unsigned int i=0; i<tmp_size; ++i)
	{
		Area_4 m_area4;
		m_area4.pt1 = m_Area4_Array[i]->pt1;
		m_area4.pt2 = m_Area4_Array[i]->pt2;
		m_area4.pt3 = m_Area4_Array[i]->pt3;
		m_area4.pt4 = m_Area4_Array[i]->pt4;
	

		CPointPolygonRelationship tmp_ppr;

		PPR_Polygon tmp_polygon;
		PPR_Point tmp_point;

		tmp_point.x = m_area4.pt1._x; tmp_point.y = m_area4.pt1._z;
		tmp_polygon.push_back(tmp_point);

		tmp_point.x = m_area4.pt2._x; tmp_point.y = m_area4.pt2._z;
		tmp_polygon.push_back(tmp_point);

		tmp_point.x = m_area4.pt3._x; tmp_point.y = m_area4.pt3._z;
		tmp_polygon.push_back(tmp_point);

		tmp_point.x = m_area4.pt4._x; tmp_point.y = m_area4.pt4._z;
		tmp_polygon.push_back(tmp_point);


		PPR_Point tmp_dem_point;
		
		

		int inPolygonFlag = tmp_ppr.InPolygon(tmp_polygon, _mp);

		if(inPolygonFlag == 0) // ���ڶ������
		{

			// �Ҽ���ݲ˵�
			CMenu menu;
			menu.LoadMenu(IDR_POPUP_MENU_AREA_TEXTURE_UPDATE);
			CMenu *pPopUp = menu.GetSubMenu(0);
			ClientToScreen(&point);
			pPopUp->TrackPopupMenu(/*TPM_LEFTALIGN | */TPM_RIGHTBUTTON, point.x, point.y, this);

			area_id = i;
			
			 
		}
		else
		{
			//AfxMessageBox("�㲻�ڶ������!"); 
		}


	}
 


}







/************************************************************************/
/* �����ģ��                                                            */
/************************************************************************/
// �˵� ==����ӵ����ģ��
void CMy3DSymbolLibNewView::OnMenuAddPointSymbol()
{
	// TODO: �ڴ���������������
}

// 3dsMax ��Ƿ���
void CMy3DSymbolLibNewView::OnMenuAddPoint3dsmax()
{
	// TODO: �ڴ���������������
	int newFlag = 0;

	if(!exist_point_file())
	{	
		INT_PTR nRes;
		nRes = MessageBox("û�д򿪵ĵ��ļ�����Ҫ�½��ļ���", "�Ҳ������ļ�", MB_YESNO | MB_ICONQUESTION);
		if(nRes == IDYES)
		{
			newFlag = new_point_file();
			if(0 == newFlag)
			{
				exist_point_flag = TRUE;
			}
		}	
	}
	else
	{
		On3dsModelLoad();
	}
}

// 2D ͼƬ��Ƿ���
void CMy3DSymbolLibNewView::OnMenuAddPoint2dImg()
{
	// TODO: �ڴ���������������
	int newFlag = 0;

	if(!exist_point_file())
	{	
		INT_PTR nRes;
		nRes = MessageBox("û�д򿪵ĵ��ļ�����Ҫ�½��ļ���", "�Ҳ������ļ�", MB_YESNO | MB_ICONQUESTION);
		if(nRes == IDYES)
		{
			newFlag = new_point_file();
			if(0 == newFlag)
			{
				exist_point_flag = TRUE;
			}
		}	
	}
	else
	{
		OnTreeLoad();
	}
}

// 3D ͼƬ��Ƿ���
void CMy3DSymbolLibNewView::OnMenuAddPoint3dImg()
{
	// TODO: �ڴ���������������
	int newFlag = 0;

	if(!exist_point_file())
	{	
		INT_PTR nRes;
		nRes = MessageBox("û�д򿪵ĵ��ļ�����Ҫ�½��ļ���", "�Ҳ������ļ�", MB_YESNO | MB_ICONQUESTION);
		if(nRes == IDYES)
		{
			newFlag = new_point_file();
			if(0 == newFlag)
			{
				exist_point_flag = TRUE;
			}
		}	
	}
	else
	{
		On3dTreeLoad();
	}
}



// �½�����/�򿪹��� �Ի���, ��Ϣ��Ӧ
LRESULT CMy3DSymbolLibNewView::OnProjectSetted(WPARAM wParam, LPARAM lParam)
{
	if(1 == wParam)			//new project
	{
		OnSceneNew();
	}
	else if(0 == wParam)	//open project
	{
		if(g_recentlyOpenedProjectName == "")
		{
			AfxMessageBox(_T("��ѡ����Ҫ�򿪵Ĺ���!"));
		}
		else if(g_recentlyOpenedProjectName == _T("���๤��..."))
		{
			OnSceneLoad();
		}
		else
		{
			// ����ѡ�еĹ����ļ�
			CString tmpName = g_recentlyOpenedProjectName.c_str();
			loadSceneFile(tmpName);
			m_CurrentProjectName = tmpName;
		}
		
	}
	return 0;
}




// ����Ƶ�����Ŷ�������һ������˵�������Ӧ
void CMy3DSymbolLibNewView::OnMenuUpdateAreaTexture()
{
	// TODO: �ڴ���������������
	//AfxMessageBox("���ڶ������.");
	CAreaClassification ac_dlg;
	CString selectItem = "";


	if(ac_dlg.DoModal() == IDOK)
	{ 
		selectItem = ac_dlg.m_selectItem;
		CString m_areaTexturePath = ac_dlg.m_Dir + "\\" + selectItem;

		if(area_id >= 0 && area_id < m_Area4_Array.GetSize() )
		{
			m_Area4_Array[area_id]->area_texture = m_areaTexturePath;
			LoadAreaTexture(m_areaTexturePath, m_Area4_Array[area_id]->area_texture_rd);
		}
		
	}

	else
		return;	
}


// ɾ��ָ�������
void CMy3DSymbolLibNewView::OnMenuAreaDelete()
{
	// TODO: �ڴ���������������
	m_Area4_Array[area_id]->deleted = 1;
}
