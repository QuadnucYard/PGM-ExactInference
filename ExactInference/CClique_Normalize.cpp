////////////////////////////////////////////////////////////////////////////////
// CClique_Normalize.cpp
// �淶����
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CClique.h"


//�淶����
void CClique::Normalize()
{
	double fNormalization = qy::ranges::sum(m_CliqueRows, &CliqueRow::fValue);
	std::ranges::for_each(m_CliqueRows, [=](CliqueRow& r) { r.fValue /= fNormalization; });
}