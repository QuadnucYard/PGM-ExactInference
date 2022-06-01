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
#include "Helper.h"									//辅助函数头文件


//名  称：		Normalize()
//功  能：		规范化团
//参  数：		无
//返回值：		无
void CClique::Normalize()
{
	//遍历所有团行，计算归一化团
	double fNormalization = 0.0f;
	for (unsigned int i = 0; i < m_CliqueRows.size(); i++)
	{
		//累计所有团行值
		fNormalization += m_CliqueRows[i].fValue;
	}

	//归一化
	for (unsigned int i = 0; i < m_CliqueRows.size(); i++)
	{
		//归一化概率
		m_CliqueRows[i].fValue /= fNormalization;
	}
}