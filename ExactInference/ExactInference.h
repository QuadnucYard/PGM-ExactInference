////////////////////////////////////////////////////////////////////////////////
// ExactInference.h
// 定义应用程序类
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include <cstring>

// 定义应用程序类CExactInferenceApp: 
class CExactInferenceApp : public CWinApp
{
public:
	CExactInferenceApp();

public:
	virtual BOOL InitInstance();	//初始化应用程序实例

	DECLARE_MESSAGE_MAP()			//开始消息映射
};

extern CExactInferenceApp theApp;	//唯一的应用程序对象