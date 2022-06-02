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
	for (const CTQuery& q : m_CTQueries)
	{
		Query_Helper(q);
	}

#ifndef USE_YAML
	OutputToXML();
#else
	OutputToYAML();
#endif // !USE_YAML

}