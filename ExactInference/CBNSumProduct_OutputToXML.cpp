////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_OutputToXML.cpp
// 输出查询结果到XML文件
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"

#ifndef USE_YAML

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

	namespace fs = std::filesystem;
	fs::path sFileName = fs::current_path() / "Data" / "Output.xml";
	doc.SaveFile(sFileName.string().c_str());
	doc.Clear();

	//自动打开文件
	ShellExecute(NULL, _T("open"), sFileName.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

#endif // !USE_YAML