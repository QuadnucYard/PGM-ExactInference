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
#include "CCliqueTree.h"


//��Ӧ��ʼ������
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


//��Ӧ���������ĳ�ʼ������ѯ����
void CExactInferenceDlg::OnBnClickedButtonCt()
{
	//������������
	CCliqueTree theCliqueTree;

	//��ʼ��
	theCliqueTree.Init();
	//��ʾ
	AfxMessageBox(_T("��ɶ�ȡ������У׼��׼����ʼ����...���밴ȷ��������"));

	//��ѯ
	theCliqueTree.Query();
}
