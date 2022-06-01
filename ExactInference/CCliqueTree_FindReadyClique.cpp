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
				if (it->second.size() == 0 || IsAllSEPSetExisted(nCliqueID, it->second)) {
					return nCliqueID;
				}
			}
		}
	}
	//û���ҵ��������š���ʾ����ʵ���ϲ�������������
	return -1;
}