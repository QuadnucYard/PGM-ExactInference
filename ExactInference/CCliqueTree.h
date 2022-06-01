/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CCliqueTree.h
//功  能：		定义团树类
//开发者：		高志强
//日  期：		2021年03月30日
//更  新：		2021年04月12日
//更  新：		2021年05月18日
//长  度：		160行
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once


#include <filesystem>
#include <queue>
#include "CClique.h"
#include "tinyxml.h"
#include "xmlutils.hpp"


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

	//////////////////////////////////////////////////////////////////////////////////////
	//向上传递消息
	void UpwardPass();																				//向上传递消息
	void BuildUpwardTree(unsigned int);																//构建向根团的树
	void CreateCliqueWaitedMessages(map<unsigned int, set<unsigned int>>&);							//创建团等待的消息集合
	void InsertToWaitedMessages(unsigned int, unsigned int, map<unsigned int, set<unsigned int>>&);	//插入等待消息集合
	bool IsCliqueReady(unsigned int, map<unsigned int, set<unsigned int>>& WaitedMessages);			//检查团是否就绪
	bool IsAllSEPSetExisted(unsigned int, set<unsigned int>&);										//检查是否所有割集都已经存在。每条边包括向上和向下两个割集
	bool IsAllSEPSetExisted_Helper(unsigned int, unsigned int);										//检查是否所有割集都已经存在的辅助函数
	unsigned int FindReadyClique(map <unsigned int, set<unsigned int>>& WaitedMessages, set<unsigned int>&);	//要避免已经处理过的ID查找一个就绪的团
	//发送消息
	void SendCliqueMessage(unsigned int);															//向父节点发送消息
	//接收消息
	void ReceiveMessages(unsigned int, map<unsigned int, set<unsigned int>>& WaitedMessages);		//接收消息
	CClique GetSEPSet(unsigned int, unsigned int);													//获取两个团之间的割集	
	bool IsThereParentID(unsigned int, unsigned int&);												//检查是否存在双亲
	void FindCommonVariableIDs(unsigned int, unsigned int, set<unsigned int>&);						//发现共享的变量ID集合

	//////////////////////////////////////////////////////////////////////////////////////
	//向下传递消息
	void DownwardPass();																			//向下传递消息
	void CreateCliqueWaitedMessages_Downward(map<unsigned int, set<unsigned int>>&);				//向下传递消息时，创建团等待的消息集合
	void SendCliqueMessage_Downward(unsigned int, unsigned int);										//向下传递消息
	set<unsigned int> GetChildren(unsigned int);													//获取孩子节点集合

	////////////////////////////////////////////////////////////////////////////////////
	//查询辅助函数
	void Query_Helper(CT_QUERY&);																	//查询的辅助函数
	unsigned int GetStartCliquePos(set<unsigned int>&);												//获取查询开始团的位置
	void GetIntersections(const vector<unsigned int>&, set<unsigned int>&, set<unsigned int>&);			//求列表和集合的交集
	//查询概率分布
	void Query_Probability(CT_QUERY&, set<unsigned int>&, unsigned int);							//查询概率
	unsigned int GetSEPSetPos(unsigned int, unsigned int);											//根据边的节点ID、获取割集位置
	bool IsSetContainedIn(set<unsigned int>&, set<unsigned int>&);									//判断集合是否包含于另外一个集合
	vector<unsigned int> GetSubstract(vector<unsigned int>&, set<unsigned int>&);					//求序列和集合的差

	////////////////////////////////////////////////////////////////////////////////////
	//输出查询结果。存储到CliqueTree_Output.xml
	void OutputToXML();																				//输出概率到XML文件


	//数据成员
private:
	//团树
	vector<CT_NODE> m_CTNodes;									//团树的节点表
	multimap<unsigned int, unsigned int> m_CTEdges;				//团树的边表

	unsigned int m_nRootID;										//根团的ID
	map<unsigned int, string> m_VariableID2Names;				//从变量ID到变量名称的映射
	multimap<unsigned int, unsigned int> m_VariableID2CliqueIDs;//从变量ID到团ID的多映射。一个变量可能属于多个团
	fidmap m_CliqueID2Poses;			//从团ID到团位置的映射
	fidmap m_UpwardTree;				//向根团的树
	map<unsigned int, set<unsigned int>> m_Parent2Childs;		//双亲节点指向子节点集合

	//和积消息传递算法
	vector<CClique> m_Cliques;									//团列表
	vector<SEP_SET> m_SEPSets;									//割集列表

	//查询
	vector<CT_QUERY> m_CTQueries;								//团树查询列表。支持多个查询
	vector<double> m_CTQueryResults;							//团树查询结果列表
};