/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_BuildUpwardTree.cpp
//��  �ܣ�		��������ŵ���
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��01��
//��  �£�		2021��04��03��
//��  �£�		2021��05��18��
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		BuildUpwardTree()
//��  �ܣ�		��������ŵ���
//��  ����		unsigned int
//����ֵ��		��
//��  ʾ��		���ù�����������ķ�ʽ���죬�������ID
void CCliqueTree::BuildUpwardTree(fid_t nParentID)
{
	//����OPEN�б��CLOSED��
	queue <unsigned int> OPEN;
	set<unsigned int> CLOSED;

	//��ʼ��OPEN��
	OPEN.push(nParentID);

	//���OPEN���Ƿ�Ϊ��
	while (OPEN.size() > 0)
	{
		//����
		unsigned int nID = OPEN.front();
		OPEN.pop();
		
		//����CLOSED��
		CLOSED.insert(nID);

		//���Һ��
		multimap<unsigned int, unsigned int>::iterator beg = m_CTEdges.lower_bound(nID);
		multimap<unsigned int, unsigned int>::iterator end = m_CTEdges.upper_bound(nID);
		//����Ƿ���ں�̣����������
		while (beg != end)
		{
			//��ȡ��̽��
			unsigned int nChildID = beg->second;

			//����̽ڵ��Ƿ���CLOSED������Ѿ����ڣ�����Ҫ���
			if (!qy::ranges::includes(CLOSED,nChildID))
			{
				//��ӱߵ�����ŵ���
				m_UpwardTree.insert(make_pair(nChildID, nID));
				
				//��ӵ�OPEN��
				OPEN.push(nChildID);
			}

			//���µ�����
			beg++;
		}
	}
}