////////////////////////////////////////////////////////////////////////////////
// CFactor.h
// ����������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>
#include <algorithm>
#include <numeric>
#include "Helper.h"
#include "stl_utils.h"
#include "xiterator.h"

// ���Ͷ���
using fid_t = unsigned int;
using fval_t = double;
using fidlist = std::vector<fid_t>;
using fvallist = std::vector<fval_t>;

//������
struct FACTOR_ROW
{
	fidlist ValueIDs;	//01 ����ֵID���б����ձ���ID�б��˳������
	fval_t fValue;		//02 ���ӵ�ֵ

	FACTOR_ROW() = default;
	FACTOR_ROW(const fidlist& ValueIDs, fval_t fValue): ValueIDs(ValueIDs), fValue(fValue) {}
	FACTOR_ROW(fidlist&& ValueIDs, fval_t fValue): ValueIDs(ValueIDs), fValue(fValue) {}
	inline const fid_t& operator[](size_t index) const { return ValueIDs[index]; }
	inline fid_t& operator[](size_t index) { return ValueIDs[index]; }
	inline size_t size() const { return ValueIDs.size(); }
};


//������
class CFactor
{
public:
	//�������ӵı���ID�б�
	void SetFactorVariableIDs(const fidlist&);
	//���������е�ֵ
	void SetFactorRow(const fidlist&, fval_t);
	//��ȡ����ID�б�
	const fidlist& GetFactorVariableIDs() const;
	//���ӻ���������������ID���ͱ���ֵID
	void ReduceGivenVariable(fid_t, fid_t);
	//������͵���������ID
	void SumOutVariable(fid_t);
	//���ӹ�һ��
	void Normalize();								
	//���ݸ�������ID���ϡ�����ֵID�ļ��ϣ���ȡ�����ѯ�ĸ���ֵ
	fval_t Query(const fidlist&, const fidlist&);

	//�������ӻ�
	CFactor operator*(const CFactor& second) const;

private:
	fidlist m_VariableIDs;					//���ӱ���ID�б�
	std::vector<FACTOR_ROW> m_FactorRows;	//�����е��б�
	fidlist m_IdOrder;						//id˳�� 
};

using CFactorList = std::vector<CFactor>;