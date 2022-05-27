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
#include <algorithm>
#include "stl_utils.h"

//��  �ƣ�		ReduceGivenVariable()
//��  �ܣ�		���ݸ����ı���ID��ֵID����������
//��  ����		unsigned int,unsigned int
//����ֵ��		��
void CFactor::ReduceGivenVariable(fid_t nVariableID, fid_t nValueID)
{
	//���ұ���ID�Ƿ���������
	if (size_t nPos = qy::index_of(m_VariableIDs, nVariableID); nPos != -1)
	{
		//�ҵ�����Ҫ���м�
		//���������С�����ض�λ�ã��У��ı���ֵ�Ƿ����
		//ɾ�� nValueID != it->ValueIDs[nPos] ����
		qy::remove_if(m_FactorRows, [=](const FACTOR_ROW& t) {return t[nPos] != nValueID; });
	}
}