////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_Query_Helper.cpp
// ��ѯ�ĸ�������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//��ѯ�ĸ�������
fval_t CCliqueTree::Query_Helper(const CTQuery& query) const
{
	//����1�����ݱ�Ե�����͸�����������ȡ��ѯ����ID�ļ���
	fidset QueryVariableIDs;
	std::ranges::transform(query.MarginalVariables, qy::set_inserter(QueryVariableIDs),
		&GroundingVariable::nVariableID);
	std::ranges::transform(query.GivenVariables, qy::set_inserter(QueryVariableIDs),
		&GroundingVariable::nVariableID);
	
	//����2�����������ţ���ȡ��ʼ�ŵ�ID���Ӱ�����ѯ��������һ���ſ�ʼ
	//����3��������ȱ����ţ������Ե���ʻ���������		
	return Query_Probability(query, QueryVariableIDs, GetStartClique(QueryVariableIDs));
}