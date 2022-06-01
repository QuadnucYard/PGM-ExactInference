////////////////////////////////////////////////////////////////////////////////
// CClique_ReduceGivenVariable.cpp
// ���ݸ����ı�����ֵ�������š����ڼ����������ʷֲ�
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CClique.h"


//���ݸ����ı���ID��ֵID��������
void CClique::ReduceGivenVariable(fid_t nVariableID, fid_t nValueID)
{
	if (size_t nPos = qy::ranges::index_of(m_VariableIDs, nVariableID); nPos != -1)
	{
		qy::remove_if(m_CliqueRows, [=](const CLIQUE_ROW& t) {return t[nPos] != nValueID; });
	}
}