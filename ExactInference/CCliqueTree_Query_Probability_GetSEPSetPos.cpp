/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_Query_Probability_GetSEPSetPos.cpp
//��  �ܣ�		��ȡ���λ��
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��12��
//��  �£�		
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		GetSEPSetPos()
//��  �ܣ�		��ȡ�λ��
//��  ����		unsigned int,unsigned int
//����ֵ��		unsigned int
unsigned int CCliqueTree::GetSEPSetPos(unsigned int nID, unsigned int nChildID)
{
	//�������и
	for (unsigned int i = 0; i < m_SEPSets.size(); i++)
	{
		//�����Ƿ����
		if ((m_SEPSets[i].nStartID == nID && m_SEPSets[i].nEndID == nChildID) || //������������
			(m_SEPSets[i].nStartID == nChildID && m_SEPSets[i].nEndID == nID))
		{
			//����Ƿ����
			if (m_SEPSets[i].bReady == true)
			{
				//���ظλ��
				return i;
			}
		}
	}

	//��ʾ���㷨һ�����ҵ��
}