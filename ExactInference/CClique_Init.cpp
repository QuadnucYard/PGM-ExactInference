/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CClique_Init.cpp
//��  �ܣ�		��ʼ�����������ñ���ID�б�����
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��31��
//��  �£�		2021��04��12��
//��  �£�		2021��05��18��
//��  �ȣ�		60��
/////////////////////////////////////////////////////////////////////////////////////////////
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