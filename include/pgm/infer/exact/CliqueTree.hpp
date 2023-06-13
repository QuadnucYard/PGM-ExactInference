#pragma once
#include "pgm/factors/factordef.hpp"
#include "pgm/io/iohelper.hpp"
#include "utils/qyranges.hpp"
#include <queue>

namespace pgm {

	struct CliqueTree {
		struct Node {
			//fid_t id;
			fidlist varids;
			fvallist cptvals;
			fid_t parent;
			fidlist children;
		};

		VariableList variables;
		std::vector<Node> nodes; // 要求下标必须从0开始连续
		fid_t root;
		fidmultimap edges;
		fidlist orderseq; // 建树序列

		// 建树的问题。读入是一个无向树，要搞成有向树

		inline void addEdge(fid_t u, fid_t v) {
			edges.emplace(u, v);
			edges.emplace(v, u);
		}

		void build(fid_t root);

		inline const Variable& getVar(fid_t id) const {
			return *std::ranges::find(variables, id, &Variable::id);
		}
	};

} // namespace pgm