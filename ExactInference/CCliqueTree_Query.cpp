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
	for (unsigned int i = 0; i < m_CTQueries.size(); i++)
	{
		//���ò�ѯ�ĸ�������
		Query_Helper(m_CTQueries[i]);
	}

	//�����ѯ���
	OutputToXML();
}