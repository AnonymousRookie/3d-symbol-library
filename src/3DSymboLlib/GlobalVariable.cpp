/************************************************************************/
/*         全局变量定义                                                 */
/************************************************************************/

#include "stdafx.h"
#include "GlobalVariable.h"


// XML 与 tree control

// 模型种类的个数
const int32 g_modelKindNumber = 5;

// "3DS Model","City Symbol","Tree Model","3D Tree Model","Weather Symbol"
std::list<std::string> g_modelList[5];
// 保存被删的选项,取消时还原到g_modelList中
std::list<std::string> g_delList[5];
// 保存添加的选项,取消时从g_modelList删除中
std::list<std::string> g_addList[5];


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
std::string g_sceneDataPath = "";               // NOLINT

// 系统设置配置文件名
std::string g_systemConfigureFile = "";         // NOLINT

std::string g_point_symbolConfigureFile  = "";  // NOLINT
std::string g_line_symbolConfigureFile   = "";  // NOLINT
std::string g_area_symbolConfigureFile   = "";  // NOLINT

float g_max_height = 0;  // 最大高程

std::string g_recentlyOpenedProjectName = "";    // 选中的最近打开的工程文件名  // NOLINT

// 最近打开的工程文件列表
CStringArray g_strRecentOpenedFileArray;




namespace Global {
float GetHeight(float x, float z, float (*g_terrain)[3]) {
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
}