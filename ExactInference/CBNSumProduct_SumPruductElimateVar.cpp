/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CBNSumProduct_SumProductEliminateVar.cpp
//功  能：		和积消除变量
//开发者：		高志强
//日  期：		2021年03月14日
//更  新：		2021年03月24日
//长  度：		80行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CBNSumProduct.h"							//贝叶斯网络精确推理类头文件，采用和积变量消除法
#include "Helper.h"									//辅助函数头文件


//名  称：		Sum_Product_Eliminate_Var()
//功  能：		和积消除变量
//参  数：		unsigned int,CFactorList&
//返回值：		无
void CBNSumProduct::Sum_Product_Eliminate_Var(fid_t nVariableID, CFactorList& OldFactors)
{
	//定义因子列表  从OldFactors划分出
	CFactorList NewFactors;
	
	/////////////////////////////////////////////////////////////////////////////
	//步骤1：构建因子列表，并从因子列表中删除和给定变量值不一致的行
	qy::split(OldFactors, std::back_inserter(NewFactors),
		[=](CFactor& t) { return qy::includes(t.GetFactorVariableIDs(), nVariableID); });

	//检查因子列表的大小
	if (NewFactors.size() == 0)
	{
		//没有因子包含给定变量、直接返回
		return;
	}
	else
	{
		//步骤2：因子积
		CFactor psai = qy::product(NewFactors);
		
		//步骤3：求和掉给定变量
		psai.SumOutVariable(nVariableID);

		//步骤4：将因子积添加到因子列表
		OldFactors.push_back(psai);
	}
}

