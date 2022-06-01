////////////////////////////////////////////////////////////////////////////////
// CClique_OutputToXML.cpp
// 输出查询结果到XML文件
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ExactInference.h"
#include "CCliqueTree.h"
#include "tinyxml.h"


//声明外部变量，以获取当前工作路径
extern CExactInferenceApp theApp;


//输出查询结果到XML文件
void CCliqueTree::OutputToXML()
{
	//生成XML文档
	TiXmlDocument doc;
	//设置文档属性
	TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "GBK", "");
	//连接描述信息到文档
	doc.LinkEndChild(pDecl);

	//创建根元素
	TiXmlElement *pRootElement = new TiXmlElement("Probilities");
	//连接根元素
	doc.LinkEndChild(pRootElement);


	//遍历所有查询结果
	for (unsigned int i = 0; i < m_CTQueryResults.size(); i++)
	{
		//创建概率元素
		TiXmlElement* pProbability = new TiXmlElement("Probability");

		//设置概率取值
		char sTemp[MAX_PATH];
		sprintf_s(sTemp, "%.6f", m_CTQueryResults[i]);
		pProbability->SetAttribute("PROBABILITY_VALUE", sTemp);


		//连接概率到概率列表
		pRootElement->LinkEndChild(pProbability);
	}

	//获取当前工作路径
	namespace fs = std::filesystem;
	fs::path sPath = fs::current_path() / "Data" / "CliqueTree_Output.xml";

	//保存XML文件
	doc.SaveFile(sPath.string().c_str());

	//释放内存
	doc.Clear();

	//自动打开文件
	ShellExecute(NULL, L"open", sPath.c_str(), NULL, NULL, SW_SHOWNORMAL);
}