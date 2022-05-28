/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		Helper.cpp
//��  �ܣ�		ʵ�ָ�������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��01��
//��  �£�		2021��03��29��
//��  �ȣ�		250��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Helper.h"
#include <regex>


//��  �ƣ�		Separate()
//��  �ܣ�		�зִ�
//��  ����		string&,vector<string>&
//����ֵ��		��
void Separate(const std::string& str, std::vector<std::string>& result)
{
	std::regex re("[\\s,;������]+");
	std::copy(std::sregex_token_iterator(str.begin(), str.end(), re, -1),
		std::sregex_token_iterator(),
		std::back_inserter(result));
}

auto Separate(const std::string& str)
{
	std::regex re("[\\s,;������]+");
	return std::sregex_token_iterator(str.begin(), str.end(), re, -1);
}

//��  �ƣ�		MapCStringToString()
//��  �ܣ�		��CStringӳ�䵽string
//��  ����		CString&
//����ֵ��		string
std::string MapCStringToString(CString& sGivenCString)
{
	CStringA sTemp(sGivenCString.GetBuffer(0));
	sGivenCString.ReleaseBuffer();

	std::string sReturnString = sTemp.GetBuffer(0);
	sTemp.ReleaseBuffer();

	return sReturnString;
}

//��  �ƣ�		StoWs()
//��  �ܣ�		��stringӳ�䵽wstring
//��  ����		string&
//����ֵ��		wstring
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

//��  �ƣ�		WS2S()
//��  �ܣ�		��wstringת��Ϊstring
//��  ����		wstring&
//����ֵ��		string
std::string WS2S(const std::wstring& ws)
{
	return (char*)(_bstr_t)ws.c_str();
}
