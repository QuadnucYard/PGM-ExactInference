#pragma once
#include "BayesianNetwork.h"
#include "Factor.h"

namespace pgm {

	class CBNSumProduct
	{
	public:
		CBNSumProduct(const BayesianNetwork& bn);
		fvallist query(const ProbQueryList&) const;
		fval_t query(const ProbQuery&) const;

	private:
		//��ȡ��������˳��
		fidlist getEliminationOrder(const ProbQuery& query) const;
		//�ͻ���������
		void eliminateVar(fid_t, FactorList&) const;

	private:
		BayesianNetwork m_net;
		FactorList m_Factors;	//�����б�

	};

}