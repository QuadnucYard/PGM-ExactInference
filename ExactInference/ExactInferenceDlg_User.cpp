/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		ExactInferenceDlg_User.cpp
//功  能：		响应用户命令
//开发者：		高志强
//日  期：		2021年02月20日
//更  新：		
//长  度：		70行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ExactInference.h"
#include "ExactInferenceDlg.h"
#include "CBNSumProduct.h"


//响应初始化命令
void CExactInferenceDlg::OnBnClickedButtonBnInit()
{
	CBNSumProduct theBN;
	theBN.Init();
	AfxMessageBox(_T("完成读取贝叶斯网络的结构和参数，并开始推理...。请按确定键继续"));
	theBN.Query();
}

