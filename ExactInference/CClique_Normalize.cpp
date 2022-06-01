/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CClique_Normalize.cpp
//��  �ܣ�		�淶����
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��31��
//��  �£�	    2021��04��12��
//��  �£�		2021��05��18��
//��  �ȣ�		40��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CClique.h"								//����ͷ�ļ�


//�淶����
void CClique::Normalize()
{
	double fNormalization = qy::ranges::sum(m_CliqueRows, &CLIQUE_ROW::fValue);
	std::ranges::for_each(m_CliqueRows, [=](CLIQUE_ROW& r) { r.fValue /= fNormalization; });
}