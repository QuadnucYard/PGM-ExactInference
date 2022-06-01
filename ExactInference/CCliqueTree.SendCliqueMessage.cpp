////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_SendCliqueMessage.cpp
// 发送团消息
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//发送团消息
void CCliqueTree::SendCliqueMessage(fid_t nID)
{
	//找到双亲节点
	fid_t nParentID;

	//如果找到双亲,则通过参数获取双亲ID
	if (IsThereParentID(nID, nParentID))
	{
		//找到两个团相交的变量ID集合
		fidset CommonVariableIDs = FindCommonVariableIDs(nID, nParentID);

		//获取团的位置
		fid_t nPos = GetCliquePosByID(nID);

		//获取需要求和掉的变量ID集合
		fidset EliminateVariableIDs;
		//求集合的差。团的变量集合-割集变量集合=求和掉的变量集合
		std::ranges::set_difference(m_Cliques[nPos].GetVariableIDs(), CommonVariableIDs,
			std::inserter(EliminateVariableIDs, EliminateVariableIDs.end()));

		//定义割集  从子指向父
		SEP_SET sep_set(nID, nParentID, m_Cliques[nPos]);
		
		//遍历所有消除变量
		for (fid_t s: EliminateVariableIDs)
		{
			sep_set.clique.SumOutVariable(s);
		}

		m_SEPSets.push_back(sep_set);
	}
}

//求两个团的变量ID交集
fidset CCliqueTree::FindCommonVariableIDs(fid_t nID1, fid_t nID2)
{
	fidset Intersections;
	std::ranges::set_intersection(m_Cliques[nID1].GetVariableIDs(), m_Cliques[nID2].GetVariableIDs(),
		std::inserter(Intersections, Intersections.end()));
	return Intersections;
}

//查找双亲是否存在，如果存在，则返回双亲ID
//				团是否存在双亲。如果有的话，则通过参数获取双亲ID
bool CCliqueTree::IsThereParentID(fid_t nID, fid_t& nParentID)
{
	//在向根团的树中查找
	if (auto it = m_UpwardTree.find(nID); it != m_UpwardTree.end())
	{
		//赋值、获取双亲ID
		nParentID = it->second;
		return true;
	}
	else
	{
		return false;
	}
}
