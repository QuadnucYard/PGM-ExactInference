////////////////////////////////////////////////////////////////////////////////
// Helper.cpp
// 实现辅助函数
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Helper.h"


//将string映射到wstring
std::wstring StoWs(const std::string& s)
{
	size_t slength = s.length() + 1;
	size_t len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

//将wstring转换为string
std::string WS2S(const std::wstring& ws)
{
	return (char*)(_bstr_t)ws.c_str();
}

void msgerr(const char* msg) {
	static auto _ = setlocale(LC_ALL, "chs");
	wchar_t buf[255];
	swprintf(buf, sizeof(buf) / sizeof(wchar_t), L"%hs", msg);
	AfxMessageBox(buf);
}
