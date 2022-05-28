#pragma once
#include "TinyXML.h"
#include <string>

//获取XML文件中属性的值
inline const char* GetAttribute(TiXmlElement* pEle, const char* name) {
	const char* s = pEle->Attribute(name);
	if (s) return s;
	else return "";
}

inline int GetAttributeI(TiXmlElement* pEle, const char* name) {
	return std::stoi(GetAttribute(pEle, name));
}

inline double GetAttributeD(TiXmlElement* pEle, const char* name) {
	return std::stod(GetAttribute(pEle, name));
}

inline const char* GetAttribute(const TiXmlElement& pEle, const char* name) {
	const char* s = pEle.Attribute(name);
	if (s) return s;
	else return "";
}

inline int GetAttributeI(const TiXmlElement& pEle, const char* name) {
	return std::stoi(GetAttribute(pEle, name));
}

inline double GetAttributeD(const TiXmlElement& pEle, const char* name) {
	return std::stod(GetAttribute(pEle, name));
}