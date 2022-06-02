////////////////////////////////////////////////////////////////////////////////
// CBNSumProduct.h
// 定义贝叶斯网络的精确推理类。采用和积变量消除法
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>
#include "CFactor.h"
#include "iohelper.h"


//贝叶斯网络节点
struct BNNode
{
	fid_t nID;						//01 节点ID，如0
	std::string sName;				//02 节点名称，如Difficulty
	std::string sAbbr;				//03 节点简称，如D
	size_t nNumberOfValues;			//04 节点值的个数。节点取值用0、1、2代替，以学生例子中的Grade为例，取值不能是1、2、3。
	size_t nNumberOfParents;		//05 父节点个数，
	fidlist ParentIDs;				//06 父节点ID列表。遵循该顺序给定条件概率分布表
	fvallist CPTRowValues;			//07 条件概率分布表中每行的值
	CPTRowList CPTRowIDs;			//08 条件概率分布表中每行的变量ID序列
};

//贝叶斯网络的边
struct BNEdge
{
	fid_t nID;						//01 边的ID。保留、未用
	fid_t nStartNodeID;				//02 边的起点ID
	fid_t nEndNodeID;				//03 边的终点ID
};


//定义贝叶斯网络的精确推理类CBNSumProduct。采用和积变量消除法
class CBNSumProduct
{

	//实例化变量类型
	struct GroundingVariable
	{
		fid_t nNodeID;				//01 变量ID
		fid_t nValueID;				//02 变量的值ID

		static GroundingVariable fromPair(fidpair pair) {
			return GroundingVariable {pair.first, pair.second};
		}
	};

	using GVarList = std::vector<GroundingVariable>;

	//查询
	struct BNQuery
	{
		GVarList QueryVariables;		//查询的节点及其取值
		GVarList GivenVariables;		//给定的节点及其取值
		fidlist EliminateVariables;		//删除节点的顺序
	};

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
	void Query_Helper(const BNQuery&, CFactorList);
	//查询边缘概率分布
	void Query_Marginal(const BNQuery&, CFactorList&);

	//排列父节点ID及其取值
	void Arrange(fid_t, const fidlist&, const fidlist&, size_t, size_t&);
	//获取因子
	double GetFactor(fid_t nNodeID, fid_t nNodeValue, const GVarList& QueryVariables);
	//获取值的ID
	fid_t GetValueID(fid_t, const GVarList&);

	//输出概率分布到XML文件
	void OutputToXML();				
	void OutputToYAML();

	//和积变量消除
	void Sum_Product_Eliminate_Var(fid_t, CFactorList&);	

private:
	std::vector<BNNode> m_Nodes;		//BN的节点表
	std::vector<BNEdge> m_Edges;		//BN的边表
	CFactorList m_Factors;				//因子列表
	std::vector<BNQuery> m_Queries;		//查询列表
	fvallist m_QueryResults;			//查询结果列表
};