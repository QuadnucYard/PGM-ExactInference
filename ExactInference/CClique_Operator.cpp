/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CClique_Operator.cpp
//��  �ܣ�		���ز�������ء���Ҫ�����ӻ����������������ӳ�
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��31��
//��  �£�		2021��04��12��
//��  �£�		2021��05��18��
//��  �ȣ�		50��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CClique.h"								//����ͷ�ļ�


//��  �ƣ�		IsConsistentValueID()
//��  �ܣ�		����������е�ֵID�Ƿ���ݣ������жϳ˻�ʱ�ܷ�ϲ�
//��  ����		const FACTOR_ROW&, 
//				const FACTOR_ROW&, 
//				map<unsigned int, unsigned int>&
//����ֵ��		bool
bool CClique::IsConsistentValueID(const CLIQUE_ROW& FirstRow, const CLIQUE_ROW& SecondRow, map<unsigned int, unsigned int>& FirstToSeconds)
{
	//����������ͬ����λ�õ�ӳ��
	for (map<unsigned int, unsigned int>::iterator it = FirstToSeconds.begin(); it != FirstToSeconds.end(); it++)
	{
		//��ȡλ��
		unsigned int nFirstPos = it->first;		//��λ��
		unsigned int nSecondPos = it->second;	//βλ��

		//������ֵ��ID�Ƿ����
		if (FirstRow.ValueIDs[nFirstPos] != SecondRow.ValueIDs[nSecondPos])
		{
			//���ؼ�
			return false;
		}
	}

	//ȱʡ������
	return true;
}

