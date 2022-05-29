/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CFactor_SumOutVariable.cpp
//��  �ܣ�		���ݸ������������������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��13��
//��  �£�		2021��03��23��
//��  �£�		2021��03��29��
//��  �ȣ�		150��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CFactor.h"


void CFactor::SumOutVariable(fid_t nVariableID)
{
	//����Ƿ��ҵ�����ID
	if (size_t nRemovePos = qy::index_of(m_VariableIDs, nVariableID); nRemovePos != -1) 
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
			auto jt = std::find_if(m_FactorRows.begin(), it, [it](auto& t) {return t.ValueIDs == it->ValueIDs; });
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
