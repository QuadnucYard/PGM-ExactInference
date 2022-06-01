////////////////////////////////////////////////////////////////////////////////
// CClique_SumOutVariable.cpp
// 根据给定变量，对团求和
// Originated by	高志强
// Refined    by	QuadnucYard
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CClique.h"


//根据给定变量，对团求和
void CClique::SumOutVariable(fid_t nVariableID)
{
	if (size_t nRemovePos = qy::ranges::index_of(m_VariableIDs, nVariableID); nRemovePos != -1)
	{
		//步骤1：化简变量ID的列表
		m_VariableIDs.erase(m_VariableIDs.begin() + nRemovePos);

		//步骤2：化简变量值的ID列表  删除行中冗余的变量值
		for (CliqueRow& t : m_CliqueRows)
			t.ValueIDs.erase(t.ValueIDs.begin() + nRemovePos);

		//步骤3：对因子中相应的行求和  把ValueIDs相同的行合并到第一次出现的行
		for (auto it = m_CliqueRows.begin(); it != m_CliqueRows.end();)
		{
			auto jt = std::ranges::find(m_CliqueRows.begin(), it, it->ValueIDs, &CliqueRow::ValueIDs);
			if (jt != it) {
				jt->fValue += it->fValue;
				it = m_CliqueRows.erase(it);
			} else
			{
				it++;
			}
		}
	}
}
