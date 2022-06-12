#include "stdafx.h"
#include "CommonIO.h"

namespace pgm::io {

	ProbQueryList readQuery(const std::string& filename) {
		namespace fs = std::filesystem;
		ProbQueryList queries;
#ifdef USE_YAML
		fs::path path = fs::current_path() / "Data" / (filename + ".yaml");
		YAML::Node doc = YAML::LoadFile(path.string());

		for (auto&& q : doc["queries"]) {
			queries.emplace_back(
				q["marginal"].as<fidmap>(fidmap {}) | qy::views::to<fidpairlist>,
				q["given"].as<fidmap>(fidmap {}) | qy::views::to<fidpairlist>
			);
		}
#endif // USE_YAML
		return queries;
	}

	std::filesystem::path outputQueryResult(const std::string& filename, const fvallist& queryResults) {
		namespace fs = std::filesystem;
#ifdef USE_YAML
		YAML::Node root;
		for (fval_t qr : queryResults) {
			root["prob"].push_back(std::format("{:.6f}", qr));
		}
		fs::path path = fs::current_path() / "Data" / (filename + ".yaml");
		std::ofstream fout(path);
		fout << root;
		fout.close();
		return path;
#endif // !USE_YAML
	}

}