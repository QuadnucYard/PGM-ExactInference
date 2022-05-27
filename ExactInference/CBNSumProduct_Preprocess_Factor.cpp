/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CBNSumProduct_Preprocess_Factor.cpp
//功  能：		预处理因子
//开发者：		高志强
//日  期：		2021年03月13日
//更  新：		2021年03月23日
//长  度：		70行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CBNSumProduct.h"							//贝叶斯网络精确推理类头文件，采用和积变量消除法
#include "Helper.h"									//辅助函数头文件


//名  称：		Preprocess_Factor()
//功  能：		预处理因子
//参  数：		无
//返回值：		无
void CBNSumProduct::Preprocess_Factor()
{
	//遍历BN中的所有节点
	for (BN_NODE& node : m_Nodes)
	{
		CFactor factor;

		//////////////////////////////////////////////////////////////
		//步骤1：初始化因子。设置因子的变量ID的列表
		fidlist NodeIDs = node.ParentIDs;	//父节点ID列表
		//添加本身节点的ID
		NodeIDs.push_back(node.nID);
		//初始化因子
		factor.SetFactorVariableIDs(NodeIDs);

		//////////////////////////////////////////////////////////////
		//步骤2：初始化因子。设置因子值的ID表
		for (CPT_ROW& row : node.CPTRowIDs)
		{
			factor.SetFactorRow(row.ValueIDs, row.fProb);
		}

		//添加到因子集合
		m_Factors.push_back(factor);
	}
}