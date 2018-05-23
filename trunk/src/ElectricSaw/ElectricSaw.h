
// ElectricSaw.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// 判断是否在测试环境下
 #ifdef DEBUG 

	#pragma comment(lib, "../../lib/DataManagerd.lib")
	#pragma comment(lib, "../../lib/FileReadWrited.lib")
	#pragma comment(lib, "../../lib/tinyxmld.lib")
	#pragma  message(".......................................当前为debug版本")

#else

	#pragma comment(lib, "../../lib/DataManager.lib")
	#pragma comment(lib, "../../lib/FileReadWrite.lib")
	#pragma comment(lib, "../../lib/tinyxml.lib")
	#pragma  message(".......................................当前为release版本")

 #endif



#define WM_REFRESH_PANEL_VIEW WM_USER+1
// CElectricSawApp:
// 有关此类的实现，请参阅 ElectricSaw.cpp
//

class CElectricSawApp : public CWinApp
{
public:
	CElectricSawApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()

protected:
	Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_pGdiToken;
public:
	virtual int ExitInstance();
};

extern CElectricSawApp theApp;