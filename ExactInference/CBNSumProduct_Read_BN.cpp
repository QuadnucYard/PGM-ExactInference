////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_Read_BN.cpp
// ��ȡ��Ҷ˹����ṹ�Ͳ���
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"
#include "tinyxmliterator.h"
#include <filesystem>


//��ȡ��Ҷ˹����ṹ�Ͳ���
void CBNSumProduct::Read_BN()
{
	namespace fs = std::filesystem;
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
				| qy::views::tokenize(std::regex("[\\s,;������]+"))
				| std::views::transform(stoi_)
				| qy::views::to<fidlist>;
		}

		//07 CPT�еĸ���ֵ
		std::string tmp = GetAttribute(pNode, "CPT");
		bn_node.CPTRowValues = tmp
			| qy::views::tokenize(std::regex("[\\s,;������]+"))
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
}