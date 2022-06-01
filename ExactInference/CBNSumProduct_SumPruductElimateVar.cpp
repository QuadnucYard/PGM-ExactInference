////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_SumProductEliminateVar.cpp
// 和积消除变量
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


//和积消除变量
void CBNSumProduct::Sum_Product_Eliminate_Var(fid_t nVariableID, CFactorList& OldFactors)
{
	CFactorList NewFactors;
	//步骤1：构建因子列表，从OldFactors划分出，并从因子列表中删除和给定变量值不一致的行
	qy::split(OldFactors, std::back_inserter(NewFactors),
		[=](CFactor& t) { return qy::ranges::includes(t.GetFactorVariableIDs(), nVariableID); });

	if (NewFactors.size() == 0)
	{
		//没有因子包含给定变量、直接返回
		return;
	}
	else
	{
		//步骤2：因子积
		CFactor psi = qy::ranges::product(NewFactors);
		
		//步骤3：求和掉给定变量
		psi.SumOutVariable(nVariableID);

		//步骤4：将因子积添加到因子列表
		OldFactors.push_back(std::move(psi));
	}
}

