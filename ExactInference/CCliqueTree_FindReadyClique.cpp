/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CCliqueTree_FindReadyClique.cpp
//功  能：		查找一个就绪的团
//开发者：		高志强
//日  期：		2021年04月03日
//更  新：		2021年05月18日
//长  度：		60行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		FindReadyClique()
//功  能：		查找一个就绪的团
//参  数：		map<unsigned int,set<unsigned int>>&
//				set<unsigned int>&
//返回值：		unsigned int
//				就绪团的ID
unsigned int CCliqueTree::FindReadyClique(map<unsigned int,set<unsigned int>>& CliqueWaitedMessages,set<unsigned int>& VisitedIDs)
{
	//遍历所有团
	for (unsigned int i = 0; i < m_Cliques.size(); i++)
	{
		//获取团的ID
		unsigned int nCliqueID = m_Cliques[i].GetID();
		
		//获取团等待消息的集合
		//查找
		map<unsigned int,set<unsigned int>>::iterator it = CliqueWaitedMessages.find(nCliqueID);

		//检查是否找到
		if (it != CliqueWaitedMessages.end())
		{
			//检查等待消息的集合是否为空
			if (it->second.size() == 0 && (!qy::ranges::includes(VisitedIDs, nCliqueID)))
			{
				//返回团的ID
				return nCliqueID;
			}
			else
			{
				//检查相关割集是否都已经存在
				if (IsAllSEPSetExisted(nCliqueID, it->second) &&  (!qy::ranges::includes(VisitedIDs, nCliqueID)))
				{
					//返回团的ID
					return nCliqueID;
				}
			}
		}
	}

	//没有找到就绪的团、提示出错。实际上不会出现这种情况
}