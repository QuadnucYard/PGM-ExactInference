/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CBNSumProduct_Read_Query.cpp
//��  �ܣ�		��ȡ��ѯ���񡣰�����ѯ�ڵ㡢�����ڵ㡢�ڵ�ɾ��˳��
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��06��
//��  �£�		2021��03��08��
//��  �£�		2021��03��23��
//��  �ȣ�		180��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ExactInference.h"
#include "CBNSumProduct.h"
#include "tinyxmliterator.h"

extern CExactInferenceApp theApp;

//��ȡ��ѯ���񡣰�����ѯ�ڵ㡢�����ڵ㡢ɾ���ڵ�˳��
void CBNSumProduct::Read_Query()
{
	//��ȡ��ǰ����·��
	const char* sFileName = strcat(theApp.m_sWorkPath, "\\Data\\BayesianNetwork_Query.xml");

	//�����ļ�������ļ������ڣ���ֱ�ӷ���
	if (!CFileFind().FindFile(CString(sFileName))) return;

	//���ļ�
	TiXmlDocument aDoc(sFileName);
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

		//����1����ȡ��Եָ��
		TiXmlElement* pMarginal = pQuery.FirstChildElement();
		std::transform(begin(pMarginal), end(pMarginal), std::back_inserter(query.QueryVariables),
			[](TiXmlElement& pVariable) { return GROUNDING_VARIABLE(
				GetAttributeI(pVariable, "ID"),
				GetAttributeI(pVariable, "VALUE")
			); });

		//����2����ȡ��������ָ��
		TiXmlElement* pGiven = pMarginal->NextSiblingElement();
		std::transform(begin(pGiven), end(pGiven), std::back_inserter(query.GivenVariables),
			[](TiXmlElement& pVariable) { return GROUNDING_VARIABLE(
				GetAttributeI(pVariable, "ID"),
				GetAttributeI(pVariable, "VALUE")
			); });

		//����3����ȡɾ������˳��
		if (TiXmlElement* pEliminate = pGiven->NextSiblingElement(); pEliminate != NULL)
		{
			//��ȡɾ������ID�б�
			if (std::string sTemp = GetAttribute(pEliminate, "IDs"); sTemp != "")
			{
				query.EliminateVariables = sTemp
					| qy::views::tokenize(std::regex("[\\s,;������]+"))
					| std::views::transform(stoi_)
					| qy::views::to<fidlist>;
			}
		}

		m_Queries.push_back(std::move(query));
	}

	aDoc.Clear();
}