////////////////////////////////////////////////////////////////////////////////
// CClique_Preprocess.cpp
// 预处理团树
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//预处理团树
void CCliqueTree::Preprocess()
{
	//遍历BN中的所有节点
	for (const CT_NODE& node : m_CTNodes)
	{
		CClique clique;
		clique.SetCliqueID(node.nID);
		clique.SetCliqueVariableIDs(node.VariableIDs);

		//建立变量ID到团ID的多映射
		for (fid_t var : node.VariableIDs)
		{
			m_VariableID2CliqueIDs.insert({var, node.nID});
		}

		//步骤2：初始化团。设置团行
		for (const CT_FACTOR_ROW& row : node.FactorRows)
		{
			clique.SetCliqueRow(row.ValueIDs, row.fValue);
		}

		//建立团的ID到位置的映射
		m_CliqueID2Poses.insert({clique.GetID(), m_Cliques.size()});
		m_Cliques.push_back(clique);
	}
}

//获取团的位置
const CClique& CCliqueTree::GetCliquePosByID(fid_t nCliqueID) const
{
	return m_Cliques.at(m_CliqueID2Poses.at(nCliqueID));
}

CClique& CCliqueTree::GetCliquePosByID(fid_t nCliqueID)
{
	return m_Cliques.at(m_CliqueID2Poses.at(nCliqueID));
}