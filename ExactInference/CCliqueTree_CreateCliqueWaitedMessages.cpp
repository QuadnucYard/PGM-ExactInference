////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_CreateCliqueWaitedMessages.cpp
// 创建团的等待消息集合
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//创建团的等待消息集合
fidsetmap CCliqueTree::CreateCliqueWaitedMessages() const
{
	fidsetmap WaitedMessages;

	//步骤1：遍历所有团，初始化团的等待消息集合为空
	for (const CTNode& node : m_CTNodes)
	{
		WaitedMessages.insert({node.nID, {}});
	}

	//步骤2：遍历向根团树的边，并建立等待消息的集合
	for (const fidpair& p : m_UpwardTree)
	{
		//添加到等待消息集合
		WaitedMessages[p.second].insert(p.first);
	}
	return WaitedMessages;
}
