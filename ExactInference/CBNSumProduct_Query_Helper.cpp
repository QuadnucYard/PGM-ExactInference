/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CBNSumProduct_Query_Helper.cpp
//��  �ܣ�		��ѯ�ĸ�������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��14��
//��  �£�		2021��03��24��
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
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