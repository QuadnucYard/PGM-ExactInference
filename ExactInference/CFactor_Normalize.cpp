/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CFactor_Normalize.cpp
//��  �ܣ�		�淶������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��15��
//��  �£�		2021��03��23��
//��  �£�		2021��03��29��
//��  �ȣ�		40��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CFactor.h"								//������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�
#include <algorithm>
#include "stl_utils.h"

//��  �ƣ�		Normalize()
//��  �ܣ�		�淶������
//��  ����		��
//����ֵ��		��
void CFactor::Normalize()
{
	//�������������У������һ������
	//�ۼ���������ֵ
	double fNormalization = qy::sum(m_FactorRows.begin(), m_FactorRows.end(),
		[](const FACTOR_ROW& y) { return y.fValue; });
	//��һ��
	std::ranges::for_each(m_FactorRows, [=](FACTOR_ROW& r) { r.fValue /= fNormalization; });
}