/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CFactor_Query.cpp
//功  能：		查询因子中的特定概率。例如因子中包括A、B、C三个变量，只想获取A、B、C特定取值的概率等。需要给定变量ID列表和变量值的ID列表
//开发者：		高志强
//日  期：		2021年03月15日
//更  新：		2021年03月23日
//更  新：		2021年03月29日
//长  度：		80行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CFactor.h"								//因子类头文件
#include "Helper.h"									//辅助函数头文件
#include <ranges>

//名  称：		Query()
//功  能：		查询特定值
//参  数：		vector<unsigned int>&,vector<unsigned int>&
//返回值：		double
double CFactor::Query(const fidlist& VariableIDs, const fidlist& ValueIDs)
{
	//定义位置集合
	auto Positions = std::views::transform(VariableIDs,
		[&](fid_t i) { return qy::index_of(m_VariableIDs, i); });

	//初始化返回的概率值
	double fProb = 0.0f;

	//遍历因子行，求和
	for (const FACTOR_ROW& factor_row : m_FactorRows)
	{
		//检查对应位置和值是否正确
		bool bMatch = std::ranges::all_of(std::views::iota(0, (int)Positions.size()),
			[&](int j) { return factor_row[Positions[j]] == ValueIDs[j]; });
		//bool bMatch = std::ranges::all_of(std::views::zip(Positions, ValueIDs),
		//	[&](auto t) { return factor_row[std::get<0>(t)] == std::get<1>(t); };
		//检查该行是否匹配。如果匹配的话，则需要累加概率值
		if (bMatch)
		{
			fProb += factor_row.fValue;
		}
	}

	return fProb;
}

//名  称：		GetFactorVariableIDs()
//功  能：		获取变量ID列表
//参  数：		无
//返回值：		unsigned int
const fidlist& CFactor::GetFactorVariableIDs() const
{
	//返回变量ID列表
	return m_VariableIDs;
}