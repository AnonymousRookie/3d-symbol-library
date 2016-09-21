#pragma once


#define _CRT_SECURE_NO_WARNINGS

#ifndef  WINVER
#define WINVER 0x0500
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501  // 控制PNG图片透明显示
#endif

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0510
#endif

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif  // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持

#include <atlimage.h>

#include "define.h"

#include "DesingScheme.h"
extern CDesingScheme myDesingScheme;



#include <gl\glew.h>
#include <gl\gl.h>      // OpenGL32库的头文件
#include <gl\glu.h>     // GLu32库的头文件
#include <gl\glaux.h>   // GLaux库的头文件
#include <gl\glut.h>
#include <gl\glext.h>
#include <afxdlgs.h>


// use google log
#ifdef ERROR
#undef ERROR  // Windows.h
#endif  // ERROR

#define GOOGLE_GLOG_DLL_DECL
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include "glog/logging.h"
#pragma comment(lib, "libglog_static.lib")

#define LOGGER_INFO     LOG(INFO)
#define LOGGER_WARNING  LOG(WARNING)
#define LOGGER_ERROR    LOG(ERROR)
// LOGGER_INFO << "..." << "...";


// CProjectFileSetting 自定义消息宏

#define WM_NEW_PROJECT          WM_USER+104     // 单选按钮 新建工程 选中
#define WM_OPEN_PROJECT         WM_USER+105     // 单选按钮 打开工程 选中

#define WM_PROJECT_SET_OK       WM_USER+106     // 单选按钮 打开工程 选中



#define MAP_W       32         // size of map aint64 x-axis 32， 32*32地面方阵
#define MAP_SCALE   24.0f      // the scale of the terrain map，边长为24
#define MAP         MAP_W*MAP_SCALE/2
#define PAI         3.1415926       // 定义π常量
#define HDANGLE     52.706     // 定义1弧度等于多少度(1弧度=180/PAI)
#define PAI_D180    PAI/180    // 定义1度等于多少弧度(1度=PAI/180弧度)
#define MODEL_NUM_MAX 30


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


#include <gdiplus.h>             // GDI+声明，可以GDI/GDI+混合使用
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;  // NOLINT