/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CClique_Operator.cpp
//功  能：		重载操作符相关。主要是因子积。后来增加了因子除
//开发者：		高志强
//日  期：		2021年03月31日
//更  新：		2021年04月12日
//更  新：		2021年05月18日
//长  度：		50行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CClique.h"								//团类头文件


//名  称：		IsConsistentValueID()
//功  能：		检查团中两行的值ID是否兼容，用于判断乘积时能否合并
//参  数：		const FACTOR_ROW&, 
//				const FACTOR_ROW&, 
//				map<unsigned int, unsigned int>&
//返回值：		bool
bool CClique::IsConsistentValueID(const CLIQUE_ROW& FirstRow, const CLIQUE_ROW& SecondRow, map<unsigned int, unsigned int>& FirstToSeconds)
{
	//遍历所有相同变量位置的映射
	for (map<unsigned int, unsigned int>::iterator it = FirstToSeconds.begin(); it != FirstToSeconds.end(); it++)
	{
		//获取位置
		unsigned int nFirstPos = it->first;		//首位置
		unsigned int nSecondPos = it->second;	//尾位置

		//检查变量值的ID是否相等
		if (FirstRow.ValueIDs[nFirstPos] != SecondRow.ValueIDs[nSecondPos])
		{
			//返回假
			return false;
		}
	}

	//缺省返回真
	return true;
}

