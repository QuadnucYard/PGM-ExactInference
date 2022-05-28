#pragma once
#include <ranges>

namespace qy {

	namespace views {
		template <class T>
		class _To_fn {
		public:
			template <std::ranges::range R>
			friend constexpr auto operator|(R&& __r, _To_fn self) {
				return T(std::ranges::begin(__r), std::ranges::end(__r));
			}
		};

		template <class T>
		inline constexpr _To_fn<T> to;

		class _Tokenize_view {
			using tokenit = std::sregex_token_iterator;
			tokenit first;
		public:
			_Tokenize_view(tokenit it): first(it) {}
			tokenit begin() { return first; }
			tokenit end() { return tokenit {}; }
		};

		template <class Regex>
		class _Tokenize_impl {
			Regex re;
		public:
			_Tokenize_impl(Regex&& re): re(re) {}
			template <std::ranges::range R>
			friend auto operator|(R&& __r, _Tokenize_impl&& self) {
				return _Tokenize_view(std::sregex_token_iterator(std::ranges::begin(__r), std::ranges::end(__r), self.re, -1));
			}
		};

		class _Tokenize_fn {
		public:
template <class Regex>
			auto operator()(Regex re) {
				return _Tokenize_impl(std::forward<std::regex>(re));
			}
		};

		inline _Tokenize_fn tokenize;
	}
}