////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_IsReady.cpp
// ������Ƿ����
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//������Ƿ����
//				���Ƿ������
bool CCliqueTree::IsCliqueReady(fid_t nCliqueID, const fidsetmap& WaitedMessages) const
{
	if (auto it = WaitedMessages.find(nCliqueID); it!= WaitedMessages.end()) {
		const fidset& msg = it->second;
		return msg.empty() || IsAllSEPSetExisted(nCliqueID, msg);
	}
	return true;
}

//����Ƿ����и���Ѿ�����
bool CCliqueTree::IsAllSEPSetExisted(fid_t nID, const fidset& WaitedMessages) const
{
	return std::ranges::all_of(WaitedMessages,
		[=](fid_t nStartID) { return IsAllSEPSetExisted_Helper(nStartID, nID); });
}

//����Ƿ����и���Ѿ����ڵĸ�������
bool CCliqueTree::IsAllSEPSetExisted_Helper(fid_t nStartID, fid_t nID) const
{
	return std::ranges::any_of(m_SEPSets,
		[=](const SEP_SET& s) { return nStartID == s.nStartID && nID == s.nEndID; });
}