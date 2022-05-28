/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CBNSumProduct_Read_BN.cpp
//��  �ܣ�		��ȡ��Ҷ˹����ṹ�Ͳ���
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��01��
//��  �£�		2021��03��06��
//��  �£�		2021��03��08��
//��  �£�		2021��03��23��
//��  �ȣ�		170��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ExactInference.h"
#include "CBNSumProduct.h"
#include "Helper.h"
#include "tinyxmliterator.h"

//�����ⲿ����
extern CExactInferenceApp theApp;


//��  �ƣ�		Read_BN()
//��  �ܣ�		��ȡ��Ҷ˹����ṹ�Ͳ���
//��  ����		��
//����ֵ��		��
void CBNSumProduct::Read_BN()
{
	//��ȡ��ǰ����·��
	CString sFileName = CString(theApp.m_sWorkPath) + _T("\\Data\\BayesianNetwork.xml");

	//�����ļ�������ļ������ڣ���ֱ�ӷ���
	if (!CFileFind().FindFile(sFileName))
	{
		AfxMessageBox(_T("��Ҷ˹����ṹ�Ͳ����ļ�BayesianNetwork.xml������"));
		return;
	}

	//���ļ�
	USES_CONVERSION;
	TiXmlDocument aDoc(T2A(sFileName));

	//�����ļ��Ƿ�ɹ�
	if (!aDoc.LoadFile())
	{
		AfxMessageBox(_T("��BayesianNetwork_Part.xmlʧ��:"));
		return exit(0);
	}

	//��ȡ�����
	TiXmlElement* pRoot = aDoc.RootElement();

	////////////////////////////////////////////////////////////////////////////////////////////////
	//����1����ȡ�ڵ��
	TiXmlElement* pNodes = pRoot->FirstChildElement();

	//�������нڵ�
	for (const TiXmlElement& pNode : pNodes)
	{
		//��ȡ�ڵ�����
		BN_NODE bn_node;
		bn_node.nID = GetAttributeI(pNode, "ID");
		bn_node.sName = GetAttribute(pNode, "NAME");
		bn_node.sAbbreviation = GetAttribute(pNode, "ABBREVIATION");
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

	///////////////////////////////////////////////////////////////////////////////////////////////
	//����2����ȡ�߱�
	if (TiXmlElement* pEdges = pNodes->NextSiblingElement(); pEdges)
	{
		std::transform(begin(pEdges), end(pEdges), std::back_inserter(m_Edges),
			[](TiXmlElement& pEdge) { return BN_EDGE(
				GetAttributeI(pEdge, "ID"),
				GetAttributeI(pEdge, "START_NODE_ID"),
				GetAttributeI(pEdge, "END_NODE_ID")
			); });
	}

	//�ͷ��ļ���ռ�ڴ�
	aDoc.Clear();
}