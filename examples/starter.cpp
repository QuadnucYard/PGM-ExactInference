#include "pgm/infer/exact/VariableElimination.hpp"
#include "pgm/io/BayesianNetwork_Input.hpp"
#include "pgm/io/QueryInput.hpp"
#include <format>

template <typename... Args>
void print(const std::string_view fmt_str, Args&&... args) {
	auto fmt_args{std::make_format_args(args...)};
	std::string outstr{vformat(fmt_str, fmt_args)};
	fputs(outstr.c_str(), stdout);
}

int main(int argc, char const* argv[]) {
	auto bn = pgm::io::readBayesianNetwork("E:/Project/ExactInference/data/BayesianNetwork.yaml");
	auto ve = pgm::VariableElimination(bn);
	auto queries = pgm::io::readQuery("E:/Project/ExactInference/data/Query.yaml");
	auto result = ve.query(queries);
	// print("{}\n", result);
	for (auto v : result) {
		print("- {:.6}\n", v);
	}
	return 0;
}