//�������ӻ�
CClique CClique::operator*(const CClique& second)
{
	//�����µġ������ص�������
	CClique clique;

	////////////////////////////////////////////////////////////////////////
	//ע�⣺�����ӻ���Ҫ������ID�����ǲ���ģ�������Ӳ�ͬ�������Ƕ�̬�仯��
	clique.m_nCliqueID = m_nCliqueID;
	////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//����1���������ŵĽ�������ͬ����ID�ļ���		
	//������ͬ����ID���ӵ����ŵ���β��λ�õ�ӳ�䡣�����3��������Ӧ�ڵ�5������
	map<unsigned int, unsigned int> FirstToSeconds;

	//����1.1���������ŵı���ID
	for (unsigned int i = 0; i < m_VariableIDs.size(); i++)
	{
		//��ȡ�ױ���ID
		unsigned int nFirstVariableID = m_VariableIDs[i];

		//����β�ŵı���ID
		for (unsigned int j = 0; j < second.m_VariableIDs.size(); j++)
		{
			//��ȡβ����ID
			unsigned int nSecondVariableID = second.m_VariableIDs[j];

			//�����������ID�Ƿ����
			if (nFirstVariableID == nSecondVariableID)
			{
				//��ӵ���ͬ������������ָ��β�ŵ�λ��ӳ��
				//ע�⣺���ô�λ�õ�λ�õ�ӳ�䣬�����Ǵӱ���ID������ID��ӳ��
				FirstToSeconds.insert(make_pair(i, j));
			}
		}
	}

	//����1.2����ȡβ���к�������ͬ������λ�ü���
	set<unsigned int> RedundantSeconds;
	for (map<unsigned int, unsigned int>::iterator it = FirstToSeconds.begin(); it != FirstToSeconds.end(); it++)
	{
		//��ӵ���ͬ������λ�ü���
		RedundantSeconds.insert(it->second);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//����2��ֱ��ƴ��
	//����Ƿ�����ͬ����ID
	if (FirstToSeconds.size() == 0)//���һ��������û����ͬ��������ֱ��ƴ��
	{
		//����2.1��ֱ��ƴ�ӱ���ֵID
		for (unsigned int i = 0; i < m_CliqueRows.size(); i++)
		{
			for (unsigned int j = 0; j < second.m_CliqueRows.size(); j++)
			{
				//�����µ�����
				CLIQUE_ROW clique_row;

				//��ӱ���ֵ��ID����
				clique_row.ValueIDs = m_CliqueRows[i].ValueIDs;//��������ֵ������
				//���β��ֵ������
				for (unsigned int m = 0; m < second.m_CliqueRows[j].ValueIDs.size(); m++)
				{
					//���β��ֵ��ID
					clique_row.ValueIDs.push_back(second.m_CliqueRows[j].ValueIDs[m]);
				}

				//�������е�ֵ����Ҫ���ó˷�
				clique_row.fValue = m_CliqueRows[i].fValue * second.m_CliqueRows[j].fValue;

				//��������ӵ���
				clique.m_CliqueRows.push_back(clique_row);
			}
		}

		//����2.2��ƴ�ӱ���ID
		clique.m_VariableIDs = m_VariableIDs;//��ʼ��Ϊ���ŵı���ID����
		//���β�ŵı���ID
		for (unsigned int i = 0; i < second.m_VariableIDs.size(); i++)
		{
			//���β�ŵı���ID
			clique.m_VariableIDs.push_back(second.m_VariableIDs[i]);
		}
	}
	////////////////////////////////////////////////////////////////////
	//����3�����ƴ��
	else //�����������������ͬ����������ƴ��
	{
		//����3.1�����ƴ��
		for (unsigned int i = 0; i < m_CliqueRows.size(); i++)
		{
			for (unsigned int j = 0; j < second.m_CliqueRows.size(); j++)
			{
				//����Ӧ�ı���ֵ��ID�Ƿ����
				if (IsConsistentValueID(m_CliqueRows[i], second.m_CliqueRows[j], FirstToSeconds))
				{
					//����������
					CLIQUE_ROW clique_row;
					clique_row.ValueIDs = m_CliqueRows[i].ValueIDs;//��ʼ�����е�ֵID����
					//����β�ŵ�ֵ
					for (unsigned int m = 0; m < second.m_CliqueRows[j].ValueIDs.size(); m++)
					{
						//������Ƿ�����ͬ����������
						if (!qy::ranges::includes(RedundantSeconds, m))
						{
							//���β�ŵ���
							clique_row.ValueIDs.push_back(second.m_CliqueRows[j].ValueIDs[m]);
						}
					}

					//�����ȡ���е�ֵ
					clique_row.fValue = m_CliqueRows[i].fValue * second.m_CliqueRows[j].fValue;

					//��������е�����
					clique.m_CliqueRows.push_back(clique_row);
				}
			}
		}

		//����3.2����ӱ���ID���б�
		clique.m_VariableIDs = m_VariableIDs;
		//����β��
		for (unsigned int i = 0; i < second.m_VariableIDs.size(); i++)
		{
			//���β�ű���ID��λ���Ƿ�������ͬ����ID����
			if (!qy::ranges::includes(RedundantSeconds, i))
			{
				//���β�ŵı���ID
				clique.m_VariableIDs.push_back(second.m_VariableIDs[i]);
			}
		}
	}

	//������
	return clique;
};

CClique CClique::operator/(const CClique& second)
{
	//�����µġ������ص���
	CClique clique;

	///////////////////////////
	//ע�⣺�������еı�����
	clique.m_VariableIDs = m_VariableIDs;
	///////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//����1���������ŵĽ�������ͬ����ID�ļ���		
	//������ͬ����ID���ӵ������ӵ���β����λ�õ�ӳ�䡣�����3��������Ӧ�ڵ�5������
	map<unsigned int, unsigned int> FirstToSeconds;

	//����1.1�����������ӵı���ID
	for (unsigned int i = 0; i < m_VariableIDs.size(); i++)
	{
		//��ȡ�ױ���ID
		unsigned int nFirstVariableID = m_VariableIDs[i];

		//����β���ӵı���ID
		for (unsigned int j = 0; j < second.m_VariableIDs.size(); j++)
		{
			//��ȡβ����ID
			unsigned int nSecondVariableID = second.m_VariableIDs[j];

			//�����������ID�Ƿ����
			if (nFirstVariableID == nSecondVariableID)
			{
				//��ӵ���ͬ��������������ָ��β���ӵ�λ��ӳ��
				//ע�⣺���ô�λ�õ�λ�õ�ӳ�䣬�����Ǵӱ���ID������ID��ӳ��
				FirstToSeconds.insert(make_pair(i, j));
			}
		}
	}

	//����1.2����ȡβ�����к���������ͬ������λ�ü���
	set<unsigned int> RedundantSeconds;
	for (map<unsigned int, unsigned int>::iterator it = FirstToSeconds.begin(); it != FirstToSeconds.end(); it++)
	{
		//��ӵ���ͬ������λ�ü���
		RedundantSeconds.insert(it->second);
	}

	/////////////////////////////////////////////////////////////////////////////////
	//����2�����ӳ�
	//˵���������ŵ�Ͻ��һ���������ŵ�Ͻ��
	for (unsigned int i = 0; i < m_CliqueRows.size(); i++)
	{
		for (unsigned int j = 0; j < second.m_CliqueRows.size(); j++)
		{
			//����Ӧ�ı���ֵ��ID�Ƿ����
			if (IsConsistentValueID(m_CliqueRows[i], second.m_CliqueRows[j], FirstToSeconds))
			{
				//��������
				CLIQUE_ROW clique_row;

				//��ʼ�����е�ֵID����
				clique_row.ValueIDs = m_CliqueRows[i].ValueIDs;
				//�����ȡ�����е�ֵ
				clique_row.fValue = m_CliqueRows[i].fValue / second.m_CliqueRows[j].fValue;

				//������е���
				clique.m_CliqueRows.push_back(clique_row);
			}
		}
	}

	//������
	return clique;
};