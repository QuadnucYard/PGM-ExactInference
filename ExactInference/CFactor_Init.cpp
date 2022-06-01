////////////////////////////////////////////////////////////////////////////////
// CFactor_Init.cpp
// ��ʼ�����������ñ���ID�б�������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CFactor.h"


void CFactor::SetFactorVariableIDs(const fidlist& VariableIDs)
{
	m_VariableIDs = VariableIDs;
	// ����λ��ӳ�� ��ÿ��id��rank
	std::ranges::sort(m_VariableIDs);
	m_IdOrder.resize(m_VariableIDs.size());
	for (size_t i = 0; i < m_IdOrder.size(); i++) {
		m_IdOrder[i] = std::ranges::lower_bound(m_VariableIDs, VariableIDs[i]) - m_VariableIDs.begin();
	}
}

void CFactor::SetFactorRow(const fidlist& ValueIDs, fval_t fRowValue)
{
	// ��ӳ�䣬������˳��
	fidlist mappedIDs(ValueIDs.size());
	for (size_t i = 0; i < m_IdOrder.size(); i++) {
		mappedIDs[i] = ValueIDs[m_IdOrder[i]];
	}
	m_FactorRows.emplace_back(std::move(mappedIDs), fRowValue);
}
