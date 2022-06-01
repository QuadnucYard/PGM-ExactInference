////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_Query_Helper_GetStartedCliquePos.cpp
// ��ȡ��ѯ��ʼ���ŵ�λ��
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//��ȡ��ѯ��ʼ���ŵ�λ��
//��ѯ�������ĸ�
//ѡȡ������ѯ���������ţ���Ϊ��ʼ��
const CClique& CCliqueTree::GetStartClique(const fidset& QueryVariableIDs) const
{
	return *std::ranges::max_element(m_Cliques, {}, [&](auto& c) {
		return qy::set_intersection<fidlist>(c.GetVariableIDs(), QueryVariableIDs).size();
	});
}
