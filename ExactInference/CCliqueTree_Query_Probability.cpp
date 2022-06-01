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
void CCliqueTree::Query_Probability(CT_QUERY& query, set<unsigned int>& QueryVariableIDs, unsigned int nStartCliquePos)
{
	//��ȡ��ʼ��ID
	unsigned int nStartCliqueID = m_Cliques[nStartCliquePos].GetID();
	
	//��ȡ��ʼ�Ű����Ĳ�ѯ��������
	set<unsigned int> StartVariableIDs;
	GetIntersections(m_Cliques[nStartCliquePos].GetCliqueVariableIDs(), QueryVariableIDs, StartVariableIDs);
	
	//�����š�����ʼ��Ϊ��ʼ��
	CClique theClique = m_Cliques[nStartCliquePos];
	
	//��ʼ��OPEN�б�
	queue<unsigned int> OPEN;
	OPEN.push(nStartCliqueID);
	//����CLOSED��
	set<unsigned int> CLOSED;

	///////////////////////////////////////////////////////////////////////////////////////////
	m_SEPSets;
	//����1��������ȹ����ѯ�漰����������ͬʱ���㵱ǰ����
	//���OPEN���Ƿ�Ϊ��
	while (OPEN.size() > 0)
	{
		//��ǰ��ID����
		unsigned int nID = OPEN.front();
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
			unsigned int nChildID = beg->second;

			//����̽ڵ��Ƿ���CLOSED������Ѿ����ڣ�����Ҫ���
			if (!qy::ranges::includes(CLOSED, nChildID))
			{
				//����ǰ���Ӻͺ���������ӻ�
				CClique product_clique = m_Cliques[GetCliquePosByID(nChildID)];
				theClique= theClique*product_clique;

				//���͸�����ӳ���ע�⣺Ҫ�ҵ�����У׼�ĸ
				unsigned int nSEPSetPos = GetSEPSetPos(nID, nChildID);
				CClique divide_clique = m_SEPSets[nSEPSetPos].clique;
				theClique = theClique/divide_clique;

				//��ӵ�OPEN��
				OPEN.push(nChildID);

				//����Ƿ��Ѿ��������б���
				//������������ID����
				set<unsigned int> AddVariableIDs;
				//��ȡ��������ID����
				GetIntersections(m_Cliques[GetCliquePosByID(nChildID)].GetCliqueVariableIDs(), QueryVariableIDs, AddVariableIDs);

				//��ӵ���ʼ����ID���ϡ�����ǰ����ID����
				StartVariableIDs.insert(AddVariableIDs.begin(), AddVariableIDs.end());				
				//������ID�����Ƿ��Ѿ��������в�ѯ����
				if (IsSetContainedIn(QueryVariableIDs,StartVariableIDs))
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
	line10: vector<unsigned int> CurrVariableIDs = theClique.GetCliqueVariableIDs();
	//������͵��ı�������
	vector<unsigned int> SumOutVariableIDs = GetSubstract(CurrVariableIDs, QueryVariableIDs);
	//��͵��������
	for (unsigned int i = 0; i < SumOutVariableIDs.size(); i++)
	{
		//��͵�����
		theClique.SumOutVariable(SumOutVariableIDs[i]);
	}


	/////////////////////////////////////////////////////////////////////
	//����3�����ݸ�����������
	for (unsigned int i = 0; i < query.GivenVariables.size(); i++)
	{
		//������
		theClique.ReduceGivenVariable(query.GivenVariables[i].nVariableID, query.GivenVariables[i].nValueID);
	}


	////////////////////////////////////////////////////////////////////
	//����4����һ����
	theClique.Normalize();


	////////////////////////////////////////////////////////////////////
	//����5����ȡ����
	double fProb;
	vector<unsigned int> VariableIDs;
	vector<unsigned int> ValueIDs;
	for (unsigned int i = 0; i < query.MarginalVariables.size(); i++)
	{
		//��ӵ�����ID��
		VariableIDs.push_back(query.MarginalVariables[i].nVariableID);

		//��ӵ�����ֵ��
		ValueIDs.push_back(query.MarginalVariables[i].nValueID);
	}

	//�����ӽ��в�ѯ
	fProb = theClique.Query(VariableIDs, ValueIDs);

	//��Ӹ��ʵ���ѯ���
	m_CTQueryResults.push_back(fProb);
}