/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CBNSumProduct_GetFactor.cpp
//��  �ܣ�		��ȡ����ֵ
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��09��
//��  �£�		2021��03��24��
//��  �ȣ�		100��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CBNSumProduct.h"							//��Ҷ˹���羫ȷ������ͷ�ļ������úͻ�����������


//��  �ƣ�		GetFactor()
//��  �ܣ�		�������ӵ�ֵ
//��  ����		unsigned int,unsigned int,vector<QUERY_VARIABLE>&
//����ֵ��		��
double CBNSumProduct::GetFactor(unsigned int nNodeID,						//�ڵ�ID
								unsigned int nValueID,						//�ڵ�ֵID
								vector<GROUNDING_VARIABLE>& QueryVariables)	//��ѯ�����б�
{
	//��ȡ�ڵ�
	BN_NODE bn_node = m_Nodes[nNodeID];

	//���塢����ʼ����ȡ���ڵ�ID�б�
	vector<unsigned int> NodeIDs = bn_node.ParentIDs;

	//����ֵID�б�
	vector<unsigned int> ValueIDs;

	//�������ڵ�ID����ȡ��ֵID
	for (unsigned int i = 0; i < NodeIDs.size(); i++)
	{
		//��ȡ�µĽڵ�ID
		unsigned int nNewNodeID = NodeIDs[i];
		//�����µ�ֵID
		unsigned int nNewValueID = GetValueID(nNewNodeID, QueryVariables);

		//��ӵ�ֵID��
		ValueIDs.push_back(nNewValueID);
	}

	//��ӵ�ǰ�ڵ��ֵID
	ValueIDs.push_back(nValueID);


	//�ڵ�ǰ�ڵ��CPT�в���
	vector<CPT_ROW> CPTRows = m_Nodes[nNodeID].CPTRowIDs;
	//����������
	for (unsigned int i = 0; i < CPTRows.size(); i++)
	{
		//�������Ƿ����
		if (CPTRows[i].ValueIDs == ValueIDs)
		{
			//���塢����ȡ����
			double fProb = m_Nodes[nNodeID].CPTRowValues[i];

			//���ظ���
			return fProb;
		}
	}


	//��ʾ�쳣
	AfxMessageBox(_T("GetFactor()�쳣"));
	
	//ȱʡ������1.0
	return 1.0f;
}

//��  �ƣ�		GetValueID()
//��  �ܣ�		��ȡֵID
//��  ����		unsigned int,vector<QUERY_VARIABLE>&
//����ֵ��		unsigned int
unsigned int CBNSumProduct::GetValueID(unsigned int nNodeID,						//�ڵ�ID
										vector<GROUNDING_VARIABLE>& QueryVariables)	//��ѯ�����б�
{
	//�������в�ѯ����
	for (unsigned int i = 0; i < QueryVariables.size(); i++)
	{
		//����Ƿ��ҵ������Ľڵ�ID
		if (nNodeID == QueryVariables[i].nNodeID)
		{
			//����ҵ����򷵻���ӦֵID
			return QueryVariables[i].nValueID;
		}
	}

	//��ʾ�쳣
	AfxMessageBox(_T("GetValueID()�쳣"));
	//ȱʡ����0
	return 0;
}