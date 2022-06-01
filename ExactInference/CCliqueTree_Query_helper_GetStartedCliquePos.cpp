////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_Query_Helper_GetStartedCliquePos.cpp
// 获取查询开始的团的位置
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//获取查询开始的团的位置
//查询子团树的根
//选取包含查询变量最多的团，作为开始团
const CClique& CCliqueTree::GetStartClique(const fidset& QueryVariableIDs) const
{
	return *std::ranges::max_element(m_Cliques, {}, [&](auto& c) {
		return qy::set_intersection<fidlist>(c.GetVariableIDs(), QueryVariableIDs).size();
	});
}
