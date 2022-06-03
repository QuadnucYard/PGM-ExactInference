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
	fid_t nParentID;
	//����ҵ�˫��,��ͨ��������ȡ˫��ID
	if (IsThereParentID(nID, nParentID))
	{
		//�ҵ��������ཻ�ı���ID����
		fidset CommonVariableIDs = FindCommonVariableIDs(nID, nParentID);
		const CClique& c = GetCliquePosByID(nID);
		//��ȡ��Ҫ��͵��ı���ID����
		fidlist EliminateVariableIDs = qy::set_difference<fidlist>(c.GetVariableIDs(), CommonVariableIDs);

		//����  ����ָ��
		CutSet sep_set {nID, nParentID, c, false};

		//����������������
		for (fid_t s : EliminateVariableIDs)
		{
			sep_set.clique.SumOutVariable(s);
		}

		m_SEPSets.push_back(std::move(sep_set));
	}
}

//�������ŵı���ID����
fidset CCliqueTree::FindCommonVariableIDs(fid_t nID1, fid_t nID2) const
{
	fidset Intersections;
	std::ranges::set_intersection(m_Cliques[nID1].GetVariableIDs(), m_Cliques[nID2].GetVariableIDs(),
		std::inserter(Intersections, Intersections.end()));
	return Intersections;
}

//����˫���Ƿ���ڣ�������ڣ��򷵻�˫��ID
//				���Ƿ����˫�ס�����еĻ�����ͨ��������ȡ˫��ID
bool CCliqueTree::IsThereParentID(fid_t nID, fid_t& nParentID) const
{
	//������ŵ����в���
	if (auto it = m_UpwardTree.find(nID); it != m_UpwardTree.end())
	{
		//��ֵ����ȡ˫��ID
		nParentID = it->second;
		return true;
	} else
	{
		return false;
	}
}
