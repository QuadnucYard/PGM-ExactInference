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
size_t CCliqueTree::GetStartCliquePos(const fidset& QueryVariableIDs)
{
	return std::ranges::max_element(m_Cliques, {}, [&](auto& c) {
		return qy::set_intersection<fidlist>(c.GetVariableIDs(), QueryVariableIDs).size();
	}) - m_Cliques.begin();
}
