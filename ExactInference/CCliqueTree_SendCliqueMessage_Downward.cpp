////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_SendCliqueMessage_Downward.cpp
// 向下发送团消息
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//向下发送团消息
void CCliqueTree::SendCliqueMessage_Downward(fid_t nID, fid_t nChildID)
{	
	//找到相交的变量ID集合
	fidset CommonVariableIDs = FindCommonVariableIDs(nID, nChildID);
	//nID(父)传给nChildID
	
	// 下面是nID传给nParentID

		//获取团的位置
	fid_t nPos = GetCliquePosByID(nID);

	//获取需要求和掉的变量ID集合
	fidset EliminateVariableIDs;
	//求集合的差。团的变量集合-割集变量集合=求和掉的变量集合
	std::ranges::set_difference(m_Cliques[nPos].GetVariableIDs(), CommonVariableIDs,
		std::inserter(EliminateVariableIDs, EliminateVariableIDs.end()));

	//定义割集  从父指向子
	SEP_SET sep_set(nID, nChildID, m_Cliques[nPos], true);

	//遍历所有消除变量
	for (fid_t s : EliminateVariableIDs)
	{
		sep_set.clique.SumOutVariable(s);
	}

	m_SEPSets.push_back(sep_set);
}