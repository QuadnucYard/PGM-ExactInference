/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_Query_Helper.cpp
//��  �ܣ�		��ѯ�ĸ�������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��01��
//��  �£�		2021��04��12��
//��  �£�		2021��05��18��
//��  �ȣ�		60��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		Query_Helper()
//��  �ܣ�		��ѯ�ĸ�������
//��  ����		CT_QUERY&
//����ֵ��		��
void CCliqueTree::Query_Helper(CT_QUERY& query)
{
	//////////////////////////////////////////////////////////////////////////////
	//����1�����ݱ�Ե�����͸�����������ȡ��ѯ����ID�ļ���
	set<unsigned int> QueryVariableIDs;
	//�������б�Ե����ID
	for (unsigned int i = 0; i < query.MarginalVariables.size(); i++)
	{
		//��ȡ��ѯ����ID
		unsigned int nVariableID = query.MarginalVariables[i].nVariableID;

		//��ӵ���ѯ����ID�ļ���
		QueryVariableIDs.insert(nVariableID);
	}

	//�������и�������ID
	for (unsigned int i = 0; i < query.GivenVariables.size(); i++)
	{
		//��ȡ����ID
		unsigned int nVariableID = query.GivenVariables[i].nVariableID;

		//��ӵ���ѯ��������
		QueryVariableIDs.insert(nVariableID);
	}

	
	/////////////////////////////////////////////////////////////////////////////
	//����2�����������ţ���ȡ��ʼ�ŵ�ID���Ӱ�����ѯ��������һ���ſ�ʼ
	unsigned int nStartCliquePos = GetStartCliquePos(QueryVariableIDs);
	
	
	/////////////////////////////////////////////////////////////////////////////
	//����3��������ȱ����ţ������Ե���ʻ���������		
	Query_Probability(query, QueryVariableIDs, nStartCliquePos);
}