////////////////////////////////////////////////////////////////////////////////
// CFactor.h
// ����������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#pragma once


#include "factordef.h"
#include "Helper.h"
#include "stl_utils.h"
#include "qyranges.hpp"
#include "qynumeric.hpp"


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
	fval_t Query(const fidlist&, const fidlist&) const;

	//�������ӻ�
	CFactor operator*(const CFactor& second) const;

private:
	fidlist m_VariableIDs;					//���ӱ���ID�б�
	FactorRowList m_FactorRows;				//�����е��б�
	fidlist m_IdOrder;						//id˳�� 
};

using CFactorList = std::vector<CFactor>;