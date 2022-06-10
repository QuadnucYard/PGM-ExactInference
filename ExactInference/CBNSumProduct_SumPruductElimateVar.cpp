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
	void CBNSumProduct::eliminateVar(fid_t varId, FactorList& oldFactors) const
	{
		// ������������ǰѰ���var�����ӳ������ϲ���һ��
		FactorList newFactors;
		//���������б��Ѱ����������������Ӵ�OldFactors���ֳ������������б���ɾ���͸�������ֵ��һ�µ���
		qy::split(oldFactors, std::back_inserter(newFactors),
			[=](auto&& t) { return t.containsVar(varId); });

		if (newFactors.empty()) {
			return; //û�����Ӱ�������������ֱ�ӷ���
		} else {
			Factor psi = qy::ranges::product(newFactors); //���ӻ�
			psi.sumOutVariable(varId); //��͵���������
			oldFactors.push_back(std::move(psi)); //�����ӻ���ӵ������б�
		}
	}

}