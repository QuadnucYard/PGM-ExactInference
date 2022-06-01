////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_SendCliqueMessage_Downward.cpp
// ���·�������Ϣ
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//���·�������Ϣ
void CCliqueTree::SendCliqueMessage_Downward(fid_t nID, fid_t nChildID)
{	
	//�ҵ��ཻ�ı���ID����
	fidset CommonVariableIDs = FindCommonVariableIDs(nID, nChildID);
	//nID(��)����nChildID

	const CClique& c = m_Cliques[GetCliquePosByID(nID)];
	//��ȡ��Ҫ��͵��ı���ID����
	fidlist EliminateVariableIDs = qy::set_difference<fidlist>(c.GetVariableIDs(), CommonVariableIDs);

	//����  �Ӹ�ָ����
	SEP_SET sep_set(nID, nChildID, c, true);

	//����������������
	for (fid_t s : EliminateVariableIDs)
	{
		sep_set.clique.SumOutVariable(s);
	}

	m_SEPSets.push_back(sep_set);
}