/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CFactor_Operator.cpp
//��  �ܣ�		���ز�������ء���Ҫ�����ӻ�
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��12��
//��  �£�		2021��03��13��
//��  �£�		2021��03��23��
//��  �£�		2021��03��29��
//��  �ȣ�		50��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CFactor.h"


CFactor CFactor::operator*(const CFactor& second) const
{
	// Ӧ����֤������������
	assert(std::ranges::is_sorted(m_VariableIDs));
	assert(std::ranges::is_sorted(second.m_VariableIDs));
	// ��������ܷ�ϲ�
	auto checkMerge = [](const fidlist& id1, const FACTOR_ROW& row1, const fidlist& id2, const FACTOR_ROW& row2) {
		size_t n = id1.size(), m = id2.size();
		for (size_t i = 0, j = 0; i < n && j < m;) {
			if (id1[i] < id2[j])  ++i;
			else if (id1[i] > id2[j]) ++j;
			else {
				if (row1[i] != row2[j]) return false;
				++i, ++j;
			}
		}
		return true;
	};
	auto doMerge = [](const fidlist& id1, const FACTOR_ROW& row1, const fidlist& id2, const FACTOR_ROW& row2) {
		size_t n = id1.size(), m= id2.size();
		fidlist result;
		for (size_t i = 0, j = 0; i < n || j < m;) {
			if (i < n && (j == m || id1[i] < id2[j])) result.push_back(row1[i++]);
			else if (j < m && (i == n || id1[i] > id2[j])) result.push_back(row2[j++]);
			else result.push_back(row1[i++]), j++;
		}
		return result;
	};

	CFactor factor;
	//�Ա���ID������
	std::ranges::set_union(m_VariableIDs, second.m_VariableIDs, std::back_inserter(factor.m_VariableIDs));
	// �����п��Ժϲ����кϲ������뵽�����
	for (const auto& r1 : m_FactorRows) {
		for (const auto& r2 : second.m_FactorRows) {
			if (checkMerge(m_VariableIDs, r1, second.m_VariableIDs, r2)) {
				factor.m_FactorRows.emplace_back(
					doMerge(m_VariableIDs, r1, second.m_VariableIDs, r2),
					r1.fValue * r2.fValue
				);
			}
		}
	}
	
	return factor;
};