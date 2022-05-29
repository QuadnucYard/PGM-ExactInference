/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CBNSumProduct_GetFactor.cpp
//功  能：		获取因子值
//开发者：		高志强
//日  期：		2021年03月09日
//更  新：		2021年03月24日
//长  度：		100行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


//计算因子的值
fval_t CBNSumProduct::GetFactor(
	fid_t nNodeID,					//节点ID
	fid_t nValueID,					//节点值ID
	const GVarList& QueryVariables)	//查询变量列表
{
	//定义、并初始化获取父节点ID列表
	fidlist NodeIDs = m_Nodes[nNodeID].ParentIDs;

	//遍历父节点ID，获取其值ID
	fidlist ValueIDs = NodeIDs | std::views::transform([&](auto t) { return GetValueID(t, QueryVariables); }) | qy::views::to<fidlist>;
	//添加当前节点的值ID
	ValueIDs.push_back(nValueID);

	//在当前节点的CPT中查找
	size_t result = qy::index_of_if(m_Nodes[nNodeID].CPTRowIDs, [=](const CPT_ROW& t) { return t.ValueIDs == ValueIDs; });
	if (result != -1)
		return m_Nodes[nNodeID].CPTRowValues[result];
	AfxMessageBox(_T("GetFactor()异常"));
	return 1.0f;
}

//获取值ID
fid_t CBNSumProduct::GetValueID(fid_t nNodeID,		//节点ID
	const GVarList& QueryVariables)	//查询变量列表
{
	auto result = std::ranges::find_if(QueryVariables, [=](GROUNDING_VARIABLE t) { return t.nNodeID == nNodeID; });
	if (result != QueryVariables.end())
		return result->nValueID;
	AfxMessageBox(_T("GetValueID()异常"));
	return 0;
}