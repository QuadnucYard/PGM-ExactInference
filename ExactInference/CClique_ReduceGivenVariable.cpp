/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CClique_ReduceGivenVariable.cpp
//��  �ܣ�		���ݸ����ı�����ֵ�������š����ڼ����������ʷֲ�
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��31��
//��  �£�		2021��04��12��
//��  �£�		2021��05��18��
//��  �ȣ�		50��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CClique.h"								//����ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		ReduceGivenVariable()
//��  �ܣ�		���ݸ����ı���ID��ֵID��������
//��  ����		unsigned int,unsigned int
//����ֵ��		��
void CClique::ReduceGivenVariable(unsigned int nVariableID, unsigned int nValueID)
{
	//���ұ���ID�Ƿ�������
	unsigned int nPos = 0;
	bool bFind = IsINTInVector(nVariableID, m_VariableIDs, nPos);//����ҵ����򷵻����б��е�λ��nPos
	//����Ƿ��ҵ�
	if (bFind)//�ҵ�����Ҫ���м�
	{
		//���������С�����ض�λ�ã��У��ı���ֵ�Ƿ����
		vector<CLIQUE_ROW>::iterator it = m_CliqueRows.begin();
		while (it != m_CliqueRows.end())
		{
			//������ֵ�Ƿ����
			if (nValueID == it->ValueIDs[nPos])
			{
				//�����С����µ�����
				it++;
			}
			else
			{
				//ɾ���С������µ�����
				it = m_CliqueRows.erase(it);
			}
		}
	}
}