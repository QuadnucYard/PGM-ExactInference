/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CFactor_Operator.cpp
//功  能：		重载操作符相关。主要是因子积
//开发者：		高志强
//日  期：		2021年03月12日
//更  新：		2021年03月13日
//更  新：		2021年03月23日
//更  新：		2021年03月29日
//长  度：		50行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CFactor.h"								//因子类头文件
#include "Helper.h"									//辅助函数头文件
#include <algorithm>

//名  称：		IsConsistentValueID()
//功  能：		检查因子中两行的值ID是否兼容，用于判断乘积时能否合并
//参  数：		const FACTOR_ROW&, 
//				const FACTOR_ROW&, 
//				map<unsigned int, unsigned int>&
//返回值：		bool
bool CFactor::IsConsistentValueID(const FACTOR_ROW& FirstRow, const FACTOR_ROW& SecondRow, const fidmap& FirstToSeconds) const
{
	// 检查对应位置id相等
	return std::all_of(FirstToSeconds.begin(), FirstToSeconds.end(),
		[&](auto t) { return FirstRow[t.first] == SecondRow[t.second]; });
}

CFactor CFactor::operator*(const CFactor& second) const
{
	//定义新的、待返回的因子
	CFactor factor;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//步骤1：求两个因子的交，即相同变量ID的集合		
	//定义相同变量ID，从第首因子到第尾因子位置的映射。例如第3个变量对应于第5个变量
	fidmap FirstToSeconds;

	//步骤1.1：遍历首因子的变量ID
	for (size_t i = 0; i < m_VariableIDs.size(); i++)
	{
		//获取首变量ID
		fid_t nFirstVariableID = m_VariableIDs[i];

		//遍历尾因子的变量ID
		for (fid_t j = 0; j < second.m_VariableIDs.size(); j++)
		{
			//获取尾变量ID
			fid_t nSecondVariableID = second.m_VariableIDs[j];

			//检查两个变量ID是否相等
			if (nFirstVariableID == nSecondVariableID)
			{
				//添加到相同变量、从首因子指向尾因子的位置映射
				//注意：采用从位置到位置的映射，而不是从变量ID到变量ID的映射
				FirstToSeconds.insert(std::make_pair(i, j));
			}
		}
	}

	//步骤1.2：获取尾因子中和首因子相同变量的位置集合
	//fidset RedundantSeconds(qy::values_begin(FirstToSeconds), qy::values_end(FirstToSeconds));
	fidset RedundantSeconds(std::views::values(FirstToSeconds) | qy::views::to<fidset>);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//步骤2：直接拼接
	//检查是否有相同变量ID
	if (FirstToSeconds.size() == 0)//情况一：两个因子没有相同变量，则直接拼接
	{
		//步骤2.1：直接拼接变量值ID
		for (auto& r1 : m_FactorRows)
		{
			for (auto& r2 : second.m_FactorRows)
			{
				//定义新的因子行
				FACTOR_ROW factor_row(r1.ValueIDs, r1.fValue * r2.fValue); //计算因子行的值。需要采用惩罚

				//添加尾因子值的序列
				factor_row.ValueIDs.insert(factor_row.ValueIDs.end(), r2.ValueIDs.begin(), r2.ValueIDs.end());

				//将因子行添加到因子
				factor.m_FactorRows.push_back(std::move(factor_row));
			}
		}

		//步骤2.2：拼接变量ID
		factor.m_VariableIDs = m_VariableIDs;//初始化为首因子的变量ID序列
		//添加尾因子的变量ID
		factor.m_VariableIDs.insert(factor.m_VariableIDs.end(), second.m_VariableIDs.begin(), second.m_VariableIDs.end());
	}
	////////////////////////////////////////////////////////////////////
	//步骤3：间接拼接
	else //情况二：两个因子有相同变量，则间接拼接
	{
		//步骤3.1：间接拼接
		for (auto& r1 : m_FactorRows)
		{
			for (auto& r2 : second.m_FactorRows)
			{
				//检查对应的变量值的ID是否相等
				if (IsConsistentValueID(r1, r2, FirstToSeconds))
				{
					//定义因子行
					FACTOR_ROW factor_row(r1.ValueIDs, r1.fValue * r2.fValue);

					//遍历尾因子的值
					//添加不在相同变量集合中尾因子的列
					for (size_t m = 0; m < r2.ValueIDs.size(); m++)
					{
						//检查列是否在相同变量集合中
						if (!qy::includes(RedundantSeconds, m))
						{
							//添加尾因子的列
							factor_row.ValueIDs.push_back(r2.ValueIDs[m]);
						}
					}

					//添加因子行到因子
					factor.m_FactorRows.push_back(std::move(factor_row));
				}
			}
		}

		//步骤3.2：添加变量ID的列表
		factor.m_VariableIDs = m_VariableIDs;
		//遍历尾因子
		for (size_t i = 0; i < second.m_VariableIDs.size(); i++)
		{
			//检查尾因子变量ID的位置是否属于相同变量ID集合
			if (!qy::includes(RedundantSeconds, i))
			{
				//添加尾因子的变量ID
				factor.m_VariableIDs.push_back(second.m_VariableIDs[i]);
			}
		}
	}

	//返回因子
	return factor;
};