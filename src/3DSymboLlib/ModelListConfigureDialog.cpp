#include "stdafx.h"
#include "3DSymbolLibNew.h"
#include "ModelListConfigureDialog.h"
#include "afxdialogex.h"
#include "GlobalVariable.h"

// ModelListConfigureDialog 对话框

// 仿函数,用于比较字符串大小,对List进行排序
class MyCompare {
  public:
    bool operator()(const string str1, const string str2) {
        return (str1 < str2);
    }
};

IMPLEMENT_DYNAMIC(ModelListConfigureDialog, CDialog)

ModelListConfigureDialog::ModelListConfigureDialog(CWnd* pParent /*=NULL*/)
    : CDialog(ModelListConfigureDialog::IDD, pParent) {
    // Empty
}

ModelListConfigureDialog::~ModelListConfigureDialog() {
    // Empty
}

void ModelListConfigureDialog::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TREE_CONGIGURE_MODELLIST, m_configureModeListTree);
    DDX_Control(pDX, IDC_STATIC_IMAGE, m_image);
}


BEGIN_MESSAGE_MAP(ModelListConfigureDialog, CDialog)
    ON_BN_CLICKED(IDOK, &ModelListConfigureDialog::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &ModelListConfigureDialog::OnBnClickedCancel)
    ON_WM_CONTEXTMENU()
    ON_COMMAND(ID_EDIT_DELETE_SYMBOL, &ModelListConfigureDialog::OnEditDeleteSymbol)
    ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_CONGIGURE_MODELLIST, &ModelListConfigureDialog::OnTvnSelchangedTreeCongigureModellist)
    ON_COMMAND(ID_EDIT_ADD_SYMBOL, &ModelListConfigureDialog::OnEditAddSymbol)
END_MESSAGE_MAP()


// ModelListConfigureDialog 消息处理程序


void ModelListConfigureDialog::OnBnClickedOk() {
    // TODO(jason): 在此添加控件通知处理程序代码
    for (int32 i = 0; i < g_modelKindNumber; ++i) {
        // Update only changed
        if (g_modelTree[i].isChanged) {
            CoInitialize(NULL);  // 初始化COM。
            CComPtr<IXMLDOMDocument> spXMLDOM;
            // 创建解析器实例。
            HRESULT hr = spXMLDOM.CoCreateInstance(_uuidof(DOMDocument));
            VARIANT_BOOL bSuccess = false;
            // 装载XML文档。
            hr = spXMLDOM->load(CComVariant(g_point_symbolConfigureFile.c_str()), &bSuccess);
            int32 strLen = g_modelTree[i]._noteDirectory.length();
            // "/root/XXX/*" ==> "/root/XXX"
            string subStr = g_modelTree[i]._noteDirectory.substr(0, strLen - 2);
            CComBSTR bstrSS(subStr.c_str());
            CComPtr<IXMLDOMNode> spDevice;
            hr = spXMLDOM->selectSingleNode(bstrSS, &spDevice);  // 搜索bstrSS。
            CComPtr<IXMLDOMElement> spRootEle;
            spXMLDOM->get_documentElement(&spRootEle);  // 根节点
            CComPtr<IXMLDOMNodeList> spNodeList;
            spRootEle->selectNodes(_bstr_t(g_modelTree[i]._noteDirectory.c_str()), &spNodeList);
            long nLen;  // 子节点数  // NOLINT
            spNodeList->get_length(&nLen);  // 子节点数
            for (int64 j = 0; j != nLen; ++j) {  // 遍历子节点
                CComPtr<IXMLDOMNode> spNode;
                spNodeList->get_item(j, &spNode);
                // 删除所有子节点(item)
                spDevice->removeChild(spNode, NULL);
            }
            // 从List中添加结点
            list<string>::iterator iter;
            for (iter = g_modelList[i].begin(); iter != g_modelList[i].end(); ++iter) {
                CComPtr<IXMLDOMNode> spModelNode;
                // 创建"Model"节点。
                hr = spXMLDOM->createNode(CComVariant(NODE_ELEMENT), CComBSTR("item"), NULL, & spModelNode);
                CComPtr<IXMLDOMNode> spInsertedNode;
                hr = spDevice->appendChild(spModelNode, &spInsertedNode);
                CString strID = (*iter).c_str();
                // 设置"Model"的文本。
                spInsertedNode->put_text(strID.AllocSysString());
            }
            // 保存文档。
            spXMLDOM->save(CComVariant(g_point_symbolConfigureFile.c_str()));
            // 结束对COM的使用。
            CoUninitialize();
        }
    }
    CDialog::OnOK();
}


