////////////////////////////////////////////////////////////////////////////////
// Helper.cpp
// ʵ�ָ�������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Helper.h"


//��stringӳ�䵽wstring
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

//��wstringת��Ϊstring
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
