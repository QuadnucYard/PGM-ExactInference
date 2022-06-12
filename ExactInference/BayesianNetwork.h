#pragma once
#include "factordef.h"
#include "qyranges.hpp"

namespace pgm {

	class BayesianNetwork {

	public:
		struct Node {
			fid_t id;
			fidlist parents;	//父结点id
			fvallist cptvals;	//CPT表值
		};

		VariableList variables;		//变量集
		std::vector<Node> nodes;	//结点列表

	public:
		inline const Variable& getVar(fid_t id) const {
			return *std::ranges::find(variables, id, &Variable::id);
		}
	};

	namespace io {
		//读取贝叶斯网络结构和参数
		BayesianNetwork readBayesianNetwork(const std::string& filename);
	}
}