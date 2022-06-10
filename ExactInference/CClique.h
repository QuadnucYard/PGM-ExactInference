////////////////////////////////////////////////////////////////////////////////
// CClique.h
// 定义团类
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "factordef.h"
#include "stl_utils.h"
#include "qyranges.hpp"
#include "qynumeric.hpp"


using CliqueRow = FactorRow;
using CliqueRowList = FactorRowList;

//定义团类
class CClique
{
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
	double Query(const fidlist&, const fidlist&) const;

	//重载因子积
	CClique operator*(const CClique& second) const;
	//重载因子除
	CClique operator/(const CClique& second) const;

private:
	//在因子积时判断两行是否可以合并
	bool IsConsistentValueID(const CliqueRow&, const CliqueRow&, const fidmap&) const;	//检查两行是否兼容	

private:
	fid_t m_nCliqueID;				//团ID
	fidlist m_VariableIDs;			//团变量ID列表
	CliqueRowList m_CliqueRows;		//团行的列表
};

