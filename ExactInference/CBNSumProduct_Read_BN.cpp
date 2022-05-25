/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CBNSumProduct_Read_BN.cpp
//��  �ܣ�		��ȡ��Ҷ˹����ṹ�Ͳ���
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��01��
//��  �£�		2021��03��06��
//��  �£�		2021��03��08��
//��  �£�		2021��03��23��
//��  �ȣ�		170��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "ExactInference.h"							//Ӧ�ó�����ͷ�ļ�
#include "CBNSumProduct.h"							//��Ҷ˹���羫ȷ������ͷ�ļ������úͻ�����������
#include "Helper.h"									//��������ͷ�ļ�


//�����ⲿ����
extern CExactInferenceApp theApp;


//��  �ƣ�		Read_BN()
//��  �ܣ�		��ȡ��Ҷ˹����ṹ�Ͳ���
//��  ����		��
//����ֵ��		��
void CBNSumProduct::Read_BN()
{
	//��ȡ��ǰ����·��
	CString sFileName = CString(theApp.m_sWorkPath);
	sFileName = sFileName + _T("\\Data");
	sFileName = sFileName + _T("\\BayesianNetwork.xml");

	
	//�����ļ�������ļ������ڣ���ֱ�ӷ���
	CFileFind findWenJian;								//�ļ�����
	BOOL bWenJian = findWenJian.FindFile(sFileName);	//�����ļ��Ƿ����
	//���û�з����ļ�����ֱ�ӷ���
	if (!bWenJian)
	{
		//��ʾ
		AfxMessageBox(_T("��Ҷ˹����ṹ�Ͳ����ļ�BayesianNetwork.xml������"));
		
		//����
		return;
	}

	
	//���ļ�
	TiXmlDocument aDoc(MapCStringToString(sFileName).c_str());

	//�����ļ��Ƿ�ɹ�
	if (!aDoc.LoadFile())
	{
		//��ʾ
		AfxMessageBox(_T("��BayesianNetwork_Part.xmlʧ��:"));

		//�˳�
		return exit(0);
	}

	//��ȡ�����
	TiXmlElement *pRoot = aDoc.RootElement();


	////////////////////////////////////////////////////////////////////////////////////////////////
	//����1����ȡ�ڵ��
	TiXmlElement* pNodes = pRoot->FirstChildElement();
	if (pNodes != NULL)
	{
		//��ȡ�ڵ�
		TiXmlElement* pNode = pNodes->FirstChildElement();
		//�������нڵ�
		while (pNode != NULL)
		{
			//��ȡ�ڵ�����
			BN_NODE bn_node;
			//01 �ڵ�ID
			string sTemp = GetAttribute(pNode, "ID");
			bn_node.nID = TransformStringToInt(sTemp);
			//02 �ڵ�����
			bn_node.sName = GetAttribute(pNode, "NAME");			
			//03 �ڵ����Ƽ�д
			bn_node.sAbbreviation = GetAttribute(pNode, "ABBREVIATION");
			//04 �ڵ�ֵ�ĸ���
			sTemp = GetAttribute(pNode, "NUMBER_OF_VALUES");
			bn_node.nNumberOfValues=TransformStringToInt(sTemp);
			//05 ���ڵ����
			sTemp = GetAttribute(pNode, "NUMBER_OF_PARENTS");
			bn_node.nNumberOfParents = TransformStringToInt(sTemp);

			//06 ���ڵ��б�
			if (bn_node.nNumberOfParents != 0)
			{
				sTemp = GetAttribute(pNode, "PARENT_IDS");
				vector<string> IDs;
				//��ȡ˫��ID�б�
				Separate(sTemp, IDs);
				//ת��Ϊ�޷�������
				for (unsigned int i = 0; i < IDs.size(); i++)
				{
					//��ȡ����
					unsigned int nID = TransformStringToInt(IDs[i]);

					//���븸�ڵ�ID�б�
					bn_node.ParentIDs.push_back(nID);
				}
			}
			
			//07 CPT�еĸ���ֵ
			sTemp = GetAttribute(pNode, "CPT");
			vector<string> Probabilities;
			//�з�
			Separate(sTemp, Probabilities);
			//ת��Ϊ˫������
			for (unsigned int i = 0; i < Probabilities.size(); i++)
			{
				//��ȡ˫������
				double fProb = TransformStringToDouble(Probabilities[i]);

				//����CPTÿ�е�ֵ
				bn_node.CPTRowValues.push_back(fProb);
			}

			//��ӵ��ڵ��
			m_Nodes.push_back(bn_node);


			//���½ڵ�
			pNode = pNode->NextSiblingElement();
		}
	}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//����2����ȡ�߱�
	TiXmlElement* pEdges = pNodes->NextSiblingElement();
	if (pEdges != NULL)
	{
		TiXmlElement* pEdge = pEdges->FirstChildElement();

		//���ָ���Ƿ�Ϊ��
		while (pEdge != NULL)
		{
			//��ȡ������
			BN_EDGE bn_edge;
			//01 ��ID
			string sTemp = GetAttribute(pEdge, "ID");
			bn_edge.nID = TransformStringToInt(sTemp);
			//02 �ߵ����ID
			sTemp = GetAttribute(pEdge, "START_NODE_ID");
			bn_edge.nStartNodeID = TransformStringToInt(sTemp);
			//03 �ߵ��յ�ID
			sTemp = GetAttribute(pEdge, "END_NODE_ID");
			bn_edge.nEndNodeID = TransformStringToInt(sTemp);

			//��ӵ��߱�
			m_Edges.push_back(bn_edge);


			//���±�ָ��
			pEdge = pEdge->NextSiblingElement();
		}
	}
	
	
	//�ͷ��ļ���ռ�ڴ�
	aDoc.Clear();
}