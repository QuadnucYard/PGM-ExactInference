/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CFactor_SumOutVariable.cpp
//功  能：		根据给定变量，对因子求和
//开发者：		高志强
//日  期：		2021年03月13日
//更  新：		2021年03月23日
//更  新：		2021年03月29日
//长  度：		150行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CFactor.h"								//因子类头文件
#include "Helper.h"									//辅助函数头文件
#include "stl_utils.h"
#include <algorithm>

//名  称：		SumOutVariable()
//功  能：		根据给定变量，对因子求和
//参  数：		unsigned int
//返回值：		无
void CFactor::SumOutVariable(fid_t nVariableID)
{
	//检查是否找到变量ID
	if (size_t nRemovePos = qy::index_of(m_VariableIDs, nVariableID); nRemovePos != -1) //找到变量ID，需要进行求和化简
	{
		/////////////////////////////////////////////////////////////////////
		//步骤1：化简变量ID的列表
		//删除nRemovePos项
		m_VariableIDs.erase(m_VariableIDs.begin() + nRemovePos);

		///////////////////////////////////////////////////////////////////////
		//步骤2：化简变量值的ID列表
		//删除行中冗余的变量值: i行的nRemovePos项
		for (FACTOR_ROW& t : m_FactorRows)
			t.ValueIDs.erase(t.ValueIDs.begin() + nRemovePos);

		//////////////////////////////////////////////////////////////////
		//步骤3：对因子中相应的行求和
		//定义新的因子行的列表
		std::vector<FACTOR_ROW> FactorRows;
		while (m_FactorRows.size() > 0)
		{
			//获取首行
			FACTOR_ROW first_row = m_FactorRows[0];

			//将因子值累加到首行
			MergeIntoFirstRow(first_row);

			//添加到因子行的列表
			FactorRows.push_back(first_row);
		}

		//需要换回因子行的列表
		m_FactorRows = FactorRows;
	}
}

//名  称：		MergeIntoFirstRow()
//功  能：		累积因子值到首行
//参  数：		FACTOR_ROW&
//返回值：		无
void CFactor::MergeIntoFirstRow(FACTOR_ROW& first_row)
{
	//遍历所有因子行，累加并删除变量值ID的列表相等的项
	auto it = m_FactorRows.begin();
	it = m_FactorRows.erase(it); //删除首行
	while (it != m_FactorRows.end())
	{
		if (first_row.ValueIDs == it->ValueIDs)
		{
			first_row.fValue += it->fValue;
			it = m_FactorRows.erase(it);
		} else
		{
			it++;
		}
	}
}