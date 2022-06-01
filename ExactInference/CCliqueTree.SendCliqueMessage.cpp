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
void CCliqueTree::SendCliqueMessage(unsigned int nID)
{
	//�ҵ�˫�׽ڵ�
	unsigned int nParentID;

	//����ҵ�˫��,��ͨ��������ȡ˫��ID
	if (IsThereParentID(nID, nParentID))
	{
		//�ҵ��������ཻ�ı���ID����
		set<unsigned int> CommonVariableIDs;

		//��ȡ�����ŵı���ID����
		FindCommonVariableIDs(nID, nParentID, CommonVariableIDs);

		//��ȡ�ŵ�λ��
		unsigned int nPos = GetCliquePosByID(nID);
		//���岢��ȡ�ŵı�������
		set<unsigned int> CliqueVariableIDs = m_Cliques[nPos].GetVariableIDs();
		//��ȡ��Ҫ��͵��ı���ID����
		set<unsigned int> EliminateVariableIDs;

		//�󼯺ϵĲ�ŵı�������-���������=��͵��ı�������
		std::ranges::set_difference(CliqueVariableIDs, CommonVariableIDs, 
			std::inserter(EliminateVariableIDs, EliminateVariableIDs.end()));

		//����
		SEP_SET sep_set;
		sep_set.nStartID = nID;
		sep_set.nEndID = nParentID;
		sep_set.clique = m_Cliques[nPos];
		sep_set.bReady = false;//���ϴ�����Ϣ
		
		//����������������
		for (set<unsigned int>::iterator it = EliminateVariableIDs.begin(); it != EliminateVariableIDs.end(); it++)
		{
			//��͵�����
			sep_set.clique.SumOutVariable(*it);
		}

		//��ӵ���б�
		m_SEPSets.push_back(sep_set);
	}
}

//��  �ƣ�		FindCommonVariableID()
//��  �ܣ�		�������ŵı���ID����
//��  ����		unsigned int,unsigned int
//����ֵ��		��
void CCliqueTree::FindCommonVariableIDs(unsigned int nID1, unsigned int nID2, set<unsigned int>& Intersections)
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
bool CCliqueTree::IsThereParentID(unsigned int nID, unsigned int& nParentID)
{
	//������ŵ����в���
	map<unsigned int, unsigned int>::iterator it = m_UpwardTree.find(nID);

	//����Ƿ��ҵ�˫��
	if (it != m_UpwardTree.end())
	{
		//��ֵ����ȡ˫��ID
		nParentID = it->second;

		//������
		return true;
	}
	else
	{
		//���ؼ�
		return false;
	}
}
