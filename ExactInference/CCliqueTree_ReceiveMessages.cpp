/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CCliqueTree_ReceiveMessages.cpp
//功  能：		接收消息
//开发者：		高志强
//日  期：		2021年04月03日
//更  新：		2021年05月18日
//长  度：		80行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		ReceiveMessages()
//功  能：		接收消息
//参  数：		unsigned int,map<unsigned int,set<unsigned int>>&
//				团ID、收到的所有消息
//返回值：		无
void CCliqueTree::ReceiveMessages(unsigned int nCliqueID, map<unsigned int,set<unsigned int>>& CliqueWaitedMessages)
{
	//获取等待消息的集合
	map<unsigned int,set<unsigned int>>::iterator it = CliqueWaitedMessages.find(nCliqueID);
	
	//检查是否找到
	if (it != CliqueWaitedMessages.end())
	{
		//检查等待消息的集合是否为空
		if (it->second.size() == 0)
		{
			//返回
			return;
		}
		else
		{
			//获取消息源
			set<unsigned int> FromCliques = it->second;

			//遍历所有消息源
			for (set<unsigned int>::iterator it = FromCliques.begin(); it != FromCliques.end(); it++)
			{
				//定义起始节点
				unsigned int nStartID = *it;
				
				//获取割集
				CClique SEPSet = GetSEPSet(nStartID, nCliqueID);

				//获取团的位置
				unsigned int nCliquePos = GetCliquePosByID(nCliqueID);
				//获取团
				CClique clique = m_Cliques[nCliquePos];
				
				//通过因子积、更新所在位置的团
				m_Cliques[nCliquePos] = clique*SEPSet;
			}
		}
	}
}

//名  称：		GetSEPSet()
//功  能：		获取割集
//参  数：		unsigned int,unsigned int
//				起点团ID、终点团ID
//返回值：		CClique
//				割集。也是团
CClique CCliqueTree::GetSEPSet(unsigned int nStartID, unsigned int nCliqueID)
{
	//遍历割集
	for (unsigned int i = 0; i <m_SEPSets.size(); i++)
	{
		//检查是否为所要的割集
		if (nStartID  == m_SEPSets[i].nStartID && 
		    nCliqueID == m_SEPSets[i].nEndID)
		{
			//返回割集
			return m_SEPSets[i].clique;
		}
	}
}