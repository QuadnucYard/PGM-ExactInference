////////////////////////////////////////////////////////////////////////////////
// CFactor_Query.cpp
// 查询因子中的特定概率。例如因子中包括A、B、C三个变量，只想获取A、B、C特定取值的概率等。需要给定变量ID列表和变量值的ID列表
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CFactor.h"


double CFactor::Query(const fidlist& VariableIDs, const fidlist& ValueIDs)
{
	// 使用m_VariableIDs在VariableIDs中的位置构建列表
	auto mmap = std::views::transform(m_VariableIDs, [&](fid_t id) -> fid_t {
		size_t i = qy::ranges::index_of(VariableIDs, id);
		return i == -1 ? -1 : ValueIDs[i];
	});

	//过滤对应位置id相同的行，对其fValue求和
	return qy::ranges::sum(m_FactorRows | std::views::filter([&](auto& r) {
		return std::ranges::equal(r.ValueIDs, mmap, [](fid_t x, fid_t y) { return y == -1 || x == y; });
	}), &FACTOR_ROW::fValue);

}

const fidlist& CFactor::GetFactorVariableIDs() const
{
	return m_VariableIDs;
}