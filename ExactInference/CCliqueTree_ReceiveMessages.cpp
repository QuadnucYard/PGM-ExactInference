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
void CCliqueTree::ReceiveMessages(fid_t nCliqueID, const fidsetmap& CliqueWaitedMessages)
{
	//获取等待消息的集合
	if (auto it = CliqueWaitedMessages.find(nCliqueID); it != CliqueWaitedMessages.end())
	{
		//遍历所有消息源
		for (fid_t nStartID : it->second)
		{
			//获取团的位置
			size_t nCliquePos = GetCliquePosByID(nCliqueID);
			//通过因子积、更新所在位置的团
			m_Cliques[nCliquePos] = m_Cliques[nCliquePos] * GetSEPSet(nStartID, nCliqueID);
		}
	}
}

//名  称：		GetSEPSet()
//功  能：		获取割集
//参  数：		unsigned int,unsigned int
//				起点团ID、终点团ID
//返回值：		CClique
//				割集。也是团
const CClique& CCliqueTree::GetSEPSet(fid_t nStartID, fid_t nCliqueID)
{
	return std::ranges::find_if(m_SEPSets,
		[=](const SEP_SET& s) { return s.nStartID == nStartID && s.nEndID == nCliqueID; })->clique;
}