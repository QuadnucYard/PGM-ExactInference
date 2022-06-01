/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CFactor_ReduceGivenVariable.cpp
//功  能：		根据给定的变量和值，化简因子。用于计算条件概率分布
//开发者：		高志强
//日  期：		2021年03月13日
//更  新：		2021年03月14日
//更  新：		2021年03月23日
//更  新：		2021年03月29日
//长  度：		50行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CFactor.h"								//因子类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		ReduceGivenVariable()
//功  能：		根据给定的变量ID和值ID，化简因子
//参  数：		unsigned int,unsigned int
//返回值：		无
void CFactor::ReduceGivenVariable(unsigned int nVariableID, unsigned int nValueID)
{
	//查找变量ID是否在因子中
	unsigned int nPos = 0;
	bool bFind = IsINTInVector(nVariableID, m_VariableIDs,nPos);//如果找到，则返回在列表中的位置nPos
	//检查是否找到
	if (bFind)//找到，需要进行简化
	{
		//遍历所有行。检查特定位置（列）的变量值是否相等
		vector<FACTOR_ROW>::iterator it = m_FactorRows.begin();
		while (it != m_FactorRows.end())
		{
			//检查变量值是否相等
			if (nValueID == it->ValueIDs[nPos])
			{
				//保留行、更新迭代器
				it++;
			}
			else
			{
				//删除行、并更新迭代器
				it = m_FactorRows.erase(it);
			}
		}
	}
}