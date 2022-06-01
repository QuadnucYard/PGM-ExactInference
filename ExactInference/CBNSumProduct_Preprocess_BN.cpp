////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_Preprocess_BN.cpp
// 预处理贝叶斯网络结构与参数
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


//预处理贝叶斯网络结构与参数
void CBNSumProduct::Preprocess_BN()
{
	//遍历所有节点，整理条件概率分布CPT
	for (BN_NODE& node : m_Nodes)
	{
		size_t nRow = 0;								//从CPT表的第0行开始
		Arrange(node.nID, fidlist(), qy::concat(node.ParentIDs, node.nID), 0, nRow);	//0表示变量值的起始位置。
	}
}

//对父节点的ID及其取值进行排列
void CBNSumProduct::Arrange(
	fid_t nNodeID,			//当前节点ID
	const fidlist& ValueIDs,//变量值ID的排列
	const fidlist& NodeIDs,	//节点ID排列
	size_t nPos,			//当前节点ID位置，从第0列开始
	size_t& nRow)			//当前行号
{
	//检查递归是否结束
	if (nPos == NodeIDs.size())
	{
		//添加到节点的CPT
		m_Nodes[nNodeID].CPTRowIDs.emplace_back(ValueIDs, m_Nodes[nNodeID].CPTRowValues[nRow++]);
		return;
	}

	//取首节点
	size_t nNumberOfValues = m_Nodes[NodeIDs[nPos]].nNumberOfValues;
	//遍历所有节点值
	for (size_t i = 0; i < nNumberOfValues; i++)
	{
		fidlist NewValueIDs = ValueIDs;
		NewValueIDs.push_back(i);
		//递归调用
		Arrange(nNodeID, NewValueIDs, NodeIDs, nPos + 1, nRow);
	}
}