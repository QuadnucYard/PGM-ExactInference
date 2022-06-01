/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CCliqueTree_BuildUpwardTree.cpp
//功  能：		构造向根团的树
//开发者：		高志强
//日  期：		2021年04月01日
//更  新：		2021年04月03日
//更  新：		2021年05月18日
//长  度：		70行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		BuildUpwardTree()
//功  能：		构造向根团的树
//参  数：		unsigned int
//返回值：		无
//提  示：		采用广度优先搜索的方式构造，输入根团ID
void CCliqueTree::BuildUpwardTree(fid_t nParentID)
{
	//定义OPEN列表和CLOSED表
	queue <unsigned int> OPEN;
	set<unsigned int> CLOSED;

	//初始化OPEN表
	OPEN.push(nParentID);

	//检查OPEN表是否为空
	while (OPEN.size() > 0)
	{
		//出队
		unsigned int nID = OPEN.front();
		OPEN.pop();
		
		//加入CLOSED表
		CLOSED.insert(nID);

		//查找后继
		multimap<unsigned int, unsigned int>::iterator beg = m_CTEdges.lower_bound(nID);
		multimap<unsigned int, unsigned int>::iterator end = m_CTEdges.upper_bound(nID);
		//检查是否存在后继，并依次入队
		while (beg != end)
		{
			//获取后继结点
			unsigned int nChildID = beg->second;

			//检查后继节点是否在CLOSED表。如果已经存在，则不需要入队
			if (!qy::ranges::includes(CLOSED,nChildID))
			{
				//添加边到向根团的树
				m_UpwardTree.insert(make_pair(nChildID, nID));
				
				//添加到OPEN表
				OPEN.push(nChildID);
			}

			//更新迭代器
			beg++;
		}
	}
}