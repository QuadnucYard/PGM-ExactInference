////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_IsReady.cpp
// 检查团是否就绪
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//检查团是否就绪
//				团是否就绪？
bool CCliqueTree::IsCliqueReady(fid_t nCliqueID, const fidsetmap& WaitedMessages) const
{
	if (auto it = WaitedMessages.find(nCliqueID); it!= WaitedMessages.end()) {
		const fidset& msg = it->second;
		return msg.empty() || IsAllSEPSetExisted(nCliqueID, msg);
	}
	return true;
}

//检查是否所有割集都已经存在
bool CCliqueTree::IsAllSEPSetExisted(fid_t nID, const fidset& WaitedMessages) const
{
	return std::ranges::all_of(WaitedMessages,
		[=](fid_t nStartID) { return IsAllSEPSetExisted_Helper(nStartID, nID); });
}

//检查是否所有割集都已经存在的辅助函数
bool CCliqueTree::IsAllSEPSetExisted_Helper(fid_t nStartID, fid_t nID) const
{
	return std::ranges::any_of(m_SEPSets,
		[=](const SEP_SET& s) { return nStartID == s.nStartID && nID == s.nEndID; });
}