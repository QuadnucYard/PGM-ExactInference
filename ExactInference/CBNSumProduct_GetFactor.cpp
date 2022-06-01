/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CBNSumProduct_GetFactor.cpp
//��  �ܣ�		��ȡ����ֵ
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��09��
//��  �£�		2021��03��24��
//��  �ȣ�		100��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBNSumProduct.h"


//�������ӵ�ֵ
fval_t CBNSumProduct::GetFactor(
	fid_t nNodeID,					//�ڵ�ID
	fid_t nValueID,					//�ڵ�ֵID
	const GVarList& QueryVariables)	//��ѯ�����б�
{

	const BN_NODE& theNode = m_Nodes[nNodeID];
	//�������ڵ�ID����ȡ��ֵID
	fidlist ValueIDs = theNode.ParentIDs | std::views::transform([&](auto t) { return GetValueID(t, QueryVariables); }) | qy::views::to<fidlist>;

	//�ڵ�ǰ�ڵ��CPT�в���
	size_t result = qy::ranges::index_of(theNode.CPTRowIDs, qy::concat(ValueIDs, nValueID), &CPT_ROW::ValueIDs);
	if (result != -1)
		return theNode.CPTRowValues[result];
	AfxMessageBox(_T("GetFactor()�쳣"));
	return 1.0f;
}

//��ȡֵID
fid_t CBNSumProduct::GetValueID(fid_t nNodeID,		//�ڵ�ID
	const GVarList& QueryVariables)	//��ѯ�����б�
{
	auto result = std::ranges::find(QueryVariables, nNodeID, &GROUNDING_VARIABLE::nNodeID);
	if (result != QueryVariables.end())
		return result->nValueID;
	AfxMessageBox(_T("GetValueID()�쳣"));
	return 0;
}