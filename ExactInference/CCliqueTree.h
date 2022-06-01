////////////////////////////////////////////////////////////////////////////////
// CCliqueTree.h
// 定义团树类
// Originated by	高志强
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

//定义类型
//团树中的实例化变量类型
struct CT_GROUNDING_VARIABLE
{
	fid_t nVariableID;		//01 变量ID
	fid_t nValueID;			//02 变量值ID
};

using CTGVarList = std::vector<CT_GROUNDING_VARIABLE>;

//团行
struct CT_FACTOR_ROW
{
	fidlist ValueIDs;		//01 变量值ID列表
	fval_t fValue;			//02 值
};

using CTFactorRowList = std::vector<CT_FACTOR_ROW>;

//团树节点
struct CT_NODE
{
	fid_t nID;						//01 团树节点ID,如0
	fidlist VariableIDs;			//02 变量ID列表
	CTFactorRowList FactorRows;		//03 团行的列表
};

//团树割集
struct SEP_SET
{
	fid_t nStartID;			//01 开始的团节点ID
	fid_t nEndID;			//02 结束的团结点
	CClique clique;			//03 割集。采用团表示
	bool bReady;			//04 是否就绪。在向下传播消息时为就绪，向上传播消息时未就绪

	SEP_SET() = default;
	SEP_SET(fid_t nStartID, fid_t nEndID, const CClique& clique, bool bReady = false):
		nStartID(nStartID), nEndID(nEndID), clique(clique), bReady(bReady) {}
	bool operator==(const fidpair& rhs) const {
		return nStartID == rhs.first && nEndID == rhs.second;
	}
};

//查询
struct CT_QUERY
{
	CTGVarList MarginalVariables;	//01 边缘变量ID和值ID列表
	CTGVarList GivenVariables;		//02 给定变量ID和值ID列表
};


//定义团树的精确推理类CCliqueTree
class CCliqueTree
{

public:
	//初始化
	void Init();
	//查询
	void Query();

private:
	//读取团树
	void Read_CT();

	//读取团树查询的边缘变量、给定变量及其值
	void Read_QueryCT();
	//预处理
	void Preprocess();
	//根据团ID获取团位置。团存储在vector中，其位置和ID未必相等
	fid_t GetCliquePosByID(fid_t);

	//向上传递消息
	void UpwardPass();
	//构建向根团的树
	void BuildUpwardTree(fid_t);
	//创建团等待的消息集合
	fidsetmap CreateCliqueWaitedMessages();
	//插入等待消息集合
	void InsertToWaitedMessages(fid_t, fid_t, fidsetmap&);
	//检查团是否就绪
	bool IsCliqueReady(fid_t, const fidsetmap&) const;
	//检查是否所有割集都已经存在。每条边包括向上和向下两个割集
	bool IsAllSEPSetExisted(fid_t, const fidset&) const;
	//检查是否所有割集都已经存在的辅助函数
	bool IsAllSEPSetExisted_Helper(fid_t, fid_t) const;
	//要避免已经处理过的ID查找一个就绪的团
	fid_t FindReadyClique(const fidsetmap&, const fidset&) const;

	//向父节点发送消息
	void SendCliqueMessage(fid_t);
	//接收消息
	void ReceiveMessages(fid_t, const fidsetmap&);
	//获取两个团之间的割集	
	const CClique& GetSEPSet(fid_t, fid_t);
	//检查是否存在双亲
	bool IsThereParentID(fid_t, fid_t&);
	//发现共享的变量ID集合
	fidset FindCommonVariableIDs(fid_t, fid_t);

	//向下传递消息
	void DownwardPass();
	//向下传递消息时，创建团等待的消息集合
	fidsetmap CreateCliqueWaitedMessages_Downward();
	//向下传递消息
	void SendCliqueMessage_Downward(fid_t, fid_t);

	//查询的辅助函数
	void Query_Helper(const CT_QUERY&);
	//获取查询开始团的位置
	size_t GetStartCliquePos(const fidset&);

	//查询概率分布
	void Query_Probability(const CT_QUERY&, const fidset&, size_t);
	//根据边的节点ID、获取割集位置
	size_t GetSEPSetPos(fid_t, fid_t);

	//输出查询结果概率到XML文件
	void OutputToXML();

private:
	//团树
	std::vector<CT_NODE> m_CTNodes;					//团树的节点表
	fidmultimap m_CTEdges;						//团树的边表

	fid_t m_nRootID;							//根团的ID
	std::map<fid_t, std::string> m_VariableID2Names;		//从变量ID到变量名称的映射
	fidmultimap m_VariableID2CliqueIDs;			//从变量ID到团ID的多映射。一个变量可能属于多个团
	fidmap m_CliqueID2Poses;					//从团ID到团位置的映射
	fidmap m_UpwardTree;						//向根团的树
	fidsetmap m_Parent2Childs;					//双亲节点指向子节点集合

	//和积消息传递算法
	std::vector<CClique> m_Cliques;					//团列表
	std::vector<SEP_SET> m_SEPSets;					//割集列表

	//查询
	std::vector<CT_QUERY> m_CTQueries;				//团树查询列表。支持多个查询
	std::vector<fval_t> m_CTQueryResults;			//团树查询结果列表
};