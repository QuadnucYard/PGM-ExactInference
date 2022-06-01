/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_CreateCliqueWaitedMessages.cpp
//��  �ܣ�		�����ŵĵȴ���Ϣ����
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��01��
//��  �£�		2021��04��03��
//��  �£�		2021��05��08��
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"	


//��  �ƣ�		CreateCliqueWaitedMessages()
//��  �ܣ�		�����ŵĵȴ���Ϣ����
//��  ����		map<unsigned int,set<unsigned int>>&
//				��ID���ŵĺ��ID����
//����ֵ��		��
fidsetmap CCliqueTree::CreateCliqueWaitedMessages()
{
	fidsetmap WaitedMessages;
	////////////////////////////////////////////////////////////////////////////////
	//����1�����������ţ���ʼ���ŵĵȴ���Ϣ����Ϊ��
	for (const CT_NODE& node : m_CTNodes)
	{
		//��ӵ��ŵĵȴ���Ϣ����
		WaitedMessages.insert({node.nID, {}});
	}

	
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//����2��������������ıߣ��������ȴ���Ϣ�ļ���
	for (const fidpair& p : m_UpwardTree)
	{
		//��ӵ��ȴ���Ϣ����
		InsertToWaitedMessages(p.second, p.first, WaitedMessages);
	}
	return WaitedMessages;
}

//��  �ƣ�		InsertToWaitedMessages()
//��  �ܣ�		�����ŵĵȴ���Ϣ��
//��  ����		unsigned int,unsigned int, map<unsigned int,set<unsigned int>>&
//����ֵ��		��
void CCliqueTree::InsertToWaitedMessages(fid_t nParentID, fid_t nCliqueID, fidsetmap& WaitedMessages)
{
	/*if (auto it = WaitedMessages.find(nParentID); it != WaitedMessages.end())
	{
		//����ŵĵȴ���Ϣ����
		it->second.insert(nCliqueID);
	}*/
	WaitedMessages[nParentID].insert(nCliqueID);
}