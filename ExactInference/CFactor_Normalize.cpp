/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CFactor_Normalize.cpp
//功  能：		规范化因子
//开发者：		高志强
//日  期：		2021年03月15日
//更  新：		2021年03月23日
//更  新：		2021年03月29日
//长  度：		40行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CFactor.h"								//因子类头文件
#include "Helper.h"									//辅助函数头文件
#include <algorithm>
#include "stl_utils.h"

//名  称：		Normalize()
//功  能：		规范化因子
//参  数：		无
//返回值：		无
void CFactor::Normalize()
{
	//遍历所有因子行，计算归一化因子
	//累计所有因子值
	double fNormalization = qy::sum(m_FactorRows.begin(), m_FactorRows.end(),
		[](const FACTOR_ROW& y) { return y.fValue; });
	//归一化
	std::ranges::for_each(m_FactorRows, [=](FACTOR_ROW& r) { r.fValue /= fNormalization; });
}