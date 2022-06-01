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
void CFactor::SetFactorVariableIDs(vector<unsigned int>& VariableIDs)
{
	//��ʼ�������б���ID���б�
	m_VariableIDs = VariableIDs;
}

//��  �ƣ�		SetFactorRow()
//��  �ܣ�		����������
//��  ����		vector<unsigned int>&,double&
//����ֵ��		��
void CFactor::SetFactorRow(vector<unsigned int>& ValueIDs, double& fRowValue)
{
	//����������
	FACTOR_ROW factor_row;
	
	//����ֵID���б�
	factor_row.ValueIDs = ValueIDs;
	//���������е�ֵ
	factor_row.fValue = fRowValue;

	//��ӵ������е��б�
	m_FactorRows.push_back(factor_row);
}