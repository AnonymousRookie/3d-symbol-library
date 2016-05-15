/************************************************************************/
/*    ȫ�ֱ�������														*/
/************************************************************************/

#pragma once


#include <iostream>
#include <list>
#include <string>
#include <algorithm>


using namespace std;


// XML �� tree control 

// ģ������ĸ���
extern const int g_modelKindNumber;

// "3DS Model","City Symbol","Tree Model","3D Tree Model","Weather Symbol"
extern list<string> g_modelList[5];
// ���汻ɾ��ѡ��,ȡ��ʱ��ԭ��g_modelList��
extern list<string> g_delList[5];
// ������ӵ�ѡ��,ȡ��ʱ��g_modelListɾ����
extern list<string> g_addList[5];
 
struct ModelTreeStruct
{
	string _item;			//"3DS Model","City Symbol","Tree Model","3D Tree Model","Weather Symbol"
	string _noteDirectory;	//"/root/T3DSModel/*","/root/CitySymbol/*","/root/TreeModel/*","/root/T3DTreeModel/*",/root/WeatherSymbol/*
	bool isChanged;			// �Ƿ�����add/delete����
};
extern ModelTreeStruct g_modelTree[5];

//���������ļ�������
struct SymbolFolder
{
	string _3DSFolder;
	string _CityFolder;
	string _TreeFolder;
	string _3DTreeFolder;
	string _WeatherFolder;
};
extern SymbolFolder g_symbolFolder;





// ��������Ŀ¼
extern string g_sceneDataPath;


// ϵͳ���������ļ���(·��+�ļ���)
extern string g_systemConfigureFile;


// ���ſ������ļ�(·��+�ļ���)
// extern string g_symbolConfigureFile;
// �㡢�ߡ���
extern string g_point_symbolConfigureFile;
extern string g_line_symbolConfigureFile;
extern string g_area_symbolConfigureFile;

// ����
extern float	g_terrain	[MAP_W*MAP_W][3];		// ��������
extern GLuint	g_index		[MAP_W*MAP_W* 2];		// ��������
extern float	g_texcoord	[MAP_W*MAP_W][2];		// ��������



extern float g_max_height;// ���߳�


extern string g_recentlyOpenedProjectName;	// ѡ�е�����򿪵Ĺ����ļ���


// ����򿪵Ĺ����ļ��б�
extern CStringArray g_strRecentOpenedFileArray;