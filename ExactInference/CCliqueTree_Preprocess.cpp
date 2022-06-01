/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CClique_Preprocess.cpp
//��  �ܣ�		Ԥ��������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��31��
//��  �£�		2021��05��18��
//��  �ȣ�		90��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//Ԥ��������
void CCliqueTree::Preprocess()
{
	//����BN�е����нڵ�
	for (const CT_NODE& node : m_CTNodes)
	{
		//��������
		CClique clique;

		//////////////////////////////////////////////////////////////
		//����1����ʼ���š�������ID
		clique.SetCliqueID(node.nID);
		//�����ŵı���ID�б�
		clique.SetCliqueVariableIDs(node.VariableIDs);

		//��������ID����ID�Ķ�ӳ��
		for (fid_t var : node.VariableIDs)
		{
			m_VariableID2CliqueIDs.insert({var, node.nID});
		}

		//////////////////////////////////////////////////////////////
		//����2����ʼ���š���������
		for (const CT_FACTOR_ROW& row : node.FactorRows)
		{
			clique.SetCliqueRow(row.ValueIDs, row.fValue);
		}

		//�����ŵ�ID��λ�õ�ӳ��
		m_CliqueID2Poses.insert({clique.GetID(), m_Cliques.size()});

		//��ӵ��ű�
		m_Cliques.push_back(clique);
	}
}

//��ȡ�ŵ�λ��
fid_t CCliqueTree::GetCliquePosByID(fid_t nCliqueID)
{
	return m_CliqueID2Poses[nCliqueID];
}