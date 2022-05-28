#pragma once
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <iterator>
#include <ranges>
#include "qyranges.hpp"

namespace qy {

	template <class InputIt>
	inline typename std::iterator_traits<InputIt>::value_type
		sum(InputIt first, InputIt last) {
		return std::accumulate(first, last,
			(typename std::iterator_traits<InputIt>::value_type)0,
			std::plus<typename std::iterator_traits<InputIt>::value_type>());
	}

	template <class InputIt, class Selector>
	inline typename std::invoke_result_t<Selector, typename std::iterator_traits<InputIt>::value_type>
		sum(InputIt first, InputIt last, Selector selector) {
		/*typename std::invoke_result_t<Selector, typename iterator_traits<InputIt>::value_type> init = 0;
		for (; first != last; ++first)
			init = init + selector(*first);
		return init;*/
		return std::accumulate(first, last,
			(std::invoke_result_t<Selector, typename std::iterator_traits<InputIt>::value_type>)0,
			[=](auto x, auto& y) { return x + selector(y); });
	}

	template <class InputIt>
	inline typename std::iterator_traits<InputIt>::value_type
		product(InputIt first, InputIt last) {
		return std::accumulate(first + 1, last,
			*first,
			std::multiplies<typename std::iterator_traits<InputIt>::value_type>());
	}

	template <std::ranges::range R>
	inline typename std::ranges::range_value_t<R>
		product(R&& r) {
		return std::accumulate(std::ranges::begin(r) + 1, std::ranges::end(r),
			*std::ranges::begin(r),
			std::multiplies<typename std::ranges::range_value_t<R>>());
	}

	template <class C, class Value>
	inline bool includes(const C& c, Value x) {
		return std::find(std::begin(c), std::end(c), x) != std::end(c);
	}

	template <class C, class Value>
	inline size_t index_of(const C& c, Value x) {
		auto it = std::find(std::begin(c), std::end(c), x);
		return it == std::end(c) ? -1 : it - std::begin(c);
	}

	template <class C, class Pred>
	inline size_t index_of_if(const C& c, Pred pred) {
		auto it = std::find_if(std::begin(c), std::end(c), pred);
		return it == std::end(c) ? -1 : it - std::begin(c);
	}

	template <class C, class Pred>
	inline void remove_if(C& c, Pred pred) {
		c.erase(std::remove_if(std::begin(c), std::end(c), pred), std::end(c));
	}

	template <class C, class OutIt, class Pred>
	inline void split(C& c, OutIt out_true, Pred pred) {
		c.erase(std::partition_copy(std::begin(c), std::end(c), out_true, std::begin(c), pred).second, std::end(c));
	}

	template <class Key, class Value, class OutContainer>
	inline void map_keys(const std::map<Key, Value>& m, OutContainer& c) {
		std::transform(m.begin(), m.end(),
			std::inserter(c, std::end(c)), [](auto p) {return p.first; });
	}

	template <class Key, class Value, class OutContainer>
	inline void map_values(const std::map<Key, Value>& m, OutContainer& c) {
		std::transform(m.begin(), m.end(),
			std::inserter(c, std::end(c)), [](auto p) {return p.second; });
	}

	namespace ranges {
		template <class T, std::ranges::range R>
		auto to(R&& r) {
			return T(std::ranges::begin(r), std::ranges::end(r));
		}
	}


}
