/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CBNSumProduct_OutputToXML.cpp
//功  能：		输出查询结果到XML文件
//开发者：		高志强
//日  期：		2021年03月10日
//更  新：		2021年03月24日
//长  度：		70行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ExactInference.h"
#include "CBNSumProduct.h"
#include "tinyxml.h"
#include <format>

extern CExactInferenceApp theApp;

//输出查询结果到XML文件
void CBNSumProduct::OutputToXML()
{
	TiXmlDocument doc;
	//设置文档属性
	TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "GBK", "");
	//连接描述信息到文档
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

	//自动打开文件
	ShellExecute(NULL, _T("open"), sFileName, NULL, NULL, SW_SHOWNORMAL);
}