/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_Query_Probability_GetSubtract.cpp
//��  �ܣ�		��ȡ�б�ͼ��ϵĲ�
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��12��
//��  �£�		
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		GetSubstract()
//��  �ܣ�		��ȡ�б�ͼ��ϵĲ�
//��  ����		vector<unsigned int>&,set<unsigned int>&
//����ֵ��		��
vector<unsigned int> CCliqueTree::GetSubstract(vector<unsigned int>&LastVariableIDs, set<unsigned int>& VariableIDs)
{
	//���巵�ؽ��
	vector<unsigned int> Results;

	//������������
	for (unsigned int i = 0; i < LastVariableIDs.size(); i++)
	{
		//������ID�Ƿ��ڼ�����
		if (!IsINTInSet(LastVariableIDs[i], VariableIDs))
		{
			//��ӵ����ؽ��
			Results.push_back(LastVariableIDs[i]);
		}
	}

	//���ؽ��
	return Results;
}