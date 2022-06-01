/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		Helper.cpp
//��  �ܣ�		ʵ�ָ�������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��01��
//��  �£�		2021��03��29��
//��  �ȣ�		250��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"						//MFCͷ�ļ�
#include "Helper.h"						//��������ͷ�ļ�
#include<comutil.h>						//���ù��ܺ���ͷ�ļ�	
#pragma comment(lib, "comsuppw.lib")	//���ù��ܺ������ļ�


//��  �ƣ�		Separate()
//��  �ܣ�		�зִ�
//��  ����		string&,vector<string>&
//����ֵ��		��
void Separate(string& sDiagnosises, vector<string>& DiagNames)
{
	//������ַ���
	wstring str = StoWs(sDiagnosises);

	//�����зֵĿ�ʼ�ͽ���λ��
	int nSepPosition = 0;

	//����ָ�λ��
	vector<int> SepPositions;
	//��ӵ�1��Ԫ��
	SepPositions.push_back(nSepPosition);

	//���������ַ�
	unsigned int i = nSepPosition;
	while (i<str.size())
	{
		//����Ƿ�Ϊ�ָ���
		WCHAR ch = str[i];

		if (ch == ',' || ch == ';' ||
			ch == L'��' || ch == L'��' ||
			ch == L'��')
		{
			//��ȡ�ָ�λ��
			nSepPosition = i;

			//��ӵ��ָ�λ���б�
			SepPositions.push_back(nSepPosition);

			//����λ��
			i++;
		}
		else
		{
			//����λ��
			i++;
		}
	}

	//������һ��Ԫ�طָ�����λ��
	//ע�⣺���﷢��һ������Ӧ���ǿ��ַ���str�ĳ��ȣ�����Ӧ�����ַ���sDiagnosis�ĳ���
	SepPositions.push_back(str.size());

	//�������зָ�λ�á�ע�⣺���������һ���ָ�λ��
	//�޸ģ�2014��05��01�ա����һ���ַ������Ƿָ���
	for (unsigned int i = 0; i<SepPositions.size() - 1; i++)
	{
		//��ȡ��ʼλ��
		int nStartPos = SepPositions[i];
		//����ǵڶ����ֶ�����������һ���ַ�λ��
		if (i>0)
		{
			nStartPos = SepPositions[i] + 1;
		}

		//��ȡ����λ��
		int nEndPos = SepPositions[i + 1];

		//�����ʼλ�úͽ���λ���Ƿ����
		if (nStartPos<(int)str.size()
			&& nEndPos <= (int)str.size()
			&& nStartPos != nEndPos)
		{
			//��ȡ��ǰ���ַ���
			wstring sDiagName = str.substr(nStartPos, nEndPos - nStartPos);

			//�ü����ҿո�
			RemoveSpace(sDiagName);

			//ת��Ϊ�ַ���
			string sTemp = WS2S(sDiagName);

			//��ӵ���������б�
			DiagNames.push_back(sTemp);
		}
	}
}

//��  �ƣ�		MapCStringToString()
//��  �ܣ�		��CStringӳ�䵽string
//��  ����		CString&
//����ֵ��		string
string MapCStringToString(CString& sGivenCString)
{
	CStringA sTemp(sGivenCString.GetBuffer(0));
	sGivenCString.ReleaseBuffer();

	string sReturnString = sTemp.GetBuffer(0);
	sTemp.ReleaseBuffer();

	//���ؽ��
	return sReturnString;
}

//��  �ƣ�		StoWs()
//��  �ܣ�		��stringӳ�䵽wstring
//��  ����		string&
//����ֵ��		wstring
wstring StoWs(const string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
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
string WS2S(const wstring& ws)
{
	_bstr_t t = ws.c_str();

	char* pchar = (char*)t;

	//��ȡ�ַ���
	string result = pchar;

	//���ؽ��
	return result;
}

//��  �ƣ�		RemoveSpace()
//��  �ܣ�		ȥ���ո�
//��  ����		string&
//����ֵ��		��
void RemoveSpace(wstring& str)
{
	//��ȡ���ַ�
	wstring buff(str);

	//����ո��
	WCHAR space = ' ';

	//�ü����ҿո�
	str.assign(buff.begin() + buff.find_first_not_of(space), buff.begin() + buff.find_last_not_of(space) + 1);
}

//��  �ƣ�		TransformCStringToDouble()
//��  �ܣ�		��stringת��Ϊdouble
//��  ����		CString
//����ֵ��		dobule
double TransformStringToDouble(string sProbability)
{
	//��stringץ��Ϊdouble
	double fProb = atof(sProbability.c_str());

	//���ؽ��
	return fProb;
}

//��  �ƣ�		TransformStringToInt()
//��  �ܣ�		��stringת��Ϊunsigned int
//��  ����		string
//����ֵ��		unsigned int
unsigned int TransformStringToInt(string sNumber)
{
	//��stringץ��Ϊunsigned int
	unsigned int nNumber = (unsigned int)atoi(sNumber.c_str());

	//���ؽ��
	return nNumber;
}

// ��  �ƣ�		GetAttribute()
// ��  �ܣ�		��ȡ����ֵ
// ��  ����		TiXmlElement*,const char*
// ����ֵ��		string
string GetAttribute(TiXmlElement *pEle, const char * name)
{
	const char * s = pEle->Attribute(name);
	if (s) return s;	// ���const char *��Ϊ�գ������ַ���
	else return "";		// ����ǿ�ָ�룬���ؿ��ַ���
}

//��  �ƣ�		IsINTInVector()
//��  �ܣ�		����޺����ͱ����Ƿ����б���
//��  ����		unsigned int&,vector<unsigned int>&,unsigned int&
//����ֵ��		bool
bool IsINTInVector(unsigned int& nValue, vector<unsigned int>& Values, unsigned int& nPos)
{
	//��������ֵ
	for (unsigned int i = 0; i < Values.size(); i++)
	{
		//����Ƿ����
		if (nValue == Values[i])
		{
			//���·��ص�λ��
			nPos = i;

			//������
			return true;
		}
	}

	//ȱʡ���ؼ�
	return false;
}

//��  �ƣ�		IsINTInSet()
//��  �ܣ�		����޷��������Ƿ��ڼ�����
//��  ����		unsigned int&,set<unsigned int>&
//����ֵ��		bool
bool IsINTInSet(unsigned int& nNumber, set<unsigned int>& Numbers)
{
	//�ڼ����в���
	set<unsigned int>::iterator it = Numbers.find(nNumber);
	if (it != Numbers.end())
	{
		//�ҵ�
		return true;
	}
	else
	{
		//δ�ҵ�
		return false;
	}
}