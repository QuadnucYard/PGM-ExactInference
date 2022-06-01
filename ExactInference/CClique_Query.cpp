////////////////////////////////////////////////////////////////////////////////
// CClique_Query.cpp
// ��ѯ���е��ض����ʡ��������а���A��B��C����������ֻ���ȡA��B��C�ض�ȡֵ�ĸ��ʵȡ���Ҫ��������ID�б�ͱ���ֵ��ID�б�
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CClique.h"


//��ѯ�ض�ֵ
fval_t CClique::Query(const fidlist& VariableIDs, const fidlist& ValueIDs) const
{
	// ʹ��m_VariableIDs��VariableIDs�е�λ�ù����б�
	auto mmap = std::views::transform(m_VariableIDs, [&](fid_t id) -> fid_t {
		size_t i = qy::ranges::index_of(VariableIDs, id);
		return i == -1 ? -1 : ValueIDs[i];
	});

	//���˶�Ӧλ��id��ͬ���У�����fValue���
	return qy::ranges::sum(m_CliqueRows | std::views::filter([&](auto& r) {
		return std::ranges::equal(r.ValueIDs, mmap, [](fid_t x, fid_t y) { return y == -1 || x == y; });
	}), &CliqueRow::fValue);
}

//��ȡ����ID�б�
const fidlist& CClique::GetCliqueVariableIDs() const
{
	return m_VariableIDs;
}

//��ȡ����ID����
fidset CClique::GetVariableIDs() const
{
	return fidset {m_VariableIDs.begin(), m_VariableIDs.end()};
}

//��ȡ�ŵ�ID
fid_t CClique::GetID() const
{
	return m_nCliqueID;
}