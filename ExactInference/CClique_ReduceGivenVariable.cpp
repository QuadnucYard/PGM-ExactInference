/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CClique_ReduceGivenVariable.cpp
//��  �ܣ�		���ݸ����ı�����ֵ�������š����ڼ����������ʷֲ�
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��31��
//��  �£�		2021��04��12��
//��  �£�		2021��05��18��
//��  �ȣ�		50��
/////////////////////////////////////////////////////////////////////////////////////////////
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