/************************************************************************/
/*    全局变量声明                                                      */
/************************************************************************/

#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H


#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include "Base/ZTypes.h"


// XML 与 tree control

// 模型种类的个数
extern const int32 g_modelKindNumber;

// "3DS Model","City Symbol","Tree Model","3D Tree Model","Weather Symbol"
extern std::list<std::string> g_modelList[5];
// 保存被删的选项,取消时还原到g_modelList中
extern std::list<std::string> g_delList[5];
// 保存添加的选项,取消时从g_modelList删除中
extern std::list<std::string> g_addList[5];

struct ModelTreeStruct {
    std::string _item;           // "3DS Model","City Symbol","Tree Model","3D Tree Model","Weather Symbol"
    std::string _noteDirectory;  // "/root/T3DSModel/*","/root/CitySymbol/*","/root/TreeModel/*","/root/T3DTreeModel/*",/root/WeatherSymbol/*
    bool isChanged;         // 是否发生了add/delete操作
};
extern ModelTreeStruct g_modelTree[5];

// 符号所在文件夹名称
struct SymbolFolder {
    std::string _3DSFolder;
    std::string _CityFolder;
    std::string _TreeFolder;
    std::string _3DTreeFolder;
    std::string _WeatherFolder;
};
extern SymbolFolder g_symbolFolder;





// 场景数据目录
extern std::string g_sceneDataPath;


// 系统设置配置文件名(路径+文件名)
extern std::string g_systemConfigureFile;


// 符号库配置文件(路径+文件名)
// extern string g_symbolConfigureFile;
// 点、线、面
extern std::string g_point_symbolConfigureFile;
extern std::string g_line_symbolConfigureFile;
extern std::string g_area_symbolConfigureFile;

// 地形
extern float    g_terrain   [MAP_W * MAP_W][3];     // 地形数据
extern GLuint   g_index     [MAP_W * MAP_W * 2];    // 顶点数据
extern float    g_texcoord  [MAP_W * MAP_W][2];     // 索引数组



extern float g_max_height;  // 最大高程


extern std::string g_recentlyOpenedProjectName;  // 选中的最近打开的工程文件名


// 最近打开的工程文件列表
extern CStringArray g_strRecentOpenedFileArray;


namespace Global {
float GetHeight(float x, float z, float (*g_terrain)[3]);
}

#endif  // GLOBAL_VARIABLE_H