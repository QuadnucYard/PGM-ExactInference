////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_FindReadyClique.cpp
// 查找一个就绪的团
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//查找一个就绪的团
//return:	就绪团的ID
fid_t CCliqueTree::FindReadyClique(const fidsetmap& CliqueWaitedMessages, const fidset& VisitedIDs) const
{
	//遍历所有团
	for (const CClique& clique : m_Cliques)
	{
		fid_t nCliqueID = clique.GetID();

		//获取团等待消息的集合
		if (auto it = CliqueWaitedMessages.find(nCliqueID); it != CliqueWaitedMessages.end())
		{
			//检查等待消息的集合是否为空
			if (!VisitedIDs.contains(nCliqueID)) {
				if (it->second.empty() || IsAllSEPSetExisted(nCliqueID, it->second)) {
					return nCliqueID;
				}
			}
		}
	}
	//没有找到就绪的团、提示出错。实际上不会出现这种情况
	return -1;
}