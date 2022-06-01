////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_Query_Probability_GetSEPSetPos.cpp
// 获取割集的位置
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//获取割集位置
size_t CCliqueTree::GetSEPSetPos(fid_t nID, fid_t nChildID)
{
	//nChildID为父
	return qy::ranges::index_of_if(m_SEPSets, [=](const SEP_SET& s) {
		return (s.nStartID == nID && s.nEndID == nChildID || s.nStartID == nChildID && s.nEndID == nID)
			&& s.bReady; //检查边是否相等, 割集是否就绪
	});
}