////////////////////////////////////////////////////////////////////////////////
// CClique_Query.cpp
// ��ѯ
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//��ѯ
void CCliqueTree::Query()
{
	//�������в�ѯ��������
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