/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		ExactInference.h
//功  能：		定义应用程序类
//开发者：		高志强
//日  期：		2021年03月01日
//更  新：		
//长  度：		40行
/////////////////////////////////////////////////////////////////////////////////////////////

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