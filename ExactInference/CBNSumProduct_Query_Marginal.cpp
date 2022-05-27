/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CBNSumProduct_Query_Marginal.cpp
//功  能：		查询边缘概率分布
//开发者：		高志强
//日  期：		2021年03月14日
//更  新：		2021年03月24日
//长  度：		70行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CBNSumProduct.h"							//贝叶斯网络精确推理类头文件，采用和积变量消除法
#include "Helper.h"									//辅助函数头文件
#include "stl_utils.h"


//名  称：		Query_Marginal()
//功  能：		查询边缘概率分布
//参  数：		QUERY&,vectot<CFactor>&
//返回值：		无
void CBNSumProduct::Query_Marginal(const QUERY& query, CFactorList& Factors)
{
	//////////////////////////////////////////////////////////////////////////////
	//步骤1：遍历所有删除变量，并进行边缘概率计算。测试用例：边缘概率l1=0.502
	for (fid_t ev : query.EliminateVariables)
	{
		//调用辅助函数，消除变量
		Sum_Product_Eliminate_Var(ev, Factors);
	}

	//////////////////////////////////////////////////////////////////////////////
	//步骤2：计算剩余的因子积
	CFactor phi = qy::product(Factors);

	/////////////////////////////////////////////////////////////////////////////
	//步骤3：对因子归一化。该因子为最终的计算结果。不论是否需要，都进行归一化。如果不需要的话，也不影响计算结果
	phi.Normalize();

	//////////////////////////////////////////////////////////////////////////////////
	//步骤4：获取概率
	fidlist VariableIDs = query.QueryVariables | std::views::transform([](auto t) {return t.nNodeID; }) | qy::views::to<fidlist>;
	fidlist ValueIDs = query.QueryVariables | std::views::transform([](auto t) {return t.nValueID; }) | qy::views::to<fidlist>;

	//对因子进行查询，添加概率到查询结果
	m_QueryResults.push_back(phi.Query(VariableIDs, ValueIDs));
}


