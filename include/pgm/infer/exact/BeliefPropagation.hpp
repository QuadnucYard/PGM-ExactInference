#pragma once
#include "CliqueTree.h"
#include "Factor.h"

namespace pgm {

	class CliqueTreeMethod {

	public:
		CliqueTreeMethod(const CliqueTree& ct);

		fvallist query(const ProbQueryList& queries) const;

		fval_t query(const ProbQuery& query) const;

	private:
		void sendMessages();

	private:
		CliqueTree m_tree;
		std::vector<Factor> m_cliques;
		fidmultimap m_var2clique;
		std::vector<Factor> m_cutsets;

	};

}