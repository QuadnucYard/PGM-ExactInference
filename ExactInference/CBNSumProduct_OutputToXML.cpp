/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CBNSumProduct_OutputToXML.cpp
//��  �ܣ�		�����ѯ�����XML�ļ�
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��10��
//��  �£�		2021��03��24��
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ExactInference.h"
#include "CBNSumProduct.h"
#include "tinyxml.h"
#include <format>

extern CExactInferenceApp theApp;

//�����ѯ�����XML�ļ�
void CBNSumProduct::OutputToXML()
{
	TiXmlDocument doc;
	//�����ĵ�����
	TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "GBK", "");
	//����������Ϣ���ĵ�
	doc.LinkEndChild(pDecl);

	TiXmlElement *pRootElement = new TiXmlElement("Probilities");
	doc.LinkEndChild(pRootElement);

	for (fval_t qr : m_QueryResults)
	{
		TiXmlElement* pProbability = new TiXmlElement("Probability");
		pProbability->SetAttribute("PROBABILITY_VALUE", std::format("{:.6f}", qr).c_str());
		pRootElement->LinkEndChild(pProbability);
	}

	CString sFileName = theApp.m_sWorkPath + _T("\\Data\\Output.xml");
	USES_CONVERSION;
	doc.SaveFile(T2A(sFileName));
	doc.Clear();

	//�Զ����ļ�
	ShellExecute(NULL, _T("open"), sFileName, NULL, NULL, SW_SHOWNORMAL);
}