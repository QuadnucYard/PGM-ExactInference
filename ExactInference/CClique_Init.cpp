/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CClique_Init.cpp
//��  �ܣ�		��ʼ�����������ñ���ID�б�����
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��31��
//��  �£�		2021��04��12��
//��  �£�		2021��05��18��
//��  �ȣ�		60��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CClique.h"								//����ͷ�ļ�


//��  �ƣ�		SetCliqueID()
//��  �ܣ�		������ID
//��  ����		unsigned int&
//����ֵ��		��
void CClique::SetCliqueID(unsigned int& nCliqueID)
{
	//������ID
	m_nCliqueID = nCliqueID;
}

//��  �ƣ�		SetVariableIDs()
//��  �ܣ�		���ñ���ID�б�
//��  ����		vector<unsigned int>&
//����ֵ��		��
void CClique::SetCliqueVariableIDs(vector<unsigned int>& VariableIDs)
{
	//��ʼ�����б���ID���б�
	m_VariableIDs = VariableIDs;
}

//��  �ƣ�		SetCliqueRow()
//��  �ܣ�		��������
//��  ����		vector<unsigned int>&,double&
//����ֵ��		��
void CClique::SetCliqueRow(vector<unsigned int>& ValueIDs, double& fRowValue)
{
	//��������
	CLIQUE_ROW clique_row;

	//����ֵID���б�
	clique_row.ValueIDs = ValueIDs;
	//���������е�ֵ
	clique_row.fValue = fRowValue;

	//��ӵ����е��б�
	m_CliqueRows.push_back(clique_row);
}