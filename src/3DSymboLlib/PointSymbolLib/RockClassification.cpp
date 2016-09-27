/************************************************************************/
/*      岩石分类对话框类                                                    */
/************************************************************************/
#include "stdafx.h"
#include "../3DSymbolLibNew.h"
#include "RockClassification.h"
#include "afxdialogex.h"
#include <io.h>

IMPLEMENT_DYNAMIC(CRockClassification, CDialog)

CRockClassification::CRockClassification(CWnd* pParent /*=NULL*/)
    : CDialog(CRockClassification::IDD, pParent) {
}

CRockClassification::~CRockClassification() {
}

void CRockClassification::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TREE_ROCK_LIST, m_Rock_Tree_List);
    DDX_Control(pDX, IDC_STATIC_IMAGE, m_image);
}


BEGIN_MESSAGE_MAP(CRockClassification, CDialog)

    ON_BN_CLICKED(IDOK, &CRockClassification::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &CRockClassification::OnBnClickedCancel)
    ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_ROCK_LIST, &CRockClassification::OnSelchangedTreeRockList)
END_MESSAGE_MAP()



BOOL CRockClassification::OnInitDialog() {
    CDialog::OnInitDialog();
    CString tmp = "\\";
    CString topItem = "岩石分类";
    CString RockType[3] = {"岩浆岩", "沉积岩", "变质岩"};
    hRoot = m_Rock_Tree_List.InsertItem(topItem, 0, 0);
    for (int32 i = 0; i < 3; ++i) {
        hCataItem = m_Rock_Tree_List.InsertItem(RockType[i], 1, 1, hRoot, TVI_LAST);
        m_Dir = g_sceneDataPath.c_str() + tmp + topItem + tmp + RockType[i];
        if (1) {
            // 获取文件夹下所有指定类型文件
            _finddata_t fileDir;
            char* dir = new char[m_Dir.GetLength() + strlen("\\*.BMP")];
            sprintf(dir, m_Dir + "\\*.BMP");  // NOLINT
            int64 lfDir;
            int32 fileNum = 0;
            // 搜索与指定的文件名称匹配的第一个实例，若成功则返回第一个实例的句柄，否则返回-1L
            if ((lfDir = _findfirst(dir, &fileDir)) == -1l) {
                printf("No file is found\n");
            } else {
                printf("file list:\n");
                do {
                    printf("%s\n", fileDir.name);  // XXX.format
                    hArtItem = m_Rock_Tree_List.InsertItem(fileDir.name, 2, 2, hCataItem, TVI_LAST);
                    ++fileNum;
                } while (_findnext(lfDir, &fileDir) == 0);
            }
            _findclose(lfDir);
        }
    }
    return TRUE;
}



void CRockClassification::OnBnClickedOk() {
    // TODO(jason): 在此添加控件通知处理程序代码
    CDialog::OnOK();
    CString tmp = "\\";
    CString topItem = "岩石分类";
    HTREEITEM selectItem = m_Rock_Tree_List.GetSelectedItem();
    CString selectItemText = m_Rock_Tree_List.GetItemText(selectItem);
    HTREEITEM parentItem = m_Rock_Tree_List.GetParentItem(selectItem);
    CString parentItemText = m_Rock_Tree_List.GetItemText(parentItem);
    m_selectItem = selectItemText;
    m_Dir = g_sceneDataPath.c_str() + tmp + topItem + tmp + parentItemText;
}


void CRockClassification::OnBnClickedCancel() {
    // TODO(jason): 在此添加控件通知处理程序代码
    CDialog::OnCancel();
}


void CRockClassification::OnSelchangedTreeRockList(NMHDR* pNMHDR, LRESULT* pResult) {
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    // TODO(jason): 在此添加控件通知处理程序代码
    *pResult = 0;
    HTREEITEM selectItem = m_Rock_Tree_List.GetSelectedItem();
    CString selectItemText = m_Rock_Tree_List.GetItemText(selectItem);
    HTREEITEM parentItem = m_Rock_Tree_List.GetParentItem(selectItem);
    CString parentItemText = m_Rock_Tree_List.GetItemText(parentItem);
    CString topItem = "岩石分类";
    CString RockType[3] = {"岩浆岩", "沉积岩", "变质岩"};
    CString imgPathAndName;
    CString tmp = "\\";
    for (int32 i = 0; i < 3; ++i) {
        if (parentItemText == RockType[i]) {
            imgPathAndName = g_sceneDataPath.c_str() + tmp + topItem + tmp + RockType[i] + tmp + selectItemText;
            // BMP
            {
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
void CRockClassification::drawBitmapFromFile(CString bitmapFilePath, CDC* pDC, CRect rect) {
    HANDLE   filehandle =::LoadImage(NULL, bitmapFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);  // 加载影像文件
    if (filehandle != NULL) {
        CBitmap   bmp;
        if (bmp.Attach(filehandle)) {
            BITMAP   bmpInfo;
            bmp.GetBitmap(&bmpInfo);            // 获取资源位图信息
            CDC   dcMemory;
            dcMemory.CreateCompatibleDC(pDC);   // 创建一个与特定设备场景一致的内存设备场景
            dcMemory.SelectObject(&bmp);        // 选择bmp对象到指定的设备上下文环境中,该新对象替换先前的相同类型的对象
            // 设置指定设备环境中的位图拉伸模式. HALFTONE：将源矩形区中的像素映射到目标矩形区的像素块中，
            // 覆盖目标像素块的一般颜色与源像素的颜色接近。
            // StretchBlt():源矩形中复制一个位图到目标矩形,必要时按目前目标设备设置的模式进行图像的拉伸或压缩。
            pDC->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(), &dcMemory, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
            bmp.Detach();   // 销毁bmp对象
        }
    }
}
