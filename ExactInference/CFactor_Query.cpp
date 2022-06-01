////////////////////////////////////////////////////////////////////////////////
// CFactor_Query.cpp
// ��ѯ�����е��ض����ʡ����������а���A��B��C����������ֻ���ȡA��B��C�ض�ȡֵ�ĸ��ʵȡ���Ҫ��������ID�б�ͱ���ֵ��ID�б�
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CFactor.h"


double CFactor::Query(const fidlist& VariableIDs, const fidlist& ValueIDs)
{
	// ʹ��m_VariableIDs��VariableIDs�е�λ�ù����б�
	auto mmap = std::views::transform(m_VariableIDs, [&](fid_t id) -> fid_t {
		size_t i = qy::ranges::index_of(VariableIDs, id);
		return i == -1 ? -1 : ValueIDs[i];
	});

	//���˶�Ӧλ��id��ͬ���У�����fValue���
	return qy::ranges::sum(m_FactorRows | std::views::filter([&](auto& r) {
		return std::ranges::equal(r.ValueIDs, mmap, [](fid_t x, fid_t y) { return y == -1 || x == y; });
	}), &FACTOR_ROW::fValue);

}

const fidlist& CFactor::GetFactorVariableIDs() const
{
	return m_VariableIDs;
}