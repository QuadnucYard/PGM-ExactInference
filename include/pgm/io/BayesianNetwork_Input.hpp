#include "iohelper.hpp"
#include "pgm/models/BayesianNetwork.hpp"

namespace pgm::io {

	inline BayesianNetwork readBayesianNetwork(const char* path) {
		std::string contents = file_get_contents<std::string>(path);
		auto tree = ryml::parse_in_arena(ryml::to_csubstr(contents));
		auto const& root = tree["BayesianNetwork"];

		BayesianNetwork bn;

		for (auto&& n : root["variables"].children()) {
			Variable var;
			ryml::from_chars(n.key(), &var.id);
			n["numValues"] >> var.numValues;
			n["name"] >> var.name;
			n["abbr"] >> var.abbr;
			bn.addVar(var);
		}
		for (auto&& n : root["nodes"]) {
			BayesianNetwork::Node node;
			ryml::from_chars(n.key(), &node.id);
			if (n.has_child("parents"))
				n["parents"] >> node.parents;
			n["CPT"] >> node.cpt;
			bn.nodes.push_back(node);
		}
		return bn;
	}
} // namespace pgm::io