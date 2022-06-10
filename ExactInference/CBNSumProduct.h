////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct.h
// 定义贝叶斯网络的精确推理类。采用和积变量消除法
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "BayesianNetwork.h"
#include "Factor.h"

namespace pgm {

	//定义贝叶斯网络的精确推理类CBNSumProduct。采用和积变量消除法
	class CBNSumProduct
	{
	public:
		CBNSumProduct(const BayesianNetwork& bn);
		fvallist query(const ProbQueryList&) const;
		fval_t query(const ProbQuery&) const;

	private:
		//获取变量消除顺序
		fidlist getEliminationOrder(const ProbQuery& query) const;
		//和积变量消除
		void eliminateVar(fid_t, FactorList&) const;

	private:
		BayesianNetwork m_net;
		FactorList m_Factors;	//因子列表

	};

}