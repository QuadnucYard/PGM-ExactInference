////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_Preprocess_Factor.cpp
// Ԥ��������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


//Ԥ��������
void CBNSumProduct::Preprocess_Factor()
{
	for (const BN_NODE& node : m_Nodes)
	{
		CFactor factor;

		//����1���������ӵı���ID���б�
		factor.SetFactorVariableIDs(qy::concat(node.ParentIDs, node.nID));

		//����2����������ֵ��ID��
		for (const CPT_ROW& row : node.CPTRowIDs)
		{
			factor.SetFactorRow(row.ValueIDs, row.fProb);
		}

		m_Factors.push_back(factor);
	}
}