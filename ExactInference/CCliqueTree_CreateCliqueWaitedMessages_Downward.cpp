/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CCliqueTree_CreateCliqueWaitedMessages_Downward.cpp
//功  能：		向下传递消息时，创建团的等待消息集合
//开发者：		高志强
//日  期：		2021年04月04日
//更  新：		2021年05月18日
//长  度：		70行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		CreateCliqueWaitedMessages_Downward()
//功  能：		向下传递消息时，创建团的等待消息集合
//参  数：		map<unsigned int,set<unsigned int>>&
//返回值：		无
fidsetmap CCliqueTree::CreateCliqueWaitedMessages_Downward()
{
	fidsetmap WaitedMessages;
	////////////////////////////////////////////////////////////////////////////////
	//步骤1：遍历所有团，初始化向下传递消息时，团的等待消息集合为空

	//应该是找所有指向它的点
	for (const CT_NODE& node : m_CTNodes) {
		for (fid_t to : m_Parent2Childs[node.nID]) {
			InsertToWaitedMessages(to, node.nID, WaitedMessages);
		}
	}
	return WaitedMessages;
}