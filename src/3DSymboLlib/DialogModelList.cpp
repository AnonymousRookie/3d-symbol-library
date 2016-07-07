#include "stdafx.h"
#include "3DSymbolLibNew.h"
#include "DialogModelList.h"
#include "afxdialogex.h"


#include <io.h>
#include <vector>

// CDialogModelList 对话框

IMPLEMENT_DYNAMIC(CDialogModelList, CDialog)

CDialogModelList::CDialogModelList(CWnd* pParent /*=NULL*/)
    : CDialog(CDialogModelList::IDD, pParent) {
    // Empty
}

CDialogModelList::~CDialogModelList() {
    // Empty
}

void CDialogModelList::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_MODEL, m_listCtlModel);
}


BEGIN_MESSAGE_MAP(CDialogModelList, CDialog)
    ON_WM_CREATE()
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_MODEL, &CDialogModelList::OnLvnItemchangedListModel)
END_MESSAGE_MAP()


// CDialogModelList 消息处理程序


BOOL CDialogModelList::OnInitDialog() {
    CDialog::OnInitDialog();
    // 通过配置文件加载符号
    string fileDirAndName;
    if (m_type == "3DS") {
        string _3dsFile;
        list<string>::iterator iter = g_modelList[0].begin();
        while (iter != g_modelList[0].end()) {
            string tmp = "\\";
            fileDirAndName = LPCTSTR(m_Dir) + tmp + (*iter) + LPCTSTR(m_format);
            _3dsFile = LPCTSTR(m_Dir) + tmp + (*iter) + LPCTSTR(".3DS");
            // 确保模型文件(.3DS) 和 纹理文件(.bmp)都存在
            if (PathFileExists(fileDirAndName.c_str()) && PathFileExists(_3dsFile.c_str())) {
                m_fileNameArray.Add((*iter).c_str() + m_format);
            }
            ++iter;
        }
    } else if (m_type == "City") {
        list<string>::iterator iter = g_modelList[1].begin();
        while (iter != g_modelList[1].end()) {
            string tmp = "\\";
            fileDirAndName = LPCTSTR(m_Dir) + tmp + (*iter) + LPCTSTR(m_format);
            if (PathFileExists(fileDirAndName.c_str())) {
                m_fileNameArray.Add((*iter).c_str() + m_format);
            }
            ++iter;
        }
    } else if (m_type == "Tree") {
        list<string>::iterator iter = g_modelList[2].begin();
        while (iter != g_modelList[2].end()) {
            string tmp = "\\";
            fileDirAndName = LPCTSTR(m_Dir) + tmp + (*iter) + LPCTSTR(m_format);
            if (PathFileExists(fileDirAndName.c_str())) {
                m_fileNameArray.Add((*iter).c_str() + m_format);
            }
            ++iter;
        }
    } else if (m_type == "3DTree") {
        list<string>::iterator iter = g_modelList[3].begin();
        while (iter != g_modelList[3].end()) {
            string tmp = "\\";
            fileDirAndName = LPCTSTR(m_Dir) + tmp + (*iter) + LPCTSTR(m_format);
            if (PathFileExists(fileDirAndName.c_str())) {
                m_fileNameArray.Add((*iter).c_str() + m_format);
            }
            ++iter;
        }
    } else if (m_type == "Weather") {
        list<string>::iterator iter = g_modelList[4].begin();
        while (iter != g_modelList[4].end()) {
            string tmp = "\\";
            fileDirAndName = LPCTSTR(m_Dir) + tmp + (*iter) + LPCTSTR(m_format);
            if (PathFileExists(fileDirAndName.c_str())) {
                m_fileNameArray.Add((*iter).c_str() + m_format);
            }
            ++iter;
        }
    } else if (m_type == "StoneTexture") {  // 石头纹理
        // 获取文件夹下所有指定类型文件
        _finddata_t fileDir;
        char* dir = new char[m_Dir.GetLength() + strlen("\\*") + m_format.GetLength()];  // "d:\\temp\\*.*";
        sprintf(dir, m_Dir + "\\*" + m_format);  // NOLINT
        int64 lfDir;
        int32 fileNum = 0;
        // vector<CString> fileName;
        // 搜索与指定的文件名称匹配的第一个实例，若成功则返回第一个实例的句柄，否则返回-1L
        if ((lfDir = _findfirst(dir, &fileDir)) == -1l) {
            printf("No file is found\n");
        } else {
            printf("file list:\n");
            do {
                printf("%s\n", fileDir.name);  // XXX.format
                m_fileNameArray.Add(fileDir.name);
                ++fileNum;
            } while (_findnext(lfDir, &fileDir) == 0);
        }
        _findclose(lfDir);
    }
    // 填充ClistCtrl 和CimageList
    m_listCtlModel.SetExtendedStyle(LVS_ALIGNTOP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    // m_listCtlModel.SetIconSpacing(CSize(80, 80));     // set pictures spacing
    m_imgListModel.Create(50, 50, ILC_COLOR32 | ILC_MASK, m_fileNameArray.GetSize(), m_fileNameArray.GetSize());
    m_listCtlModel.SetImageList(&m_imgListModel, LVSIL_NORMAL);
    DrawThumbnails();
    return TRUE;  // return TRUE  unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}


void  CDialogModelList::DrawThumbnails() {
    CBitmap*    pImage = NULL;
    HBITMAP     hBmp = NULL;
    CString     strPath;
    int32         i;
    // no images
    if (m_fileNameArray.IsEmpty())
        return;
    // set the length of the space between thumbnails
    // you can also calculate and set it based on the length of your list control
    int32 nGap = 6;
    // hold the window update to avoid flicking
    m_listCtlModel.SetRedraw(FALSE);
    // reset our image list
    for (i = 0; i < m_imgListModel.GetImageCount(); i++)
        m_imgListModel.Remove(i);
    // remove all items from list view
    if (m_listCtlModel.GetItemCount() != 0)
        m_listCtlModel.DeleteAllItems();
    // set the size of the image list
    m_imgListModel.SetImageCount(m_fileNameArray.GetSize());
    i = 0;
    // draw the thumbnails
    for (int32 i = 0; i < m_fileNameArray.GetSize(); i++) {
        // load the bitmap
        strPath.Format(TEXT("%s\\%s"), m_Dir, m_fileNameArray.GetAt(i));
        USES_CONVERSION;
        Bitmap img(A2W(strPath));
        Bitmap* pThumbnail = static_cast<Bitmap*>(img.GetThumbnailImage(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, NULL, NULL));
        int32 H = img.GetHeight();
        // attach the thumbnail bitmap handle to an CBitmap object
        pThumbnail->GetHBITMAP(Color(255, 255, 255), &hBmp);
        pImage = new CBitmap();
        pImage->Attach(hBmp);
        // add bitmap to our image list
        m_imgListModel.Replace(i, pImage, NULL);
        // put item to display
        // set the image file name as item text
        CString disName = m_fileNameArray.GetAt(i).Left(m_fileNameArray.GetAt(i).Find("."));
        m_listCtlModel.InsertItem(i, disName, i);
        delete pImage;
        delete pThumbnail;
    }
    // let's show the new thumbnails
    m_listCtlModel.SetRedraw();
}

// 相应ClistCtrl 消息
void CDialogModelList::OnLvnItemchangedListModel(NMHDR* pNMHDR, LRESULT* pResult) {
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    m_selectItem = m_listCtlModel.GetItemText(pNMLV->iItem, pNMLV->iSubItem);
    *pResult = 0;
}
