#include "stdafx.h"
#include "CBNSumProduct.h"

namespace pgm {

	CBNSumProduct::CBNSumProduct(const BayesianNetwork& bn): m_net(bn) {
		// 把因子整出来
		for (auto&& node : bn.nodes) {
			fidpairlist vars;
			for (fid_t id : node.parents) {
				vars.emplace_back(id, bn.getVar(id).numValues);
			}
			vars.emplace_back(node.id, bn.getVar(node.id).numValues);
			std::ranges::reverse(vars);
			m_Factors.emplace_back(vars, node.cptvals);
		}
	}

}