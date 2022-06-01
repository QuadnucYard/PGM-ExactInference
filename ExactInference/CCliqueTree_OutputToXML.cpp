////////////////////////////////////////////////////////////////////////////////
// CClique_OutputToXML.cpp
// �����ѯ�����XML�ļ�
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"
#include <format>


//�����ѯ�����XML�ļ�
void CCliqueTree::OutputToXML() const
{
	TiXmlDocument doc;
	TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "GBK", "");
	doc.LinkEndChild(pDecl);

	TiXmlElement *pRootElement = new TiXmlElement("Probilities");
	doc.LinkEndChild(pRootElement);

	for (fval_t v : m_CTQueryResults)
	{
		TiXmlElement* pProbability = new TiXmlElement("Probability");
		pProbability->SetAttribute("PROBABILITY_VALUE", std::format("{:.6f}", v).c_str());
		pRootElement->LinkEndChild(pProbability);
	}

	namespace fs = std::filesystem;
	fs::path sPath = fs::current_path() / "Data" / "CliqueTree_Output.xml";

	doc.SaveFile(sPath.string().c_str());
	doc.Clear();

	ShellExecute(NULL, L"open", sPath.c_str(), NULL, NULL, SW_SHOWNORMAL);
}