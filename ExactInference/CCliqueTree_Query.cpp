////////////////////////////////////////////////////////////////////////////////
// CClique_Query.cpp
// 查询
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//查询
fvallist CCliqueTree::Query(const QueryList& queries) const
{
	fvallist queryResult;
	//遍历所有查询进行推理
	std::ranges::transform(queries, std::back_inserter(queryResult),
		[this](const CTQuery& q) { return Query_Helper(q); });

	return queryResult;
}