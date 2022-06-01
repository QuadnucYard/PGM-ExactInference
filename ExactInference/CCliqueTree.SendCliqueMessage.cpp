/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CCliqueTree_SendCliqueMessage.cpp
//功  能：		发送团消息
//开发者：		高志强
//日  期：		2021年04月03日
//更  新：		2021年05月18日
//长  度：		150行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		SendCliqueMessage()
//功  能：		发送团消息
//参  数：		unsigned int
//				就绪团ID
//返回值：		无
void CCliqueTree::SendCliqueMessage(unsigned int nID)
{
	//找到双亲节点
	unsigned int nParentID;

	//如果找到双亲,则通过参数获取双亲ID
	if (IsThereParentID(nID, nParentID))
	{
		//找到两个团相交的变量ID集合
		set<unsigned int> CommonVariableIDs;

		//获取两个团的变量ID交集
		FindCommonVariableIDs(nID, nParentID, CommonVariableIDs);

		//获取团的位置
		unsigned int nPos = GetCliquePosByID(nID);
		//定义并获取团的变量集合
		set<unsigned int> CliqueVariableIDs = m_Cliques[nPos].GetVariableIDs();
		//获取需要求和掉的变量ID集合
		set<unsigned int> EliminateVariableIDs;

		//求集合的差。团的变量集合-割集变量集合=求和掉的变量集合
		SubtractBetweenSets(CliqueVariableIDs, CommonVariableIDs, EliminateVariableIDs);

		//定义割集
		SEP_SET sep_set;
		sep_set.nStartID = nID;
		sep_set.nEndID = nParentID;
		sep_set.clique = m_Cliques[nPos];
		sep_set.bReady = false;//向上传递消息
		
		//遍历所有消除变量
		for (set<unsigned int>::iterator it = EliminateVariableIDs.begin(); it != EliminateVariableIDs.end(); it++)
		{
			//求和掉变量
			sep_set.clique.SumOutVariable(*it);
		}

		//添加到割集列表
		m_SEPSets.push_back(sep_set);
	}
}

//名  称：		FindCommonVariableID()
//功  能：		求两个团的变量ID交集
//参  数：		unsigned int,unsigned int
//返回值：		无
void CCliqueTree::FindCommonVariableIDs(unsigned int nID1, unsigned int nID2, set<unsigned int>& Intersections)
{
	//获取节点1的变量集合
	set <unsigned int> VariableIDs1 = m_Cliques[nID1].GetVariableIDs();
	
	//获取节点2的变量集合
	set <unsigned int> VariableIDs2 = m_Cliques[nID2].GetVariableIDs();

	//求两个集合的交集
	FindIntersections(VariableIDs1, VariableIDs2, Intersections);
}

//名  称：		FindIntersections()
//功  能：		求两个集合的交集
//参  数：		set<unsigned int>&,set<unsigned int>&,set<unsigned int>&
//返回值：		无
void CCliqueTree::FindIntersections(set<unsigned int>& s1, set<unsigned int>& s2, set<unsigned int>& s)
{
	for (set<unsigned int>::iterator it = s1.begin(); it != s1.end(); it++)
	{
		//定义ID
		unsigned int nID = *it;
		
		//查找是否在集合
		if (IsINTInSet(nID, s2))
		{
			//添加到交集
			s.insert(*it);
		}
	}
}

//名  称：		IsThereParentID()
//功  能：		查找双亲是否存在，如果存在，则返回双亲ID
//参  数：		unsigned int,unsigned int&
//				团ID、团双亲ID
//返回值：		bool
//				团是否存在双亲。如果有的话，则通过参数获取双亲ID
bool CCliqueTree::IsThereParentID(unsigned int nID, unsigned int& nParentID)
{
	//在向根团的树中查找
	map<unsigned int, unsigned int>::iterator it = m_UpwardTree.find(nID);

	//检查是否找到双亲
	if (it != m_UpwardTree.end())
	{
		//赋值、获取双亲ID
		nParentID = it->second;

		//返回真
		return true;
	}
	else
	{
		//返回假
		return false;
	}
}

//名  称：		SubtractBetweenSets()
//功  能：		求两个集合的差
//参  数：		set<unsigned int>&,set<unsigned int>&,set<unsigned int>&
//				集合1、集合2、两个集合的差
//返回值：		无
void CCliqueTree::SubtractBetweenSets(set<unsigned int>& s1, set<unsigned int>& s2, set<unsigned int>& s)
{
	//遍历集合1
	for (set<unsigned int>::iterator it = s1.begin(); it != s1.end(); it++)
	{
		//定义ID
		unsigned int nID = *it;
		
		//查找是否在集合2中
		if (!IsINTInSet(nID, s2))
		{
			//如果不存在，则添加到差集
			s.insert(*it);
		}
	}
}