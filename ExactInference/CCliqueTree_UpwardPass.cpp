/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_UpwardPass.cpp
//��  �ܣ�		���ϴ�����Ϣ
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��01��
//��  �£�		2021��04��04��
//��  �£�		2021��04��12��
//��  �£�		2021��05��18��
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		UpwardPass()
//��  �ܣ�		����Ŵ�����Ϣ
//��  ����		��
//����ֵ��		��
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
