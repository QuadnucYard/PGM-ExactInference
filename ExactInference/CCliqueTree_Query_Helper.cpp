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
void CCliqueTree::Query_Helper(const CT_QUERY& query)
{
	//////////////////////////////////////////////////////////////////////////////
	//����1�����ݱ�Ե�����͸�����������ȡ��ѯ����ID�ļ���
	fidset QueryVariableIDs;
	std::ranges::transform(query.MarginalVariables, std::inserter(QueryVariableIDs, QueryVariableIDs.end()),
		&CT_GROUNDING_VARIABLE::nVariableID);
	std::ranges::transform(query.GivenVariables, std::inserter(QueryVariableIDs, QueryVariableIDs.end()),
		&CT_GROUNDING_VARIABLE::nVariableID);
	
	/////////////////////////////////////////////////////////////////////////////
	//����2�����������ţ���ȡ��ʼ�ŵ�ID���Ӱ�����ѯ��������һ���ſ�ʼ
	fid_t nStartCliquePos = GetStartCliquePos(QueryVariableIDs);
	
	/////////////////////////////////////////////////////////////////////////////
	//����3��������ȱ����ţ������Ե���ʻ���������		
	Query_Probability(query, QueryVariableIDs, nStartCliquePos);
}