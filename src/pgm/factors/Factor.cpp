#include "pgm/factors/Factor.hpp"

namespace pgm {

	Factor::Factor(fidpairlist const& vars) : m_vars(vars) {
		std::ranges::sort(m_vars);
		createStrideSelf();
		m_vals.resize(rowSize());
	}

	Factor::Factor(fidpairlist const& vars, fvallist const& vals) : Factor(vars) {
		// 下面按照变量id进行重排，小因子排前面
		auto stride_old = createRefStride(vars);
		for (size_t i = 0; i < m_vals.size(); i++) {
			auto k = getRefIndex(stride_old, i);
			m_vals[i] = vals[k];
		}
	}

	Factor Factor::reduceGivenVariables(const fidpairlist& vars) const {
		// 一个问题，这个函数执行后，该变量id的取值就是其中一个了，不好用索引表示出来
		// 事实上调用者知道你保留了哪些，不重要
		Factor result(qy::except(m_vars, vars, &fidpair::first, &fidpair::first));
		fid_t offset = getVarsOffset(vars); // 被消除变量对应的偏移
		auto stride = result.createRefStride(m_vars);
		for (size_t i = 0; i < result.m_vals.size(); i++) {
			auto k = result.getRefIndex(stride, i) + offset;
			result.m_vals[i] = m_vals[k];
		}
		return result;
	}

	Factor Factor::sumOverVariable(fid_t varId) const {
		Factor result(qy::except(m_vars, varId, &fidpair::first));
		fid_t stride = getStride(varId), card = getVar(varId).second;
		for (size_t i = 0; i < result.m_vals.size(); i++) {
			result.m_vals[i] =
				m_vals[std::slice(i / stride * stride * card + i % stride, card, stride)].sum();
		}
		return result;
	}

	Factor Factor::sumOverVariable(fidlist varIds) const {
		Factor result(qy::except(m_vars, varIds, &fidpair::first));
		auto stride = createRefStride(result.m_vars);
		for (size_t i = 0; i < m_vals.size(); i++) {
			auto k = getRefIndex(stride, i);
			result.m_vals[k] += m_vals[i];
		}
		return result;
	}

	fval_t Factor::query(const fidpairlist& vars) const {
		// 只要把相关行挑出来求和就行了？？
		return reduceGivenVariables(vars).m_vals.sum();
	}

	Factor Factor::operator*(const Factor& o) const {
		Factor result(qy::set_union<fidpairlist>(m_vars, o.m_vars));
		auto s1 = result.createRefStride(m_vars);
		auto s2 = result.createRefStride(o.m_vars);
		result.m_vals.resize(result.rowSize());
		for (size_t i = 0; i < result.m_vals.size(); i++) {
			auto k1 = result.getRefIndex(s1, i), k2 = result.getRefIndex(s2, i);
			result.m_vals[i] = m_vals[k1] * o.m_vals[k2];
		}
		return result;
	}

	Factor Factor::operator/(const Factor& o) const {
		Factor result(m_vars);
		auto stride = result.createRefStride(o.m_vars);
		for (size_t i = 0; i < result.m_vals.size(); i++) {
			auto k = result.getRefIndex(stride, i);
			result.m_vals[i] = m_vals[i] == 0 && o.m_vals[k] == 0 ? 0 : m_vals[i] / o.m_vals[k];
		}
		return result;
	}

} // namespace pgm
