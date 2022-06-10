////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_SumProductEliminateVar.cpp
// 和积消除变量
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"
#include <queue>

namespace pgm {

	// 拓扑排序求消除顺序
	fidlist CBNSumProduct::getEliminationOrder(const ProbQuery& query) const {
		fidlist order;
		fidset close;
		std::queue<fid_t> open;
		for (auto&& node : m_net.nodes) {
			if (node.parents.empty()) {
				open.push(node.id);
				close.insert(node.id);
			}
		}
		while (!open.empty()) {
			order.push_back(open.front());
			open.pop();
			for (auto&& node : m_net.nodes) {
				if (!close.contains(node.id) && std::ranges::all_of(node.parents, LAMBDA(t, close.contains(t)))) {
					open.push(node.id);
					close.insert(node.id);
				}
			}
		}
		return qy::except(qy::except(order, query.marginalVars, {}, &fidpair::first), query.givenVars, {}, &fidpair::first);
	}


	//和积消除变量
	void CBNSumProduct::eliminateVar(fid_t varId, FactorList& factors) const
	{
		// 这个函数本质是把包含var的因子乘起来合并成一个
		auto it=std::partition(factors.begin(), factors.end(), LAMBDA(t, !t.containsVar(varId)));
		if (it == factors.end()) return; //没有因子包含给定变量，直接返回
		*it = qy::ranges::product(it, factors.end()).sumOutVariable(varId); // 后面的因子求积
		factors.erase(++it, factors.end());
	}

}