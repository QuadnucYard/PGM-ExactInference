/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CFactor_Normalize.cpp
//��  �ܣ�		�淶������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��15��
//��  �£�		2021��03��23��
//��  �£�		2021��03��29��
//��  �ȣ�		40��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CFactor.h"


void CFactor::Normalize()
{
	//�������������У��ۼ���������ֵ�������һ������
	double fNormalization = qy::ranges::sum(m_FactorRows, &FACTOR_ROW::fValue);
	//��һ��
	std::ranges::for_each(m_FactorRows, [=](FACTOR_ROW& r) { r.fValue /= fNormalization; });
}