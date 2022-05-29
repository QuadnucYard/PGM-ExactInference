/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CBNSumProduct.h
//��  �ܣ�		���屴Ҷ˹����ľ�ȷ�����ࡣ���úͻ�����������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��02��28��
//��  �£�		2021��03��08��
//��  �£�		2021��03��23��
//��  �£�		2021��03��29��
//��  �ȣ�		130��
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>
#include "CFactor.h"
#include "xmlutils.hpp"

//��������
//ʵ������������
struct GROUNDING_VARIABLE
{
	fid_t nNodeID;				//01 ����ID
	fid_t nValueID;				//02 ������ֵID

	GROUNDING_VARIABLE() {}
	GROUNDING_VARIABLE(fid_t nNodeID, fid_t nValueID): nNodeID(nNodeID), nValueID(nValueID) {}
};

using GVarList = std::vector<GROUNDING_VARIABLE>;

//�������ʷֲ������
struct CPT_ROW
{
	fidlist ValueIDs;			//01 �ڵ�ֵID���б������ڵ��˫�ס��ڵ��Լ����ڵ�ID���б��PARENT_ID��ͬ�������ӽڵ��Լ�
	fval_t fProb;				//02 ���ʡ��൱���������ʷֲ����һ�������ĸ���

	CPT_ROW() {}
	CPT_ROW(const fidlist& ValueIDs, fval_t fProb):ValueIDs(ValueIDs), fProb(fProb) {}
	CPT_ROW(fidlist&& ValueIDs, fval_t fProb):ValueIDs(ValueIDs), fProb(fProb) {}
};

using CPTRowList = std::vector<CPT_ROW>;

//��Ҷ˹����ڵ�
struct BN_NODE
{
	fid_t nID;						//01 �ڵ�ID����0
	std::string sName;				//02 �ڵ����ƣ���Difficulty
	std::string sAbbreviation;		//03 �ڵ��ƣ���D
	size_t nNumberOfValues;			//04 �ڵ�ֵ�ĸ������ڵ�ȡֵ��0��1��2���棬��ѧ�������е�GradeΪ����ȡֵ������1��2��3��
	size_t nNumberOfParents;		//05 ���ڵ������
	fidlist ParentIDs;				//06 ���ڵ�ID�б���ѭ��˳������������ʷֲ���
	fvallist CPTRowValues;			//07 �������ʷֲ�����ÿ�е�ֵ
	CPTRowList CPTRowIDs;			//08 �������ʷֲ�����ÿ�еı���ID����
};

//��Ҷ˹����ı�
struct BN_EDGE
{
	fid_t nID;						//01 �ߵ�ID��������δ��
	fid_t nStartNodeID;				//02 �ߵ����ID
	fid_t nEndNodeID;				//03 �ߵ��յ�ID

	BN_EDGE() {}
	BN_EDGE(fid_t nID, fid_t nStartNodeID, fid_t nEndNodeID):
		nID(nID), nStartNodeID(nStartNodeID), nEndNodeID(nEndNodeID) {}
};

//��ѯ
struct QUERY
{
	GVarList QueryVariables;		//��ѯ�Ľڵ㼰��ȡֵ
	GVarList GivenVariables;		//�����Ľڵ㼰��ȡֵ
	fidlist EliminateVariables;		//ɾ���ڵ��˳��
};


//���屴Ҷ˹����ľ�ȷ������CBNSumProduct�����úͻ�����������
class CBNSumProduct
{
public:
	//��ʼ��
	void Init();
	//��ѯ
	void Query();

private:
	//��ȡ��Ҷ˹����ṹ�����
	void Read_BN();
	//��ȡ��ѯ������������������������˳��
	void Read_Query();

	//Ԥ����
	void Preprocess();
	//Ԥ����Ҷ˹����ṹ�����
	void Preprocess_BN();
	//Ԥ��������
	void Preprocess_Factor();

	//��ѯ�ĸ�������
	void Query_Helper(const QUERY&, CFactorList);
	//��ѯ��Ե���ʷֲ�
	void Query_Marginal(const QUERY&, CFactorList&);

	//���и��ڵ�ID����ȡֵ
	void Arrange(fid_t, const fidlist&, const fidlist&, size_t, size_t&);
	//��CPT�в��Ҹ���
	double GetProbFromCPT(CPTRowList& cpts, fidlist&);
	//��ȡ����
	double GetFactor(fid_t nNodeID, fid_t nNodeValue, const GVarList& QueryVariables);
	//��ȡֵ��ID
	fid_t GetValueID(fid_t, const GVarList&);

	void OutputToXML();																								//������ʷֲ���XML�ļ�

	//�ͻ���������
	void Sum_Product_Eliminate_Var(fid_t, CFactorList&);	

private:
	std::vector<BN_NODE> m_Nodes;		//BN�Ľڵ��
	std::vector<BN_EDGE> m_Edges;		//BN�ı߱�
	CFactorList m_Factors;				//�����б�
	std::vector<QUERY> m_Queries;		//��ѯ�б�
	fvallist m_QueryResults;			//��ѯ����б�
};