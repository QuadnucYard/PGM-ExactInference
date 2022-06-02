////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_Read_BN.cpp
// 读取贝叶斯网络结构和参数
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


//读取贝叶斯网络结构和参数
void CBNSumProduct::Read_BN()
{
	namespace fs = std::filesystem;

#ifndef USE_YAML

	fs::path sPath = fs::current_path() / "Data" / "BayesianNetwork.xml";
	if (!fs::exists(sPath)) {
		AfxMessageBox(_T("贝叶斯网络结构和参数文件BayesianNetwork.xml不存在"));
		return;
	}

	//打开文件
	TiXmlDocument aDoc(sPath.string().c_str());
	if (!aDoc.LoadFile())
	{
		AfxMessageBox(_T("打开BayesianNetwork_Part.xml失败:"));
		return exit(0);
	}

	//获取根结点
	TiXmlElement* pRoot = aDoc.RootElement();

	////
	//步骤1：获取节点表
	TiXmlElement* pNodes = pRoot->FirstChildElement();

	//遍历所有节点
	for (const TiXmlElement& pNode : pNodes)
	{
		//获取节点属性
		BNNode bn_node;
		bn_node.nID = GetAttributeI(pNode, "ID");
		bn_node.sName = GetAttribute(pNode, "NAME");
		bn_node.sAbbr = GetAttribute(pNode, "ABBREVIATION");
		bn_node.nNumberOfValues = GetAttributeI(pNode, "NUMBER_OF_VALUES");
		bn_node.nNumberOfParents = GetAttributeI(pNode, "NUMBER_OF_PARENTS");

		//06 父节点列表
		if (bn_node.nNumberOfParents != 0)
		{
			std::string tmp = GetAttribute(pNode, "PARENT_IDS");
			bn_node.ParentIDs = tmp
				| qy::views::tokenize(std::regex("[\\s,;]+"))
				| std::views::transform(stoi_)
				| qy::views::to<fidlist>;
		}

		//07 CPT中的概率值
		std::string tmp = GetAttribute(pNode, "CPT");
		bn_node.CPTRowValues = tmp
			| qy::views::tokenize(std::regex("[\\s,;]+"))
			| std::views::transform(stod_)
			| qy::views::to<fvallist>;

		m_Nodes.push_back(bn_node);
	}

	////
	//步骤2：获取边表
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