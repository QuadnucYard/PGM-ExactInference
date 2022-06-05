////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_Query_Marginal.cpp
// ��ѯ��Ե���ʷֲ�
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


//��ѯ��Ե���ʷֲ�
fval_t CBNSumProduct::Query_Marginal(const BNQuery& query, CFactorList& Factors) const
{
	//����1����������ɾ�������������б�Ե���ʼ���
	for (fid_t ev : query.EliminateVariables)
	{
		Sum_Product_Eliminate_Var(ev, Factors);
	}

	//����2������ʣ������ӻ�
	CFactor phi = qy::ranges::product(Factors);

	//����3�������ӹ�һ����������Ϊ���յļ������������Ƿ���Ҫ�������й�һ�����������Ҫ�Ļ���Ҳ��Ӱ�������
	phi.Normalize();

	//����4����ȡ����
	fidlist VariableIDs = query.QueryVariables | std::views::transform(&GroundingVariable::nNodeID) | qy::views::to<fidlist>;
	fidlist ValueIDs = query.QueryVariables | std::views::transform(&GroundingVariable::nValueID) | qy::views::to<fidlist>;

	//�����ӽ��в�ѯ����Ӹ��ʵ���ѯ���
	return phi.Query(VariableIDs, ValueIDs);
}


