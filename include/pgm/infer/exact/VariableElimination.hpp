#pragma once
#include "pgm/factors/Factor.hpp"
#include "pgm/models/BayesianNetwork.hpp"

namespace pgm {

	class VariableElimination {
	public:
		VariableElimination(const BayesianNetwork& bn);
		fvallist query(const ProbQueryList&) const;
		fval_t query(const ProbQuery&) const;

	private:
		//获取变量消除顺序
		fidlist getEliminationOrder(const ProbQuery& query) const;
		//和积变量消除
		void eliminateVar(fid_t, FactorList&) const;

	private:
		const BayesianNetwork& m_net;
		FactorList m_Factors; //因子列表
	};

} // namespace pgm