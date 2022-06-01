////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_Preprocess_Factor.cpp
// 预处理因子
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
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