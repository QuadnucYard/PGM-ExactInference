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
void CCliqueTree::CreateCliqueWaitedMessages(map<unsigned int,set<unsigned int>>& WaitedMessages)
{
	////////////////////////////////////////////////////////////////////////////////
	//����1�����������ţ���ʼ���ŵĵȴ���Ϣ����Ϊ��
	for (unsigned int i = 0; i<m_CTNodes.size(); i++)
	{
		//��ȡ��ID
		unsigned int nCliqueID = m_CTNodes[i].nID;

		//��ӵ��ŵĵȴ���Ϣ����
		set<unsigned int> NullMessages;
		WaitedMessages.insert(make_pair(nCliqueID, NullMessages));
	}

	
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//����2��������������ıߣ��������ȴ���Ϣ�ļ���
	for (map<unsigned int, unsigned int>::iterator it = m_UpwardTree.begin(); it != m_UpwardTree.end(); it++)
	{
		//��ȡ�����ID
		unsigned int nCliqueID = it->first;
		//��ȡ˫����ID
		unsigned int nParentID = it->second;

		//��ӵ��ȴ���Ϣ����
		InsertToWaitedMessages(nParentID, nCliqueID, WaitedMessages);
	}
}

//��  �ƣ�		InsertToWaitedMessages()
//��  �ܣ�		�����ŵĵȴ���Ϣ��
//��  ����		unsigned int,unsigned int, map<unsigned int,set<unsigned int>>&
//����ֵ��		��
void CCliqueTree::InsertToWaitedMessages(unsigned int nParentID, unsigned int nCliqueID, 
				map <unsigned int, set<unsigned int>>& WaitedMessages)
{
	//���Ҹ���
	map <unsigned int,set<unsigned int>>::iterator it = WaitedMessages.find(nParentID);

	//����ҵ�
	if (it != WaitedMessages.end())
	{
		//����ŵĵȴ���Ϣ����
		it->second.insert(nCliqueID);
	}
}