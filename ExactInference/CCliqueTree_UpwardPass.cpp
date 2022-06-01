/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CCliqueTree_UpwardPass.cpp
//功  能：		向上传递消息
//开发者：		高志强
//日  期：		2021年04月01日
//更  新：		2021年04月04日
//更  新：		2021年04月12日
//更  新：		2021年05月18日
//长  度：		70行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		UpwardPass()
//功  能：		向根团传递消息
//参  数：		无
//返回值：		无
void CCliqueTree::UpwardPass()
{
	//////////////////////////////////////////////////////////////////
	//步骤1：采用通用图搜索算法，构建向根团的树。参见《人工智能导论》中的GRAPHSEARCH
	BuildUpwardTree(m_nRootID);

	
	//////////////////////////////////////////////////////////////////
	//步骤2：构造团等待的消息集合
	map <unsigned int,set<unsigned int>> CliqueWaitedMessages;
	CreateCliqueWaitedMessages(CliqueWaitedMessages);
	//获取双亲节点指向子节点集合
	m_Parent2Childs = CliqueWaitedMessages;


	//////////////////////////////////////////////////////////////////
	//步骤3：进入主循环，使就绪的团向上传递消息
	set<unsigned int> VisitedIDs;
	//检查根团是否就绪？
	while (!IsCliqueReady(m_nRootID, CliqueWaitedMessages))
	{	
		//找到一个就绪的团
		unsigned int nCliqueID = FindReadyClique(CliqueWaitedMessages,VisitedIDs);

		//检查是否已经访问过
		if (!IsINTInSet(nCliqueID, VisitedIDs))
		{
			//添加到访问过的ID集合
			VisitedIDs.insert(nCliqueID);

			//就绪团接收消息
			ReceiveMessages(nCliqueID, CliqueWaitedMessages);

			//就绪团向父节点发送消息
			SendCliqueMessage(nCliqueID);
		}
	}
	
	//根团接收消息
	ReceiveMessages(m_nRootID,CliqueWaitedMessages);
}
