////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_Init.cpp
// ��ʼ��
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


void CBNSumProduct::Init()
{
	//����1����ȡ��Ҷ˹����ṹ�Ͳ���
	Read_BN();

	//����2����ȡ��ѯ���񣬰�����ѯ������������������������˳��
	Read_Query();

	//����3��Ԥ����
	Preprocess();
}