/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CFactorTree_Read_QueryCT.cpp
//��  �ܣ�		��ȡ����Clique�Ĳ�ѯ���񡣰�����Ե�ڵ㡢�����ڵ��ID��ֵID
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��30��
//��  �£�		2021��03��31��
//��  �£�		2021��04��01��
//��  �£�		2021��04��10��
//��  �£�		2021��04��12��
//��  �£�		2021��05��18��
//��  �ȣ�		150��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "ExactInference.h"							//Ӧ�ó�����ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//�����ⲿ����
extern CExactInferenceApp theApp;


//��  �ƣ�		Read_QueryCT()
//��  �ܣ�		��ȡ������ѯ���񡣰�����ѯ�ڵ㡢�����ڵ�
//��  ����		��
//����ֵ��		��
void CCliqueTree::Read_QueryCT()
{
	//��ȡ��ǰ����·��
	CString sFileName = CString(theApp.m_sWorkPath);
	sFileName = sFileName + _T("\\Data");
	sFileName = sFileName + _T("\\CliqueTree_Query.xml");


	//�����ļ�������ļ������ڣ���ֱ�ӷ���
	CFileFind findWenJian;								//�ļ�����
	BOOL bWenJian = findWenJian.FindFile(sFileName);	//�����ļ��Ƿ����
	//���û�з����ļ�����ֱ�ӷ���
	if (!bWenJian)
	{
		//ֱ�ӷ���
		return;
	}


	//���ļ�
	TiXmlDocument aDoc(MapCStringToString(sFileName).c_str());

	//�����ļ��Ƿ�ɹ�
	if (!aDoc.LoadFile())
	{
		//��ʾ
		AfxMessageBox(_T("��CliqueTree_Query.xmlʧ��:"));

		//�˳�
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
				query_variable.nVariableID = TransformStringToInt(sTemp);

				//��ȡ��ѯ����ֵID
				sTemp = GetAttribute(pVariable, "VALUE");

				//�����Ƿ����ֵ
				query_variable.nValueID = TransformStringToInt(sTemp);//��ȡ�ڵ�ֵ��ID

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
				given_variable.nVariableID = TransformStringToInt(sTemp);

				//��ȡ��ѯ����ֵID
				sTemp = GetAttribute(pVariable, "VALUE");

				//�����Ƿ����ֵ
				given_variable.nValueID = TransformStringToInt(sTemp);//��ȡ�ڵ�ֵ��ID

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