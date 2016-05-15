#pragma once


#include <math.h>
#include <iostream>
using namespace std;
#include <vector>

//��ά������ṹ
typedef struct  
{
	double x;	//x����
	double y;	//y����
	double z;	//z����
}Cordinate3D, *PCordinate3D;

//·������ṹ
typedef struct  
{
	float   m_Railway_width;		//·�������ܿ��
	float	m_Lj_width;				//·����
	float	m_Lj_Dh;				//�������ŵĸ߶�
	float   m_GuiMianToLujianWidth;	//���쵽���ľ���
	float	m_TieGui_width;			//������
	
}Railway;


//��·����ṹ
typedef struct  
{
	//�����������
	double x1; double y1; double z1;
	//�Ҳ���������
	double x2; double y2; double z2;

	int TW_left;	//�����������
	int TW_right;	//�����������
	float mAngle;	//��ǰ��ת�Ƕ�
}Railway3DCordinate, *PRailway3DCordinate;

// ��·��ά���ۺϽṹ
typedef struct  
{
	//�������(x,y,z)
	double x; double y; double z; 
	CString strJDStyle;	//��������
	float dmh;			//��ĵ���߳�
	float Derh;			//��ĸ߲�
	double Lc;			//������
}Cordinate, *PCordinate;



//��·��ƽ���ṹ
typedef struct  
{
	CString  ID;	//����ID��
	double  JDLC;	//�������
	float Alfa;		//����ת��
	float fwj;		//����ƫ��1
	float fwj2;		//����ƫ��2
	float T;		//���߳�
	int L0;			//�������߳�
	float L;		//���߳�
	float Ly;		//
	float Jzxc;		//��ֱ�߳�
	double HZ;		//��ֱ�����
	double ZH;		//ֱ�������
	double HY;		//��Բ�����
	double YH;		//Բ�������
	long R;			//���߰뾶
	float E;		//��ʸ��
	float P;		//
	float Dist;		//
	int  RoateStyle;//��ת����(��ת,��ת)
	double x;		//����x����
	double y;		//����y����
	double z;		//����z����
	
	PCordinate ZH_xy;//ֱ��������
	PCordinate HZ_xy;//��ֱ������
	PCordinate YH_xy;//Բ��������
	PCordinate HY_xy;//��Բ������
	
	double Cneterx; //����Բ��x����
	double Cnetery;//����Բ��y����
	
}LineCurve, *PLineCurve;


//���½ṹ
typedef struct  
{
	Cordinate3D Hp[3];	//һ�׻���3����
	float h;			//��
	float m;			//����	
	float b;			//����ƽ̨��
	int style;			//��������
}HuPo, *PHuPo;

//·���ܽṹ
typedef struct  
{
	HuPo HuPo_L[3];		// ��໤�½ṹ
	int Huponums_L;		// ��໤�¼���
	HuPo HuPo_R[3];		// �Ҳ໤�½ṹ
	int Huponums_R;		// �Ҳ໤�¼���
	int TW_left;		// TW_left=-1: ·ǵ
	int TW_right;		// TW_right=-1:·ǵ
	double Lc;			// ���
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
	
	//������·ǰ�������ߵ���ά����������춥�����ҵ��x,y,z����
	void Get3DCorrdinate(double x1, double y1, double z1,double x2, double y2, double z2,float dx,float dz, float L,double *x11,double *y11,double *z11,double *x12,double *y12,double *z12,double *x21,double *y21,double *z21,double *x22,double *y22,double *z22 ,float *angle);
	
	// ��������������Ҫ��
	void CalculateCurveData();

	//�ڽ�����ڲ�㲢���浽������,���������
	void Save3DlineZX();

	void NeiChaDian(float ZHLength, double x1, double y1, double z1, double x2, double y2, double z2,double lc);
	void GetQLXY(float L0, long R, int RoateStyle, float LL, float fwj, double ZH_xy_x, double ZH_xy_y, double HZ_xy_x, double HZ_xy_y, double *xc, double *yc, int Q_H_L);
	void GetYQXXY(double centerx, double centery, long R, int RoateStyle, float LL, float alfa, double HY_xy_x, double HY_xy_y, double YH_xy_x, double YH_xy_y, double *xc, double *yc);
	

	//�������������Ľ������� 
	void GetDMJD(double x1, double y1, double z1, double x2, double y2, double z2,float L,float h0, double x0,double z0,int TW, int LeftRight,\
			double tx0,double ty0,double tz0,double tx1,double ty1,double tz1,double mLC,CString strJDstyle);
	
	//�����յ㴦����������Ľ������� 
	void GetDMJDLast(double x1, double y1, double z1, double x2, double y2, double z2,float L,float h0, double x0,double z0,int TW, int LeftRight,\
		double tx0,double ty0,double tz0,double tx1,double ty1,double tz1,double mLC,CString strJDstyle);

	
	//������µ�������ߵĽ������� 
	void GetBpJD(float H0, float Afla, float mangle, double x0, double z0, int bsignTW, int mLeftRight, double *tx, double *ty, double *tz);

	float GetH(float L, float Afla, float mAngle,double x0,double z0,int mLeftRight,double *xx,double *zz);
	//������µ���������
	int GetTW(double x, double z, float H);

	float GetHeightValue(float x, float z);


	// ���������ϵĵ�
	void CalculateFillFacePoints(vector<Railway3DCordinate> &rcVector2,vector<Railway3DCordinate> &rcVector1);

public:
	// ��·����
	CArray<PCordinate,PCordinate> PtS_3DLineZX;

	// ·��
	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_RailwayLj3D;

	// ���
	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_Railway3D;

	// ��·��ƽ���
	CArray<PLineCurve,PLineCurve> JDCurveElements;

	// ����
	CArray<PCordinate,PCordinate> PtS_JD;

	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_RailwayLjToBP3D;
	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_RailwayBP3D;

	CArray<PLuQianHuPo,PLuQianHuPo> PtS_HuPo;
	CArray<PLuQianHuPoTemp,PLuQianHuPoTemp> PtSHuPoTemp;
 
};

