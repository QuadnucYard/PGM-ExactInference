/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CClique_SumOutVariable.cpp
//功  能：		根据给定变量，对团求和
//开发者：		高志强
//日  期：		2021年03月31日
//更  新：		2021年04月12日
//更  新：		2021年05月18日
//长  度：		150行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CClique.h"								//团类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		SumOutVariable()
//功  能：		根据给定变量，对团求和
//参  数：		unsigned int
//返回值：		无
void CClique::SumOutVariable(unsigned int nVariableID)
{
	//检查是否找到变量ID
	if (size_t nRemovePos = qy::ranges::index_of(m_VariableIDs, nVariableID); nRemovePos != -1)//找到变量ID，需要进行求和化简
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
		for (unsigned int i = 0; i < m_CliqueRows.size(); i++)
		{
			//删除行中冗余的变量值
			vector<unsigned int>::iterator it = m_CliqueRows[i].ValueIDs.begin();
			//定义并初始化当前位置
			unsigned int nCurrPos = 0;

			//循环判断，并删除
			while (it != m_CliqueRows[i].ValueIDs.end())
			{
				//检查是否到指定位置
				if (nCurrPos == nRemovePos)
				{
					//删除变量
					it = m_CliqueRows[i].ValueIDs.erase(it);

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
		//步骤3：对团中相应的行求和
		//定义新的团行的列表
		vector<CLIQUE_ROW> CliqueRows;
		while (m_CliqueRows.size()>0)
		{
			//获取首行
			CLIQUE_ROW first_row = m_CliqueRows[0];

			//将因子值累加到首行
			MergeIntoFirstRow(first_row);

			//添加到团行的列表
			CliqueRows.push_back(first_row);
		}

		//需要换回团行的列表
		m_CliqueRows = CliqueRows;
	}
}

//名  称：		MergeIntoFirstRow()
//功  能：		累积因子值到首行
//参  数：		FACTOR_ROW&
//返回值：		无
void CClique::MergeIntoFirstRow(CLIQUE_ROW& first_row)
{
	//遍历所有团行
	vector<CLIQUE_ROW>::iterator it = m_CliqueRows.begin();

	//删除首行
	it = m_CliqueRows.erase(it);

	//检查是否结束
	while (it != m_CliqueRows.end())
	{
		//检查变量值ID的列表是否相等
		if (first_row.ValueIDs == it->ValueIDs)
		{
			//累加因子值
			first_row.fValue += it->fValue;

			//删除、并更新迭代器
			it = m_CliqueRows.erase(it);
		}
		else
		{
			//更新迭代器
			it++;
		}
	}
}