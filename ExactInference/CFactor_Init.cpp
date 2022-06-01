////////////////////////////////////////////////////////////////////////////////
// CFactor_Init.cpp
// 初始化。包括设置变量ID列表、因子行
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CFactor.h"


void CFactor::SetFactorVariableIDs(const fidlist& VariableIDs)
{
	m_VariableIDs = VariableIDs;
	// 建立位置映射 求每个id的rank
	std::ranges::sort(m_VariableIDs);
	m_IdOrder.resize(m_VariableIDs.size());
	for (size_t i = 0; i < m_IdOrder.size(); i++) {
		m_IdOrder[i] = std::ranges::lower_bound(m_VariableIDs, VariableIDs[i]) - m_VariableIDs.begin();
	}
}

void CFactor::SetFactorRow(const fidlist& ValueIDs, fval_t fRowValue)
{
	// 重映射，整理列顺序
	fidlist mappedIDs(ValueIDs.size());
	for (size_t i = 0; i < m_IdOrder.size(); i++) {
		mappedIDs[i] = ValueIDs[m_IdOrder[i]];
	}
	m_FactorRows.emplace_back(std::move(mappedIDs), fRowValue);
}
