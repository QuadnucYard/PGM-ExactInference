////////////////////////////////////////////////////////////////////////////////
// ExactInferenceDlg_User.cpp
// 响应用户命令
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ExactInferenceDlg.h"
#include "CBNSumProduct.h"
#include "CliqueTreeMethod.h"
#include "CommonIO.h"
#include "Helper.h"


//响应初始化命令
void CExactInferenceDlg::OnBnClickedButtonBnInit()
{
	using namespace pgm;
	try {
		CBNSumProduct theBN(io::readBayesianNetwork("BayesianNetwork"));

		AfxMessageBox(L"完成读取贝叶斯网络的结构和参数……请按确定键继续");

		auto queries = io::readQuery("BayesianNetwork_Query");
		shellOpen(io::outputQueryResult("Output", theBN.query(queries)).c_str());

	} catch (std::exception e) {
		msgerr(e.what());
	}
}


//响应基于团树的初始化、查询命令
void CExactInferenceDlg::OnBnClickedButtonCt()
{
	using namespace pgm;
	try {
		CliqueTreeMethod theCT(io::readCliqueTree("CliqueTree"));

		AfxMessageBox(L"完成读取团树和校准，准备开始推理……请按确定键继续");

		auto queries = io::readQuery("CliqueTree_Query");
		shellOpen(io::outputQueryResult("CliqueTree_Output", theCT.query(queries)).c_str());

	} catch (std::exception e) {
		msgerr(e.what());
	}
}