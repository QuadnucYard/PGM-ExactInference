////////////////////////////////////////////////////////////////////////////////
// Helper.h
// 定义辅助函数
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <locale>


//将string转换为wstring
std::wstring StoWs(const std::string& s);
//将wstring转换为string
std::string WS2S(const std::wstring& ws);

void msgerr(const char* msg);

//打开文件
void shellOpen(const wchar_t* path);