////////////////////////////////////////////////////////////////////////////////
// ExactInferenceDlg_User.cpp
// 响应用户命令
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ExactInferenceDlg.h"
#include "CBNSumProduct.h"
#include "CBNSumProduct_IO.h"
#include "CCliqueTree.h"
#include "CCliqueTree_IO.h"
#include "Helper.h"


//响应初始化命令
void CExactInferenceDlg::OnBnClickedButtonBnInit()
{
	try {
		CBNSumProduct theBN = CBNSumProductReader::Read_BN("BayesianNetwork");
		theBN.Preprocess();

		AfxMessageBox(L"完成读取贝叶斯网络的结构和参数，并开始推理……请按确定键继续");

		auto queries = CBNSumProductReader::Read_Query("BayesianNetwork_Query");
		CBNSumProductWriter::OutputResult("Output", theBN.Query(queries));

	} catch (std::exception e) {
		msgerr(e.what());
	}

}


//响应基于团树的初始化、查询命令
void CExactInferenceDlg::OnBnClickedButtonCt()
{
	try {
		CCliqueTree theCliqueTree = CCliqueTreeReader::Read_CT("CliqueTree");
		theCliqueTree.Init();

		AfxMessageBox(L"完成读取团树和校准，准备开始推理……请按确定键继续");

		auto queries = CCliqueTreeReader::Read_Query("CliqueTree_Query");
		CCliqueTreeWriter::OutputResult("CliqueTree_Output", theCliqueTree.Query(queries));

	} catch (std::exception e) {
		msgerr(e.what());
	}
}