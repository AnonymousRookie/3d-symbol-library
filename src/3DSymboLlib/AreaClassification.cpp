#include "stdafx.h"
#include "3DSymbolLibNew.h"
#include "AreaClassification.h"
#include "afxdialogex.h"




#include <io.h>


// CAreaClassification 对话框

IMPLEMENT_DYNAMIC(CAreaClassification, CDialog)

CAreaClassification::CAreaClassification(CWnd* pParent /*=NULL*/)
    : CDialog(CAreaClassification::IDD, pParent) {
}

CAreaClassification::~CAreaClassification() {
}

void CAreaClassification::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_IMAGE, m_Image);
    DDX_Control(pDX, IDC_TREE_AREA_LIST, m_Area_Texture_List);
}


BEGIN_MESSAGE_MAP(CAreaClassification, CDialog)
    ON_BN_CLICKED(IDOK, &CAreaClassification::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &CAreaClassification::OnBnClickedCancel)
    ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_AREA_LIST, &CAreaClassification::OnSelchangedTreeAreaList)
    //  ON_COMMAND(ID_MENU_UPDATE_AREA_TEXTURE, &CAreaClassification::OnMenuUpdateAreaTexture)
    // ON_COMMAND(ID_MENU_AREA_DELETE, &CAreaClassification::OnMenuAreaDelete)
END_MESSAGE_MAP()


// CAreaClassification 消息处理程序


void CAreaClassification::OnBnClickedOk() {
    // TODO(jason): 在此添加控件通知处理程序代码
    CDialog::OnOK();
    CString tmp = "\\";
    CString topItem = "AreaTexture";
    HTREEITEM selectItem = m_Area_Texture_List.GetSelectedItem();
    CString selectItemText = m_Area_Texture_List.GetItemText(selectItem);
    HTREEITEM parentItem = m_Area_Texture_List.GetParentItem(selectItem);
    CString parentItemText = m_Area_Texture_List.GetItemText(parentItem);
    m_selectItem = selectItemText;
    m_Dir = g_sceneDataPath.c_str() + tmp + topItem + tmp + parentItemText;
}


void CAreaClassification::OnBnClickedCancel() {
    // TODO(jason): 在此添加控件通知处理程序代码
    CDialog::OnCancel();
}




void CAreaClassification::OnSelchangedTreeAreaList(NMHDR* pNMHDR, LRESULT* pResult) {
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    // TODO(jason): 在此添加控件通知处理程序代码
    *pResult = 0;
    HTREEITEM selectItem = m_Area_Texture_List.GetSelectedItem();
    CString selectItemText = m_Area_Texture_List.GetItemText(selectItem);
    HTREEITEM parentItem = m_Area_Texture_List.GetParentItem(selectItem);
    CString parentItemText = m_Area_Texture_List.GetItemText(parentItem);
    CString topItem = "AreaTexture";
    CString RockType[1] = {"grassland"};
    CString imgPathAndName;
    CString tmp = "\\";
    for (int32 i = 0; i < 1; ++i) {
        if (parentItemText == RockType[i]) {
            imgPathAndName = g_sceneDataPath.c_str() + tmp + topItem + tmp + RockType[i] + tmp + selectItemText;
            // MessageBox(imgPathAndName,"");
            // BMP
            if (1) {
                CRect rect;
                CDC* pdc = GetDC();
                GetDlgItem(IDC_STATIC_IMAGE)->GetWindowRect(rect);
                this->ScreenToClient(rect);
                drawBitmapFromFile(imgPathAndName, pdc, rect);
            }
        }
    }
}


// 将选中的bmp纹理影像在控件上绘制
void CAreaClassification::drawBitmapFromFile(CString bitmapFilePath, CDC* pDC, CRect rect) {
    HANDLE   filehandle =::LoadImage(NULL, bitmapFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);  // 加载影像文件
    if (filehandle != NULL) {  // 如果加载成功
        CBitmap   bmp;
        if (bmp.Attach(filehandle)) {
            BITMAP   bmpInfo;
            bmp.GetBitmap(&bmpInfo);   // 获取资源位图信息
            CDC   dcMemory;
            dcMemory.CreateCompatibleDC(pDC);   // 创建一个与特定设备场景一致的内存设备场景
            dcMemory.SelectObject(&bmp);   // 选择bmp对象到指定的设备上下文环境中,该新对象替换先前的相同类型的对象
            // 设置指定设备环境中的位图拉伸模式. HALFTONE：将源矩形区中的像素映射到目标矩形区的像素块中，
            // 覆盖目标像素块的一般颜色与源像素的颜色接近。
            // StretchBlt():源矩形中复制一个位图到目标矩形,必要时按目前目标设备设置的模式进行图像的拉伸或压缩。
            pDC->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(), &dcMemory, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
            bmp.Detach();   // 销毁bmp对象
        }
    }
}

BOOL CAreaClassification::OnInitDialog() {
    CDialog::OnInitDialog();
    CString tmp = "\\";
    CString topItem = "AreaTexture";
    CString RockType[1] = {"grassland"};
    hRoot = m_Area_Texture_List.InsertItem(topItem, 0, 0);
    for (int32 i = 0; i < 1; ++i) {
        hCataItem = m_Area_Texture_List.InsertItem(RockType[i], 1, 1, hRoot, TVI_LAST);
        m_Dir = g_sceneDataPath.c_str() + tmp + topItem + tmp + RockType[i];
        if (1) {
            // 获取文件夹下所有指定类型文件
            _finddata_t fileDir;
            char* dir = new char[m_Dir.GetLength() + strlen("\\*.BMP")];
            sprintf(dir, m_Dir + "\\*.BMP");  // NOLINT
            int64 lfDir;
            int32 fileNum = 0;
            // 搜索与指定的文件名称匹配的第一个实例，若成功则返回第一个实例的句柄，否则返回-1L
            if ((lfDir = _findfirst(dir, &fileDir)) == -1l)
                printf("No file is found\n");
            else {
                printf("file list:\n");
                do {
                    printf("%s\n", fileDir.name);  // XXX.format
                    hArtItem = m_Area_Texture_List.InsertItem(fileDir.name, 2, 2, hCataItem, TVI_LAST);
                    ++fileNum;
                } while (_findnext(lfDir, &fileDir) == 0);
            }
            _findclose(lfDir);
        }
    }
    return TRUE;
}

