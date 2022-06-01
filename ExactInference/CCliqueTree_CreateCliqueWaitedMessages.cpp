////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_CreateCliqueWaitedMessages.cpp
// �����ŵĵȴ���Ϣ����
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//�����ŵĵȴ���Ϣ����
fidsetmap CCliqueTree::CreateCliqueWaitedMessages()
{
	fidsetmap WaitedMessages;

	//����1�����������ţ���ʼ���ŵĵȴ���Ϣ����Ϊ��
	for (const CT_NODE& node : m_CTNodes)
	{
		WaitedMessages.insert({node.nID, {}});
	}

	//����2��������������ıߣ��������ȴ���Ϣ�ļ���
	for (const fidpair& p : m_UpwardTree)
	{
		//��ӵ��ȴ���Ϣ����
		InsertToWaitedMessages(p.second, p.first, WaitedMessages);
	}
	return WaitedMessages;
}

//�����ŵĵȴ���Ϣ��
void CCliqueTree::InsertToWaitedMessages(fid_t nParentID, fid_t nCliqueID, fidsetmap& WaitedMessages)
{
	WaitedMessages[nParentID].insert(nCliqueID);
}