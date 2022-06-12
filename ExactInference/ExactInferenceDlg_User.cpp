////////////////////////////////////////////////////////////////////////////////
// ExactInferenceDlg_User.cpp
// ��Ӧ�û�����
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ExactInferenceDlg.h"
#include "CBNSumProduct.h"
#include "CliqueTreeMethod.h"
#include "CommonIO.h"
#include "Helper.h"


//��Ӧ��ʼ������
void CExactInferenceDlg::OnBnClickedButtonBnInit()
{
	using namespace pgm;
	try {
		CBNSumProduct theBN(io::readBayesianNetwork("BayesianNetwork"));

		AfxMessageBox(L"��ɶ�ȡ��Ҷ˹����Ľṹ�Ͳ��������밴ȷ��������");

		auto queries = io::readQuery("BayesianNetwork_Query");
		shellOpen(io::outputQueryResult("Output", theBN.query(queries)).c_str());

	} catch (std::exception e) {
		msgerr(e.what());
	}
}


//��Ӧ���������ĳ�ʼ������ѯ����
void CExactInferenceDlg::OnBnClickedButtonCt()
{
	using namespace pgm;
	try {
		CliqueTreeMethod theCT(io::readCliqueTree("CliqueTree"));

		AfxMessageBox(L"��ɶ�ȡ������У׼��׼����ʼ�������밴ȷ��������");

		auto queries = io::readQuery("CliqueTree_Query");
		shellOpen(io::outputQueryResult("CliqueTree_Output", theCT.query(queries)).c_str());

	} catch (std::exception e) {
		msgerr(e.what());
	}
}