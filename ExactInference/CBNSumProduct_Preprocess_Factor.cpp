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
	for (unsigned int i = 0; i < m_Nodes.size(); i++)
	{
		//��������
		CFactor factor;

		//////////////////////////////////////////////////////////////
		//����1����ʼ�����ӡ��������ӵı���ID���б�
		vector<unsigned int>NodeIDs= m_Nodes[i].ParentIDs;	//���ڵ�ID�б�
		//��ӱ���ڵ��ID
		NodeIDs.push_back(m_Nodes[i].nID);
		//��ʼ������
		factor.SetFactorVariableIDs(NodeIDs);


		//////////////////////////////////////////////////////////////
		//����2����ʼ�����ӡ���������ֵ��ID��
		for (unsigned int j = 0; j < m_Nodes[i].CPTRowIDs.size(); j++)
		{
			//��ȡֵID�ı�
			vector<unsigned int> ValueIDs=m_Nodes[i].CPTRowIDs[j].ValueIDs;
			//��ȡ����ֵ
			double fValue = m_Nodes[i].CPTRowIDs[j].fProb;

			//�������ӵ���
			factor.SetFactorRow(ValueIDs, fValue);
		}
		
		//��ӵ����Ӽ���
		m_Factors.push_back(factor);
	}


	//////////////////////////////////////////////////////////////////////////////
	//����ע�͵�����Ҫ���ڲ����������㡣�������ӻ������ӻ���������͵����ֱ�����	
	//���ӻ�
	//CFactor new_factor = m_Factors[0] * m_Factors[2];

	//���ӻ���
	//new_factor.ReduceGivenVariable(0, 0);

	//���Ӻ�
	//new_factor.SumVariable(0);
	///////////////////////////////////////////////////////////////////////////////
}