/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		Helper.h
//��  �ܣ�		���帨������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��01��
//��  �£�		2021��03��29��
//��  �ȣ�		60��
/////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <vector>
#include "TinyXML.h"


//�зִ������罫����ĳ����ַ����з�Ϊ����̴����޷�����������
void Separate(const std::string&, std::vector<std::string>&);

//��CStringӳ�䵽string
std::string MapCStringToString(CString&);
//��stringת��Ϊwstring
std::wstring StoWs(const std::string& s);
//��wstringת��Ϊstring
std::string WS2S(const std::wstring& ws);
//ȥ���ո�
void RemoveSpace(std::wstring& str);

//���ַ���ת��Ϊ˫������
inline double stod_(const std::string& str) {
	return std::stod(str);
}
//���ַ���ת��Ϊ����
inline int stoi_(const std::string& str) {
	return std::stoi(str);
}

//��ȡXML�ļ������Ե�ֵ
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