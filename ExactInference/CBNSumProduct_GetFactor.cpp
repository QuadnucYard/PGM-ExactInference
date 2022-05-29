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
	//���塢����ʼ����ȡ���ڵ�ID�б�
	fidlist NodeIDs = m_Nodes[nNodeID].ParentIDs;

	//�������ڵ�ID����ȡ��ֵID
	fidlist ValueIDs = NodeIDs | std::views::transform([&](auto t) { return GetValueID(t, QueryVariables); }) | qy::views::to<fidlist>;
	//��ӵ�ǰ�ڵ��ֵID
	ValueIDs.push_back(nValueID);

	//�ڵ�ǰ�ڵ��CPT�в���
	size_t result = qy::index_of_if(m_Nodes[nNodeID].CPTRowIDs, [=](const CPT_ROW& t) { return t.ValueIDs == ValueIDs; });
	if (result != -1)
		return m_Nodes[nNodeID].CPTRowValues[result];
	AfxMessageBox(_T("GetFactor()�쳣"));
	return 1.0f;
}

//��ȡֵID
fid_t CBNSumProduct::GetValueID(fid_t nNodeID,		//�ڵ�ID
	const GVarList& QueryVariables)	//��ѯ�����б�
{
	auto result = std::ranges::find_if(QueryVariables, [=](GROUNDING_VARIABLE t) { return t.nNodeID == nNodeID; });
	if (result != QueryVariables.end())
		return result->nValueID;
	AfxMessageBox(_T("GetValueID()�쳣"));
	return 0;
}