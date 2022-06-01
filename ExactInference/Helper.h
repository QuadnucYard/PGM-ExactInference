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


//�зִ������罫����ĳ����ַ����з�Ϊ����̴����޷�����������
void Separate(const std::string&, std::vector<std::string>&);

auto Separate(const std::string&);

//��stringת��Ϊwstring
std::wstring StoWs(const std::string& s);
//��wstringת��Ϊstring
std::string WS2S(const std::wstring& ws);

//���ַ���ת��Ϊ˫������
inline double stod_(const std::string& str) {
	return std::stod(str);
}
//���ַ���ת��Ϊ����
inline int stoi_(const std::string& str) {
	return std::stoi(str);
}
