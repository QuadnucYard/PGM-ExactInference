/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_FindReadyClique.cpp
//��  �ܣ�		����һ����������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��03��
//��  �£�		2021��05��18��
//��  �ȣ�		60��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		FindReadyClique()
//��  �ܣ�		����һ����������
//��  ����		map<unsigned int,set<unsigned int>>&
//				set<unsigned int>&
//����ֵ��		unsigned int
//				�����ŵ�ID
unsigned int CCliqueTree::FindReadyClique(map<unsigned int,set<unsigned int>>& CliqueWaitedMessages,set<unsigned int>& VisitedIDs)
{
	//����������
	for (unsigned int i = 0; i < m_Cliques.size(); i++)
	{
		//��ȡ�ŵ�ID
		unsigned int nCliqueID = m_Cliques[i].GetID();
		
		//��ȡ�ŵȴ���Ϣ�ļ���
		//����
		map<unsigned int,set<unsigned int>>::iterator it = CliqueWaitedMessages.find(nCliqueID);

		//����Ƿ��ҵ�
		if (it != CliqueWaitedMessages.end())
		{
			//���ȴ���Ϣ�ļ����Ƿ�Ϊ��
			if (it->second.size() == 0 && (!qy::ranges::includes(VisitedIDs, nCliqueID)))
			{
				//�����ŵ�ID
				return nCliqueID;
			}
			else
			{
				//�����ظ�Ƿ��Ѿ�����
				if (IsAllSEPSetExisted(nCliqueID, it->second) &&  (!qy::ranges::includes(VisitedIDs, nCliqueID)))
				{
					//�����ŵ�ID
					return nCliqueID;
				}
			}
		}
	}

	//û���ҵ��������š���ʾ����ʵ���ϲ�������������
}