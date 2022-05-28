/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CBNSumProduct_Read_Query.cpp
//功  能：		读取查询任务。包括查询节点、给定节点、节点删除顺序
//开发者：		高志强
//日  期：		2021年03月06日
//更  新：		2021年03月08日
//更  新：		2021年03月23日
//长  度：		180行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "ExactInference.h"							//应用程序类头文件
#include "CBNSumProduct.h"							//贝叶斯网络精确推理类头文件，采用和积变量消除法
#include "Helper.h"									//辅助函数头文件
#include "tinyxmliterator.h"

//声明外部变量
extern CExactInferenceApp theApp;


//名  称：		Read_Query()
//功  能：		读取查询任务。包括查询节点、给定节点、删除节点顺序
//参  数：		无
//返回值：		无
void CBNSumProduct::Read_Query()
{
	//获取当前工作路径
	CString sFileName = CString(theApp.m_sWorkPath);
	sFileName = sFileName + _T("\\Data");
	sFileName = sFileName + _T("\\BayesianNetwork_Query.xml");

	//搜索文件，如果文件不存在，则直接返回
	CFileFind findWenJian;								//文件名称
	//如果没有发现文件，则直接返回
	if (!findWenJian.FindFile(sFileName))
	{
		return;
	}

	//打开文件
	TiXmlDocument aDoc(MapCStringToString(sFileName).c_str());

	//检查打开文件是否成功
	if (!aDoc.LoadFile())
	{
		AfxMessageBox(_T("打开BayesianNetwork_Query.xml失败:"));
		return exit(0);
	}

	//获取根结点
	TiXmlElement* pRoot = aDoc.RootElement();
	for (TiXmlElement& pQuery : pRoot)
	{
		QUERY query;

		////////////////////////////////////////////////////////////////////////////////////////////
		//步骤1：获取边缘指针
		TiXmlElement* pMarginal = pQuery.FirstChildElement();
		//遍历所有查询变量
		std::transform(begin(pMarginal), end(pMarginal), std::back_inserter(query.QueryVariables),
			[](TiXmlElement& pVariable) { return GROUNDING_VARIABLE(
				GetAttributeI(pVariable, "ID"),
				GetAttributeI(pVariable, "VALUE")
			); });
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//步骤2：获取给定变量指针
		TiXmlElement* pGiven = pMarginal->NextSiblingElement();
		std::transform(begin(pGiven), end(pGiven), std::back_inserter(query.GivenVariables),
			[](TiXmlElement& pVariable) { return GROUNDING_VARIABLE(
				GetAttributeI(pVariable, "ID"),
				GetAttributeI(pVariable, "VALUE")
			); });

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//步骤3：获取删除变量顺序

		if (TiXmlElement* pEliminate = pGiven->NextSiblingElement(); pEliminate != NULL)
		{
			//获取删除变量ID列表
			if (string sTemp = GetAttribute(pEliminate, "IDs"); sTemp != "")
			{
				//转换为字符列表
				vector<string> IDs;
				Separate(sTemp, IDs);
				std::ranges::transform(IDs, std::back_inserter(query.EliminateVariables), stoi_);
			}
		}

		//添加到查询列表
		m_Queries.push_back(std::move(query));
	}//结束查询节点

	//释放文件所占内存
	aDoc.Clear();
}