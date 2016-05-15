// GLFont.h: interface for the CGLFont class.

#if !defined(AFX_GLFONT_H__88F1F000_50F5_452A_B95E_60ED83712FA5__INCLUDED_)
#define AFX_GLFONT_H__88F1F000_50F5_452A_B95E_60ED83712FA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGLFont  
{
public:
	// 常规文字显示。 平面字符显示，不支持汉字
	void Entext(float x,float y, LPCTSTR str,HFONT hFont,float r,float g,float b);
	
	// 3D文字显示。 支持汉字
	void C3dtext(LPCTSTR str,HFONT hFont,float z);
	void Printfc3d(CString strText,HFONT hFont,float z=0.05f);

	// 平面汉字
	void Printftext(int x, int y, LPCTSTR lpszText,HFONT hFont);
	void Settext(float x,float y,CString str,HFONT Font,float r,float g,float b);

	CGLFont();
	virtual ~CGLFont();
protected:
	HFONT hFont; //字体句柄
};

#endif // !defined(AFX_GLFONT_H__88F1F000_50F5_452A_B95E_60ED83712FA5__INCLUDED_)
