////////////////////////////////////////////////////////////////////////////////
// Helper.h
// ���帨������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <locale>


//��stringת��Ϊwstring
std::wstring StoWs(const std::string& s);
//��wstringת��Ϊstring
std::string WS2S(const std::wstring& ws);

void msgerr(const char* msg);

//���ļ�
void shellOpen(const wchar_t* path);