#pragma once
#include <ranges>

namespace qy {

#define _SR ::std::ranges:: 

	namespace ranges {

#include "qyrange.hpp"
#include "qyviews.hpp"

	}



	namespace views = ranges::views;

	inline constexpr auto range(size_t n) { 
		return std::ranges::iota_view(0, (int)n);
	}

	template <_SR range _Rng>
	inline constexpr auto range(_Rng&& _Range) {
		return range(_SR size(_Range));
	}

#undef _SR
}