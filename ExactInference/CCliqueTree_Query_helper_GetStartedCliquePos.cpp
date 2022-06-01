/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_Query_Helper_GetStartedCliquePos.cpp
//��  �ܣ�		��ȡ��ѯ��ʼ���ŵ�λ��
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��12��
//��  �£�		2021��05��18��
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		Query_Helper_GetStartedCliquePos()
//��  �ܣ�		��ȡ��ѯ��ʼ���ŵ�λ��
//��  ����		set<unsigned int>&
//				��ѯ��������
//����ֵ��		unsigned int
//				��ѯ�������ĸ�
//��  ����		ѡȡ������ѯ���������ţ���Ϊ��ʼ��
unsigned int CCliqueTree::GetStartCliquePos(set<unsigned int>& QueryVariableIDs)
{
	//���岢��ʼ�������ŵ�λ��
	unsigned int nStartCliquePos = 0;
	
	//���忪ʼ���а�����ѯ����ID�ĸ������Ա�����֮����бȽ�
	unsigned int nIntersectedVariableCount = 0;	
	
	//���������ţ����ҿ�ʼ��
	for (unsigned int i = 0; i < m_Cliques.size(); i++)
	{
		//��ȡ���б���ID�б�
		vector<unsigned int> CliqueVariableIDs = m_Cliques[i].GetCliqueVariableIDs();

		//�����ID�б����ж��ٸ��ڲ�ѯ����������
		set<unsigned int> IntersectedIDs;//�ڲ�ѯ���������еı���ID����
		GetIntersections(CliqueVariableIDs, QueryVariableIDs, IntersectedIDs);

		//����Ƿ�������е���
		if (IntersectedIDs.size() >= nIntersectedVariableCount)
		{
			//���¿�ʼ��
			nStartCliquePos = i;
			nIntersectedVariableCount = IntersectedIDs.size();
		}
	}

	//���ؿ�ʼ�ŵ�λ��
	return nStartCliquePos;
}

//��  �ƣ�		GetIntersections()
//��  �ܣ�		���б�ͼ��ϵĽ���
//��  ����		vector<unsigned int>&,set<unsigned int>&
//				set<unsigned int>&
//����ֵ��		��
void CCliqueTree::GetIntersections(vector<unsigned int>& VectorIDs, set<unsigned int>& SetIDs, set<unsigned int>& IntersectedIDs)
{
	//�����б�
	for (unsigned int i = 0; i < VectorIDs.size(); i++)
	{
		//����Ƿ��ཻ
		if (IsINTInSet(VectorIDs[i], SetIDs))
		{			
			//��ӵ��������
			IntersectedIDs.insert(VectorIDs[i]);
		}
	}
}