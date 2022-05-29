/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CBNSumProduct_Query.cpp
//功  能：		查询
//开发者：		高志强
//日  期：		2021年03月24日
//更  新：		
//长  度：		70行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


//查询
void CBNSumProduct::Query()
{
	//遍历所有查询进行推理
	for (const QUERY& q : m_Queries)
	{
		//Preprocess_Query(m_Queries[i]);
		//调用查询的辅助函数
		Query_Helper(q, m_Factors);
	}
	//输出查询结果
	OutputToXML();
}