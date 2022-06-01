////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_Query.cpp
// 查询
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
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