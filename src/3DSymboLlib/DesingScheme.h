#pragma once


#include <math.h>
#include <iostream>
using namespace std;
#include <vector>

//三维点坐标结构
typedef struct  
{
	double x;	//x坐标
	double y;	//y坐标
	double z;	//z坐标
}Cordinate3D, *PCordinate3D;

//路基断面结构
typedef struct  
{
	float   m_Railway_width;		//路基断面总宽度
	float	m_Lj_width;				//路肩宽度
	float	m_Lj_Dh;				//碴肩至碴脚的高度
	float   m_GuiMianToLujianWidth;	//铁轨到碴肩的距离
	float	m_TieGui_width;			//铁轨间距
	
}Railway;


//线路轨道结构
typedef struct  
{
	//左侧轨道点坐标
	double x1; double y1; double z1;
	//右侧轨道点坐标
	double x2; double y2; double z2;

	int TW_left;	//左侧填挖类型
	int TW_right;	//左侧填挖类型
	float mAngle;	//当前旋转角度
}Railway3DCordinate, *PRailway3DCordinate;

// 线路三维点综合结构
typedef struct  
{
	//点的坐标(x,y,z)
	double x; double y; double z; 
	CString strJDStyle;	//交点类型
	float dmh;			//点的地面高程
	float Derh;			//点的高差
	double Lc;			//点的里程
}Cordinate, *PCordinate;



//线路设计交点结构
typedef struct  
{
	CString  ID;	//交点ID号
	double  JDLC;	//交点里程
	float Alfa;		//交点转角
	float fwj;		//交点偏角1
	float fwj2;		//交点偏角2
	float T;		//切线长
	int L0;			//缓和曲线长
	float L;		//曲线长
	float Ly;		//
	float Jzxc;		//夹直线长
	double HZ;		//缓直点里程
	double ZH;		//直缓点里程
	double HY;		//缓圆点里程
	double YH;		//圆缓点里程
	long R;			//曲线半径
	float E;		//外矢距
	float P;		//
	float Dist;		//
	int  RoateStyle;//旋转类型(左转,右转)
	double x;		//交点x坐标
	double y;		//交点y坐标
	double z;		//交点z坐标
	
	PCordinate ZH_xy;//直缓点坐标
	PCordinate HZ_xy;//缓直点坐标
	PCordinate YH_xy;//圆缓点坐标
	PCordinate HY_xy;//缓圆点坐标
	
	double Cneterx; //曲线圆心x坐标
	double Cnetery;//曲线圆心y坐标
	
}LineCurve, *PLineCurve;


//护坡结构
typedef struct  
{
	Cordinate3D Hp[3];	//一阶护坡3个点
	float h;			//高
	float m;			//坡率	
	float b;			//边坡平台宽
	int style;			//护坡类型
}HuPo, *PHuPo;

//路基总结构
typedef struct  
{
	HuPo HuPo_L[3];		// 左侧护坡结构
	int Huponums_L;		// 左侧护坡级数
	HuPo HuPo_R[3];		// 右侧护坡结构
	int Huponums_R;		// 右侧护坡级数
	int TW_left;		// TW_left=-1: 路堑
	int TW_right;		// TW_right=-1:路堑
	double Lc;			// 里程
	CString strJDStyle;
}LuQianHuPo,*PLuQianHuPo;

typedef struct 
{
	long InsertIndex;
	CArray<PLuQianHuPo,PLuQianHuPo> tempHuPo;
}LuQianHuPoTemp,*PLuQianHuPoTemp;


class CDesingScheme
{
public:
	CDesingScheme(void);
	~CDesingScheme(void);


public:
	double GetDistenceXY(double x1,double y1,double x2,double y2);

	float GetDistenceXYZ(double x1, double y1, double z1, double x2, double y2, double z2);
	 
	void Get3DLineModel(double x1,double y1,double z1,double x2,double y2,double z2,float fRailwayWidth,float LjWidth,float h_FromGmToLj,float mWidthGuiMianToLujian,float mAngleLujinaToBianPo,CString strJDstyle,CString strJDstyleNext,long index,double mLC);
	void Get3DLineModelLast(double x1, double y1, double z1,double x2, double y2, double z2, float fRailwayWidth, float LjWidth, float h_FromGmToLj,float mWidthGuiMianToLujian,float mAngleLujinaToBianPo,CString strJDstyle,CString strJDstyleNext,long index,double mLC);
	
	//根据线路前后中心线的三维坐标计算铁轨顶面左右点的x,y,z坐标
	void Get3DCorrdinate(double x1, double y1, double z1,double x2, double y2, double z2,float dx,float dz, float L,double *x11,double *y11,double *z11,double *x12,double *y12,double *z12,double *x21,double *y21,double *z21,double *x22,double *y22,double *z22 ,float *angle);
	
	// 计算各交点的曲线要素
	void CalculateCurveData();

	//在交点间内插点并保存到数组中,供程序调用
	void Save3DlineZX();

	void NeiChaDian(float ZHLength, double x1, double y1, double z1, double x2, double y2, double z2,double lc);
	void GetQLXY(float L0, long R, int RoateStyle, float LL, float fwj, double ZH_xy_x, double ZH_xy_y, double HZ_xy_x, double HZ_xy_y, double *xc, double *yc, int Q_H_L);
	void GetYQXXY(double centerx, double centery, long R, int RoateStyle, float LL, float alfa, double HY_xy_x, double HY_xy_y, double YH_xy_x, double YH_xy_y, double *xc, double *yc);
	

	//计算边坡与在面的交点坐标 
	void GetDMJD(double x1, double y1, double z1, double x2, double y2, double z2,float L,float h0, double x0,double z0,int TW, int LeftRight,\
			double tx0,double ty0,double tz0,double tx1,double ty1,double tz1,double mLC,CString strJDstyle);
	
	//计算终点处边坡与在面的交点坐标 
	void GetDMJDLast(double x1, double y1, double z1, double x2, double y2, double z2,float L,float h0, double x0,double z0,int TW, int LeftRight,\
		double tx0,double ty0,double tz0,double tx1,double ty1,double tz1,double mLC,CString strJDstyle);

	
	//计算边坡点与地面线的交点坐标 
	void GetBpJD(float H0, float Afla, float mangle, double x0, double z0, int bsignTW, int mLeftRight, double *tx, double *ty, double *tz);

	float GetH(float L, float Afla, float mAngle,double x0,double z0,int mLeftRight,double *xx,double *zz);
	//计算边坡的填挖类型
	int GetTW(double x, double z, float H);

	float GetHeightValue(float x, float z);


	// 计算填补面边上的点
	void CalculateFillFacePoints(vector<Railway3DCordinate> &rcVector2,vector<Railway3DCordinate> &rcVector1);

public:
	// 铁路中线
	CArray<PCordinate,PCordinate> PtS_3DLineZX;

	// 路肩
	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_RailwayLj3D;

	// 轨道
	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_Railway3D;

	// 线路设计交点
	CArray<PLineCurve,PLineCurve> JDCurveElements;

	// 交点
	CArray<PCordinate,PCordinate> PtS_JD;

	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_RailwayLjToBP3D;
	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_RailwayBP3D;

	CArray<PLuQianHuPo,PLuQianHuPo> PtS_HuPo;
	CArray<PLuQianHuPoTemp,PLuQianHuPoTemp> PtSHuPoTemp;
 
};

