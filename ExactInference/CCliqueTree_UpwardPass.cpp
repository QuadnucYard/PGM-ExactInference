////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_UpwardPass.cpp
// 向上传递消息
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//向根团传递消息
void CCliqueTree::UpwardPass()
{
	//////////////////////////////////////////////////////////////////
	//步骤1：采用通用图搜索算法，构建向根团的树。参见《人工智能导论》中的GRAPHSEARCH
	BuildUpwardTree(m_nRootID);

	//////////////////////////////////////////////////////////////////
	//步骤2：构造团等待的消息集合
	fidsetmap CliqueWaitedMessages = CreateCliqueWaitedMessages();
	//只有1等待0,2的消息，其他无等待
	//获取双亲节点指向子节点集合
	m_Parent2Childs = CliqueWaitedMessages;

	//////////////////////////////////////////////////////////////////
	//步骤3：进入主循环，使就绪的团向上传递消息
	fidset VisitedIDs;
	//检查根团是否就绪？
	while (!IsCliqueReady(m_nRootID, CliqueWaitedMessages))
	{	
		//找到一个就绪的团
		fid_t nCliqueID = FindReadyClique(CliqueWaitedMessages,VisitedIDs);

		//检查是否已经访问过
		if (!VisitedIDs.contains(nCliqueID))
		{
			//添加到访问过的ID集合
			VisitedIDs.insert(nCliqueID);

			//就绪团接收消息  因子积被更新
			ReceiveMessages(nCliqueID, CliqueWaitedMessages);

			//就绪团向父节点发送消息
			SendCliqueMessage(nCliqueID);
		}
	}
	
	//根团接收消息
	ReceiveMessages(m_nRootID, CliqueWaitedMessages);
}
