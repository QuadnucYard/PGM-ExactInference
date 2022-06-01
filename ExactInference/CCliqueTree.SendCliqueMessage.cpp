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
		SubtractBetweenSets(CliqueVariableIDs, CommonVariableIDs, EliminateVariableIDs);

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
	//��ȡ�ڵ�1�ı�������
	set <unsigned int> VariableIDs1 = m_Cliques[nID1].GetVariableIDs();
	
	//��ȡ�ڵ�2�ı�������
	set <unsigned int> VariableIDs2 = m_Cliques[nID2].GetVariableIDs();

	//���������ϵĽ���
	FindIntersections(VariableIDs1, VariableIDs2, Intersections);
}

//��  �ƣ�		FindIntersections()
//��  �ܣ�		���������ϵĽ���
//��  ����		set<unsigned int>&,set<unsigned int>&,set<unsigned int>&
//����ֵ��		��
void CCliqueTree::FindIntersections(set<unsigned int>& s1, set<unsigned int>& s2, set<unsigned int>& s)
{
	for (set<unsigned int>::iterator it = s1.begin(); it != s1.end(); it++)
	{
		//����ID
		unsigned int nID = *it;
		
		//�����Ƿ��ڼ���
		if (IsINTInSet(nID, s2))
		{
			//��ӵ�����
			s.insert(*it);
		}
	}
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

//��  �ƣ�		SubtractBetweenSets()
//��  �ܣ�		���������ϵĲ�
//��  ����		set<unsigned int>&,set<unsigned int>&,set<unsigned int>&
//				����1������2���������ϵĲ�
//����ֵ��		��
void CCliqueTree::SubtractBetweenSets(set<unsigned int>& s1, set<unsigned int>& s2, set<unsigned int>& s)
{
	//��������1
	for (set<unsigned int>::iterator it = s1.begin(); it != s1.end(); it++)
	{
		//����ID
		unsigned int nID = *it;
		
		//�����Ƿ��ڼ���2��
		if (!IsINTInSet(nID, s2))
		{
			//��������ڣ�����ӵ��
			s.insert(*it);
		}
	}
}