/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CBNSumProduct_OutputToXML.cpp
//��  �ܣ�		�����ѯ�����XML�ļ�
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��10��
//��  �£�		2021��03��24��
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "ExactInference.h"							//Ӧ�ó�����ͷ�ļ�
#include "CBNSumProduct.h"							//��Ҷ˹���羫ȷ������ͷ�ļ������úͻ�����������
#include "tinyxml.h"								//TinyXMLͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//�����ⲿ����
extern CExactInferenceApp theApp;


//��  �ƣ�		OutputJointToXML()
//��  �ܣ�		�����ѯ�����XML�ļ�
//��  ����		��
//����ֵ��		��
void CBNSumProduct::OutputToXML()
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
	for (unsigned int i = 0; i < m_QueryResults.size(); i++)
	{
		//��������Ԫ��
		TiXmlElement* pProbability = new TiXmlElement("Probability");

		//���ø���ȡֵ
		char sTemp[MAX_PATH];
		sprintf_s(sTemp, "%.6f", m_QueryResults[i]);
		pProbability->SetAttribute("PROBABILITY_VALUE", sTemp);
		

		//���Ӹ��ʵ������б�
		pRootElement->LinkEndChild(pProbability);
	}

	//��ȡ��ǰ����·��
	CString sFileName = theApp.m_sWorkPath;
	sFileName = sFileName + _T("\\Data");
	sFileName = sFileName + _T("\\Output.xml");

	//����XML�ļ�
	doc.SaveFile((MapCStringToString(sFileName)).c_str());

	//�ͷ��ڴ�
	doc.Clear();

	//�Զ����ļ�
	ShellExecute(NULL, _T("open"), sFileName, NULL, NULL, SW_SHOWNORMAL);
}