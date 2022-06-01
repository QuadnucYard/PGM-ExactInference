/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CClique.h
//��  �ܣ�		��������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��30��
//��  �£�		2021��04��11�ա�����������ȣ����������ӳ�����
//��  �£�		2021��04��12��
//��  �£�		2021��05��18��
//��  �ȣ�		300��
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


//��������
typedef struct
{
	vector<unsigned int> ValueIDs;								//01 ����ֵID���б����ձ���ID�б��˳������
	double fValue;												//02 ���е�ֵ
}CLIQUE_ROW;


//��������
class CClique
{
	//���캯������������
public:
	CClique();													//���캯��
	~CClique();													//��������

	//���з���
public:
	//��ʼ��
	void SetCliqueID(unsigned int&);							//�����ŵ�ID
	void SetCliqueVariableIDs(vector<unsigned int>&);			//�����ŵı���ID�б�
	void SetCliqueRow(vector<unsigned int>&, double&);			//�������е�ֵ
	//����
	vector<unsigned int> GetCliqueVariableIDs();				//��ȡ�ŵı���ID�б�
	set<unsigned int> GetVariableIDs();							//���ر���ID����
	unsigned int GetID();										//��ȡ�ŵ�ID
	//����
	void ReduceGivenVariable(unsigned int, unsigned int);		//�Ż���������������ID���ͱ���ֵID
	void SumOutVariable(unsigned int);							//����͵���������ID
	void Normalize();											//�Ź�һ��
	//��ѯ
	double Query(vector<unsigned int>&, vector<unsigned int>&);	//���ݸ�������ID���ϡ�����ֵID�ļ��ϣ���ȡ�����ѯ�ĸ���ֵ

