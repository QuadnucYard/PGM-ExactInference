/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_SendCliqueMessage_Downward.cpp
//��  �ܣ�		���·�������Ϣ
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��04��
//��  �£�		2021��05��18��
//��  �ȣ�		60��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//���·�������Ϣ
void CCliqueTree::SendCliqueMessage_Downward(fid_t nID, fid_t nChildID)
{	
	//�ҵ��ཻ�ı���ID����
	fidset CommonVariableIDs = FindCommonVariableIDs(nID, nChildID);
	//nID(��)����nChildID
	
	// ������nID����nParentID

		//��ȡ�ŵ�λ��
	fid_t nPos = GetCliquePosByID(nID);

	//��ȡ��Ҫ��͵��ı���ID����
	fidset EliminateVariableIDs;
	//�󼯺ϵĲ�ŵı�������-���������=��͵��ı�������
	std::ranges::set_difference(m_Cliques[nPos].GetVariableIDs(), CommonVariableIDs,
		std::inserter(EliminateVariableIDs, EliminateVariableIDs.end()));

	//����  �Ӹ�ָ����
	SEP_SET sep_set(nID, nChildID, m_Cliques[nPos], true);

	//����������������
	for (fid_t s : EliminateVariableIDs)
	{
		sep_set.clique.SumOutVariable(s);
	}

	m_SEPSets.push_back(sep_set);
}