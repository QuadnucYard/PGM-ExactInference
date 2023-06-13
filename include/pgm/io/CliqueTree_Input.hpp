
#include "iohelper.hpp"
#include "pgm/models/CliqueTree.hpp"

namespace pgm::io {

	inline CliqueTree readCliqueTree(const char* path) {
		auto tree = parse_yaml(path);
		auto const& root = tree["CliqueTree"];

		CliqueTree ct;
		root["root"] >> ct.root;
		for (auto&& n : root["variables"]) {
			Variable var;
			ryml::from_chars(n.key(), &var.id);
			n["numValues"] >> var.numValues;
			n["name"] >> var.name;
			n["abbr"] >> var.abbr;
			ct.variables.push_back(std::move(var));
		}
		for (auto&& n : root["cliques"]) {
			CliqueTree::Node node;
			n["vars"] >> node.varids;
			n["vals"] >> node.cptvals;
			ct.nodes.push_back(std::move(node));
		}
		for (auto&& n : root["edges"]) {
			fid_t u, v;
			n[0] >> u;
			n[1] >> v;
			ct.addEdge(u, v);
		}
		ct.build(ct.root);
		return ct;
	}
} // namespace pgm::io