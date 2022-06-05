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
fval_t CBNSumProduct::Query_Helper(const BNQuery& query, CFactorList Factors) const
{
	//����1�����ݸ�����������Լ�����б�
	for (const GroundingVariable& v : query.GivenVariables)
	{
		std::ranges::for_each(Factors,
			std::bind(std::mem_fn(&CFactor::ReduceGivenVariable), std::placeholders::_1, v.nNodeID, v.nValueID));
	}

	//����2�������Ե����
	return Query_Marginal(query, Factors);
}