/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CCliqueTree_Query_Probability_IsSetContainedIn.cpp
//功  能：		判断集合是否包含于另一个集合
//开发者：		高志强
//日  期：		2021年04月12日
//更  新：		
//长  度：		70行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		IsSetContainedIn()
//功  能：		判断集合是否包含于另一集合
//参  数：		set<unsigned int>&,set<unsigned int>&
//返回值：		bool
bool CCliqueTree::IsSetContainedIn(set<unsigned int>& QueryVariableIDs,set<unsigned int>& StartVariableIDs)
{
	//遍历集合
	for (set<unsigned int>::iterator it = QueryVariableIDs.begin(); it != QueryVariableIDs.end(); it++)
	{
		//获取当前ID
		unsigned int nID = *it;

		//检查当前ID是否在集合
		if (!IsINTInSet(nID, StartVariableIDs))
		{
			//返回假
			return false;
		}
	}

	//缺省返回真
	return true;
}