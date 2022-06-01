/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CCliqueTree_IsReady.cpp
//功  能：		检查团是否就绪
//开发者：		高志强
//日  期：		2021年04月01日
//更  新：		2021年04月03日
//更  新：		2021年05月18日
//长  度：		110行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		IsCliqueReady()
//功  能：		检查团是否就绪
//参  数：		unsigned int,map<unsigned int, set<unsigned int>>&
//				团ID、等待的消息集合
//返回值：		bool
//				团是否就绪？
bool CCliqueTree::IsCliqueReady(fid_t nCliqueID, const fidsetmap& WaitedMessages) const
{
	const fidset& msg = WaitedMessages.at(nCliqueID);
	return msg.empty() || IsAllSEPSetExisted(nCliqueID, msg);
}

//名  称：		IsAllSEPSetExisted()
//功  能：		检查是否所有割集都已经存在
//参  数：		unsigned int,set<unsigned int>&
//				团ID、等待的消息集合
//返回值：		bool
//				是否所需的割集都已经存在？
bool CCliqueTree::IsAllSEPSetExisted(fid_t nID, const fidset& WaitedMessages) const
{
	return std::ranges::all_of(WaitedMessages,
		[=](fid_t nStartID) { return IsAllSEPSetExisted_Helper(nStartID, nID); });
}

//名  称：		IsAllSEPSetExisted_Helper()
//功  能：		检查是否所有割集都已经存在的辅助函数
//参  数：		unsigned int,unsigned int
//				起点团ID、终点团ID
//返回值：		bool
//				是否割集存在？
bool CCliqueTree::IsAllSEPSetExisted_Helper(fid_t nStartID, fid_t nID) const
{
	return std::ranges::any_of(m_SEPSets,
		[=](const SEP_SET& s) { return nStartID == s.nStartID && nID == s.nEndID; });
}