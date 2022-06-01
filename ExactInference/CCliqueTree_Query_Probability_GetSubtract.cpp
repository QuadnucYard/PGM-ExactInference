/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CCliqueTree_Query_Probability_GetSubtract.cpp
//功  能：		获取列表和集合的差
//开发者：		高志强
//日  期：		2021年04月12日
//更  新：		
//长  度：		70行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		GetSubstract()
//功  能：		获取列表和集合的差
//参  数：		vector<unsigned int>&,set<unsigned int>&
//返回值：		无
vector<unsigned int> CCliqueTree::GetSubstract(vector<unsigned int>&LastVariableIDs, set<unsigned int>& VariableIDs)
{
	//定义返回结果
	vector<unsigned int> Results;

	//遍历所有向量
	for (unsigned int i = 0; i < LastVariableIDs.size(); i++)
	{
		//检查变量ID是否在集合中
		if (!IsINTInSet(LastVariableIDs[i], VariableIDs))
		{
			//添加到返回结果
			Results.push_back(LastVariableIDs[i]);
		}
	}

	//返回结果
	return Results;
}