////////////////////////////////////////////////////////////////////////////////
// CClique.h
// ��������
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <algorithm>		
#include <numeric>			
#include "factordef.h"
#include "stl_utils.h"
#include "qyranges.hpp"

using namespace std;

//��������
struct CLIQUE_ROW
{
	fidlist ValueIDs;		//01 ����ֵID���б����ձ���ID�б��˳������
	fval_t fValue;			//02 ���е�ֵ

	CLIQUE_ROW() = default;
	CLIQUE_ROW(const fidlist& ValueIDs, fval_t fValue): ValueIDs(ValueIDs), fValue(fValue) {}
	inline const fid_t& operator[](size_t index) const { return ValueIDs[index]; }
	inline fid_t& operator[](size_t index) { return ValueIDs[index]; }
	inline size_t size() const { return ValueIDs.size(); }
};

using CliqueRowList = std::vector<CLIQUE_ROW>;

//��������
class CClique
{

	//���з���
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
	double Query(const fidlist&, const fidlist&);

	//�������ӻ�
	CClique operator*(const CClique& second);
	//�������ӳ�
	CClique operator/(const CClique& second);

private:
	//�����ӻ�ʱ�ж������Ƿ���Ժϲ�
	bool IsConsistentValueID(const CLIQUE_ROW&, const CLIQUE_ROW&, map<unsigned int, unsigned int>&);	//��������Ƿ����	

private:
	fid_t m_nCliqueID;				//��ID
	fidlist m_VariableIDs;			//�ű���ID�б�
	CliqueRowList m_CliqueRows;		//���е��б�
};

