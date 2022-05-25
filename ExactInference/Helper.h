/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		Helper.h
//��  �ܣ�		���帨������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��01��
//��  �£�		2021��03��29��
//��  �ȣ�		60��
/////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <map>								//mapͷ�ļ�
#include <set>								//setͷ�ļ�
#include <string>							//stringͷ�ļ�
#include <list>								//listͷ�ļ�
#include <vector>							//vectorͷ�ļ�
#include <algorithm>						//algorithm��ͷ�ļ�
#include <numeric>							//numeric��ͷ�ļ�
#include <sstream>							//sstream��ͷ�ļ�
#include <fstream>							//fstream��ͷ�ļ�
#include <iostream>							//iostream��ͷ�ļ�
#include <time.h>							//ʱ�亯����ͷ�ļ�
#include "math.h"							//��ѧ����ͷ�ļ�
#include "TinyXML.h"								//TinyXMLͷ�ļ�


//���������ռ�
using namespace std;						//ʹ�ñ�׼�����ռ�


//�зִ������罫����ĳ����ַ����з�Ϊ����̴����޷�����������
void Separate(string&, vector<string>&);

//��CStringӳ�䵽string
string MapCStringToString(CString&);
//��stringת��Ϊwstring
wstring StoWs(const std::string& s);
//��wstringת��Ϊstring
string WS2S(const wstring& ws);
//ȥ���ո�
void RemoveSpace(wstring& str);

//���ַ���ת��Ϊ˫������
double TransformStringToDouble(string);
//���ַ���ת��Ϊ����
unsigned int TransformStringToInt(string);

//��ȡXML�ļ������Ե�ֵ
string GetAttribute(TiXmlElement *pEle, const char * name);

//����޷��������Ƿ����б���
bool IsINTInVector(unsigned int& nValue, vector<unsigned int>& Values, unsigned int& nPos);
//����޷��������Ƿ��ڼ�����
bool IsINTInSet(unsigned int& nNumber, set<unsigned int>& Numbers);
