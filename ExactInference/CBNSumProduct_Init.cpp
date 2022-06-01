/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CBNSumProduct_Init.cpp
//功  能：		初始化
//开发者：		高志强
//日  期：		2021年03月01日
//更  新：		2021年03月08日
//更  新：		2021年03月23日
//长  度：		40行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CBNSumProduct.h"							//贝叶斯网络精确推理类头文件，采用和积变量消除法


//名  称：		Init()
//功  能：		初始化
//参  数：		无
//返回值：		无
void CBNSumProduct::Init()
{
	////////////////////////////////////////////////////////////////
	//步骤1：读取贝叶斯网络结构和参数
	Read_BN();


	////////////////////////////////////////////////////////////////
	//步骤2：读取查询任务，包括查询变量、给定变量、变量消除顺序
	Read_Query();


	////////////////////////////////////////////////////////////////
	//步骤3：预处理
	Preprocess();
}