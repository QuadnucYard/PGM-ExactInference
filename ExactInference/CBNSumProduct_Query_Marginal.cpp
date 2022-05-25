/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CBNSumProduct_Query_Marginal.cpp
//��  �ܣ�		��ѯ��Ե���ʷֲ�
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��14��
//��  �£�		2021��03��24��
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CBNSumProduct.h"							//��Ҷ˹���羫ȷ������ͷ�ļ������úͻ�����������
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		Query_Marginal()
//��  �ܣ�		��ѯ��Ե���ʷֲ�
//��  ����		QUERY&,vectot<CFactor>&
//����ֵ��		��
void CBNSumProduct::Query_Marginal(QUERY& query,vector<CFactor>& Factors)
{
	//////////////////////////////////////////////////////////////////////////////
	//����1����������ɾ�������������б�Ե���ʼ��㡣������������Ե����l1=0.502
	for (unsigned int i = 0; i < query.EliminateVariables.size(); i++)
	{
		//���ø�����������������
		Sum_Product_Eliminate_Var(query.EliminateVariables[i],Factors);
	}


	//////////////////////////////////////////////////////////////////////////////
	//����2������ʣ������ӻ�
	//�����µ�����phi������ʼ��Ϊ��0������
	CFactor phi = Factors[0];
	//�������ӻ�
	for (unsigned int i = 1; i < Factors.size(); i++)
	{
		//�������ӻ�
		phi = phi*Factors[i];
	}


	/////////////////////////////////////////////////////////////////////////////
	//����3�������ӹ�һ����������Ϊ���յļ������������Ƿ���Ҫ�������й�һ�����������Ҫ�Ļ���Ҳ��Ӱ�������
	phi.Normalize();


	//////////////////////////////////////////////////////////////////////////////////
	//����4����ȡ����
	double fProb;
	vector<unsigned int> VariableIDs;
	vector<unsigned int> ValueIDs;
	for (unsigned int i = 0; i < query.QueryVariables.size(); i++)
	{
		//��ӵ�����ID��
		VariableIDs.push_back(query.QueryVariables[i].nNodeID);
		
		//��ӵ�����ֵ��
		ValueIDs.push_back(query.QueryVariables[i].nValueID);
	}
	
	//�����ӽ��в�ѯ
	fProb = phi.Query(VariableIDs,ValueIDs);
	
	//��Ӹ��ʵ���ѯ���
	m_QueryResults.push_back(fProb);
}


