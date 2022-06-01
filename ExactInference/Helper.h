////////////////////////////////////////////////////////////////////////////////
// Helper.h
// 定义辅助函数
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <vector>


//切分串。例如将输入的长的字符串切分为多个短串（无符号整数）等
void Separate(const std::string&, std::vector<std::string>&);

auto Separate(const std::string&);

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
