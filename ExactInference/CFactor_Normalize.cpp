////////////////////////////////////////////////////////////////////////////////
// CFactor_Normalize.cpp
// 规范化因子
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CFactor.h"


void CFactor::Normalize()
{
	//遍历所有因子行，累计所有因子值，计算归一化因子
	double fNormalization = qy::ranges::sum(m_FactorRows, &FactorRow::fValue);
	//归一化
	std::ranges::for_each(m_FactorRows, [=](FactorRow& r) { r.fValue /= fNormalization; });
}