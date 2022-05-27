/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CBNSumProduct_Query_Helper.cpp
//��  �ܣ�		��ѯ�ĸ�������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��14��
//��  �£�		2021��03��24��
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CBNSumProduct.h"							//��Ҷ˹���羫ȷ������ͷ�ļ������úͻ�����������
#include "Helper.h"									//��������ͷ�ļ�
#include <functional>

//��  �ƣ�		Query_Helper()
//��  �ܣ�		��ѯ�ĸ�������
//��  ����		QUERY&,CFactorList
//����ֵ��		��
void CBNSumProduct::Query_Helper(const QUERY& query, CFactorList Factors)
{
	//////////////////////////////////////////////////////////////////////////////
	//����1�����ݸ�����������Լ�����б�
	//�������и�������ID
	for (GROUNDING_VARIABLE v : query.GivenVariables)
	{
		std::ranges::for_each(Factors,
			std::bind(std::mem_fn(&CFactor::ReduceGivenVariable), std::placeholders::_1, v.nNodeID, v.nValueID));
	}

	/////////////////////////////////////////////////////////////////////////////
	//����2�������Ե����
	Query_Marginal(query, Factors);
}