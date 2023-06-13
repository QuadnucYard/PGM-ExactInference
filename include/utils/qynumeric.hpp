#pragma once
#include <ranges>
#include <algorithm>
#include <numeric>

namespace qy {

#define _SR ::std::ranges:: 

	namespace ranges {

		struct _sum_fn {
			template <class _InputIt, class _Pj = std::identity>
			constexpr auto operator()(_InputIt first, _InputIt last, _Pj _Proj = {}) const {
				auto val = std::invoke(_Proj, *first++);
				for (; first != last; ++first) {
					val = _STD move(val) + std::invoke(_Proj, *first);
				}
				return val;
			}

			template <_SR input_range _Rng, class _Pj = std::identity>
			constexpr auto operator()(_Rng&& _Range, _Pj _Proj = {}) const {
				return (*this)(_SR begin(_Range), _SR end(_Range), _Proj);
			}
		};

		inline constexpr _sum_fn sum;

		struct _product_fn {
			template <class _InputIt, class _Pj = std::identity>
			constexpr auto operator()(_InputIt first, _InputIt last, _Pj _Proj = {}) const {
				auto val = std::invoke(_Proj, *first++);
				for (; first != last; ++first) {
					val = _STD move(val) * std::invoke(_Proj, *first);
				}
				return val;
			}

			template <_SR input_range _Rng, class _Pj = std::identity>
			constexpr auto operator()(_Rng&& _Range, _Pj _Proj = {}) const {
				return (*this)(_SR begin(_Range), _SR end(_Range), _Proj);
			}
		};

		inline constexpr _product_fn product;
		

	}

#undef _SR
}
