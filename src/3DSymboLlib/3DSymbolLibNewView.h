
// 3DSymbolLibNewView.h : CMy3DSymbolLibNewView ��Ľӿ�
//

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
#include "Vector.h"
#include <math.h>
#include <atlimage.h>
#include <algorithm>

#include "PointPolygonRelationship.h"

#pragma once

// SkyBox Tex
enum {TP,LF,BK,RT,FR};


//[160119]LINE_ADD �����   [160209]AREA_ADD �����
enum { QUERY_COORDINATE,QUERY_DISTENCE,SELECTLINE,SELECTFLYPATH, LINE_ADD, AREA_ADD};/*MOUSEMOVE_3DMODEL��ʶ���ƶ�ģ�ͣ�����select����3dmodelģʽ�µĲ���Ӧ����ͣ*/
enum { SELECT, MOVE, SCALE }; 

enum {GIS_FLY_STATICHEIGHT,	GIS_FLY_PATHHEIGHT};

// model type
enum {MODEL_3DS, MODEL_CITY, MODEL_TREE_3D, MODEL_TREE};

// mouse shape
enum {MOUSE_SHAPE_SLECT, MOUSE_SHAPE_EDIT, MOUSE_SHAPE_ARROW};

// load model type "change parameter" "add new model"
// ����ģ�ͣ�����ģ��
enum{MODEL_NEW, MODEL_CHANGE};


// a �Ƿ�Ϊ0
#define DOUBLE_NUMBER_IS_ZERO(a) ( ((a)>-0.000001) && ((a)<0.000001) )



// �Ƿ�����Ѿ��򿪵ķ����ļ�
#define EXIST_OPENED_SYMBOLLIB_FILE			1
#define NOT_EXIST_OPENED_SYMBOLLIB_FILE		0




// model select struct
typedef struct  
{
	int modelType;
	int modelID;
}SelectedModel, *PSelectedModel;

 
// ģ�ͽṹ��,�洢�������״̬
typedef struct  
{
	CString strModelPath;		// ģ��·��
	int		iModelNum;			// ģ����������ID
	int		xPos;				// ƽ��ˮƽλ��
	int		zPos;				// ƽ��Zλ��
	float	hPos;				// ����������߶�
	float	radiu;				// ģ����ת�뾶������������
	int		angle;				// ģ����Y����ת
	float	scale;				// ģ����������
	bool	isSelected;			// ģ���Ƿ���ѡ��״̬
	int		iRotateX;			// ģ����X����ת�Ƕ�
	int		iRotateY;			// ģ����Y����ת�Ƕ�
	int		iRotateZ;			// ģ����Z����ת�Ƕ�
	int		iDisplayType;		// ����ӳ�䷽ʽ�� �ظ�  ����
}CModelStruct, *PModelStruct;

typedef struct  
{
	int posX;	int posY;	int posZ;
	int rotX;	int rotY;	int rotZ;
	float scale;
	CString modelPath;
	bool isDeleted; //�Ƿ�ɾ��
	int modelID;
	bool modelSelected;
	// 3dsģ������·�����ļ���
	CString m_3DS_Mode_Texture_PATH_NAME;
}CModelParamStruct, *PModelParamStruct;


// ���߰뾶,�������߳���(���س���)
typedef struct Curve_R_L0_Struct
{
	long curve_R;
	int curve_L0;
}Curve_R_L0_Struct, *PCurve_R_L0_Struct;





//[160119]
//��
typedef struct _Point3
{
	double _x;
	double _y;
	double _z;
}Point3, *PPoint3;

//��
typedef struct _Line3
{
	Point3 pt1;
	Point3 pt2;
}Line3, *PLine3;


/************************************************************************/
/* ��������ǻ�															*/
/************************************************************************/

typedef struct _Triangle{
	Point3 pt1;
	Point3 pt2;
	Point3 pt3;
}Triangle, *PTriangle;




