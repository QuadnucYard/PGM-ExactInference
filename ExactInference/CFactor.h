/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CFactor.h
//功  能：		定义因子类
//开发者：		高志强
//日  期：		2021年03月12日
//更  新：		2021年03月13日
//更  新：		2021年03月29日
//长  度：		210行
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include "Helper.h"
#include "stl_utils.h"
#include "xiterator.h"

// 类型定义
using fid_t = unsigned int;
using fval_t = double;
using fidset = std::set<fid_t>;
using fidmap = std::map<fid_t, fid_t>;
using fidlist = std::vector<fid_t>;
using fvallist = std::vector<fval_t>;

//定义因子行
struct FACTOR_ROW
{
	fidlist ValueIDs;								//01 变量值ID的列表，按照变量ID列表的顺序排列
	fval_t fValue;												//02 因子的值

	FACTOR_ROW() {}
	FACTOR_ROW(const fidlist& ValueIDs, fval_t fValue): ValueIDs(ValueIDs), fValue(fValue) {}
	FACTOR_ROW(fidlist&& ValueIDs, fval_t fValue): ValueIDs(ValueIDs), fValue(fValue) {}
	inline const fid_t& operator[](size_t index) const { return ValueIDs[index]; }
	inline fid_t& operator[](size_t index) { return ValueIDs[index]; }
	inline size_t size() const { return ValueIDs.size(); }
};


//定义因子类
class CFactor
{
	//构造函数与析构函数
public:
	CFactor();													//构造函数
	~CFactor();													//析构函数

	//公有方法
public:
	//初始化
	void SetFactorVariableIDs(const fidlist&);
	void SetFactorVariableIDs(fidlist&&);			//设置因子的变量ID列表
	void SetFactorRow(const fidlist&, fval_t);
	void SetFactorRow(fidlist&&, fval_t);			//设置因子行的值
	//访问
	const fidlist& GetFactorVariableIDs() const;				//获取变量ID列表
	//操作
	void ReduceGivenVariable(fid_t, fid_t);		//因子化简。消除给定变量ID、和变量值ID
	void SumOutVariable(fid_t);								//因子求和掉给定变量ID
	void Normalize();											//因子归一化
	//查询
	fval_t Query(const fidlist&, const fidlist&);	//根据给定变量ID集合、变量值ID的集合，获取具体查询的概率值

	//重载因子积
	CFactor operator*(const CFactor& second) const;

	//私有方法
private:
	//在因子积时判断两行是否可以合并
	bool IsConsistentValueID(const FACTOR_ROW&, const FACTOR_ROW&, const fidmap&) const;	//检查两行是否兼容	
	//在求和时将因子的值合并到首行
	void MergeIntoFirstRow(FACTOR_ROW&);

	//私有数据
private:
	fidlist m_VariableIDs;					//因子变量ID列表
	std::vector<FACTOR_ROW> m_FactorRows;					//因子行的列表
};

using CFactorList = std::vector<CFactor>;