	//�������ӻ�
	CClique operator*(const CClique& second)
	{
		//�����µġ������ص�������
		CClique clique;

		////////////////////////////////////////////////////////////////////////
		//ע�⣺�����ӻ���Ҫ������ID�����ǲ���ģ�������Ӳ�ͬ�������Ƕ�̬�仯��
		clique.m_nCliqueID = m_nCliqueID;
		////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//����1���������ŵĽ�������ͬ����ID�ļ���		
		//������ͬ����ID���ӵ����ŵ���β��λ�õ�ӳ�䡣�����3��������Ӧ�ڵ�5������
		map<unsigned int, unsigned int> FirstToSeconds;

		//����1.1���������ŵı���ID
		for (unsigned int i = 0; i <m_VariableIDs.size(); i++)
		{
			//��ȡ�ױ���ID
			unsigned int nFirstVariableID = m_VariableIDs[i];

			//����β�ŵı���ID
			for (unsigned int j = 0; j < second.m_VariableIDs.size(); j++)
			{
				//��ȡβ����ID
				unsigned int nSecondVariableID = second.m_VariableIDs[j];

				//�����������ID�Ƿ����
				if (nFirstVariableID == nSecondVariableID)
				{
					//��ӵ���ͬ������������ָ��β�ŵ�λ��ӳ��
					//ע�⣺���ô�λ�õ�λ�õ�ӳ�䣬�����Ǵӱ���ID������ID��ӳ��
					FirstToSeconds.insert(make_pair(i, j));
				}
			}
		}

		//����1.2����ȡβ���к�������ͬ������λ�ü���
		set<unsigned int> RedundantSeconds;
		for (map<unsigned int, unsigned int>::iterator it = FirstToSeconds.begin(); it != FirstToSeconds.end(); it++)
		{
			//��ӵ���ͬ������λ�ü���
			RedundantSeconds.insert(it->second);
		}


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//����2��ֱ��ƴ��
		//����Ƿ�����ͬ����ID
		if (FirstToSeconds.size() == 0)//���һ��������û����ͬ��������ֱ��ƴ��
		{
			//����2.1��ֱ��ƴ�ӱ���ֵID
			for (unsigned int i = 0; i < m_CliqueRows.size(); i++)
			{
				for (unsigned int j = 0; j < second.m_CliqueRows.size(); j++)
				{
					//�����µ�����
					CLIQUE_ROW clique_row;

					//��ӱ���ֵ��ID����
					clique_row.ValueIDs = m_CliqueRows[i].ValueIDs;//��������ֵ������
					//���β��ֵ������
					for (unsigned int m = 0; m < second.m_CliqueRows[j].ValueIDs.size(); m++)
					{
						//���β��ֵ��ID
						clique_row.ValueIDs.push_back(second.m_CliqueRows[j].ValueIDs[m]);
					}

					//�������е�ֵ����Ҫ���ó˷�
					clique_row.fValue = m_CliqueRows[i].fValue*second.m_CliqueRows[j].fValue;

					//��������ӵ���
					clique.m_CliqueRows.push_back(clique_row);
				}
			}

			//����2.2��ƴ�ӱ���ID
			clique.m_VariableIDs = m_VariableIDs;//��ʼ��Ϊ���ŵı���ID����
			//���β�ŵı���ID
			for (unsigned int i = 0; i < second.m_VariableIDs.size(); i++)
			{
				//���β�ŵı���ID
				clique.m_VariableIDs.push_back(second.m_VariableIDs[i]);
			}
		}
		////////////////////////////////////////////////////////////////////
		//����3�����ƴ��
		else //�����������������ͬ����������ƴ��
		{
			//����3.1�����ƴ��
			for (unsigned int i = 0; i < m_CliqueRows.size(); i++)
			{
				for (unsigned int j = 0; j < second.m_CliqueRows.size(); j++)
				{
					//����Ӧ�ı���ֵ��ID�Ƿ����
					if (IsConsistentValueID(m_CliqueRows[i], second.m_CliqueRows[j], FirstToSeconds))
					{
						//����������
						CLIQUE_ROW clique_row;
						clique_row.ValueIDs = m_CliqueRows[i].ValueIDs;//��ʼ�����е�ֵID����
						//����β�ŵ�ֵ
						for (unsigned int m = 0; m < second.m_CliqueRows[j].ValueIDs.size(); m++)
						{
							//������Ƿ�����ͬ����������
							if (!IsINTInSet(m, RedundantSeconds))
							{
								//���β�ŵ���
								clique_row.ValueIDs.push_back(second.m_CliqueRows[j].ValueIDs[m]);
							}
						}

						//�����ȡ���е�ֵ
						clique_row.fValue = m_CliqueRows[i].fValue*second.m_CliqueRows[j].fValue;

						//��������е�����
						clique.m_CliqueRows.push_back(clique_row);
					}
				}
			}

			//����3.2����ӱ���ID���б�
			clique.m_VariableIDs = m_VariableIDs;
			//����β��
			for (unsigned int i = 0; i < second.m_VariableIDs.size(); i++)
			{
				//���β�ű���ID��λ���Ƿ�������ͬ����ID����
				if (!IsINTInSet(i, RedundantSeconds))
				{
					//���β�ŵı���ID
					clique.m_VariableIDs.push_back(second.m_VariableIDs[i]);
				}
			}
		}

		//������
		return clique;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//�������ӳ�
	CClique operator/(const CClique& second)
	{
		//�����µġ������ص���
		CClique clique;

		///////////////////////////
		//ע�⣺�������еı�����
		clique.m_VariableIDs = m_VariableIDs;
		///////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//����1���������ŵĽ�������ͬ����ID�ļ���		
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

		/////////////////////////////////////////////////////////////////////////////////
		//����2�����ӳ�
		//˵���������ŵ�Ͻ��һ���������ŵ�Ͻ��
		for (unsigned int i = 0; i < m_CliqueRows.size(); i++)
		{
			for (unsigned int j = 0; j < second.m_CliqueRows.size(); j++)
			{
				//����Ӧ�ı���ֵ��ID�Ƿ����
				if (IsConsistentValueID(m_CliqueRows[i], second.m_CliqueRows[j], FirstToSeconds))
				{
					//��������
					CLIQUE_ROW clique_row;
					
					//��ʼ�����е�ֵID����
					clique_row.ValueIDs = m_CliqueRows[i].ValueIDs;					
					//�����ȡ�����е�ֵ
					clique_row.fValue = m_CliqueRows[i].fValue/second.m_CliqueRows[j].fValue;

					//������е���
					clique.m_CliqueRows.push_back(clique_row);
				}
			}
		}

		//������
		return clique;
	};

	//˽�з���
private:
	//�����ӻ�ʱ�ж������Ƿ���Ժϲ�
	bool IsConsistentValueID(const CLIQUE_ROW&, const CLIQUE_ROW&, map<unsigned int, unsigned int>&);	//��������Ƿ����	
	//�����ʱ�����ӵ�ֵ�ϲ�������
	void MergeIntoFirstRow(CLIQUE_ROW&);

	//˽������
private:
	unsigned int m_nCliqueID;							//��ID
	vector<unsigned int> m_VariableIDs;					//�ű���ID�б�
	vector<CLIQUE_ROW> m_CliqueRows;					//���е��б�
};