/************************************************************************/
/* Function: 取消的时候将List中被删除的元素重新插入                         */
/************************************************************************/
void ModelListConfigureDialog::OnBnClickedCancel() {
    // TODO(jason): 在此添加控件通知处理程序代码
    for (int32 i = 0; i < g_modelKindNumber; ++i) {
        // add
        list<string>::iterator iter_del;
        for (iter_del = g_delList[i].begin(); iter_del != g_delList[i].end(); ++iter_del) {
            g_modelList[i].push_back(*iter_del);
        }
        g_delList[i].clear();
        // delete
        list<string>::iterator iter_add = g_delList[i].begin();
        while (iter_add != g_delList[i].end()) {
            iter_add = g_delList[i].erase(iter_add);
        }
        g_addList[i].clear();
    }
    CDialog::OnCancel();
}


BOOL ModelListConfigureDialog::OnInitDialog() {
    CDialog::OnInitDialog();
    // ============================================
    // 从list中读取信息显示在tree中
    // ============================================
    for (int32 i = 0; i < g_modelKindNumber; ++i) {
        g_modelTree[i].isChanged = 0;
        // 排序
        g_modelList[i].sort(MyCompare());
    }
    hRoot = m_configureModeListTree.InsertItem("符号列表配置", 0, 0);
    LPCTSTR item[5];    // {"3DS Model","City Symbol","Tree Model","3D Tree Model","Weather Symbol"};
    for (int32 i = 0; i < g_modelKindNumber; ++i) {
        item[i] = g_modelTree[i]._item.c_str();
    }
    for (int32 i = 0; i < g_modelKindNumber; ++i) {
        hCataItem = m_configureModeListTree.InsertItem(item[i], 1, 1, hRoot, TVI_LAST);
        list<string>::iterator iter;
        for (iter = g_modelList[i].begin(); iter != g_modelList[i].end(); ++iter) {
            hArtItem = m_configureModeListTree.InsertItem((*iter).c_str(), 2, 2, hCataItem, TVI_LAST);
        }
    }
    return TRUE;
}


/************************************************************************/
/* Function: 弹出菜单                                                   */
/************************************************************************/
void ModelListConfigureDialog::OnContextMenu(CWnd* pWnd, CPoint point) {
    // TODO(jason): 在此处添加消息处理程序代码
    if (point != CPoint(-1, -1)) {
        CPoint ptTree = point;
        m_configureModeListTree.ScreenToClient(&ptTree);
        UINT flags = 0;
        HTREEITEM hTreeItem = m_configureModeListTree.HitTest(ptTree, &flags);
        if (hTreeItem != NULL) {
            m_configureModeListTree.SelectItem(hTreeItem);
            CMenu menu;
            menu.LoadMenu(IDR_MENU_POPUP_CONFIGURE_EDIT);
            CMenu* pMenu = menu.GetSubMenu(0);
            m_configureModeListTree.SetFocus();
            // ========================================================
            HTREEITEM selectedItem = m_configureModeListTree.GetSelectedItem();
            HTREEITEM selectedParentItem = m_configureModeListTree.GetParentItem(selectedItem);
            HTREEITEM rootItem = m_configureModeListTree.GetRootItem();
            if (rootItem == selectedParentItem) {
                // MessageBox("二级节点","",MB_OK);
                pMenu->EnableMenuItem(ID_EDIT_DELETE_SYMBOL, MF_DISABLED | MF_GRAYED);
            }
            if (rootItem == m_configureModeListTree.GetParentItem(selectedParentItem)) {
                pMenu->EnableMenuItem(ID_EDIT_ADD_SYMBOL, MF_DISABLED | MF_GRAYED);
                // MessageBox("3级节点","",MB_OK);
            }
            if (rootItem == selectedItem) {
                // MessageBox("根节点","",MB_OK);
                pMenu->EnableMenuItem(ID_EDIT_ADD_SYMBOL, MF_DISABLED | MF_GRAYED);
                pMenu->EnableMenuItem(ID_EDIT_DELETE_SYMBOL, MF_DISABLED | MF_GRAYED);
            }
            // ========================================================
            pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
        }
    }
}


