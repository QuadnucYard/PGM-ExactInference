////////////////////////////////////////////////////////////////////////////////
// CFactor_SumOutVariable.cpp
// 根据给定变量，对因子求和
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CFactor.h"
#include <unordered_map>


void CFactor::SumOutVariable(fid_t nVariableID)
{
	if (size_t nRemovePos = qy::ranges::index_of(m_VariableIDs, nVariableID); nRemovePos != -1) 
	{
		//找到变量ID，需要进行求和化简

		//步骤1：化简变量ID的列表
		m_VariableIDs.erase(m_VariableIDs.begin() + nRemovePos);

		//步骤2：化简变量值的ID列表  删除行中冗余的变量值
		for (FACTOR_ROW& t : m_FactorRows)
			t.ValueIDs.erase(t.ValueIDs.begin() + nRemovePos);

		//步骤3：对因子中相应的行求和  把ValueIDs相同的行合并到第一次出现的行
		for (auto it = m_FactorRows.begin(); it != m_FactorRows.end();)
		{
			auto jt = std::ranges::find(m_FactorRows.begin(), it, it->ValueIDs, &FACTOR_ROW::ValueIDs);
			if (jt != it) {
				jt->fValue += it->fValue;
				it = m_FactorRows.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
}
