/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CClique_Query.cpp
//��  �ܣ�		��ѯ���е��ض����ʡ��������а���A��B��C����������ֻ���ȡA��B��C�ض�ȡֵ�ĸ��ʵȡ���Ҫ��������ID�б�ͱ���ֵ��ID�б�
//				����3�������Ĳ�ѯ����
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��31��
//��  �£�		2021��04��12��
//��  �£�		2021��05��18��
//��  �ȣ�		120��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CClique.h"								//����ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		Query()
//��  �ܣ�		��ѯ�ض�ֵ
//��  ����		vector<unsigned int>&,vector<unsigned int>&
//����ֵ��		double
double CClique::Query(vector<unsigned int>& VariableIDs, vector<unsigned int>& ValueIDs)
{
	//����λ�ü���
	vector<unsigned int> Positions;

	//������ѯ�ı���ID
	for (unsigned int i = 0; i < VariableIDs.size(); i++)
	{
		//�������ӵı���ID
		for (unsigned int j = 0; j < m_VariableIDs.size(); j++)
		{
			//������ID�Ƿ���ͬ
			if (VariableIDs[i] == m_VariableIDs[j])
			{
				//��ӵ�λ�ü���
				Positions.push_back(j);
			}
		}
	}


	//��ʼ�����صĸ���ֵ
	double fProb = 0.0f;

	//�������У����
	for (unsigned int i = 0; i < m_CliqueRows.size(); i++)
	{
		//��������
		CLIQUE_ROW factor_row = m_CliqueRows[i];

		//���λ�ú�ֵ�Ƿ���ȷ
		bool bMatch = true;

		//��������λ��
		for (unsigned int j = 0; j < Positions.size(); j++)
		{
			//��ȡλ��
			unsigned int nPos = Positions[j];		//��ȡλ��
			unsigned int nValue = ValueIDs[j];	//��ȡ����ֵ��ID
			//�������ȣ������ƥ����
			if (factor_row.ValueIDs[nPos] != nValue)
			{
				//����ƥ�����������ƺ�������ֹѭ��
				bMatch = false;
			}
		}

		//�������Ƿ�ƥ�䡣���ƥ��Ļ�������Ҫ�ۼӸ���ֵ
		if (bMatch == true)
		{
			//�ۼƸ���ֵ
			fProb += factor_row.fValue;
		}
	}

	//���ظ���
	return fProb;
}

//��  �ƣ�		GetCliqueVariableIDs()
//��  �ܣ�		��ȡ����ID�б�
//��  ����		��
//����ֵ��		unsigned int
vector<unsigned int> CClique::GetCliqueVariableIDs()
{
	//���ر���ID�б�
	return m_VariableIDs;
}

//��  �ƣ�		GetVariableIDs()
//��  �ܣ�		��ȡ����ID����
//��  ����		��
//����ֵ��		unsigned int
set <unsigned int> CClique::GetVariableIDs()
{
	set<unsigned int> VariableIDs;

	for (unsigned int i = 0; i < m_VariableIDs.size(); i++)
	{
		VariableIDs.insert(m_VariableIDs[i]);
	}
	
	//���ر���ID����
	return VariableIDs;
}

//��  �ƣ�		GetID()
//��  �ܣ�		��ȡ�ŵ�ID
//��  ����		��
//����ֵ��		unsigned int
unsigned int CClique::GetID()
{
	//�����ŵ�ID
	return m_nCliqueID;
}