////////////////////////////////////////////////////////////////////////////////
// CClique_Query.cpp
// 查询团中的特定概率。例如团中包括A、B、C三个变量，只想获取A、B、C特定取值的概率等。需要给定变量ID列表和变量值的ID列表
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CClique.h"


//查询特定值
fval_t CClique::Query(const fidlist& VariableIDs, const fidlist& ValueIDs) const
{
	// 使用m_VariableIDs在VariableIDs中的位置构建列表
	auto mmap = std::views::transform(m_VariableIDs, [&](fid_t id) -> fid_t {
		size_t i = qy::ranges::index_of(VariableIDs, id);
		return i == -1 ? -1 : ValueIDs[i];
	});

	//过滤对应位置id相同的行，对其fValue求和
	return qy::ranges::sum(m_CliqueRows | std::views::filter([&](auto& r) {
		return std::ranges::equal(r.ValueIDs, mmap, [](fid_t x, fid_t y) { return y == -1 || x == y; });
	}), &CliqueRow::fValue);
}

//获取变量ID列表
const fidlist& CClique::GetCliqueVariableIDs() const
{
	return m_VariableIDs;
}

//获取变量ID集合
fidset CClique::GetVariableIDs() const
{
	return fidset {m_VariableIDs.begin(), m_VariableIDs.end()};
}

//获取团的ID
fid_t CClique::GetID() const
{
	return m_nCliqueID;
}