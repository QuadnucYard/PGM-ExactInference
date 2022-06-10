////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_Query.cpp
// 查询
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"

namespace pgm {

	//查询
	fvallist CBNSumProduct::query(const ProbQueryList& queries) const
	{
		fvallist queryResult;
		//遍历所有查询进行推理
		std::ranges::transform(queries, std::back_inserter(queryResult),
			[this](auto&& q) { return query(q); });

		return queryResult;
	}

	//查询的辅助函数
	fval_t CBNSumProduct::query(const ProbQuery& query) const
	{
		//步骤1：根据给定变量、规约因子列表
		FactorList reducedFactors;
		for (auto&& factor : m_Factors) {
			reducedFactors.push_back(factor.reduceGivenVariables(query.givenVars));
		}

		//步骤2：计算边缘概率
		//步骤1：遍历所有删除变量，并进行边缘概率计算
		// 这里做一个简化处理，是错误的
		for (fid_t ev : getEliminationOrder(query)) {
			eliminateVar(ev, reducedFactors);
		}

		//步骤2：计算剩余的因子积
		//步骤3：对最后得到的因子归一化，这个是必要的
		Factor phi = qy::ranges::product(reducedFactors).normalized();
		//对因子进行查询
		return phi.query(query.marginalVars);
	}

}