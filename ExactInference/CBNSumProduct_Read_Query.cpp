/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CBNSumProduct_Read_Query.cpp
//功  能：		读取查询任务。包括查询节点、给定节点、节点删除顺序
//开发者：		高志强
//日  期：		2021年03月06日
//更  新：		2021年03月08日
//更  新：		2021年03月23日
//长  度：		180行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ExactInference.h"
#include "CBNSumProduct.h"
#include "tinyxmliterator.h"

extern CExactInferenceApp theApp;

//读取查询任务。包括查询节点、给定节点、删除节点顺序
void CBNSumProduct::Read_Query()
{
	//获取当前工作路径
	const char* sFileName = strcat(theApp.m_sWorkPath, "\\Data\\BayesianNetwork_Query.xml");

	//搜索文件，如果文件不存在，则直接返回
	if (!CFileFind().FindFile(CString(sFileName))) return;

	//打开文件
	TiXmlDocument aDoc(sFileName);
	if (!aDoc.LoadFile())
	{
		AfxMessageBox(_T("打开BayesianNetwork_Query.xml失败:"));
		return exit(0);
	}

	//获取根结点
	TiXmlElement* pRoot = aDoc.RootElement();
	for (TiXmlElement& pQuery : pRoot)
	{
		QUERY query;

		//步骤1：获取边缘指针
		TiXmlElement* pMarginal = pQuery.FirstChildElement();
		std::transform(begin(pMarginal), end(pMarginal), std::back_inserter(query.QueryVariables),
			[](TiXmlElement& pVariable) { return GROUNDING_VARIABLE(
				GetAttributeI(pVariable, "ID"),
				GetAttributeI(pVariable, "VALUE")
			); });

		//步骤2：获取给定变量指针
		TiXmlElement* pGiven = pMarginal->NextSiblingElement();
		std::transform(begin(pGiven), end(pGiven), std::back_inserter(query.GivenVariables),
			[](TiXmlElement& pVariable) { return GROUNDING_VARIABLE(
				GetAttributeI(pVariable, "ID"),
				GetAttributeI(pVariable, "VALUE")
			); });

		//步骤3：获取删除变量顺序
		if (TiXmlElement* pEliminate = pGiven->NextSiblingElement(); pEliminate != NULL)
		{
			//获取删除变量ID列表
			if (std::string sTemp = GetAttribute(pEliminate, "IDs"); sTemp != "")
			{
				query.EliminateVariables = sTemp
					| qy::views::tokenize(std::regex("[\\s,;，；、]+"))
					| std::views::transform(stoi_)
					| qy::views::to<fidlist>;
			}
		}

		m_Queries.push_back(std::move(query));
	}

	aDoc.Clear();
}