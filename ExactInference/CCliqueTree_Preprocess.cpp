/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CClique_Preprocess.cpp
//功  能：		预处理团树
//开发者：		高志强
//日  期：		2021年03月31日
//更  新：		2021年05月18日
//长  度：		90行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		Preprocess()
//功  能：		预处理团树
//参  数：		无
//返回值：		无
void CCliqueTree::Preprocess()
{
	//遍历BN中的所有节点
	for (unsigned int i = 0; i < m_CTNodes.size(); i++)
	{
		//定义因子
		CClique clique;

		//////////////////////////////////////////////////////////////
		//步骤1：初始化团。设置团ID
		clique.SetCliqueID(m_CTNodes[i].nID);
		//设置团的变量ID列表
		clique.SetCliqueVariableIDs(m_CTNodes[i].VariableIDs);

		//建立变量ID到团ID的多映射
		for (unsigned int j = 0; j < m_CTNodes[i].VariableIDs.size(); j++)
		{
			//添加到多映射
			unsigned int nVariableID = m_CTNodes[i].VariableIDs[j];
			unsigned int nCliqueID = m_CTNodes[i].nID;

			m_VariableID2CliqueIDs.insert(make_pair(nVariableID,nCliqueID));
		}


		//////////////////////////////////////////////////////////////
		//步骤2：初始化团。设置团行
		for (unsigned int j = 0; j < m_CTNodes[i].FactorRows.size(); j++)
		{
			//获取值ID的表。此处似乎有问题。
			vector<unsigned int> ValueIDs = m_CTNodes[i].FactorRows[j].ValueIDs;
			//获取因子值
			double fValue = m_CTNodes[i].FactorRows[j].fValue;

			//设置团行
			clique.SetCliqueRow(ValueIDs, fValue);
		}

		//建立团的ID到位置的映射
		unsigned int nPos = m_Cliques.size();
		unsigned int nCliqueID = clique.GetID();
		m_CliqueID2Poses.insert(make_pair(nCliqueID, nPos));

		//添加到团表
		m_Cliques.push_back(clique);
	}
}

//名  称：		GetCliquePosByID()
//功  能：		获取团的位置
//参  数：		unsigned int
//返回值：		unsigned int
unsigned int CCliqueTree::GetCliquePosByID(unsigned int nCliqueID)
{
	//查找团的ID到位置的映射
	map<unsigned int, unsigned int>::iterator it = m_CliqueID2Poses.find(nCliqueID);

	//如果找到
	if (it != m_CliqueID2Poses.end())
	{
		//返回位置
		return it->second;
	}
	else
	{
		//出现异常，返回0
		return 0;
	}
}