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

#include <map>							//mapͷ�ļ�
#include <set>							//setͷ�ļ�
#include <string>						//stringͷ�ļ�
#include <list>							//listͷ�ļ�
#include <vector>						//vectorͷ�ļ�
#include <algorithm>					//algorithm��ͷ�ļ�
#include <numeric>						//numeric��ͷ�ļ�
#include <sstream>						//sstream��ͷ�ļ�
#include <fstream>						//fstream��ͷ�ļ�
#include <time.h>						//ʱ�亯����ͷ�ļ�
#include "math.h"						//��ѧ����ͷ�ļ�
#include "Helper.h"						//��������ͷ�ļ�


//���������ռ�
using namespace std;					//ʹ�ñ�׼�����ռ�


//����������
typedef struct
{
	vector<unsigned int> ValueIDs;								//01 ����ֵID���б����ձ���ID�б��˳������
	double fValue;												//02 ���ӵ�ֵ
}FACTOR_ROW;


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
	void SetFactorVariableIDs(vector<unsigned int>&);			//�������ӵı���ID�б�
	void SetFactorRow(vector<unsigned int>&, double&);			//���������е�ֵ
	//����
	vector<unsigned int> GetFactorVariableIDs();				//��ȡ����ID�б�
	//����
	void ReduceGivenVariable(unsigned int, unsigned int);		//���ӻ���������������ID���ͱ���ֵID
	void SumOutVariable(unsigned int);								//������͵���������ID
	void Normalize();											//���ӹ�һ��
	//��ѯ
	double Query(vector<unsigned int>&,vector<unsigned int>&);	//���ݸ�������ID���ϡ�����ֵID�ļ��ϣ���ȡ�����ѯ�ĸ���ֵ

	//�������ӻ�
	CFactor operator*(const CFactor& second)
	{
		//�����µġ������ص�����
		CFactor factor;


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//����1�����������ӵĽ�������ͬ����ID�ļ���		
		//������ͬ����ID���ӵ������ӵ���β����λ�õ�ӳ�䡣�����3��������Ӧ�ڵ�5������
		map<unsigned int, unsigned int> FirstToSeconds;

		//����1.1�����������ӵı���ID
		for (unsigned int i = 0; i <m_VariableIDs.size(); i++)
		{
			//��ȡ�ױ���ID
			unsigned int nFirstVariableID = m_VariableIDs[i];

			//����β���ӵı���ID
			for (unsigned int j = 0; j < second.m_VariableIDs.size(); j++)
			{
				//��ȡβ����ID
				unsigned int nSecondVariableID = second.m_VariableIDs[j];

				//�����������ID�Ƿ����
				if (nFirstVariableID == nSecondVariableID)
				{
					//��ӵ���ͬ��������������ָ��β���ӵ�λ��ӳ��
					//ע�⣺���ô�λ�õ�λ�õ�ӳ�䣬�����Ǵӱ���ID������ID��ӳ��
					FirstToSeconds.insert(make_pair(i, j));
				}
			}
		}
		
		//����1.2����ȡβ�����к���������ͬ������λ�ü���
		set<unsigned int> RedundantSeconds;
		for (map<unsigned int, unsigned int>::iterator it = FirstToSeconds.begin(); it != FirstToSeconds.end(); it++)
		{
			//��ӵ���ͬ������λ�ü���
			RedundantSeconds.insert(it->second);
		}

		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//����2��ֱ��ƴ��
		//����Ƿ�����ͬ����ID
		if (FirstToSeconds.size() == 0)//���һ����������û����ͬ��������ֱ��ƴ��
		{
			//����2.1��ֱ��ƴ�ӱ���ֵID
			for (unsigned int i = 0; i < m_FactorRows.size(); i++)
			{
				for (unsigned int j = 0; j < second.m_FactorRows.size(); j++)
				{
					//�����µ�������
					FACTOR_ROW factor_row;

					//��ӱ���ֵ��ID����
					factor_row.ValueIDs = m_FactorRows[i].ValueIDs;//����������ֵ������
					//���β����ֵ������
					for (unsigned int m = 0; m < second.m_FactorRows[j].ValueIDs.size(); m++)
					{
						//���β����ֵ��ID
						factor_row.ValueIDs.push_back(second.m_FactorRows[j].ValueIDs[m]);
					}

					//���������е�ֵ����Ҫ���óͷ�
					factor_row.fValue = m_FactorRows[i].fValue*second.m_FactorRows[j].fValue;

					//����������ӵ�����
					factor.m_FactorRows.push_back(factor_row);
				}
			}

			//����2.2��ƴ�ӱ���ID
			factor.m_VariableIDs = m_VariableIDs;//��ʼ��Ϊ�����ӵı���ID����
			//���β���ӵı���ID
			for (unsigned int i = 0; i < second.m_VariableIDs.size(); i++)
			{
				//���β���ӵı���ID
				factor.m_VariableIDs.push_back(second.m_VariableIDs[i]);
			}
		}
		////////////////////////////////////////////////////////////////////
		//����3�����ƴ��
		else //�������������������ͬ����������ƴ��
		{
			//����3.1�����ƴ��
			for (unsigned int i = 0; i < m_FactorRows.size(); i++)
			{
				for (unsigned int j = 0; j < second.m_FactorRows.size(); j++)
				{
					//����Ӧ�ı���ֵ��ID�Ƿ����
					if (IsConsistentValueID(m_FactorRows[i], second.m_FactorRows[j], FirstToSeconds))
					{
						//����������
						FACTOR_ROW factor_row;
						factor_row.ValueIDs = m_FactorRows[i].ValueIDs;//��ʼ�������е�ֵID����
						//����β���ӵ�ֵ
						for (unsigned int m = 0; m < second.m_FactorRows[j].ValueIDs.size(); m++)
						{
							//������Ƿ�����ͬ����������
							if (!IsINTInSet(m, RedundantSeconds))
							{
								//���β���ӵ���
								factor_row.ValueIDs.push_back(second.m_FactorRows[j].ValueIDs[m]);
							}
						}

						//�����ȡ�����е�ֵ
						factor_row.fValue = m_FactorRows[i].fValue*second.m_FactorRows[j].fValue;

						//��������е�����
						factor.m_FactorRows.push_back(factor_row);
					}
				}
			}

			//����3.2����ӱ���ID���б�
			factor.m_VariableIDs = m_VariableIDs;
			//����β����
			for (unsigned int i = 0; i < second.m_VariableIDs.size(); i++)
			{
				//���β���ӱ���ID��λ���Ƿ�������ͬ����ID����
				if (!IsINTInSet(i, RedundantSeconds))
				{
					//���β���ӵı���ID
					factor.m_VariableIDs.push_back(second.m_VariableIDs[i]);
				}
			}
		}

		//��������
		return factor;
	};		
	
	//˽�з���
private:
	//�����ӻ�ʱ�ж������Ƿ���Ժϲ�
	bool IsConsistentValueID(const FACTOR_ROW&, const FACTOR_ROW&, map<unsigned int, unsigned int>&);	//��������Ƿ����	
	//�����ʱ�����ӵ�ֵ�ϲ�������
	void MergeIntoFirstRow(FACTOR_ROW&);
	
	//˽������
private:	
	vector<unsigned int> m_VariableIDs;					//���ӱ���ID�б�
	vector<FACTOR_ROW> m_FactorRows;					//�����е��б�
};