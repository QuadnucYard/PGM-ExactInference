////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_Read_CT.cpp
// 读取团树CliqueTree
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ExactInference.h"
#include "CCliqueTree.h"


//声明外部变量
extern CExactInferenceApp theApp;


//读取团树
void CCliqueTree::Read_CT()
{
	//获取当前工作路径
	namespace fs = std::filesystem;
	fs::path sPath = fs::current_path() / "Data" / "CliqueTree.xml";
	if (!fs::exists(sPath))
	{
		AfxMessageBox(_T("团树文件CliqueTree.xml不存在"));
		return;
	}

	TiXmlDocument aDoc(sPath.string().c_str());
	if (!aDoc.LoadFile())
	{
		AfxMessageBox(_T("打开CliqueTree.xml失败:"));
		return exit(0);
	}

	TiXmlElement *pCliqueTree = aDoc.RootElement();
	string sTemp;

	if (pCliqueTree != NULL)
	{
		m_nRootID = GetAttributeI(pCliqueTree, "ROOT_ID");
	}
	else
	{
		AfxMessageBox(_T("根节点CliqueTree不存在"));
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
			unsigned int nVariableID = GetAttributeI(pVariable, "ID");
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

			//获取团的ID
			ct_node.nID = GetAttributeI(pClique, "ID");

			//获取团的变量ID列表
			sTemp = GetAttribute(pClique, "VARIABLE_IDS");
			vector<string> IDs;
			//获取双亲ID列表
			Separate(sTemp, IDs);
			//转化为无符号整数
			for (unsigned int i = 0; i < IDs.size(); i++)
			{
				//获取整数
				unsigned int nID = stoi_(IDs[i]);
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
				factor_row.fValue = stod_(sTemp);

				//获取变量
				TiXmlElement* pVariable = pRow->FirstChildElement();
				//遍历变量
				while (pVariable != NULL)
				{
					//获取变量ID和变量值
					sTemp = GetAttribute(pVariable, "ID");
					unsigned int nVariableID = stoi_(sTemp);
					sTemp = GetAttribute(pVariable, "VALUE");
					unsigned int nValueID = stoi_(sTemp);

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
			unsigned int nStartCliqueID = stoi_(sTemp);
			//02 边的终点ID
			sTemp = GetAttribute(pEdge, "END_CLIQUE_ID");
			unsigned int nEndCliqueID = stoi_(sTemp);

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