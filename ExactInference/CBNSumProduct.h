/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CBNSumProduct.h
//功  能：		定义贝叶斯网络的精确推理类。采用和积变量消除法
//开发者：		高志强
//日  期：		2021年02月28日
//更  新：		2021年03月08日
//更  新：		2021年03月23日
//更  新：		2021年03月29日
//长  度：		130行
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>
#include "CFactor.h"
#include "xmlutils.hpp"

//定义类型
//实例化变量类型
struct GROUNDING_VARIABLE
{
	fid_t nNodeID;				//01 变量ID
	fid_t nValueID;				//02 变量的值ID

	GROUNDING_VARIABLE() {}
	GROUNDING_VARIABLE(fid_t nNodeID, fid_t nValueID): nNodeID(nNodeID), nValueID(nValueID) {}
};

using GVarList = std::vector<GROUNDING_VARIABLE>;

//条件概率分布表的行
struct CPT_ROW
{
	fidlist ValueIDs;			//01 节点值ID的列表，包括节点的双亲、节点自己。节点ID的列表和PARENT_ID相同。最后添加节点自己
	fval_t fProb;				//02 概率。相当于条件概率分布表的一行中最后的概率

	CPT_ROW() {}
	CPT_ROW(const fidlist& ValueIDs, fval_t fProb):ValueIDs(ValueIDs), fProb(fProb) {}
	CPT_ROW(fidlist&& ValueIDs, fval_t fProb):ValueIDs(ValueIDs), fProb(fProb) {}
};

using CPTRowList = std::vector<CPT_ROW>;

//贝叶斯网络节点
struct BN_NODE
{
	fid_t nID;						//01 节点ID，如0
	std::string sName;				//02 节点名称，如Difficulty
	std::string sAbbreviation;		//03 节点简称，如D
	size_t nNumberOfValues;			//04 节点值的个数。节点取值用0、1、2代替，以学生例子中的Grade为例，取值不能是1、2、3。
	size_t nNumberOfParents;		//05 父节点个数，
	fidlist ParentIDs;				//06 父节点ID列表。遵循该顺序给定条件概率分布表
	fvallist CPTRowValues;			//07 条件概率分布表中每行的值
	CPTRowList CPTRowIDs;			//08 条件概率分布表中每行的变量ID序列
};

//贝叶斯网络的边
struct BN_EDGE
{
	fid_t nID;						//01 边的ID。保留、未用
	fid_t nStartNodeID;				//02 边的起点ID
	fid_t nEndNodeID;				//03 边的终点ID

	BN_EDGE() {}
	BN_EDGE(fid_t nID, fid_t nStartNodeID, fid_t nEndNodeID):
		nID(nID), nStartNodeID(nStartNodeID), nEndNodeID(nEndNodeID) {}
};

//查询
struct QUERY
{
	GVarList QueryVariables;		//查询的节点及其取值
	GVarList GivenVariables;		//给定的节点及其取值
	fidlist EliminateVariables;		//删除节点的顺序
};


//定义贝叶斯网络的精确推理类CBNSumProduct。采用和积变量消除法
class CBNSumProduct
{
public:
	//初始化
	void Init();
	//查询
	void Query();

private:
	//读取贝叶斯网络结构与参数
	void Read_BN();
	//读取查询变量、给定变量、变量消除顺序
	void Read_Query();

	//预处理
	void Preprocess();
	//预处理贝叶斯网络结构与参数
	void Preprocess_BN();
	//预处理因子
	void Preprocess_Factor();

	//查询的辅助函数
	void Query_Helper(const QUERY&, CFactorList);
	//查询边缘概率分布
	void Query_Marginal(const QUERY&, CFactorList&);

	//排列父节点ID及其取值
	void Arrange(fid_t, const fidlist&, const fidlist&, size_t, size_t&);
	//从CPT中查找概率
	double GetProbFromCPT(CPTRowList& cpts, fidlist&);
	//获取因子
	double GetFactor(fid_t nNodeID, fid_t nNodeValue, const GVarList& QueryVariables);
	//获取值的ID
	fid_t GetValueID(fid_t, const GVarList&);

	void OutputToXML();																								//输出概率分布到XML文件

	//和积变量消除
	void Sum_Product_Eliminate_Var(fid_t, CFactorList&);	

private:
	std::vector<BN_NODE> m_Nodes;		//BN的节点表
	std::vector<BN_EDGE> m_Edges;		//BN的边表
	CFactorList m_Factors;				//因子列表
	std::vector<QUERY> m_Queries;		//查询列表
	fvallist m_QueryResults;			//查询结果列表
};