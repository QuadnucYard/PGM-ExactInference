////////////////////////////////////////////////////////////////////////////////
// ExactInference.h
// ����Ӧ�ó�����
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include <cstring>

// ����Ӧ�ó�����CExactInferenceApp: 
class CExactInferenceApp : public CWinApp
{
public:
	CExactInferenceApp();

public:
	virtual BOOL InitInstance();	//��ʼ��Ӧ�ó���ʵ��

	DECLARE_MESSAGE_MAP()			//��ʼ��Ϣӳ��
};

extern CExactInferenceApp theApp;	//Ψһ��Ӧ�ó������