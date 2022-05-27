/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		Helper.h
//功  能：		定义辅助函数
//开发者：		高志强
//日  期：		2021年03月01日
//更  新：		2021年03月29日
//长  度：		60行
/////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <vector>
#include "TinyXML.h"


//切分串。例如将输入的长的字符串切分为多个短串（无符号整数）等
void Separate(const std::string&, std::vector<std::string>&);

//将CString映射到string
std::string MapCStringToString(CString&);
//将string转换为wstring
std::wstring StoWs(const std::string& s);
//将wstring转换为string
std::string WS2S(const std::wstring& ws);
//去除空格
void RemoveSpace(std::wstring& str);

//将字符串转换为双精度数
inline double stod_(const std::string& str) {
	return std::stod(str);
}
//将字符串转换为整数
inline int stoi_(const std::string& str) {
	return std::stoi(str);
}

//获取XML文件中属性的值
const char* GetAttribute(TiXmlElement* pEle, const char* name);

inline int GetAttributeI(TiXmlElement* pEle, const char* name) {
	return std::stoi(GetAttribute(pEle, name));
}

inline double GetAttributeD(TiXmlElement* pEle, const char* name) {
	return std::stod(GetAttribute(pEle, name));
}

const char* GetAttribute(const TiXmlElement& pEle, const char* name);

inline int GetAttributeI(const TiXmlElement& pEle, const char* name) {
	return std::stoi(GetAttribute(pEle, name));
}

inline double GetAttributeD(const TiXmlElement& pEle, const char* name) {
	return std::stod(GetAttribute(pEle, name));
}