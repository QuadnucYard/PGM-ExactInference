////////////////////////////////////////////////////////////////////////////////
// CFactor.h
// 定义因子类
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>
#include <algorithm>
#include <numeric>
#include "Helper.h"
#include "stl_utils.h"
#include "xiterator.h"

// 类型定义
using fid_t = unsigned int;
using fval_t = double;
using fidlist = std::vector<fid_t>;
using fvallist = std::vector<fval_t>;

//因子行
struct FACTOR_ROW
{
	fidlist ValueIDs;	//01 变量值ID的列表，按照变量ID列表的顺序排列
	fval_t fValue;		//02 因子的值

	FACTOR_ROW() = default;
	FACTOR_ROW(const fidlist& ValueIDs, fval_t fValue): ValueIDs(ValueIDs), fValue(fValue) {}
	FACTOR_ROW(fidlist&& ValueIDs, fval_t fValue): ValueIDs(ValueIDs), fValue(fValue) {}
	inline const fid_t& operator[](size_t index) const { return ValueIDs[index]; }
	inline fid_t& operator[](size_t index) { return ValueIDs[index]; }
	inline size_t size() const { return ValueIDs.size(); }
};


//因子类
class CFactor
{
public:
	//设置因子的变量ID列表
	void SetFactorVariableIDs(const fidlist&);
	//设置因子行的值
	void SetFactorRow(const fidlist&, fval_t);
	//获取变量ID列表
	const fidlist& GetFactorVariableIDs() const;
	//因子化简。消除给定变量ID、和变量值ID
	void ReduceGivenVariable(fid_t, fid_t);
	//因子求和掉给定变量ID
	void SumOutVariable(fid_t);
	//因子归一化
	void Normalize();								
	//根据给定变量ID集合、变量值ID的集合，获取具体查询的概率值
	fval_t Query(const fidlist&, const fidlist&);

	//重载因子积
	CFactor operator*(const CFactor& second) const;

private:
	fidlist m_VariableIDs;					//因子变量ID列表
	std::vector<FACTOR_ROW> m_FactorRows;	//因子行的列表
	fidlist m_IdOrder;						//id顺序 
};

using CFactorList = std::vector<CFactor>;