#ifndef SYMBOL_DEFINES_H
#define SYMBOL_DEFINES_H

#include <vector>


// LINE_ADD 添加线   AREA_ADD 添加面
enum { QUERY_COORDINATE = 0, QUERY_DISTENCE, SELECTLINE, SELECTFLYPATH, LINE_ADD, AREA_ADD}; /*MOUSEMOVE_3DMODEL标识在移动模型，这是select——3dmodel模式下的操作应该暂停*/
enum { SELECT = 0, MOVE, SCALE };
enum {GIS_FLY_STATICHEIGHT = 0, GIS_FLY_PATHHEIGHT};
// model type
enum {MODEL_3DS = 0, MODEL_CITY, MODEL_TREE_3D, MODEL_TREE};
// mouse shape
enum {MOUSE_SHAPE_SLECT = 0, MOUSE_SHAPE_EDIT, MOUSE_SHAPE_ARROW};
// load model type "change parameter" "add new model"
// 新增模型，更新模型
enum {MODEL_NEW, MODEL_CHANGE};

// 是否存在已经打开的符号文件
#define EXIST_OPENED_SYMBOLLIB_FILE         1
#define NOT_EXIST_OPENED_SYMBOLLIB_FILE     0


// model select struct
typedef struct {
    int32 modelType;
    int32 modelID;
} SelectedModel, *PSelectedModel;


// 模型结构体,存储各类符号状态
typedef struct {
    CString strModelPath;       // 模型路径
    int32   iModelNum;          // 模型在种类中ID
    int32   xPos;               // 平面水平位置
    int32   zPos;               // 平面Z位置
    float   hPos;               // 底面距离地面高度
    float   radiu;              // 模型旋转半径，距离中心线
    int32   angle;              // 模型绕Y轴旋转
    float   scale;              // 模型缩放因子
    bool    isSelected;         // 模型是否处于选中状态
    int32   iRotateX;           // 模型绕X轴旋转角度
    int32   iRotateY;           // 模型绕Y轴旋转角度
    int32   iRotateZ;           // 模型绕Z轴旋转角度
    int32   iDisplayType;       // 纹理映射方式： 重复  拉伸
} CModelStruct, *PModelStruct;

typedef struct {
    int32 posX;
    int32 posY;
    int32 posZ;
    int32 rotX;
    int32 rotY;
    int32 rotZ;
    float scale;
    CString modelPath;
    bool isDeleted;  // 是否被删除
    int32 modelID;
    bool modelSelected;
    // 3ds模型纹理路径及文件名
    CString m_3DS_Mode_Texture_PATH_NAME;
} CModelParamStruct, *PModelParamStruct;


// 曲线半径,缓和曲线长度(加载场景)
typedef struct Curve_R_L0_Struct {
    int64 curve_R;
    int32 curve_L0;
} Curve_R_L0_Struct, *PCurve_R_L0_Struct;

// 点
typedef Vec3 Point3;

// 线
typedef struct _Line3 {
    Point3 pt1;
    Point3 pt2;
} Line3, *PLine3;





typedef struct _TerrainData {
    // 地形文件夹，地形纹理文件夹，地形等高文件夹
    CString m_TerrainFolder;
    CString m_TerrainTextureFolder;
    CString m_TerrainContourFolder;
    // 地形纹理，地形等高图
    CString m_TerrainTexture;
    CString m_TerrainContour;
} TerrainData;


// 城市标识数据
typedef struct _CitySymbolData {
    CString m_CitySymbolFolder;
    CString m_CitySymbolTex;

    float m_CitySymbolPosX;
    float m_CitySymbolPosY;
    float m_CitySymbolPosZ;
} CitySymbolData;


// 景观树数据
typedef struct _TreeModelData {
    CString m_TreeModelFolder;
    CString m_TreeModelTex;

    float m_TreeModelPosX;
    float m_TreeModelPosY;
    float m_TreeModelPosZ;
} TreeModelData;

// 3DS 模型
typedef struct _T3DModelData {
    CString m_3DModelFolder;
    CString m_3DModelPath;

    float m_3DModelPosX;
    float m_3DModelPosY;
    float m_3DModelPosZ;

    float m_3DModelRotX;
    float m_3DModelRotY;
    float m_3DModelRotZ;

    float m_3DModelScale;

} T3DModelData;



#endif  // SYMBOL_DEFINES_H