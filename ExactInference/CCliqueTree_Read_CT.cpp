/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CCliqueTree_Read_CT.cpp
//功  能：		读取团树CliqueTree
//开发者：		高志强
//日  期：		2021年03月30日
//更  新：		2021年04月12日
//更  新：		2021年05月18日
//长  度：		220行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "ExactInference.h"							//应用程序类头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"									//辅助函数头文件


//声明外部变量
extern CExactInferenceApp theApp;


//名  称：		Read_CT()
//功  能：		读取团树
//参  数：		无
//返回值：		无
void CCliqueTree::Read_CT()
{
	//获取当前工作路径
	CString sFileName = CString(theApp.m_sWorkPath);
	sFileName = sFileName + _T("\\Data");
	sFileName = sFileName + _T("\\CliqueTree.xml");


	//搜索文件，如果文件不存在，则直接返回
	CFileFind findWenJian;								//文件名称
	BOOL bWenJian = findWenJian.FindFile(sFileName);	//搜索文件是否存在
	//如果没有发现文件，则直接返回
	if (!bWenJian)
	{
		//提示
		AfxMessageBox(_T("团树文件CliqueTree.xml不存在"));

		//返回
		return;
	}


	//打开文件
	TiXmlDocument aDoc(MapCStringToString(sFileName).c_str());

	//检查打开文件是否成功
	if (!aDoc.LoadFile())
	{
		//提示
		AfxMessageBox(_T("打开CliqueTree.xml失败:"));

		//退出
		return exit(0);
	}

	//获取团树结点
	TiXmlElement *pCliqueTree = aDoc.RootElement();
	//定义临时变量
	string sTemp;

	//检查是否合法
	if (pCliqueTree != NULL)
	{
		//定义临时变量
		sTemp = GetAttribute(pCliqueTree, "ROOT_ID");
		//获取团树的根团ID
		m_nRootID = TransformStringToInt(sTemp);
	}
	else
	{
		//提示
		AfxMessageBox(_T("根节点CliqueTree不存在"));

		//退出
		return exit(0);
	}
	

	////////////////////////////////////////////////////////////////////////////////////////////////
	//步骤1：获取变量表
	TiXmlElement* pVariables = pCliqueTree->FirstChildElement();
	if (pVariables != NULL)
	{
		//获取变量
		TiXmlElement* pVariable = pVariables->FirstChildElement();

		//遍历所有变量
		while (pVariable != NULL)
		{
			//获取变量ID
			sTemp = GetAttribute(pVariable, "ID");
			unsigned int nVariableID = TransformStringToInt(sTemp);
			//获取变量名称
			string sVariableName = GetAttribute(pVariable, "NAME");

			//添加到变量ID到名称的映射
			m_VariableID2Names.insert(make_pair(nVariableID, sVariableName));
			
			//更新变量指针
			pVariable = pVariable->NextSiblingElement();
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	//步骤2：获取团表
	TiXmlElement* pCliques = pVariables->NextSiblingElement();
	if (pCliques != NULL)
	{
		//获取团
		TiXmlElement* pClique = pCliques->FirstChildElement();

		//遍历所有团
		while (pClique != NULL)
		{
			//定义团树节点
			CT_NODE ct_node;

			//定义临时变量
			sTemp = GetAttribute(pClique, "ID");
			//获取团的ID
			ct_node.nID = TransformStringToInt(sTemp);

			//获取团的变量ID列表
			sTemp = GetAttribute(pClique, "VARIABLE_IDS");
			vector<string> IDs;
			//获取双亲ID列表
			Separate(sTemp, IDs);
			//转化为无符号整数
			for (unsigned int i = 0; i < IDs.size(); i++)
			{
				//获取整数
				unsigned int nID = TransformStringToInt(IDs[i]);
				//加入变量ID列表
				ct_node.VariableIDs.push_back(nID);
			}

			//获取行
			TiXmlElement* pRow = pClique->FirstChildElement();
			//遍历行
			while (pRow != NULL)
			{
				//定义因子行
				CT_FACTOR_ROW factor_row;

				//获取因子行值
				sTemp = GetAttribute(pRow, "VALUE");
				factor_row.fValue = TransformStringToDouble(sTemp);

				//获取变量
				TiXmlElement* pVariable = pRow->FirstChildElement();
				//遍历变量
				while (pVariable != NULL)
				{
					//获取变量ID和变量值
					sTemp = GetAttribute(pVariable, "ID");
					unsigned int nVariableID = TransformStringToInt(sTemp);
					sTemp = GetAttribute(pVariable, "VALUE");
					unsigned int nValueID = TransformStringToInt(sTemp);

					//添加到实例化变量表
					factor_row.ValueIDs.push_back(nValueID);

					//更新变量指针
					pVariable = pVariable->NextSiblingElement();
				}

				//添加到因子行表
				ct_node.FactorRows.push_back(factor_row);

				//更新行指针
				pRow = pRow->NextSiblingElement();
			}

			//添加到节点表
			m_CTNodes.push_back(ct_node);

			//更新团指针
			pClique = pClique->NextSiblingElement();
		}
	}//END IF pClique!=NULL


	///////////////////////////////////////////////////////////////////////////////////////////////
	//步骤3：获取边表
	TiXmlElement* pEdges = pCliques->NextSiblingElement();
	if (pEdges != NULL)
	{
		//获取边
		TiXmlElement* pEdge = pEdges->FirstChildElement();

		//检查是否为空
		while (pEdge != NULL)
		{			
			//01 边的起点ID
			sTemp = GetAttribute(pEdge, "START_CLIQUE_ID");
			unsigned int nStartCliqueID = TransformStringToInt(sTemp);
			//02 边的终点ID
			sTemp = GetAttribute(pEdge, "END_CLIQUE_ID");
			unsigned int nEndCliqueID = TransformStringToInt(sTemp);

			//添加到边表。注意：采用双向映射
			m_CTEdges.insert(make_pair(nStartCliqueID,nEndCliqueID));
			//双向多映射
			m_CTEdges.insert(make_pair(nEndCliqueID, nStartCliqueID));

			//更新边指针
			pEdge = pEdge->NextSiblingElement();
		}
	}


	//释放文件所占内存
	aDoc.Clear();
}