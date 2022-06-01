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
void CCliqueTree::ReceiveMessages(fid_t nCliqueID, const fidsetmap& CliqueWaitedMessages)
{
	//��ȡ�ȴ���Ϣ�ļ���
	if (auto it = CliqueWaitedMessages.find(nCliqueID); it != CliqueWaitedMessages.end())
	{
		//����������ϢԴ
		for (fid_t nStartID : it->second)
		{
			//��ȡ�ŵ�λ��
			size_t nCliquePos = GetCliquePosByID(nCliqueID);
			//ͨ�����ӻ�����������λ�õ���
			m_Cliques[nCliquePos] = m_Cliques[nCliquePos] * GetSEPSet(nStartID, nCliqueID);
		}
	}
}

//��  �ƣ�		GetSEPSet()
//��  �ܣ�		��ȡ�
//��  ����		unsigned int,unsigned int
//				�����ID���յ���ID
//����ֵ��		CClique
//				���Ҳ����
const CClique& CCliqueTree::GetSEPSet(fid_t nStartID, fid_t nCliqueID)
{
	return std::ranges::find_if(m_SEPSets,
		[=](const SEP_SET& s) { return s.nStartID == nStartID && s.nEndID == nCliqueID; })->clique;
}