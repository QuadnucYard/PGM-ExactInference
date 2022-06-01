////////////////////////////////////////////////////////////////////////////////
// CFactor_ReduceGivenVariable.cpp
// 根据给定的变量和值，化简因子。用于计算条件概率分布
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CFactor.h"


//根据给定的变量ID和值ID，化简因子
void CFactor::ReduceGivenVariable(fid_t nVariableID, fid_t nValueID)
{
	//查找变量ID是否在因子中
	if (size_t nPos = qy::ranges::index_of(m_VariableIDs, nVariableID); nPos != -1)
	{
		//找到，需要进行简化
		//遍历所有行。检查特定位置（列）的变量值是否相等
		//删掉 nValueID != it->ValueIDs[nPos] 的项
		qy::remove_if(m_FactorRows, [=](const FACTOR_ROW& t) {return t[nPos] != nValueID; });
	}
}