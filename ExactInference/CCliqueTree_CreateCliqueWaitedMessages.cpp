/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CCliqueTree_CreateCliqueWaitedMessages.cpp
//功  能：		创建团的等待消息集合
//开发者：		高志强
//日  期：		2021年04月01日
//更  新：		2021年04月03日
//更  新：		2021年05月08日
//长  度：		70行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"	


//名  称：		CreateCliqueWaitedMessages()
//功  能：		创建团的等待消息集合
//参  数：		map<unsigned int,set<unsigned int>>&
//				团ID、团的后继ID集合
//返回值：		无
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

//名  称：		InsertToWaitedMessages()
//功  能：		插入团的等待消息表
//参  数：		unsigned int,unsigned int, map<unsigned int,set<unsigned int>>&
//返回值：		无
void CCliqueTree::InsertToWaitedMessages(fid_t nParentID, fid_t nCliqueID, fidsetmap& WaitedMessages)
{
	/*if (auto it = WaitedMessages.find(nParentID); it != WaitedMessages.end())
	{
		//添加团的等待消息集合
		it->second.insert(nCliqueID);
	}*/
	WaitedMessages[nParentID].insert(nCliqueID);
}