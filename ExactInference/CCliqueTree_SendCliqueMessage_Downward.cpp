/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CCliqueTree_SendCliqueMessage_Downward.cpp
//功  能：		向下发送团消息
//开发者：		高志强
//日  期：		2021年04月04日
//更  新：		2021年05月18日
//长  度：		60行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		SendCliqueMessage_Downward()
//功  能：		向下发送团消息
//参  数：		unsigned int
//返回值：		无
void CCliqueTree::SendCliqueMessage_Downward(unsigned int nID,unsigned int nChildID)
{	
	//找到相交的变量ID集合
	set<unsigned int> CommonVariableIDs;

	//获取两个团的变量ID交集
	FindCommonVariableIDs(nID, nChildID, CommonVariableIDs);

	
}