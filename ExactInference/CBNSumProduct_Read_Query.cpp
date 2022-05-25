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
		AfxMessageBox(_T("��BayesianNetwork_Query.xmlʧ��:"));

		//�˳�
		return exit(0);
	}

	//��ȡ�����
	TiXmlElement *pRoot = aDoc.RootElement();
	TiXmlElement *pQuery = pRoot->FirstChildElement();
	while (pQuery != NULL)
	{
		//�����ѯ
		QUERY query;

		////////////////////////////////////////////////////////////////////////////////////////////
		//����1����ȡ��Եָ��
		TiXmlElement* pMarginal = pQuery->FirstChildElement();
		//�������в�ѯ����
		if (pMarginal != NULL)
		{
			//��ȡ��ѯ����ָ��
			TiXmlElement* pVariable = pMarginal->FirstChildElement();
			//������ѯ����ָ��
			while (pVariable != NULL)
			{
				//����ʵ��������
				GROUNDING_VARIABLE query_variable;

				//��ȡ��ѯ����ID
				string sTemp = GetAttribute(pVariable, "ID");
				query_variable.nNodeID = TransformStringToInt(sTemp);

				//��ȡ��ѯ����ֵID
				sTemp = GetAttribute(pVariable, "VALUE");

				//�����Ƿ����ֵ
				query_variable.nValueID = TransformStringToInt(sTemp);//��ȡ�ڵ�ֵ��ID

				//��ӵ���ѯ������
				query.QueryVariables.push_back(query_variable);

				//���²�ѯ����ָ��
				pVariable = pVariable->NextSiblingElement();
			}
		}


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//����2����ȡ��������ָ��
		TiXmlElement* pGiven = pMarginal->NextSiblingElement();
		if (pGiven != NULL)
		{
			//��ȡ��������ָ��
			TiXmlElement* pVariable = pGiven->FirstChildElement();

			//����������ָ���Ƿ�Ϊ��
			while (pVariable != NULL)
			{
				//����ʵ��������
				GROUNDING_VARIABLE given_variable;

				//��ȡ��������ID
				string sTemp = GetAttribute(pVariable, "ID");
				given_variable.nNodeID = TransformStringToInt(sTemp);

				//��ȡ��������ֵ��ID
				sTemp = GetAttribute(pVariable, "VALUE");

				//�����Ƿ����ֵ
				//��ȡ��������ֵID
				given_variable.nValueID = TransformStringToInt(sTemp);

				//��ӵ���������ֵ��
				query.GivenVariables.push_back(given_variable);

				//���¸�������ָ��
				pVariable = pVariable->NextSiblingElement();
			}
		}


		////////////////////////////////////////////////////////////////////////////////////////////////////
		//����3����ȡɾ������˳��
		TiXmlElement* pEliminate = pGiven->NextSiblingElement();
		if (pEliminate != NULL)
		{
			//��ȡɾ������ID�б�
			string sTemp = GetAttribute(pEliminate, "IDs");

			//����Ƿ�Ϊ��
			if (sTemp != "")
			{
				//ת��Ϊ�ַ��б�
				vector<string>IDs;
				Separate(sTemp, IDs);

				//ת��Ϊ����
				for (unsigned int i = 0; i < IDs.size(); i++)
				{
					//��ȡɾ���ڵ�ID
					unsigned int nID = TransformStringToInt(IDs[i]);

					//��ӵ�ɾ���ڵ㼯��
					query.EliminateVariables.push_back(nID);
				}
			}
		}

		//��ӵ���ѯ�б�
		m_Queries.push_back(query);

		//���²�ѯָ��
		pQuery = pQuery->NextSiblingElement();
	}//������ѯ�ڵ�

	
	//�ͷ��ļ���ռ�ڴ�
	aDoc.Clear();
}