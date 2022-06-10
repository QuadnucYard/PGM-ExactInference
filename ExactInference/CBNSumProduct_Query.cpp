////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_Query.cpp
// ��ѯ
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"

namespace pgm {

	//��ѯ
	fvallist CBNSumProduct::query(const ProbQueryList& queries) const
	{
		fvallist queryResult;
		//�������в�ѯ��������
		std::ranges::transform(queries, std::back_inserter(queryResult),
			[this](auto&& q) { return query(q); });

		return queryResult;
	}

	//��ѯ�ĸ�������
	fval_t CBNSumProduct::query(const ProbQuery& query) const
	{
		//����1�����ݸ�����������Լ�����б�
		FactorList reducedFactors;
		for (auto&& factor : m_Factors) {
			reducedFactors.push_back(factor.reduceGivenVariables(query.givenVars));
		}

		//����2�������Ե����
		//����1����������ɾ�������������б�Ե���ʼ���
		// ������һ���򻯴����Ǵ����
		for (fid_t ev : getEliminationOrder(query)) {
			eliminateVar(ev, reducedFactors);
		}

		//����2������ʣ������ӻ�
		//����3�������õ������ӹ�һ��������Ǳ�Ҫ��
		Factor phi = qy::ranges::product(reducedFactors).normalized();
		//�����ӽ��в�ѯ
		return phi.query(query.marginalVars);
	}

}