////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_Init.cpp
// 初始化，形成校准的团树
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//初始化
void CCliqueTree::Init()
{
	auto& x = *this;
	////////////////////////////////////////////////////////////////
	//步骤1：读取团树
	Read_CT();


	////////////////////////////////////////////////////////////////
	//步骤2：读取查询任务，包括边缘变量、给定变量ID和值ID
	Read_QueryCT();


	////////////////////////////////////////////////////////////////
	//步骤3：预处理
	Preprocess();


	//步骤4：向上传递信息
	UpwardPass();
	

	//步骤5：向下传递信息
	DownwardPass();
}