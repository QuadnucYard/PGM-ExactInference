////////////////////////////////////////////////////////////////////////////////
// ExactInferenceDlg_User.cpp
// 响应用户命令
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ExactInference.h"
#include "ExactInferenceDlg.h"
#include "CBNSumProduct.h"
#include "CCliqueTree.h"


//响应初始化命令
void CExactInferenceDlg::OnBnClickedButtonBnInit()
{
	//定义贝叶斯网络对象
	CBNSumProduct theBN;
	
	//初始化
	theBN.Init();
	//提示
	AfxMessageBox(_T("完成读取贝叶斯网络的结构和参数，并开始推理...。请按确定键继续"));
	
	//查询
	theBN.Query();
}


//响应基于团树的初始化、查询命令
void CExactInferenceDlg::OnBnClickedButtonCt()
{
	//定义团树对象
	CCliqueTree theCliqueTree;

	//初始化
	theCliqueTree.Init();
	//提示
	AfxMessageBox(_T("完成读取团树和校准，准备开始推理...。请按确定键继续"));

	//查询
	theCliqueTree.Query();
}
