/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CFactor_Init.cpp
//功  能：		初始化。包括设置变量ID列表、因子行
//开发者：		高志强
//日  期：		2021年03月12日
//更  新：		2021年03月23日
//更  新：		2021年03月29日
//长  度：		50行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CFactor.h"								//因子类头文件


//名  称：		SetVariableIDs()
//功  能：		设置变量ID列表
//参  数：		vector<unsigned int>&
//返回值：		无
void CFactor::SetFactorVariableIDs(const fidlist& VariableIDs)
{
	//初始化因子中变量ID的列表
	m_VariableIDs = VariableIDs;
}

void CFactor::SetFactorVariableIDs(fidlist&& VariableIDs)
{
	//初始化因子中变量ID的列表
	m_VariableIDs = VariableIDs;
}

//名  称：		SetFactorRow()
//功  能：		设置因子行
//参  数：		vector<unsigned int>&,double&
//返回值：		无
void CFactor::SetFactorRow(const fidlist& ValueIDs, fval_t fRowValue)
{
	//添加到因子行的列表
	m_FactorRows.emplace_back(ValueIDs, fRowValue);
}

void CFactor::SetFactorRow(fidlist&& ValueIDs, fval_t fRowValue)
{
	//添加到因子行的列表
	m_FactorRows.emplace_back(ValueIDs, fRowValue);
}