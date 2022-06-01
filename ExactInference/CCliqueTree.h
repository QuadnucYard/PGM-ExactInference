/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree.h
//��  �ܣ�		����������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��30��
//��  �£�		2021��04��12��
//��  �£�		2021��05��18��
//��  �ȣ�		160��
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once


#include <filesystem>
#include <queue>
#include "CClique.h"
#include "tinyxml.h"
#include "xmlutils.hpp"


//��������
//�����е�ʵ������������
struct CT_GROUNDING_VARIABLE
{
	fid_t nVariableID;		//01 ����ID
	fid_t nValueID;			//02 ����ֵID
};

using CTGVarList = std::vector<CT_GROUNDING_VARIABLE>;

//����
struct CT_FACTOR_ROW
{
	fidlist ValueIDs;		//01 ����ֵID�б�
	fval_t fValue;			//02 ֵ
};

using CTFactorRowList = std::vector<CT_FACTOR_ROW>;

//�����ڵ�
struct CT_NODE
{
	fid_t nID;						//01 �����ڵ�ID,��0
	fidlist VariableIDs;			//02 ����ID�б�
	CTFactorRowList FactorRows;		//03 ���е��б�
};

//�����
struct SEP_SET
{
	fid_t nStartID;			//01 ��ʼ���Žڵ�ID
	fid_t nEndID;			//02 �������Ž��
	CClique clique;			//03 ��������ű�ʾ
	bool bReady;			//04 �Ƿ�����������´�����ϢʱΪ���������ϴ�����Ϣʱδ����
};

//��ѯ
struct CT_QUERY
{
	CTGVarList MarginalVariables;	//01 ��Ե����ID��ֵID�б�
	CTGVarList GivenVariables;		//02 ��������ID��ֵID�б�
};


//���������ľ�ȷ������CCliqueTree
class CCliqueTree
{

public:
	//��ʼ��
	void Init();
	//��ѯ
	void Query();

private:
	//��ȡ����
	void Read_CT();

	//��ȡ������ѯ�ı�Ե������������������ֵ
	void Read_QueryCT();
	//Ԥ����
	void Preprocess();
	//������ID��ȡ��λ�á��Ŵ洢��vector�У���λ�ú�IDδ�����
	fid_t GetCliquePosByID(fid_t);

	//////////////////////////////////////////////////////////////////////////////////////
	//���ϴ�����Ϣ
	void UpwardPass();																				//���ϴ�����Ϣ
	void BuildUpwardTree(unsigned int);																//��������ŵ���
	void CreateCliqueWaitedMessages(map<unsigned int, set<unsigned int>>&);							//�����ŵȴ�����Ϣ����
	void InsertToWaitedMessages(unsigned int, unsigned int, map<unsigned int, set<unsigned int>>&);	//����ȴ���Ϣ����
	bool IsCliqueReady(unsigned int, map<unsigned int, set<unsigned int>>& WaitedMessages);			//������Ƿ����
	bool IsAllSEPSetExisted(unsigned int, set<unsigned int>&);										//����Ƿ����и���Ѿ����ڡ�ÿ���߰������Ϻ����������
	bool IsAllSEPSetExisted_Helper(unsigned int, unsigned int);										//����Ƿ����и���Ѿ����ڵĸ�������
	unsigned int FindReadyClique(map <unsigned int, set<unsigned int>>& WaitedMessages, set<unsigned int>&);	//Ҫ�����Ѿ��������ID����һ����������
	//������Ϣ
	void SendCliqueMessage(unsigned int);															//�򸸽ڵ㷢����Ϣ
	//������Ϣ
	void ReceiveMessages(unsigned int, map<unsigned int, set<unsigned int>>& WaitedMessages);		//������Ϣ
	CClique GetSEPSet(unsigned int, unsigned int);													//��ȡ������֮��ĸ	
	bool IsThereParentID(unsigned int, unsigned int&);												//����Ƿ����˫��
	void FindCommonVariableIDs(unsigned int, unsigned int, set<unsigned int>&);						//���ֹ���ı���ID����

	//////////////////////////////////////////////////////////////////////////////////////
	//���´�����Ϣ
	void DownwardPass();																			//���´�����Ϣ
	void CreateCliqueWaitedMessages_Downward(map<unsigned int, set<unsigned int>>&);				//���´�����Ϣʱ�������ŵȴ�����Ϣ����
	void SendCliqueMessage_Downward(unsigned int, unsigned int);										//���´�����Ϣ
	set<unsigned int> GetChildren(unsigned int);													//��ȡ���ӽڵ㼯��

	////////////////////////////////////////////////////////////////////////////////////
	//��ѯ��������
	void Query_Helper(CT_QUERY&);																	//��ѯ�ĸ�������
	unsigned int GetStartCliquePos(set<unsigned int>&);												//��ȡ��ѯ��ʼ�ŵ�λ��
	void GetIntersections(const vector<unsigned int>&, set<unsigned int>&, set<unsigned int>&);			//���б�ͼ��ϵĽ���
	//��ѯ���ʷֲ�
	void Query_Probability(CT_QUERY&, set<unsigned int>&, unsigned int);							//��ѯ����
	unsigned int GetSEPSetPos(unsigned int, unsigned int);											//���ݱߵĽڵ�ID����ȡ�λ��
	bool IsSetContainedIn(set<unsigned int>&, set<unsigned int>&);									//�жϼ����Ƿ����������һ������
	vector<unsigned int> GetSubstract(vector<unsigned int>&, set<unsigned int>&);					//�����кͼ��ϵĲ�

	////////////////////////////////////////////////////////////////////////////////////
	//�����ѯ������洢��CliqueTree_Output.xml
	void OutputToXML();																				//������ʵ�XML�ļ�


	//���ݳ�Ա
private:
	//����
	vector<CT_NODE> m_CTNodes;									//�����Ľڵ��
	multimap<unsigned int, unsigned int> m_CTEdges;				//�����ı߱�

	unsigned int m_nRootID;										//���ŵ�ID
	map<unsigned int, string> m_VariableID2Names;				//�ӱ���ID���������Ƶ�ӳ��
	multimap<unsigned int, unsigned int> m_VariableID2CliqueIDs;//�ӱ���ID����ID�Ķ�ӳ�䡣һ�������������ڶ����
	fidmap m_CliqueID2Poses;			//����ID����λ�õ�ӳ��
	fidmap m_UpwardTree;				//����ŵ���
	map<unsigned int, set<unsigned int>> m_Parent2Childs;		//˫�׽ڵ�ָ���ӽڵ㼯��

	//�ͻ���Ϣ�����㷨
	vector<CClique> m_Cliques;									//���б�
	vector<SEP_SET> m_SEPSets;									//��б�

	//��ѯ
	vector<CT_QUERY> m_CTQueries;								//������ѯ�б�֧�ֶ����ѯ
	vector<double> m_CTQueryResults;							//������ѯ����б�
};