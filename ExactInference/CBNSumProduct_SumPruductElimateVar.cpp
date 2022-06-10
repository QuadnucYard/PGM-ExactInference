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
	void CBNSumProduct::eliminateVar(fid_t varId, FactorList& oldFactors) const
	{
		// 这个函数本质是把包含var的因子乘起来合并成一个
		FactorList newFactors;
		//构建因子列表，把包含给定变量的因子从OldFactors划分出，并从因子列表中删除和给定变量值不一致的行
		qy::split(oldFactors, std::back_inserter(newFactors),
			[=](auto&& t) { return t.containsVar(varId); });

		if (newFactors.empty()) {
			return; //没有因子包含给定变量，直接返回
		} else {
			Factor psi = qy::ranges::product(newFactors); //因子积
			psi.sumOutVariable(varId); //求和掉给定变量
			oldFactors.push_back(std::move(psi)); //将因子积添加到因子列表
		}
	}

}