////////////////////////////////////////////////////////////////////////////////
// Helper.h
// ���帨������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <vector>
#include <locale>


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

void msgerr(const char* msg);