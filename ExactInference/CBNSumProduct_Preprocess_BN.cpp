////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_Preprocess_BN.cpp
// Ԥ����Ҷ˹����ṹ�����
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


//Ԥ����Ҷ˹����ṹ�����
void CBNSumProduct::Preprocess_BN()
{
	//�������нڵ㣬�����������ʷֲ�CPT
	for (BN_NODE& node : m_Nodes)
	{
		size_t nRow = 0;								//��CPT��ĵ�0�п�ʼ
		Arrange(node.nID, fidlist(), qy::concat(node.ParentIDs, node.nID), 0, nRow);	//0��ʾ����ֵ����ʼλ�á�
	}
}

//�Ը��ڵ��ID����ȡֵ��������
void CBNSumProduct::Arrange(
	fid_t nNodeID,			//��ǰ�ڵ�ID
	const fidlist& ValueIDs,//����ֵID������
	const fidlist& NodeIDs,	//�ڵ�ID����
	size_t nPos,			//��ǰ�ڵ�IDλ�ã��ӵ�0�п�ʼ
	size_t& nRow)			//��ǰ�к�
{
	//���ݹ��Ƿ����
	if (nPos == NodeIDs.size())
	{
		//��ӵ��ڵ��CPT
		m_Nodes[nNodeID].CPTRowIDs.emplace_back(ValueIDs, m_Nodes[nNodeID].CPTRowValues[nRow++]);
		return;
	}

	//ȡ�׽ڵ�
	size_t nNumberOfValues = m_Nodes[NodeIDs[nPos]].nNumberOfValues;
	//�������нڵ�ֵ
	for (size_t i = 0; i < nNumberOfValues; i++)
	{
		fidlist NewValueIDs = ValueIDs;
		NewValueIDs.push_back(i);
		//�ݹ����
		Arrange(nNodeID, NewValueIDs, NodeIDs, nPos + 1, nRow);
	}
}