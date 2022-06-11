////////////////////////////////////////////////////////////////////////////////
// ExactInferenceDlg_User.cpp
// ��Ӧ�û�����
// Originated by	��־ǿ
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ExactInferenceDlg.h"
#include "CBNSumProduct.h"
#include "CBNSumProduct_IO.h"
#include "CliqueTreeMethod.h"
#include "CCliqueTree_IO.h"
#include "Helper.h"


//��Ӧ��ʼ������
void CExactInferenceDlg::OnBnClickedButtonBnInit()
{
	using namespace pgm;
	try {
		CBNSumProduct theBN(CBNSumProductReader::Read_BN("BayesianNetwork"));

		AfxMessageBox(L"��ɶ�ȡ��Ҷ˹����Ľṹ�Ͳ��������밴ȷ��������");

		auto queries = CBNSumProductReader::Read_Query("BayesianNetwork_Query");
		CBNSumProductWriter::OutputResult("Output", theBN.query(queries));

	} catch (std::exception e) {
		msgerr(e.what());
	}
}


//��Ӧ���������ĳ�ʼ������ѯ����
void CExactInferenceDlg::OnBnClickedButtonCt()
{
	using namespace pgm;
	try {
		CliqueTreeMethod theCT(CCliqueTreeReader::Read_CT("CliqueTree"));

		AfxMessageBox(L"��ɶ�ȡ������У׼��׼����ʼ�������밴ȷ��������");

		auto queries = CCliqueTreeReader::Read_Query("CliqueTree_Query");
		CCliqueTreeWriter::OutputResult("CliqueTree_Output", theCT.query(queries));

	} catch (std::exception e) {
		msgerr(e.what());
	}
}