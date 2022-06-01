/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CFactor_Operator.cpp
//��  �ܣ�		���ز�������ء���Ҫ�����ӻ�
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��12��
//��  �£�		2021��03��13��
//��  �£�		2021��03��23��
//��  �£�		2021��03��29��
//��  �ȣ�		50��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CFactor.h"								//������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		IsConsistentValueID()
//��  �ܣ�		������������е�ֵID�Ƿ���ݣ������жϳ˻�ʱ�ܷ�ϲ�
//��  ����		const FACTOR_ROW&, 
//				const FACTOR_ROW&, 
//				map<unsigned int, unsigned int>&
//����ֵ��		bool
bool CFactor::IsConsistentValueID(const FACTOR_ROW& FirstRow, const FACTOR_ROW& SecondRow, map<unsigned int, unsigned int>& FirstToSeconds)
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