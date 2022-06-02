////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_OutputToXML.cpp
// �����ѯ�����XML�ļ�
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"

#ifndef USE_YAML

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

	namespace fs = std::filesystem;
	fs::path sFileName = fs::current_path() / "Data" / "Output.xml";
	doc.SaveFile(sFileName.string().c_str());
	doc.Clear();

	//�Զ����ļ�
	ShellExecute(NULL, _T("open"), sFileName.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

#endif // !USE_YAML