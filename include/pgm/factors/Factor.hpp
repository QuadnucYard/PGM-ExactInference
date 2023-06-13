#pragma once
#include "factordef.hpp"
#include "utils/qyalgo.hpp"
#include "utils/qynumeric.hpp"
#include "utils/qyranges.hpp"
#include "utils/stl_utils.hpp"

namespace pgm {

	class Factor {
		// 有一个方案，存储所有因子，但标记是否有

	private:
		//Factor() = delete; // 禁用无参构造函数

	public:
		Factor() = default;

		Factor(fidpairlist const& vars);

		Factor(fidpairlist const& vars, fvallist const& vals);

		inline fidlist getVarIds() const {
			return std::views::transform(m_vars, LAMBDA(t, t.first)) | std::ranges::to<fidlist>();
		}

		inline fid_t rowSize() const {
			return m_vars.empty() ? 1 : qy::ranges::product(m_vars, &fidpair::second);
		}

		inline bool containsVar(fid_t varId) const {
			return std::ranges::contains(m_vars, varId, &fidpair::first);
		}

		inline void normalize() {
			m_vals /= m_vals.sum();
		}

		inline Factor normalized() const {
			Factor result{*this};
			result.normalize();
			return result;
		}

		// 返回具有与给定变量匹配的行的因子
		Factor reduceGivenVariables(const fidpairlist& vars) const;

		Factor sumOverVariable(fid_t varId) const;

		Factor sumOverVariable(fidlist varIds) const;

		// 对具有给定变量的行求和
		fval_t query(const fidpairlist& vars) const;

		// 因子积
		Factor operator*(const Factor& o) const;

		// 因子除
		Factor operator/(const Factor& o) const;

	private:
		/* inline fid_t getVarIndex(fid_t varId) const {
			return qy::ranges::index_of(m_vars, varId, &fidpair::first);
		} */

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
			return m_vars | std::views::transform(LAMBDA(p, getStride(vars, p.first))) |
				   std::ranges::to<fidlist>();
		}

		inline size_t getRefIndex(const fidlist& s1, size_t i) const {
			return getRefIndex(m_stride, s1, i);
		}

		// 获取原本在s中的i在s1中的索引
		inline size_t getRefIndex(const fidlist& s, const fidlist& s1, size_t i) const {
			fid_t k = 0;
			for (size_t j = 0; j < s.size(); j++)
				k += i / s[j] % m_vars[j].second * s1[j];
			return k;
		}

		inline fid_t getVarsOffset(const fidpairlist& vars) const {
			fid_t offset = 0;
			for (auto&& p : vars)
				offset += p.second * getStride(p.first);
			return offset;
		}

		static fidlist createStride(const fidpairlist& vars) {
			fidlist stride(vars.size());
			std::exclusive_scan(vars.begin(), vars.end(), stride.begin(), 1,
								[](auto&& x, auto&& y) { return x * y.second; });
			return stride;
		}

		static fid_t getStride(const fidpairlist& vars, fid_t varId) {
			fid_t result = 1;
			for (auto&& p : vars) {
				if (p.first == varId)
					return result;
				result *= p.second;
			}
			return 0; // 不存在的id的stride为0
		}

	private:
		fidpairlist m_vars; // 变量及其card
		fvalarr m_vals;		// 按索引顺序的CPT值
		fidlist m_stride;	// 步长
	};

	using FactorList = std::vector<Factor>;

} // namespace pgm