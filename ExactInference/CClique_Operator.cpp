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
#include "Helper.h"									//��������ͷ�ļ�


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