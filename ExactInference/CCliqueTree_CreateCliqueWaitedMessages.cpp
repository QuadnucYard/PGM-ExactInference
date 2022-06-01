////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_CreateCliqueWaitedMessages.cpp
// �����ŵĵȴ���Ϣ����
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//�����ŵĵȴ���Ϣ����
fidsetmap CCliqueTree::CreateCliqueWaitedMessages() const
{
	fidsetmap WaitedMessages;

	//����1�����������ţ���ʼ���ŵĵȴ���Ϣ����Ϊ��
	for (const CTNode& node : m_CTNodes)
	{
		WaitedMessages.insert({node.nID, {}});
	}

	//����2��������������ıߣ��������ȴ���Ϣ�ļ���
	for (const fidpair& p : m_UpwardTree)
	{
		//��ӵ��ȴ���Ϣ����
		WaitedMessages[p.second].insert(p.first);
	}
	return WaitedMessages;
}
