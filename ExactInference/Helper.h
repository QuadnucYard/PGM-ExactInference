////////////////////////////////////////////////////////////////////////////////
// Helper.h
// 定义辅助函数
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <vector>
#include <locale>


//将string转换为wstring
std::wstring StoWs(const std::string& s);
//将wstring转换为string
std::string WS2S(const std::wstring& ws);

//将字符串转换为双精度数
inline double stod_(const std::string& str) {
	return std::stod(str);
}
//将字符串转换为整数
inline int stoi_(const std::string& str) {
	return std::stoi(str);
}

void msgerr(const char* msg);