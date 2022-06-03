////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_OutputResult.cpp
// �����ѯ�����XML/YAML�ļ�
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"

#ifndef USE_YAML

//�����ѯ�����XML�ļ�
void CBNSumProduct::OutputResult()
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

	namespace fs = std::filesystem;
	fs::path sFileName = fs::current_path() / "Data" / "Output.xml";
	doc.SaveFile(sFileName.string().c_str());
	doc.Clear();

	//�Զ����ļ�
	ShellExecute(NULL, _T("open"), sFileName.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

#else

void CBNSumProduct::OutputResult()
{
	YAML::Node root;

	for (fval_t qr : m_QueryResults)
	{
		root["prob"].push_back(std::format("{:.6f}", qr));
	}

	namespace fs = std::filesystem;
	fs::path path = fs::current_path() / "Data" / "Output.yaml";
	std::ofstream fout(path);
	fout << root;
	fout.close();

	ShellExecute(NULL, L"open", path.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

#endif // !USE_YAML