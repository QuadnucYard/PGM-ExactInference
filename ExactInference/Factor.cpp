#include "stdafx.h"
#include "Factor.h"

namespace pgm {

	Factor::Factor(const fidpairlist& vars): m_vars(vars) {
		std::ranges::sort(m_vars);
		createStrideSelf();
		m_vals.resize(rowSize());
	}

	Factor::Factor(const fidpairlist& vars, const fvallist& vals): Factor(vars) {
		// ���水�ձ���id�������ţ�С������ǰ��
		auto stride_old = createRefStride(vars);
		for (size_t i = 0; i < m_vals.size(); i++) {
			auto k = getRefIndex(stride_old, i);
			m_vals[i] = vals[k];
		}
	}

	fid_t Factor::rowSize() const {
		if (m_vars.empty()) return 1;
		return qy::ranges::product(m_vars, &fidpair::second);
	}

	bool Factor::containsVar(fid_t varId) const {
		return std::ranges::find(m_vars, varId, &fidpair::first) != m_vars.end();
	}

	Factor Factor::normalized() const {
		Factor result {*this};
		result.m_vals /= m_vals.sum();
		return result;
	}

	Factor Factor::reduceGivenVariables(const fidpairlist& vars) const {
		// һ�����⣬�������ִ�к󣬸ñ���id��ȡֵ��������һ���ˣ�������������ʾ����
		// ��ʵ�ϵ�����֪���㱣������Щ������Ҫ
		Factor result(qy::except(m_vars, vars, &fidpair::first, &fidpair::first));
		fid_t offset = getVarsOffset(vars); // ������������Ӧ��ƫ��
		auto stride = result.createRefStride(m_vars);
		for (size_t i = 0; i < result.m_vals.size(); i++) {
			auto k = result.getRefIndex(stride, i) + offset;
			result.m_vals[i] = m_vals[k];
		}
		return result;
	}

	Factor Factor::sumOutVariable(fid_t varId) const {
		Factor result(qy::except(m_vars, varId, &fidpair::first));
		fid_t stride = getStride(varId), card = getVar(varId).second;
		for (size_t i = 0; i < result.m_vals.size(); i++) {
			result.m_vals[i] = m_vals[std::slice(i / stride * stride * card + i % stride, card, stride)].sum();
		}
		return result;
	}

	Factor Factor::sumOutVariable(fidlist varIds) const {
		Factor result(qy::except(m_vars, varIds, &fidpair::first));
		auto stride = createRefStride(result.m_vars);
		for (size_t i = 0; i < m_vals.size(); i++) {
			auto k = getRefIndex(stride, i);
			result.m_vals[k] += m_vals[i];
		}
		return result;
	}

	fval_t Factor::query(const fidpairlist& vars) const {
		// ֻҪ���������������;����ˣ���
		return reduceGivenVariables(vars).m_vals.sum();
	}

	Factor Factor::operator* (const Factor& o) const {
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

	Factor Factor::operator/ (const Factor& o) const {
		Factor result(m_vars);
		auto stride = result.createRefStride(o.m_vars);
		for (size_t i = 0; i < result.m_vals.size(); i++) {
			auto k = result.getRefIndex(stride, i);
			result.m_vals[i] = m_vals[i] == 0 && o.m_vals[k] == 0 ? 0 : m_vals[i] / o.m_vals[k];
		}
		return result;
	}

	fid_t Factor::getRefIndex(const fidlist& s, const fidlist& s1, fid_t i) const {
		fid_t k = 0;
		for (size_t j = 0; j < s.size(); j++) {
			k += i / s[j] % m_vars[j].second * s1[j];
		}
		return k;
	}

	fid_t Factor::getVarsOffset(const fidpairlist& vars) const {
		fid_t offset = 0;
		for (auto&& p : vars) {
			offset += p.second * getStride(p.first);
		}
		return offset;
	}

	fidlist Factor::createStride(const fidpairlist& vars) {
		fidlist stride(vars.size());
		std::exclusive_scan(vars.begin(), vars.end(), stride.begin(), 1,
			[](auto&& x, auto&& y) {return x * y.second; });
		return stride;
	}

	fid_t Factor::getStride(const fidpairlist& vars, fid_t varId) {
		fid_t result = 1;
		for (auto&& p : vars) {
			if (p.first == varId) return result;
			result *= p.second;
		}
		return 0; // �����ڵ�id��strideΪ0
	}

}

