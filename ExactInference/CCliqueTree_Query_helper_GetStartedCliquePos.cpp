/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CCliqueTree_Query_Helper_GetStartedCliquePos.cpp
//功  能：		获取查询开始的团的位置
//开发者：		高志强
//日  期：		2021年04月12日
//更  新：		2021年05月18日
//长  度：		70行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		Query_Helper_GetStartedCliquePos()
//功  能：		获取查询开始的团的位置
//参  数：		set<unsigned int>&
//				查询变量集合
//返回值：		unsigned int
//				查询子团树的根
//算  法：		选取包含查询变量最多的团，作为开始团
size_t CCliqueTree::GetStartCliquePos(const fidset& QueryVariableIDs)
{
	//定义并初始化返回团的位置
	size_t nStartCliquePos = 0;
	
	//定义开始团中包含查询变量ID的个数，以便在团之间进行比较
	size_t nIntersectedVariableCount = 0;
	
	//遍历所有团，查找开始团
	for (size_t i = 0; i < m_Cliques.size(); i++)
	{

		//求变量ID列表中有多少个在查询变量集合中
		fidset IntersectedIDs;//在查询变量集合中的变量ID集合
		std::ranges::set_intersection(m_Cliques[i].GetCliqueVariableIDs(), QueryVariableIDs, qy::set_inserter(IntersectedIDs));

		//检查是否大于已有的团
		if (IntersectedIDs.size() >= nIntersectedVariableCount)
		{
			//更新开始团
			nStartCliquePos = i;
			nIntersectedVariableCount = IntersectedIDs.size();
		}
	}

	//返回开始团的位置
	return nStartCliquePos;
}
