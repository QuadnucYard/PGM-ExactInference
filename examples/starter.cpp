#include "pgm/infer/exact/BeliefPropagation.hpp"
#include "pgm/infer/exact/VariableElimination.hpp"
#include "pgm/io/BayesianNetwork_Input.hpp"
#include "pgm/io/CliqueTree_Input.hpp"
#include "pgm/io/QueryInput.hpp"
#include <format>

template <typename... Args>
void print(const std::string_view fmt_str, Args&&... args) {
	auto fmt_args{std::make_format_args(args...)};
	std::string outstr{vformat(fmt_str, fmt_args)};
	fputs(outstr.c_str(), stdout);
}

int main(int argc, char const* argv[]) {
	auto queries = pgm::io::readQuery("E:/Project/ExactInference/data/Query.yaml");

	{
		auto bn = pgm::io::readBayesianNetwork(
			"E:/Project/ExactInference/data/BayesianNetwork.yaml");
		pgm::VariableElimination ve{bn};
		auto result = ve.query(queries);
		for (auto v : result)
			print("- {:.6f}\n", v);
	}
	print("----\n");
	{
		auto ct = pgm::io::readCliqueTree("E:/Project/ExactInference/data/CliqueTree.yaml");
		pgm::BeliefPropagation bp{ct};
		auto result = bp.query(queries);
		for (auto v : result)
			print("- {:.6f}\n", v);
	}

	return 0;
}
