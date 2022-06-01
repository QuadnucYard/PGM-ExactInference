////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_Query_Helper.cpp
// 查询的辅助函数
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//查询的辅助函数
void CCliqueTree::Query_Helper(const CT_QUERY& query)
{
	//步骤1：根据边缘变量和给定变量，获取查询变量ID的集合
	fidset QueryVariableIDs;
	std::ranges::transform(query.MarginalVariables, qy::set_inserter(QueryVariableIDs),
		&CT_GROUNDING_VARIABLE::nVariableID);
	std::ranges::transform(query.GivenVariables, qy::set_inserter(QueryVariableIDs),
		&CT_GROUNDING_VARIABLE::nVariableID);
	
	//步骤2：遍历所有团，获取开始团的ID。从包含查询变量最多的一个团开始
	//步骤3：广度优先遍历团，计算边缘概率或条件概率		
	Query_Probability(query, QueryVariableIDs, GetStartClique(QueryVariableIDs));
}