
// 3DSymbolLibNew.h : 3DSymbolLibNew Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
//#include "GdiPlus.h"
#include "stdafx.h"
#include "GlobalVariable.h"

#include "ProjectFileSetting.h"

// ��д�����ļ�Buffer��С
#define MAX_SIZE 256


// CMy3DSymbolLibNewApp:
// �йش����ʵ�֣������ 3DSymbolLibNew.cpp
//

class CMy3DSymbolLibNewApp : public CWinAppEx
{
public:
	CMy3DSymbolLibNewApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

	GdiplusStartupInput   m_gdiplusStartupInput;   //ֻ��Ҫ�ڳ��������ʼ��ʼ��һ��
	ULONG_PTR             m_gdiplusToken;          //ֻ��Ҫ�ڳ��������ʼ��ʼ��һ��
};

extern CMy3DSymbolLibNewApp theApp;
