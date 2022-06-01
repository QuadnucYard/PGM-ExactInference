////////////////////////////////////////////////////////////////////////////////
// CFactor_Normalize.cpp
// �淶������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CFactor.h"


void CFactor::Normalize()
{
	//�������������У��ۼ���������ֵ�������һ������
	double fNormalization = qy::ranges::sum(m_FactorRows, &FactorRow::fValue);
	//��һ��
	std::ranges::for_each(m_FactorRows, [=](FactorRow& r) { r.fValue /= fNormalization; });
}