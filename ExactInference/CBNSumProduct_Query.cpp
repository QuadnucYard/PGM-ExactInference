/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CBNSumProduct_Query.cpp
//��  �ܣ�		��ѯ
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��24��
//��  �£�		
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


//��ѯ
void CBNSumProduct::Query()
{
	//�������в�ѯ��������
	for (const QUERY& q : m_Queries)
	{
		//Preprocess_Query(m_Queries[i]);
		//���ò�ѯ�ĸ�������
		Query_Helper(q, m_Factors);
	}
	//�����ѯ���
	OutputToXML();
}