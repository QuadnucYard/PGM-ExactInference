////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_Read_CT.cpp
// ��ȡ����CliqueTree
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ExactInference.h"
#include "CCliqueTree.h"


//�����ⲿ����
extern CExactInferenceApp theApp;


//��ȡ����
void CCliqueTree::Read_CT()
{
	//��ȡ��ǰ����·��
	namespace fs = std::filesystem;
	fs::path sPath = fs::current_path() / "Data" / "CliqueTree.xml";
	if (!fs::exists(sPath))
	{
		AfxMessageBox(_T("�����ļ�CliqueTree.xml������"));
		return;
	}

	TiXmlDocument aDoc(sPath.string().c_str());
	if (!aDoc.LoadFile())
	{
		AfxMessageBox(_T("��CliqueTree.xmlʧ��:"));
		return exit(0);
	}

	TiXmlElement *pCliqueTree = aDoc.RootElement();
	string sTemp;

	if (pCliqueTree != NULL)
	{
		m_nRootID = GetAttributeI(pCliqueTree, "ROOT_ID");
	}
	else
	{
		AfxMessageBox(_T("���ڵ�CliqueTree������"));
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
			unsigned int nVariableID = GetAttributeI(pVariable, "ID");
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

			//��ȡ�ŵ�ID
			ct_node.nID = GetAttributeI(pClique, "ID");

			//��ȡ�ŵı���ID�б�
			sTemp = GetAttribute(pClique, "VARIABLE_IDS");
			vector<string> IDs;
			//��ȡ˫��ID�б�
			Separate(sTemp, IDs);
			//ת��Ϊ�޷�������
			for (unsigned int i = 0; i < IDs.size(); i++)
			{
				//��ȡ����
				unsigned int nID = stoi_(IDs[i]);
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
				factor_row.fValue = stod_(sTemp);

				//��ȡ����
				TiXmlElement* pVariable = pRow->FirstChildElement();
				//��������
				while (pVariable != NULL)
				{
					//��ȡ����ID�ͱ���ֵ
					sTemp = GetAttribute(pVariable, "ID");
					unsigned int nVariableID = stoi_(sTemp);
					sTemp = GetAttribute(pVariable, "VALUE");
					unsigned int nValueID = stoi_(sTemp);

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
			unsigned int nStartCliqueID = stoi_(sTemp);
			//02 �ߵ��յ�ID
			sTemp = GetAttribute(pEdge, "END_CLIQUE_ID");
			unsigned int nEndCliqueID = stoi_(sTemp);

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