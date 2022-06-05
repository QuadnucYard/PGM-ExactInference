////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_Query.cpp
// ��ѯ
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


//��ѯ
fvallist CBNSumProduct::Query(const QueryList& queries) const
{
	fvallist queryResult;
	//�������в�ѯ��������
	std::ranges::transform(queries, std::back_inserter(queryResult),
		[this](const BNQuery& q) { return Query_Helper(q, m_Factors); });
	
	return queryResult;
}