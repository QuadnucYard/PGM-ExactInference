/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_SendCliqueMessage_Downward.cpp
//��  �ܣ�		���·�������Ϣ
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��04��
//��  �£�		2021��05��18��
//��  �ȣ�		60��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//���·�������Ϣ
void CCliqueTree::SendCliqueMessage_Downward(unsigned int nID,unsigned int nChildID)
{	
	//�ҵ��ཻ�ı���ID����
	set<unsigned int> CommonVariableIDs;

	//��ȡ�����ŵı���ID����
	FindCommonVariableIDs(nID, nChildID, CommonVariableIDs);

	
}