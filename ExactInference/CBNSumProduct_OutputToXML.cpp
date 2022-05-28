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
#include <format>

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

	//������Ԫ�ز�����
	TiXmlElement *pRootElement = new TiXmlElement("Probilities");
	doc.LinkEndChild(pRootElement);

	//�������в�ѯ���
	for (fval_t qr : m_QueryResults)
	{
		TiXmlElement* pProbability = new TiXmlElement("Probability");

		//���ø���ȡֵ
		pProbability->SetAttribute("PROBABILITY_VALUE", std::format("{:.6f}", qr).c_str());

		//���Ӹ��ʵ������б�
		pRootElement->LinkEndChild(pProbability);
	}

	//��ȡ��ǰ����·��
	CString sFileName = theApp.m_sWorkPath + _T("\\Data\\Output.xml");

	//����XML�ļ�
	USES_CONVERSION;
	doc.SaveFile(T2A(sFileName));

	//�ͷ��ڴ�
	doc.Clear();

	//�Զ����ļ�
	ShellExecute(NULL, _T("open"), sFileName, NULL, NULL, SW_SHOWNORMAL);
}