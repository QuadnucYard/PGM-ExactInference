/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CClique_SumOutVariable.cpp
//��  �ܣ�		���ݸ����������������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��31��
//��  �£�		2021��04��12��
//��  �£�		2021��05��18��
//��  �ȣ�		150��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CClique.h"								//����ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		SumOutVariable()
//��  �ܣ�		���ݸ����������������
//��  ����		unsigned int
//����ֵ��		��
void CClique::SumOutVariable(unsigned int nVariableID)
{
	//����Ƿ��ҵ�����ID
	if (size_t nRemovePos = qy::ranges::index_of(m_VariableIDs, nVariableID); nRemovePos != -1)//�ҵ�����ID����Ҫ������ͻ���
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
		for (unsigned int i = 0; i < m_CliqueRows.size(); i++)
		{
			//ɾ����������ı���ֵ
			vector<unsigned int>::iterator it = m_CliqueRows[i].ValueIDs.begin();
			//���岢��ʼ����ǰλ��
			unsigned int nCurrPos = 0;

			//ѭ���жϣ���ɾ��
			while (it != m_CliqueRows[i].ValueIDs.end())
			{
				//����Ƿ�ָ��λ��
				if (nCurrPos == nRemovePos)
				{
					//ɾ������
					it = m_CliqueRows[i].ValueIDs.erase(it);

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
		//����3����������Ӧ�������
		//�����µ����е��б�
		vector<CLIQUE_ROW> CliqueRows;
		while (m_CliqueRows.size()>0)
		{
			//��ȡ����
			CLIQUE_ROW first_row = m_CliqueRows[0];

			//������ֵ�ۼӵ�����
			MergeIntoFirstRow(first_row);

			//��ӵ����е��б�
			CliqueRows.push_back(first_row);
		}

		//��Ҫ�������е��б�
		m_CliqueRows = CliqueRows;
	}
}

//��  �ƣ�		MergeIntoFirstRow()
//��  �ܣ�		�ۻ�����ֵ������
//��  ����		FACTOR_ROW&
//����ֵ��		��
void CClique::MergeIntoFirstRow(CLIQUE_ROW& first_row)
{
	//������������
	vector<CLIQUE_ROW>::iterator it = m_CliqueRows.begin();

	//ɾ������
	it = m_CliqueRows.erase(it);

	//����Ƿ����
	while (it != m_CliqueRows.end())
	{
		//������ֵID���б��Ƿ����
		if (first_row.ValueIDs == it->ValueIDs)
		{
			//�ۼ�����ֵ
			first_row.fValue += it->fValue;

			//ɾ���������µ�����
			it = m_CliqueRows.erase(it);
		}
		else
		{
			//���µ�����
			it++;
		}
	}
}