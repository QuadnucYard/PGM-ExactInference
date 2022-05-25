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


//��  �ƣ�		SumOutVariable()
//��  �ܣ�		���ݸ������������������
//��  ����		unsigned int
//����ֵ��		��
void CFactor::SumOutVariable(unsigned int nVariableID)
{
	//���ұ���ID�Ƿ���������
	unsigned int nRemovePos = 0;
	//���ø�������
	bool bFind = IsINTInVector(nVariableID, m_VariableIDs, nRemovePos);
	
	
	//����Ƿ��ҵ�����ID
	if (bFind)//�ҵ�����ID����Ҫ������ͻ���
	{
		/////////////////////////////////////////////////////////////////////
		//����1���������ID���б�
		vector<unsigned int>::iterator it = m_VariableIDs.begin();
		//���岢��ʼ����ǰλ��
		unsigned int nCurrPos = 0;

		//ѭ���жϣ���ɾ��
		while (it != m_VariableIDs.end())
		{
			//����Ƿ�ָ��λ��
			if (nCurrPos == nRemovePos)
			{
				//ɾ���ڵ�
				it = m_VariableIDs.erase(it);

				//��ֹѭ��
				break;
			}
			else
			{
				//����λ��
				nCurrPos++;

				//���µ�����
				it++;
			}
		}


		///////////////////////////////////////////////////////////////////////
		//����2���������ֵ��ID�б�
		for (unsigned int i = 0; i < m_FactorRows.size(); i++)
		{
			//ɾ����������ı���ֵ
			vector<unsigned int>::iterator it = m_FactorRows[i].ValueIDs.begin();
			//���岢��ʼ����ǰλ��
			unsigned int nCurrPos = 0;

			//ѭ���жϣ���ɾ��
			while (it != m_FactorRows[i].ValueIDs.end())
			{
				//����Ƿ�ָ��λ��
				if (nCurrPos == nRemovePos)
				{
					//ɾ������
					it = m_FactorRows[i].ValueIDs.erase(it);

					//��ֹѭ��
					break;
				}
				else
				{
					//����λ��
					nCurrPos++;

					//���µ�����
					it++;
				}
			}
		}
	
		//////////////////////////////////////////////////////////////////
		//����3������������Ӧ�������
		//�����µ������е��б�
		vector<FACTOR_ROW> FactorRows;
		while (m_FactorRows.size()>0)
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
	vector<FACTOR_ROW>::iterator it = m_FactorRows.begin();

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
		}
		else
		{
			//���µ�����
			it++;
		}
	}
}