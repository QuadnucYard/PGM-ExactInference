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

	const CClique& c = m_Cliques[GetCliquePosByID(nID)];
	//获取需要求和掉的变量ID集合
	fidlist EliminateVariableIDs = qy::set_difference<fidlist>(c.GetVariableIDs(), CommonVariableIDs);

	//定义割集  从父指向子
	SEP_SET sep_set(nID, nChildID, c, true);

	//遍历所有消除变量
	for (fid_t s : EliminateVariableIDs)
	{
		sep_set.clique.SumOutVariable(s);
	}

	m_SEPSets.push_back(sep_set);
}