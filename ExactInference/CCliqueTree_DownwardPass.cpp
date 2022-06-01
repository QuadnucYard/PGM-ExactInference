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
	//定义OPEN列表和CLOSED表
	queue <unsigned int> OPEN;
	set<unsigned int> CLOSED;

	//初始化OPEN表
	OPEN.push(m_nRootID);

	//检查OPEN表是否为空
	while (OPEN.size() > 0)
	{
		//出队
		unsigned int nID = OPEN.front();
		OPEN.pop();

		//加入CLOSED表
		CLOSED.insert(nID);

		//查找后继
		set<unsigned int> Children = GetChildren(nID);
		//检查是否有后继
		if (Children.size() == 0)
		{
			//检查团是否就绪
			if(IsCliqueReady(nID, CliqueWaitedMessages))
			{
				//如果就绪，则接收消息
				ReceiveMessages(nID, CliqueWaitedMessages);
			}
		}
		else
		{
			//检查是否存在后继，并依次入队
			for (set<unsigned int>::iterator it = Children.begin(); it != Children.end(); it++)
			{
				//获取后继结点
				unsigned int nChildID = *it;

				//检查后继节点是否在CLOSED表。如果已经存在，则不需要入队
				if (!qy::ranges::includes(CLOSED, nChildID) &&
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

//名  称：		GetChildren()
//功  能：		获取孩子
//参  数：		unsigned int
//				团ID
//返回值：		set<unsigned int>
//				团的孩子ID集合
set<unsigned int> CCliqueTree::GetChildren(unsigned int nID)
{
	//从双亲到孩子集合的映射中查找
	map<unsigned int, set<unsigned int>>::iterator it = m_Parent2Childs.find(nID);
	
	if (it != m_Parent2Childs.end())
	{
		//如果找到的话，则返回孩子ID集合
		return it->second;
	}
}