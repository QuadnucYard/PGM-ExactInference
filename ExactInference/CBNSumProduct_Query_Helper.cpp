////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_Query_Helper.cpp
// 查询的辅助函数
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"
#include <functional>


//查询的辅助函数
fval_t CBNSumProduct::Query_Helper(const BNQuery& query, CFactorList Factors) const
{
	//步骤1：根据给定变量、规约因子列表
	for (const GroundingVariable& v : query.GivenVariables)
	{
		std::ranges::for_each(Factors,
			std::bind(std::mem_fn(&CFactor::ReduceGivenVariable), std::placeholders::_1, v.nNodeID, v.nValueID));
	}

	//步骤2：计算边缘概率
	return Query_Marginal(query, Factors);
}