// �ı���
typedef struct _Area_4
{
	Point3 pt1;
	Point3 pt2;
	Point3 pt3;
	Point3 pt4;


	// �������ж�����ڲ�������������
	vector<Triangle> TrianglesInPolygonVecotr;
	// �������оֲ����ǻ��˵�������(������ֻ��1�����ڶ������, �Ҷ���ε�ĳ��������������2������)
	vector<Triangle> LocalTrianglesVecotr1;
	// �������оֲ����ǻ��˵�������(������ֻ��2�����ڶ������, �Ҷ���ε�ĳ��������������2������)
	vector<Triangle> LocalTrianglesVecotr2;
	// �������оֲ����ǻ��˵�������(������ֻ��1�����ڶ������, �Ҷ���ε�1���˵�����������)
	vector<Triangle> LocalTrianglesVecotr1_1;
	// �������оֲ����ǻ��˵�������(������ֻ��2�����ڶ������, �Ҷ���ε�1���˵�����������)
	vector<Triangle> LocalTrianglesVecotr2_1;
	// �������оֲ����ǻ��˵�������(ĳ������û�е��ڶ������, ������ε�1���˵�����������)
	vector<Triangle> LocalTrianglesVecotr_last;


	CString area_texture;
	UINT area_texture_rd;

	unsigned short deleted;


}Area_4, *PArea_4;







class CMy3DSymbolLibNewView : public CView
{
protected: // �������л�����
	CMy3DSymbolLibNewView();
	DECLARE_DYNCREATE(CMy3DSymbolLibNewView)

	// ����
public:
	CMy3DSymbolLibNewDoc* GetDocument() const;

	// ����
public:

	// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// ʵ��
public:
	virtual ~CMy3DSymbolLibNewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
	PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;

	HWND		hwnd;
	CDC*	    m_pDC;			
	HGLRC		m_hRC;	

	int m_SCREEN_WIDTH;		//��Ļ���
	int m_SCREEN_HEIGHT;	//��Ļ�߶�

	int WinViewX,WinViewY;	//�洢�������ӿڵĿ�Ⱥ͸߶�
	BOOL bStereoAvailable;	//�Կ��Ƿ�֧��������ʾ

	GLfloat m_ViewWideNarrow;   //��������gluPerspective()��������ƽ��ͷ�����Ұ�ĽǶ�(������С)
	double m_near,m_far;	//gluPerspective()��������ƽ��ͷ��Ľ�����ƽ���Զ����ƽ��ľ���
	
	float m_FrustumAngle;

	BOOL SetupPixelFormat();
	BOOL InitializeOpenGL(CDC *pDC);

	void InitData();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContourTerrainImport();

	afx_msg LRESULT OnGoodBye(WPARAM wParam,LPARAM lParam);	// �Զ�����Ӧ��Ϣ,��Ӧģ������,��ģʽ�Ի���

	// ����ȸ��ߵ���ͼ��������
	int					iTerrainType;						// 1-�ȸ�, 2-���, 0-û�е������
	CString				terrainTexFileName;
	CString				terrainContourFileName;
	BITMAPINFOHEADER	g_bit;								// ����λͼ�ṹ����ModelObj��ʹ�ûҶȵȸ���ͼ���ɵ���
	unsigned char		*g_imageData;						// ����ͼ�λ���������ModelObj��ʹ�ûҶȵȸ���ͼ���ɵ���
	UINT				texTerrain;							// ��ͼ	
	bool				LoadT8(char *filename, GLuint &texture);
	unsigned char*		LoadBit(char *filename, BITMAPINFOHEADER *bitmap);


	bool		g_isTerrainInit;
	void		InitTerrain();
	void		DrawTerrain();
	float		GetHeight(float x, float z);		// ��ȡ����߶�


	//����������� 
	CVector3	m_vEyePosition;		//����ӵ�����
	CVector3	m_vLook;			//����۲������
	CVector3	m_vUp;				//���������άʸ��
	

	float		m_viewHeight;		//�ӵ�߶�
	float		m_oldviewHeight;	//ǰһ�ӵ�߶�

	CVector3	m_originLook;		//�����ʼ�ӵ�����
	float		m_viewdegree;		//�۲�����ӵ�֮��ĸ��ӽ�


	// ����
	float	    rad_xz;				// �Ƕ�
	float	    g_Angle;			// ��λ��
	float	    g_elev;				// ������
	float		gao;

	//���ڼ�������²�����CVector3���ͱ���
	CVector3	m_vStrafe;		
	CVector3	View;		

	void DrawScene();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	// ���û�ͼģʽ
	int m_Drawmode;
	void SetDrawMode();

