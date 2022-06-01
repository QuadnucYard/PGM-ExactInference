/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_ReceiveMessages.cpp
//��  �ܣ�		������Ϣ
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��03��
//��  �£�		2021��05��18��
//��  �ȣ�		80��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		ReceiveMessages()
//��  �ܣ�		������Ϣ
//��  ����		unsigned int,map<unsigned int,set<unsigned int>>&
//				��ID���յ���������Ϣ
//����ֵ��		��
void CCliqueTree::ReceiveMessages(unsigned int nCliqueID, map<unsigned int,set<unsigned int>>& CliqueWaitedMessages)
{
	//��ȡ�ȴ���Ϣ�ļ���
	map<unsigned int,set<unsigned int>>::iterator it = CliqueWaitedMessages.find(nCliqueID);
	
	//����Ƿ��ҵ�
	if (it != CliqueWaitedMessages.end())
	{
		//���ȴ���Ϣ�ļ����Ƿ�Ϊ��
		if (it->second.size() == 0)
		{
			//����
			return;
		}
		else
		{
			//��ȡ��ϢԴ
			set<unsigned int> FromCliques = it->second;

			//����������ϢԴ
			for (set<unsigned int>::iterator it = FromCliques.begin(); it != FromCliques.end(); it++)
			{
				//������ʼ�ڵ�
				unsigned int nStartID = *it;
				
				//��ȡ�
				CClique SEPSet = GetSEPSet(nStartID, nCliqueID);

				//��ȡ�ŵ�λ��
				unsigned int nCliquePos = GetCliquePosByID(nCliqueID);
				//��ȡ��
				CClique clique = m_Cliques[nCliquePos];
				
				//ͨ�����ӻ�����������λ�õ���
				m_Cliques[nCliquePos] = clique*SEPSet;
			}
		}
	}
}

//��  �ƣ�		GetSEPSet()
//��  �ܣ�		��ȡ�
//��  ����		unsigned int,unsigned int
//				�����ID���յ���ID
//����ֵ��		CClique
//				���Ҳ����
CClique CCliqueTree::GetSEPSet(unsigned int nStartID, unsigned int nCliqueID)
{
	//�����
	for (unsigned int i = 0; i <m_SEPSets.size(); i++)
	{
		//����Ƿ�Ϊ��Ҫ�ĸ
		if (nStartID  == m_SEPSets[i].nStartID && 
		    nCliqueID == m_SEPSets[i].nEndID)
		{
			//���ظ
			return m_SEPSets[i].clique;
		}
	}
}