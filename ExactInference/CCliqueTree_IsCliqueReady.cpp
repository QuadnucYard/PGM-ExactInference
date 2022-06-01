/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_IsReady.cpp
//��  �ܣ�		������Ƿ����
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��01��
//��  �£�		2021��04��03��
//��  �£�		2021��05��18��
//��  �ȣ�		110��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		IsCliqueReady()
//��  �ܣ�		������Ƿ����
//��  ����		unsigned int,map<unsigned int, set<unsigned int>>&
//				��ID���ȴ�����Ϣ����
//����ֵ��		bool
//				���Ƿ������
bool CCliqueTree::IsCliqueReady(unsigned int nCliqueID, map<unsigned int,set<unsigned int>>& WaitedMessages)
{
	//���ҵȴ�����Ϣӳ��
	map<unsigned int, set<unsigned int>>::iterator it = WaitedMessages.find(nCliqueID);

	//����Ƿ��ҵ�
	if (it != WaitedMessages.end())
	{
		//���ȴ���Ϣ�ļ����Ƿ�Ϊ��
		if (it->second.size() == 0)
		{
			//������
			return true;
		}
		else
		{
			//�����ظ�Ƿ��Ѿ�����
			if (IsAllSEPSetExisted(nCliqueID, it->second))
			{
				//������
				return true;
			}
			else
			{
				//���ؼ�
				return false;
			}
		}
	}
	else
	{
		//��ʾ�����쳣���������һ�㲻�����
		//ȱʡ���ؼ�
		return false;
	}
}

//��  �ƣ�		IsAllSEPSetExisted()
//��  �ܣ�		����Ƿ����и���Ѿ�����
//��  ����		unsigned int,set<unsigned int>&
//				��ID���ȴ�����Ϣ����
//����ֵ��		bool
//				�Ƿ�����ĸ���Ѿ����ڣ�
bool CCliqueTree::IsAllSEPSetExisted(unsigned int nID, set<unsigned int>& WaitedMessages)
{
	//�������еȴ���Ϣ
	for (set<unsigned int>::iterator it = WaitedMessages.begin(); it != WaitedMessages.end(); it++)
	{
		//��ȡ��ID
		unsigned int nStartID = *it;

		//����Ƿ����
		if (!IsAllSEPSetExisted_Helper(nStartID, nID))
		{
			//���ؼ�
			return false;
		}
	}
	
	//ȱʡ������
	return true;
}

//��  �ƣ�		IsAllSEPSetExisted_Helper()
//��  �ܣ�		����Ƿ����и���Ѿ����ڵĸ�������
//��  ����		unsigned int,unsigned int
//				�����ID���յ���ID
//����ֵ��		bool
//				�Ƿ����ڣ�
bool CCliqueTree::IsAllSEPSetExisted_Helper(unsigned int nStartID, unsigned int nID)
{
	//�������и
	for (unsigned int i = 0; i < m_SEPSets.size(); i++)
	{
		//����Ƿ����
		if (nStartID == m_SEPSets[i].nStartID && nID == m_SEPSets[i].nEndID)
		{
			//������
			return true;
		}
	}

	//ȱʡ���ؼ�
	return false;
}