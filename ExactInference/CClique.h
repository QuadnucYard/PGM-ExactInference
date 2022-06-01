/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CClique.h
//功  能：		定义团类
//开发者：		高志强
//日  期：		2021年03月30日
//更  新：		2021年04月11日。和因子类相比，增加了因子除重载
//更  新：		2021年04月12日
//更  新：		2021年05月18日
//长  度：		300行
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <algorithm>		
#include <numeric>			
#include "factordef.h"
#include "Helper.h"			
#include "stl_utils.h"
#include "qyranges.hpp"

using namespace std;

//定义团行
struct CLIQUE_ROW
{
	fidlist ValueIDs;		//01 变量值ID的列表，按照变量ID列表的顺序排列
	fval_t fValue;			//02 团行的值

	CLIQUE_ROW() = default;
	CLIQUE_ROW(const fidlist& ValueIDs, fval_t fValue): ValueIDs(ValueIDs), fValue(fValue) {}
	inline const fid_t& operator[](size_t index) const { return ValueIDs[index]; }
	inline fid_t& operator[](size_t index) { return ValueIDs[index]; }
	inline size_t size() const { return ValueIDs.size(); }
};

using CliqueRowList = std::vector<CLIQUE_ROW>;

//定义团类
class CClique
{

	//公有方法
public:
	//设置团的ID
	void SetCliqueID(fid_t);
	//设置团的变量ID列表
	void SetCliqueVariableIDs(const fidlist&);
	//设置团行的值
	void SetCliqueRow(const fidlist&, fval_t);

	//获取团的变量ID列表
	const fidlist& GetCliqueVariableIDs() const;
	//返回变量ID集合
	fidset GetVariableIDs() const;
	//获取团的ID
	fid_t GetID() const;

	//团化简。消除给定变量ID、和变量值ID
	void ReduceGivenVariable(fid_t, fid_t);
	//团求和掉给定变量ID
	void SumOutVariable(fid_t);
	//团归一化
	void Normalize();

	//根据给定变量ID集合、变量值ID的集合，获取具体查询的概率值
	double Query(const fidlist&, const fidlist&);

	//重载因子积
	CClique operator*(const CClique& second);
	//重载因子除
	CClique operator/(const CClique& second);

private:
	//在因子积时判断两行是否可以合并
	bool IsConsistentValueID(const CLIQUE_ROW&, const CLIQUE_ROW&, map<unsigned int, unsigned int>&);	//检查两行是否兼容	

private:
	fid_t m_nCliqueID;				//团ID
	fidlist m_VariableIDs;			//团变量ID列表
	CliqueRowList m_CliqueRows;		//团行的列表
};

