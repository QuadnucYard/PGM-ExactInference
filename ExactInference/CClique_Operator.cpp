/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CClique_Operator.cpp
//功  能：		重载操作符相关。主要是因子积。后来增加了因子除
//开发者：		高志强
//日  期：		2021年03月31日
//更  新：		2021年04月12日
//更  新：		2021年05月18日
//长  度：		50行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CClique.h"								//团类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		IsConsistentValueID()
//功  能：		检查团中两行的值ID是否兼容，用于判断乘积时能否合并
//参  数：		const FACTOR_ROW&, 
//				const FACTOR_ROW&, 
//				map<unsigned int, unsigned int>&
//返回值：		bool
bool CClique::IsConsistentValueID(const CLIQUE_ROW& FirstRow, const CLIQUE_ROW& SecondRow, map<unsigned int, unsigned int>& FirstToSeconds)
{
	//遍历所有相同变量位置的映射
	for (map<unsigned int, unsigned int>::iterator it = FirstToSeconds.begin(); it != FirstToSeconds.end(); it++)
	{
		//获取位置
		unsigned int nFirstPos = it->first;		//首位置
		unsigned int nSecondPos = it->second;	//尾位置

		//检查变量值的ID是否相等
		if (FirstRow.ValueIDs[nFirstPos] != SecondRow.ValueIDs[nSecondPos])
		{
			//返回假
			return false;
		}
	}

	//缺省返回真
	return true;
}