/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CBNSumProduct_SumProductEliminateVar.cpp
//��  �ܣ�		�ͻ���������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��14��
//��  �£�		2021��03��24��
//��  �ȣ�		80��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


//�ͻ���������
void CBNSumProduct::Sum_Product_Eliminate_Var(fid_t nVariableID, CFactorList& OldFactors)
{
	CFactorList NewFactors;
	//����1�����������б���OldFactors���ֳ������������б���ɾ���͸�������ֵ��һ�µ���
	qy::split(OldFactors, std::back_inserter(NewFactors),
		[=](CFactor& t) { return qy::includes(t.GetFactorVariableIDs(), nVariableID); });

	if (NewFactors.size() == 0)
	{
		//û�����Ӱ�������������ֱ�ӷ���
		return;
	}
	else
	{
		//����2�����ӻ�
		CFactor psai = qy::product(NewFactors);
		
		//����3����͵���������
		psai.SumOutVariable(nVariableID);

		//����4�������ӻ���ӵ������б�
		OldFactors.push_back(std::move(psai));
	}
}

