/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CClique_ReduceGivenVariable.cpp
//功  能：		根据给定的变量和值，化简团。用于计算条件概率分布
//开发者：		高志强
//日  期：		2021年03月31日
//更  新：		2021年04月12日
//更  新：		2021年05月18日
//长  度：		50行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"	
#include "CClique.h"


//根据给定的变量ID和值ID，化简团
void CClique::ReduceGivenVariable(fid_t nVariableID, fid_t nValueID)
{
	if (size_t nPos = qy::ranges::index_of(m_VariableIDs, nVariableID); nPos != -1)
	{
		qy::remove_if(m_CliqueRows, [=](const CLIQUE_ROW& t) {return t[nPos] != nValueID; });
	}
}