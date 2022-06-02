////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct.h
// ���屴Ҷ˹����ľ�ȷ�����ࡣ���úͻ�����������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>
#include "CFactor.h"
#include "iohelper.h"


//��Ҷ˹����ڵ�
struct BNNode
{
	fid_t nID;						//01 �ڵ�ID����0
	std::string sName;				//02 �ڵ����ƣ���Difficulty
	std::string sAbbr;				//03 �ڵ��ƣ���D
	size_t nNumberOfValues;			//04 �ڵ�ֵ�ĸ������ڵ�ȡֵ��0��1��2���棬��ѧ�������е�GradeΪ����ȡֵ������1��2��3��
	size_t nNumberOfParents;		//05 ���ڵ������
	fidlist ParentIDs;				//06 ���ڵ�ID�б���ѭ��˳������������ʷֲ���
	fvallist CPTRowValues;			//07 �������ʷֲ�����ÿ�е�ֵ
	CPTRowList CPTRowIDs;			//08 �������ʷֲ�����ÿ�еı���ID����
};

//��Ҷ˹����ı�
struct BNEdge
{
	fid_t nID;						//01 �ߵ�ID��������δ��
	fid_t nStartNodeID;				//02 �ߵ����ID
	fid_t nEndNodeID;				//03 �ߵ��յ�ID
};


//���屴Ҷ˹����ľ�ȷ������CBNSumProduct�����úͻ�����������
class CBNSumProduct
{

	//ʵ������������
	struct GroundingVariable
	{
		fid_t nNodeID;				//01 ����ID
		fid_t nValueID;				//02 ������ֵID

		static GroundingVariable fromPair(fidpair pair) {
			return GroundingVariable {pair.first, pair.second};
		}
	};

	using GVarList = std::vector<GroundingVariable>;

	//��ѯ
	struct BNQuery
	{
		GVarList QueryVariables;		//��ѯ�Ľڵ㼰��ȡֵ
		GVarList GivenVariables;		//�����Ľڵ㼰��ȡֵ
		fidlist EliminateVariables;		//ɾ���ڵ��˳��
	};

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
	void Query_Helper(const BNQuery&, CFactorList);
	//��ѯ��Ե���ʷֲ�
	void Query_Marginal(const BNQuery&, CFactorList&);

	//���и��ڵ�ID����ȡֵ
	void Arrange(fid_t, const fidlist&, const fidlist&, size_t, size_t&);
	//��ȡ����
	double GetFactor(fid_t nNodeID, fid_t nNodeValue, const GVarList& QueryVariables);
	//��ȡֵ��ID
	fid_t GetValueID(fid_t, const GVarList&);

	//������ʷֲ���XML�ļ�
	void OutputToXML();				
	void OutputToYAML();

	//�ͻ���������
	void Sum_Product_Eliminate_Var(fid_t, CFactorList&);	

private:
	std::vector<BNNode> m_Nodes;		//BN�Ľڵ��
	std::vector<BNEdge> m_Edges;		//BN�ı߱�
	CFactorList m_Factors;				//�����б�
	std::vector<BNQuery> m_Queries;		//��ѯ�б�
	fvallist m_QueryResults;			//��ѯ����б�
};