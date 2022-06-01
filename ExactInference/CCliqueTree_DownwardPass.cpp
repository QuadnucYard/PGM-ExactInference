////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_DownwardPass.cpp
// 由根团向下传递消息
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//由根团向下传递消息
void CCliqueTree::DownwardPass()
{
	//步骤1：构造团等待的消息集合
	fidsetmap CliqueWaitedMessages = CreateCliqueWaitedMessages_Downward();

	//步骤2：采用广度优先，使就绪的团向下传递消息
	std::queue<fid_t> OPEN;
	fidset CLOSED;
	OPEN.push(m_nRootID);

	while (!OPEN.empty())
	{
		fid_t nID = OPEN.front();
		OPEN.pop();
		CLOSED.insert(nID);

		const auto& Children = m_Parent2Childs[nID];
		if (Children.empty())
		{
			//检查团是否就绪
			if (IsCliqueReady(nID, CliqueWaitedMessages))
			{
				//如果就绪，则接收消息
				ReceiveMessages(nID, CliqueWaitedMessages);
			}
		}
		else
		{
			for (fid_t nChildID : Children)
			{
				//检查后继节点是否在CLOSED表。如果已经存在，则不需要入队
				if (!CLOSED.contains(nChildID) && IsCliqueReady(nID, CliqueWaitedMessages))
				{
					//接收消息
					ReceiveMessages(nID, CliqueWaitedMessages);
					//向父节点发送消息
					SendCliqueMessage_Downward(nID, nChildID);

					OPEN.push(nChildID);
				}
			}
		}
	}
}
