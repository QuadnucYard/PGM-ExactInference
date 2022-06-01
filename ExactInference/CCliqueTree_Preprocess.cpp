////////////////////////////////////////////////////////////////////////////////
// CClique_Preprocess.cpp
// Ԥ��������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//Ԥ��������
void CCliqueTree::Preprocess()
{
	//����BN�е����нڵ�
	for (const CT_NODE& node : m_CTNodes)
	{
		CClique clique;
		clique.SetCliqueID(node.nID);
		clique.SetCliqueVariableIDs(node.VariableIDs);

		//��������ID����ID�Ķ�ӳ��
		for (fid_t var : node.VariableIDs)
		{
			m_VariableID2CliqueIDs.insert({var, node.nID});
		}

		//����2����ʼ���š���������
		for (const CT_FACTOR_ROW& row : node.FactorRows)
		{
			clique.SetCliqueRow(row.ValueIDs, row.fValue);
		}

		//�����ŵ�ID��λ�õ�ӳ��
		m_CliqueID2Poses.insert({clique.GetID(), m_Cliques.size()});
		m_Cliques.push_back(clique);
	}
}

//��ȡ�ŵ�λ��
const CClique& CCliqueTree::GetCliquePosByID(fid_t nCliqueID) const
{
	return m_Cliques.at(m_CliqueID2Poses.at(nCliqueID));
}

CClique& CCliqueTree::GetCliquePosByID(fid_t nCliqueID)
{
	return m_Cliques.at(m_CliqueID2Poses.at(nCliqueID));
}