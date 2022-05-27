/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CBNSumProduct_Query_Helper.cpp
//功  能：		查询的辅助函数
//开发者：		高志强
//日  期：		2021年03月14日
//更  新：		2021年03月24日
//长  度：		70行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CBNSumProduct.h"							//贝叶斯网络精确推理类头文件，采用和积变量消除法
#include "Helper.h"									//辅助函数头文件
#include <functional>

//名  称：		Query_Helper()
//功  能：		查询的辅助函数
//参  数：		QUERY&,CFactorList
//返回值：		无
void CBNSumProduct::Query_Helper(const QUERY& query, CFactorList Factors)
{
	//////////////////////////////////////////////////////////////////////////////
	//步骤1：根据给定变量、规约因子列表
	//遍历所有给定变量ID
	for (GROUNDING_VARIABLE v : query.GivenVariables)
	{
		std::ranges::for_each(Factors,
			std::bind(std::mem_fn(&CFactor::ReduceGivenVariable), std::placeholders::_1, v.nNodeID, v.nValueID));
	}

	/////////////////////////////////////////////////////////////////////////////
	//步骤2：计算边缘概率
	Query_Marginal(query, Factors);
}