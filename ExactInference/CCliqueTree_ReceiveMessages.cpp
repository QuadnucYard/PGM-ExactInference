////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_ReceiveMessages.cpp
// 接收消息
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//接收消息
void CCliqueTree::ReceiveMessages(fid_t nCliqueID, const fidsetmap& CliqueWaitedMessages)
{
	//获取等待消息的集合
	if (auto it = CliqueWaitedMessages.find(nCliqueID); it != CliqueWaitedMessages.end())
	{
		//遍历所有消息源
		for (fid_t nStartID : it->second)
		{
			//获取团的位置
			CClique& c = GetCliquePosByID(nCliqueID);
			//通过因子积、更新所在位置的团
			c = c * GetSEPSet(nStartID, nCliqueID).clique;
		}
	}
}

//获取割集
//割集。也是团
const SEP_SET& CCliqueTree::GetSEPSet(fid_t nStartID, fid_t nCliqueID) const
{
	return *std::ranges::find_if(m_SEPSets,
		[=](const SEP_SET& s) { return s.nStartID == nStartID && s.nEndID == nCliqueID; });
}