////////////////////////////////////////////////////////////////////////////////
// CClique_Operator.cpp
// 重载操作符相关。主要是因子积。后来增加了因子除
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CClique.h"


//检查团中两行的值ID是否兼容，用于判断乘积时能否合并
bool CClique::IsConsistentValueID(const CLIQUE_ROW& FirstRow, const CLIQUE_ROW& SecondRow, const fidmap& FirstToSeconds) const
{
	return std::ranges::all_of(FirstToSeconds,
		[&](auto t) { return FirstRow[t.first] == SecondRow[t.second]; });
}

//重载因子积
CClique CClique::operator*(const CClique& second) const
{
	CClique clique;
	//注意：在因子积中要保留团ID。团是不变的，这和因子不同。因子是动态变化的
	clique.m_nCliqueID = m_nCliqueID;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//步骤1：求两个团的交，即相同变量ID的集合		
	//定义相同变量ID，从第首团到第尾团位置的映射。例如第3个变量对应于第5个变量
	fidmap FirstToSeconds;

	//步骤1.1：遍历首团的变量ID
	for (size_t i = 0; i < m_VariableIDs.size(); i++)
	{
		for (fid_t j = 0; j < second.m_VariableIDs.size(); j++)
		{
			if (m_VariableIDs[i] == second.m_VariableIDs[j])
			{
				//添加到相同变量、从首因子指向尾因子的位置映射
				//注意：采用从位置到位置的映射，而不是从变量ID到变量ID的映射
				FirstToSeconds.insert(std::make_pair(i, j));
			}
		}
	}

	//步骤1.2：获取尾团中和首团相同变量的位置集合
	fidset RedundantSeconds(std::views::values(FirstToSeconds) | qy::views::to<fidset>);

	//间接拼接
	for (const CLIQUE_ROW& r1 : m_CliqueRows)
	{
		for (const CLIQUE_ROW& r2 : second.m_CliqueRows)
		{
			if (IsConsistentValueID(r1, r2, FirstToSeconds))
			{
				clique.m_CliqueRows.emplace_back(
					qy::concat(r1.ValueIDs,
						qy::range(r2.ValueIDs)
						| std::views::filter([&](int i) { return !RedundantSeconds.contains(i); })
						| std::views::transform([&](int i) { return r2.ValueIDs[i]; })
						| qy::views::to<fidlist>
					),
					r1.fValue * r2.fValue
				);
			}
		}
	}

	//步骤3.2：添加变量ID的列表
	clique.m_VariableIDs = qy::concat(m_VariableIDs,
		qy::range(second.m_VariableIDs)
		| std::views::filter([&](int i) { return !RedundantSeconds.contains(i); })
		| std::views::transform([&](int i) { return second.m_VariableIDs[i]; })
		| qy::views::to<fidlist>
	);

	return clique;
};

CClique CClique::operator/(const CClique& second) const
{
	CClique clique;
	clique.m_VariableIDs = m_VariableIDs;

	//步骤1：求两个团的交，即相同变量ID的集合		
	//定义相同变量ID，从第首因子到第尾因子位置的映射。例如第3个变量对应于第5个变量
	fidmap FirstToSeconds;
	//步骤1.1：遍历首因子的变量ID
	for (size_t i = 0; i < m_VariableIDs.size(); i++)
	{
		for (fid_t j = 0; j < second.m_VariableIDs.size(); j++)
		{
			if (m_VariableIDs[i] == second.m_VariableIDs[j])
			{
				FirstToSeconds.insert(std::make_pair(i, j));
			}
		}
	}

	//步骤1.2：获取尾因子中和首因子相同变量的位置集合
	fidset RedundantSeconds(std::views::values(FirstToSeconds) | qy::views::to<fidset>);

	//步骤2：因子除
	//说明：被除团的辖域一定包含除团的辖域
	for (const CLIQUE_ROW& r1 : m_CliqueRows)
	{
		for (const CLIQUE_ROW& r2 : second.m_CliqueRows)
		{
			if (IsConsistentValueID(r1, r2, FirstToSeconds))
			{
				clique.m_CliqueRows.emplace_back(r1.ValueIDs, r1.fValue / r2.fValue);
			}
		}
	}

	return clique;
};