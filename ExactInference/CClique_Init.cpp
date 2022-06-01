/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CClique_Init.cpp
//功  能：		初始化。包括设置变量ID列表、团行
//开发者：		高志强
//日  期：		2021年03月31日
//更  新：		2021年04月12日
//更  新：		2021年05月18日
//长  度：		60行
/////////////////////////////////////////////////////////////////////////////////////////////
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