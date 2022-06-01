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
size_t CCliqueTree::GetSEPSetPos(fid_t nID, fid_t nChildID)
{
	//nChildIDΪ��
	return qy::ranges::index_of_if(m_SEPSets, [=](const SEP_SET& s) {
		return (s.nStartID == nID && s.nEndID == nChildID || s.nStartID == nChildID && s.nEndID == nID)
			&& s.bReady; //�����Ƿ����, ��Ƿ����
	});
}