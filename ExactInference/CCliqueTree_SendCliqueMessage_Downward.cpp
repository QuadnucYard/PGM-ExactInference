/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_SendCliqueMessage_Downward.cpp
//��  �ܣ�		���·�������Ϣ
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��04��
//��  �£�		2021��05��18��
//��  �ȣ�		60��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		SendCliqueMessage_Downward()
//��  �ܣ�		���·�������Ϣ
//��  ����		unsigned int
//����ֵ��		��
void CCliqueTree::SendCliqueMessage_Downward(unsigned int nID,unsigned int nChildID)
{	
	//�ҵ��ཻ�ı���ID����
	set<unsigned int> CommonVariableIDs;

	//��ȡ�����ŵı���ID����
	FindCommonVariableIDs(nID, nChildID, CommonVariableIDs);

	
}