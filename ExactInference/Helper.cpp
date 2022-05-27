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

	//���ؽ��
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
	//���ؽ��
	return (char*)(_bstr_t)ws.c_str();
}

//��  �ƣ�		RemoveSpace()
//��  �ܣ�		ȥ���ո�
//��  ����		string&
//����ֵ��		��
void RemoveSpace(std::wstring& str)
{
	std::wstring buff(str);
	WCHAR space = ' ';
	//�ü����ҿո�
	auto x1 = buff.find_first_not_of(space), x2 = buff.find_last_not_of(space);
	str.assign(buff.begin() + buff.find_first_not_of(space), buff.begin() + buff.find_last_not_of(space) + 1);
}

//��  �ƣ�		TransformCStringToDouble()
//��  �ܣ�		��stringת��Ϊdouble
//��  ����		CString
//����ֵ��		dobule
double TransformStringToDouble(const std::string& sProbability)
{
	return atof(sProbability.c_str());
}

//��  �ƣ�		TransformStringToInt()
//��  �ܣ�		��stringת��Ϊint
//��  ����		string
//����ֵ��		int
int TransformStringToInt(const std::string& sNumber)
{
	return atoi(sNumber.c_str());
}

// ��  �ƣ�		GetAttribute()
// ��  �ܣ�		��ȡ����ֵ
// ��  ����		TiXmlElement*,const char*
// ����ֵ��		string
std::string GetAttribute(TiXmlElement* pEle, const char* name)
{
	const char* s = pEle->Attribute(name);
	if (s) return s;	// ���const char *��Ϊ�գ������ַ���
	else return "";		// ����ǿ�ָ�룬���ؿ��ַ���
}
