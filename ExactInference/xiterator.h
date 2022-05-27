#pragma once
#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING
#include <iterator>
#include <map>

namespace qy {


	template <class Key, class Value>
	class map_key_iterator {
	private:
		using _Tp = Key;
		using self = map_key_iterator;
		using mapiterator = typename std::map<Key, Value>::iterator;
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = _Tp;
		using difference_type = std::ptrdiff_t;
		using pointer = const _Tp*;
		using reference = const  _Tp&;
	private:
		mapiterator it;
	public:
		inline map_key_iterator(mapiterator it): it(it) {}
		inline self operator ++ () { ++it; return *this; }
		inline reference operator * () const { return it->first; }
		inline pointer operator -> () const { return &it->first; }
		inline bool operator == (const self& o) const { return it == o.it; }
		inline bool operator != (const self& o) const { return it != o.it; }
	};

	template <class Key, class Value>
	inline map_key_iterator<Key, Value> keys_begin(std::map<Key, Value>& m) {
		return map_key_iterator<Key, Value>(m.begin());
	}

	template <class Key, class Value>
	inline map_key_iterator<Key, Value> keys_end(std::map<Key, Value>& m) {
		return map_key_iterator<Key, Value>(m.end());
	}

	template <class Key, class Value>
	class map_value_iterator {
	private:
		using _Tp = Value;
		using self = map_value_iterator;
		using mapiterator = typename std::map<Key, Value>::iterator;
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = _Tp;
		using difference_type = std::ptrdiff_t;
		using pointer = const _Tp*;
		using reference = const  _Tp&;
	private:
		mapiterator it;
	public:
		inline map_value_iterator(mapiterator it): it(it) {}
		inline self operator ++ () { ++it; return *this; }
		inline reference operator * () const { return it->second; }
		inline pointer operator -> () const { return &it->second; }
		inline bool operator == (const self& o) const { return it == o.it; }
		inline bool operator != (const self& o) const { return it != o.it; }
	};

	template <class Key, class Value>
	inline map_value_iterator<Key, Value> values_begin(std::map<Key, Value>& m) {
		return map_value_iterator<Key, Value>(m.begin());
	}

	template <class Key, class Value>
	inline map_value_iterator<Key, Value> values_end(std::map<Key, Value>& m) {
		return map_value_iterator<Key, Value>(m.end());
	}
}