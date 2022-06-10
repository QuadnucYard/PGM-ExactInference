////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_OutputResult.cpp
// 输出查询结果到XML/YAML文件
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct_IO.h"

namespace pgm {

//输出查询结果
void CBNSumProductWriter::OutputResult(const std::string& filename, const fvallist& queryResults)
{
	namespace fs = std::filesystem;

#ifndef USE_YAML

	TiXmlDocument doc;
	//设置文档属性
	TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "GBK", "");
	//连接描述信息到文档
	doc.LinkEndChild(pDecl);

	TiXmlElement* pRootElement = new TiXmlElement("Probilities");
	doc.LinkEndChild(pRootElement);

	for (fval_t qr : queryResults)
	{
		TiXmlElement* pProbability = new TiXmlElement("Probability");
		pProbability->SetAttribute("PROBABILITY_VALUE", std::format("{:.6f}", qr).c_str());
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

	namespace fs = std::filesystem;
	fs::path path = fs::current_path() / "Data" / (filename + ".yaml");
	std::ofstream fout(path);
	fout << root;
	fout.close();

#endif // !USE_YAML

	ShellExecute(NULL, L"open", path.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

}
