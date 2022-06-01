////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_FindReadyClique.cpp
// ����һ����������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//����һ����������
//return:	�����ŵ�ID
fid_t CCliqueTree::FindReadyClique(const fidsetmap& CliqueWaitedMessages, const fidset& VisitedIDs) const
{
	//����������
	for (const CClique& clique : m_Cliques)
	{
		fid_t nCliqueID = clique.GetID();

		//��ȡ�ŵȴ���Ϣ�ļ���
		if (auto it = CliqueWaitedMessages.find(nCliqueID); it != CliqueWaitedMessages.end())
		{
			//���ȴ���Ϣ�ļ����Ƿ�Ϊ��
			if (!VisitedIDs.contains(nCliqueID)) {
				if (it->second.empty() || IsAllSEPSetExisted(nCliqueID, it->second)) {
					return nCliqueID;
				}
			}
		}
	}
	//û���ҵ��������š���ʾ����ʵ���ϲ�������������
	return -1;
}