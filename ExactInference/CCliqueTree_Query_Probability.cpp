////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_Query_Marginal.cpp
// ��ѯ��Ե����
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//��ѯ����
void CCliqueTree::Query_Probability(const CT_QUERY& query, const fidset& QueryVariableIDs, const CClique& startClique)
{
	//��ȡ��ʼ��ID
	fid_t nStartCliqueID = startClique.GetID();

	//��ȡ��ʼ�Ű����Ĳ�ѯ��������
	fidset StartVariableIDs = qy::set_intersection<fidset>(startClique.GetVariableIDs(), QueryVariableIDs);

	//�����š�����ʼ��Ϊ��ʼ��
	CClique theClique = startClique;

	std::queue<fid_t> OPEN;
	OPEN.push(nStartCliqueID);
	fidset CLOSED;

	//����1��������ȹ����ѯ�漰����������ͬʱ���㵱ǰ����
	while (!OPEN.empty())
	{
		fid_t nID = OPEN.front();
		OPEN.pop();
		//����ǰ��ID����CLOSED��������ֿ��涯��
		CLOSED.insert(nID);

		//���ҵ�ǰ��ID�ĺ��
		auto er = m_CTEdges.equal_range(nID);
		for (auto p : std::ranges::subrange(er.first, er.second)) {
			//��ȡ�����ID
			fid_t nChildID = p.second;

			//����̽ڵ��Ƿ���CLOSED������Ѿ����ڣ�����Ҫ���
			if (CLOSED.contains(nChildID)) continue;

			//����ǰ���Ӻͺ���������ӻ�
			//���͸�����ӳ���ע�⣺Ҫ�ҵ�����У׼�ĸ
			theClique = theClique
				* GetCliquePosByID(nChildID)
				/ GetReadySEPSet(nID, nChildID).clique;

			OPEN.push(nChildID);

			//����Ƿ��Ѿ��������б���
			//������������ID����
			fidset AddVariableIDs = qy::set_intersection<fidset>(GetCliquePosByID(nChildID).GetVariableIDs(), QueryVariableIDs);

			//��ӵ���ʼ����ID���ϡ�����ǰ����ID����
			StartVariableIDs.insert(AddVariableIDs.begin(), AddVariableIDs.end());
			//������ID�����Ƿ��Ѿ��������в�ѯ����  query������start
			if (std::ranges::includes(StartVariableIDs, QueryVariableIDs))
			{
				//�Ѿ��������в�ѯ����ID����ֹ����ѭ��
				break;
			}

		}
	}

	//����2�����������͵�����Ҫ�ı���
	//������͵��ı�������
	fidlist SumOutVariableIDs = qy::set_difference<fidlist>(theClique.GetVariableIDs(), QueryVariableIDs);
	//��͵��������
	for (fid_t var : SumOutVariableIDs)
	{
		theClique.SumOutVariable(var);
	}

	//����3�����ݸ�����������
	for (const CT_GROUNDING_VARIABLE& var : query.GivenVariables)
	{
		theClique.ReduceGivenVariable(var.nVariableID, var.nValueID);
	}

	//����4����һ����
	theClique.Normalize();

	//����5����ȡ����
	fidlist VariableIDs = query.MarginalVariables | std::views::transform(&CT_GROUNDING_VARIABLE::nVariableID) | qy::views::to<fidlist>;
	fidlist ValueIDs = query.MarginalVariables | std::views::transform(&CT_GROUNDING_VARIABLE::nValueID) | qy::views::to<fidlist>;

	//��Ӹ��ʵ���ѯ���
	m_CTQueryResults.push_back(theClique.Query(VariableIDs, ValueIDs));
}