/************************************************************************/
/* Function: tree control 上右击菜单，delete                                */
/************************************************************************/
void ModelListConfigureDialog::OnEditDeleteSymbol() {
    // TODO(jason): 在此添加命令处理程序代码
    HTREEITEM selectItem = m_configureModeListTree.GetSelectedItem();
    CString selectItemText = m_configureModeListTree.GetItemText(selectItem);
    HTREEITEM parentItem = m_configureModeListTree.GetParentItem(selectItem);
    CString parentItemText = m_configureModeListTree.GetItemText(parentItem);
    // delete from tree control
    m_configureModeListTree.DeleteItem(selectItem);
    for (int32 i = 0; i < g_modelKindNumber; ++i) {
        if (parentItemText == g_modelTree[i]._item.c_str()) {
            list<string>::iterator iter = g_modelList[i].begin();
            while (iter != g_modelList[i].end()) {
                if ((*iter).c_str() == selectItemText) {
                    // delete from model list
                    iter = g_modelList[i].erase(iter);
                    list<string>::iterator tmpIter;
                    for (tmpIter = g_addList[i].begin(); tmpIter != g_addList[i].end();) {
                        if ((*tmpIter).c_str() == selectItemText) {
                            tmpIter = g_addList[i].erase(tmpIter);
                        } else {
                            ++tmpIter;
                        }
                    }
                    if (tmpIter == g_addList[i].end()) {
                        g_delList[i].push_back(LPCSTR(selectItemText));
                    }
                    g_modelTree[i].isChanged = 1;
                } else {
                    ++iter;
                }
            }
        }
    }
}


/************************************************************************/
/* Function: tree control 上右击菜单，add                                   */
/************************************************************************/
void ModelListConfigureDialog::OnEditAddSymbol() {
    // TODO(jason): 在此添加命令处理程序代码
    HTREEITEM selectItem = m_configureModeListTree.GetSelectedItem();
    CString selectItemText = m_configureModeListTree.GetItemText(selectItem);
    // 文件对话框标题,格式过滤器,默认路径
    CString l_title, l_filter, l_initialDir;
    CString l_tmp = "\\";
    int32 l_symbolType = -1;
    if (selectItemText == g_modelTree[0]._item.c_str()) {
        l_symbolType = 0;
        l_title = "添加3DS模型";
        l_filter = "3DS模型(*.BMP)|*.BMP|";
        l_initialDir = g_sceneDataPath.c_str() + l_tmp + g_symbolFolder._3DSFolder.c_str();
    }
    if (selectItemText == g_modelTree[1]._item.c_str()) {
        l_symbolType = 1;
        l_title = "添加城市符号";
        l_filter = "城市符号(*.png)|*.png|";
        l_initialDir = g_sceneDataPath.c_str() + l_tmp + g_symbolFolder._CityFolder.c_str();
    }
    if (selectItemText == g_modelTree[2]._item.c_str()) {
        l_symbolType = 2;
        l_title = "添加景观树";
        l_filter = "景观树(*.BMP)|*.BMP|";
        l_initialDir = g_sceneDataPath.c_str() + l_tmp + g_symbolFolder._TreeFolder.c_str();
    }
    if (selectItemText == g_modelTree[3]._item.c_str()) {
        l_symbolType = 3;
        l_title = "添加3D景观树";
        l_filter = "3D景观树(*.BMP)|*.BMP|";
        l_initialDir = g_sceneDataPath.c_str() + l_tmp + g_symbolFolder._3DTreeFolder.c_str();
    }
    if (selectItemText == g_modelTree[4]._item.c_str()) {
        l_symbolType = 4;
        l_title = "添加天气符号";
        l_filter = "天气符号(*.BMP)|*.BMP|";
        l_initialDir = g_sceneDataPath.c_str() + l_tmp + g_symbolFolder._WeatherFolder.c_str();
    }
    CString file;
    CFileDialog FileDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, l_filter, NULL);
    // 默认打开配置中的文件路径
    FileDialog.m_ofn.lpstrInitialDir = l_initialDir;
    FileDialog.m_ofn.lpstrTitle = l_title;
    if ((FileDialog.DoModal() == IDOK) && (l_symbolType != -1)) {
        file = FileDialog.GetFileName();
        int32 index = file.Find('.');
        CString ret = file.Left(index);
        list<string>::iterator iter = g_modelList[l_symbolType].begin();
        while (iter != g_modelList[l_symbolType].end()) {
            if ((*iter).c_str() == ret) {
                MessageBox("请不要重复添加相同的符号!", "Warning", MB_OK);
                return;
            } else {
                ++iter;
            }
        }
        if (iter == g_modelList[l_symbolType].end()) {
            g_modelList[l_symbolType].push_back(LPCSTR(ret));
            list<string>::iterator tmpIter;
            for (tmpIter = g_delList[l_symbolType].begin(); tmpIter != g_delList[l_symbolType].end();) {
                if ((*tmpIter).c_str() == ret) {
                    tmpIter = g_delList[l_symbolType].erase(tmpIter);
                } else {
                    ++tmpIter;
                }
            }
            if (tmpIter == g_delList[l_symbolType].end()) {
                g_addList[l_symbolType].push_back(LPCSTR(ret));
            }
            m_configureModeListTree.InsertItem(ret, 2, 2, selectItem, TVI_LAST);
            g_modelTree[l_symbolType].isChanged = 1;
        }
    }
}


