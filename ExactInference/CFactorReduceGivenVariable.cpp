/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CFactor_ReduceGivenVariable.cpp
//��  �ܣ�		���ݸ����ı�����ֵ���������ӡ����ڼ����������ʷֲ�
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��13��
//��  �£�		2021��03��14��
//��  �£�		2021��03��23��
//��  �£�		2021��03��29��
//��  �ȣ�		50��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CFactor.h"								//������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		ReduceGivenVariable()
//��  �ܣ�		���ݸ����ı���ID��ֵID����������
//��  ����		unsigned int,unsigned int
//����ֵ��		��
void CFactor::ReduceGivenVariable(unsigned int nVariableID, unsigned int nValueID)
{
	//���ұ���ID�Ƿ���������
	unsigned int nPos = 0;
	bool bFind = IsINTInVector(nVariableID, m_VariableIDs,nPos);//����ҵ����򷵻����б��е�λ��nPos
	//����Ƿ��ҵ�
	if (bFind)//�ҵ�����Ҫ���м�
	{
		//���������С�����ض�λ�ã��У��ı���ֵ�Ƿ����
		vector<FACTOR_ROW>::iterator it = m_FactorRows.begin();
		while (it != m_FactorRows.end())
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
				it = m_FactorRows.erase(it);
			}
		}
	}
}