/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_Read_CT.cpp
//��  �ܣ�		��ȡ����CliqueTree
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��30��
//��  �£�		2021��04��12��
//��  �£�		2021��05��18��
//��  �ȣ�		220��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "ExactInference.h"							//Ӧ�ó�����ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//�����ⲿ����
extern CExactInferenceApp theApp;


//��  �ƣ�		Read_CT()
//��  �ܣ�		��ȡ����
//��  ����		��
//����ֵ��		��
void CCliqueTree::Read_CT()
{
	//��ȡ��ǰ����·��
	CString sFileName = CString(theApp.m_sWorkPath);
	sFileName = sFileName + _T("\\Data");
	sFileName = sFileName + _T("\\CliqueTree.xml");


	//�����ļ�������ļ������ڣ���ֱ�ӷ���
	CFileFind findWenJian;								//�ļ�����
	BOOL bWenJian = findWenJian.FindFile(sFileName);	//�����ļ��Ƿ����
	//���û�з����ļ�����ֱ�ӷ���
	if (!bWenJian)
	{
		//��ʾ
		AfxMessageBox(_T("�����ļ�CliqueTree.xml������"));

		//����
		return;
	}


	//���ļ�
	TiXmlDocument aDoc(MapCStringToString(sFileName).c_str());

	//�����ļ��Ƿ�ɹ�
	if (!aDoc.LoadFile())
	{
		//��ʾ
		AfxMessageBox(_T("��CliqueTree.xmlʧ��:"));

		//�˳�
		return exit(0);
	}

	//��ȡ�������
	TiXmlElement *pCliqueTree = aDoc.RootElement();
	//������ʱ����
	string sTemp;

	//����Ƿ�Ϸ�
	if (pCliqueTree != NULL)
	{
		//������ʱ����
		sTemp = GetAttribute(pCliqueTree, "ROOT_ID");
		//��ȡ�����ĸ���ID
		m_nRootID = TransformStringToInt(sTemp);
	}
	else
	{
		//��ʾ
		AfxMessageBox(_T("���ڵ�CliqueTree������"));

		//�˳�
		return exit(0);
	}
	

	////////////////////////////////////////////////////////////////////////////////////////////////
	//����1����ȡ������
	TiXmlElement* pVariables = pCliqueTree->FirstChildElement();
	if (pVariables != NULL)
	{
		//��ȡ����
		TiXmlElement* pVariable = pVariables->FirstChildElement();

		//�������б���
		while (pVariable != NULL)
		{
			//��ȡ����ID
			sTemp = GetAttribute(pVariable, "ID");
			unsigned int nVariableID = TransformStringToInt(sTemp);
			//��ȡ��������
			string sVariableName = GetAttribute(pVariable, "NAME");

			//��ӵ�����ID�����Ƶ�ӳ��
			m_VariableID2Names.insert(make_pair(nVariableID, sVariableName));
			
			//���±���ָ��
			pVariable = pVariable->NextSiblingElement();
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	//����2����ȡ�ű�
	TiXmlElement* pCliques = pVariables->NextSiblingElement();
	if (pCliques != NULL)
	{
		//��ȡ��
		TiXmlElement* pClique = pCliques->FirstChildElement();

		//����������
		while (pClique != NULL)
		{
			//���������ڵ�
			CT_NODE ct_node;

			//������ʱ����
			sTemp = GetAttribute(pClique, "ID");
			//��ȡ�ŵ�ID
			ct_node.nID = TransformStringToInt(sTemp);

			//��ȡ�ŵı���ID�б�
			sTemp = GetAttribute(pClique, "VARIABLE_IDS");
			vector<string> IDs;
			//��ȡ˫��ID�б�
			Separate(sTemp, IDs);
			//ת��Ϊ�޷�������
			for (unsigned int i = 0; i < IDs.size(); i++)
			{
				//��ȡ����
				unsigned int nID = TransformStringToInt(IDs[i]);
				//�������ID�б�
				ct_node.VariableIDs.push_back(nID);
			}

			//��ȡ��
			TiXmlElement* pRow = pClique->FirstChildElement();
			//������
			while (pRow != NULL)
			{
				//����������
				CT_FACTOR_ROW factor_row;

				//��ȡ������ֵ
				sTemp = GetAttribute(pRow, "VALUE");
				factor_row.fValue = TransformStringToDouble(sTemp);

				//��ȡ����
				TiXmlElement* pVariable = pRow->FirstChildElement();
				//��������
				while (pVariable != NULL)
				{
					//��ȡ����ID�ͱ���ֵ
					sTemp = GetAttribute(pVariable, "ID");
					unsigned int nVariableID = TransformStringToInt(sTemp);
					sTemp = GetAttribute(pVariable, "VALUE");
					unsigned int nValueID = TransformStringToInt(sTemp);

					//��ӵ�ʵ����������
					factor_row.ValueIDs.push_back(nValueID);

					//���±���ָ��
					pVariable = pVariable->NextSiblingElement();
				}

				//��ӵ������б�
				ct_node.FactorRows.push_back(factor_row);

				//������ָ��
				pRow = pRow->NextSiblingElement();
			}

			//��ӵ��ڵ��
			m_CTNodes.push_back(ct_node);

			//������ָ��
			pClique = pClique->NextSiblingElement();
		}
	}//END IF pClique!=NULL


	///////////////////////////////////////////////////////////////////////////////////////////////
	//����3����ȡ�߱�
	TiXmlElement* pEdges = pCliques->NextSiblingElement();
	if (pEdges != NULL)
	{
		//��ȡ��
		TiXmlElement* pEdge = pEdges->FirstChildElement();

		//����Ƿ�Ϊ��
		while (pEdge != NULL)
		{			
			//01 �ߵ����ID
			sTemp = GetAttribute(pEdge, "START_CLIQUE_ID");
			unsigned int nStartCliqueID = TransformStringToInt(sTemp);
			//02 �ߵ��յ�ID
			sTemp = GetAttribute(pEdge, "END_CLIQUE_ID");
			unsigned int nEndCliqueID = TransformStringToInt(sTemp);

			//��ӵ��߱�ע�⣺����˫��ӳ��
			m_CTEdges.insert(make_pair(nStartCliqueID,nEndCliqueID));
			//˫���ӳ��
			m_CTEdges.insert(make_pair(nEndCliqueID, nStartCliqueID));

			//���±�ָ��
			pEdge = pEdge->NextSiblingElement();
		}
	}


	//�ͷ��ļ���ռ�ڴ�
	aDoc.Clear();
}