////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_Read_CT.cpp
// 读取团树CliqueTree
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//读取团树
void CCliqueTree::Read_CT()
{
	namespace fs = std::filesystem;

#ifndef USE_YAML

	fs::path sPath = fs::current_path() / "Data" / "CliqueTree.xml";
	if (!fs::exists(sPath))
	{
		AfxMessageBox(_T("团树文件CliqueTree.xml不存在"));
		return;
	}

	TiXmlDocument aDoc(sPath.string().c_str());
	if (!aDoc.LoadFile())
	{
		AfxMessageBox(_T("打开CliqueTree.xml失败:"));
		return exit(0);
	}

	TiXmlElement* pCliqueTree = aDoc.RootElement();
	if (pCliqueTree != NULL)
	{
		m_nRootID = GetAttributeI(pCliqueTree, "ROOT_ID");
	} else
	{
		AfxMessageBox(_T("根节点CliqueTree不存在"));
		return exit(0);
	}

	//步骤1：获取变量表
	TiXmlElement* pVariables = pCliqueTree->FirstChildElement();

	for (const auto& pVariable : pVariables)
	{
		//添加到变量ID到名称的映射
		m_VariableID2Names.insert({GetAttributeI(pVariable, "ID"), GetAttribute(pVariable, "NAME")});
	}

	//步骤2：获取团表
	TiXmlElement* pCliques = pVariables->NextSiblingElement();
	for (auto& pClique : pCliques)
	{
		CTNode ct_node;
		ct_node.nID = GetAttributeI(pClique, "ID");

		std::string tmp = GetAttribute(pClique, "VARIABLE_IDS");
		ct_node.VariableIDs = tmp
			| qy::views::tokenize(std::regex("[\\s,;，；、]+"))
			| std::views::transform(stoi_)
			| qy::views::to<fidlist>;

		//遍历行
		for (auto& pRow : pClique)
		{
			CTFactorRow factor_row;
			factor_row.fValue = GetAttributeD(pRow, "VALUE");
			//遍历变量
			for (const auto& pVariable : pRow)
			{
				fid_t nVariableID = GetAttributeI(pVariable, "ID");
				fid_t nValueID = GetAttributeI(pVariable, "VALUE");
				factor_row.ValueIDs.push_back(nValueID);
			}
			ct_node.FactorRows.push_back(factor_row);
		}

		m_CTNodes.push_back(std::move(ct_node));
	}

	//步骤3：获取边表
	TiXmlElement* pEdges = pCliques->NextSiblingElement();
	for (auto& pEdge : pEdges)
	{
		fid_t nStartCliqueID = GetAttributeI(pEdge, "START_CLIQUE_ID");
		fid_t nEndCliqueID = GetAttributeI(pEdge, "END_CLIQUE_ID");
		//添加到边表。注意：采用双向映射
		m_CTEdges.insert({nStartCliqueID, nEndCliqueID});
		m_CTEdges.insert({nEndCliqueID, nStartCliqueID});
	}

	aDoc.Clear();

#else

	fs::path sPath = fs::current_path() / "Data" / "CliqueTree.yaml";
	YAML::Node doc = YAML::LoadFile(sPath.string());

	auto root = doc["CliqueTree"];
	m_nRootID = root["root"].as<fid_t>();
	fidmap numValuesMap;
	for (auto node : root["vars"]) {
		m_VariableID2Names[node.first.as<fid_t>()] = node.second["name"].as<std::string>();
		numValuesMap[node.first.as<fid_t>()] = node.second["numValues"].as<fid_t>();
	}

	for (auto node : root["cliques"]) {
		CTNode ct_node;
		ct_node.nID = node.first.as<fid_t>();
		ct_node.VariableIDs = node.second["vars"].as<fidlist>();

		// 下面构造所有值组合
		fidlist numValues; //按顺序每个变量的取值数
		std::ranges::transform(ct_node.VariableIDs, std::back_inserter(numValues),
			[&](fid_t i) { return numValuesMap[i]; });

		size_t n = numValues.size(), i = 0;
		fidlist a(n);
		do {
			ct_node.FactorRows.emplace_back(a, node.second["vals"][i++].as<fval_t>());
			// 从高位开始做加法
			++a[n - 1];
			for (size_t j = n - 1; j > 0 && a[j] == numValues[j]; j--) {
				a[j] = 0;
				++a[j - 1];
			}
		} while (a[0] != numValues[0]);

		m_CTNodes.push_back(std::move(ct_node));
	}

	for (auto node : root["edges"]) {
		m_CTEdges.insert({node[0].as<fid_t>(), node[1].as<fid_t>()});
		m_CTEdges.insert({node[1].as<fid_t>(), node[0].as<fid_t>()});
	}

#endif // USE_YAML

}