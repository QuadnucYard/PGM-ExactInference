////////////////////////////////////////////////////////////////////////////////
// CClique_OutputResult.cpp
// 输出查询结果到XML/YAML文件
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree_IO.h"


//输出查询结果
void CCliqueTreeWriter::OutputResult(const std::string& filename, const fvallist& queryResults)
{
	namespace fs = std::filesystem;

#ifndef USE_YAML
	TiXmlDocument doc;
	TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "GBK", "");
	doc.LinkEndChild(pDecl);

	TiXmlElement *pRootElement = new TiXmlElement("Probilities");
	doc.LinkEndChild(pRootElement);

	for (fval_t v : queryResults)
	{
		TiXmlElement* pProbability = new TiXmlElement("Probability");
		pProbability->SetAttribute("PROBABILITY_VALUE", std::format("{:.6f}", v).c_str());
		pRootElement->LinkEndChild(pProbability);
	}

	fs::path path = fs::current_path() / "Data" / (filename + ".xml");

	doc.SaveFile(path.string().c_str());
	doc.Clear();

#else

	YAML::Node root;
	for (fval_t qr : queryResults)
	{
		root["prob"].push_back(std::format("{:.6f}", qr));
	}

	fs::path path = fs::current_path() / "Data" / (filename + ".yaml");
	std::ofstream fout(path);
	fout << root;
	fout.close();

#endif // !USE_YAML

	ShellExecute(NULL, L"open", path.c_str(), NULL, NULL, SW_SHOWNORMAL);
}