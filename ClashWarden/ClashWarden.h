
// ClashWarden.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CClashWardenApp:
// 有关此类的实现，请参阅 ClashWarden.cpp
//

class CClashWardenApp : public CWinApp
{
public:
	CClashWardenApp();

// 重写
public:
	virtual BOOL InitInstance();
	CString path;
	int tunmode;
	CString iniFile;
	int startup;
	int sysproxy;
	int subscribe;
	int upwproxy;
	int mintotray;
	int closetotray;

// 实现

	DECLARE_MESSAGE_MAP();
};

extern CClashWardenApp theApp;
