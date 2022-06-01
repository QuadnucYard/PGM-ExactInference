/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_CreateCliqueWaitedMessages_Downward.cpp
//��  �ܣ�		���´�����Ϣʱ�������ŵĵȴ���Ϣ����
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��04��
//��  �£�		2021��05��18��
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		CreateCliqueWaitedMessages_Downward()
//��  �ܣ�		���´�����Ϣʱ�������ŵĵȴ���Ϣ����
//��  ����		map<unsigned int,set<unsigned int>>&
//����ֵ��		��
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