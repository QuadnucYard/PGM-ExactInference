/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CBNSumProduct_Query_Helper.cpp
//��  �ܣ�		��ѯ�ĸ�������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��14��
//��  �£�		2021��03��24��
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CBNSumProduct.h"							//��Ҷ˹���羫ȷ������ͷ�ļ������úͻ�����������
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		Query_Helper()
//��  �ܣ�		��ѯ�ĸ�������
//��  ����		QUERY&,vector<CFactor>
//����ֵ��		��
void CBNSumProduct::Query_Helper(QUERY& query, vector<CFactor> Factors)
{
	//////////////////////////////////////////////////////////////////////////////
	//����1�����ݸ�����������Լ�����б�
	//�������и�������ID
	for (unsigned int i = 0; i < query.GivenVariables.size(); i++)
	{
		//������������
		for (unsigned int j = 0; j <Factors.size(); j++)
		{
			//��Լ����
			Factors[j].ReduceGivenVariable(query.GivenVariables[i].nNodeID, query.GivenVariables[i].nValueID);
		}
	}


	/////////////////////////////////////////////////////////////////////////////
	//����2�������Ե����
	Query_Marginal(query,Factors);
}