////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_Read_CT.cpp
// ��ȡ����CliqueTree
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree_IO.h"

namespace pgm {

//��ȡ����
CliqueTree CCliqueTreeReader::Read_CT(const std::string& filename)
{
	namespace fs = std::filesystem;
	CliqueTree ct;

#ifndef USE_YAML

	fs::path sPath = fs::current_path() / "Data" / (filename + ".xml");
	if (!fs::exists(sPath))
	{
		throw std::runtime_error("�ļ������ڣ�" + filename + ".xml");
	}

	TiXmlDocument aDoc(sPath.string().c_str());
	if (!aDoc.LoadFile())
	{
		throw std::runtime_error("���ļ�ʧ�ܣ�" + filename + ".xml");
	}

	TiXmlElement* pCliqueTree = aDoc.RootElement();
	ct.m_nRootID = GetAttributeI(pCliqueTree, "ROOT_ID");

	//����1����ȡ������
	TiXmlElement* pVariables = pCliqueTree->FirstChildElement();

	for (const auto& pVariable : pVariables)
	{
		//��ӵ�����ID�����Ƶ�ӳ��
		ct.m_VariableID2Names.insert({GetAttributeI(pVariable, "ID"), GetAttribute(pVariable, "NAME")});
	}

	//����2����ȡ�ű�
	TiXmlElement* pCliques = pVariables->NextSiblingElement();
	for (auto& pClique : pCliques)
	{
		CTNode ct_node;
		ct_node.nID = GetAttributeI(pClique, "ID");

		std::string tmp = GetAttribute(pClique, "VARIABLE_IDS");
		ct_node.VariableIDs = tmp
			| qy::views::tokenize(std::regex("[\\s,;]+"))
			| std::views::transform(stoi_)
			| qy::views::to<fidlist>;

		//������
		for (auto& pRow : pClique)
		{
			CTFactorRow factor_row;
			factor_row.fValue = GetAttributeD(pRow, "VALUE");
			//��������
			for (const auto& pVariable : pRow)
			{
				fid_t nVariableID = GetAttributeI(pVariable, "ID");
				fid_t nValueID = GetAttributeI(pVariable, "VALUE");
				factor_row.ValueIDs.push_back(nValueID);
			}
			ct_node.FactorRows.push_back(factor_row);
		}

		ct.m_CTNodes.push_back(std::move(ct_node));
	}

	//����3����ȡ�߱�
	TiXmlElement* pEdges = pCliques->NextSiblingElement();
	for (auto& pEdge : pEdges)
	{
		fid_t nStartCliqueID = GetAttributeI(pEdge, "START_CLIQUE_ID");
		fid_t nEndCliqueID = GetAttributeI(pEdge, "END_CLIQUE_ID");
		//��ӵ��߱�ע�⣺����˫��ӳ��
		ct.m_CTEdges.insert({nStartCliqueID, nEndCliqueID});
		ct.m_CTEdges.insert({nEndCliqueID, nStartCliqueID});
	}

	aDoc.Clear();

#else

	fs::path sPath = fs::current_path() / "Data" / (filename + ".yaml");
	YAML::Node doc = YAML::LoadFile(sPath.string());

	auto&& root = doc["CliqueTree"];
	for (auto&& node : root["variables"]) {
		ct.variables.emplace_back(
			node.first.as<fid_t>(),
			node.second["numValues"].as<size_t>(),
			node.second["name"].as<std::string>(""),
			node.second["abbr"].as<std::string>("")
		);
	}
	for (auto&& node : root["cliques"]) {
		ct.nodes.emplace_back(
			//node.first.as<fid_t>(),
			node.second["vars"].as<fidlist>(fidlist {}),
			node.second["vals"].as<fvallist>()
		);
	}
	for (auto&& node : root["edges"]) {
		ct.addEdge(node[0].as<fid_t>(), node[1].as<fid_t>());
	}
	ct.build(root["root"].as<fid_t>());

#endif // USE_YAML

	return ct;
}

}