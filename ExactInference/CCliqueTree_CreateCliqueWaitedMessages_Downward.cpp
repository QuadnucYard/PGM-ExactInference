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
	////////////////////////////////////////////////////////////////////////////////
	//����1�����������ţ���ʼ�����´�����Ϣʱ���ŵĵȴ���Ϣ����Ϊ��

	//Ӧ����������ָ�����ĵ�
	for (const CT_NODE& node : m_CTNodes) {
		for (fid_t to : m_Parent2Childs[node.nID]) {
			InsertToWaitedMessages(to, node.nID, WaitedMessages);
		}
	}
	return WaitedMessages;
}