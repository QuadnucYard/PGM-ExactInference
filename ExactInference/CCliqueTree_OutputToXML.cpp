/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CClique_OutputToXML.cpp
//功  能：		输出查询结果到XML文件
//开发者：		高志强
//日  期：		2021年04月01日
//更  新：		2021年05月18日
//长  度：		70行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "ExactInference.h"							//应用程序类头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "tinyxml.h"								//TinyXML头文件
#include "Helper.h"									//辅助函数头文件


//声明外部变量，以获取当前工作路径
extern CExactInferenceApp theApp;


//名  称：		OutputToXML()
//功  能：		输出查询结果到XML文件
//参  数：		无
//返回值：		无
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
	CString sFileName = theApp.m_sWorkPath;
	sFileName = sFileName + _T("\\Data");
	sFileName = sFileName + _T("\\CliqueTree_Output.xml");

	//保存XML文件
	doc.SaveFile((MapCStringToString(sFileName)).c_str());

	//释放内存
	doc.Clear();

	//自动打开文件
	ShellExecute(NULL, _T("open"), sFileName, NULL, NULL, SW_SHOWNORMAL);
}