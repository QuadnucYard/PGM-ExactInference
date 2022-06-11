#pragma once
#include "factordef.h"
#include "Variable.h"
#include "qyranges.hpp"
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
		std::vector<Node> nodes; // Ҫ���±�����0��ʼ����
		fid_t root;
		fidmultimap edges;
		fidlist orderseq; // ��������

		// ���������⡣������һ����������Ҫ���������

		/*void addNode(fid_t u) {
			nodes.insert({u, {u}});
		}*/

		inline void addEdge(fid_t u, fid_t v) {
			edges.emplace(u, v);
			edges.emplace(v, u);
		}

		void build(fid_t root);

		inline const Variable& getVar(fid_t id) const {
			return *std::ranges::find(variables, id, &Variable::id);
		}
	};

}