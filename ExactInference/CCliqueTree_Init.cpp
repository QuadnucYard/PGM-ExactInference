////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_Init.cpp
// ��ʼ�����γ�У׼������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//��ʼ��
void CCliqueTree::Init()
{
	//����3��Ԥ����
	Preprocess();

	//����4�����ϴ�����Ϣ
	UpwardPass();
	
	//����5�����´�����Ϣ
	DownwardPass();
}