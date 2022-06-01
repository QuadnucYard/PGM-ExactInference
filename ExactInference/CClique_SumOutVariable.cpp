////////////////////////////////////////////////////////////////////////////////
// CClique_SumOutVariable.cpp
// ���ݸ����������������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CClique.h"


//���ݸ����������������
void CClique::SumOutVariable(fid_t nVariableID)
{
	if (size_t nRemovePos = qy::ranges::index_of(m_VariableIDs, nVariableID); nRemovePos != -1)
	{
		//����1���������ID���б�
		m_VariableIDs.erase(m_VariableIDs.begin() + nRemovePos);

		//����2���������ֵ��ID�б�  ɾ����������ı���ֵ
		for (CliqueRow& t : m_CliqueRows)
			t.ValueIDs.erase(t.ValueIDs.begin() + nRemovePos);

		//����3������������Ӧ�������  ��ValueIDs��ͬ���кϲ�����һ�γ��ֵ���
		for (auto it = m_CliqueRows.begin(); it != m_CliqueRows.end();)
		{
			auto jt = std::ranges::find(m_CliqueRows.begin(), it, it->ValueIDs, &CliqueRow::ValueIDs);
			if (jt != it) {
				jt->fValue += it->fValue;
				it = m_CliqueRows.erase(it);
			} else
			{
				it++;
			}
		}
	}
}
