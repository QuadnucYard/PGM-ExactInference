/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CClique_Query.cpp
//功  能：		查询团中的特定概率。例如团中包括A、B、C三个变量，只想获取A、B、C特定取值的概率等。需要给定变量ID列表和变量值的ID列表
//				包括3个辅助的查询函数
//开发者：		高志强
//日  期：		2021年03月31日
//更  新：		2021年04月12日
//更  新：		2021年05月18日
//长  度：		120行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CClique.h"								//团类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		Query()
//功  能：		查询特定值
//参  数：		vector<unsigned int>&,vector<unsigned int>&
//返回值：		double
double CClique::Query(vector<unsigned int>& VariableIDs, vector<unsigned int>& ValueIDs)
{
	//定义位置集合
	vector<unsigned int> Positions;

	//遍历查询的变量ID
	for (unsigned int i = 0; i < VariableIDs.size(); i++)
	{
		//遍历因子的变量ID
		for (unsigned int j = 0; j < m_VariableIDs.size(); j++)
		{
			//检查变量ID是否相同
			if (VariableIDs[i] == m_VariableIDs[j])
			{
				//添加到位置集合
				Positions.push_back(j);
			}
		}
	}


	//初始化返回的概率值
	double fProb = 0.0f;

	//遍历团行，求和
	for (unsigned int i = 0; i < m_CliqueRows.size(); i++)
	{
		//定义团行
		CLIQUE_ROW factor_row = m_CliqueRows[i];

		//检查位置和值是否正确
		bool bMatch = true;

		//遍历所有位置
		for (unsigned int j = 0; j < Positions.size(); j++)
		{
			//获取位置
			unsigned int nPos = Positions[j];		//获取位置
			unsigned int nValue = ValueIDs[j];	//获取变量值的ID
			//如果不相等，则更新匹配结果
			if (factor_row.ValueIDs[nPos] != nValue)
			{
				//更新匹配结果。这里似乎可以终止循环
				bMatch = false;
			}
		}

		//检查该行是否匹配。如果匹配的话，则需要累加概率值
		if (bMatch == true)
		{
			//累计概率值
			fProb += factor_row.fValue;
		}
	}

	//返回概率
	return fProb;
}

//名  称：		GetCliqueVariableIDs()
//功  能：		获取变量ID列表
//参  数：		无
//返回值：		unsigned int
vector<unsigned int> CClique::GetCliqueVariableIDs()
{
	//返回变量ID列表
	return m_VariableIDs;
}

//名  称：		GetVariableIDs()
//功  能：		获取变量ID集合
//参  数：		无
//返回值：		unsigned int
set <unsigned int> CClique::GetVariableIDs()
{
	set<unsigned int> VariableIDs;

	for (unsigned int i = 0; i < m_VariableIDs.size(); i++)
	{
		VariableIDs.insert(m_VariableIDs[i]);
	}
	
	//返回变量ID集合
	return VariableIDs;
}

//名  称：		GetID()
//功  能：		获取团的ID
//参  数：		无
//返回值：		unsigned int
unsigned int CClique::GetID()
{
	//返回团的ID
	return m_nCliqueID;
}