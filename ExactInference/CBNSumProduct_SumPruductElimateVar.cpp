////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_SumProductEliminateVar.cpp
// �ͻ���������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"
#include <queue>

namespace pgm {

	// ��������������˳��
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


	//�ͻ���������
	void CBNSumProduct::eliminateVar(fid_t varId, FactorList& factors) const
	{
		// ������������ǰѰ���var�����ӳ������ϲ���һ��
		auto it=std::partition(factors.begin(), factors.end(), LAMBDA(t, !t.containsVar(varId)));
		if (it == factors.end()) return; //û�����Ӱ�������������ֱ�ӷ���
		*it = qy::ranges::product(it, factors.end()).sumOutVariable(varId); // ������������
		factors.erase(++it, factors.end());
	}

}