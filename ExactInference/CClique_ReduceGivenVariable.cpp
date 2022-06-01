////////////////////////////////////////////////////////////////////////////////
// CClique_ReduceGivenVariable.cpp
// 根据给定的变量和值，化简团。用于计算条件概率分布
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
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