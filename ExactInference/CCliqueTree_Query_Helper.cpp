////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_Query_Helper.cpp
// ��ѯ�ĸ�������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//��ѯ�ĸ�������
void CCliqueTree::Query_Helper(const CT_QUERY& query)
{
	//����1�����ݱ�Ե�����͸�����������ȡ��ѯ����ID�ļ���
	fidset QueryVariableIDs;
	std::ranges::transform(query.MarginalVariables, qy::set_inserter(QueryVariableIDs),
		&CT_GROUNDING_VARIABLE::nVariableID);
	std::ranges::transform(query.GivenVariables, qy::set_inserter(QueryVariableIDs),
		&CT_GROUNDING_VARIABLE::nVariableID);
	
	//����2�����������ţ���ȡ��ʼ�ŵ�ID���Ӱ�����ѯ��������һ���ſ�ʼ
	//����3��������ȱ����ţ������Ե���ʻ���������		
	Query_Probability(query, QueryVariableIDs, GetStartClique(QueryVariableIDs));
}