#pragma once
#include <ranges>
#include <algorithm>
#include <numeric>

namespace qy {

#define _SR ::std::ranges:: 

	namespace ranges {

		template <_SR random_access_range _Rng, class _OutIt, class _Pr = _SR less, class _Pj = std::identity>
		void argsort(_Rng&& _Range, _OutIt _Dest, _Pr _Pred = {}, _Pj _Proj = {}) {
			std::iota(_Dest, _Dest + _SR size(_Range), 0);
			std::ranges::sort(_Dest, _Dest + _SR size(_Range),
				[=](auto i1, auto i2) { return std::invoke(_Pred, std::invoke(_Proj, _Range[i1]), _STD invoke(_Proj, _Range[i2])); });
		}

		template <_SR forward_range _Rng, class _Pj = std::identity, class _Pr = _SR less>
		size_t argmax(_Rng&& _Range, _Pr _Pred = {}, _Pj _Proj = {}) {
			return _SR max_element(std::forward<_Rng>(_Range), _Pred, _Proj) - _SR begin(_Range);
		}


	}

#undef _SR
}
