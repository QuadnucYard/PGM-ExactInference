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
double TransformStringToDouble(const std::string&);
//���ַ���ת��Ϊ����
int TransformStringToInt(const std::string&);

//��ȡXML�ļ������Ե�ֵ
std::string GetAttribute(TiXmlElement* pEle, const char* name);
