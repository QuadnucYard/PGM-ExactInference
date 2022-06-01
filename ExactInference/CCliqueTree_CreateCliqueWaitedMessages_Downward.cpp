////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_CreateCliqueWaitedMessages_Downward.cpp
// 向下传递消息时，创建团的等待消息集合
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//向下传递消息时，创建团的等待消息集合
fidsetmap CCliqueTree::CreateCliqueWaitedMessages_Downward()
{
	fidsetmap WaitedMessages;

	//步骤1：遍历所有团，初始化向下传递消息时，团的等待消息集合为空
	//应该是找所有指向它的点
	for (const CT_NODE& node : m_CTNodes)
	{
		WaitedMessages.insert({node.nID, {}});
	}

	//步骤2：遍历向根团树的边，并建立等待消息的集合
	for (const fidpair& p : m_UpwardTree)
	{
		//添加到等待消息集合
		InsertToWaitedMessages(p.first, p.second, WaitedMessages);
	}
	return WaitedMessages;
}