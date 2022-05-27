/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CFactor_SumOutVariable.cpp
//��  �ܣ�		���ݸ������������������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��13��
//��  �£�		2021��03��23��
//��  �£�		2021��03��29��
//��  �ȣ�		150��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CFactor.h"								//������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�
#include "stl_utils.h"
#include <algorithm>

//��  �ƣ�		SumOutVariable()
//��  �ܣ�		���ݸ������������������
//��  ����		unsigned int
//����ֵ��		��
void CFactor::SumOutVariable(unsigned int nVariableID)
{
	//����Ƿ��ҵ�����ID
	if (size_t nRemovePos = qy::index_of(m_VariableIDs, nVariableID); nRemovePos != -1) //�ҵ�����ID����Ҫ������ͻ���
	{
		/////////////////////////////////////////////////////////////////////
		//����1���������ID���б�
		//ɾ��nRemovePos��
		m_VariableIDs.erase(m_VariableIDs.begin() + nRemovePos);

		///////////////////////////////////////////////////////////////////////
		//����2���������ֵ��ID�б�
		/*for (size_t i = 0; i < m_FactorRows.size(); i++)
		{
			//ɾ����������ı���ֵ: i�е�nRemovePos��
			m_FactorRows[i].ValueIDs.erase(m_FactorRows[i].ValueIDs.begin() + nRemovePos);
		}*/
		std::for_each(m_FactorRows.begin(), m_FactorRows.end(),
			[=](FACTOR_ROW& t) { t.ValueIDs.erase(t.ValueIDs.begin() + nRemovePos); });

		//////////////////////////////////////////////////////////////////
		//����3������������Ӧ�������
		//�����µ������е��б�
		std::vector<FACTOR_ROW> FactorRows;
		while (m_FactorRows.size() > 0)
		{
			//��ȡ����
			FACTOR_ROW first_row = m_FactorRows[0];

			//������ֵ�ۼӵ�����
			MergeIntoFirstRow(first_row);

			//��ӵ������е��б�
			FactorRows.push_back(first_row);
		}

		//��Ҫ���������е��б�
		m_FactorRows = FactorRows;
	}
}

//��  �ƣ�		MergeIntoFirstRow()
//��  �ܣ�		�ۻ�����ֵ������
//��  ����		FACTOR_ROW&
//����ֵ��		��
void CFactor::MergeIntoFirstRow(FACTOR_ROW& first_row)
{
	//��������������
	std::vector<FACTOR_ROW>::iterator it = m_FactorRows.begin();

	//ɾ������
	it = m_FactorRows.erase(it);

	//����Ƿ����
	while (it != m_FactorRows.end())
	{
		//������ֵID���б��Ƿ����
		if (first_row.ValueIDs == it->ValueIDs)
		{
			//�ۼ�����ֵ
			first_row.fValue += it->fValue;

			//ɾ���������µ�����
			it = m_FactorRows.erase(it);
		} else
		{
			//���µ�����
			it++;
		}
	}
}