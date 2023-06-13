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

		//从包含查询变量最多的一个团开始
		fid_t startCliqueId = qy::ranges::argmax(m_cliques, {}, [&](auto&& c) {
			return qy::set_intersection<fidlist>(c.getVarIds(), queryVars).size();
		});
		Factor theClique = m_cliques[startCliqueId];

		//广度优先构造查询涉及的子树、并同时计算当前因子
		std::queue<fid_t> open;
		open.push(startCliqueId);
		fidset close;
		bool finished = false;
		while (!open.empty() && !finished) {
			fid_t u = open.front();
			open.pop();
			close.insert(u);
			//查找当前团ID的后继
			auto er = m_tree.edges.equal_range(u);
			for (auto&& [_, v] : std::ranges::subrange(er.first, er.second)) {
				if (close.contains(v)) continue;
				//将当前因子和后继团做因子积，做和割集的因子除
				//注意，这里割集要找子结点对应的那个
				fid_t cutsetId = m_tree.nodes[v].parent == u ? v : u;
				theClique = theClique * m_cliques[v] / m_cutsets[cutsetId];
				open.push(v);
				//当该团已经覆盖所有查询变量时终止所有循环
				if (std::ranges::includes(theClique.getVarIds(), queryVars)) {
					finished = true;
					break;
				}
			}
		}
		//求和掉无关查询的多余变量
		theClique = theClique
			.sumOutVariable(qy::set_difference<fidlist>(theClique.getVarIds(), queryVars))
			.reduceGivenVariables(query.givenVars)
			.normalized();
		return theClique.query(query.marginalVars);
	}

	void CliqueTreeMethod::sendMessages() {
		// 先从下往上发消息，割集存在指向的点上
		for (fid_t u : std::views::reverse(m_tree.orderseq)) {
			// Receive
			for (fid_t v : m_tree.nodes[u].children) { //对所有子结点
				m_cliques[u] = m_cliques[u] * m_cutsets[v];
			}
			// Send Upward
			if (fid_t p = m_tree.nodes[u].parent; p != -1) { //对父结点
				auto elimilatedVars = qy::set_difference<fidlist>(m_cliques[u].getVarIds(), m_cliques[p].getVarIds());
				m_cutsets[u] = m_cliques[u].sumOutVariable(elimilatedVars);
			}
		}
		// 然后从上往下发消息
		for (fid_t u : m_tree.orderseq) {
			// Receive
			if (fid_t p = m_tree.nodes[u].parent; p != -1) { //对父结点
				m_cliques[u] = m_cliques[u] * m_cutsets[u];
			}
			// Send Downward
			for (fid_t v : m_tree.nodes[u].children) { //对所有子结点
				auto elimilatedVars = qy::set_difference<fidlist>(m_cliques[u].getVarIds(), m_cliques[v].getVarIds());
				m_cutsets[v] = m_cliques[u].sumOutVariable(elimilatedVars);
			}
		}
	}

}