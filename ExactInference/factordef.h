#pragma once
#include <vector>
#include <set>
#include <map>

// 类型定义
using fid_t = unsigned int;
using fval_t = double;
using fidlist = std::vector<fid_t>;
using fvallist = std::vector<fval_t>;
using fidset = std::set<fid_t>;
using fidmap = std::map<fid_t, fid_t>;


//因子行
struct FactorRow
{
	fidlist ValueIDs;	//01 变量值ID的列表，按照变量ID列表的顺序排列
	fval_t fValue;		//02 因子的值

	FactorRow() = default;
	FactorRow(const fidlist& ValueIDs, fval_t fValue): ValueIDs(ValueIDs), fValue(fValue) {}
	FactorRow(fidlist&& ValueIDs, fval_t fValue): ValueIDs(ValueIDs), fValue(fValue) {}
	inline const fid_t& operator[](size_t index) const { return ValueIDs[index]; }
	inline fid_t& operator[](size_t index) { return ValueIDs[index]; }
	inline size_t size() const { return ValueIDs.size(); }
};

using FactorRowList = std::vector<FactorRow>;


//条件概率分布表的行
struct CPTRow
{
	fidlist ValueIDs;			//01 节点值ID的列表，包括节点的双亲、节点自己。节点ID的列表和PARENT_ID相同。最后添加节点自己
	fval_t fProb;				//02 概率。相当于条件概率分布表的一行中最后的概率

	CPTRow() = default;
	CPTRow(const fidlist& ValueIDs, fval_t fProb):ValueIDs(ValueIDs), fProb(fProb) {}
	CPTRow(fidlist&& ValueIDs, fval_t fProb):ValueIDs(ValueIDs), fProb(fProb) {}
};

using CPTRowList = std::vector<CPTRow>;

