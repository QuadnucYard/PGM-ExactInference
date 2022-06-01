/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_SendCliqueMessage.cpp
//��  �ܣ�		��������Ϣ
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��03��
//��  �£�		2021��05��18��
//��  �ȣ�		150��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		SendCliqueMessage()
//��  �ܣ�		��������Ϣ
//��  ����		unsigned int
//				������ID
//����ֵ��		��
void CCliqueTree::SendCliqueMessage(fid_t nID)
{
	//�ҵ�˫�׽ڵ�
	fid_t nParentID;

	//����ҵ�˫��,��ͨ��������ȡ˫��ID
	if (IsThereParentID(nID, nParentID))
	{
		//�ҵ��������ཻ�ı���ID����
		fidset CommonVariableIDs;

		//��ȡ�����ŵı���ID����
		FindCommonVariableIDs(nID, nParentID, CommonVariableIDs);

		//��ȡ�ŵ�λ��
		fid_t nPos = GetCliquePosByID(nID);

		//��ȡ��Ҫ��͵��ı���ID����
		fidset EliminateVariableIDs;
		//�󼯺ϵĲ�ŵı�������-���������=��͵��ı�������
		std::ranges::set_difference(m_Cliques[nPos].GetVariableIDs(), CommonVariableIDs,
			std::inserter(EliminateVariableIDs, EliminateVariableIDs.end()));

		//����
		SEP_SET sep_set(nID, nParentID, m_Cliques[nPos]);
		
		//����������������
		for (fid_t s: EliminateVariableIDs)
		{
			sep_set.clique.SumOutVariable(s);
		}

		m_SEPSets.push_back(sep_set);
	}
}

//��  �ƣ�		FindCommonVariableID()
//��  �ܣ�		�������ŵı���ID����
//��  ����		unsigned int,unsigned int
//����ֵ��		��
void CCliqueTree::FindCommonVariableIDs(fid_t nID1, fid_t nID2, fidset& Intersections)
{
	std::ranges::set_intersection(m_Cliques[nID1].GetVariableIDs(), m_Cliques[nID2].GetVariableIDs(),
		std::inserter(Intersections, Intersections.end()));
}

//��  �ƣ�		IsThereParentID()
//��  �ܣ�		����˫���Ƿ���ڣ�������ڣ��򷵻�˫��ID
//��  ����		unsigned int,unsigned int&
//				��ID����˫��ID
//����ֵ��		bool
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
