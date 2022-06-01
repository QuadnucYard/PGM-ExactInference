////////////////////////////////////////////////////////////////////////////////
// CClique_Normalize.cpp
// 规范化团
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CClique.h"


//规范化团
void CClique::Normalize()
{
	double fNormalization = qy::ranges::sum(m_CliqueRows, &CliqueRow::fValue);
	std::ranges::for_each(m_CliqueRows, [=](CliqueRow& r) { r.fValue /= fNormalization; });
}