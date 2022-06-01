////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_SumProductEliminateVar.cpp
// �ͻ���������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


//�ͻ���������
void CBNSumProduct::Sum_Product_Eliminate_Var(fid_t nVariableID, CFactorList& OldFactors)
{
	CFactorList NewFactors;
	//����1�����������б���OldFactors���ֳ������������б���ɾ���͸�������ֵ��һ�µ���
	qy::split(OldFactors, std::back_inserter(NewFactors),
		[=](CFactor& t) { return qy::ranges::includes(t.GetFactorVariableIDs(), nVariableID); });

	if (NewFactors.size() == 0)
	{
		//û�����Ӱ�������������ֱ�ӷ���
		return;
	}
	else
	{
		//����2�����ӻ�
		CFactor psi = qy::ranges::product(NewFactors);
		
		//����3����͵���������
		psi.SumOutVariable(nVariableID);

		//����4�������ӻ���ӵ������б�
		OldFactors.push_back(std::move(psi));
	}
}

