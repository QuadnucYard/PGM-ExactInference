/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CClique_ReduceGivenVariable.cpp
//功  能：		根据给定的变量和值，化简团。用于计算条件概率分布
//开发者：		高志强
//日  期：		2021年03月31日
//更  新：		2021年04月12日
//更  新：		2021年05月18日
//长  度：		50行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CClique.h"								//团类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		ReduceGivenVariable()
//功  能：		根据给定的变量ID和值ID，化简团
//参  数：		unsigned int,unsigned int
//返回值：		无
void CClique::ReduceGivenVariable(unsigned int nVariableID, unsigned int nValueID)
{
	//检查是否找到
	if (size_t nPos = qy::ranges::index_of(m_VariableIDs, nVariableID); nPos != -1)//找到，需要进行简化
	{
		//遍历所有行。检查特定位置（列）的变量值是否相等
		vector<CLIQUE_ROW>::iterator it = m_CliqueRows.begin();
		while (it != m_CliqueRows.end())
		{
			//检查变量值是否相等
			if (nValueID == it->ValueIDs[nPos])
			{
				//保留行、更新迭代器
				it++;
			} else
			{
				//删除行、并更新迭代器
				it = m_CliqueRows.erase(it);
			}
		}
	}
}