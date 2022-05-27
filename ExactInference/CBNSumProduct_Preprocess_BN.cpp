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
	for (BN_NODE& node : m_Nodes)
	{
		//����ڵ�ĸ��ڵ�ID��ȡֵ������
		fidlist NodeIDs = node.ParentIDs;
		//��ӵ�ǰ�ڵ�ID���Ա��γ�����
		NodeIDs.push_back(node.nID);

		//���常�ڵ�ȡֵ
		size_t nRow = 0;									//��CPT��ĵ�0�п�ʼ
		Arrange(node.nID, fidlist(), NodeIDs, 0, nRow);	//0��ʾ����ֵ����ʼλ�á�
	}
}

//��  �ƣ�		Arrange()
//��  �ܣ�		�Ը��ڵ��ID����ȡֵ��������
//��  ����		unsigned int,vector<unsigned int>,vector<unsigned int>,unsigned int,unsigned int&
//����ֵ��		��
void CBNSumProduct::Arrange(
	fid_t nNodeID,		//��ǰ�ڵ�ID
	const fidlist& ValueIDs,  //����ֵID������
	const fidlist& NodeIDs,	//�ڵ�ID����
	size_t nPos,				//��ǰ�ڵ�IDλ�ã��ӵ�0�п�ʼ
	size_t& nRow)				//��ǰ�к�
{
	//���ݹ��Ƿ����
	if (nPos == NodeIDs.size())
	{
		//��ӵ��ڵ��CPT
		m_Nodes[nNodeID].CPTRowIDs.push_back(CPT_ROW(ValueIDs, m_Nodes[nNodeID].CPTRowValues[nRow]));
		//�����к�
		nRow++;
		return;
	}

	//ȡ�׽ڵ�
	fid_t nCurrID = NodeIDs[nPos];

	size_t nNumberOfValues = m_Nodes[nCurrID].nNumberOfValues;
	//�������нڵ�ֵ
	for (size_t i = 0; i < nNumberOfValues; i++)
	{
		fidlist NewValueIDs = ValueIDs;
		NewValueIDs.push_back(i);

		//�ݹ����
		Arrange(nNodeID, NewValueIDs, NodeIDs, nPos + 1, nRow);
	}
}