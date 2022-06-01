////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_DownwardPass.cpp
// �ɸ������´�����Ϣ
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//�ɸ������´�����Ϣ
void CCliqueTree::DownwardPass()
{
	//����1�������ŵȴ�����Ϣ����
	fidsetmap CliqueWaitedMessages = CreateCliqueWaitedMessages_Downward();

	//����2�����ù�����ȣ�ʹ�����������´�����Ϣ
	std::queue<fid_t> OPEN;
	fidset CLOSED;
	OPEN.push(m_nRootID);

	while (!OPEN.empty())
	{
		fid_t nID = OPEN.front();
		OPEN.pop();
		CLOSED.insert(nID);

		const auto& Children = m_Parent2Childs[nID];
		if (Children.empty())
		{
			//������Ƿ����
			if (IsCliqueReady(nID, CliqueWaitedMessages))
			{
				//����������������Ϣ
				ReceiveMessages(nID, CliqueWaitedMessages);
			}
		}
		else
		{
			for (fid_t nChildID : Children)
			{
				//����̽ڵ��Ƿ���CLOSED������Ѿ����ڣ�����Ҫ���
				if (!CLOSED.contains(nChildID) && IsCliqueReady(nID, CliqueWaitedMessages))
				{
					//������Ϣ
					ReceiveMessages(nID, CliqueWaitedMessages);
					//�򸸽ڵ㷢����Ϣ
					SendCliqueMessage_Downward(nID, nChildID);

					OPEN.push(nChildID);
				}
			}
		}
	}
}
