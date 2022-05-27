/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CFactor.h
//��  �ܣ�		����������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��12��
//��  �£�		2021��03��13��
//��  �£�		2021��03��29��
//��  �ȣ�		210��
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

// ���Ͷ���
using fid_t = unsigned int;
using fval_t = double;
using fidset = std::set<fid_t>;
using fidmap = std::map<fid_t, fid_t>;
using fidlist = std::vector<fid_t>;
using fvallist = std::vector<fval_t>;

//����������
struct FACTOR_ROW
{
	fidlist ValueIDs;								//01 ����ֵID���б����ձ���ID�б��˳������
	fval_t fValue;												//02 ���ӵ�ֵ

	FACTOR_ROW() {}
	FACTOR_ROW(const fidlist& ValueIDs, fval_t fValue): ValueIDs(ValueIDs), fValue(fValue) {}
	FACTOR_ROW(fidlist&& ValueIDs, fval_t fValue): ValueIDs(ValueIDs), fValue(fValue) {}
	inline const fid_t& operator[](size_t index) const { return ValueIDs[index]; }
	inline fid_t& operator[](size_t index) { return ValueIDs[index]; }
	inline size_t size() const { return ValueIDs.size(); }
};


//����������
class CFactor
{
	//���캯������������
public:
	CFactor();													//���캯��
	~CFactor();													//��������

	//���з���
public:
	//��ʼ��
	void SetFactorVariableIDs(const fidlist&);
	void SetFactorVariableIDs(fidlist&&);			//�������ӵı���ID�б�
	void SetFactorRow(const fidlist&, fval_t);
	void SetFactorRow(fidlist&&, fval_t);			//���������е�ֵ
	//����
	const fidlist& GetFactorVariableIDs() const;				//��ȡ����ID�б�
	//����
	void ReduceGivenVariable(fid_t, fid_t);		//���ӻ���������������ID���ͱ���ֵID
	void SumOutVariable(fid_t);								//������͵���������ID
	void Normalize();											//���ӹ�һ��
	//��ѯ
	fval_t Query(const fidlist&, const fidlist&);	//���ݸ�������ID���ϡ�����ֵID�ļ��ϣ���ȡ�����ѯ�ĸ���ֵ

	//�������ӻ�
	CFactor operator*(const CFactor& second) const;

	//˽�з���
private:
	//�����ӻ�ʱ�ж������Ƿ���Ժϲ�
	bool IsConsistentValueID(const FACTOR_ROW&, const FACTOR_ROW&, const fidmap&) const;	//��������Ƿ����	
	//�����ʱ�����ӵ�ֵ�ϲ�������
	void MergeIntoFirstRow(FACTOR_ROW&);

	//˽������
private:
	fidlist m_VariableIDs;					//���ӱ���ID�б�
	std::vector<FACTOR_ROW> m_FactorRows;					//�����е��б�
};

using CFactorList = std::vector<CFactor>;