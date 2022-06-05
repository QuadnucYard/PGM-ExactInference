////////////////////////////////////////////////////////////////////////////////
// CClique_Query.cpp
// ��ѯ
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//��ѯ
fvallist CCliqueTree::Query(const QueryList& queries) const
{
	fvallist queryResult;
	//�������в�ѯ��������
	std::ranges::transform(queries, std::back_inserter(queryResult),
		[this](const CTQuery& q) { return Query_Helper(q); });

	return queryResult;
}