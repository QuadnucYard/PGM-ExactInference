#pragma once
#include "factordef.h"
#include "stl_utils.h"
#include "qyalgo.hpp"
#include "qynumeric.hpp"
#include "qyranges.hpp"


namespace pgm {

	class Factor {
		// ��һ���������洢�������ӣ�������Ƿ���

	private:
		//Factor() = delete; // �����޲ι��캯��
		
	public:
		Factor() = default;
		Factor(const fidpairlist& vars);
		Factor(const fidpairlist& vars, const fvallist& vals);

		inline fidlist getVarIds() const {
			return std::views::transform(m_vars, LAMBDA(t, t.first)) | qy::views::to<fidlist>;
		}

		fid_t rowSize() const;

		bool containsVar(fid_t varId) const;

		Factor normalized() const;

		// ���ؾ������������ƥ����е�����
		Factor reduceGivenVariables(const fidpairlist& vars) const;

		Factor sumOutVariable(fid_t varId) const;

		Factor sumOutVariable(fidlist varIds) const;

		// �Ծ��и��������������
		fval_t query(const fidpairlist& vars) const;

		// ���ӻ�
		Factor operator* (const Factor& o) const;

		// ���ӳ�
		Factor operator/ (const Factor& o) const;

	private:

		inline fid_t getVarIndex(fid_t varId) const {
			return qy::ranges::index_of(m_vars, varId, &fidpair::first);
		}
		inline const fidpair& getVar(fid_t varId) const {
			return *std::ranges::find(m_vars, varId, &fidpair::first);
		}

		inline void createStrideSelf() {
			m_stride = createStride(m_vars);
		}

		inline fidlist createStride() const {
			return createStride(m_vars);
		}

		inline fid_t getStride(fid_t varId) const {
			return getStride(m_vars, varId);
		}

		// ����CPT������ȡ������ֵ
		inline fid_t getVarValueId(fid_t varIndex, fid_t i) const {
			return i / m_stride[varIndex] % m_vars[varIndex].second;
		}

		// ��ȡ�����������һ��������stride
		inline fidlist createRefStride(const fidpairlist& vars) const {
			return m_vars | std::views::transform(LAMBDA(p, getStride(vars, p.first))) | qy::views::to<fidlist>;
		}

		inline fid_t getRefIndex(const fidlist& s1, fid_t i) const {
			return getRefIndex(m_stride, s1, i);
		}

		// ��ȡԭ����s�е�i��s1�е�����
		fid_t getRefIndex(const fidlist& s, const fidlist& s1, fid_t i) const;

		fid_t getVarsOffset(const fidpairlist& vars) const;

		static fidlist createStride(const fidpairlist& vars);

		static fid_t getStride(const fidpairlist& vars, fid_t varId);

	private:
		fidpairlist m_vars;// ��������card
		fvalarr m_vals;// ������˳���CPTֵ
		fidlist m_stride; // ����
	};

	using FactorList = std::vector<Factor>;

}