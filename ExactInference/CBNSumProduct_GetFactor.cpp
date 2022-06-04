////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct_GetFactor.cpp
// ��ȡ����ֵ
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


//�������ӵ�ֵ
fval_t CBNSumProduct::GetFactor(
	fid_t nNodeID,					//�ڵ�ID
	fid_t nValueID,					//�ڵ�ֵID
	const GVarList& QueryVariables)	//��ѯ�����б�
const {

	const BNNode& theNode = m_Nodes[nNodeID];
	//�������ڵ�ID����ȡ��ֵID
	fidlist ValueIDs = theNode.ParentIDs | std::views::transform([&](auto t) { return GetValueID(t, QueryVariables); }) | qy::views::to<fidlist>;

	//�ڵ�ǰ�ڵ��CPT�в���
	size_t result = qy::ranges::index_of(theNode.CPTRowIDs, qy::concat(ValueIDs, nValueID), &CPTRow::ValueIDs);
	return theNode.CPTRowValues[result];
}

//��ȡֵID
fid_t CBNSumProduct::GetValueID(fid_t nNodeID,		//�ڵ�ID
	const GVarList& QueryVariables)	//��ѯ�����б�
const {
	auto result = std::ranges::find(QueryVariables, nNodeID, &GroundingVariable::nNodeID);
	return result->nValueID;
}