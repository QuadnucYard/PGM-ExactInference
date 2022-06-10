////////////////////////////////////////////////////////////////////////////////
// CClique.h
// ��������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "factordef.h"
#include "stl_utils.h"
#include "qyranges.hpp"
#include "qynumeric.hpp"


using CliqueRow = FactorRow;
using CliqueRowList = FactorRowList;

//��������
class CClique
{
public:
	//�����ŵ�ID
	void SetCliqueID(fid_t);
	//�����ŵı���ID�б�
	void SetCliqueVariableIDs(const fidlist&);
	//�������е�ֵ
	void SetCliqueRow(const fidlist&, fval_t);

	//��ȡ�ŵı���ID�б�
	const fidlist& GetCliqueVariableIDs() const;
	//���ر���ID����
	fidset GetVariableIDs() const;
	//��ȡ�ŵ�ID
	fid_t GetID() const;

	//�Ż���������������ID���ͱ���ֵID
	void ReduceGivenVariable(fid_t, fid_t);
	//����͵���������ID
	void SumOutVariable(fid_t);
	//�Ź�һ��
	void Normalize();

	//���ݸ�������ID���ϡ�����ֵID�ļ��ϣ���ȡ�����ѯ�ĸ���ֵ
	double Query(const fidlist&, const fidlist&) const;

	//�������ӻ�
	CClique operator*(const CClique& second) const;
	//�������ӳ�
	CClique operator/(const CClique& second) const;

private:
	//�����ӻ�ʱ�ж������Ƿ���Ժϲ�
	bool IsConsistentValueID(const CliqueRow&, const CliqueRow&, const fidmap&) const;	//��������Ƿ����	

private:
	fid_t m_nCliqueID;				//��ID
	fidlist m_VariableIDs;			//�ű���ID�б�
	CliqueRowList m_CliqueRows;		//���е��б�
};

