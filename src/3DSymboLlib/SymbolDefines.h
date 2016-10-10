#ifndef SYMBOL_DEFINES_H
#define SYMBOL_DEFINES_H

#include <vector>

// SkyBox Tex
enum {TP = 0, LF, BK, RT, FR};
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


/************************************************************************/
/* 面符号三角化                                                         */
/************************************************************************/

typedef struct _Triangle {
    Point3 pt1;
    Point3 pt2;
    Point3 pt3;
} Triangle, *PTriangle;


// 四边形
typedef struct _Area_4 {
    Point3 pt1;
    Point3 pt2;
    Point3 pt3;
    Point3 pt4;

    // 保存所有多边形内部完整的三角形
    vector<Triangle> TrianglesInPolygonVecotr;
    // 保存所有局部三角化了的三角形(三角形只有1个点在多边形内, 且多边形的某条边与三角形有2个交点)
    vector<Triangle> LocalTrianglesVecotr1;
    // 保存所有局部三角化了的三角形(三角形只有2个点在多边形内, 且多边形的某条边与三角形有2个交点)
    vector<Triangle> LocalTrianglesVecotr2;
    // 保存所有局部三角化了的三角形(三角形只有1个点在多边形内, 且多边形的1个端点在三角形中)
    vector<Triangle> LocalTrianglesVecotr1_1;
    // 保存所有局部三角化了的三角形(三角形只有2个点在多边形内, 且多边形的1个端点在三角形中)
    vector<Triangle> LocalTrianglesVecotr2_1;
    // 保存所有局部三角化了的三角形(某三角形没有点在多边形内, 但多边形的1个端点在三角形中)
    vector<Triangle> LocalTrianglesVecotr_last;

    CString area_texture;
    UINT area_texture_rd;

    uint16 deleted;
} Area_4, *PArea_4;

// SkyBox
typedef struct _SkyBox {
    CString m_SkyBoxFolder;
    CString m_SkyBoxKindFolder;
    CString m_SkyBoxTP;
    CString m_SkyBoxLT;
    CString m_SkyBoxRT;
    CString m_SkyBoxBK;
    CString m_SkyBoxFR;

    bool iSkyBoxLoaded_;
    UINT g_texSkyBox[5];
} SkyBox;


#endif  // SYMBOL_DEFINES_H