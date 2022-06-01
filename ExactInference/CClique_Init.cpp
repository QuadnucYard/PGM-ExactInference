/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CClique_Init.cpp
//功  能：		初始化。包括设置变量ID列表、团行
//开发者：		高志强
//日  期：		2021年03月31日
//更  新：		2021年04月12日
//更  新：		2021年05月18日
//长  度：		60行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CClique.h"								//团类头文件


//名  称：		SetCliqueID()
//功  能：		设置团ID
//参  数：		unsigned int&
//返回值：		无
void CClique::SetCliqueID(unsigned int& nCliqueID)
{
	//设置团ID
	m_nCliqueID = nCliqueID;
}

//名  称：		SetVariableIDs()
//功  能：		设置变量ID列表
//参  数：		vector<unsigned int>&
//返回值：		无
void CClique::SetCliqueVariableIDs(vector<unsigned int>& VariableIDs)
{
	//初始化团中变量ID的列表
	m_VariableIDs = VariableIDs;
}

//名  称：		SetCliqueRow()
//功  能：		设置团行
//参  数：		vector<unsigned int>&,double&
//返回值：		无
void CClique::SetCliqueRow(vector<unsigned int>& ValueIDs, double& fRowValue)
{
	//定义团行
	CLIQUE_ROW clique_row;

	//设置值ID的列表
	clique_row.ValueIDs = ValueIDs;
	//设置因子行的值
	clique_row.fValue = fRowValue;

	//添加到团行的列表
	m_CliqueRows.push_back(clique_row);
}