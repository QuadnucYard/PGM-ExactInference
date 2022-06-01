/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CClique_OutputToXML.cpp
//��  �ܣ�		�����ѯ�����XML�ļ�
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��01��
//��  �£�		2021��05��18��
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "ExactInference.h"							//Ӧ�ó�����ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "tinyxml.h"								//TinyXMLͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//�����ⲿ�������Ի�ȡ��ǰ����·��
extern CExactInferenceApp theApp;


//��  �ƣ�		OutputToXML()
//��  �ܣ�		�����ѯ�����XML�ļ�
//��  ����		��
//����ֵ��		��
void CCliqueTree::OutputToXML()
{
	//����XML�ĵ�
	TiXmlDocument doc;
	//�����ĵ�����
	TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "GBK", "");
	//����������Ϣ���ĵ�
	doc.LinkEndChild(pDecl);

	//������Ԫ��
	TiXmlElement *pRootElement = new TiXmlElement("Probilities");
	//���Ӹ�Ԫ��
	doc.LinkEndChild(pRootElement);


	//�������в�ѯ���
	for (unsigned int i = 0; i < m_CTQueryResults.size(); i++)
	{
		//��������Ԫ��
		TiXmlElement* pProbability = new TiXmlElement("Probability");

		//���ø���ȡֵ
		char sTemp[MAX_PATH];
		sprintf_s(sTemp, "%.6f", m_CTQueryResults[i]);
		pProbability->SetAttribute("PROBABILITY_VALUE", sTemp);


		//���Ӹ��ʵ������б�
		pRootElement->LinkEndChild(pProbability);
	}

	//��ȡ��ǰ����·��
	namespace fs = std::filesystem;
	fs::path sPath = fs::current_path() / "Data" / "CliqueTree_Output.xml";

	//����XML�ļ�
	doc.SaveFile(sPath.string().c_str());

	//�ͷ��ڴ�
	doc.Clear();

	//�Զ����ļ�
	ShellExecute(NULL, L"open", sPath.c_str(), NULL, NULL, SW_SHOWNORMAL);
}