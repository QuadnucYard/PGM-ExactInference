////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_BuildUpwardTree.cpp
// 构造向根团的树
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//构造向根团的树
//采用广度优先搜索的方式构造，输入根团ID
void CCliqueTree::BuildUpwardTree(fid_t nParentID)
{
	std::queue<fid_t> OPEN;
	fidset CLOSED;
	OPEN.push(nParentID);

	while (!OPEN.empty())
	{
		fid_t nID = OPEN.front();
		OPEN.pop();
		CLOSED.insert(nID);

		auto er = m_CTEdges.equal_range(nID);
		for (auto p : std::ranges::subrange(er.first, er.second)) {

			fid_t nChildID = p.second;
			//检查后继节点是否在CLOSED表。如果已经存在，则不需要入队
			if (!CLOSED.contains(nChildID))
			{
				//添加边到向根团的树
				m_UpwardTree.insert({nChildID, nID});
				OPEN.push(nChildID);
			}
		}
	}
}