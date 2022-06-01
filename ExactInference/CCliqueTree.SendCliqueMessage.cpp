////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_SendCliqueMessage.cpp
// ��������Ϣ
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//��������Ϣ
void CCliqueTree::SendCliqueMessage(fid_t nID)
{
	//�ҵ�˫�׽ڵ�
	fid_t nParentID;

	//����ҵ�˫��,��ͨ��������ȡ˫��ID
	if (IsThereParentID(nID, nParentID))
	{
		//�ҵ��������ཻ�ı���ID����
		fidset CommonVariableIDs = FindCommonVariableIDs(nID, nParentID);

		//��ȡ�ŵ�λ��
		fid_t nPos = GetCliquePosByID(nID);

		//��ȡ��Ҫ��͵��ı���ID����
		fidset EliminateVariableIDs;
		//�󼯺ϵĲ�ŵı�������-���������=��͵��ı�������
		std::ranges::set_difference(m_Cliques[nPos].GetVariableIDs(), CommonVariableIDs,
			std::inserter(EliminateVariableIDs, EliminateVariableIDs.end()));

		//����  ����ָ��
		SEP_SET sep_set(nID, nParentID, m_Cliques[nPos]);
		
		//����������������
		for (fid_t s: EliminateVariableIDs)
		{
			sep_set.clique.SumOutVariable(s);
		}

		m_SEPSets.push_back(sep_set);
	}
}

//�������ŵı���ID����
fidset CCliqueTree::FindCommonVariableIDs(fid_t nID1, fid_t nID2)
{
	fidset Intersections;
	std::ranges::set_intersection(m_Cliques[nID1].GetVariableIDs(), m_Cliques[nID2].GetVariableIDs(),
		std::inserter(Intersections, Intersections.end()));
	return Intersections;
}

//����˫���Ƿ���ڣ�������ڣ��򷵻�˫��ID
//				���Ƿ����˫�ס�����еĻ�����ͨ��������ȡ˫��ID
bool CCliqueTree::IsThereParentID(fid_t nID, fid_t& nParentID)
{
	//������ŵ����в���
	if (auto it = m_UpwardTree.find(nID); it != m_UpwardTree.end())
	{
		//��ֵ����ȡ˫��ID
		nParentID = it->second;
		return true;
	}
	else
	{
		return false;
	}
}
