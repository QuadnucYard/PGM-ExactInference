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


//名  称：		SumOutVariable()
//功  能：		根据给定变量，对因子求和
//参  数：		unsigned int
//返回值：		无
void CFactor::SumOutVariable(unsigned int nVariableID)
{
	//查找变量ID是否在因子中
	unsigned int nRemovePos = 0;
	//调用辅助函数
	bool bFind = IsINTInVector(nVariableID, m_VariableIDs, nRemovePos);
	
	
	//检查是否找到变量ID
	if (bFind)//找到变量ID，需要进行求和化简
	{
		/////////////////////////////////////////////////////////////////////
		//步骤1：化简变量ID的列表
		vector<unsigned int>::iterator it = m_VariableIDs.begin();
		//定义并初始化当前位置
		unsigned int nCurrPos = 0;

		//循环判断，并删除
		while (it != m_VariableIDs.end())
		{
			//检查是否到指定位置
			if (nCurrPos == nRemovePos)
			{
				//删除节点
				it = m_VariableIDs.erase(it);

				//终止循环
				break;
			}
			else
			{
				//更新位置
				nCurrPos++;

				//更新迭代器
				it++;
			}
		}


		///////////////////////////////////////////////////////////////////////
		//步骤2：化简变量值的ID列表
		for (unsigned int i = 0; i < m_FactorRows.size(); i++)
		{
			//删除行中冗余的变量值
			vector<unsigned int>::iterator it = m_FactorRows[i].ValueIDs.begin();
			//定义并初始化当前位置
			unsigned int nCurrPos = 0;

			//循环判断，并删除
			while (it != m_FactorRows[i].ValueIDs.end())
			{
				//检查是否到指定位置
				if (nCurrPos == nRemovePos)
				{
					//删除变量
					it = m_FactorRows[i].ValueIDs.erase(it);

					//终止循环
					break;
				}
				else
				{
					//更新位置
					nCurrPos++;

					//更新迭代器
					it++;
				}
			}
		}
	
		//////////////////////////////////////////////////////////////////
		//步骤3：对因子中相应的行求和
		//定义新的因子行的列表
		vector<FACTOR_ROW> FactorRows;
		while (m_FactorRows.size()>0)
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
	//遍历所有因子行
	vector<FACTOR_ROW>::iterator it = m_FactorRows.begin();

	//删除首行
	it = m_FactorRows.erase(it);

	//检查是否结束
	while (it != m_FactorRows.end())
	{
		//检查变量值ID的列表是否相等
		if (first_row.ValueIDs == it->ValueIDs)
		{
			//累加因子值
			first_row.fValue += it->fValue;

			//删除、并更新迭代器
			it = m_FactorRows.erase(it);
		}
		else
		{
			//更新迭代器
			it++;
		}
	}
}