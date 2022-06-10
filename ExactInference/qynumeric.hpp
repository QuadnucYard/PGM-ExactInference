#pragma once
#include <ranges>
#include <algorithm>
#include <numeric>

namespace qy {

#define _SR ::std::ranges:: 

	namespace ranges {

		template <_SR input_range _Rng, class _Pj = std::identity>
		auto sum(_Rng&& _Range, _Pj _Proj = {}) {
			auto first = _SR begin(_Range);
			const auto last = _SR end(_Range);
			auto val = std::invoke(_Proj, *first++);
			for (; first != last; ++first) {
				val = _STD move(val) + std::invoke(_Proj, *first);
			}
			return val;
		}

		template <_SR input_range _Rng, class _Pj = std::identity>
		auto product(_Rng&& _Range, _Pj _Proj = {}) {
			auto first = _SR begin(_Range);
			const auto last = _SR end(_Range);
			auto val = std::invoke(_Proj, *first++);
			for (; first != last; ++first) {
				val = _STD move(val) * std::invoke(_Proj, *first);
			}
			return val;
			/*return std::accumulate(_SR begin(_Range) + 1, _SR end(_Range),
				std::invoke(_Proj, *_SR begin(_Range)),
				[=](auto x, auto& y) { return x * std::invoke(_Proj, y); });*/
		}

	}

#undef _SR
}
