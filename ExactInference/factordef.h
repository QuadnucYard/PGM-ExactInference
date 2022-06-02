#pragma once
#include <vector>
#include <set>
#include <map>

// ���Ͷ���
using fid_t = unsigned int;
using fval_t = double;
using fidlist = std::vector<fid_t>;
using fvallist = std::vector<fval_t>;
using fidset = std::set<fid_t>;
using fidmap = std::map<fid_t, fid_t>;
using fidpair = std::pair<fid_t, fid_t>;
using fidsetmap = std::map<fid_t, fidset>;
using fidmultimap = std::multimap<fid_t, fid_t>;
using fidpairlist = std::vector<fidpair>;


//������
struct FactorRow
{
	fidlist ValueIDs;	//01 ����ֵID���б����ձ���ID�б��˳������
	fval_t fValue;		//02 ���ӵ�ֵ

	inline const fid_t& operator[](size_t index) const { return ValueIDs[index]; }
	inline fid_t& operator[](size_t index) { return ValueIDs[index]; }
	inline size_t size() const { return ValueIDs.size(); }
};

using FactorRowList = std::vector<FactorRow>;


//�������ʷֲ������
struct CPTRow
{
	fidlist ValueIDs;			//01 �ڵ�ֵID���б������ڵ��˫�ס��ڵ��Լ����ڵ�ID���б��PARENT_ID��ͬ�������ӽڵ��Լ�
	fval_t fProb;				//02 ���ʡ��൱���������ʷֲ����һ�������ĸ���

	CPTRow() = default;
	CPTRow(const fidlist& ValueIDs, fval_t fProb):ValueIDs(ValueIDs), fProb(fProb) {}
	CPTRow(fidlist&& ValueIDs, fval_t fProb):ValueIDs(ValueIDs), fProb(fProb) {}
};

using CPTRowList = std::vector<CPTRow>;

