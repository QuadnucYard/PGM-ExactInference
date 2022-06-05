////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_Query_Marginal.cpp
// 查询边缘概率分布
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


//查询边缘概率分布
fval_t CBNSumProduct::Query_Marginal(const BNQuery& query, CFactorList& Factors) const
{
	//步骤1：遍历所有删除变量，并进行边缘概率计算
	for (fid_t ev : query.EliminateVariables)
	{
		Sum_Product_Eliminate_Var(ev, Factors);
	}

	//步骤2：计算剩余的因子积
	CFactor phi = qy::ranges::product(Factors);

	//步骤3：对因子归一化。该因子为最终的计算结果。不论是否需要，都进行归一化。如果不需要的话，也不影响计算结果
	phi.Normalize();

	//步骤4：获取概率
	fidlist VariableIDs = query.QueryVariables | std::views::transform(&GroundingVariable::nNodeID) | qy::views::to<fidlist>;
	fidlist ValueIDs = query.QueryVariables | std::views::transform(&GroundingVariable::nValueID) | qy::views::to<fidlist>;

	//对因子进行查询，添加概率到查询结果
	return phi.Query(VariableIDs, ValueIDs);
}


