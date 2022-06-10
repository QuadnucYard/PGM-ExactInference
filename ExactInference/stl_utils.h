#pragma once
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <iterator>
#include <ranges>

#define LAMBDA(x, func) [&] (auto &&x) { return (func); }

namespace qy {

	/*template <class T>
	std::ostream& operator <<(std::ostream& out, const std::vector<T>& rhs) {
		out << "{";
		std::copy(rhs.begin(), rhs.end(), std::ostream_iterator<T>(out, ","));
		out << "}";
		return out;
	}*/

	template <class C, class Pred>
	inline void remove_if(C& c, Pred pred) {
		auto ret = std::ranges::remove_if(c, pred);
		c.erase(ret.begin(), ret.end());
	}

	template <class C, class _Ty, class _Pj = std::identity>
	inline void remove(C& c, const _Ty& _Val, _Pj _Proj = {}) {
		auto ret = std::ranges::remove(c, _Val, _Proj);
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
		Result result {};
		std::ranges::set_intersection(first, second, std::inserter(result, std::end(result)));
		return result;
	}

	template <class Result, std::ranges::input_range _Rng1, std::ranges::input_range _Rng2>
	Result set_union(_Rng1&& first, _Rng2&& second) {
		Result result {};
		std::ranges::set_union(first, second, std::inserter(result, std::end(result)));
		return result;
	}

	template <class Result, std::ranges::input_range _Rng1, std::ranges::input_range _Rng2>
	Result set_difference(_Rng1&& first, _Rng2&& second) {
		Result result {};
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

	template <class C>
	inline constexpr auto reversed(const C& c) {
		C result {c};
		std::ranges::reverse(result);
		return result;
	}

	template <class Cont, std::ranges::input_range _Rng, class _Pj1 = std::identity, class _Pj2 = std::identity>
	Cont except(const Cont& first, _Rng&& second, _Pj1 _Proj1 = {}, _Pj2 _Proj2 = {}) {
		Cont result {};
		std::ranges::copy_if(first, std::inserter(result, std::end(result)),
			[&](auto&& t) { return std::ranges::find(second, std::invoke(_Proj1, t), _Proj2) == std::ranges::end(second); });
		return result;
	}

	template <class Cont, class _Ty, class _Pj = std::identity>
	Cont except(const Cont& first, const _Ty& _Val, _Pj _Proj = {}) {
		Cont result {};
		std::ranges::copy_if(first, std::inserter(result, std::end(result)),
			[&](auto&& t) { return std::invoke(_Proj, t) != _Val; });
		return result;
	}
}
