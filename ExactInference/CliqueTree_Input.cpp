#include "stdafx.h"
#include "CliqueTree.h"
#include "iohelper.h"

namespace pgm::io {

	CliqueTree readCliqueTree(const std::string& filename) {
		namespace fs = std::filesystem;
		CliqueTree ct;

#ifdef USE_YAML
		fs::path sPath = fs::current_path() / "Data" / (filename + ".yaml");
		YAML::Node doc = YAML::LoadFile(sPath.string());

		auto&& root = doc["CliqueTree"];
		for (auto&& node : root["variables"]) {
			ct.variables.emplace_back(
				node.first.as<fid_t>(),
				node.second["numValues"].as<size_t>(),
				node.second["name"].as<std::string>(""),
				node.second["abbr"].as<std::string>("")
			);
		}
		for (auto&& node : root["cliques"]) {
			ct.nodes.emplace_back(
				//node.first.as<fid_t>(),
				node.second["vars"].as<fidlist>(fidlist {}),
				node.second["vals"].as<fvallist>()
			);
		}
		for (auto&& node : root["edges"]) {
			ct.addEdge(node[0].as<fid_t>(), node[1].as<fid_t>());
		}
		ct.build(root["root"].as<fid_t>());

#endif // USE_YAML
		return ct;
	}

}