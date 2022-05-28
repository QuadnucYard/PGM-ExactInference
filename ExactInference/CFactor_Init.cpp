/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CFactor_Init.cpp
//��  �ܣ�		��ʼ�����������ñ���ID�б�������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��12��
//��  �£�		2021��03��23��
//��  �£�		2021��03��29��
//��  �ȣ�		50��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CFactor.h"								//������ͷ�ļ�


//��  �ƣ�		SetVariableIDs()
//��  �ܣ�		���ñ���ID�б�
//��  ����		vector<unsigned int>&
//����ֵ��		��
void CFactor::SetFactorVariableIDs(const fidlist& VariableIDs)
{
	//��ʼ�������б���ID���б�
	m_VariableIDs = VariableIDs;
}

void CFactor::SetFactorVariableIDs(fidlist&& VariableIDs)
{
	//��ʼ�������б���ID���б�
	m_VariableIDs = VariableIDs;
}

//��  �ƣ�		SetFactorRow()
//��  �ܣ�		����������
//��  ����		vector<unsigned int>&,double&
//����ֵ��		��
void CFactor::SetFactorRow(const fidlist& ValueIDs, fval_t fRowValue)
{
	//��ӵ������е��б�
	m_FactorRows.emplace_back(ValueIDs, fRowValue);
}

void CFactor::SetFactorRow(fidlist&& ValueIDs, fval_t fRowValue)
{
	//��ӵ������е��б�
	m_FactorRows.emplace_back(ValueIDs, fRowValue);
}