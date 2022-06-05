////////////////////////////////////////////////////////////////////////////////
// CFactorTree_Read_QueryCT.cpp
// 读取团树Clique的查询任务。包括边缘节点、给定节点的ID和值ID
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree_IO.h"


//读取团树查询任务。包括查询节点、给定节点
CCliqueTree::QueryList CCliqueTreeReader::Read_Query(const std::string& filename)
{
	namespace fs = std::filesystem;
	CCliqueTree::QueryList queries;

#ifndef USE_YAML

	fs::path sPath = fs::current_path() / "Data" / (filename + ".xml");
	if (!fs::exists(sPath))
	{
		throw std::runtime_error("文件不存在：" + filename + ".xml");
	}

	TiXmlDocument aDoc(sPath.string().c_str());
	if (!aDoc.LoadFile())
	{
		throw std::runtime_error("打开文件失败：" + filename + ".xml");
	}

	//获取根结点
	TiXmlElement* pQueries = aDoc.RootElement();
	for (auto& pQuery : pQueries)
	{
		CCliqueTree::CTQuery ct_query;

		//步骤1：获取边缘指针
		TiXmlElement* pMarginal = pQuery.FirstChildElement();
		//遍历所有边缘
		for (auto& pVariable : pMarginal)
		{
			ct_query.MarginalVariables.emplace_back(
				GetAttributeI(pVariable, "ID"),
				GetAttributeI(pVariable, "VALUE")
			);
		}

		//步骤2：获取给定变量指针
		TiXmlElement* pGiven = pMarginal->NextSiblingElement();
		//遍历查询变量
		for (auto& pVariable : pGiven)
		{
			ct_query.GivenVariables.emplace_back(
				GetAttributeI(pVariable, "ID"),
				GetAttributeI(pVariable, "VALUE")
			);
		}

		queries.push_back(std::move(ct_query));
	}

	aDoc.Clear();


#else

	fs::path sPath = fs::current_path() / "Data" / (filename + ".yaml");
	YAML::Node doc = YAML::LoadFile(sPath.string());

	for (auto q : doc["queries"]) {
		queries.emplace_back(
			q["marginal"].as<fidmap>(fidmap {}) | std::views::transform(CCliqueTree::GroundingVariable::fromPair) | qy::views::to<CCliqueTree::GVarList>,
			q["given"].as<fidmap>(fidmap {}) | std::views::transform(CCliqueTree::GroundingVariable::fromPair) | qy::views::to<CCliqueTree::GVarList>
		);
	}

#endif // USE_YAML

	return queries;
}