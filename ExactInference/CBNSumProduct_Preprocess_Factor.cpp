/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CBNSumProduct_Preprocess_Factor.cpp
//��  �ܣ�		Ԥ��������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��13��
//��  �£�		2021��03��23��
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


//Ԥ��������
void CBNSumProduct::Preprocess_Factor()
{
	for (BN_NODE& node : m_Nodes)
	{
		CFactor factor;

		//����1����ʼ�����ӡ��������ӵı���ID���б�
		fidlist NodeIDs = node.ParentIDs;
		//��ӱ���ڵ��ID
		NodeIDs.push_back(node.nID);
		//��ʼ������
		factor.SetFactorVariableIDs(NodeIDs);

		//����2����ʼ�����ӡ���������ֵ��ID��
		for (CPT_ROW& row : node.CPTRowIDs)
		{
			factor.SetFactorRow(row.ValueIDs, row.fProb);
		}

		m_Factors.push_back(factor);
	}
}