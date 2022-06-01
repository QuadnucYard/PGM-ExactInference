/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CCliqueTree_Query_Probability_GetSEPSetPos.cpp
//功  能：		获取割集的位置
//开发者：		高志强
//日  期：		2021年04月12日
//更  新：		
//长  度：		70行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		GetSEPSetPos()
//功  能：		获取割集位置
//参  数：		unsigned int,unsigned int
//返回值：		unsigned int
unsigned int CCliqueTree::GetSEPSetPos(unsigned int nID, unsigned int nChildID)
{
	//遍历所有割集
	for (unsigned int i = 0; i < m_SEPSets.size(); i++)
	{
		//检查边是否相等
		if ((m_SEPSets[i].nStartID == nID && m_SEPSets[i].nEndID == nChildID) || //边有两个方向
			(m_SEPSets[i].nStartID == nChildID && m_SEPSets[i].nEndID == nID))
		{
			//检查割集是否就绪
			if (m_SEPSets[i].bReady == true)
			{
				//返回割集位置
				return i;
			}
		}
	}

	//提示：算法一定能找到割集
}