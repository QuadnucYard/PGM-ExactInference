#pragma once
#include "tinyxml.h"
#include <iterator>

class TiXmlElementIterator {
private:
	using self = TiXmlElementIterator;
public:
	using iterator_category = std::forward_iterator_tag;
	using value_type = TiXmlElement;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using reference = value_type&;
private:
	TiXmlElement* it;
public:
	inline TiXmlElementIterator(TiXmlElement* ele): it(ele) {}
	inline self operator ++ () { it = it->NextSiblingElement(); return *this; }
	inline const reference operator * () const { return *it->FirstChildElement(); }
	inline reference operator * () { return *it; }
	inline pointer operator -> () { return it; }
	inline bool operator == (const self& o) const { return it == o.it; }
	inline bool operator != (const self& o) const { return it != o.it; }
};

inline TiXmlElementIterator begin(TiXmlElement* ele) {
	return TiXmlElementIterator(ele ? ele->FirstChildElement() : nullptr);
}

inline TiXmlElementIterator end(TiXmlElement* ele) {
	return TiXmlElementIterator(nullptr);
}

inline TiXmlElementIterator begin(TiXmlElement& ele) {
	return begin(&ele);
}

inline TiXmlElementIterator end(TiXmlElement& ele) {
	return TiXmlElementIterator(nullptr);
}