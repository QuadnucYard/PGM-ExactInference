/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CBNSumProduct_Preprocess_Factor.cpp
//功  能：		预处理因子
//开发者：		高志强
//日  期：		2021年03月13日
//更  新：		2021年03月23日
//长  度：		70行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


//预处理因子
void CBNSumProduct::Preprocess_Factor()
{
	for (const BN_NODE& node : m_Nodes)
	{
		CFactor factor;

		//步骤1：设置因子的变量ID的列表
		factor.SetFactorVariableIDs(qy::concat(node.ParentIDs, node.nID));

		//步骤2：设置因子值的ID表
		for (const CPT_ROW& row : node.CPTRowIDs)
		{
			factor.SetFactorRow(row.ValueIDs, row.fProb);
		}

		m_Factors.push_back(factor);
	}
}