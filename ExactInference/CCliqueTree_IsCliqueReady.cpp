/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CCliqueTree_IsReady.cpp
//功  能：		检查团是否就绪
//开发者：		高志强
//日  期：		2021年04月01日
//更  新：		2021年04月03日
//更  新：		2021年05月18日
//长  度：		110行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		IsCliqueReady()
//功  能：		检查团是否就绪
//参  数：		unsigned int,map<unsigned int, set<unsigned int>>&
//				团ID、等待的消息集合
//返回值：		bool
//				团是否就绪？
bool CCliqueTree::IsCliqueReady(unsigned int nCliqueID, map<unsigned int,set<unsigned int>>& WaitedMessages)
{
	//查找等待的消息映射
	map<unsigned int, set<unsigned int>>::iterator it = WaitedMessages.find(nCliqueID);

	//检查是否找到
	if (it != WaitedMessages.end())
	{
		//检查等待消息的集合是否为空
		if (it->second.size() == 0)
		{
			//返回真
			return true;
		}
		else
		{
			//检查相关割集是否都已经存在
			if (IsAllSEPSetExisted(nCliqueID, it->second))
			{
				//返回真
				return true;
			}
			else
			{
				//返回假
				return false;
			}
		}
	}
	else
	{
		//提示出现异常。这种情况一般不会出现
		//缺省返回假
		return false;
	}
}

//名  称：		IsAllSEPSetExisted()
//功  能：		检查是否所有割集都已经存在
//参  数：		unsigned int,set<unsigned int>&
//				团ID、等待的消息集合
//返回值：		bool
//				是否所需的割集都已经存在？
bool CCliqueTree::IsAllSEPSetExisted(unsigned int nID, set<unsigned int>& WaitedMessages)
{
	//遍历所有等待消息
	for (set<unsigned int>::iterator it = WaitedMessages.begin(); it != WaitedMessages.end(); it++)
	{
		//获取团ID
		unsigned int nStartID = *it;

		//检查割集是否存在
		if (!IsAllSEPSetExisted_Helper(nStartID, nID))
		{
			//返回假
			return false;
		}
	}
	
	//缺省返回真
	return true;
}

//名  称：		IsAllSEPSetExisted_Helper()
//功  能：		检查是否所有割集都已经存在的辅助函数
//参  数：		unsigned int,unsigned int
//				起点团ID、终点团ID
//返回值：		bool
//				是否割集存在？
bool CCliqueTree::IsAllSEPSetExisted_Helper(unsigned int nStartID, unsigned int nID)
{
	//遍历所有割集
	for (unsigned int i = 0; i < m_SEPSets.size(); i++)
	{
		//检查是否相等
		if (nStartID == m_SEPSets[i].nStartID && nID == m_SEPSets[i].nEndID)
		{
			//返回真
			return true;
		}
	}

	//缺省返回假
	return false;
}