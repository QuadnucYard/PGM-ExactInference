////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_Read_BN.cpp
// ��ȡ��Ҷ˹����ṹ�Ͳ���
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


//��ȡ��Ҷ˹����ṹ�Ͳ���
void CBNSumProduct::Read_BN()
{
	namespace fs = std::filesystem;

#ifndef USE_YAML

	fs::path sPath = fs::current_path() / "Data" / "BayesianNetwork.xml";
	if (!fs::exists(sPath)) {
		AfxMessageBox(_T("��Ҷ˹����ṹ�Ͳ����ļ�BayesianNetwork.xml������"));
		return;
	}

	//���ļ�
	TiXmlDocument aDoc(sPath.string().c_str());
	if (!aDoc.LoadFile())
	{
		AfxMessageBox(_T("��BayesianNetwork_Part.xmlʧ��:"));
		return exit(0);
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

		m_Nodes.push_back(bn_node);
	}

	////
	//����2����ȡ�߱�
	if (TiXmlElement* pEdges = pNodes->NextSiblingElement(); pEdges)
	{
		std::transform(begin(pEdges), end(pEdges), std::back_inserter(m_Edges),
			[](TiXmlElement& pEdge) { return BNEdge(
				GetAttributeI(pEdge, "ID"),
				GetAttributeI(pEdge, "START_NODE_ID"),
				GetAttributeI(pEdge, "END_NODE_ID")
			); });
	}

	aDoc.Clear();

#else

	fs::path sPath = fs::current_path() / "Data" / "BayesianNetwork.yaml";
	YAML::Node doc = YAML::LoadFile(sPath.string());

	auto root = doc["BayesianNetwork"];
	for (auto node : root["nodes"]) {
		BNNode bn_node;
		bn_node.nID = node.first.as<fid_t>();
		bn_node.sName = node.second["name"].as<std::string>("");
		bn_node.sAbbr = node.second["abbr"].as<std::string>("");
		bn_node.nNumberOfValues = node.second["numValues"].as<size_t>();
		bn_node.ParentIDs = node.second["parants"].as<fidlist>(fidlist {});
		bn_node.CPTRowValues = node.second["CPT"].as<fvallist>();
		m_Nodes.push_back(std::move(bn_node));
	}

	for (auto edge : root["edges"]) {
		m_Edges.emplace_back(
			edge.first.as<fid_t>(),
			edge.second["start"].as<fid_t>(),
			edge.second["end"].as<fid_t>()
		);
	}

#endif // USE_YAML

}