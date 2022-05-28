/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CFactor_Operator.cpp
//��  �ܣ�		���ز�������ء���Ҫ�����ӻ�
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��12��
//��  �£�		2021��03��13��
//��  �£�		2021��03��23��
//��  �£�		2021��03��29��
//��  �ȣ�		50��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CFactor.h"								//������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�
#include <algorithm>

//��  �ƣ�		IsConsistentValueID()
//��  �ܣ�		������������е�ֵID�Ƿ���ݣ������жϳ˻�ʱ�ܷ�ϲ�
//��  ����		const FACTOR_ROW&, 
//				const FACTOR_ROW&, 
//				map<unsigned int, unsigned int>&
//����ֵ��		bool
bool CFactor::IsConsistentValueID(const FACTOR_ROW& FirstRow, const FACTOR_ROW& SecondRow, const fidmap& FirstToSeconds) const
{
	// ����Ӧλ��id���
	return std::all_of(FirstToSeconds.begin(), FirstToSeconds.end(),
		[&](auto t) { return FirstRow[t.first] == SecondRow[t.second]; });
}

CFactor CFactor::operator*(const CFactor& second) const
{
	//�����µġ������ص�����
	CFactor factor;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//����1�����������ӵĽ�������ͬ����ID�ļ���		
	//������ͬ����ID���ӵ������ӵ���β����λ�õ�ӳ�䡣�����3��������Ӧ�ڵ�5������
	fidmap FirstToSeconds;

	//����1.1�����������ӵı���ID
	for (size_t i = 0; i < m_VariableIDs.size(); i++)
	{
		//��ȡ�ױ���ID
		fid_t nFirstVariableID = m_VariableIDs[i];

		//����β���ӵı���ID
		for (fid_t j = 0; j < second.m_VariableIDs.size(); j++)
		{
			//��ȡβ����ID
			fid_t nSecondVariableID = second.m_VariableIDs[j];

			//�����������ID�Ƿ����
			if (nFirstVariableID == nSecondVariableID)
			{
				//��ӵ���ͬ��������������ָ��β���ӵ�λ��ӳ��
				//ע�⣺���ô�λ�õ�λ�õ�ӳ�䣬�����Ǵӱ���ID������ID��ӳ��
				FirstToSeconds.insert(std::make_pair(i, j));
			}
		}
	}

	//����1.2����ȡβ�����к���������ͬ������λ�ü���
	//fidset RedundantSeconds(qy::values_begin(FirstToSeconds), qy::values_end(FirstToSeconds));
	fidset RedundantSeconds(std::views::values(FirstToSeconds) | qy::views::to<fidset>);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//����2��ֱ��ƴ��
	//����Ƿ�����ͬ����ID
	if (FirstToSeconds.size() == 0)//���һ����������û����ͬ��������ֱ��ƴ��
	{
		//����2.1��ֱ��ƴ�ӱ���ֵID
		for (auto& r1 : m_FactorRows)
		{
			for (auto& r2 : second.m_FactorRows)
			{
				//�����µ�������
				FACTOR_ROW factor_row(r1.ValueIDs, r1.fValue * r2.fValue); //���������е�ֵ����Ҫ���óͷ�

				//���β����ֵ������
				factor_row.ValueIDs.insert(factor_row.ValueIDs.end(), r2.ValueIDs.begin(), r2.ValueIDs.end());

				//����������ӵ�����
				factor.m_FactorRows.push_back(std::move(factor_row));
			}
		}

		//����2.2��ƴ�ӱ���ID
		factor.m_VariableIDs = m_VariableIDs;//��ʼ��Ϊ�����ӵı���ID����
		//���β���ӵı���ID
		factor.m_VariableIDs.insert(factor.m_VariableIDs.end(), second.m_VariableIDs.begin(), second.m_VariableIDs.end());
	}
	////////////////////////////////////////////////////////////////////
	//����3�����ƴ��
	else //�������������������ͬ����������ƴ��
	{
		//����3.1�����ƴ��
		for (auto& r1 : m_FactorRows)
		{
			for (auto& r2 : second.m_FactorRows)
			{
				//����Ӧ�ı���ֵ��ID�Ƿ����
				if (IsConsistentValueID(r1, r2, FirstToSeconds))
				{
					//����������
					FACTOR_ROW factor_row(r1.ValueIDs, r1.fValue * r2.fValue);

					//����β���ӵ�ֵ
					//��Ӳ�����ͬ����������β���ӵ���
					for (size_t m = 0; m < r2.ValueIDs.size(); m++)
					{
						//������Ƿ�����ͬ����������
						if (!qy::includes(RedundantSeconds, m))
						{
							//���β���ӵ���
							factor_row.ValueIDs.push_back(r2.ValueIDs[m]);
						}
					}

					//��������е�����
					factor.m_FactorRows.push_back(std::move(factor_row));
				}
			}
		}

		//����3.2����ӱ���ID���б�
		factor.m_VariableIDs = m_VariableIDs;
		//����β����
		for (size_t i = 0; i < second.m_VariableIDs.size(); i++)
		{
			//���β���ӱ���ID��λ���Ƿ�������ͬ����ID����
			if (!qy::includes(RedundantSeconds, i))
			{
				//���β���ӵı���ID
				factor.m_VariableIDs.push_back(second.m_VariableIDs[i]);
			}
		}
	}

	//��������
	return factor;
};