//重载因子积
CClique CClique::operator*(const CClique& second)
{
	//定义新的、待返回的因子团
	CClique clique;

	////////////////////////////////////////////////////////////////////////
	//注意：在因子积中要保留团ID。团是不变的，这和因子不同。因子是动态变化的
	clique.m_nCliqueID = m_nCliqueID;
	////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//步骤1：求两个团的交，即相同变量ID的集合		
	//定义相同变量ID，从第首团到第尾团位置的映射。例如第3个变量对应于第5个变量
	map<unsigned int, unsigned int> FirstToSeconds;

	//步骤1.1：遍历首团的变量ID
	for (unsigned int i = 0; i < m_VariableIDs.size(); i++)
	{
		//获取首变量ID
		unsigned int nFirstVariableID = m_VariableIDs[i];

		//遍历尾团的变量ID
		for (unsigned int j = 0; j < second.m_VariableIDs.size(); j++)
		{
			//获取尾变量ID
			unsigned int nSecondVariableID = second.m_VariableIDs[j];

			//检查两个变量ID是否相等
			if (nFirstVariableID == nSecondVariableID)
			{
				//添加到相同变量、从首团指向尾团的位置映射
				//注意：采用从位置到位置的映射，而不是从变量ID到变量ID的映射
				FirstToSeconds.insert(make_pair(i, j));
			}
		}
	}

	//步骤1.2：获取尾团中和首团相同变量的位置集合
	set<unsigned int> RedundantSeconds;
	for (map<unsigned int, unsigned int>::iterator it = FirstToSeconds.begin(); it != FirstToSeconds.end(); it++)
	{
		//添加到相同变量的位置集合
		RedundantSeconds.insert(it->second);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//步骤2：直接拼接
	//检查是否有相同变量ID
	if (FirstToSeconds.size() == 0)//情况一：两个团没有相同变量，则直接拼接
	{
		//步骤2.1：直接拼接变量值ID
		for (unsigned int i = 0; i < m_CliqueRows.size(); i++)
		{
			for (unsigned int j = 0; j < second.m_CliqueRows.size(); j++)
			{
				//定义新的团行
				CLIQUE_ROW clique_row;

				//添加变量值的ID集合
				clique_row.ValueIDs = m_CliqueRows[i].ValueIDs;//赋予首团值的序列
				//添加尾团值的序列
				for (unsigned int m = 0; m < second.m_CliqueRows[j].ValueIDs.size(); m++)
				{
					//添加尾团值的ID
					clique_row.ValueIDs.push_back(second.m_CliqueRows[j].ValueIDs[m]);
				}

				//计算团行的值。需要采用乘法
				clique_row.fValue = m_CliqueRows[i].fValue * second.m_CliqueRows[j].fValue;

				//将团行添加到团
				clique.m_CliqueRows.push_back(clique_row);
			}
		}

		//步骤2.2：拼接变量ID
		clique.m_VariableIDs = m_VariableIDs;//初始化为首团的变量ID序列
		//添加尾团的变量ID
		for (unsigned int i = 0; i < second.m_VariableIDs.size(); i++)
		{
			//添加尾团的变量ID
			clique.m_VariableIDs.push_back(second.m_VariableIDs[i]);
		}
	}
	////////////////////////////////////////////////////////////////////
	//步骤3：间接拼接
	else //情况二：两个团有相同变量，则间接拼接
	{
		//步骤3.1：间接拼接
		for (unsigned int i = 0; i < m_CliqueRows.size(); i++)
		{
			for (unsigned int j = 0; j < second.m_CliqueRows.size(); j++)
			{
				//检查对应的变量值的ID是否相等
				if (IsConsistentValueID(m_CliqueRows[i], second.m_CliqueRows[j], FirstToSeconds))
				{
					//定义因子行
					CLIQUE_ROW clique_row;
					clique_row.ValueIDs = m_CliqueRows[i].ValueIDs;//初始化团行的值ID序列
					//遍历尾团的值
					for (unsigned int m = 0; m < second.m_CliqueRows[j].ValueIDs.size(); m++)
					{
						//检查列是否在相同变量集合中
						if (!qy::ranges::includes(RedundantSeconds, m))
						{
							//添加尾团的列
							clique_row.ValueIDs.push_back(second.m_CliqueRows[j].ValueIDs[m]);
						}
					}

					//计算获取团行的值
					clique_row.fValue = m_CliqueRows[i].fValue * second.m_CliqueRows[j].fValue;

					//添加因子行到因子
					clique.m_CliqueRows.push_back(clique_row);
				}
			}
		}

		//步骤3.2：添加变量ID的列表
		clique.m_VariableIDs = m_VariableIDs;
		//遍历尾团
		for (unsigned int i = 0; i < second.m_VariableIDs.size(); i++)
		{
			//检查尾团变量ID的位置是否属于相同变量ID集合
			if (!qy::ranges::includes(RedundantSeconds, i))
			{
				//添加尾团的变量ID
				clique.m_VariableIDs.push_back(second.m_VariableIDs[i]);
			}
		}
	}

	//返回团
	return clique;
};

CClique CClique::operator/(const CClique& second)
{
	//定义新的、待返回的团
	CClique clique;

	///////////////////////////
	//注意：保持已有的变量集
	clique.m_VariableIDs = m_VariableIDs;
	///////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//步骤1：求两个团的交，即相同变量ID的集合		
	//定义相同变量ID，从第首因子到第尾因子位置的映射。例如第3个变量对应于第5个变量
	map<unsigned int, unsigned int> FirstToSeconds;

	//步骤1.1：遍历首因子的变量ID
	for (unsigned int i = 0; i < m_VariableIDs.size(); i++)
	{
		//获取首变量ID
		unsigned int nFirstVariableID = m_VariableIDs[i];

		//遍历尾因子的变量ID
		for (unsigned int j = 0; j < second.m_VariableIDs.size(); j++)
		{
			//获取尾变量ID
			unsigned int nSecondVariableID = second.m_VariableIDs[j];

			//检查两个变量ID是否相等
			if (nFirstVariableID == nSecondVariableID)
			{
				//添加到相同变量、从首因子指向尾因子的位置映射
				//注意：采用从位置到位置的映射，而不是从变量ID到变量ID的映射
				FirstToSeconds.insert(make_pair(i, j));
			}
		}
	}

	//步骤1.2：获取尾因子中和首因子相同变量的位置集合
	set<unsigned int> RedundantSeconds;
	for (map<unsigned int, unsigned int>::iterator it = FirstToSeconds.begin(); it != FirstToSeconds.end(); it++)
	{
		//添加到相同变量的位置集合
		RedundantSeconds.insert(it->second);
	}

	/////////////////////////////////////////////////////////////////////////////////
	//步骤2：因子除
	//说明：被除团的辖域一定包含除团的辖域
	for (unsigned int i = 0; i < m_CliqueRows.size(); i++)
	{
		for (unsigned int j = 0; j < second.m_CliqueRows.size(); j++)
		{
			//检查对应的变量值的ID是否相等
			if (IsConsistentValueID(m_CliqueRows[i], second.m_CliqueRows[j], FirstToSeconds))
			{
				//定义团行
				CLIQUE_ROW clique_row;

				//初始化团行的值ID序列
				clique_row.ValueIDs = m_CliqueRows[i].ValueIDs;
				//计算获取因子行的值
				clique_row.fValue = m_CliqueRows[i].fValue / second.m_CliqueRows[j].fValue;

				//添加团行到团
				clique.m_CliqueRows.push_back(clique_row);
			}
		}
	}

	//返回团
	return clique;
};