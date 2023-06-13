#pragma once
#include <ranges>

namespace qy_exp {

#define _SR ::std::ranges:: 

	namespace ranges {


		template <_SR input_range _Vw, _SR input_range _Rng>
		class except_view: public _SR view_interface<except_view<_Vw, _Rng>>
		{
		private:
			_Vw vw;
			_Rng other;

			struct _Iterator: _SR iterator_t<_Vw>
			{
				using base = _SR iterator_t<_Vw>;
				using reference = typename _SR range_value_t<_Vw>;

				_Iterator(base const& b, _Rng _other): base {b}, other(_other) {}

				_Iterator operator++(int) {
					return static_cast<base&>(*this)++;
				}

				_Iterator& operator++() {
					++static_cast<base&>(*this);
					return (*this);
				}

				reference operator*() const {
					return *static_cast<base>(*this);
				}

			private:
				_Rng other;
			};

		public:
			using iterator = _Iterator;
			using const_iterator = _Iterator;

			except_view() = default;
			constexpr except_view(_Vw _vw, _Rng _Range): vw(std::move(vw)), other(_Range) {}

			constexpr iterator begin() const {
				return iterator(std::begin(vw), other);
			}
			constexpr iterator end() const {
				return iterator(std::end(vw), other);
			}
			constexpr iterator begin() {
				return iterator(std::begin(vw), other);
			}
			constexpr iterator end() {
				return iterator(std::end(vw), other);
			}
		};

		template <class _Rng, class _Rng2>
		except_view(_Rng&&, _Rng2)->except_view<_SR views::all_t<_Rng>, _SR views::all_t<_Rng2>>;

		namespace views {

			struct _Except_fn {
				template <_SR viewable_range _Vw, _SR input_range _Rng>
				constexpr auto operator()(_Vw&& _vw, _Rng&& _Range) const {
					return except_view(std::forward<_Vw>(_vw), std::forward<_Rng>(_Range));
				}

				template <_SR input_range _Rng>
				constexpr auto operator()(_Rng&& _Range) const {
					return _SR _Range_closure<_Except_fn, std::decay_t<_Rng>>{ std::forward<_Rng>(_Range)};
				}
				
			};

			inline constexpr _Except_fn except;

		}


		template <_SR input_range _Vw>
		class enumerate_view: public _SR view_interface<enumerate_view<_Vw>>
		{
		private:
			struct _Iterator: _SR iterator_t<_Vw>
			{
				using base = _SR iterator_t<_Vw>;
				using range_value = _SR range_value_t<_Vw>;
				using value_type = std::pair<size_t, range_value&>;
				base it;

				_Iterator(base b): base {b}, index {0}, it(b) {}

				_Iterator& operator++() {
					++static_cast<base&>(*this);
					++index;
					++it;
					return *this;
				}
				value_type operator*() {
					return value_type(index, *it);
				}

				value_type operator*() const {
					return value_type(index, *it);
				}

			private:
				size_t index;
			};

			_Vw _Range;

		public:
			using iterator = _Iterator;
			using const_iterator = _Iterator;

			enumerate_view() = default;
			constexpr enumerate_view(_Vw _Range): _Range(std::move(_Range)) {}

			constexpr iterator begin() const {
				return iterator(std::begin(_Range));
			}
			constexpr iterator end() const {
				return iterator(std::end(_Range));
			}
			constexpr iterator begin() {
				return iterator(std::begin(_Range));
			}
			constexpr iterator end() {
				return iterator(std::end(_Range));
			}
		};

		template <class _Rng>
		enumerate_view(_Rng&&)->enumerate_view<_SR views::all_t<_Rng>>;

		namespace views {

			struct _Enumerate_fn {
				template <_SR viewable_range _Vw>
				constexpr auto operator()(_Vw&& _vw) const {
					return enumerate_view {std::forward<_Vw>(_vw)};
				}

				constexpr auto operator()() const {
					return _SR _Range_closure<_Enumerate_fn>{};
				}
			};

			inline constexpr _Enumerate_fn enumerate;

		}

	}

	namespace views = ranges::views;

#undef _SR
}
