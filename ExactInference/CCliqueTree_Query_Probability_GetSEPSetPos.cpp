/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CCliqueTree_Query_Probability_GetSEPSetPos.cpp
//功  能：		获取割集的位置
//开发者：		高志强
//日  期：		2021年04月12日
//更  新：		
//长  度：		70行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		GetSEPSetPos()
//功  能：		获取割集位置
//参  数：		unsigned int,unsigned int
//返回值：		unsigned int
size_t CCliqueTree::GetSEPSetPos(fid_t nID, fid_t nChildID)
{
	//nChildID为父
	return qy::ranges::index_of_if(m_SEPSets, [=](const SEP_SET& s) {
		return (s.nStartID == nID && s.nEndID == nChildID || s.nStartID == nChildID && s.nEndID == nID)
			&& s.bReady; //检查边是否相等, 割集是否就绪
	});
}