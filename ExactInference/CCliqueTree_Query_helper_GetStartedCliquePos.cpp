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
unsigned int CCliqueTree::GetStartCliquePos(set<unsigned int>& QueryVariableIDs)
{
	//定义并初始化返回团的位置
	unsigned int nStartCliquePos = 0;
	
	//定义开始团中包含查询变量ID的个数，以便在团之间进行比较
	unsigned int nIntersectedVariableCount = 0;	
	
	//遍历所有团，查找开始团
	for (unsigned int i = 0; i < m_Cliques.size(); i++)
	{
		//获取团中变量ID列表
		vector<unsigned int> CliqueVariableIDs = m_Cliques[i].GetCliqueVariableIDs();

		//求变量ID列表中有多少个在查询变量集合中
		set<unsigned int> IntersectedIDs;//在查询变量集合中的变量ID集合
		GetIntersections(CliqueVariableIDs, QueryVariableIDs, IntersectedIDs);

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

//名  称：		GetIntersections()
//功  能：		求列表和集合的交集
//参  数：		vector<unsigned int>&,set<unsigned int>&
//				set<unsigned int>&
//返回值：		无
void CCliqueTree::GetIntersections(vector<unsigned int>& VectorIDs, set<unsigned int>& SetIDs, set<unsigned int>& IntersectedIDs)
{
	//遍历列表
	for (unsigned int i = 0; i < VectorIDs.size(); i++)
	{
		//检查是否相交
		if (IsINTInSet(VectorIDs[i], SetIDs))
		{			
			//添加到结果集合
			IntersectedIDs.insert(VectorIDs[i]);
		}
	}
}