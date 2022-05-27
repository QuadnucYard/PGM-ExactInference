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

	//返回结果
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
	//返回结果
	return (char*)(_bstr_t)ws.c_str();
}

//名  称：		RemoveSpace()
//功  能：		去除空格
//参  数：		string&
//返回值：		无
void RemoveSpace(std::wstring& str)
{
	std::wstring buff(str);
	WCHAR space = ' ';
	//裁剪左右空格
	auto x1 = buff.find_first_not_of(space), x2 = buff.find_last_not_of(space);
	str.assign(buff.begin() + buff.find_first_not_of(space), buff.begin() + buff.find_last_not_of(space) + 1);
}

//名  称：		TransformCStringToDouble()
//功  能：		将string转换为double
//参  数：		CString
//返回值：		dobule
double TransformStringToDouble(const std::string& sProbability)
{
	return atof(sProbability.c_str());
}

//名  称：		TransformStringToInt()
//功  能：		将string转换为int
//参  数：		string
//返回值：		int
int TransformStringToInt(const std::string& sNumber)
{
	return atoi(sNumber.c_str());
}

// 名  称：		GetAttribute()
// 功  能：		获取属性值
// 参  数：		TiXmlElement*,const char*
// 返回值：		string
std::string GetAttribute(TiXmlElement* pEle, const char* name)
{
	const char* s = pEle->Attribute(name);
	if (s) return s;	// 如果const char *不为空，返回字符串
	else return "";		// 如果是空指针，返回空字符串
}
