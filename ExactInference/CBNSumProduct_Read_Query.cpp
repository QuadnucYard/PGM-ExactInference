/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CBNSumProduct_Read_Query.cpp
//��  �ܣ�		��ȡ��ѯ���񡣰�����ѯ�ڵ㡢�����ڵ㡢�ڵ�ɾ��˳��
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��06��
//��  �£�		2021��03��08��
//��  �£�		2021��03��23��
//��  �ȣ�		180��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "ExactInference.h"							//Ӧ�ó�����ͷ�ļ�
#include "CBNSumProduct.h"							//��Ҷ˹���羫ȷ������ͷ�ļ������úͻ�����������
#include "Helper.h"									//��������ͷ�ļ�
#include "tinyxmliterator.h"

//�����ⲿ����
extern CExactInferenceApp theApp;


//��  �ƣ�		Read_Query()
//��  �ܣ�		��ȡ��ѯ���񡣰�����ѯ�ڵ㡢�����ڵ㡢ɾ���ڵ�˳��
//��  ����		��
//����ֵ��		��
void CBNSumProduct::Read_Query()
{
	//��ȡ��ǰ����·��
	CString sFileName = CString(theApp.m_sWorkPath);
	sFileName = sFileName + _T("\\Data");
	sFileName = sFileName + _T("\\BayesianNetwork_Query.xml");

	//�����ļ�������ļ������ڣ���ֱ�ӷ���
	CFileFind findWenJian;								//�ļ�����
	//���û�з����ļ�����ֱ�ӷ���
	if (!findWenJian.FindFile(sFileName))
	{
		return;
	}

	//���ļ�
	TiXmlDocument aDoc(MapCStringToString(sFileName).c_str());

	//�����ļ��Ƿ�ɹ�
	if (!aDoc.LoadFile())
	{
		AfxMessageBox(_T("��BayesianNetwork_Query.xmlʧ��:"));
		return exit(0);
	}

	//��ȡ�����
	TiXmlElement* pRoot = aDoc.RootElement();
	for (TiXmlElement& pQuery : pRoot)
	{
		QUERY query;

		////////////////////////////////////////////////////////////////////////////////////////////
		//����1����ȡ��Եָ��
		TiXmlElement* pMarginal = pQuery.FirstChildElement();
		//�������в�ѯ����
		std::transform(begin(pMarginal), end(pMarginal), std::back_inserter(query.QueryVariables),
			[](TiXmlElement& pVariable) { return GROUNDING_VARIABLE(
				GetAttributeI(pVariable, "ID"),
				GetAttributeI(pVariable, "VALUE")
			); });
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//����2����ȡ��������ָ��
		TiXmlElement* pGiven = pMarginal->NextSiblingElement();
		std::transform(begin(pGiven), end(pGiven), std::back_inserter(query.GivenVariables),
			[](TiXmlElement& pVariable) { return GROUNDING_VARIABLE(
				GetAttributeI(pVariable, "ID"),
				GetAttributeI(pVariable, "VALUE")
			); });

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//����3����ȡɾ������˳��

		if (TiXmlElement* pEliminate = pGiven->NextSiblingElement(); pEliminate != NULL)
		{
			//��ȡɾ������ID�б�
			if (string sTemp = GetAttribute(pEliminate, "IDs"); sTemp != "")
			{
				//ת��Ϊ�ַ��б�
				vector<string> IDs;
				Separate(sTemp, IDs);
				std::ranges::transform(IDs, std::back_inserter(query.EliminateVariables), stoi_);
			}
		}

		//��ӵ���ѯ�б�
		m_Queries.push_back(std::move(query));
	}//������ѯ�ڵ�

	//�ͷ��ļ���ռ�ڴ�
	aDoc.Clear();
}