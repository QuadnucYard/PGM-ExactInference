////////////////////////////////////////////////////////////////////////////////
// ExactInferenceDlg_User.cpp
// ��Ӧ�û�����
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
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

