////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_CreateCliqueWaitedMessages.cpp
// 创建团的等待消息集合
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//创建团的等待消息集合
fidsetmap CCliqueTree::CreateCliqueWaitedMessages()
{
	fidsetmap WaitedMessages;
	////////////////////////////////////////////////////////////////////////////////
	//步骤1：遍历所有团，初始化团的等待消息集合为空
	for (const CT_NODE& node : m_CTNodes)
	{
		//添加到团的等待消息集合
		WaitedMessages.insert({node.nID, {}});
	}

	
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//步骤2：遍历向根团树的边，并建立等待消息的集合
	for (const fidpair& p : m_UpwardTree)
	{
		//添加到等待消息集合
		InsertToWaitedMessages(p.second, p.first, WaitedMessages);
	}
	return WaitedMessages;
}

//插入团的等待消息表
void CCliqueTree::InsertToWaitedMessages(fid_t nParentID, fid_t nCliqueID, fidsetmap& WaitedMessages)
{
	/*if (auto it = WaitedMessages.find(nParentID); it != WaitedMessages.end())
	{
		//添加团的等待消息集合
		it->second.insert(nCliqueID);
	}*/
	WaitedMessages[nParentID].insert(nCliqueID);
}