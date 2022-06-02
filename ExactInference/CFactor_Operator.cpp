////////////////////////////////////////////////////////////////////////////////
// CFactor_Operator.cpp
// 重载操作符相关。主要是因子积
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CFactor.h"


CFactor CFactor::operator*(const CFactor& second) const
{
	// 应当保证因子升序排序
	// 检查两列能否合并
	auto checkMerge = [](const fidlist& id1, const FactorRow& row1, const fidlist& id2, const FactorRow& row2) {
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
	auto doMerge = [](const fidlist& id1, const FactorRow& row1, const fidlist& id2, const FactorRow& row2) {
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
	//对变量ID作并集
	std::ranges::set_union(m_VariableIDs, second.m_VariableIDs, std::back_inserter(factor.m_VariableIDs));
	// 把所有可以合并的行合并，加入到结果中
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