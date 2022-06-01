////////////////////////////////////////////////////////////////////////////////
// CClique_Query.cpp
// 查询
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//查询
void CCliqueTree::Query()
{
	//遍历所有查询进行推理
	for (unsigned int i = 0; i < m_CTQueries.size(); i++)
	{
		//调用查询的辅助函数
		Query_Helper(m_CTQueries[i]);
	}

	//输出查询结果
	OutputToXML();
}