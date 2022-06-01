////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_CreateCliqueWaitedMessages_Downward.cpp
// ���´�����Ϣʱ�������ŵĵȴ���Ϣ����
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//���´�����Ϣʱ�������ŵĵȴ���Ϣ����
fidsetmap CCliqueTree::CreateCliqueWaitedMessages_Downward()
{
	fidsetmap WaitedMessages;

	//����1�����������ţ���ʼ�����´�����Ϣʱ���ŵĵȴ���Ϣ����Ϊ��
	//Ӧ����������ָ�����ĵ�
	for (const CT_NODE& node : m_CTNodes)
	{
		WaitedMessages.insert({node.nID, {}});
	}

	//����2��������������ıߣ��������ȴ���Ϣ�ļ���
	for (const fidpair& p : m_UpwardTree)
	{
		//��ӵ��ȴ���Ϣ����
		InsertToWaitedMessages(p.first, p.second, WaitedMessages);
	}
	return WaitedMessages;
}