////////////////////////////////////////////////////////////////////////////////
// CClique_Init.cpp
// ��ʼ�����������ñ���ID�б�����
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CClique.h"


//������ID
void CClique::SetCliqueID(fid_t nCliqueID)
{
	m_nCliqueID = nCliqueID;
}

//���ñ���ID�б�
void CClique::SetCliqueVariableIDs(const fidlist& VariableIDs)
{
	m_VariableIDs = VariableIDs;
}

//��������
void CClique::SetCliqueRow(const fidlist& ValueIDs, fval_t fRowValue)
{
	m_CliqueRows.emplace_back(ValueIDs, fRowValue);
}