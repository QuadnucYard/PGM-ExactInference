////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_GetFactor.cpp
// 获取因子值
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


//计算因子的值
fval_t CBNSumProduct::GetFactor(
	fid_t nNodeID,					//节点ID
	fid_t nValueID,					//节点值ID
	const GVarList& QueryVariables)	//查询变量列表
{

	const BNNode& theNode = m_Nodes[nNodeID];
	//遍历父节点ID，获取其值ID
	fidlist ValueIDs = theNode.ParentIDs | std::views::transform([&](auto t) { return GetValueID(t, QueryVariables); }) | qy::views::to<fidlist>;

	//在当前节点的CPT中查找
	size_t result = qy::ranges::index_of(theNode.CPTRowIDs, qy::concat(ValueIDs, nValueID), &CPTRow::ValueIDs);
	if (result != -1)
		return theNode.CPTRowValues[result];
	AfxMessageBox(_T("GetFactor()异常"));
	return 1.0f;
}

//获取值ID
fid_t CBNSumProduct::GetValueID(fid_t nNodeID,		//节点ID
	const GVarList& QueryVariables)	//查询变量列表
{
	auto result = std::ranges::find(QueryVariables, nNodeID, &GroundingVariable::nNodeID);
	if (result != QueryVariables.end())
		return result->nValueID;
	AfxMessageBox(_T("GetValueID()异常"));
	return 0;
}