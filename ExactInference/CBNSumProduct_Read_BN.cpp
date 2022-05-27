/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CBNSumProduct_Read_BN.cpp
//功  能：		读取贝叶斯网络结构和参数
//开发者：		高志强
//日  期：		2021年03月01日
//更  新：		2021年03月06日
//更  新：		2021年03月08日
//更  新：		2021年03月23日
//长  度：		170行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ExactInference.h"
#include "CBNSumProduct.h"
#include "Helper.h"
#include "tinyxmliterator.h"

//声明外部变量
extern CExactInferenceApp theApp;


//名  称：		Read_BN()
//功  能：		读取贝叶斯网络结构和参数
//参  数：		无
//返回值：		无
void CBNSumProduct::Read_BN()
{
	//获取当前工作路径
	CString sFileName = CString(theApp.m_sWorkPath) + _T("\\Data\\BayesianNetwork.xml");

	//搜索文件，如果文件不存在，则直接返回
	if (!CFileFind().FindFile(sFileName))
	{
		AfxMessageBox(_T("贝叶斯网络结构和参数文件BayesianNetwork.xml不存在"));
		return;
	}

	//打开文件
	TiXmlDocument aDoc(MapCStringToString(sFileName).c_str());

	//检查打开文件是否成功
	if (!aDoc.LoadFile())
	{
		AfxMessageBox(_T("打开BayesianNetwork_Part.xml失败:"));
		return exit(0);
	}

	//获取根结点
	TiXmlElement* pRoot = aDoc.RootElement();

	////////////////////////////////////////////////////////////////////////////////////////////////
	//步骤1：获取节点表
	TiXmlElement* pNodes = pRoot->FirstChildElement();

	//遍历所有节点
	for (const TiXmlElement& pNode : pNodes)
	{
		//获取节点属性
		BN_NODE bn_node;
		bn_node.nID = GetAttributeI(pNode, "ID");
		bn_node.sName = GetAttribute(pNode, "NAME");
		bn_node.sAbbreviation = GetAttribute(pNode, "ABBREVIATION");
		bn_node.nNumberOfValues = GetAttributeI(pNode, "NUMBER_OF_VALUES");
		bn_node.nNumberOfParents = GetAttributeI(pNode, "NUMBER_OF_PARENTS");

		//06 父节点列表
		if (bn_node.nNumberOfParents != 0)
		{
			vector<string> IDs;
			//获取双亲ID列表
			Separate(GetAttribute(pNode, "PARENT_IDS"), IDs);
			//转化为无符号整数
			std::ranges::transform(IDs, std::back_inserter(bn_node.ParentIDs), stoi_);
		}

		//07 CPT中的概率值
		vector<string> Probabilities;
		//切分
		Separate(GetAttribute(pNode, "CPT"), Probabilities);
		//转化为双精度数
		std::ranges::transform(Probabilities, std::back_inserter(bn_node.CPTRowValues), stod_);
		m_Nodes.push_back(bn_node);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//步骤2：获取边表
	if (TiXmlElement* pEdges = pNodes->NextSiblingElement(); pEdges)
	{
		std::transform(begin(pEdges), end(pEdges), std::back_inserter(m_Edges),
			[](TiXmlElement& pEdge) { return BN_EDGE(
				GetAttributeI(pEdge, "ID"),
				GetAttributeI(pEdge, "START_NODE_ID"),
				GetAttributeI(pEdge, "END_NODE_ID")
			); });
	}

	//释放文件所占内存
	aDoc.Clear();
}