/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CClique_SumOutVariable.cpp
//��  �ܣ�		���ݸ����������������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��31��
//��  �£�		2021��04��12��
//��  �£�		2021��05��18��
//��  �ȣ�		150��
/////////////////////////////////////////////////////////////////////////////////////////////
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
		for (CLIQUE_ROW& t : m_CliqueRows)
			t.ValueIDs.erase(t.ValueIDs.begin() + nRemovePos);

		//����3������������Ӧ�������  ��ValueIDs��ͬ���кϲ�����һ�γ��ֵ���
		for (auto it = m_CliqueRows.begin(); it != m_CliqueRows.end();)
		{
			auto jt = std::ranges::find(m_CliqueRows.begin(), it, it->ValueIDs, &CLIQUE_ROW::ValueIDs);
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
