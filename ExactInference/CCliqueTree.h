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

#include <map>							//mapͷ�ļ�
#include <set>							//setͷ�ļ�
#include <string>						//stringͷ�ļ�
#include <list>							//listͷ�ļ�
#include <vector>						//vectorͷ�ļ�
#include <queue>						//queueͷ�ļ�
#include <algorithm>					//algorithm��ͷ�ļ�
#include <numeric>						//numeric��ͷ�ļ�
#include <sstream>						//sstream��ͷ�ļ�
#include <fstream>						//fstream��ͷ�ļ�
#include <time.h>						//ʱ�亯����ͷ�ļ�
#include "math.h"						//��ѧ����ͷ�ļ�
#include "CClique.h"					//����ͷ�ļ�


//���������ռ�
using namespace std;					//ʹ�ñ�׼�����ռ�


//��������
//�����е�ʵ������������
typedef struct
{
	unsigned int nVariableID;							//01 ����ID
	unsigned int nValueID;								//02 ����ֵID
}CT_GROUNDING_VARIABLE;

//����
typedef struct
{
	vector<unsigned int> ValueIDs;						//01 ����ֵID�б�
	double fValue;										//02 ֵ
}CT_FACTOR_ROW;

//�����ڵ�
typedef struct
{
	unsigned int nID;									//01 �����ڵ�ID,��0
	vector<unsigned int> VariableIDs;					//02 ����ID�б�
	vector<CT_FACTOR_ROW> FactorRows;					//03 ���е��б�
}CT_NODE;

//�����
typedef struct
{
	unsigned int nStartID;								//01 ��ʼ���Žڵ�ID
	unsigned int nEndID;								//02 �������Ž��
	CClique clique;										//03 ��������ű�ʾ
	bool bReady;										//04 �Ƿ�����������´�����ϢʱΪ���������ϴ�����Ϣʱδ����
}SEP_SET;

//��ѯ
typedef struct
{
	vector<CT_GROUNDING_VARIABLE> MarginalVariables;	//01 ��Ե����ID��ֵID�б�
	vector<CT_GROUNDING_VARIABLE> GivenVariables;		//02 ��������ID��ֵID�б�
}CT_QUERY;


//���������ľ�ȷ������CCliqueTree
class CCliqueTree
{
	//���캯������������
public:
	CCliqueTree();										//���캯��
	~CCliqueTree();										//��������

	//���з���
public:
	//��ʼ��
	void Init();										//��ʼ��
	//��ѯ
	void Query();										//��ѯ

	//˽�з���
private:
	//��ȡ
	void Read_CT();										//��ȡ����Clique Tree
	void Read_QueryCT();								//��ȡ������ѯ�ı�Ե������������������ֵ
	//Ԥ����
	void Preprocess();									//Ԥ����
	unsigned int GetCliquePosByID(unsigned int);		//������ID��ȡ��λ�á��Ŵ洢��vector�У���λ�ú�IDδ�����
	
	//////////////////////////////////////////////////////////////////////////////////////
	//���ϴ�����Ϣ
	void UpwardPass();																				//���ϴ�����Ϣ
	void BuildUpwardTree(unsigned int);																//��������ŵ���
	void CreateCliqueWaitedMessages(map<unsigned int,set<unsigned int>>&);							//�����ŵȴ�����Ϣ����
	void InsertToWaitedMessages(unsigned int, unsigned int, map<unsigned int,set<unsigned int>>&);	//����ȴ���Ϣ����
	bool IsCliqueReady(unsigned int, map<unsigned int, set<unsigned int>>& WaitedMessages);			//������Ƿ����
	bool IsAllSEPSetExisted(unsigned int, set<unsigned int>&);										//����Ƿ����и���Ѿ����ڡ�ÿ���߰������Ϻ����������
	bool IsAllSEPSetExisted_Helper(unsigned int, unsigned int);										//����Ƿ����и���Ѿ����ڵĸ�������
	unsigned int FindReadyClique(map <unsigned int,set<unsigned int>>& WaitedMessages,set<unsigned int>&);	//Ҫ�����Ѿ��������ID����һ����������
	//������Ϣ
	void SendCliqueMessage(unsigned int);															//�򸸽ڵ㷢����Ϣ
	//������Ϣ
	void ReceiveMessages(unsigned int, map<unsigned int,set<unsigned int>>& WaitedMessages);		//������Ϣ
	CClique GetSEPSet(unsigned int, unsigned int);													//��ȡ������֮��ĸ	
	bool IsThereParentID(unsigned int, unsigned int&);												//����Ƿ����˫��
	void FindCommonVariableIDs(unsigned int, unsigned int, set<unsigned int>&);						//���ֹ���ı���ID����
	void FindIntersections(set<unsigned int>&, set<unsigned int>&, set<unsigned int>&);				//���������ϵĽ�
	void SubtractBetweenSets(set<unsigned int>&, set<unsigned int>&, set<unsigned int>&);			//���������ϵĲ�
	
	//////////////////////////////////////////////////////////////////////////////////////
	//���´�����Ϣ
	void DownwardPass();																			//���´�����Ϣ
	void CreateCliqueWaitedMessages_Downward(map<unsigned int, set<unsigned int>>&);				//���´�����Ϣʱ�������ŵȴ�����Ϣ����
	void SendCliqueMessage_Downward(unsigned int,unsigned int);										//���´�����Ϣ
	set<unsigned int> GetChildren(unsigned int);													//��ȡ���ӽڵ㼯��
	
	////////////////////////////////////////////////////////////////////////////////////
	//��ѯ��������
	void Query_Helper(CT_QUERY&);																	//��ѯ�ĸ�������
	unsigned int GetStartCliquePos(set<unsigned int>&);												//��ȡ��ѯ��ʼ�ŵ�λ��
	void GetIntersections(vector<unsigned int>&, set<unsigned int>&, set<unsigned int>&);			//���б�ͼ��ϵĽ���
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
	map<unsigned int, unsigned int> m_CliqueID2Poses;			//����ID����λ�õ�ӳ��
	map<unsigned int, unsigned int> m_UpwardTree;				//����ŵ���
	map<unsigned int, set<unsigned int>> m_Parent2Childs;		//˫�׽ڵ�ָ���ӽڵ㼯��

	//�ͻ���Ϣ�����㷨
	vector<CClique> m_Cliques;									//���б�
	vector<SEP_SET> m_SEPSets;									//��б�
	
	//��ѯ
	vector<CT_QUERY> m_CTQueries;								//������ѯ�б�֧�ֶ����ѯ
	vector<double> m_CTQueryResults;							//������ѯ����б�
};