////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_BuildUpwardTree.cpp
// 构造向根团的树
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//构造向根团的树
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