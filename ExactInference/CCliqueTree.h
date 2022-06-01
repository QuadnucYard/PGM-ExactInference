////////////////////////////////////////////////////////////////////////////////
// CCliqueTree.h
// ����������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#pragma once


#include <filesystem>
#include <queue>
#include "CClique.h"
#include "Helper.h"
#include "tinyxml.h"
#include "xmlutils.hpp"
#include "tinyxmliterator.h"

using fidpair = std::pair<fid_t, fid_t>;
using fidsetmap = std::map<fid_t, fidset>;
using fidmultimap = std::multimap<fid_t, fid_t>;

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

	SEP_SET() = default;
	SEP_SET(fid_t nStartID, fid_t nEndID, const CClique& clique, bool bReady = false):
		nStartID(nStartID), nEndID(nEndID), clique(clique), bReady(bReady) {}
	bool operator==(const fidpair& rhs) const {
		return nStartID == rhs.first && nEndID == rhs.second;
	}
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

	//���ϴ�����Ϣ
	void UpwardPass();
	//��������ŵ���
	void BuildUpwardTree(fid_t);
	//�����ŵȴ�����Ϣ����
	fidsetmap CreateCliqueWaitedMessages();
	//����ȴ���Ϣ����
	void InsertToWaitedMessages(fid_t, fid_t, fidsetmap&);
	//������Ƿ����
	bool IsCliqueReady(fid_t, const fidsetmap&) const;
	//����Ƿ����и���Ѿ����ڡ�ÿ���߰������Ϻ����������
	bool IsAllSEPSetExisted(fid_t, const fidset&) const;
	//����Ƿ����и���Ѿ����ڵĸ�������
	bool IsAllSEPSetExisted_Helper(fid_t, fid_t) const;
	//Ҫ�����Ѿ��������ID����һ����������
	fid_t FindReadyClique(const fidsetmap&, const fidset&) const;

	//�򸸽ڵ㷢����Ϣ
	void SendCliqueMessage(fid_t);
	//������Ϣ
	void ReceiveMessages(fid_t, const fidsetmap&);
	//��ȡ������֮��ĸ	
	const CClique& GetSEPSet(fid_t, fid_t);
	//����Ƿ����˫��
	bool IsThereParentID(fid_t, fid_t&);
	//���ֹ���ı���ID����
	fidset FindCommonVariableIDs(fid_t, fid_t);

	//���´�����Ϣ
	void DownwardPass();
	//���´�����Ϣʱ�������ŵȴ�����Ϣ����
	fidsetmap CreateCliqueWaitedMessages_Downward();
	//���´�����Ϣ
	void SendCliqueMessage_Downward(fid_t, fid_t);

	//��ѯ�ĸ�������
	void Query_Helper(const CT_QUERY&);
	//��ȡ��ѯ��ʼ�ŵ�λ��
	size_t GetStartCliquePos(const fidset&);

	//��ѯ���ʷֲ�
	void Query_Probability(const CT_QUERY&, const fidset&, size_t);
	//���ݱߵĽڵ�ID����ȡ�λ��
	size_t GetSEPSetPos(fid_t, fid_t);

	//�����ѯ������ʵ�XML�ļ�
	void OutputToXML();

private:
	//����
	std::vector<CT_NODE> m_CTNodes;					//�����Ľڵ��
	fidmultimap m_CTEdges;						//�����ı߱�

	fid_t m_nRootID;							//���ŵ�ID
	std::map<fid_t, std::string> m_VariableID2Names;		//�ӱ���ID���������Ƶ�ӳ��
	fidmultimap m_VariableID2CliqueIDs;			//�ӱ���ID����ID�Ķ�ӳ�䡣һ�������������ڶ����
	fidmap m_CliqueID2Poses;					//����ID����λ�õ�ӳ��
	fidmap m_UpwardTree;						//����ŵ���
	fidsetmap m_Parent2Childs;					//˫�׽ڵ�ָ���ӽڵ㼯��

	//�ͻ���Ϣ�����㷨
	std::vector<CClique> m_Cliques;					//���б�
	std::vector<SEP_SET> m_SEPSets;					//��б�

	//��ѯ
	std::vector<CT_QUERY> m_CTQueries;				//������ѯ�б�֧�ֶ����ѯ
	std::vector<fval_t> m_CTQueryResults;			//������ѯ����б�
};