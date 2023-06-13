#pragma once
#include "pgm/factors/Factor.hpp"
#include "pgm/models/CliqueTree.hpp"

namespace pgm {

	class BeliefPropagation {
	public:
		BeliefPropagation(const CliqueTree& ct);

		fvallist query(const ProbQueryList& queries) const;

		fval_t query(const ProbQuery& query) const;

	private:
		void sendMessages();

	private:
		const CliqueTree& m_tree;
		std::vector<Factor> m_cliques;
		fidmultimap m_var2clique;
		std::vector<Factor> m_cutsets;
	};

} // namespace pgm