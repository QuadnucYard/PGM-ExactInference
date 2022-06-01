////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_UpwardPass.cpp
// ���ϴ�����Ϣ
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//����Ŵ�����Ϣ
void CCliqueTree::UpwardPass()
{
	//////////////////////////////////////////////////////////////////
	//����1������ͨ��ͼ�����㷨����������ŵ������μ����˹����ܵ��ۡ��е�GRAPHSEARCH
	BuildUpwardTree(m_nRootID);

	//////////////////////////////////////////////////////////////////
	//����2�������ŵȴ�����Ϣ����
	fidsetmap CliqueWaitedMessages = CreateCliqueWaitedMessages();
	//ֻ��1�ȴ�0,2����Ϣ�������޵ȴ�
	//��ȡ˫�׽ڵ�ָ���ӽڵ㼯��
	m_Parent2Childs = CliqueWaitedMessages;

	//////////////////////////////////////////////////////////////////
	//����3��������ѭ����ʹ�����������ϴ�����Ϣ
	fidset VisitedIDs;
	//�������Ƿ������
	while (!IsCliqueReady(m_nRootID, CliqueWaitedMessages))
	{	
		//�ҵ�һ����������
		fid_t nCliqueID = FindReadyClique(CliqueWaitedMessages,VisitedIDs);

		//����Ƿ��Ѿ����ʹ�
		if (!VisitedIDs.contains(nCliqueID))
		{
			//��ӵ����ʹ���ID����
			VisitedIDs.insert(nCliqueID);

			//�����Ž�����Ϣ  ���ӻ�������
			ReceiveMessages(nCliqueID, CliqueWaitedMessages);

			//�������򸸽ڵ㷢����Ϣ
			SendCliqueMessage(nCliqueID);
		}
	}
	
	//���Ž�����Ϣ
	ReceiveMessages(m_nRootID, CliqueWaitedMessages);
}
