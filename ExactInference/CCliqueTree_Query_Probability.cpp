/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CCliqueTree_Query_Marginal.cpp
//功  能：		查询边缘概率
//开发者：		高志强
//日  期：		2021年04月11日
//更  新：		2021年04月12日
//更  新：		2021年05月18日
//长  度：		130行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		Query_Probability()
//功  能：		查询概率
//参  数：		CT_QUERY&,set<unsigned int>&,unsigned int
//返回值：		无
void CCliqueTree::Query_Probability(CT_QUERY& query, set<unsigned int>& QueryVariableIDs, unsigned int nStartCliquePos)
{
	//获取开始团ID
	unsigned int nStartCliqueID = m_Cliques[nStartCliquePos].GetID();
	
	//获取开始团包含的查询变量集合
	set<unsigned int> StartVariableIDs;
	GetIntersections(m_Cliques[nStartCliquePos].GetCliqueVariableIDs(), QueryVariableIDs, StartVariableIDs);
	
	//定义团、并初始化为开始团
	CClique theClique = m_Cliques[nStartCliquePos];
	
	//初始化OPEN列表
	queue<unsigned int> OPEN;
	OPEN.push(nStartCliqueID);
	//定义CLOSED表
	set<unsigned int> CLOSED;

	///////////////////////////////////////////////////////////////////////////////////////////
	m_SEPSets;
	//步骤1：广度优先构造查询涉及的子树、并同时计算当前因子
	//检查OPEN表是否为空
	while (OPEN.size() > 0)
	{
		//当前团ID出队
		unsigned int nID = OPEN.front();
		OPEN.pop();

		//将当前团ID加入CLOSED表，以免出现可逆动作
		CLOSED.insert(nID);

		//查找当前团ID的后继
		multimap<unsigned int, unsigned int>::iterator beg = m_CTEdges.lower_bound(nID);
		multimap<unsigned int, unsigned int>::iterator end = m_CTEdges.upper_bound(nID);
		//检查是否存在后继，并依次入队
		while (beg != end)
		{
			//获取后继团ID
			unsigned int nChildID = beg->second;

			//检查后继节点是否在CLOSED表。如果已经存在，则不需要入队
			if (!qy::ranges::includes(CLOSED, nChildID))
			{
				//将当前因子和后继团做因子积
				CClique product_clique = m_Cliques[GetCliquePosByID(nChildID)];
				theClique= theClique*product_clique;

				//做和割集的因子除。注意：要找到经过校准的割集
				unsigned int nSEPSetPos = GetSEPSetPos(nID, nChildID);
				CClique divide_clique = m_SEPSets[nSEPSetPos].clique;
				theClique = theClique/divide_clique;

				//添加到OPEN表
				OPEN.push(nChildID);

				//检查是否已经覆盖所有变量
				//定义新增变量ID集合
				set<unsigned int> AddVariableIDs;
				//获取新增变量ID集合
				GetIntersections(m_Cliques[GetCliquePosByID(nChildID)].GetCliqueVariableIDs(), QueryVariableIDs, AddVariableIDs);

				//添加到开始变量ID集合。即当前变量ID集合
				StartVariableIDs.insert(AddVariableIDs.begin(), AddVariableIDs.end());				
				//检查变量ID个数是否已经覆盖所有查询变量
				if (IsSetContainedIn(QueryVariableIDs,StartVariableIDs))
				{
					//已经覆盖所有查询变量ID，终止所有循环
					goto line10;
				}
			}

			//更新迭代器
			beg++;
		}
	}


	///////////////////////////////////////////////////////////////
	//步骤2：针对因子求和掉不必要的变量
	line10: vector<unsigned int> CurrVariableIDs = theClique.GetCliqueVariableIDs();
	//定义求和掉的变量集合
	vector<unsigned int> SumOutVariableIDs = GetSubstract(CurrVariableIDs, QueryVariableIDs);
	//求和掉多余变量
	for (unsigned int i = 0; i < SumOutVariableIDs.size(); i++)
	{
		//求和掉变量
		theClique.SumOutVariable(SumOutVariableIDs[i]);
	}


	/////////////////////////////////////////////////////////////////////
	//步骤3：根据给定变量简化团
	for (unsigned int i = 0; i < query.GivenVariables.size(); i++)
	{
		//简化因子
		theClique.ReduceGivenVariable(query.GivenVariables[i].nVariableID, query.GivenVariables[i].nValueID);
	}


	////////////////////////////////////////////////////////////////////
	//步骤4：归一化团
	theClique.Normalize();


	////////////////////////////////////////////////////////////////////
	//步骤5：获取概率
	double fProb;
	vector<unsigned int> VariableIDs;
	vector<unsigned int> ValueIDs;
	for (unsigned int i = 0; i < query.MarginalVariables.size(); i++)
	{
		//添加到变量ID表
		VariableIDs.push_back(query.MarginalVariables[i].nVariableID);

		//添加到变量值表
		ValueIDs.push_back(query.MarginalVariables[i].nValueID);
	}

	//对因子进行查询
	fProb = theClique.Query(VariableIDs, ValueIDs);

	//添加概率到查询结果
	m_CTQueryResults.push_back(fProb);
}