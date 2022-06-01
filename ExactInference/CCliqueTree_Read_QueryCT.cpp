////////////////////////////////////////////////////////////////////////////////
// CFactorTree_Read_QueryCT.cpp
// ��ȡ����Clique�Ĳ�ѯ���񡣰�����Ե�ڵ㡢�����ڵ��ID��ֵID
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ExactInference.h"
#include "CCliqueTree.h"


//�����ⲿ����
extern CExactInferenceApp theApp;


//��ȡ������ѯ���񡣰�����ѯ�ڵ㡢�����ڵ�
void CCliqueTree::Read_QueryCT()
{
	//��ȡ��ǰ����·��
	namespace fs = std::filesystem;
	fs::path sPath = fs::current_path() / "Data" / "CliqueTree_Query.xml";
	if (!fs::exists(sPath))
	{
		return;
	}

	TiXmlDocument aDoc(sPath.string().c_str());
	if (!aDoc.LoadFile())
	{
		AfxMessageBox(_T("��CliqueTree_Query.xmlʧ��:"));
		return exit(0);
	}

	//������ʱ����
	string sTemp;

	//��ȡ�����
	TiXmlElement *pQueries = aDoc.RootElement();
	TiXmlElement *pQuery = pQueries->FirstChildElement();
	while (pQuery != NULL)
	{
		//����������ѯ
		CT_QUERY ct_query;

		////////////////////////////////////////////////////////////////////////////////////////////
		//����1����ȡ��Եָ��
		TiXmlElement* pMarginal = pQuery->FirstChildElement();
		//�������б�Ե
		if (pMarginal != NULL)
		{
			//����1����ȡ����ָ��
			TiXmlElement* pVariable = pMarginal->FirstChildElement();
			
			//������ѯ����ָ��
			while (pVariable != NULL)
			{
				//����ʵ��������
				CT_GROUNDING_VARIABLE query_variable;

				//��ȡ��ѯ����ID
				string sTemp = GetAttribute(pVariable, "ID");
				query_variable.nVariableID = stoi_(sTemp);

				//��ȡ��ѯ����ֵID
				sTemp = GetAttribute(pVariable, "VALUE");

				//�����Ƿ����ֵ
				query_variable.nValueID = stoi_(sTemp);//��ȡ�ڵ�ֵ��ID

				//��ӵ���ѯ������
				ct_query.MarginalVariables.push_back(query_variable);

				//���²�ѯ����ָ��
				pVariable = pVariable->NextSiblingElement();
			}
		}


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//����2����ȡ��������ָ��
		TiXmlElement* pGiven = pMarginal->NextSiblingElement();
		if (pGiven != NULL)
		{
			//����1����ȡ����ָ��
			TiXmlElement* pVariable = pGiven->FirstChildElement();

			//������ѯ����ָ��
			while (pVariable != NULL)
			{
				//����ʵ��������
				CT_GROUNDING_VARIABLE given_variable;

				//��ȡ��ѯ����ID
				string sTemp = GetAttribute(pVariable, "ID");
				given_variable.nVariableID = stoi_(sTemp);

				//��ȡ��ѯ����ֵID
				sTemp = GetAttribute(pVariable, "VALUE");

				//�����Ƿ����ֵ
				given_variable.nValueID = stoi_(sTemp);//��ȡ�ڵ�ֵ��ID

				//��ӵ���ѯ������
				ct_query.GivenVariables.push_back(given_variable);

				//���²�ѯ����ָ��
				pVariable = pVariable->NextSiblingElement();
			}
		}


		//��ӵ���ѯ�б�
		m_CTQueries.push_back(ct_query);

		//���²�ѯָ��
		pQuery = pQuery->NextSiblingElement();
	}//������ѯ�ڵ�


	//�ͷ��ļ���ռ�ڴ�
	aDoc.Clear();
}