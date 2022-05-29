/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CFactor_Query.cpp
//功  能：		查询因子中的特定概率。例如因子中包括A、B、C三个变量，只想获取A、B、C特定取值的概率等。需要给定变量ID列表和变量值的ID列表
//开发者：		高志强
//日  期：		2021年03月15日
//更  新：		2021年03月23日
//更  新：		2021年03月29日
//长  度：		80行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CFactor.h"


double CFactor::Query(const fidlist& VariableIDs, const fidlist& ValueIDs)
{
	auto Positions = std::views::transform(VariableIDs,
		[&](fid_t i) { return qy::index_of(m_VariableIDs, i); });

	double fProb = 0.0f;

	//遍历因子行，求和
	for (const FACTOR_ROW& factor_row : m_FactorRows)
	{
		//检查对应位置和值是否正确
		bool bMatch = std::ranges::all_of(std::views::iota(0, (int)Positions.size()),
			[&](int j) { return factor_row[Positions[j]] == ValueIDs[j]; });
		//检查该行是否匹配。如果匹配的话，则需要累加概率值
		if (bMatch)
		{
			fProb += factor_row.fValue;
		}
	}

	return fProb;
}

const fidlist& CFactor::GetFactorVariableIDs() const
{
	return m_VariableIDs;
}