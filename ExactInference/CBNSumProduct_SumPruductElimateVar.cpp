/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CBNSumProduct_SumProductEliminateVar.cpp
//��  �ܣ�		�ͻ���������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��14��
//��  �£�		2021��03��24��
//��  �ȣ�		80��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CBNSumProduct.h"							//��Ҷ˹���羫ȷ������ͷ�ļ������úͻ�����������
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		Sum_Product_Eliminate_Var()
//��  �ܣ�		�ͻ���������
//��  ����		unsigned int,vector<CFactor>&
//����ֵ��		��
void CBNSumProduct::Sum_Product_Eliminate_Var(unsigned int nVariableID,vector<CFactor>& OldFactors)
{
	//���������б�
	vector<CFactor> NewFactors;

	
	/////////////////////////////////////////////////////////////////////////////
	//����1�����������б����������б���ɾ���͸�������ֵ��һ�µ���
	vector<CFactor>::iterator it = OldFactors.begin();
	while (it != OldFactors.end())
	{
		//�����������λ��
		unsigned int nPos;
		//���岢��ʼ�����ӵı���ID�б�
		vector<unsigned int> VariableIDs = it->GetFactorVariableIDs();
		//������ӵı������Ƿ������������������еĻ�����ͨ������������λ��
		if (IsINTInVector(nVariableID, VariableIDs, nPos))
		{
			//��ӵ������б�
			NewFactors.push_back(*it);

			//ɾ����������ָ��
			it = OldFactors.erase(it);
		}
		else
		{
			//����ָ��
			it++;
		}
	}

	//��������б�Ĵ�С
	if (NewFactors.size() == 0)
	{
		//û�����Ӱ�������������ֱ�ӷ���
		return;
	}
	else
	{
		//�����µĳ˻�����PSAI
		CFactor psai = NewFactors[0];

		
		///////////////////////////////////////////////////////////////////////////
		//����2�����ӻ�
		for (unsigned int i = 1; i < NewFactors.size(); i++)
		{
			//�������ӻ�
			psai = psai*NewFactors[i];
		}


		//////////////////////////////////////////////////////////////////////////
		//����3����͵���������
		psai.SumOutVariable(nVariableID);


		//����4�������ӻ���ӵ������б�
		OldFactors.push_back(psai);
	}
}

