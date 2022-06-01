/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CBNSumProduct_Preprocess_BN.cpp
//��  �ܣ�		Ԥ����Ҷ˹����ṹ�����
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��09��
//��  �£�		2021��03��23��
//��  �ȣ�		90��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CBNSumProduct.h"							//��Ҷ˹���羫ȷ������ͷ�ļ������úͻ�����������


//��  �ƣ�		Preprocess_BN()
//��  �ܣ�		Ԥ����Ҷ˹����ṹ�����
//��  ����		��
//����ֵ��		��
void CBNSumProduct::Preprocess_BN()
{
	//�������нڵ㣬�����������ʷֲ�CPT
	for (unsigned int i = 0; i < m_Nodes.size(); i++)
	{
		//����ڵ�ĸ��ڵ�ID��ȡֵ������
		vector<unsigned int> NodeIDs = m_Nodes[i].ParentIDs;
		//��ӵ�ǰ�ڵ�ID���Ա��γ�����
		NodeIDs.push_back(m_Nodes[i].nID);

		//���常�ڵ�ȡֵ
		unsigned int nRow = 0;									//��CPT��ĵ�0�п�ʼ
		vector<unsigned int> ValueIDs;							//ֵID�ı��͸����Ľڵ�ID˳����ͬ
		Arrange(m_Nodes[i].nID, ValueIDs, NodeIDs, 0, nRow);	//0��ʾ����ֵ����ʼλ�á�
	}
}

//��  �ƣ�		Arrange()
//��  �ܣ�		�Ը��ڵ��ID����ȡֵ��������
//��  ����		unsigned int,vector<unsigned int>,vector<unsigned int>,unsigned int,unsigned int&
//����ֵ��		��
void CBNSumProduct::Arrange(unsigned int nNodeID,		//��ǰ�ڵ�ID
						vector<unsigned int> ValueIDs,  //����ֵID������
						vector<unsigned int> NodeIDs,	//�ڵ�ID����
						unsigned int nPos,				//��ǰ�ڵ�IDλ�ã��ӵ�0�п�ʼ
						unsigned int& nRow)				//��ǰ�к�
{
	//���ݹ��Ƿ����
	if (nPos == NodeIDs.size())
	{
		//��ȡ�ڵ�ֵ��
		CPT_ROW cpt_row;
		cpt_row.ValueIDs = ValueIDs;
		cpt_row.fProb = m_Nodes[nNodeID].CPTRowValues[nRow];

		//��ӵ��ڵ��CPT
		m_Nodes[nNodeID].CPTRowIDs.push_back(cpt_row);

		//�����к�
		nRow++;

		//����
		return;
	}

	//ȡ�׽ڵ�
	unsigned int nCurrID = NodeIDs[nPos];

	//��ȡ��ֵ�ĸ���
	unsigned int nNumberOfValues = m_Nodes[nCurrID].nNumberOfValues;
	//�������нڵ�ֵ
	for (unsigned int i = 0; i < nNumberOfValues; i++)
	{
		//�����µ�ֵID�б�
		vector<unsigned int> NewValueIDs = ValueIDs;
		//���ֵ
		NewValueIDs.push_back(i);
		
		//�����µ�λ��
		unsigned int nNewPos = nPos + 1;

		//�ݹ����
		Arrange(nNodeID, NewValueIDs, NodeIDs, nNewPos, nRow);
	}
}