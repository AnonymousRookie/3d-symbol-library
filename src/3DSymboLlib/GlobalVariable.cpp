/************************************************************************/
/*         ȫ�ֱ�������													*/
/************************************************************************/

#include "stdafx.h"
#include "GlobalVariable.h"


// XML �� tree control 

// ģ������ĸ���
const int g_modelKindNumber = 5;

// "3DS Model","City Symbol","Tree Model","3D Tree Model","Weather Symbol"
list<string> g_modelList[5];
// ���汻ɾ��ѡ��,ȡ��ʱ��ԭ��g_modelList��
list<string> g_delList[5];
// ������ӵ�ѡ��,ȡ��ʱ��g_modelListɾ����
list<string> g_addList[5];


ModelTreeStruct g_modelTree[5] = {
	{"3DS Model", "/root/T3DSModel/*",0},
	{"City Symbol", "/root/CitySymbol/*",0},
	{"Tree Model"," /root/TreeModel/*",0},
	{"3D Tree Model", "/root/T3DTreeModel/*",0},
	{"Weather Symbol", "/root/WeatherSymbol/*",0}
};

//���������ļ�������
SymbolFolder g_symbolFolder = {
	"3DModel","CitySymbol","TreeModel","TreeModel","Weather"
};


// ����
float	g_terrain	[MAP_W*MAP_W][3];		// ��������
GLuint	g_index		[MAP_W*MAP_W* 2];		// ��������
float	g_texcoord	[MAP_W*MAP_W][2];		// ��������



// ��������Ŀ¼
string g_sceneDataPath = "";


// ϵͳ���������ļ���
string g_systemConfigureFile = "";


// ���ſ������ļ�(·��+�ļ���)
//string g_symbolConfigureFile = "";

string g_point_symbolConfigureFile	= "";
string g_line_symbolConfigureFile	= "";
string g_area_symbolConfigureFile	= "";


float g_max_height = 0;// ���߳�


string g_recentlyOpenedProjectName = "";	// ѡ�е�����򿪵Ĺ����ļ���

// ����򿪵Ĺ����ļ��б�
CStringArray g_strRecentOpenedFileArray;