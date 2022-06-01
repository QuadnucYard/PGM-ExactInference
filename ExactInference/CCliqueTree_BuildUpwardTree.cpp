////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_BuildUpwardTree.cpp
// ��������ŵ���
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//��������ŵ���
//���ù�����������ķ�ʽ���죬�������ID
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
			//����̽ڵ��Ƿ���CLOSED������Ѿ����ڣ�����Ҫ���
			if (!CLOSED.contains(nChildID))
			{
				//��ӱߵ�����ŵ���
				m_UpwardTree.insert({nChildID, nID});
				OPEN.push(nChildID);
			}
		}
	}
}