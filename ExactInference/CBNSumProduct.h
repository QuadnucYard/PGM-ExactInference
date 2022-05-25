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

#include <map>							//mapͷ�ļ�
#include <set>							//setͷ�ļ�
#include <string>						//stringͷ�ļ�
#include <list>							//listͷ�ļ�
#include <vector>						//vectorͷ�ļ�
#include <algorithm>					//algorithm��ͷ�ļ�
#include <numeric>						//numeric��ͷ�ļ�
#include <sstream>						//sstream��ͷ�ļ�
#include <fstream>						//fstream��ͷ�ļ�
#include <time.h>						//ʱ�亯����ͷ�ļ�
#include "math.h"						//��ѧ����ͷ�ļ�
#include "CFactor.h"					//������ͷ�ļ�


//���������ռ�
using namespace std;					//ʹ�ñ�׼�����ռ�


//��������
//ʵ������������
typedef struct
{
	unsigned int nNodeID;								//01 ����ID
	unsigned int nValueID;								//02 ������ֵID
}GROUNDING_VARIABLE;

//�������ʷֲ������
typedef struct
{
	vector<unsigned int> ValueIDs;						//01 �ڵ�ֵID���б������ڵ��˫�ס��ڵ��Լ����ڵ�ID���б��PARENT_ID��ͬ�������ӽڵ��Լ�
	double fProb;										//02 ���ʡ��൱���������ʷֲ����һ�������ĸ���
}CPT_ROW;

//��Ҷ˹����ڵ�
typedef struct
{
	unsigned int nID;									//01 �ڵ�ID����0
	string sName;										//02 �ڵ����ƣ���Difficulty
	string sAbbreviation;								//03 �ڵ��ƣ���D
	unsigned int nNumberOfValues;						//04 �ڵ�ֵ�ĸ������ڵ�ȡֵ��0��1��2���棬��ѧ�������е�GradeΪ����ȡֵ������1��2��3��
	unsigned int nNumberOfParents;						//05 ���ڵ������
	vector<unsigned int> ParentIDs;						//06 ���ڵ�ID�б���ѭ��˳������������ʷֲ���
	vector<double> CPTRowValues;						//07 �������ʷֲ�����ÿ�е�ֵ
	vector<CPT_ROW> CPTRowIDs;							//08 �������ʷֲ�����ÿ�еı���ID����
}BN_NODE;

//��Ҷ˹����ı�
typedef struct
{
	unsigned int nID;									//01 �ߵ�ID��������δ��
	unsigned int nStartNodeID;							//02 �ߵ����ID
	unsigned int nEndNodeID;							//03 �ߵ��յ�ID
}BN_EDGE;

//��ѯ
typedef struct
{
	vector<GROUNDING_VARIABLE> QueryVariables;								//��ѯ�Ľڵ㼰��ȡֵ
	vector<GROUNDING_VARIABLE> GivenVariables;								//�����Ľڵ㼰��ȡֵ
	vector<unsigned int> EliminateVariables;								//ɾ���ڵ��˳��
}QUERY;


//���屴Ҷ˹����ľ�ȷ������CBNSumProduct�����úͻ�����������
class CBNSumProduct
{
	//���캯������������
public:
	CBNSumProduct();									//���캯��
	~CBNSumProduct();									//��������

	//���з���
public:
	//��ʼ��
	void Init();										//��ʼ��
	//��ѯ
	void Query();										//��ѯ
	
	//˽�з���
private:
	//��ȡ
	void Read_BN();										//��ȡ��Ҷ˹����ṹ�����
	void Read_Query();									//��ȡ��ѯ������������������������˳��
	//Ԥ����
	void Preprocess();									//Ԥ����
	void Preprocess_BN();								//Ԥ����Ҷ˹����ṹ�����
	void Preprocess_Factor();							//Ԥ��������
	//��ѯ
	void Query_Helper(QUERY&, vector<CFactor>);			//��ѯ�ĸ�������
	void Query_Marginal(QUERY&, vector<CFactor>&);		//��ѯ��Ե���ʷֲ�
	
	void Arrange(unsigned int,vector<unsigned int>, vector<unsigned int>,unsigned int,unsigned int&);				//���и��ڵ�ID����ȡֵ
	double GetProbFromCPT(vector<CPT_ROW>& cpts,vector<unsigned int>&);												//��CPT�в��Ҹ���
	double GetFactor(unsigned int nNodeID, unsigned int nNodeValue, vector<GROUNDING_VARIABLE>& QueryVariables);	//��ȡ����
	unsigned int GetValueID(unsigned int, vector<GROUNDING_VARIABLE>&);												//��ȡֵ��ID

	void OutputToXML();																								//������ʷֲ���XML�ļ�

	void Sum_Product_Eliminate_Var(unsigned int,vector<CFactor>&);													//�ͻ���������
	
	//���ݳ�Ա
private:
	vector<BN_NODE> m_Nodes;							//BN�Ľڵ��
	vector<BN_EDGE> m_Edges;							//BN�ı߱�
	vector<CFactor> m_Factors;							//�����б�
	vector<QUERY> m_Queries;							//��ѯ�б�
	vector<double> m_QueryResults;						//��ѯ����б�
};