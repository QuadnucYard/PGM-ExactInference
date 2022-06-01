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
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		Normalize()
//��  �ܣ�		�淶����
//��  ����		��
//����ֵ��		��
void CClique::Normalize()
{
	//�����������У������һ����
	double fNormalization = 0.0f;
	for (unsigned int i = 0; i < m_CliqueRows.size(); i++)
	{
		//�ۼ���������ֵ
		fNormalization += m_CliqueRows[i].fValue;
	}

	//��һ��
	for (unsigned int i = 0; i < m_CliqueRows.size(); i++)
	{
		//��һ������
		m_CliqueRows[i].fValue /= fNormalization;
	}
}