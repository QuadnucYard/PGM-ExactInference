/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CFactor_Query.cpp
//��  �ܣ�		��ѯ�����е��ض����ʡ����������а���A��B��C����������ֻ���ȡA��B��C�ض�ȡֵ�ĸ��ʵȡ���Ҫ��������ID�б�ͱ���ֵ��ID�б�
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��15��
//��  �£�		2021��03��23��
//��  �£�		2021��03��29��
//��  �ȣ�		80��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CFactor.h"								//������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�
#include <ranges>

//��  �ƣ�		Query()
//��  �ܣ�		��ѯ�ض�ֵ
//��  ����		vector<unsigned int>&,vector<unsigned int>&
//����ֵ��		double
double CFactor::Query(const fidlist& VariableIDs, const fidlist& ValueIDs)
{
	//����λ�ü���
	auto Positions = std::views::transform(VariableIDs,
		[&](fid_t i) { return qy::index_of(m_VariableIDs, i); });

	//��ʼ�����صĸ���ֵ
	double fProb = 0.0f;

	//���������У����
	for (const FACTOR_ROW& factor_row : m_FactorRows)
	{
		//����Ӧλ�ú�ֵ�Ƿ���ȷ
		bool bMatch = std::ranges::all_of(std::views::iota(0, (int)Positions.size()),
			[&](int j) { return factor_row[Positions[j]] == ValueIDs[j]; });
		//bool bMatch = std::ranges::all_of(std::views::zip(Positions, ValueIDs),
		//	[&](auto t) { return factor_row[std::get<0>(t)] == std::get<1>(t); };
		//�������Ƿ�ƥ�䡣���ƥ��Ļ�������Ҫ�ۼӸ���ֵ
		if (bMatch)
		{
			fProb += factor_row.fValue;
		}
	}

	return fProb;
}

//��  �ƣ�		GetFactorVariableIDs()
//��  �ܣ�		��ȡ����ID�б�
//��  ����		��
//����ֵ��		unsigned int
const fidlist& CFactor::GetFactorVariableIDs() const
{
	//���ر���ID�б�
	return m_VariableIDs;
}