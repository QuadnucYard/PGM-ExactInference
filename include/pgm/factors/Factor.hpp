#pragma once
#include "factordef.h"
#include "stl_utils.h"
#include "qyalgo.hpp"
#include "qynumeric.hpp"
#include "qyranges.hpp"


namespace pgm {

	class Factor {
		// 有一个方案，存储所有因子，但标记是否有

	private:
		//Factor() = delete; // 禁用无参构造函数
		
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

		// 返回具有与给定变量匹配的行的因子
		Factor reduceGivenVariables(const fidpairlist& vars) const;

		Factor sumOutVariable(fid_t varId) const;

		Factor sumOutVariable(fidlist varIds) const;

		// 对具有给定变量的行求和
		fval_t query(const fidpairlist& vars) const;

		// 因子积
		Factor operator* (const Factor& o) const;

		// 因子除
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

		// 根据CPT索引获取变量的值
		inline fid_t getVarValueId(fid_t varIndex, fid_t i) const {
			return i / m_stride[varIndex] % m_vars[varIndex].second;
		}

		// 获取自身变量在另一组变量里的stride
		inline fidlist createRefStride(const fidpairlist& vars) const {
			return m_vars | std::views::transform(LAMBDA(p, getStride(vars, p.first))) | qy::views::to<fidlist>;
		}

		inline fid_t getRefIndex(const fidlist& s1, fid_t i) const {
			return getRefIndex(m_stride, s1, i);
		}

		// 获取原本在s中的i在s1中的索引
		fid_t getRefIndex(const fidlist& s, const fidlist& s1, fid_t i) const;

		fid_t getVarsOffset(const fidpairlist& vars) const;

		static fidlist createStride(const fidpairlist& vars);

		static fid_t getStride(const fidpairlist& vars, fid_t varId);

	private:
		fidpairlist m_vars;// 变量及其card
		fvalarr m_vals;// 按索引顺序的CPT值
		fidlist m_stride; // 步长
	};

	using FactorList = std::vector<Factor>;

}