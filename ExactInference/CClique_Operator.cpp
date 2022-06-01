////////////////////////////////////////////////////////////////////////////////
// CClique_Operator.cpp
// ���ز�������ء���Ҫ�����ӻ����������������ӳ�
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CClique.h"


//����������е�ֵID�Ƿ���ݣ������жϳ˻�ʱ�ܷ�ϲ�
bool CClique::IsConsistentValueID(const CLIQUE_ROW& FirstRow, const CLIQUE_ROW& SecondRow, const fidmap& FirstToSeconds) const
{
	return std::ranges::all_of(FirstToSeconds,
		[&](auto t) { return FirstRow[t.first] == SecondRow[t.second]; });
}

//�������ӻ�
CClique CClique::operator*(const CClique& second) const
{
	CClique clique;
	//ע�⣺�����ӻ���Ҫ������ID�����ǲ���ģ�������Ӳ�ͬ�������Ƕ�̬�仯��
	clique.m_nCliqueID = m_nCliqueID;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//����1���������ŵĽ�������ͬ����ID�ļ���		
	//������ͬ����ID���ӵ����ŵ���β��λ�õ�ӳ�䡣�����3��������Ӧ�ڵ�5������
	fidmap FirstToSeconds;

	//����1.1���������ŵı���ID
	for (size_t i = 0; i < m_VariableIDs.size(); i++)
	{
		for (fid_t j = 0; j < second.m_VariableIDs.size(); j++)
		{
			if (m_VariableIDs[i] == second.m_VariableIDs[j])
			{
				//��ӵ���ͬ��������������ָ��β���ӵ�λ��ӳ��
				//ע�⣺���ô�λ�õ�λ�õ�ӳ�䣬�����Ǵӱ���ID������ID��ӳ��
				FirstToSeconds.insert(std::make_pair(i, j));
			}
		}
	}

	//����1.2����ȡβ���к�������ͬ������λ�ü���
	fidset RedundantSeconds(std::views::values(FirstToSeconds) | qy::views::to<fidset>);

	//���ƴ��
	for (const CLIQUE_ROW& r1 : m_CliqueRows)
	{
		for (const CLIQUE_ROW& r2 : second.m_CliqueRows)
		{
			if (IsConsistentValueID(r1, r2, FirstToSeconds))
			{
				clique.m_CliqueRows.emplace_back(
					qy::concat(r1.ValueIDs,
						qy::range(r2.ValueIDs)
						| std::views::filter([&](int i) { return !RedundantSeconds.contains(i); })
						| std::views::transform([&](int i) { return r2.ValueIDs[i]; })
						| qy::views::to<fidlist>
					),
					r1.fValue * r2.fValue
				);
			}
		}
	}

	//����3.2����ӱ���ID���б�
	clique.m_VariableIDs = qy::concat(m_VariableIDs,
		qy::range(second.m_VariableIDs)
		| std::views::filter([&](int i) { return !RedundantSeconds.contains(i); })
		| std::views::transform([&](int i) { return second.m_VariableIDs[i]; })
		| qy::views::to<fidlist>
	);

	return clique;
};

CClique CClique::operator/(const CClique& second) const
{
	CClique clique;
	clique.m_VariableIDs = m_VariableIDs;

	//����1���������ŵĽ�������ͬ����ID�ļ���		
	//������ͬ����ID���ӵ������ӵ���β����λ�õ�ӳ�䡣�����3��������Ӧ�ڵ�5������
	fidmap FirstToSeconds;
	//����1.1�����������ӵı���ID
	for (size_t i = 0; i < m_VariableIDs.size(); i++)
	{
		for (fid_t j = 0; j < second.m_VariableIDs.size(); j++)
		{
			if (m_VariableIDs[i] == second.m_VariableIDs[j])
			{
				FirstToSeconds.insert(std::make_pair(i, j));
			}
		}
	}

	//����1.2����ȡβ�����к���������ͬ������λ�ü���
	fidset RedundantSeconds(std::views::values(FirstToSeconds) | qy::views::to<fidset>);

	//����2�����ӳ�
	//˵���������ŵ�Ͻ��һ���������ŵ�Ͻ��
	for (const CLIQUE_ROW& r1 : m_CliqueRows)
	{
		for (const CLIQUE_ROW& r2 : second.m_CliqueRows)
		{
			if (IsConsistentValueID(r1, r2, FirstToSeconds))
			{
				clique.m_CliqueRows.emplace_back(r1.ValueIDs, r1.fValue / r2.fValue);
			}
		}
	}

	return clique;
};