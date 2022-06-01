////////////////////////////////////////////////////////////////////////////////
// CClique_Init.cpp
// 初始化。包括设置变量ID列表、团行
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CClique.h"


//设置团ID
void CClique::SetCliqueID(fid_t nCliqueID)
{
	m_nCliqueID = nCliqueID;
}

//设置变量ID列表
void CClique::SetCliqueVariableIDs(const fidlist& VariableIDs)
{
	m_VariableIDs = VariableIDs;
}

//设置团行
void CClique::SetCliqueRow(const fidlist& ValueIDs, fval_t fRowValue)
{
	m_CliqueRows.emplace_back(ValueIDs, fRowValue);
}