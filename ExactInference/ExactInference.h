/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		ExactInference.h
//��  �ܣ�		����Ӧ�ó�����
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��01��
//��  �£�		
//��  �ȣ�		40��
/////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// ����Ӧ�ó�����CExactInferenceApp: 
class CExactInferenceApp : public CWinApp
{
public:
	CExactInferenceApp();			//���캯��

// ��д
public:
	virtual BOOL InitInstance();	//��ʼ��Ӧ�ó���ʵ��

// ʵ��

	DECLARE_MESSAGE_MAP()			//��ʼ��Ϣӳ��

// �������ݳ�Ա
public:
	CString m_sWorkPath;			//����·��
};

extern CExactInferenceApp theApp;	//Ψһ��Ӧ�ó������