#include "iohelper.hpp"
#include "pgm/factors/factordef.hpp"
#include <ranges>

namespace pgm::io {
	inline ProbQueryList readQuery(const char* path) {
		auto tree = parse_yaml(path);

		ProbQueryList queries;

		for (auto&& n : tree["queries"]) {
			ProbQuery query;
			fidpair p;
			for (auto&& n2 : n["marginal"]) {
				n2 >> ryml::key(p.first) >> p.second;
				query.marginal.push_back(p);
			}
			if (n.has_child("given"))
				for (auto&& n2 : n["given"]) {
					n2 >> ryml::key(p.first) >> p.second;
					query.given.push_back(p);
				}
			queries.push_back(std::move(query));
		}
		return queries;
	}
} // namespace pgm::io
