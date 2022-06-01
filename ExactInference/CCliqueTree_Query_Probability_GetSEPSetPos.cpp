////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_Query_Probability_GetSEPSetPos.cpp
// ��ȡ���λ��
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//��ȡ�λ��
const CutSet& CCliqueTree::GetReadySEPSet(fid_t nID, fid_t nChildID) const
{
	//nChildIDΪ��
	return *std::ranges::find_if(m_SEPSets, [=](const CutSet& s) {
		return (s.nStartID == nID && s.nEndID == nChildID || s.nStartID == nChildID && s.nEndID == nID)
			&& s.bReady; //�����Ƿ����, ��Ƿ����
	});
}