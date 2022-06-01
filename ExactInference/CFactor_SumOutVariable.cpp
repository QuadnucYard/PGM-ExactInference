////////////////////////////////////////////////////////////////////////////////
// CFactor_SumOutVariable.cpp
// ���ݸ������������������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CFactor.h"
#include <unordered_map>


void CFactor::SumOutVariable(fid_t nVariableID)
{
	if (size_t nRemovePos = qy::ranges::index_of(m_VariableIDs, nVariableID); nRemovePos != -1) 
	{
		//�ҵ�����ID����Ҫ������ͻ���

		//����1���������ID���б�
		m_VariableIDs.erase(m_VariableIDs.begin() + nRemovePos);

		//����2���������ֵ��ID�б�  ɾ����������ı���ֵ
		for (FACTOR_ROW& t : m_FactorRows)
			t.ValueIDs.erase(t.ValueIDs.begin() + nRemovePos);

		//����3������������Ӧ�������  ��ValueIDs��ͬ���кϲ�����һ�γ��ֵ���
		for (auto it = m_FactorRows.begin(); it != m_FactorRows.end();)
		{
			auto jt = std::ranges::find(m_FactorRows.begin(), it, it->ValueIDs, &FACTOR_ROW::ValueIDs);
			if (jt != it) {
				jt->fValue += it->fValue;
				it = m_FactorRows.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
}
