/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CFactor_Init.cpp
//功  能：		初始化。包括设置变量ID列表、因子行
//开发者：		高志强
//日  期：		2021年03月12日
//更  新：		2021年03月23日
//更  新：		2021年03月29日
//长  度：		50行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CFactor.h"


void CFactor::SetFactorVariableIDs(const fidlist& VariableIDs)
{
	m_VariableIDs = VariableIDs;
}

void CFactor::SetFactorVariableIDs(fidlist&& VariableIDs)
{
	m_VariableIDs = std::move(VariableIDs);
}

void CFactor::SetFactorRow(const fidlist& ValueIDs, fval_t fRowValue)
{
	m_FactorRows.emplace_back(ValueIDs, fRowValue);
}

void CFactor::SetFactorRow(fidlist&& ValueIDs, fval_t fRowValue)
{
	m_FactorRows.emplace_back(std::move(ValueIDs), fRowValue);
}