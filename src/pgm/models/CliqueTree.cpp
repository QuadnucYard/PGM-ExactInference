#include "pgm/models/CliqueTree.hpp"
#include <queue>

namespace pgm {

	void CliqueTree::build(fid_t root) {
		std::queue<fid_t> open;
		fidset close;
		open.push(this->root = root);
		nodes[root].parent = -1;
		while (!open.empty()) {
			fid_t u = open.front();
			open.pop();
			close.insert(u);
			orderseq.push_back(u);
			auto er = edges.equal_range(u);
			for (auto&& p : std::ranges::subrange(er.first, er.second)) {
				fid_t v = p.second;
				if (!close.contains(v)) {
					nodes[v].parent = u;
					nodes[u].children.push_back(v);
					open.push(v);
				}
			}
		}
	}

}