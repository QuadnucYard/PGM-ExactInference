////////////////////////////////////////////////////////////////////////////////
// CCliqueTree.h
// ����������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#pragma once


#include <queue>
#include "CClique.h"
#include "iohelper.h"
#include "xmlutils.hpp"
#include "tinyxmliterator.h"
#include "Helper.h"

using CTFactorRow = FactorRow;
using CTFactorRowList = std::vector<FactorRow>;

//�����ڵ�
struct CTNode
{
	fid_t nID;						//01 �����ڵ�ID,��0
	fidlist VariableIDs;			//02 ����ID�б�
	CTFactorRowList FactorRows;		//03 ���е��б�
};

//�����
struct CutSet
{
	fid_t nStartID;			//01 ��ʼ���Žڵ�ID
	fid_t nEndID;			//02 �������Ž��
	CClique clique;			//03 ��������ű�ʾ
	bool bReady;			//04 �Ƿ�����������´�����ϢʱΪ���������ϴ�����Ϣʱδ����
};


//���������ľ�ȷ������CCliqueTree
class CCliqueTree
{
	//�����е�ʵ������������
	struct GroundingVariable
	{
		fid_t nVariableID;		//01 ����ID
		fid_t nValueID;			//02 ����ֵID

		static GroundingVariable fromPair(fidpair pair) {
			return GroundingVariable {pair.first, pair.second};
		}
	};

	using GVarList = std::vector<GroundingVariable>;

	//��ѯ
	struct CTQuery
	{
		GVarList MarginalVariables;		//01 ��Ե����ID��ֵID�б�
		GVarList GivenVariables;		//02 ��������ID��ֵID�б�
	};

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
	const CClique& GetCliquePosByID(fid_t) const;
	CClique& GetCliquePosByID(fid_t);

	//���ϴ�����Ϣ
	void UpwardPass();
	//��������ŵ���
	void BuildUpwardTree(fid_t);
	//�����ŵȴ�����Ϣ����
	fidsetmap CreateCliqueWaitedMessages() const;
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
	const CutSet& GetSEPSet(fid_t, fid_t) const;
	//����Ƿ����˫��
	bool IsThereParentID(fid_t, fid_t&) const;
	//���ֹ���ı���ID����
	fidset FindCommonVariableIDs(fid_t, fid_t) const;

	//���´�����Ϣ
	void DownwardPass();
	//���´�����Ϣʱ�������ŵȴ�����Ϣ����
	fidsetmap CreateCliqueWaitedMessages_Downward() const;
	//���´�����Ϣ
	void SendCliqueMessage_Downward(fid_t, fid_t);

	//��ѯ�ĸ�������
	void Query_Helper(const CTQuery&);
	//��ȡ��ѯ��ʼ�ŵ�λ��
	const CClique& GetStartClique(const fidset&) const;

	//��ѯ���ʷֲ�
	void Query_Probability(const CTQuery&, const fidset&, const CClique&);
	//���ݱߵĽڵ�ID����ȡ�λ��
	const CutSet& GetReadySEPSet(fid_t, fid_t) const;

	//�����ѯ������ʵ�XML�ļ�
	void OutputToXML() const;
	void OutputToYAML() const;

private:
	//����
	std::vector<CTNode> m_CTNodes;					//�����Ľڵ��
	fidmultimap m_CTEdges;							//�����ı߱�

	fid_t m_nRootID;								//���ŵ�ID
	std::map<fid_t, std::string> m_VariableID2Names;//�ӱ���ID���������Ƶ�ӳ��
	fidmultimap m_VariableID2CliqueIDs;				//�ӱ���ID����ID�Ķ�ӳ�䡣һ�������������ڶ����
	fidmap m_CliqueID2Poses;						//����ID����λ�õ�ӳ��
	fidmap m_UpwardTree;							//����ŵ���
	fidsetmap m_Parent2Childs;						//˫�׽ڵ�ָ���ӽڵ㼯��

	//�ͻ���Ϣ�����㷨
	std::vector<CClique> m_Cliques;					//���б�
	std::vector<CutSet> m_SEPSets;					//��б�

	//��ѯ
	std::vector<CTQuery> m_CTQueries;				//������ѯ�б�֧�ֶ����ѯ
	std::vector<fval_t> m_CTQueryResults;			//������ѯ����б�
};