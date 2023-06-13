#include "iohelper.hpp"
#include "pgm/models/BayesianNetwork.hpp"

namespace pgm::io {

	inline BayesianNetwork readBayesianNetwork(const char* path) {
		auto tree = parse_yaml(path);
		auto const& root = tree["BayesianNetwork"];

		BayesianNetwork bn;

		for (auto&& n : root["variables"].children()) {
			Variable var;
			ryml::from_chars(n.key(), &var.id);
			n["numValues"] >> var.numValues;
			n["name"] >> var.name;
			n["abbr"] >> var.abbr;
			bn.addVar(std::move(var));
		}
		for (auto&& n : root["nodes"]) {
			BayesianNetwork::Node node;
			ryml::from_chars(n.key(), &node.id);
			if (n.has_child("parents"))
				n["parents"] >> node.parents;
			n["CPT"] >> node.cpt;
			bn.nodes.push_back(std::move(node));
		}
		return bn;
	}
} // namespace pgm::io