////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_ReceiveMessages.cpp
// ������Ϣ
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//������Ϣ
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

//��ȡ�
//				���Ҳ����
const CClique& CCliqueTree::GetSEPSet(fid_t nStartID, fid_t nCliqueID)
{
	return std::ranges::find_if(m_SEPSets,
		[=](const SEP_SET& s) { return s.nStartID == nStartID && s.nEndID == nCliqueID; })->clique;
}