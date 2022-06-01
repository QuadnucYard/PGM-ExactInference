/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_Query_Marginal.cpp
//��  �ܣ�		��ѯ��Ե����
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��11��
//��  �£�		2021��04��12��
//��  �£�		2021��05��18��
//��  �ȣ�		130��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		Query_Probability()
//��  �ܣ�		��ѯ����
//��  ����		CT_QUERY&,set<unsigned int>&,unsigned int
//����ֵ��		��
void CCliqueTree::Query_Probability(const CT_QUERY& query, const fidset& QueryVariableIDs, size_t nStartCliquePos)
{
	//��ȡ��ʼ��ID
	fid_t nStartCliqueID = m_Cliques[nStartCliquePos].GetID();

	//��ȡ��ʼ�Ű����Ĳ�ѯ��������
	fidset StartVariableIDs;
	std::ranges::set_intersection(qy::sorted(m_Cliques[nStartCliquePos].GetCliqueVariableIDs()), QueryVariableIDs, qy::set_inserter(StartVariableIDs));

	//�����š�����ʼ��Ϊ��ʼ��
	CClique theClique = m_Cliques[nStartCliquePos];

	//��ʼ��OPEN�б�
	std::queue<fid_t> OPEN;
	OPEN.push(nStartCliqueID);
	//����CLOSED��
	fidset CLOSED;

	///////////////////////////////////////////////////////////////////////////////////////////
	//����1��������ȹ����ѯ�漰����������ͬʱ���㵱ǰ����
	while (!OPEN.empty())
	{
		//��ǰ��ID����
		fid_t nID = OPEN.front();
		OPEN.pop();

		//����ǰ��ID����CLOSED��������ֿ��涯��
		CLOSED.insert(nID);

		//���ҵ�ǰ��ID�ĺ��
		multimap<unsigned int, unsigned int>::iterator beg = m_CTEdges.lower_bound(nID);
		multimap<unsigned int, unsigned int>::iterator end = m_CTEdges.upper_bound(nID);
		//����Ƿ���ں�̣����������
		while (beg != end)
		{
			//��ȡ�����ID
			fid_t nChildID = beg->second;

			//����̽ڵ��Ƿ���CLOSED������Ѿ����ڣ�����Ҫ���
			if (!qy::ranges::includes(CLOSED, nChildID))
			{
				//����ǰ���Ӻͺ���������ӻ�
				CClique product_clique = m_Cliques[GetCliquePosByID(nChildID)];
				theClique = theClique * product_clique;

				//���͸�����ӳ���ע�⣺Ҫ�ҵ�����У׼�ĸ
				size_t nSEPSetPos = GetSEPSetPos(nID, nChildID);
				CClique divide_clique = m_SEPSets[nSEPSetPos].clique;
				theClique = theClique / divide_clique;

				//��ӵ�OPEN��
				OPEN.push(nChildID);

				//����Ƿ��Ѿ��������б���
				//������������ID����
				fidset AddVariableIDs;
				//��ȡ��������ID����
				std::ranges::set_intersection(qy::sorted(m_Cliques[GetCliquePosByID(nChildID)].GetCliqueVariableIDs()), QueryVariableIDs, qy::set_inserter(AddVariableIDs));

				//��ӵ���ʼ����ID���ϡ�����ǰ����ID����
				StartVariableIDs.insert(AddVariableIDs.begin(), AddVariableIDs.end());
				//������ID�����Ƿ��Ѿ��������в�ѯ����  query������start
				if (std::ranges::includes(StartVariableIDs, QueryVariableIDs))
				{
					//�Ѿ��������в�ѯ����ID����ֹ����ѭ��
					goto line10;
				}
			}

			//���µ�����
			beg++;
		}
	}


	///////////////////////////////////////////////////////////////
	//����2�����������͵�����Ҫ�ı���
line10:
	//������͵��ı�������
	fidlist SumOutVariableIDs;
	std::ranges::set_difference(qy::sorted(theClique.GetCliqueVariableIDs()), QueryVariableIDs, std::back_inserter(SumOutVariableIDs));
	//��͵��������
	for (fid_t var : SumOutVariableIDs)
	{
		theClique.SumOutVariable(var);
	}


	/////////////////////////////////////////////////////////////////////
	//����3�����ݸ�����������
	for (const CT_GROUNDING_VARIABLE& var : query.GivenVariables)
	{
		theClique.ReduceGivenVariable(var.nVariableID, var.nValueID);
	}

	////////////////////////////////////////////////////////////////////
	//����4����һ����
	theClique.Normalize();

	////////////////////////////////////////////////////////////////////
	//����5����ȡ����
	fidlist VariableIDs = query.MarginalVariables | std::views::transform(&CT_GROUNDING_VARIABLE::nVariableID) | qy::views::to<fidlist>;
	fidlist ValueIDs = query.MarginalVariables | std::views::transform(&CT_GROUNDING_VARIABLE::nValueID) | qy::views::to<fidlist>;

	//��Ӹ��ʵ���ѯ���
	m_CTQueryResults.push_back(theClique.Query(VariableIDs, ValueIDs));
}