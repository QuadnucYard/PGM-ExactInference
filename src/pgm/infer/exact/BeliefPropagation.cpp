#include "CliqueTreeMethod.h"

namespace pgm {

	CliqueTreeMethod::CliqueTreeMethod(const CliqueTree& ct): m_tree(ct) {
		for (auto&& node : ct.nodes) {
			fidpairlist vars;
			for (fid_t id : node.varids) {
				vars.emplace_back(id, ct.getVar(id).numValues);
			}
			std::ranges::reverse(vars);
			m_cliques.emplace_back(std::move(vars), node.cptvals);
		}
		m_cutsets.resize(m_cliques.size());
		sendMessages();
	}

	fvallist CliqueTreeMethod::query(const ProbQueryList& queries) const {
		return queries | std::views::transform(LAMBDA(q, query(q))) | qy::views::to<fvallist>;
	}

	fval_t CliqueTreeMethod::query(const ProbQuery& query) const {
		fidlist queryVars;
		std::ranges::transform(query.marginalVars, std::back_inserter(queryVars), &fidpair::first);
		std::ranges::transform(query.givenVars, std::back_inserter(queryVars), &fidpair::first);
		std::ranges::sort(queryVars);

		//�Ӱ�����ѯ��������һ���ſ�ʼ
		fid_t startCliqueId = qy::ranges::argmax(m_cliques, {}, [&](auto&& c) {
			return qy::set_intersection<fidlist>(c.getVarIds(), queryVars).size();
		});
		Factor theClique = m_cliques[startCliqueId];

		//������ȹ����ѯ�漰����������ͬʱ���㵱ǰ����
		std::queue<fid_t> open;
		open.push(startCliqueId);
		fidset close;
		bool finished = false;
		while (!open.empty() && !finished) {
			fid_t u = open.front();
			open.pop();
			close.insert(u);
			//���ҵ�ǰ��ID�ĺ��
			auto er = m_tree.edges.equal_range(u);
			for (auto&& [_, v] : std::ranges::subrange(er.first, er.second)) {
				if (close.contains(v)) continue;
				//����ǰ���Ӻͺ���������ӻ������͸�����ӳ�
				//ע�⣬����Ҫ���ӽ���Ӧ���Ǹ�
				fid_t cutsetId = m_tree.nodes[v].parent == u ? v : u;
				theClique = theClique * m_cliques[v] / m_cutsets[cutsetId];
				open.push(v);
				//�������Ѿ��������в�ѯ����ʱ��ֹ����ѭ��
				if (std::ranges::includes(theClique.getVarIds(), queryVars)) {
					finished = true;
					break;
				}
			}
		}
		//��͵��޹ز�ѯ�Ķ������
		theClique = theClique
			.sumOutVariable(qy::set_difference<fidlist>(theClique.getVarIds(), queryVars))
			.reduceGivenVariables(query.givenVars)
			.normalized();
		return theClique.query(query.marginalVars);
	}

	void CliqueTreeMethod::sendMessages() {
		// �ȴ������Ϸ���Ϣ�������ָ��ĵ���
		for (fid_t u : std::views::reverse(m_tree.orderseq)) {
			// Receive
			for (fid_t v : m_tree.nodes[u].children) { //�������ӽ��
				m_cliques[u] = m_cliques[u] * m_cutsets[v];
			}
			// Send Upward
			if (fid_t p = m_tree.nodes[u].parent; p != -1) { //�Ը����
				auto elimilatedVars = qy::set_difference<fidlist>(m_cliques[u].getVarIds(), m_cliques[p].getVarIds());
				m_cutsets[u] = m_cliques[u].sumOutVariable(elimilatedVars);
			}
		}
		// Ȼ��������·���Ϣ
		for (fid_t u : m_tree.orderseq) {
			// Receive
			if (fid_t p = m_tree.nodes[u].parent; p != -1) { //�Ը����
				m_cliques[u] = m_cliques[u] * m_cutsets[u];
			}
			// Send Downward
			for (fid_t v : m_tree.nodes[u].children) { //�������ӽ��
				auto elimilatedVars = qy::set_difference<fidlist>(m_cliques[u].getVarIds(), m_cliques[v].getVarIds());
				m_cutsets[v] = m_cliques[u].sumOutVariable(elimilatedVars);
			}
		}
	}

}