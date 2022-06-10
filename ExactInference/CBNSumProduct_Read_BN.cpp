////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_Read_BN.cpp
// ��ȡ��Ҷ˹����ṹ�Ͳ���
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct_IO.h"

namespace pgm {

//��ȡ��Ҷ˹����ṹ�Ͳ���
BayesianNetwork CBNSumProductReader::Read_BN(const std::string& filename)
{
	namespace fs = std::filesystem;
	BayesianNetwork bn;

#ifndef USE_YAML

	fs::path sPath = fs::current_path() / "Data" / (filename + ".xml");
	if (!fs::exists(sPath)) {
		throw std::runtime_error("�ļ������ڣ�" + filename + ".xml");
	}

	TiXmlDocument aDoc(sPath.string().c_str());
	if (!aDoc.LoadFile())
	{
		throw std::runtime_error("���ļ�ʧ�ܣ�" + filename + ".xml");
	}

	//��ȡ�����
	TiXmlElement* pRoot = aDoc.RootElement();

	////
	//����1����ȡ�ڵ��
	TiXmlElement* pNodes = pRoot->FirstChildElement();

	//�������нڵ�
	for (const TiXmlElement& pNode : pNodes)
	{
		//��ȡ�ڵ�����
		BNNode bn_node;
		bn_node.nID = GetAttributeI(pNode, "ID");
		bn_node.sName = GetAttribute(pNode, "NAME");
		bn_node.sAbbr = GetAttribute(pNode, "ABBREVIATION");
		bn_node.nNumberOfValues = GetAttributeI(pNode, "NUMBER_OF_VALUES");
		bn_node.nNumberOfParents = GetAttributeI(pNode, "NUMBER_OF_PARENTS");

		//06 ���ڵ��б�
		if (bn_node.nNumberOfParents != 0)
		{
			std::string tmp = GetAttribute(pNode, "PARENT_IDS");
			bn_node.ParentIDs = tmp
				| qy::views::tokenize(std::regex("[\\s,;]+"))
				| std::views::transform(stoi_)
				| qy::views::to<fidlist>;
		}

		//07 CPT�еĸ���ֵ
		std::string tmp = GetAttribute(pNode, "CPT");
		bn_node.CPTRowValues = tmp
			| qy::views::tokenize(std::regex("[\\s,;]+"))
			| std::views::transform(stod_)
			| qy::views::to<fvallist>;

		bn.m_Nodes.push_back(bn_node);
	}

	////
	//����2����ȡ�߱�
	if (TiXmlElement* pEdges = pNodes->NextSiblingElement(); pEdges)
	{
		std::transform(begin(pEdges), end(pEdges), std::back_inserter(bn.m_Edges),
			[](TiXmlElement& pEdge) { return BNEdge(
				GetAttributeI(pEdge, "ID"),
				GetAttributeI(pEdge, "START_NODE_ID"),
				GetAttributeI(pEdge, "END_NODE_ID")
			); });
	}

	aDoc.Clear();

#else

	fs::path sPath = fs::current_path() / "Data" / (filename + ".yaml");
	YAML::Node doc = YAML::LoadFile(sPath.string());

	auto&& root = doc["BayesianNetwork"];
	for (auto&& node : root["variables"]) {
		BayesianNetwork::Node bn_node;
		bn.variables.emplace_back(
			node.first.as<fid_t>(),
			node.second["numValues"].as<size_t>(),
			node.second["name"].as<std::string>(""),
			node.second["abbr"].as<std::string>("")
		);
	}
	for (auto&& node : root["nodes"]) {
		bn.nodes.emplace_back(
			node.first.as<fid_t>(),
			node.second["parants"].as<fidlist>(fidlist {}),
			node.second["CPT"].as<fvallist>()
		);
	}

#endif // USE_YAML

	return bn;
}

}