////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_Read_Query.cpp
// 读取查询任务。包括查询节点、给定节点、节点删除顺序
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


//读取查询任务。包括查询节点、给定节点、删除节点顺序
void CBNSumProduct::Read_Query()
{
	namespace fs = std::filesystem;

#ifndef USE_YAML

	fs::path sPath = fs::current_path() / "Data" / "BayesianNetwork_Query.xml";
	if (!fs::exists(sPath)) return;

	//打开文件
	TiXmlDocument aDoc(sPath.string().c_str());
	if (!aDoc.LoadFile())
	{
		AfxMessageBox(_T("打开BayesianNetwork_Query.xml失败:"));
		return exit(0);
	}

	//获取根结点
	TiXmlElement* pRoot = aDoc.RootElement();
	for (TiXmlElement& pQuery : pRoot)
	{
		BNQuery query;

		//步骤1：获取边缘指针
		TiXmlElement* pMarginal = pQuery.FirstChildElement();
		std::transform(begin(pMarginal), end(pMarginal), std::back_inserter(query.QueryVariables),
			[](TiXmlElement& pVariable) { return GroundingVariable(
				GetAttributeI(pVariable, "ID"),
				GetAttributeI(pVariable, "VALUE")
			); });

		//步骤2：获取给定变量指针
		TiXmlElement* pGiven = pMarginal->NextSiblingElement();
		std::transform(begin(pGiven), end(pGiven), std::back_inserter(query.GivenVariables),
			[](TiXmlElement& pVariable) { return GroundingVariable(
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
					| qy::views::tokenize(std::regex("[\\s,;]+"))
					| std::views::transform(stoi_)
					| qy::views::to<fidlist>;
			}
		}

		m_Queries.push_back(std::move(query));
	}

	aDoc.Clear();

#else

	fs::path sPath = fs::current_path() / "Data" / "BayesianNetwork_Query.yaml";
	YAML::Node doc = YAML::LoadFile(sPath.string());

	for (auto q : doc["queries"]) {
		m_Queries.emplace_back(
			q["marginal"].as<fidmap>(fidmap {}) | std::views::transform(GroundingVariable::fromPair) | qy::views::to<GVarList>,
			q["given"].as<fidmap>(fidmap {}) | std::views::transform(GroundingVariable::fromPair) | qy::views::to<GVarList>,
			q["eliminate"].as<fidlist>(fidlist {})
		);
	}

#endif // USE_YAML

}