/************************************************************************/
/* Function: 响应选中改变事件,显示相应的图片                                */
/************************************************************************/
void ModelListConfigureDialog::OnTvnSelchangedTreeCongigureModellist(NMHDR* pNMHDR, LRESULT* pResult) {
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    *pResult = 0;
    HTREEITEM selectItem = m_configureModeListTree.GetSelectedItem();
    CString selectItemText = m_configureModeListTree.GetItemText(selectItem);
    HTREEITEM parentItem = m_configureModeListTree.GetParentItem(selectItem);
    CString parentItemText = m_configureModeListTree.GetItemText(parentItem);
    CString imgPathAndName;
    CString tmp = "\\";
    for (int32 i = 0; i < g_modelKindNumber; ++i) {
        if (parentItemText == g_modelTree[i]._item.c_str()) {
            if (0 == i) {
                imgPathAndName = g_sceneDataPath.c_str() + tmp + g_symbolFolder._3DSFolder.c_str() + tmp + selectItemText + ".bmp";
                // MessageBox(imgPathAndName,"");
            } else if (1 == i) {  // PNG
                imgPathAndName = g_sceneDataPath.c_str() + tmp + g_symbolFolder._CityFolder.c_str() + tmp + selectItemText + ".png";
                // MessageBox(imgPathAndName,"");
                GetDlgItem(IDC_STATIC_IMAGE)->GetParent()->RedrawWindow();
                CWnd* pWnd;
                pWnd = GetDlgItem(IDC_STATIC_IMAGE);  // 这里是获得控件句柄
                CDC* pDC = pWnd->GetDC();
                HDC hDC = pDC->m_hDC;
                CRect rect_frame;
                pWnd->GetClientRect(&rect_frame);
                CImage image;
                image.Load(imgPathAndName);
                ::SetStretchBltMode(hDC, HALFTONE);
                ::SetBrushOrgEx(hDC, 0, 0, NULL);
                image.Draw(hDC, rect_frame);
                ReleaseDC(pDC);  // 释放picture控件的DC
            } else if (2 == i) {
                imgPathAndName = g_sceneDataPath.c_str() + tmp + g_symbolFolder._TreeFolder.c_str() + tmp + selectItemText + ".bmp";
                // MessageBox(imgPathAndName,"");
            } else if (3 == i) {
                imgPathAndName = g_sceneDataPath.c_str() + tmp + g_symbolFolder._3DTreeFolder.c_str() + tmp + selectItemText + ".bmp";
                // MessageBox(imgPathAndName,"");
            } else if (4 == i) {
                imgPathAndName = g_sceneDataPath.c_str() + tmp + g_symbolFolder._WeatherFolder.c_str() + tmp + selectItemText + ".bmp";
                // MessageBox(imgPathAndName,"");
            }
            // BMP
            if (i != 1) {
                CRect rect;
                CDC* pdc = GetDC();
                GetDlgItem(IDC_STATIC_IMAGE)->GetWindowRect(rect);
                this->ScreenToClient(rect);
                drawBitmapFromFile(imgPathAndName, pdc, rect);
            }
        }
    }
}


/************************************************************************/
/* Function: 将选中的bmp纹理影像在控件上绘制                                */
/************************************************************************/
void ModelListConfigureDialog::drawBitmapFromFile(CString bitmapFilePath, CDC* pDC, CRect rect) {
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



