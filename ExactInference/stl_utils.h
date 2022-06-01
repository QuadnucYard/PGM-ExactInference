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

	template <class C, class Pred>
	inline void remove_if(C& c, Pred pred) {
		auto ret = std::ranges::remove_if(c, pred);
		c.erase(ret.begin(), ret.end());
	}

	template <class C, class _Pj = std::identity>
	inline void remove(C& c, _Pj _Proj = {}) {
		auto ret = std::ranges::remove(c, _Proj);
		c.erase(ret.begin(), ret.end());
	}

	template <class C, class OutIt, class Pred>
	inline void split(C& c, OutIt out_true, Pred pred) {
		auto ret = std::ranges::partition_copy(c, out_true, std::begin(c), pred);
		c.erase(ret.out2, std::end(c));
	}

	template <class Key, class Value, class OutContainer>
	inline void map_keys(const std::map<Key, Value>& m, OutContainer& c) {
		std::ranges::transform(m,
			std::inserter(c, std::end(c)), [](auto p) {return p.first; });
	}

	template <class Key, class Value, class OutContainer>
	inline void map_values(const std::map<Key, Value>& m, OutContainer& c) {
		std::ranges::transform(m,
			std::inserter(c, std::end(c)), [](auto p) {return p.second; });
	}

	template <class T>
	inline std::vector<T> concat(const std::vector<T>& first, const std::vector<T>& second) {
		std::vector<T> result {first};
		result.insert(result.end(), second.begin(), second.end());
		return result;
	}

	template <class T>
	inline std::vector<T> concat(const std::vector<T>& first, const T& second) {
		std::vector<T> result {first};
		result.push_back(second);
		return result;
	}

	template <class Result, std::ranges::input_range _Rng1, std::ranges::input_range _Rng2>
	Result set_intersection(_Rng1&& first, _Rng2&& second) {
		Result result{};
		std::ranges::set_intersection(first, second, std::inserter(result, std::end(result)));
		return result;
	}

	template <class Result, std::ranges::input_range _Rng1, std::ranges::input_range _Rng2>
	Result set_union(_Rng1&& first, _Rng2&& second) {
		Result result{};
		std::ranges::set_union(first, second, std::inserter(result, std::end(result)));
		return result;
	}
	
	template <class Result, std::ranges::input_range _Rng1, std::ranges::input_range _Rng2>
	Result set_difference(_Rng1&& first, _Rng2&& second) {
		Result result{};
		std::ranges::set_difference(first, second, std::inserter(result, std::end(result)));
		return result;
	}

	template <class T>
	inline constexpr auto set_inserter(std::set<T>& s) {
		return std::inserter(s, s.end());
	}

	template <class C>
	inline constexpr auto sorted(const C& c) {
		C result {c};
		std::ranges::sort(result);
		return result;
	}

	template <class Cont, std::ranges::input_range _Rng>
	Cont except(const Cont& first, _Rng&& second) {
		Cont result {first};
		std::ranges::copy_if(first, std::inserter(result, std::end(result)), 
			[&](auto t) {return std::ranges::find(second, t) == std::ranges::end(second); });
		return result;
	}
}
