#include "CommonIO.h"

namespace pgm::io {

	ProbQueryList readQuery(const fs::path& path) {
		ProbQueryList queries;

		YAML::Node doc = YAML::LoadFile(path.string());

		for (auto&& q : doc["queries"]) {
			queries.emplace_back(
				q["marginal"].as<fidmap>(fidmap {}) | qy::views::to<fidpairlist>,
				q["given"].as<fidmap>(fidmap {}) | qy::views::to<fidpairlist>
			);
		}
		return queries;
	}

	void outputQueryResult(const fs::path& path, const fvallist& queryResults) {
		YAML::Node root;
		for (fval_t qr : queryResults) {
			root["prob"].push_back(std::format("{:.6f}", qr));
		}
		std::ofstream fout(path);
		fout << root;
		fout.close();
	}

	std::string toQueryString(const ProbQueryList& queries) {
		return "";
	}

	std::string toResultString(const fvallist& queryResults) {
		std::string res;
		for (fval_t v : queryResults) {
			res += std::format("  - {0:.6f}\n", v);
		}
		return res;
	}

}