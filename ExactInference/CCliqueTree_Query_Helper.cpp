/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CCliqueTree_Query_Helper.cpp
//功  能：		查询的辅助函数
//开发者：		高志强
//日  期：		2021年04月01日
//更  新：		2021年04月12日
//更  新：		2021年05月18日
//长  度：		60行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		Query_Helper()
//功  能：		查询的辅助函数
//参  数：		CT_QUERY&
//返回值：		无
void CCliqueTree::Query_Helper(const CT_QUERY& query)
{
	//////////////////////////////////////////////////////////////////////////////
	//步骤1：根据边缘变量和给定变量，获取查询变量ID的集合
	fidset QueryVariableIDs;
	std::ranges::transform(query.MarginalVariables, std::inserter(QueryVariableIDs, QueryVariableIDs.end()),
		&CT_GROUNDING_VARIABLE::nVariableID);
	std::ranges::transform(query.GivenVariables, std::inserter(QueryVariableIDs, QueryVariableIDs.end()),
		&CT_GROUNDING_VARIABLE::nVariableID);
	
	/////////////////////////////////////////////////////////////////////////////
	//步骤2：遍历所有团，获取开始团的ID。从包含查询变量最多的一个团开始
	fid_t nStartCliquePos = GetStartCliquePos(QueryVariableIDs);
	
	/////////////////////////////////////////////////////////////////////////////
	//步骤3：广度优先遍历团，计算边缘概率或条件概率		
	Query_Probability(query, QueryVariableIDs, nStartCliquePos);
}