	// ��պ�
	bool		 iSkyBoxLoaded;
	afx_msg	void OnSkyboxTex();
	UINT		 g_texSkyBox[5];
	void		 CreateSkyBox();
	void		 SkyBoxTexture(UINT textur);
	afx_msg void OnUpdateDrawmodeLine(CCmdUI *pCmdUI);
	afx_msg void OnDrawmodeRender();
	afx_msg void OnUpdateDrawmodeRender(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawmodeTexture(CCmdUI *pCmdUI);
	afx_msg void OnDrawmodeLine();
	afx_msg void OnDrawmodeTexture();
	afx_msg void OnSpacequerySet();

	// �ռ��ѯ��־����
	int		m_shizxLength;		// ��ѯ��־��ʮ���߳���
	int		m_shuzxHeight;		// ��ѯ��־����ֱ�߳���
	int		m_QueryLineWidth;	// ��ѯ��־�ߵĿ��
	int		m_QueryColorR,m_QueryColorG,m_QueryColorB;// ��ѯ��־�ߵ���ɫ(��,��,��)

	BYTE	m_QueryType;		// ��ʶ�ռ��ѯ���
	BYTE    m_OperateType;		// ģ�Ͳ�������

	bool	m_bmouseView;		// �Ƿ��������������
	POINT	m_oldMousePos;		// ǰһ���λ��

	double	pt1[3],pt2[3];		// �洢��ѯ������
	int		m_bSearchDistencePtNums;// ��ѯʱ��ȡ�Ŀռ����


	long m_linePtnums;		// ��ǰ��·������ƽ�������
	long m_oldlinePtnums;	// ԭ����·������ƽ�����


	afx_msg void OnQueryCoordinate();
	afx_msg void OnUpdateQueryCoordinate(CCmdUI *pCmdUI);
	afx_msg void OnQueryDistence();
	afx_msg void OnUpdateQueryDistence(CCmdUI *pCmdUI);

	void ScreenToGL(CPoint point);
	void DrawSearchPoint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	// �����  ���̿���

	//�����ת����
	float	m_Step_X;	//�����X�����ƶ��Ĳ���(������)
	float	m_Step_Z;	//�����Z�����ƶ��Ĳ���(������) 

	float	m_xTrans;	//��X�������ƶ��ľ���(���̿���)
	float	m_zTrans;	//��Z�������ƶ��ľ���(���̿���)
	int		m_keynumber;//��ʶ���̰���ֵ
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	void CamraUpdate();
	void MoveCameraZ(float speed);
	void CheckForMovement();
	void MoveCameraX(float speed);
	void SetCamra(); 
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void SetViewByMouse();
	void RotateView(float angle, float x, float y, float z);
	float  derAngleY;	//	������ʱY���������ϵ��
	float  derAngleZ;	//	������ʱZ���������ϵ��
	float  derDisScale; //	����ƶ�ģ��ʱ����ϵ��
	afx_msg void OnCameraParamSet();

	//��ά����
	BOOL m_ShowFlyPath; //	��ʶ�Ƿ���ʾ����·��
	CArray<PCordinate,PCordinate> m_FlayPath;		// �洢���з���·��ѡ��ʱ��ѡ���һϵ�е�����
	CArray<PCordinate,PCordinate> m_FlayPathTempPts;// �洢��ʱ���з���·��ѡ��ʱ��ѡ���һϵ�е�����
	afx_msg void OnPathManuinput();
	void DrawFlyPath();
	afx_msg void OnFlppathInterpolation(); 
	afx_msg void OnFlypathSave();
	int FlyPathSave(char *pathfile);
	BOOL m_PathFlag;//�Ƿ��������·��
	afx_msg void OnFlyOpenpath();
	int FlyPathRead(char *pathfile);
	afx_msg void OnFlyOnoffpath();
	afx_msg void OnUpdateFlyOnoffpath(CCmdUI *pCmdUI);

	BYTE m_FlyHeightType;			// ��ά��������(�̶��߶�����,�̶��߲�����)
	int m_flypathPtIndex;			// ����·������������
	int m_flyPathCurrentPtIndex;	// �ڷ��й����м�¼��ǰ·�����������,������ͣ������
	int m_flyspeed;					// ����ʱ�ļ�ʱ��ʱ���� 

	BOOL m_fly_start_pause_Enable;  // ��ͣ/��ʼ�Ƿ���Ч
	
	afx_msg void OnFlyStaticheight();
	afx_msg void OnUpdateFlyStaticheight(CCmdUI *pCmdUI);
	void SetFLyTimer();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void GetCameraCorrdinate(double x1, double y1, double z1, double x2, double y2, double z2);
	float m_maxHeight, m_minHeight,m_StaticHeight;
	afx_msg void OnFlyRoutineheight();

	GLfloat m_ViewUpDown;			// �ӽ���,����
	afx_msg void OnUpdateFlyRoutineheight(CCmdUI *pCmdUI);

	BOOL m_FlyPause;				//�Ƿ���ͣ����
	afx_msg void OnFlyPlaypause();
	afx_msg void OnUpdateFlyPlaypause(CCmdUI *pCmdUI);
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
	CGLFont* Font;			// ��ʾ����ʱ��ݼ�������ʾ
	int	m_Time,				// ��ʼʱ��
		m_Fram,				// ��ʾ����
		tim;				// ˢ���ٶ�
	HFONT	hFont,hFont0;
	void	TextFlyHelp();	// ��ʾ���� 

	//��ʾ�б���� 
	GLuint m_ClockList;		//ʱ��ָ������ʾ�б�
	float m_NorthPtangle;	//ָ�����ʼָ��Ƕ�
	void InitList();
	void MakeClockList();
	void DrawClock();
	void SetClockProjectionNavigate();
	void PrintText(float x, float y, char *string);
	void GetNorthPtangle();
	void DrawNorthPt();

	GLuint m_SkyList;		// ʱ��ָ������ʾ�б�
	bool m_bShowbreviary;	// �Ƿ���ʾ������ͼ
	void MakeSkykList();
	void DrawSky();
	void SetSkyProjection();
	void SetSkyProjectionNavigate();

	// 3DSģ��
	afx_msg void On3dsModelLoad();
	
	int m_i3DModelNum;


	CArray<PModelParamStruct, PModelParamStruct> m_3DModel;


/************************************************************************/
/*                   ��·												*/
/************************************************************************/

	BOOL b_haveMadeRail3DwayList;	// �Ƿ��Ѿ�����ά��·��ʾ�б�(͸��ͶӰģʽ��)
	
	Railway m_Railway;				// ��··���ṹ
	GLuint m_Rail3DwayList;			// ��·��άģ����ʾ�б�(͸��ͶӰģʽ)

	CArray<PCordinate,PCordinate> m_TempPts;// ��ʱ��

	CTexture m_cTxtureBP;		// ·����������
	CTexture m_cTxtureLJ;		// ·������
	CTexture m_cTxtureGdToLJ;	// ������������
	CTexture m_cTxtureRailway;	// �������
	CTexture m_cTxturePT;		// ����ƽ̨����	

	CTexture m_cFillFaceTxture;	// ��������

	// ʵ��͸��ͶӰģʽ�µ���·��άģ�ͻ���
	void DrawRailwaythesme();

	// ����������(λ�ڵ������µĲ��ֲ�����)
	void DrawCenterLine(long index, BOOL ifSelectLine);

	// ���Ʊ���
	void DrawBP(long index, int BPside);

	void fun(PCordinate ppt);
	void fun(PCordinate ppt, PCurve_R_L0_Struct pcrl0);


	// ����2������֮��ļн�,�ɲ�������
	void getDegreeBetween2Vectors(CVector3 v1_Begin/*in*/,CVector3 v1_End/*in*/,
		CVector3 v2_Begin/*in*/,CVector3 v2_End/*in*/, float *pDegreeRet/*out*/);

	void drawFillFace(vector<Railway3DCordinate> fillFacePoints);
	
//=====================================================================================


	// 3DSģ��
	CLoad3DS*	m_3ds;											// ����3DSģ�� 

	
	void Draw3DModel(PModelParamStruct model);

	afx_msg void On3dsModelSelectSet();
	afx_msg void OnUpdate3dsModelSelectSet(CCmdUI *pCmdUI);
	bool bIsSelect3DModel;

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	bool bIsMouseMove3DModel;
	afx_msg void On3dsModelMouseMove();
	afx_msg void OnUpdate3dsModelMouseMove(CCmdUI *pCmdUI);
	void JudgeModelSelected(PCordinate ppt);	// �ж�ģ��������Щģ�ͱ�ѡ��,����״̬�޸�
	int m_bMouseMove3DModelPtNums;				// �������������һ,��������ټ�һ,��2ʱ�Ϳ��ƶ�ģ��λ��,�ƶ�����Ϊ���䶯����


	CMainFrame *pMain;							// ��ȡMainFrame��ָ��

	// ����������
	afx_msg void OnTreeLoad();
	CArray<PModelStruct,PModelStruct> m_TreeModel; // �洢���о�������Ϣ
	void LoadT16(char *filename, GLuint &texture);
	int m_iTreeModelNum;		
	UINT g_cactus[50];								// ��ͼ,����

	// ��ʾ����ƽ������������תʱ��Ҳ������ת��ʼ������������û��������Ϳ�������ƽ����
	void ShowTree(int i);

	// ����3D���徰����ģ��
	afx_msg void On3dTreeLoad();
	CArray<PModelStruct,PModelStruct> m_3DTreeModel; // �洢���о�������Ϣ
	int m_i3DTreeModelNum;		
	UINT g_cactus3DTree[50];								// ��ͼ,����

	// ��ʾ����ƽ������������תʱ��Ҳ������ת��ʼ������������û��������Ϳ�������ƽ����
	void Show3DTree(int i);

	// ���з���
	afx_msg void OnCitySymbolLoad();
	int m_iCitySymbolModelNum;
	CArray<PModelStruct,PModelStruct> m_CitySymbolModel; // �洢���г��з�����Ϣ
	UINT g_citySymbolTex[50];							 // ��ͼ,����
	void ShowCitySymbol0(int i);
	void ShowCitySymbol(int i);
	void LoadPNG(const char *fileName, GLuint &texture);

	//������������ ֻ��һ������
	
	afx_msg void OnWeatherLoad();
	
	UINT g_weatherTex;									// ��ͼ,����
	void ShowWeather();
	bool bIsWeatherLoad;

	// �ж��Ƿ�����������ѯ����
	bool IsSearchPoint;

	// ���Ի��������ֵ���ṹ��
	void C3DModelParamSetTOPModelStruct(C3DModelParamSet& model, PModelStruct &pStruct);  
	// ���Ի��������ֵ���ṹ��
	void ModelParamDlgToPModelParamStruct(ModelParam &model, PModelParamStruct pStruct);
	// ���ṹ�����ݸ�ֵ������
	void PModelParamStructToModelParamDlg(ModelParam &model, PModelParamStruct pStruct);

	// ���ֿ����Ӿ�����Ĵ�С����С���Ŵ�
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	// ����ʰȡ����
	void JudgeRayIntersect(
		CVector3 rayStart,		// �������  
		CVector3 rayDir,		// ���߳��Ⱥͷ���  
		CVector3 returnNormal	// ��ѡ�ģ��ཻ�㴦������
		);
	// �ж������Ƿ���AABB��Χ�У������ؽ���
	float RayIntersect(  
		CVector3 rayStart,		// �������  
		CVector3 rayDir,		// ���߳��Ⱥͷ���  
		CVector3 returnNormal,	// ��ѡ�ģ��ཻ�㴦������  
		CVector3 min,			// ��Χ�����½Ƕ���
		CVector3 max			// ��Χ�����ϽǶ���
		);

	// ʰȡģ�ͼ���
	vector<PSelectedModel> m_pSelectedModelSet;
	// ѡ�������߿���ɫ
	float wireR,wireG,wireB;
	// ��˸��ʱ��������ʶ
	bool m_bFlash;

	bool m_bMouseMoveSelect; // ѡ��ģʽ�µ�����ƶ�ʰȡģ��
	int m_mouseShape;		 // �����̬

	// ���������ļ�����
	bool m_bSecneConfig;
	afx_msg void OnSceneLoad();

	

	CString m_AllDataPath; // ���������ļ�·��
	CString m_SceneConfig; // �����ļ���

	// �����ļ��У����������ļ��У����εȸ��ļ���
	CString m_TerrainFolder, m_TerrainTextureFolder, m_TerrainContourFolder; 
	// �����������εȸ�ͼ
	CString m_TerrainTexture, m_TerrainContour;
	// SkyBox
	CString m_SkyBoxFolder, m_SkyBoxKindFolder, m_SkyBoxTP,m_SkyBoxLT,m_SkyBoxRT,m_SkyBoxBK,m_SkyBoxFR;
	
	// 3DS ģ��	
	CString m_3DModelFolder;
	CString m_3DModelPath;
	
	float m_3DModelPosX, m_3DModelPosY, m_3DModelPosZ;
	
	float m_3DModelRotX, m_3DModelRotY, m_3DModelRotZ;
	float m_3DModelScale;


	// ���б�ʶ����
	CString m_CitySymbolFolder, m_CitySymbolTex;
	
	float m_CitySymbolPosX, m_CitySymbolPosY, m_CitySymbolPosZ;

	// ����������
	CString m_TreeModelFolder, m_TreeModelTex;
	
	float m_TreeModelPosX, m_TreeModelPosY, m_TreeModelPosZ;

	// ��������
	CString m_WeatherFolder, m_WeatherTex;

	// ��պ�����
	void LoadSkyBoxTex(CString skyTP, CString skyLF, CString skyBK, CString skyRT, CString skyFR);
	CString g_texSkyBoxFlieNameTP,g_texSkyBoxFlieNameLF,g_texSkyBoxFlieNameBK,g_texSkyBoxFlieNameRT,g_texSkyBoxFlieNameFR;

	// ��������
	void LoadTerrainTex(CString terrainTex, CString terrainContour);

	// 3Dģ������
	//void Load3DModel(PModelStruct p3d, int iModelID);
	//void Load3DModel(PModelParamStruct p3d, int iModelID);
	void Load3DModel(PModelParamStruct p3d, int iLoadModelType); 

	bool m_bIsLBtnDown;
	afx_msg void OnSceneSave();
	bool ScenSave(CString scenePth);

	// ����ѡ��ģ��,����ģ��ѡ����Կ�������ģ�Ͳ������ã���ģ��ѡ��Ļ�ֻ���ƶ����ģ��
	// �Ҽ����� ���� ��ʶ
	
	int m_selectedModelID; // ��ǰ���ѡ��ģ��ID����ǰĬ��ֻ��3DSģ��
	afx_msg void OnModelMove();
	afx_msg void OnModelParam();
	afx_msg void OnModelScale();

	afx_msg void OnConfigureSymbolList();
	afx_msg void OnSystemSetting();
	afx_msg void OnCloseCurrentScene();
	afx_msg void OnModelDelete();
	afx_msg void OnMenuBuild3dlinemodle();
	afx_msg void OnMenuLinedesign();
	afx_msg void OnUpdateMenuLinedesign(CCmdUI *pCmdUI);



/************************************************************************/
/* ��3DSģ�Ͳ������õķ�ģʽ�Ի���   ���������					    		*/
/************************************************************************/
public:
	C3DModelParamSet *paramSet_modeless_dlg;
	void C3DModelParamSetTOPModelStruct(C3DModelParamSet *model, PModelStruct &pStruct);
	PModelStruct p3dtree;			//3dtree
	PModelStruct ptree;				//tree
	PModelStruct pCitySymbol;		//CitySymbol
	BOOL m_isSetXYByMouse;

/************************************************************************/
/* Variables: ѡ����ֵ�趨(����,�н�)										*/
/************************************************************************/
private:
	// ���ڼ���2��֮���߶γ���
	float last_x, last_y, last_z;
	float pre_x,  pre_y,  pre_z;
	// ���ڼ���2�߶μ�н�
	CVector3 v1_begin, v1_end;
	CVector3 v2_begin, v2_end;
	// ��¼��ĸ���
	int p_count;		

/************************************************************************/
/* Variables: ����Ҫ���趨												*/
/************************************************************************/
private:
	long m_Curve_R;	 // ���߰뾶
	int  m_Curve_L0; // �������߳�

	float m_distance_between_2_points;	// ��ǰ2���߶μ�ľ���
	float m_pre_distance;				// ǰһ�߶μ�ľ���


public:
	afx_msg void OnMenuClearLines(); // ���������·	

private:
	void initLines(); // ��ʼ����·����
	void clearLinesData();// ���������·����
	void loadSceneFile(CString filename);// ���س��������ļ�

	// ���ص��ļ�
	void LoadPointSymbolFile(CString filename);
	// �������ļ�
	void LoadLineSymbolFile(CString filename);
	// �������ļ�
	void LoadAreaSymbolFile(CString filename);


	// ��ǰ�����ļ���
	CString m_CurrentProjectName;


	// ��ǰ�����������
	CString m_CurrentSymbolTypeNum;
	// �㡢�ߡ����ļ�
	CString m_PointSymbolFile, m_LineSymbolFile, m_AreaSymbolFile;


	// �жϵ�ǰ�������Ƿ�����Ѿ��򿪵ĵ㡢�ߡ����ļ�
	BOOL exist_point_file();
	BOOL exist_line_file();
	BOOL exist_area_file();

	BOOL exist_point_flag;
	BOOL exist_line_flag;
	BOOL exist_area_flag;

	// �½������ļ�

	int new_symbol_file(unsigned int type, char *fileName); //0,1,2 ������

	int new_point_file();
	int new_line_file();
	int new_area_file();



	// ������ļ�
	int savePointSymbolFile(CString filename);
	// �������ļ�
	int saveLineSymbolFile(CString filename);
	// �������ļ�
	int saveAreaSymbolFile(CString filename);


//[160119]�߷���
private:
	
	void drawLine(Line3 line);

	//�ռ����ͶӰ��ƽ���ֱ�߷���ϵ��ABC, Ax+By+C=0
	void getLine2ABC(double *A, double *B, double *C, Point3 p1, Point3 p2);


	int m_LineEdit_pointNum; // �߱༭  ѡ��ĵ�ĸ���

	Line3 m_line;

	CArray<PLine3,PLine3> m_LinesArray; // ������е��߷���


	// �����߶�_line�������ĺ�������������, ��������Χ
	void CalcuateGridNum(int *rowNum, int *row_index_begin, int *row_index_end, 
		int *colNum, int *col_index_begin, int *col_index_end, Line3 _line);

	// ����ƽ�潻������,�������������ĸ߳�ֵ
	void CalcuateJD(int rowNum, int row_index_begin, int row_index_end, 
		int colNum, int col_index_begin, int col_index_end, Line3 _line, vector<Point3> &_pv);

	// ����2��ֱ�ߵĽ���y=x+b, Ax+By+C=0, ����-1��ʾ�޽���
	BOOL GetJDFrom2Line(PPoint3 p/*out*/,double b, double A, double B, double C);

	vector<Point3> JD_vector1;
	vector<Point3> JD_vector2;
	vector<Point3> JD_vector3; // б�߽���

	vector<Point3> Line_a_JD_vector;
	vector<Point3> Line_b_JD_vector;


	BOOL fuse_Flag;

	void DrawJDLine(vector<Point3> &_pv1,  vector<Point3> &_pv2);


	// ���������ζ���������С���ֵ
	void GetMinXY(vector<Point3> &_pv1,  vector<Point3> &_pv2, double *_minX, double *_minY, double *_maxX, double *_maxY);

	// �߷�����������
	void GetUV(double _x, double _y, double _minX, double _minY, double _maxX, double _maxY, double *_u, double *_v);


/************************************************************************/
/*        �����															*/
/************************************************************************/
private:

	int m_Area_pointNum; // ����� ѡ��ĵ�ĸ���
	Area_4 m_area4_forScreenRecord; // 4����

	CArray<PArea_4, PArea_4> m_Area4_Array; // ������е������


	vector<Point3> Line_1_JD_vector;
	vector<Point3> Line_2_JD_vector;
	vector<Point3> Line_3_JD_vector;
	vector<Point3> Line_4_JD_vector;




	BOOL Area_fuse_Flag;
	// ��������ǻ�
	void Area_Triangled(PArea_4 &_area4);

	UINT m_area_texture;
	void LoadAreaTexture(CString _areaTexture_str, UINT &texture_id);// �������������


	// ����ѡ�е�����ŵ�����
	void UpdateAreaTexture(PPR_Point _mp, CPoint point);
	void ScreenToGL2(CPoint point, GLdouble &wx , GLdouble &wz);


	unsigned short area_id;


	// ��Ŷ�����ڵĵ�
	vector<Point3> pointsInPolygonVector;
	vector<Point3> index_pointsInPolygonVector;

	// ��������а����ڶ�����ڵĵ�
	int FindAllPointsInPolygon(Area_4 &m_area4);

	//(MAP_W * MAP_W)���� 1:�ڶ������, 0:����  
	int inPolygonArrayFlag[MAP_W][MAP_W];


	// �ҳ����а����ڶ�����ڵ�������(�������������κ;����ֲ����ǻ���������)
	int FindAllTrianglesInPolygon(Area_4 &m_area4);

	// ֻ��1�����ڶ�������ڵ�������(���������ǻ�)
	int FindTriangles_1_point_inPolygon(Area_4 &m_area4);

	// ֻ��2�����ڶ�������ڵ�������(���������ǻ�)
	int FindTriangles_2_point_inPolygon(Area_4 &m_area4);

	// ��3�����ڶ�������ڵ�������
	int FindTriangles_3_point_inPolygon(Area_4 &_area4);

	// ����ε�һ����  ��  ������  ��2������, �ҳ�����������������
	void Find_triangles_1_line_2_JD(Area_4 &m_area4, Triangle &tmp_triangle, CPointPolygonRelationship &tmp_PPR, const PPR_Point &tmp_point1, const PPR_Point &tmp_point21, const PPR_Point &tmp_point22);


	// �������оֲ����ǻ��˵�������
	//vector<Triangle> LocalTrianglesVecotr;



	// �������ж�����ڲ�������������
	//vector<Triangle> TrianglesInPolygonVecotr;



	// �������оֲ����ǻ��˵�������(������ֻ��1�����ڶ������, �Ҷ���ε�ĳ��������������2������)
	//vector<Triangle> LocalTrianglesVecotr1;

	// �������оֲ����ǻ��˵�������(������ֻ��2�����ڶ������, �Ҷ���ε�ĳ��������������2������)
	//vector<Triangle> LocalTrianglesVecotr2;


	


	// ---------------------------------------------

	// ����ζ��㴦��������
	void FindTriangles_polygon_has_vertex_in_triangle(Area_4 &m_area4);

	void FindTriangles_polygon_has_vertex_in_triangle_1_1(Area_4 &m_area4, Triangle &tmp_triangle1, Triangle &tmp_triangle2, const PPR_Point &tmp_point1, const PPR_Point &tmp_point21, const PPR_Point &tmp_point22);
	void FindTriangles_polygon_has_vertex_in_triangle_2_1(Area_4 &m_area4, Triangle &tmp_triangle1, Triangle &tmp_triangle2, Triangle &tmp_triangle3, const PPR_Point &tmp_point1, const PPR_Point &tmp_point21, const PPR_Point &tmp_point22);

 
	// �������оֲ����ǻ��˵�������(������ֻ��1�����ڶ������, �Ҷ���ε�1���˵�����������)
	//vector<Triangle> LocalTrianglesVecotr1_1;

	// �������оֲ����ǻ��˵�������(������ֻ��2�����ڶ������, �Ҷ���ε�1���˵�����������)
	//vector<Triangle> LocalTrianglesVecotr2_1;



	void FindTriangles_polygon_has_vertex_in_triangle_last(Area_4 &m_area4, Triangle &tmp_triangle1, Triangle &tmp_triangle2, Triangle &tmp_triangle3, Triangle &tmp_triangle4, const PPR_Point &tmp_point0, const PPR_Point &tmp_point1, const PPR_Point &tmp_point21, const PPR_Point &tmp_point22);
	// �������оֲ����ǻ��˵�������(ĳ������û�е��ڶ������, ������ε�1���˵�����������)
	//vector<Triangle> LocalTrianglesVecotr_last;


public:
	afx_msg LRESULT OnProjectSetted(WPARAM wParam, LPARAM lParam);

public:
	afx_msg void OnSceneNew();
	afx_msg void OnSceneSaveAs();
	afx_msg void OnMenuLineAdd();
	afx_msg void OnMenuLineFuse();
	afx_msg void OnUpdateMenuLineAdd(CCmdUI *pCmdUI);
	afx_msg void OnMenuAddLineWidth();
	afx_msg void OnMenuAddAreaSlib();
	afx_msg void OnUpdateMenuAddAreaSlib(CCmdUI *pCmdUI);
	afx_msg void OnMenuAreaFuse();
	afx_msg void OnMenuAddPointSymbol();
	afx_msg void OnMenuAddPoint3dsmax();
	afx_msg void OnMenuAddPoint2dImg();
	afx_msg void OnMenuAddPoint3dImg();
	afx_msg void OnMenuUpdateAreaTexture();
	afx_msg void OnMenuAreaDelete();
};

#ifndef _DEBUG  // 3DSymbolLibNewView.cpp �еĵ��԰汾
inline CMy3DSymbolLibNewDoc* CMy3DSymbolLibNewView::GetDocument() const
{ return reinterpret_cast<CMy3DSymbolLibNewDoc*>(m_pDocument); }
#endif

