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
#include "stl_utils.h"


//��  �ƣ�		Query_Marginal()
//��  �ܣ�		��ѯ��Ե���ʷֲ�
//��  ����		QUERY&,vectot<CFactor>&
//����ֵ��		��
void CBNSumProduct::Query_Marginal(const QUERY& query, CFactorList& Factors)
{
	//////////////////////////////////////////////////////////////////////////////
	//����1����������ɾ�������������б�Ե���ʼ��㡣������������Ե����l1=0.502
	for (fid_t ev : query.EliminateVariables)
	{
		//���ø�����������������
		Sum_Product_Eliminate_Var(ev, Factors);
	}

	//////////////////////////////////////////////////////////////////////////////
	//����2������ʣ������ӻ�
	CFactor phi = qy::product(Factors);

	/////////////////////////////////////////////////////////////////////////////
	//����3�������ӹ�һ����������Ϊ���յļ������������Ƿ���Ҫ�������й�һ�����������Ҫ�Ļ���Ҳ��Ӱ�������
	phi.Normalize();

	//////////////////////////////////////////////////////////////////////////////////
	//����4����ȡ����
	fidlist VariableIDs = query.QueryVariables | std::views::transform([](auto t) {return t.nNodeID; }) | qy::views::to<fidlist>;
	fidlist ValueIDs = query.QueryVariables | std::views::transform([](auto t) {return t.nValueID; }) | qy::views::to<fidlist>;

	//�����ӽ��в�ѯ����Ӹ��ʵ���ѯ���
	m_QueryResults.push_back(phi.Query(VariableIDs, ValueIDs));
}


