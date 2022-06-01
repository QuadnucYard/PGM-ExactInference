/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CFactorTree_Read_QueryCT.cpp
//功  能：		读取团树Clique的查询任务。包括边缘节点、给定节点的ID和值ID
//开发者：		高志强
//日  期：		2021年03月30日
//更  新：		2021年03月31日
//更  新：		2021年04月01日
//更  新：		2021年04月10日
//更  新：		2021年04月12日
//更  新：		2021年05月18日
//长  度：		150行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "ExactInference.h"							//应用程序类头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"									//辅助函数头文件


//声明外部变量
extern CExactInferenceApp theApp;


//名  称：		Read_QueryCT()
//功  能：		读取团树查询任务。包括查询节点、给定节点
//参  数：		无
//返回值：		无
void CCliqueTree::Read_QueryCT()
{
	//获取当前工作路径
	CString sFileName = CString(theApp.m_sWorkPath);
	sFileName = sFileName + _T("\\Data");
	sFileName = sFileName + _T("\\CliqueTree_Query.xml");


	//搜索文件，如果文件不存在，则直接返回
	CFileFind findWenJian;								//文件名称
	BOOL bWenJian = findWenJian.FindFile(sFileName);	//搜索文件是否存在
	//如果没有发现文件，则直接返回
	if (!bWenJian)
	{
		//直接返回
		return;
	}


	//打开文件
	TiXmlDocument aDoc(MapCStringToString(sFileName).c_str());

	//检查打开文件是否成功
	if (!aDoc.LoadFile())
	{
		//提示
		AfxMessageBox(_T("打开CliqueTree_Query.xml失败:"));

		//退出
		return exit(0);
	}

	//定义临时变量
	string sTemp;

	//获取根结点
	TiXmlElement *pQueries = aDoc.RootElement();
	TiXmlElement *pQuery = pQueries->FirstChildElement();
	while (pQuery != NULL)
	{
		//定义团树查询
		CT_QUERY ct_query;

		////////////////////////////////////////////////////////////////////////////////////////////
		//步骤1：获取边缘指针
		TiXmlElement* pMarginal = pQuery->FirstChildElement();
		//遍历所有边缘
		if (pMarginal != NULL)
		{
			//步骤1：获取变量指针
			TiXmlElement* pVariable = pMarginal->FirstChildElement();
			
			//遍历查询变量指针
			while (pVariable != NULL)
			{
				//定义实例化变量
				CT_GROUNDING_VARIABLE query_variable;

				//获取查询变量ID
				string sTemp = GetAttribute(pVariable, "ID");
				query_variable.nVariableID = TransformStringToInt(sTemp);

				//获取查询变量值ID
				sTemp = GetAttribute(pVariable, "VALUE");

				//设置是否给定值
				query_variable.nValueID = TransformStringToInt(sTemp);//获取节点值的ID

				//添加到查询变量表
				ct_query.MarginalVariables.push_back(query_variable);

				//更新查询变量指针
				pVariable = pVariable->NextSiblingElement();
			}
		}


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//步骤2：获取给定变量指针
		TiXmlElement* pGiven = pMarginal->NextSiblingElement();
		if (pGiven != NULL)
		{
			//步骤1：获取变量指针
			TiXmlElement* pVariable = pGiven->FirstChildElement();

			//遍历查询变量指针
			while (pVariable != NULL)
			{
				//定义实例化变量
				CT_GROUNDING_VARIABLE given_variable;

				//获取查询变量ID
				string sTemp = GetAttribute(pVariable, "ID");
				given_variable.nVariableID = TransformStringToInt(sTemp);

				//获取查询变量值ID
				sTemp = GetAttribute(pVariable, "VALUE");

				//设置是否给定值
				given_variable.nValueID = TransformStringToInt(sTemp);//获取节点值的ID

				//添加到查询变量表
				ct_query.GivenVariables.push_back(given_variable);

				//更新查询变量指针
				pVariable = pVariable->NextSiblingElement();
			}
		}


		//添加到查询列表
		m_CTQueries.push_back(ct_query);

		//更新查询指针
		pQuery = pQuery->NextSiblingElement();
	}//结束查询节点


	//释放文件所占内存
	aDoc.Clear();
}