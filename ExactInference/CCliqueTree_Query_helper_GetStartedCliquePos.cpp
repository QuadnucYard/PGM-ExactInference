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
size_t CCliqueTree::GetStartCliquePos(const fidset& QueryVariableIDs)
{
	//���岢��ʼ�������ŵ�λ��
	size_t nStartCliquePos = 0;
	
	//���忪ʼ���а�����ѯ����ID�ĸ������Ա�����֮����бȽ�
	size_t nIntersectedVariableCount = 0;
	
	//���������ţ����ҿ�ʼ��
	for (size_t i = 0; i < m_Cliques.size(); i++)
	{

		//�����ID�б����ж��ٸ��ڲ�ѯ����������
		fidset IntersectedIDs;//�ڲ�ѯ���������еı���ID����
		std::ranges::set_intersection(m_Cliques[i].GetCliqueVariableIDs(), QueryVariableIDs, qy::set_inserter(IntersectedIDs));

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
