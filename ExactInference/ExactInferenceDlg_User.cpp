/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		ExactInferenceDlg_User.cpp
//��  �ܣ�		��Ӧ�û�����
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��02��20��
//��  �£�		
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ExactInference.h"
#include "ExactInferenceDlg.h"
#include "CBNSumProduct.h"


//��Ӧ��ʼ������
void CExactInferenceDlg::OnBnClickedButtonBnInit()
{
	CBNSumProduct theBN;
	theBN.Init();
	AfxMessageBox(_T("��ɶ�ȡ��Ҷ˹����Ľṹ�Ͳ���������ʼ����...���밴ȷ��������"));
	theBN.Query();
}

