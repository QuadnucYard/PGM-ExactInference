////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_Query_Helper_GetStartedCliquePos.cpp
// ��ȡ��ѯ��ʼ���ŵ�λ��
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//��ȡ��ѯ��ʼ���ŵ�λ��
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
		fidset IntersectedIDs = qy::set_intersection<fidset>(m_Cliques[i].GetVariableIDs(), QueryVariableIDs);

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
