/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		ExactInferenceDlg_User.cpp
//��  �ܣ�		��Ӧ�û�����
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��02��20��
//��  �£�		
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"					//MFCͷ�ļ�
#include "ExactInference.h"			//Ӧ�ó�����ͷ�ļ�
#include "ExactInferenceDlg.h"		//���Ի�����ͷ�ļ�
#include "CBNSumProduct.h"			//��Ҷ˹���羫ȷ������ͷ�ļ������úͻ�����������


//��  �ƣ�		OnBnClickedButtonBnInit()
//��  �ܣ�		��Ӧ��ʼ������
//��  ����		��
//����ֵ��		��
void CExactInferenceDlg::OnBnClickedButtonBnInit()
{
	//���屴Ҷ˹�������
	CBNSumProduct theBN;
	
	//��ʼ��
	theBN.Init();
	//��ʾ
	AfxMessageBox(_T("��ɶ�ȡ��Ҷ˹����Ľṹ�Ͳ���������ʼ����...���밴ȷ��������"));
	
	//��ѯ
	theBN.Query();
}

