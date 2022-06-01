/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_FindReadyClique.cpp
//��  �ܣ�		����һ����������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��03��
//��  �£�		2021��05��18��
//��  �ȣ�		60��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//����һ����������
//return:	�����ŵ�ID
unsigned int CCliqueTree::FindReadyClique(map<unsigned int, set<unsigned int>>& CliqueWaitedMessages, set<unsigned int>& VisitedIDs)
{
	//����������
	for (const CClique& clique : m_Cliques)
	{
		fid_t nCliqueID = clique.GetID();

		//��ȡ�ŵȴ���Ϣ�ļ���
		if (auto it = CliqueWaitedMessages.find(nCliqueID); it != CliqueWaitedMessages.end())
		{
			//���ȴ���Ϣ�ļ����Ƿ�Ϊ��
			if (VisitedIDs.count(nCliqueID) == 0) {
				if (it->second.size() == 0 || IsAllSEPSetExisted(nCliqueID, it->second)) {
					return nCliqueID;
				}
			}
		}
	}

	//û���ҵ��������š���ʾ����ʵ���ϲ�������������
}