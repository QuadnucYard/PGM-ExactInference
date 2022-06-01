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
	for (unsigned int i = 0; i < m_CTNodes.size(); i++)
	{
		//��������
		CClique clique;

		//////////////////////////////////////////////////////////////
		//����1����ʼ���š�������ID
		clique.SetCliqueID(m_CTNodes[i].nID);
		//�����ŵı���ID�б�
		clique.SetCliqueVariableIDs(m_CTNodes[i].VariableIDs);

		//��������ID����ID�Ķ�ӳ��
		for (unsigned int j = 0; j < m_CTNodes[i].VariableIDs.size(); j++)
		{
			//��ӵ���ӳ��
			unsigned int nVariableID = m_CTNodes[i].VariableIDs[j];
			unsigned int nCliqueID = m_CTNodes[i].nID;

			m_VariableID2CliqueIDs.insert(make_pair(nVariableID,nCliqueID));
		}


		//////////////////////////////////////////////////////////////
		//����2����ʼ���š���������
		for (unsigned int j = 0; j < m_CTNodes[i].FactorRows.size(); j++)
		{
			//��ȡֵID�ı��˴��ƺ������⡣
			vector<unsigned int> ValueIDs = m_CTNodes[i].FactorRows[j].ValueIDs;
			//��ȡ����ֵ
			double fValue = m_CTNodes[i].FactorRows[j].fValue;

			//��������
			clique.SetCliqueRow(ValueIDs, fValue);
		}

		//�����ŵ�ID��λ�õ�ӳ��
		unsigned int nPos = m_Cliques.size();
		unsigned int nCliqueID = clique.GetID();
		m_CliqueID2Poses.insert(make_pair(nCliqueID, nPos));

		//��ӵ��ű�
		m_Cliques.push_back(clique);
	}
}

//��ȡ�ŵ�λ��
fid_t CCliqueTree::GetCliquePosByID(fid_t nCliqueID)
{
	//�����ŵ�ID��λ�õ�ӳ��
	if (auto it = m_CliqueID2Poses.find(nCliqueID); it != m_CliqueID2Poses.end())
		return it->second;
	else
		return 0;
}