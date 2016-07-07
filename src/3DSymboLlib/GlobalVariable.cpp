/************************************************************************/
/*         全局变量定义                                                 */
/************************************************************************/

#include "stdafx.h"
#include "GlobalVariable.h"


// XML 与 tree control

// 模型种类的个数
const int32 g_modelKindNumber = 5;

// "3DS Model","City Symbol","Tree Model","3D Tree Model","Weather Symbol"
list<string> g_modelList[5];
// 保存被删的选项,取消时还原到g_modelList中
list<string> g_delList[5];
// 保存添加的选项,取消时从g_modelList删除中
list<string> g_addList[5];


ModelTreeStruct g_modelTree[5] = {
    {"3DS Model", "/root/T3DSModel/*", 0},
    {"City Symbol", "/root/CitySymbol/*", 0},
    {"Tree Model", " /root/TreeModel/*", 0},
    {"3D Tree Model", "/root/T3DTreeModel/*", 0},
    {"Weather Symbol", "/root/WeatherSymbol/*", 0}
};

// 符号所在文件夹名称
SymbolFolder g_symbolFolder = {
    "3DModel", "CitySymbol", "TreeModel", "TreeModel", "Weather"
};


// 地形
float   g_terrain   [MAP_W * MAP_W][3];     // 地形数据
GLuint  g_index     [MAP_W * MAP_W * 2];    // 顶点数据
float   g_texcoord  [MAP_W * MAP_W][2];     // 索引数组



// 场景数据目录
string g_sceneDataPath = "";  // NOLINT


// 系统设置配置文件名
string g_systemConfigureFile = "";  // NOLINT


// 符号库配置文件(路径+文件名)
// string g_symbolConfigureFile = "";

string g_point_symbolConfigureFile  = "";  // NOLINT
string g_line_symbolConfigureFile   = "";  // NOLINT
string g_area_symbolConfigureFile   = "";  // NOLINT


float g_max_height = 0;  // 最大高程


string g_recentlyOpenedProjectName = "";    // 选中的最近打开的工程文件名  // NOLINT

// 最近打开的工程文件列表
CStringArray g_strRecentOpenedFileArray;