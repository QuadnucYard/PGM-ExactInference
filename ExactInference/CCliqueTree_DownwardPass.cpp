/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CCliqueTree_DownwardPass.cpp
//功  能：		由根团向下传递消息
//开发者：		高志强
//日  期：		2021年04月04日
//更  新：		2021年05月18日
//长  度：		110行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		DownwardPass()
//功  能：		由根团向下传递消息
//参  数：		无
//返回值：		无
void CCliqueTree::DownwardPass()
{
	//////////////////////////////////////////////////////////////////
	//步骤1：构造团等待的消息集合
	map <unsigned int, set<unsigned int>> CliqueWaitedMessages;
	CreateCliqueWaitedMessages_Downward(CliqueWaitedMessages);


	//////////////////////////////////////////////////////////////////
	//步骤2：采用广度优先，使就绪的团向下传递消息
	std::queue<fid_t> OPEN;
	std::set<fid_t> CLOSED;

	OPEN.push(m_nRootID);

	//检查OPEN表是否为空
	while (OPEN.size() > 0)
	{
		//出队
		fid_t nID = OPEN.front();
		OPEN.pop();
		CLOSED.insert(nID);

		//查找后继
		const auto& Children = m_Parent2Childs[nID];
		//检查是否有后继
		if (Children.size() == 0)
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
			//后继依次入队
			for (fid_t nChildID : Children)
			{

				//检查后继节点是否在CLOSED表。如果已经存在，则不需要入队
				if (!CLOSED.contains(nChildID) &&
					IsCliqueReady(nID, CliqueWaitedMessages))
				{
					//接收消息
					ReceiveMessages(nID, CliqueWaitedMessages);

					//向父节点发送消息
					SendCliqueMessage_Downward(nChildID, nID);

					//添加到OPEN表
					OPEN.push(nChildID);
				}
			}
		}
	}
}
