/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		Helper.cpp
//功  能：		实现辅助函数
//开发者：		高志强
//日  期：		2021年03月01日
//更  新：		2021年03月29日
//长  度：		250行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Helper.h"
#include <regex>


//名  称：		Separate()
//功  能：		切分串
//参  数：		string&,vector<string>&
//返回值：		无
void Separate(const std::string& str, std::vector<std::string>& result)
{
	std::regex re("[\\s,;，；、]+");
	std::copy(std::sregex_token_iterator(str.begin(), str.end(), re, -1),
		std::sregex_token_iterator(),
		std::back_inserter(result));
}

auto Separate(const std::string& str)
{
	std::regex re("[\\s,;，；、]+");
	return std::sregex_token_iterator(str.begin(), str.end(), re, -1);
}

//名  称：		MapCStringToString()
//功  能：		将CString映射到string
//参  数：		CString&
//返回值：		string
std::string MapCStringToString(CString& sGivenCString)
{
	CStringA sTemp(sGivenCString.GetBuffer(0));
	sGivenCString.ReleaseBuffer();

	std::string sReturnString = sTemp.GetBuffer(0);
	sTemp.ReleaseBuffer();

	return sReturnString;
}

//名  称：		StoWs()
//功  能：		将string映射到wstring
//参  数：		string&
//返回值：		wstring
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

//名  称：		WS2S()
//功  能：		将wstring转换为string
//参  数：		wstring&
//返回值：		string
std::string WS2S(const std::wstring& ws)
{
	return (char*)(_bstr_t)ws.c_str();
}
