////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_Query.cpp
// ��ѯ
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
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