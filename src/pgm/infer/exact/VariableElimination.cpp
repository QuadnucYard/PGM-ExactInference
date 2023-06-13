#include "pgm/infer/exact/VariableElimination.hpp"
#include <queue>

namespace pgm {

	VariableElimination::VariableElimination(const BayesianNetwork& bn) : m_net(bn) {
		// 把因子整出来
		for (auto&& node : bn.nodes) {
			// 生成(id,card)的列表（包括父结点和自身），并反转
			fidpairlist vars;
			for (fid_t id : node.parents) {
				vars.emplace_back(id, bn.getVar(id).numValues);
			}
			vars.emplace_back(node.id, bn.getVar(node.id).numValues);
			std::ranges::reverse(vars);
			m_Factors.emplace_back(vars, node.cpt);
		}
	}

	fvallist VariableElimination::query(const ProbQueryList& queries) const {
		return queries | std::views::transform(LAMBDA(q, query(q))) | std::ranges::to<fvallist>();
	}

	fval_t VariableElimination::query(const ProbQuery& query) const {
		//步骤1：根据给定变量、规约因子列表
		FactorList reducedFactors;
		for (auto&& factor : m_Factors) {
			reducedFactors.push_back(factor.reduceGivenVariables(query.given));
		}

		//步骤2：计算边缘概率
		//遍历所有删除变量，并进行边缘概率计算
		for (fid_t ev : getEliminationOrder(query)) {
			eliminateVar(ev, reducedFactors);
		}

		//步骤2：计算剩余的因子积
		//对最后得到的因子归一化，这个是必要的
		Factor phi = qy::ranges::product(reducedFactors).normalized();
		//对因子进行查询
		return phi.query(query.marginal);
	}

	fidlist VariableElimination::getEliminationOrder(const ProbQuery& query) const {
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
		return qy::except(qy::except(order, query.marginal, {}, &fidpair::first), query.given, {},
						  &fidpair::first);
	}

	void VariableElimination::eliminateVar(fid_t varId, FactorList& factors) const {
		// 这个函数本质是把包含var的因子乘起来合并成一个
		auto it = std::partition(factors.begin(), factors.end(), LAMBDA(t, !t.containsVar(varId)));
		if (it == factors.end()) return; //没有因子包含给定变量，直接返回
		*it = qy::ranges::product(it, factors.end()).sumOverVariable(varId); // 后面的因子求积
		factors.erase(++it, factors.end());
	}
}