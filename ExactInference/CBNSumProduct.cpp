#include "CBNSumProduct.h"
#include <queue>

namespace pgm {

	CBNSumProduct::CBNSumProduct(const BayesianNetwork& bn): m_net(bn) {
		// ������������
		for (auto&& node : bn.nodes) {
			// ����(id,card)���б���������������������ת
			fidpairlist vars;
			for (fid_t id : node.parents) {
				vars.emplace_back(id, bn.getVar(id).numValues);
			}
			vars.emplace_back(node.id, bn.getVar(node.id).numValues);
			std::ranges::reverse(vars);
			m_Factors.emplace_back(vars, node.cptvals);
		}
	}

	fvallist CBNSumProduct::query(const ProbQueryList& queries) const {
		return queries | std::views::transform(LAMBDA(q, query(q))) | qy::views::to<fvallist>;
	}

	fval_t CBNSumProduct::query(const ProbQuery& query) const {
		//����1�����ݸ�����������Լ�����б�
		FactorList reducedFactors;
		for (auto&& factor : m_Factors) {
			reducedFactors.push_back(factor.reduceGivenVariables(query.givenVars));
		}

		//����2�������Ե����
		//��������ɾ�������������б�Ե���ʼ���
		for (fid_t ev : getEliminationOrder(query)) {
			eliminateVar(ev, reducedFactors);
		}

		//����2������ʣ������ӻ�
		//�����õ������ӹ�һ��������Ǳ�Ҫ��
		Factor phi = qy::ranges::product(reducedFactors).normalized();
		//�����ӽ��в�ѯ
		return phi.query(query.marginalVars);
	}


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

	void CBNSumProduct::eliminateVar(fid_t varId, FactorList& factors) const
	{
		// ������������ǰѰ���var�����ӳ������ϲ���һ��
		auto it = std::partition(factors.begin(), factors.end(), LAMBDA(t, !t.containsVar(varId)));
		if (it == factors.end()) return; //û�����Ӱ�������������ֱ�ӷ���
		*it = qy::ranges::product(it, factors.end()).sumOutVariable(varId); // ������������
		factors.erase(++it, factors.end());
	}

}