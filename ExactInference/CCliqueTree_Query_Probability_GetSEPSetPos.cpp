////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_Query_Probability_GetSEPSetPos.cpp
// 获取割集的位置
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//获取割集位置
const CutSet& CCliqueTree::GetReadySEPSet(fid_t nID, fid_t nChildID) const
{
	//nChildID为父
	return *std::ranges::find_if(m_SEPSets, [=](const CutSet& s) {
		return (s.nStartID == nID && s.nEndID == nChildID || s.nStartID == nChildID && s.nEndID == nID)
			&& s.bReady; //检查边是否相等, 割集是否就绪
	});
}