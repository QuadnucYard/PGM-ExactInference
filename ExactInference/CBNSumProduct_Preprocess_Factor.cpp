/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CBNSumProduct_Preprocess_Factor.cpp
//��  �ܣ�		Ԥ��������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��13��
//��  �£�		2021��03��23��
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CBNSumProduct.h"							//��Ҷ˹���羫ȷ������ͷ�ļ������úͻ�����������
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		Preprocess_Factor()
//��  �ܣ�		Ԥ��������
//��  ����		��
//����ֵ��		��
void CBNSumProduct::Preprocess_Factor()
{
	//����BN�е����нڵ�
	for (BN_NODE& node : m_Nodes)
	{
		CFactor factor;

		//////////////////////////////////////////////////////////////
		//����1����ʼ�����ӡ��������ӵı���ID���б�
		fidlist NodeIDs = node.ParentIDs;	//���ڵ�ID�б�
		//��ӱ���ڵ��ID
		NodeIDs.push_back(node.nID);
		//��ʼ������
		factor.SetFactorVariableIDs(NodeIDs);

		//////////////////////////////////////////////////////////////
		//����2����ʼ�����ӡ���������ֵ��ID��
		for (CPT_ROW& row : node.CPTRowIDs)
		{
			factor.SetFactorRow(row.ValueIDs, row.fProb);
		}

		//��ӵ����Ӽ���
		m_Factors.push_back(factor);
	}
}