////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_Query_Helper.cpp
// ��ѯ�ĸ�������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"
#include <functional>


//��ѯ�ĸ�������
void CBNSumProduct::Query_Helper(const QUERY& query, CFactorList Factors)
{
	//����1�����ݸ�����������Լ�����б�
	for (const GROUNDING_VARIABLE& v : query.GivenVariables)
	{
		std::ranges::for_each(Factors,
			std::bind(std::mem_fn(&CFactor::ReduceGivenVariable), std::placeholders::_1, v.nNodeID, v.nValueID));
	}

	//����2�������Ե����
	Query_Marginal(query, Factors);
}