/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_Query_Probability_IsSetContainedIn.cpp
//��  �ܣ�		�жϼ����Ƿ��������һ������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��12��
//��  �£�		
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		IsSetContainedIn()
//��  �ܣ�		�жϼ����Ƿ��������һ����
//��  ����		set<unsigned int>&,set<unsigned int>&
//����ֵ��		bool
bool CCliqueTree::IsSetContainedIn(set<unsigned int>& QueryVariableIDs,set<unsigned int>& StartVariableIDs)
{
	//��������
	for (set<unsigned int>::iterator it = QueryVariableIDs.begin(); it != QueryVariableIDs.end(); it++)
	{
		//��ȡ��ǰID
		unsigned int nID = *it;

		//��鵱ǰID�Ƿ��ڼ���
		if (!IsINTInSet(nID, StartVariableIDs))
		{
			//���ؼ�
			return false;
		}
	}

	//ȱʡ������
	return true;
}