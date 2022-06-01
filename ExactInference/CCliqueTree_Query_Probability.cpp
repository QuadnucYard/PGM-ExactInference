////////////////////////////////////////////////////////////////////////////////
// CCliqueTree_Query_Marginal.cpp
// 查询边缘概率
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CCliqueTree.h"


//查询概率
void CCliqueTree::Query_Probability(const CT_QUERY& query, const fidset& QueryVariableIDs, const CClique& startClique)
{
	//获取开始团ID
	fid_t nStartCliqueID = startClique.GetID();

	//获取开始团包含的查询变量集合
	fidset StartVariableIDs = qy::set_intersection<fidset>(startClique.GetVariableIDs(), QueryVariableIDs);

	//定义团、并初始化为开始团
	CClique theClique = startClique;

	std::queue<fid_t> OPEN;
	OPEN.push(nStartCliqueID);
	fidset CLOSED;

	//步骤1：广度优先构造查询涉及的子树、并同时计算当前因子
	while (!OPEN.empty())
	{
		fid_t nID = OPEN.front();
		OPEN.pop();
		//将当前团ID加入CLOSED表，以免出现可逆动作
		CLOSED.insert(nID);

		//查找当前团ID的后继
		auto er = m_CTEdges.equal_range(nID);
		for (auto p : std::ranges::subrange(er.first, er.second)) {
			//获取后继团ID
			fid_t nChildID = p.second;

			//检查后继节点是否在CLOSED表。如果已经存在，则不需要入队
			if (CLOSED.contains(nChildID)) continue;

			//将当前因子和后继团做因子积
			//做和割集的因子除。注意：要找到经过校准的割集
			theClique = theClique
				* GetCliquePosByID(nChildID)
				/ GetReadySEPSet(nID, nChildID).clique;

			OPEN.push(nChildID);

			//检查是否已经覆盖所有变量
			//定义新增变量ID集合
			fidset AddVariableIDs = qy::set_intersection<fidset>(GetCliquePosByID(nChildID).GetVariableIDs(), QueryVariableIDs);

			//添加到开始变量ID集合。即当前变量ID集合
			StartVariableIDs.insert(AddVariableIDs.begin(), AddVariableIDs.end());
			//检查变量ID个数是否已经覆盖所有查询变量  query包含于start
			if (std::ranges::includes(StartVariableIDs, QueryVariableIDs))
			{
				//已经覆盖所有查询变量ID，终止所有循环
				break;
			}

		}
	}

	//步骤2：针对因子求和掉不必要的变量
	//定义求和掉的变量集合
	fidlist SumOutVariableIDs = qy::set_difference<fidlist>(theClique.GetVariableIDs(), QueryVariableIDs);
	//求和掉多余变量
	for (fid_t var : SumOutVariableIDs)
	{
		theClique.SumOutVariable(var);
	}

	//步骤3：根据给定变量简化团
	for (const CT_GROUNDING_VARIABLE& var : query.GivenVariables)
	{
		theClique.ReduceGivenVariable(var.nVariableID, var.nValueID);
	}

	//步骤4：归一化团
	theClique.Normalize();

	//步骤5：获取概率
	fidlist VariableIDs = query.MarginalVariables | std::views::transform(&CT_GROUNDING_VARIABLE::nVariableID) | qy::views::to<fidlist>;
	fidlist ValueIDs = query.MarginalVariables | std::views::transform(&CT_GROUNDING_VARIABLE::nValueID) | qy::views::to<fidlist>;

	//添加概率到查询结果
	m_CTQueryResults.push_back(theClique.Query(VariableIDs, ValueIDs));
}