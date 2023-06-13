/* #include "BayesianNetwork.h"

namespace pgm::io {

	BayesianNetwork readBayesianNetwork(const fs::path& path) {
		BayesianNetwork bn;

		YAML::Node doc = YAML::LoadFile(path.string());

		auto&& root = doc["BayesianNetwork"];
		for (auto&& node : root["variables"]) {
			BayesianNetwork::Node bn_node;
			bn.variables.emplace_back(
				node.first.as<fid_t>(),
				node.second["numValues"].as<size_t>(),
				node.second["name"].as<std::string>(""),
				node.second["abbr"].as<std::string>("")
			);
		}
		for (auto&& node : root["nodes"]) {
			bn.nodes.emplace_back(
				node.first.as<fid_t>(),
				node.second["parants"].as<fidlist>(fidlist {}),
				node.second["CPT"].as<fvallist>()
			);
		}

		return bn;
	}

} */