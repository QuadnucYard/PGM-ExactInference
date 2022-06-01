/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CClique_Normalize.cpp
//功  能：		规范化团
//开发者：		高志强
//日  期：		2021年03月31日
//更  新：	    2021年04月12日
//更  新：		2021年05月18日
//长  度：		40行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CClique.h"								//团类头文件


//规范化团
void CClique::Normalize()
{
	double fNormalization = qy::ranges::sum(m_CliqueRows, &CLIQUE_ROW::fValue);
	std::ranges::for_each(m_CliqueRows, [=](CLIQUE_ROW& r) { r.fValue /= fNormalization; });
}