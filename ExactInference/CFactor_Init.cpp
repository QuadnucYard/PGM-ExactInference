/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CFactor_Init.cpp
//��  �ܣ�		��ʼ�����������ñ���ID�б�������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��12��
//��  �£�		2021��03��23��
//��  �£�		2021��03��29��
//��  �ȣ�		50��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CFactor.h"


void CFactor::SetFactorVariableIDs(const fidlist& VariableIDs)
{
	m_VariableIDs = VariableIDs;
}

void CFactor::SetFactorVariableIDs(fidlist&& VariableIDs)
{
	m_VariableIDs = std::move(VariableIDs);
}

void CFactor::SetFactorRow(const fidlist& ValueIDs, fval_t fRowValue)
{
	m_FactorRows.emplace_back(ValueIDs, fRowValue);
}

void CFactor::SetFactorRow(fidlist&& ValueIDs, fval_t fRowValue)
{
	m_FactorRows.emplace_back(std::move(ValueIDs), fRowValue);
}