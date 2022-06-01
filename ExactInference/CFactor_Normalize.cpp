/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CFactor_Normalize.cpp
//功  能：		规范化因子
//开发者：		高志强
//日  期：		2021年03月15日
//更  新：		2021年03月23日
//更  新：		2021年03月29日
//长  度：		40行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CFactor.h"


void CFactor::Normalize()
{
	//遍历所有因子行，累计所有因子值，计算归一化因子
	double fNormalization = qy::ranges::sum(m_FactorRows, &FACTOR_ROW::fValue);
	//归一化
	std::ranges::for_each(m_FactorRows, [=](FACTOR_ROW& r) { r.fValue /= fNormalization; });
}